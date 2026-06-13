#include "GestorRestaurante.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include <iomanip>

using namespace std;

GestorRestaurante::GestorRestaurante(GestorProductos& gestor)
    : gestorProductos(gestor),
      siguienteIdPedido(1) {
      inicializarMesas(); 
}

void GestorRestaurante::inicializarMesas() {
    mesas.push_back(Mesa(1,2));
    mesas.push_back(Mesa(2,2));
    mesas.push_back(Mesa(3,4));
    mesas.push_back(Mesa(4,4));
    mesas.push_back(Mesa(5,4));
    mesas.push_back(Mesa(6,6));
    mesas.push_back(Mesa(7,6));
    mesas.push_back(Mesa(8,8));
}

int GestorRestaurante::buscarMesaPorId(int idMesa) const {
    for (int i = 0; i < static_cast<int>(mesas.size()); i++) {
        if (mesas[i].getIdMesa() == idMesa) {
            return i;
        }
    }

    return -1;
}

int GestorRestaurante::buscarPedidoActivoPorMesa(int idMesa) const {
    for (int i = 0; i < static_cast<int>(pedidos.size()); i++) {
        if (pedidos[i].getIdMesa() == idMesa && pedidos[i].estaActivo()) {
            return i;
        }
    }

    return -1;
}

