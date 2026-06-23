#include "../include/facturacion.h"

int main() {

    cargarVentas("data/ventas.csv");

    registrarVenta(1, 205, 80000, 10, 5);
    registrarVenta(2, 0, 45000, 0, 0);

    mostrarVentas();

    guardarVentas("data/ventas.csv");

    return 0;
}
