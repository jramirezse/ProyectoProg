#pragma once

#include <string>

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

double calcularIVA(double subtotal);
double calcularDescuento(double subtotal, int porcentajeDescuento);
double calcularPropina(double subtotal, int porcentajePropina);
double calcularTotal(double subtotal, double iva, double descuento, double propina);

int generarIdVenta();

bool registrarVenta(
    int idPedido,
    int idCliente,
    double subtotal,
    int porcentajeDescuento,
    int porcentajePropina
);

void mostrarFactura(Venta venta);
void mostrarVentas();
bool cargarVentas(std :: string nombreArchivo);
bool guardarVentas(std :: string nombreArchivo);