int GestorRestaurante::leerEnteroValido(const string& mensaje) const {
    int valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Entrada invalida. Intente nuevamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void GestorRestaurante::menuRestaurante() {
    int opcion;

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "\n"
             << "  ┌─────────────────────────────────────┐\n"
             << "  │        GESTIÓN DE RESTAURANTE       │\n"
             << "  ├─────────────────────────────────────┤\n"
             << "  │  1. Mostrar mesas                   │\n"
             << "  │  2. Abrir pedido en mesa            │\n"
             << "  │  3. Agregar producto a pedido       │\n"
             << "  │  4. Ver pedido activo               │\n"
             << "  │  5. Cerrar pedido y liberar mesa    │\n"
             << "  │  6. Mostrar historial de pedidos    │\n"
             << "  │  0. Volver                          │\n"
             << "  └─────────────────────────────────────┘\n";

        opcion = leerEnteroValido("  Seleccione: ");

        try {
            switch (opcion) {
                case 1:
                    mostrarMesas();
                    break;

                case 2:
                    abrirPedido();
                    break;

                case 3:
                    agregarProductoAPedido();
                    break;

                case 4:
                    verPedidoActivo();
                    break;

                case 5:
                    cerrarPedido();
                    break;

                case 6:
                    mostrarPedidos();
                    break;

                case 0:
                    break;

                default:
                    cout << "  [!] Opcion no valida.\n";
                    break;
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

void GestorRestaurante::mostrarMesas() const {
    cout << "\n" << string(70, '=') << "\n"
         << "  ESTADO DE MESAS\n"
         << string(70, '-') << "\n"
         << left << setw(10) << "ID"
         << setw(15) << "CAPACIDAD"
         << setw(15) << "ESTADO"
         << setw(20) << "PEDIDO ACTIVO"
         << "\n"
         << string(70, '-') << "\n";

    for (const Mesa& mesa : mesas) {
        cout << left
             << setw(10) << mesa.getIdMesa()
             << setw(15) << mesa.getCapacidad()
             << setw(15) << (mesa.estaOcupada() ? "OCUPADA" : "LIBRE");

        if (mesa.estaOcupada()) {
            cout << setw(20) << mesa.getIdPedidoActivo();
        } else {
            cout << setw(20) << "-";
        }

        cout << "\n";
    }

    cout << string(70, '=') << "\n";
}

void GestorRestaurante::abrirPedido() {
    cout << "\n  --- ABRIR PEDIDO EN MESA ---\n";

    mostrarMesas();

    int idMesa = leerEnteroValido("\n  ID de la mesa: ");
    int indiceMesa = buscarMesaPorId(idMesa);

    if (indiceMesa == -1) {
        cout << "  [!] No existe una mesa con ese ID.\n";
        return;
    }

    if (mesas[indiceMesa].estaOcupada()) {
        cout << "  [!] La mesa ya tiene un pedido activo.\n";
        return;
    }

    Pedido nuevoPedido(siguienteIdPedido, idMesa);
    pedidos.push_back(nuevoPedido);

    mesas[indiceMesa].ocupar(siguienteIdPedido);

    cout << "  [OK] Pedido #" << siguienteIdPedido
         << " abierto en la mesa " << idMesa << ".\n";

    siguienteIdPedido++;
}

void GestorRestaurante::agregarProductoAPedido() {
    cout << "\n  --- AGREGAR PRODUCTO A PEDIDO ---\n";

    int idMesa = leerEnteroValido("  ID de la mesa: ");
    int indiceMesa = buscarMesaPorId(idMesa);

    if (indiceMesa == -1) {
        cout << "  [!] No existe una mesa con ese ID.\n";
        return;
    }

    if (!mesas[indiceMesa].estaOcupada()) {
        cout << "  [!] La mesa no tiene un pedido activo.\n";
        return;
    }

    int indicePedido = buscarPedidoActivoPorMesa(idMesa);

    if (indicePedido == -1) {
        cout << "  [!] No se encontro pedido activo para esta mesa.\n";
        return;
    }

    cout << "\n  Productos disponibles:\n";
    gestorProductos.mostrarTodos();

    int idProducto = leerEnteroValido("\n  ID del producto: ");
    int cantidad = leerEnteroValido("  Cantidad: ");

    if (cantidad <= 0) {
        cout << "  [!] La cantidad debe ser positiva.\n";
        return;
    }

    if (!gestorProductos.productoEstaActivo(idProducto)) {
        cout << "  [!] El producto no existe o no esta activo.\n";
        return;
    }

    if (!gestorProductos.hayStockSuficiente(idProducto, cantidad)) {
        cout << "  [!] No hay stock suficiente para ese producto.\n";
        cout << "  Stock disponible: "
             << gestorProductos.getStockDisponible(idProducto)
             << "\n";
        return;
    }

    string nombre = gestorProductos.getNombreProducto(idProducto);
    double precio = gestorProductos.getPrecioProducto(idProducto);

    if (nombre.empty() || precio < 0) {
        cout << "  [!] No se pudo obtener la informacion del producto.\n";
        return;
    }

    bool stockReducido = gestorProductos.reducirStockPorVenta(idProducto, cantidad);

    if (!stockReducido) {
        cout << "  [!] No fue posible descontar el stock.\n";
        return;
    }

    pedidos[indicePedido].agregarItem(idProducto, nombre, cantidad, precio);
    gestorProductos.guardarInventario();

    cout << "  [OK] Producto agregado al pedido correctamente.\n";
}

void GestorRestaurante::verPedidoActivo() const {
    cout << "\n  --- CONSULTAR PEDIDO ACTIVO ---\n";

    int idMesa = leerEnteroValido("  ID de la mesa: ");
    int indicePedido = buscarPedidoActivoPorMesa(idMesa);

    if (indicePedido == -1) {
        cout << "  [!] No hay pedido activo para esa mesa.\n";
        return;
    }

    pedidos[indicePedido].mostrar();
}

void GestorRestaurante::cerrarPedido() {
    cout << "\n  --- CERRAR PEDIDO ---\n";

    int idMesa = leerEnteroValido("  ID de la mesa: ");
    int indiceMesa = buscarMesaPorId(idMesa);

    if (indiceMesa == -1) {
        cout << "  [!] No existe una mesa con ese ID.\n";
        return;
    }

    if (!mesas[indiceMesa].estaOcupada()) {
        cout << "  [!] La mesa ya esta libre.\n";
        return;
    }

    int indicePedido = buscarPedidoActivoPorMesa(idMesa);

    if (indicePedido == -1) {
        cout << "  [!] No se encontro pedido activo para esta mesa.\n";
        return;
    }

    pedidos[indicePedido].mostrar();

    double total = pedidos[indicePedido].calcularTotal();

    pedidos[indicePedido].cerrarPedido();
    mesas[indiceMesa].liberar();

    cout << "\n  [OK] Pedido cerrado correctamente.\n";
    cout << "  Total pagado: $" << fixed << setprecision(2) << total << "\n";
    cout << "  [OK] Mesa " << idMesa << " liberada.\n";
}

void GestorRestaurante::mostrarPedidos() const {
    cout << "\n" << string(70, '=') << "\n"
         << "  HISTORIAL DE PEDIDOS\n"
         << string(70, '-') << "\n";

    if (pedidos.empty()) {
        cout << "  [!] No hay pedidos registrados.\n";
        cout << string(70, '=') << "\n";
        return;
    }

    for (const Pedido& pedido : pedidos) {
        pedido.mostrar();
    }

    cout << string(70, '=') << "\n";
}