#include "GestorRestaurante.h"

#include <iostream>
#include <limits>
#include <stdexcept>

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
        cout << "\n===== GESTION DEL RESTAURANTE =====\n";
        cout << "1. Mostrar mesas\n";
        cout << "2. Abrir pedido en mesa\n";
        cout << "3. Agregar producto a pedido\n";
        cout << "4. Ver pedido activo de una mesa\n";
        cout << "5. Cerrar pedido y liberar mesa\n";
        cout << "6. Mostrar todos los pedidos\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                    cout << "Volviendo al menu anterior...\n";
                    break;

                default:
                    cout << "Opcion no valida.\n";
                    break;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }

    } while (opcion != 0);
}

void GestorRestaurante::mostrarMesas() const {
    cout << "\n===== MESAS =====\n";

    for (const Mesa& mesa : mesas) {
        mesa.mostrar();
    }
}

void GestorRestaurante::abrirPedido() {
    mostrarMesas();

    int idMesa = leerEnteroValido("\nIngrese el ID de la mesa: ");
    int indiceMesa = buscarMesaPorId(idMesa);

    if (indiceMesa == -1) {
        cout << "No existe una mesa con ese ID.\n";
        return;
    }

    if (mesas[indiceMesa].estaOcupada()) {
        cout << "La mesa ya tiene un pedido activo.\n";
        return;
    }

    Pedido nuevoPedido(siguienteIdPedido, idMesa);
    pedidos.push_back(nuevoPedido);

    mesas[indiceMesa].ocupar(siguienteIdPedido);

    cout << "Pedido #" << siguienteIdPedido
         << " abierto en la mesa " << idMesa << ".\n";

    siguienteIdPedido++;
}

void GestorRestaurante::agregarProductoAPedido() {
    int idMesa = leerEnteroValido("Ingrese el ID de la mesa: ");
    int indiceMesa = buscarMesaPorId(idMesa);

    if (indiceMesa == -1) {
        cout << "No existe una mesa con ese ID.\n";
        return;
    }

    if (!mesas[indiceMesa].estaOcupada()) {
        cout << "La mesa no tiene un pedido activo.\n";
        return;
    }

    int indicePedido = buscarPedidoActivoPorMesa(idMesa);

    if (indicePedido == -1) {
        cout << "No se encontro pedido activo para esta mesa.\n";
        return;
    }

    cout << "\nProductos disponibles:\n";
    gestorProductos.mostrarTodos();

    int idProducto = leerEnteroValido("\nIngrese el ID del producto: ");
    int cantidad = leerEnteroValido("Ingrese la cantidad: ");

    if (cantidad <= 0) {
        cout << "La cantidad debe ser positiva.\n";
        return;
    }

    if (!gestorProductos.productoEstaActivo(idProducto)) {
        cout << "El producto no existe o no esta activo.\n";
        return;
    }

    if (!gestorProductos.hayStockSuficiente(idProducto, cantidad)) {
        cout << "No hay stock suficiente para ese producto.\n";
        cout << "Stock disponible: "
             << gestorProductos.getStockDisponible(idProducto)
             << "\n";
        return;
    }

    string nombre = gestorProductos.getNombreProducto(idProducto);
    double precio = gestorProductos.getPrecioProducto(idProducto);

    if (nombre.empty() || precio < 0) {
        cout << "No se pudo obtener la informacion del producto.\n";
        return;
    }

    bool stockReducido = gestorProductos.reducirStockPorVenta(idProducto, cantidad);

    if (!stockReducido) {
        cout << "No fue posible descontar el stock.\n";
        return;
    }

    pedidos[indicePedido].agregarItem(idProducto, nombre, cantidad, precio);
    gestorProductos.guardarInventario();

    cout << "Producto agregado al pedido correctamente.\n";
}

void GestorRestaurante::verPedidoActivo() const {
    int idMesa = leerEnteroValido("Ingrese el ID de la mesa: ");
    int indicePedido = buscarPedidoActivoPorMesa(idMesa);

    if (indicePedido == -1) {
        cout << "No hay pedido activo para esa mesa.\n";
        return;
    }

    pedidos[indicePedido].mostrar();
}

void GestorRestaurante::cerrarPedido() {
    int idMesa = leerEnteroValido("Ingrese el ID de la mesa: ");

    int indiceMesa = buscarMesaPorId(idMesa);

    if (indiceMesa == -1) {
        cout << "No existe una mesa con ese ID.\n";
        return;
    }

    if (!mesas[indiceMesa].estaOcupada()) {
        cout << "La mesa ya esta libre.\n";
        return;
    }

    int indicePedido = buscarPedidoActivoPorMesa(idMesa);

    if (indicePedido == -1) {
        cout << "No se encontro pedido activo para esta mesa.\n";
        return;
    }

    pedidos[indicePedido].mostrar();

    double total = pedidos[indicePedido].calcularTotal();

    pedidos[indicePedido].cerrarPedido();
    mesas[indiceMesa].liberar();

    cout << "\nPedido cerrado correctamente.\n";
    cout << "Total pagado: $" << total << "\n";
    cout << "Mesa " << idMesa << " liberada.\n";
}

void GestorRestaurante::mostrarPedidos() const {
    cout << "\n===== HISTORIAL DE PEDIDOS =====\n";

    if (pedidos.empty()) {
        cout << "No hay pedidos registrados.\n";
        return;
    }

    for (const Pedido& pedido : pedidos) {
        pedido.mostrar();
    }
}