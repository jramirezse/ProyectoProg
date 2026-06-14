#pragma once

struct Venta {
    int idVenta;
    int idPedido;
    int idCliente;
    double subtotal;
    double iva;
    double descuento;
    double propina;
    double total;
};