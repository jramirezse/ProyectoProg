#include "GestorProductos.h"
#include "GestorRestaurante.h"

#include <iostream>
#include <limits>

using namespace std;

int main() {
    GestorProductos gestorProductos;
    GestorRestaurante gestorRestaurante(gestorProductos);

    int opcion;

    do {
        cout << "\n===== FOODSYSTEM =====\n";
        cout << "1. Gestionar productos e inventario\n";
        cout << "2. Gestionar mesas y pedidos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                gestorProductos.menuPrincipal();
                break;

            case 2:
                gestorRestaurante.menuRestaurante();
                break;

            case 0:
                cout << "Saliendo de FoodSystem...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
                break;
        }

    } while (opcion != 0);

    return 0;
}