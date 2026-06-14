#include "GestorProductos.h"
#include "GestorRestaurante.h"
#include "clientes.h"
#include <ctime>
#include <iostream>
#include <limits>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int leerOpcionPrincipal(const string& mensaje) {
    int valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "  [!] Entrada invalida. Intente nuevamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void limpiarPantallaPrincipal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {

    srand(time(NULL));
    cargarClientes("data/clientes.csv");
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    GestorProductos gestorProductos;
    GestorRestaurante gestorRestaurante(gestorProductos);
    int opcion;

    do {
        limpiarPantallaPrincipal();

        cout << "\n"
             << "  ╔══════════════════════════════════════╗\n"
             << "  ║             FOODSYSTEM               ║\n"
             << "  ║      SISTEMA DE RESTAURANTE          ║\n"
             << "  ╠══════════════════════════════════════╣\n"
             << "  ║  1. Productos e inventario           ║\n"
             << "  ║  2. Mesas y pedidos                  ║\n"
             << "  ║  0. Salir                            ║\n"
             << "  ╚══════════════════════════════════════╝\n";

        opcion = leerOpcionPrincipal("  Seleccione: ");

        switch (opcion) {
            case 1:
                gestorProductos.menuPrincipal();
                break;

            case 2:
                gestorRestaurante.menuRestaurante();
                break;

            case 0:
                cout << "  Hasta luego.\n\n";
                break;

            default:
                cout << "  [!] Opcion no valida.\n";
                cout << "\n  Presione ENTER para continuar...";
                cin.get();
                break;
        }

    } while (opcion != 0);

    return 0;
}