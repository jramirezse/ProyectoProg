#include "../include/GestorProductos.h"
#include "../include/GestorRestaurante.h"
#include "../include/clientes.h"
#include "../include/roles.h"
#include "../include/facturacion.h"
#include "../include/estadisticas.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int leerOpcionPrincipal(string mensaje) {
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

void pausar() {
    cout << "\n  Presione ENTER para continuar...";
    cin.get();
}

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void cargarDatosSistema(GestorProductos& gestorProductos) {

    cout << "\n"
         << "╔════════════════════════════════════════════╗\n"
         << "║          CARGANDO DATOS DEL SISTEMA        ║\n"
         << "╚════════════════════════════════════════════╝\n";

    try {
        gestorProductos.cargarProductos();
    } catch (...) {
        cout << "  [!] No se pudieron cargar los productos.\n";
    }

    try {
        gestorProductos.cargarInventario();
    } catch (...) {
        cout << "  [!] No se pudo cargar el inventario.\n";
    }

    if (cargarClientes("data/clientes.csv")) {
        cout << "  [OK] Clientes cargados.\n";
    } else {
        cout << "  [!] No se pudieron cargar los clientes.\n";
    }

    if (cargarUsuarios("data/usuarios.csv")) {
        cout << "  [OK] Usuarios cargados.\n";
    } else {
        cout << "  [!] No se pudieron cargar los usuarios.\n";
    }

    if (cargarVentas("data/ventas.csv")) {
        cout << "  [OK] Ventas cargadas.\n";
    } else {
        cout << "  [!] No se pudieron cargar las ventas.\n";
    }

    cout << "\n  Carga inicial finalizada.\n";
    pausar();
}
void guardarDatosSistema(GestorProductos& gestorProductos) {

    cout << "\n"
         << "╔════════════════════════════════════════════╗\n"
         << "║          GUARDANDO DATOS DEL SISTEMA       ║\n"
         << "╚════════════════════════════════════════════╝\n";

    try {
        gestorProductos.guardarProductos();
    } catch (...) {
        cout << "  [!] No se pudieron guardar los productos.\n";
    }

    try {
        gestorProductos.guardarInventario();
    } catch (...) {
        cout << "  [!] No se pudo guardar el inventario.\n";
    }

    if (guardarClientes("data/clientes.csv")) {
        cout << "  [OK] Clientes guardados.\n";
    } else {
        cout << "  [!] No se pudieron guardar los clientes.\n";
    }

    if (guardarUsuarios("data/usuarios.csv")) {
        cout << "  [OK] Usuarios guardados.\n";
    } else {
        cout << "  [!] No se pudieron guardar los usuarios.\n";
    }

    if (guardarVentas("data/ventas.csv")) {
        cout << "  [OK] Ventas guardadas.\n";
    } else {
        cout << "  [!] No se pudieron guardar las ventas.\n";
    }
}
string loginUsuarioRestaurante() {

    string nombre;
    string clave;

    cout << "\n"
         << "╔════════════════════════════════════════════╗\n"
         << "║          LOGIN USUARIO RESTAURANTE         ║\n"
         << "╚════════════════════════════════════════════╝\n";

    cout << "  Usuario: ";
    getline(cin, nombre);

    cout << "  Clave: ";
    getline(cin, clave);

    if (claveCorrecta(nombre, clave) == false) {
        cout << "\n  [!] Usuario o clave incorrectos.\n";
        return "";
    }

    if (usuarioActivo(nombre) == false) {
        cout << "\n  [!] El usuario esta inactivo.\n";
        return "";
    }

    string rol = obtenerRolUsuario(nombre);

    cout << "\n  [OK] Bienvenido, " << nombre << ". Rol: " << rol << endl;

    return rol;
}
void menuUsuarioRestaurante(
    string rol,
    GestorProductos& gestorProductos,
    GestorRestaurante& gestorRestaurante
) {
    int opcion;

    do {
        limpiarPantalla();

        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║        MENU USUARIO DEL RESTAURANTE        ║\n"
             << "╠════════════════════════════════════════════╣\n";

        if (rol == "ADMIN") {
            cout << "║  1. Productos e inventario                 ║\n";
            cout << "║  2. Mesas y pedidos                        ║\n";
            cout << "║  3. Gestion de clientes                    ║\n";
            cout << "║  4. Ver ventas                             ║\n";
            cout << "║  5. Estadisticas                           ║\n";
            cout << "║  6. Usuarios y roles                       ║\n";
            cout << "║  7. Guardar datos                          ║\n";
        }

        if (rol == "INVENTARIO") {
            cout << "║  1. Productos e inventario                 ║\n";
            cout << "║  7. Guardar datos                          ║\n";
        }

        if (rol == "MESERO") {
            cout << "║  2. Mesas y pedidos                        ║\n";
            cout << "║  7. Guardar datos                          ║\n";
        }

        if (rol == "CAJERO") {
            cout << "║  3. Gestion de clientes                    ║\n";
            cout << "║  4. Ver ventas                             ║\n";
            cout << "║  5. Estadisticas                           ║\n";
            cout << "║  7. Guardar datos                          ║\n";
        }

        cout << "║  0. Cerrar sesion                          ║\n"
             << "╚════════════════════════════════════════════╝\n";

        opcion = leerOpcionPrincipal("  Seleccione: ");

        switch (opcion) {

            case 1: {
                if (rol == "ADMIN" || rol == "INVENTARIO") {
                    gestorProductos.menuPrincipal();
                } else {
                    cout << "\n  [!] No tiene permiso para productos e inventario.\n";
                    pausar();
                }

                break;
            }

            case 2: {
                if (rol == "ADMIN" || rol == "MESERO") {
                    gestorRestaurante.menuRestaurante();
                } else {
                    cout << "\n  [!] No tiene permiso para mesas y pedidos.\n";
                    pausar();
                }

                break;
            }

            case 3: {
                if (rol == "ADMIN" || rol == "CAJERO") {
                    menuClientes();
                } else {
                    cout << "\n  [!] No tiene permiso para gestionar clientes.\n";
                    pausar();
                }

                break;
            }

            case 4: {
                if (rol == "ADMIN" || rol == "CAJERO") {
                    cargarVentas("data/ventas.csv");
                    mostrarVentas();
                    pausar();
                } else {
                    cout << "\n  [!] No tiene permiso para ver ventas.\n";
                    pausar();
                }

                break;
            }

            case 5: {
                if (rol == "ADMIN" || rol == "CAJERO") {
                    menuEstadisticas();
                } else {
                    cout << "\n  [!] No tiene permiso para ver estadisticas.\n";
                    pausar();
                }

                break;
            }

            case 6: {
                if (rol == "ADMIN") {
                    menuRoles();
                } else {
                    cout << "\n  [!] No tiene permiso para administrar usuarios y roles.\n";
                    pausar();
                }

                break;
            }

            case 7: {
                guardarDatosSistema(gestorProductos);
                pausar();
                break;
            }

            case 0: {
                cout << "\n  Cerrando sesion...\n";
                break;
            }

            default: {
                cout << "\n  [!] Opcion invalida.\n";
                pausar();
                break;
            }
        }

    } while (opcion != 0);
}

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string DIM     = "\033[2m";
    const string CYAN    = "\033[36m";
    const string YELLOW  = "\033[33m";
    const string GREEN   = "\033[32m";
    const string RED     = "\033[31m";

    srand(time(NULL));

    GestorProductos gestorProductos;
    GestorRestaurante gestorRestaurante(gestorProductos);

    cargarDatosSistema(gestorProductos);

    int opcion;

    do {
        limpiarPantalla();

        cout << "\n"
         << CYAN << " ╭────────────────────────────────────────────────────────────╮\n" << RESET
         << CYAN << " │" << RESET << BOLD << "                  🍔 FOODSYSTEM RESTAURANT                  " << RESET << CYAN << "│\n" << RESET
         << CYAN << " │" << DIM << "              Gestión inteligente para restaurantes         " << RESET << CYAN << "│\n" << RESET
         << CYAN << " ├────────────────────────────────────────────────────────────┤\n" << RESET
         << CYAN << " │                                                            │\n" << RESET
         << CYAN << " │" << RESET << "   Seleccione su perfil de acceso:                          " << CYAN << "│\n" << RESET
         << CYAN << " │                                                            │\n" << RESET
         << CYAN << " │   " << YELLOW << BOLD << "[ 1 ]" << RESET << BOLD << " Cliente                                            " << CYAN << "│\n" << RESET
         << CYAN << " │         " << DIM << "↳ Consultar menú de productos disponibles          " << RESET << CYAN << "│\n" << RESET
         << CYAN << " │                                                            │\n" << RESET
         << CYAN << " │   " << YELLOW << BOLD << "[ 2 ]" << RESET << BOLD << " Usuario del restaurante                            " << CYAN << "│\n" << RESET
         << CYAN << " │         " << DIM << "↳ Acceder con credenciales                         " << RESET << CYAN << "│\n" << RESET
         << CYAN << " │                                                            │\n" << RESET
         << CYAN << " │   " << RED << BOLD << "[ 0 ]" << RESET << " Salir del sistema                                  " << CYAN << "│\n" << RESET
         << CYAN << " │                                                            │\n" << RESET
         << CYAN << " ╰────────────────────────────────────────────────────────────╯\n" << RESET
         << "\n" 
         << GREEN << BOLD << " ❯ " << RESET << "Ingresa tu opción: ";

        opcion = leerOpcionPrincipal("  Seleccione: ");

        switch (opcion) {

            case 1: {
                     limpiarPantalla();
                      gestorProductos.mostrarMenuCliente();
                      pausar();
                    break;
                    }

            case 2: {
                string rol = loginUsuarioRestaurante();

                if (rol != "") {
                    pausar();
                    menuUsuarioRestaurante(rol, gestorProductos, gestorRestaurante);
                } else {
                    pausar();
                }

                break;
            }

            case 0:
                guardarDatosSistema(gestorProductos);
                cout << "\n"
                 << CYAN << " ╭────────────────────────────────────────────────────────────╮\n" << RESET
                 << CYAN << " │                                                            │\n" << RESET
                 << CYAN << " │" << RESET << BOLD << "        👋 ¡Gracias por usar FOODSYSTEM RESTAURANT!       " << RESET << CYAN << "│\n" << RESET
                 << CYAN << " │" << DIM << "             Cerrando el sistema de forma segura...         " << RESET << CYAN << "│\n" << RESET
                 << CYAN << " │                                                            │\n" << RESET
                 << CYAN << " │" << GREEN << BOLD << "               ¡Que tengas un excelente día! 🍽️              " << RESET << CYAN << "│\n" << RESET
                 << CYAN << " │                                                            │\n" << RESET
                 << CYAN << " ╰────────────────────────────────────────────────────────────╯\n" << RESET
                 << "\n";
                break;

            default:
                cout << "  [!] Opcion invalida.\n";
                pausar();
                break;
        }

    } while (opcion != 0);

    return 0;
}


