#include "Pedido.h"

#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace std;

ItemPedido::ItemPedido()
    : idProducto(0),
      nombreProducto(""),
      cantidad(0),
      precioUnitario(0.0) {
}
ItemPedido::ItemPedido(
  int idProd,
  const string& nombre,
  int cant,
  double precio
):
  idProducto(idProd),
  nombreProducto(nombre),
  cantidad(cant),
  precioUnitario(precio) {
    if (idProd <= 0) {
        throw invalid_argument("El ID del producto debe ser positivo.");
    }
    if (nombre.empty()) {
        throw invalid_argument("El nombre del producto no puede estar vacío.");
    }
    if (cant <= 0) {
        throw invalid_argument("La cantidad debe ser positiva.");
    }
    if (precio < 0.0) {
        throw invalid_argument("El precio unitario no puede ser negativo.");
    }
}

double ItemPedido::subtotal() const {
    return cantidad * precioUnitario;
}
Pedido::Pedido()
    : idPedido(0),
      idMesa(0),
      activo(false) {
}

Pedido::Pedido(int id, int idMesa)
    : idPedido(id),
      idMesa(idMesa),
      activo(true) {
    if (id <= 0) {
        throw invalid_argument("El ID del pedido debe ser positivo.");
    }
    if (idMesa <= 0) {
        throw invalid_argument("El ID de la mesa debe ser positivo.");
    }
}
int Pedido::getIdPedido() const {
    return idPedido;
}
int Pedido::getIdMesa() const {
    return idMesa;
}
bool Pedido::estaActivo() const {
    return activo;
}
void Pedido::agregarItem(int idProducto, const string& nombreProducto, int cantidad, double precioUnitario) {
    if (!activo) {
        throw logic_error("No se pueden agregar items a un pedido cerrado.");
    }
    items.push_back(ItemPedido(idProducto, nombreProducto, cantidad, precioUnitario));
}
double Pedido::calcularTotalRecursivo(int indice) const {
  if (indice >= static_cast<int>(items.size())) {
    return 0.0;
  }
  return items[indice].subtotal() + calcularTotalRecursivo(indice + 1);
}
double Pedido::calcularTotal() const {
    return calcularTotalRecursivo(0);
}
void Pedido::cerrarPedido() {
    activo = false;
}
void Pedido::mostrar() const {
    cout << "\n===== PEDIDO #" << idPedido << " =====\n";
    cout << "Mesa: " << idMesa << "\n";
    cout << "Estado: " << (activo ? "ACTIVO" : "CERRADO") << "\n";

    if (items.empty()) {
        cout << "El pedido no tiene productos.\n";
        return;
    }
    for (const ItemPedido& item : items) {
    cout << left 
         << setw(8) << item.idProducto
         << setw(25) << item.nombreProducto
         << setw(10) << item.cantidad
         << setw(12) << fixed << setprecision(2) << item.precioUnitario
         << setw(12) << fixed << setprecision(2) << item.subtotal() 
         << "\n";
    }
    cout << string(67, '-') << "\n";
    cout << "TOTAL: $" << fixed << setprecision(2) << calcularTotal() << "\n";
}
const vector<ItemPedido>& Pedido::getItems() const {
    return items;
}