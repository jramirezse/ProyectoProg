// GestorProductos.cpp - Implementación del gestor principal

#include "../include/GestorProductos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <algorithm>
#ifdef _WIN32
#include <windows.h> 
#endif
using namespace std;
GestorProductos::GestorProductos(const string& archProd,
                                  const string& archInv)
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
int GestorProductos::leerEnteroValido(const string& msg) const {
    int valor;
    while (true) {
        cout << msg;
        cin >> valor;
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Ingrese un numero entero valido.\n";
    }
}

double GestorProductos::leerDoubleValido(const string& msg) const {
    double valor;
    while (true) {
        cout << msg;
        cin >> valor;
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Ingrese un numero valido (ej: 15000.50).\n";
    }
}

string GestorProductos::leerLineaNoVacia(const string& msg) const {
    string entrada;
    while (true) {
        cout << msg;
        getline(cin, entrada);
        if (!entrada.empty()) return entrada;
        cout << "  [!] El campo no puede estar vacio.\n";
    }
}

// ── Menús ────────────────────────────────────────────────────

void GestorProductos::menuPrincipal() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif
    int opcion;
    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n"
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
                        cout << "  [OK] Datos guardados.\n";
                    } catch (const exception& e) {
                        cout << "  [!] Error al guardar: " << e.what() << "\n";
                    }
                }
                cout << "  Hasta luego.\n\n";
                break;
            default:
                cout << "  [!] Opcion no valida.\n";
        }
    } while (opcion != 0);
}

void GestorProductos::menuProductos() {
    int opcion;
    do {
        cout << "\n"
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
                
                case 0: break;
                default: cout << "  [!] Opcion no valida.\n";
            }
        } catch (const exception& e) {
            cout << "  [ERROR] " << e.what() << "\n";
        }
        if (opcion != 0) {
            cout << "\n  Presione ENTER para continuar...";
            cin.get();
        }
    } while (opcion != 0);
}

void GestorProductos::menuInventario() {
    int opcion;
    do {
        cout << "\n"
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
                default: cout << "  [!] Opcion no valida.\n";
            }
        } catch (const exception& e) {
            cout << "  [ERROR] " << e.what() << "\n";
        }
        if (opcion != 0) {
            cout << "\n  Presione ENTER para continuar...";
            cin.get();
        }
    } while (opcion != 0);
}

//  Operaciones sobre productos 

void GestorProductos::agregarProducto() {
    cout << "\n  --- AGREGAR NUEVO PRODUCTO ---\n";

    int id;
    while (true) {
        id = leerEnteroValido("  ID del producto: ");
        if (!existeId(id)) break;
        cout << "  [!] ID " << id << " ya existe. Use otro.\n";
    }

    string nombre    = leerLineaNoVacia("  Nombre: ");
    string categoria = leerLineaNoVacia("  Categoria: ");

    double precio;
    while (true) {
        precio = leerDoubleValido("  Precio: ");
        if (precio >= 0) break;
        cout << "  [!] El precio no puede ser negativo.\n";
    }

    try {
        productos.push_back(Producto(id, nombre, categoria, precio));
        cout << "  [OK] Producto '" << nombre << "' agregado.\n";
    } catch (const invalid_argument& e) {
        cout << "  [ERROR] " << e.what() << "\n";
    }
}

void GestorProductos::mostrarTodos() const {
    if (productos.empty()) { cout << "\n  [!] No hay productos.\n"; return; }

    cout << "\n" << string(75, '=') << "\n"
              << "  CATÁLOGO COMPLETO DE PRODUCTOS\n"
              << string(75, '-') << "\n"
              << left  << setw(6)  << "ID"
                            << setw(25) << "NOMBRE"
                            << setw(15) << "CATEGORIA"
              << right << setw(12) << "PRECIO"
                            << setw(10) << "ESTADO" << "\n"
              << string(75, '-') << "\n";

    for (const Producto& p : productos) p.mostrar();

    cout << string(75, '=') << "\n"
              << "  Total: " << productos.size() << " producto(s)\n";
}

