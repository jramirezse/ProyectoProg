#ifndef GESTOR_RESTAURANTE_H
#define GESTOR_RESTAURANTE_H

#include "Mesa.h"
#include "Pedido.h"
#include "GestorProductos.h"

#include <vector>
#include <string>

class GestorRestaurante {
private:
    GestorProductos& gestorProductos;
    std::vector<Mesa> mesas;
    std::vector<Pedido> pedidos;
    int siguienteIdPedido;

    void inicializarMesas();

    int buscarMesaPorId(int idMesa) const;
    int buscarPedidoActivoPorMesa(int idMesa) const;
    int leerEnteroValido(const std::string& mensaje) const;

public:
    GestorRestaurante(GestorProductos& gestor);

    void menuRestaurante();

    void mostrarMesas() const;
    void abrirPedido();
    void agregarProductoAPedido();
    void verPedidoActivo() const;
    void cerrarPedido();
    void mostrarPedidos() const;
};

#endif