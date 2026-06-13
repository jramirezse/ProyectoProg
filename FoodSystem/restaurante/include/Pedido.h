#ifndef PEDIDO_H
#define PEDIDO_H

#include <vector>
#include <string>

struct ItemPedido{
    int idProducto;
    std::string nombreProducto;
    int cantidad;
    double precioUnitario;

    ItemPedido();
    ItemPedido(
         int id,
         const std::string& nombre,
         int cant,
         double precio
    );
    double subtotal() const;

};

class Pedido{
private:
    int idPedido;
    int idMesa;
    std::vector<ItemPedido> items;
    bool activo;

    double calcularTotalRecursivo(int indice) const;
public:
    Pedido();
    Pedido(int id, int idMesa);

    int getIdPedido() const;
    int getIdMesa() const;
    bool estaActivo() const;

    void agregarItem(int idProducto, const std::string& nombreProducto, int cantidad, double precioUnitario);
    double calcularTotal() const;
    void cerrarPedido();
    void mostrar() const;

    const std::vector<ItemPedido>& getItems() const;
};

#endif