void GestorProductos::buscarPorId() const {
    int id = leerEnteroValido("  ID a buscar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1) {
        cout << "  [!] No existe producto con ID " << id << ".\n";
    } else {
        cout << "\n" << string(75, '-') << "\n";
        cout << left  << setw(6)  << "ID"
                                << setw(25) << "NOMBRE"
                                << setw(15) << "CATEGORIA"
                  << right << setw(12) << "PRECIO"
                                << setw(10) << "ESTADO" << "\n"
                  << string(75, '-') << "\n";
        productos[i].mostrar();
    }
}

void GestorProductos::buscarPorNombre() const {
    string busq = leerLineaNoVacia("  Nombre a buscar (parcial): ");
    string busqMin = busq;
    transform(busqMin.begin(), busqMin.end(), busqMin.begin(), ::tolower);

    bool encontrado = false;
    cout << "\n" << string(75, '-') << "\n";
    for (const Producto& p : productos) {
        string nomMin = p.getNombre();
        transform(nomMin.begin(), nomMin.end(), nomMin.begin(), ::tolower);
        if (nomMin.find(busqMin) != string::npos) {
            p.mostrar();
            encontrado = true;
        }
    }
    if (!encontrado) cout << "  [!] Sin resultados.\n";
}

void GestorProductos::modificarProducto() {
    int id = leerEnteroValido("  ID a modificar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1) { cout << "  [!] ID no encontrado.\n"; return; }

    cout << "\n  Datos actuales:\n";
    productos[i].mostrar();
    cout << "\n  (ENTER = mantener valor actual)\n";

    // Nombre
    cout << "  Nuevo nombre [" << productos[i].getNombre() << "]: ";
    string val; getline(cin, val);
    if (!val.empty()) {
        try { productos[i].setNombre(val); }
        catch (const exception& e) { cout << "  [!] " << e.what() << "\n"; }
    }

    // Categoria
    cout << "  Nueva categoria [" << productos[i].getCategoria() << "]: ";
    getline(cin, val);
    if (!val.empty()) {
        try { productos[i].setCategoria(val); }
        catch (const exception& e) { cout << "  [!] " << e.what() << "\n"; }
    }

    // Precio
    cout << "  Nuevo precio [" << productos[i].getPrecio() << "]: ";
    getline(cin, val);
    if (!val.empty()) {
        try { productos[i].setPrecio(stod(val)); }
        catch (...) { cout << "  [!] Precio invalido. Sin cambios.\n"; }
    }

    cout << "  [OK] Producto modificado.\n";
}

void GestorProductos::desactivarProducto() {
    int id = leerEnteroValido("  ID a desactivar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1)                     { cout << "  [!] ID no encontrado.\n"; return; }
    if (!productos[i].isActivo())    { cout << "  [!] Ya esta inactivo.\n"; return; }
    productos[i].setActivo(false);
    cout << "  [OK] '" << productos[i].getNombre() << "' desactivado.\n";
}

void GestorProductos::activarProducto() {
    int id = leerEnteroValido("  ID a activar: ");
    int i  = buscarIndicePorId(id);
    if (i == -1)                  { cout << "  [!] ID no encontrado.\n"; return; }
    if (productos[i].isActivo())  { cout << "  [!] Ya esta activo.\n";   return; }
    productos[i].setActivo(true);
    cout << "  [OK] '" << productos[i].getNombre() << "' activado.\n";
}

void GestorProductos::guardarProductos() const {
    if (productos.empty()) { cout << "  [!] No hay productos para guardar.\n"; return; }
    ofstream archivo(archivoProductos);
    if (!archivo.is_open())
        throw runtime_error("No se pudo abrir: " + archivoProductos +
                                 "\nVerifique que la carpeta 'data' existe.");
    archivo << "id,nombre,categoria,precio,estado\n";
    for (const Producto& p : productos) archivo << p.toString() << "\n";
    archivo.close();
    cout << "  [OK] " << productos.size() << " producto(s) guardado(s).\n";
}

void GestorProductos::cargarProductos() {
    ifstream archivo(archivoProductos);
    if (!archivo.is_open())
        throw runtime_error("No se pudo abrir: " + archivoProductos);

    productos.clear();
    string linea;
    getline(archivo, linea); // saltar encabezado

    int cargados = 0, errores = 0, numLinea = 2;
    while (getline(archivo, linea)) {
        if (linea.empty()) { numLinea++; continue; }
        try {
            Producto p;
            p.fromString(linea);
            if (existeId(p.getId())) {
                cerr << "  [ADVERTENCIA] ID " << p.getId()
                          << " duplicado en linea " << numLinea << ". Omitido.\n";
                errores++;
            } else {
                productos.push_back(p);
                cargados++;
            }
        } catch (const exception& e) {
            cerr << "  [ADVERTENCIA] Linea " << numLinea << ": " << e.what() << "\n";
            errores++;
        }
        numLinea++;
    }
    cout << "  [OK] Cargados: " << cargados << " producto(s).";
    if (errores > 0) cout << " Errores: " << errores << ".";
    cout << "\n";
}

// ── Operaciones sobre inventario ─────────────────────────────

void GestorProductos::registrarStockInicial() {
    int id = leerEnteroValido("  ID del producto: ");
    if (!existeId(id)) {
        cout << "  [!] Producto ID " << id << " no existe en el catalogo.\n";
        return;
    }
    int cant = leerEnteroValido("  Cantidad inicial: ");
    inventario.registrarStock(id, cant);
    cout << "  [OK] Stock inicial de " << cant << " uds. registrado.\n";
}

void GestorProductos::aumentarStock() {
    int id   = leerEnteroValido("  ID del producto: ");
    int cant = leerEnteroValido("  Cantidad a aumentar: ");
    inventario.aumentarStock(id, cant);
    cout << "  [OK] Nuevo stock: " << inventario.consultarStock(id) << " uds.\n";
}

void GestorProductos::disminuirStock() {
    int id   = leerEnteroValido("  ID del producto: ");
    int cant = leerEnteroValido("  Cantidad a disminuir: ");
    inventario.disminuirStock(id, cant);
    cout << "  [OK] Nuevo stock: " << inventario.consultarStock(id) << " uds.\n";
}

void GestorProductos::consultarStock() const {
    int id  = leerEnteroValido("  ID del producto: ");
    string nombre = getNombreProducto(id);
    int stock = inventario.consultarStock(id);
    cout << "  " << (nombre.empty() ? "(sin nombre)" : nombre)
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
    cout << "  [OK] Inventario guardado.\n";
}

void GestorProductos::cargarInventario() {
    inventario.cargarInventario(archivoInventario);
    cout << "  [OK] Inventario cargado.\n";
}

// Integracion 

double GestorProductos::getPrecioProducto(int id) const {
    int i = buscarIndicePorId(id);
    return (i == -1) ? -1.0 : productos[i].getPrecio();
}

string GestorProductos::getNombreProducto(int id) const {
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

const vector<Producto>& GestorProductos::getProductos() const {
    return productos;
}
void GestorProductos::mostrarMenuCliente() const {

    if (productos.empty()) {
        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║          NO HAY PRODUCTOS DISPONIBLES     ║\n"
             << "╚════════════════════════════════════════════╝\n";
        return;
    }

    bool hayProductosDisponibles = false;

    cout << "\n"
         << "╔════════════════════════════════════════════════════════════════════╗\n"
         << "║                         MENU DEL RESTAURANTE                     ║\n"
         << "╠════════════════════════════════════════════════════════════════════╣\n";

    cout << left
         << setw(8)  << "  ID"
         << setw(28) << "NOMBRE"
         << setw(18) << "CATEGORIA"
         << right
         << setw(12) << "PRECIO"
         << endl;

    cout << "╠════════════════════════════════════════════════════════════════════╣\n";

    for (int i = 0; i < productos.size(); i++) {

        int idProducto = productos[i].getId();

        if (productos[i].isActivo() == true &&
            inventario.hayStockSuficiente(idProducto, 1) == true) {

            cout << left
                 << "  "
                 << setw(6)  << productos[i].getId()
                 << setw(28) << productos[i].getNombre()
                 << setw(18) << productos[i].getCategoria()
                 << right
                 << fixed << setprecision(2)
                 << setw(12) << productos[i].getPrecio()
                 << endl;

            hayProductosDisponibles = true;
        }
    }

    if (hayProductosDisponibles == false) {
        cout << "  No hay productos activos con stock disponible." << endl;
    }

    cout << "╚════════════════════════════════════════════════════════════════════╝\n";
}
