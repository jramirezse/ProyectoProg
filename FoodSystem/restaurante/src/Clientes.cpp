#include "clientes.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime> 
#include <cstdlib>


using namespace std;


vector<int> idsClientes;
vector<string> nombresClientes;
vector<string> telefonosClientes;
vector<bool> activosClientes;


int buscarIndiceClientePorId(int idBuscado) {
    for (int i = 0; i < idsClientes.size(); i++) {
        if (idsClientes[i] == idBuscado) {
            return i;
        }
    }

    return -1;
}

int generarIdClienteAleatorio() {

    if (idsClientes.size() >= 999) {
        return -1;
    }

    int num;
    bool idExiste;

    do {
        num = (rand() % 999) + 1;

        if (buscarIndiceClientePorId(num) != -1) {
            idExiste = true;
        } else {
            idExiste = false;
        }

    } while (idExiste == true);

    return num;
}

int registrarCliente(string nombre, string telefono) {

    if (nombre == "") {
        return -1;
    }

    if (telefono.size()!= 10) {
        return -1;
    }

    int id = generarIdClienteAleatorio();

    if (id == -1) {
        return -1;
    }

    idsClientes.push_back(id);
    nombresClientes.push_back(nombre);
    telefonosClientes.push_back(telefono);
    activosClientes.push_back(true);

    return id;
}

void mostrarClientes() {

    if (idsClientes.empty() or nombresClientes.empty() or telefonosClientes.empty() or activosClientes.empty()){
        cout << "No hay clientes registrados." << endl;
        return;
    }

    cout << "===== CLIENTES REGISTRADOS =====" << endl;

    for (int i = 0; i < idsClientes.size(); i++) {

        cout << "ID: " << idsClientes[i]<< endl;
        cout << "Nombre: " <<nombresClientes[i]<< endl;
        cout << "Telefono: " <<telefonosClientes[i]<< endl;

        if (activosClientes[i] == true) {
            cout << "Estado: ACTIVO" << endl;
        } else {
            cout << "Estado: INACTIVO" << endl;
        }

        cout << "----------------------------" << endl;
    }
}
void mostrarClientePorId(int idBuscado) {

    int posicion = buscarIndiceClientePorId(idBuscado);

    if (posicion == -1) {
        cout << "Cliente no encontrado." << endl;
        return;
    }

    cout << "===== CLIENTE ENCONTRADO =====" << endl;
    cout << "ID: " <<idsClientes[posicion]<< endl;
    cout << "Nombre: " <<nombresClientes[posicion]<< endl;
    cout << "Telefono: " <<telefonosClientes[posicion]<< endl;

    if (activosClientes[posicion]) {
        cout << "Estado: ACTIVO" << endl;
    } else {
        cout << "Estado: INACTIVO" << endl;
    }
}

bool modificarCliente(int idBuscado, string nuevoNombre, string nuevoTelefono) {

    int posicion = buscarIndiceClientePorId(idBuscado);



    if (posicion == -1) {
        return false;
    }

    if (nuevoNombre == "") {
        return false;
    }

    if (nuevoTelefono.size()!= 10) {
        return false;
    }

    nombresClientes[posicion] = nuevoNombre;
    telefonosClientes[posicion] = nuevoTelefono;

    return true;
}

bool desactivarCliente(int idBuscado) {

    int posicion = buscarIndiceClientePorId(idBuscado);

    if (posicion == -1) {
        return false;
    }

    if (activosClientes[posicion]== false) {
        return false;
    }

    activosClientes[posicion] = false;

    return true;
}
bool activarCliente(int idBuscado) {

    int posicion = buscarIndiceClientePorId(idBuscado);

    if (posicion == -1) {
        return false;
    }

    if (activosClientes[posicion]== true) {
        return false;
    }

    activosClientes[posicion] = true;

    return true;
}

