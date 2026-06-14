#include "../include/facturacion.h"
#include <iostream>

using namespace std;

int main() {

    cargarVentas("data/ventas.csv");

    registrarVenta(1, 205, 80000, 10, 5);
    registrarVenta(2, 0, 45000, 0, 0);
    registrarVenta(3, 314, 120000, 15, 10);

    mostrarVentas();

    guardarVentas("data/ventas.csv");

    return 0;
}