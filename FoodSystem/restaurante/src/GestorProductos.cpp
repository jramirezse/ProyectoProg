// GestorProductos.cpp - Implementación del gestor principal

#include "GestorProductos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <algorithm>

GestorProductos::GestorProductos(const std::string& archProd,
                                  const std::string& archInv)
    : archivoProductos(archProd), archivoInventario(archInv)
{}

//  Auxiliares privados 

int GestorProductos::buscarIndicePorId(int id) const {
    for (int i = 0; i < (int)productos.size(); i++)
        if (productos[i].getId() == id) return i;
    return -1;
}

bool GestorProductos::existeId(int id) const {
    return buscarIndicePorId(id) != -1;
}

// Reintenta hasta recibir un entero válido
int GestorProductos::leerEnteroValido(const std::string& msg) const {
    int valor;
    while (true) {
        std::cout << msg;
        std::cin >> valor;
        if (!std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Ingrese un numero entero valido.\n";
    }
}

double GestorProductos::leerDoubleValido(const std::string& msg) const {
    double valor;
    while (true) {
        std::cout << msg;
        std::cin >> valor;
        if (!std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Ingrese un numero valido (ej: 15000.50).\n";
    }
}

std::string GestorProductos::leerLineaNoVacia(const std::string& msg) const {
    std::string entrada;
    while (true) {
        std::cout << msg;
        std::getline(std::cin, entrada);
        if (!entrada.empty()) return entrada;
        std::cout << "  [!] El campo no puede estar vacio.\n";
    }
}

// ── Menús ────────────────────────────────────────────────────

void GestorProductos::menuPrincipal() {
    int opcion;
    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        std::cout << "\n"
                  << "  ╔══════════════════════════════════════╗\n"
                  << "  ║   SISTEMA DE RESTAURANTE - MÓDULO 1  ║\n"
                  << "  ║     PRODUCTOS E INVENTARIO           ║\n"
                  << "  ╠══════════════════════════════════════╣\n"
                  << "  ║  1. Gestión de Productos             ║\n"
                  << "  ║  2. Gestión de Inventario            ║\n"
                  << "  ║  0. Salir                            ║\n"
                  << "  ╚══════════════════════════════════════╝\n";

        opcion = leerEnteroValido("  Seleccione: ");

        switch (opcion) {
            case 1: menuProductos();  break;
            case 2: menuInventario(); break;
            case 0:
                if (!productos.empty()) {
                    try {
                        guardarProductos();
                        guardarInventario();
                        std::cout << "  [OK] Datos guardados.\n";
                    } catch (const std::exception& e) {
                        std::cout << "  [!] Error al guardar: " << e.what() << "\n";
                    }
                }
                std::cout << "  Hasta luego.\n\n";
                break;
            default:
                std::cout << "  [!] Opcion no valida.\n";
        }
    } while (opcion != 0);
}

void GestorProductos::menuProductos() {
    int opcion;
    do {
        std::cout << "\n"
                  << "  ┌─────────────────────────────────────┐\n"
                  << "  │         GESTIÓN DE PRODUCTOS        │\n"
                  << "  ├─────────────────────────────────────┤\n"
                  << "  │  1. Agregar producto                │\n"
                  << "  │  2. Mostrar todos los productos     │\n"
                  << "  │  3. Buscar por ID                   │\n"
                  << "  │  4. Buscar por nombre               │\n"
                  << "  │  5. Modificar producto              │\n"
                  << "  │  6. Desactivar producto             │\n"
                  << "  │  7. Activar producto                │\n"
                  << "  │  8. Guardar en archivo              │\n"
                  << "  │  9. Cargar desde archivo            │\n"
                  << "  │  0. Volver                          │\n"
                  << "  └─────────────────────────────────────┘\n";

        opcion = leerEnteroValido("  Seleccione: ");
        try {
            switch (opcion) {
                case 1: agregarProducto();    break;
                case 2: mostrarTodos();       break;
                case 3: buscarPorId();        break;
                case 4: buscarPorNombre();    break;
                case 5: modificarProducto();  break;
                case 6: desactivarProducto(); break;
                case 7: activarProducto();    break;
                case 8: guardarProductos();   break;
                case 9: cargarProductos();    break;
                case 0: break;
                default: std::cout << "  [!] Opcion no valida.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "  [ERROR] " << e.what() << "\n";
        }
        if (opcion != 0) {
            std::cout << "\n  Presione ENTER para continuar...";
            std::cin.get();
        }
    } while (opcion != 0);
}

void GestorProductos::menuInventario() {
    int opcion;
    do {
        std::cout << "\n"
                  << "  ┌─────────────────────────────────────┐\n"
                  << "  │         GESTIÓN DE INVENTARIO       │\n"
                  << "  ├─────────────────────────────────────┤\n"
                  << "  │  1. Registrar stock inicial         │\n"
                  << "  │  2. Aumentar stock                  │\n"
                  << "  │  3. Disminuir stock                 │\n"
                  << "  │  4. Consultar stock de un producto  │\n"
                  << "  │  5. Mostrar inventario completo     │\n"
                  << "  │  6. Mostrar productos agotados      │\n"
                  << "  │  7. Guardar inventario              │\n"
                  << "  │  8. Cargar inventario               │\n"
                  << "  │  0. Volver                          │\n"
                  << "  └─────────────────────────────────────┘\n";

        opcion = leerEnteroValido("  Seleccione: ");
        try {
            switch (opcion) {
                case 1: registrarStockInicial();      break;
                case 2: aumentarStock();              break;
                case 3: disminuirStock();             break;
                case 4: consultarStock();             break;
                case 5: mostrarInventarioCompleto();  break;
                case 6: mostrarProductosAgotados();   break;
                case 7: guardarInventario();          break;
                case 8: cargarInventario();           break;
                case 0: break;
                default: std::cout << "  [!] Opcion no valida.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "  [ERROR] " << e.what() << "\n";
        }
        if (opcion != 0) {
            std::cout << "\n  Presione ENTER para continuar...";
            std::cin.get();
        }
    } while (opcion != 0);
}

//  Operaciones sobre productos 

void GestorProductos::agregarProducto() {
    std::cout << "\n  --- AGREGAR NUEVO PRODUCTO ---\n";

    int id;
    while (true) {
        id = leerEnteroValido("  ID del producto: ");
        if (!existeId(id)) break;
        std::cout << "  [!] ID " << id << " ya existe. Use otro.\n";
    }

    std::string nombre    = leerLineaNoVacia("  Nombre: ");
    std::string categoria = leerLineaNoVacia("  Categoria: ");

    double precio;
    while (true) {
        precio = leerDoubleValido("  Precio: ");
        if (precio >= 0) break;
        std::cout << "  [!] El precio no puede ser negativo.\n";
    }

    try {
        productos.push_back(Producto(id, nombre, categoria, precio));
        std::cout << "  [OK] Producto '" << nombre << "' agregado.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "  [ERROR] " << e.what() << "\n";
    }
}

void GestorProductos::mostrarTodos() const {
    if (productos.empty()) { std::cout << "\n  [!] No hay productos.\n"; return; }

    std::cout << "\n" << std::string(75, '=') << "\n"
              << "  CATÁLOGO COMPLETO DE PRODUCTOS\n"
              << std::string(75, '-') << "\n"
              << std::left  << std::setw(6)  << "ID"
                            << std::setw(25) << "NOMBRE"
                            << std::setw(15) << "CATEGORIA"
              << std::right << std::setw(12) << "PRECIO"
                            << std::setw(10) << "ESTADO" << "\n"
              << std::string(75, '-') << "\n";

    for (const Producto& p : productos) p.mostrar();

    std::cout << std::string(75, '=') << "\n"
              << "  Total: " << productos.size() << " producto(s)\n";
}

void GestorProductos::buscarPorId() const {
    int id = leerEnteroValido("  ID a buscar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1) {
        std::cout << "  [!] No existe producto con ID " << id << ".\n";
    } else {
        std::cout << "\n" << std::string(75, '-') << "\n";
        std::cout << std::left  << std::setw(6)  << "ID"
                                << std::setw(25) << "NOMBRE"
                                << std::setw(15) << "CATEGORIA"
                  << std::right << std::setw(12) << "PRECIO"
                                << std::setw(10) << "ESTADO" << "\n"
                  << std::string(75, '-') << "\n";
        productos[i].mostrar();
    }
}

void GestorProductos::buscarPorNombre() const {
    std::string busq = leerLineaNoVacia("  Nombre a buscar (parcial): ");
    std::string busqMin = busq;
    std::transform(busqMin.begin(), busqMin.end(), busqMin.begin(), ::tolower);

    bool encontrado = false;
    std::cout << "\n" << std::string(75, '-') << "\n";
    for (const Producto& p : productos) {
        std::string nomMin = p.getNombre();
        std::transform(nomMin.begin(), nomMin.end(), nomMin.begin(), ::tolower);
        if (nomMin.find(busqMin) != std::string::npos) {
            p.mostrar();
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "  [!] Sin resultados.\n";
}

void GestorProductos::modificarProducto() {
    int id = leerEnteroValido("  ID a modificar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1) { std::cout << "  [!] ID no encontrado.\n"; return; }

    std::cout << "\n  Datos actuales:\n";
    productos[i].mostrar();
    std::cout << "\n  (ENTER = mantener valor actual)\n";

    // Nombre
    std::cout << "  Nuevo nombre [" << productos[i].getNombre() << "]: ";
    std::string val; std::getline(std::cin, val);
    if (!val.empty()) {
        try { productos[i].setNombre(val); }
        catch (const std::exception& e) { std::cout << "  [!] " << e.what() << "\n"; }
    }

    // Categoria
    std::cout << "  Nueva categoria [" << productos[i].getCategoria() << "]: ";
    std::getline(std::cin, val);
    if (!val.empty()) {
        try { productos[i].setCategoria(val); }
        catch (const std::exception& e) { std::cout << "  [!] " << e.what() << "\n"; }
    }

    // Precio
    std::cout << "  Nuevo precio [" << productos[i].getPrecio() << "]: ";
    std::getline(std::cin, val);
    if (!val.empty()) {
        try { productos[i].setPrecio(std::stod(val)); }
        catch (...) { std::cout << "  [!] Precio invalido. Sin cambios.\n"; }
    }

    std::cout << "  [OK] Producto modificado.\n";
}

void GestorProductos::desactivarProducto() {
    int id = leerEnteroValido("  ID a desactivar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1)                     { std::cout << "  [!] ID no encontrado.\n"; return; }
    if (!productos[i].isActivo())    { std::cout << "  [!] Ya esta inactivo.\n"; return; }
    productos[i].setActivo(false);
    std::cout << "  [OK] '" << productos[i].getNombre() << "' desactivado.\n";
}

void GestorProductos::activarProducto() {
    int id = leerEnteroValido("  ID a activar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1)                  { std::cout << "  [!] ID no encontrado.\n"; return; }
    if (productos[i].isActivo())  { std::cout << "  [!] Ya esta activo.\n";   return; }
    productos[i].setActivo(true);
    std::cout << "  [OK] '" << productos[i].getNombre() << "' activado.\n";
}

void GestorProductos::guardarProductos() const {
    if (productos.empty()) { std::cout << "  [!] No hay productos para guardar.\n"; return; }
    std::ofstream archivo(archivoProductos);
    if (!archivo.is_open())
        throw std::runtime_error("No se pudo abrir: " + archivoProductos +
                                 "\nVerifique que la carpeta 'data' existe.");
    archivo << "id,nombre,categoria,precio,estado\n";
    for (const Producto& p : productos) archivo << p.toString() << "\n";
    archivo.close();
    std::cout << "  [OK] " << productos.size() << " producto(s) guardado(s).\n";
}

void GestorProductos::cargarProductos() {
    std::ifstream archivo(archivoProductos);
    if (!archivo.is_open())
        throw std::runtime_error("No se pudo abrir: " + archivoProductos);

    productos.clear();
    std::string linea;
    std::getline(archivo, linea); // saltar encabezado

    int cargados = 0, errores = 0, numLinea = 2;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) { numLinea++; continue; }
        try {
            Producto p;
            p.fromString(linea);
            if (existeId(p.getId())) {
                std::cerr << "  [ADVERTENCIA] ID " << p.getId()
                          << " duplicado en linea " << numLinea << ". Omitido.\n";
                errores++;
            } else {
                productos.push_back(p);
                cargados++;
            }
        } catch (const std::exception& e) {
            std::cerr << "  [ADVERTENCIA] Linea " << numLinea << ": " << e.what() << "\n";
            errores++;
        }
        numLinea++;
    }
    std::cout << "  [OK] Cargados: " << cargados << " producto(s).";
    if (errores > 0) std::cout << " Errores: " << errores << ".";
    std::cout << "\n";
}

// ── Operaciones sobre inventario ─────────────────────────────

void GestorProductos::registrarStockInicial() {
    int id = leerEnteroValido("  ID del producto: ");
    if (!existeId(id)) {
        std::cout << "  [!] Producto ID " << id << " no existe en el catalogo.\n";
        return;
    }
    int cant = leerEnteroValido("  Cantidad inicial: ");
    inventario.registrarStock(id, cant);
    std::cout << "  [OK] Stock inicial de " << cant << " uds. registrado.\n";
}

void GestorProductos::aumentarStock() {
    int id   = leerEnteroValido("  ID del producto: ");
    int cant = leerEnteroValido("  Cantidad a aumentar: ");
    inventario.aumentarStock(id, cant);
    std::cout << "  [OK] Nuevo stock: " << inventario.consultarStock(id) << " uds.\n";
}

void GestorProductos::disminuirStock() {
    int id   = leerEnteroValido("  ID del producto: ");
    int cant = leerEnteroValido("  Cantidad a disminuir: ");
    inventario.disminuirStock(id, cant);
    std::cout << "  [OK] Nuevo stock: " << inventario.consultarStock(id) << " uds.\n";
}

void GestorProductos::consultarStock() const {
    int id  = leerEnteroValido("  ID del producto: ");
    std::string nombre = getNombreProducto(id);
    int stock = inventario.consultarStock(id);
    std::cout << "  " << (nombre.empty() ? "(sin nombre)" : nombre)
              << " | Stock: " << stock << " uds.\n";
}

void GestorProductos::mostrarInventarioCompleto() const {
    inventario.mostrarInventario();
}

void GestorProductos::mostrarProductosAgotados() const {
    inventario.mostrarAgotados();
}

void GestorProductos::guardarInventario() const {
    inventario.guardarInventario(archivoInventario);
    std::cout << "  [OK] Inventario guardado.\n";
}

void GestorProductos::cargarInventario() {
    inventario.cargarInventario(archivoInventario);
    std::cout << "  [OK] Inventario cargado.\n";
}

// Integracion 

double GestorProductos::getPrecioProducto(int id) const {
    int i = buscarIndicePorId(id);
    return (i == -1) ? -1.0 : productos[i].getPrecio();
}

std::string GestorProductos::getNombreProducto(int id) const {
    int i = buscarIndicePorId(id);
    return (i == -1) ? "" : productos[i].getNombre();
}

int GestorProductos::getStockDisponible(int id) const {
    return inventario.existeEnInventario(id) ? inventario.consultarStock(id) : 0;
}

bool GestorProductos::productoEstaActivo(int id) const {
    int i = buscarIndicePorId(id);
    return (i != -1) && productos[i].isActivo();
}

bool GestorProductos::hayStockSuficiente(int id, int cantidad) const {
    return inventario.hayStockSuficiente(id, cantidad);
}

bool GestorProductos::reducirStockPorVenta(int id, int cantidad) {
    if (!inventario.hayStockSuficiente(id, cantidad)) return false;
    try { inventario.disminuirStock(id, cantidad); return true; }
    catch (...) { return false; }
}

int GestorProductos::getTotalProductos() const {
    return (int)productos.size();
}

const std::vector<Producto>& GestorProductos::getProductos() const {
    return productos;
}