bool guardarClientes(string nombreArchivo) {

    ofstream archivo(nombreArchivo);

    if (archivo.is_open()== false) {
        return false;
    }

    archivo << "idCliente,nombre,telefono,activo" << endl;

    for (int i = 0; i < idsClientes.size(); i++) {

        archivo << idsClientes[i]
                << ","
                << nombresClientes[i]
                << ","
                << telefonosClientes[i]
                << ","
                << activosClientes[i]
                << endl;
    }

    archivo.close();

    return true;
}
bool cargarClientes(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return false;
    }

    idsClientes.clear();
    nombresClientes.clear();
    telefonosClientes.clear();
    activosClientes.clear();

    string linea;

    getline(archivo, linea); 

    while (getline(archivo, linea)) {

        stringstream ss(linea);
        if (linea == "") {
         continue;
        }

        string campoId;
        string campoNombre;
        string campoTelefono;
        string campoActivo;

        getline(ss, campoId, ',');
        getline(ss, campoNombre, ',');
        getline(ss, campoTelefono, ',');
        getline(ss, campoActivo, ',');

        int id = stoi(campoId);
        int activo = stoi(campoActivo);

        idsClientes.push_back(id);
        nombresClientes.push_back(campoNombre);
        telefonosClientes.push_back(campoTelefono);
        activosClientes.push_back(activo);
    }

    archivo.close();

    return true;
}
void menuClientes() {

    int opcion;

    do {
        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║            GESTION DE CLIENTES             ║\n"
             << "╠════════════════════════════════════════════╣\n"
             << "║  1. Registrar cliente                      ║\n"
             << "║  2. Mostrar todos los clientes             ║\n"
             << "║  3. Buscar cliente por ID                  ║\n"
             << "║  4. Modificar cliente                      ║\n"
             << "║  5. Desactivar cliente                     ║\n"
             << "║  6. Activar cliente                        ║\n"
             << "║  7. Guardar clientes en archivo            ║\n"
             << "║  8. Cargar clientes desde archivo          ║\n"
             << "║  0. Volver                                 ║\n"
             << "╚════════════════════════════════════════════╝\n"
             << "Seleccione una opcion: ";

        cin >> opcion;

        switch (opcion) {

            case 1: {
                string nombre;
                string telefono;

                cin.ignore();

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║             REGISTRAR CLIENTE              ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese nombre del cliente: ";
                getline(cin, nombre);

                cout << "Ingrese telefono del cliente: ";
                getline(cin, telefono);

                int idGenerado = registrarCliente(nombre, telefono);

                if (idGenerado == -1) {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║  ERROR: No se pudo registrar el cliente    ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                } else {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║        CLIENTE REGISTRADO CORRECTO         ║\n"
                         << "╠════════════════════════════════════════════╣\n"
                         << "║  ID asignado: " << idGenerado << "\n"
                         << "╚════════════════════════════════════════════╝\n";
                }

                break;
            }

            case 2: {
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║          LISTADO DE CLIENTES               ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                mostrarClientes();

                break;
            }

            case 3: {
                int id;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║            BUSCAR CLIENTE POR ID           ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese el ID del cliente: ";
                cin >> id;

                mostrarClientePorId(id);

                break;
            }

            case 4: {
                int id;
                string nuevoNombre;
                string nuevoTelefono;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║             MODIFICAR CLIENTE              ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese el ID del cliente a modificar: ";
                cin >> id;

                cin.ignore();

                cout << "Ingrese nuevo nombre: ";
                getline(cin, nuevoNombre);

                cout << "Ingrese nuevo telefono: ";
                getline(cin, nuevoTelefono);

                bool resultado = modificarCliente(id, nuevoNombre, nuevoTelefono);

                if (resultado) {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║        CLIENTE MODIFICADO CORRECTO         ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                } else {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║  ERROR: No se pudo modificar el cliente    ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                }

                break;
            }

            case 5: {
                int id;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║            DESACTIVAR CLIENTE              ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese el ID del cliente a desactivar: ";
                cin >> id;

                bool resultado = desactivarCliente(id);

                if (resultado) {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║       CLIENTE DESACTIVADO CORRECTO         ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                } else {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║ ERROR: No se pudo desactivar el cliente    ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                }

                break;
            }

            case 6: {
                int id;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║              ACTIVAR CLIENTE               ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese el ID del cliente a activar: ";
                cin >> id;

                bool resultado = activarCliente(id);

                if (resultado) {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║         CLIENTE ACTIVADO CORRECTO          ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                } else {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║   ERROR: No se pudo activar el cliente     ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                }

                break;
            }

            case 7: {
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║              GUARDAR CLIENTES              ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                bool resultado = guardarClientes("data/clientes.csv");

                if (resultado) {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║       CLIENTES GUARDADOS CORRECTO          ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                } else {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║ ERROR: No se pudo guardar clientes         ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                }

                break;
            }

            case 8: {
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║              CARGAR CLIENTES               ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                bool resultado = cargarClientes("data/clientes.csv");

                if (resultado) {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║       CLIENTES CARGADOS CORRECTO           ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                } else {
                    cout << "\n"
                         << "╔════════════════════════════════════════════╗\n"
                         << "║ ERROR: No se pudo cargar clientes          ║\n"
                         << "╚════════════════════════════════════════════╝\n";
                }

                break;
            }

            case 0: {
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║          VOLVIENDO AL MENU ANTERIOR        ║\n"
                     << "╚════════════════════════════════════════════╝\n";
                break;
            }

            default: {
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║          OPCION INVALIDA                   ║\n"
                     << "║          Intente nuevamente                ║\n"
                     << "╚════════════════════════════════════════════╝\n";
                break;
            }
        }

    } while (opcion != 0);
}






 


