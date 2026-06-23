#include "../include/roles.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

vector<string> usuarios;
vector<string> claves;
vector<string> roles;
vector<bool> activos;

bool rolValido(string rol) {

    if (rol == "ADMIN") {
        return true;
    }

    if (rol == "INVENTARIO") {
        return true;
    }

    if (rol == "CAJERO") {
        return true;
    }

    if (rol == "MESERO") {
        return true;
    }

    return false;
}
int buscarIndiceUsuarioPorNombre(string nombreBuscado){
    for (int i = 0; i < usuarios.size(); i++){
        if(nombreBuscado == usuarios[i]){
            return i;
        }
    }
    return -1;
}
bool registrarUsuario(string nombre, string clave, string rol) {

    if(buscarIndiceUsuarioPorNombre(nombre) != -1){
        return false;
    }
    if(nombre.size() <=0){
        return false;
    }
    if(clave.size()<=0){
        return false;
    }

    if(rolValido(rol)== false){
        return false;
    }

    if(buscarIndiceUsuarioPorNombre(nombre) != -1){
        return false;
    }
    usuarios.push_back(nombre);
    claves.push_back(clave);
    roles.push_back(rol);
    activos.push_back(true);

    return true;
    
}
bool usuarioActivo(string nombre){
    if(buscarIndiceUsuarioPorNombre(nombre) == -1){
        return false;
    }
    int pos = buscarIndiceUsuarioPorNombre(nombre);
    return activos[pos];
}
bool desactivarUsuario(string nombre) {

    int pos = buscarIndiceUsuarioPorNombre(nombre);

    if(pos== -1){
        return false;
    }
    if(activos[pos]== false){
        return true;
    }
    activos[pos]=false;
    return true;
}
bool activarUsuario(string nombre) {

    int pos = buscarIndiceUsuarioPorNombre(nombre);

    if(pos== -1){
        return false;
    }
    if(activos[pos]== true){
        return true;
    }
    activos[pos]= true;
    return true;
}
bool guardarUsuarios(string nombreArchivo){
    ofstream archivo(nombreArchivo);
    if(archivo.is_open()== false){
        return false;
    }
    archivo<<"usuario,clave,rol,activo"<<endl;
    for (int i=0;i<usuarios.size();i++){
        archivo<<usuarios[i]<<","<<claves[i]<<","<<roles[i]<<","<<activos[i]<<endl;
    }
    archivo.close();
    return true;

}
bool cargarUsuarios(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if(archivo.is_open()==false){
        return false;
    }

    usuarios.clear();
    claves.clear();
    roles.clear();
    activos.clear();

    string linea;

    getline(archivo, linea);
    string campoUsuario, campoClave, campoRol, campoActivo;
    while(getline(archivo,linea)){
        if(linea.empty()){
            continue;
        }
        stringstream ss(linea);
        getline(ss,campoUsuario, ',');
        usuarios.push_back(campoUsuario);
        getline(ss,campoClave, ',');
        claves.push_back(campoClave);
        getline(ss,campoRol, ',');
        roles.push_back(campoRol);
        getline(ss,campoActivo, ',');
        int b00l= stoi(campoActivo);
        if(b00l == 1){
            activos.push_back(true);
        }else{
            activos.push_back(false);
        }
    
        

    }
    archivo.close();
    return true;
}

bool claveCorrecta(string nombre, string clave) {

    int pos = buscarIndiceUsuarioPorNombre(nombre);

    if (pos == -1) {
        return false;
    }

    if (claves[pos] == clave) {
        return true;
    }

    return false;
}
string obtenerRolUsuario(string nombre) {

    int pos = buscarIndiceUsuarioPorNombre(nombre);

    if (pos == -1) {
        return "";
    }

    return roles[pos];
}
bool cambiarClaveUsuario(string nombre, string nuevaClave) {

    int pos = buscarIndiceUsuarioPorNombre(nombre);

    if (pos == -1) {
        return false;
    }

    if (nuevaClave.empty()) {
        return false;
    }

    claves[pos] = nuevaClave;

    return true;
}
bool cambiarRolUsuario(string nombre, string nuevoRol) {

    int pos = buscarIndiceUsuarioPorNombre(nombre);

    if (pos == -1) {
        return false;
    }

    if (rolValido(nuevoRol) == false) {
        return false;
    }

    roles[pos] = nuevoRol;

    return true;
}
void mostrarUsuarios() {

    if (usuarios.empty()) {
        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║          NO HAY USUARIOS REGISTRADOS      ║\n"
             << "╚════════════════════════════════════════════╝\n";
        return;
    }

    cout << "\n"
         << "╔════════════════════════════════════════════╗\n"
         << "║              USUARIOS DEL SISTEMA         ║\n"
         << "╚════════════════════════════════════════════╝\n";

    for (int i = 0; i < usuarios.size(); i++) {

        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║                 USUARIO                   ║\n"
             << "╠════════════════════════════════════════════╣\n";

        cout << "  Nombre:       " << usuarios[i] << endl;
        cout << "  Rol:          " << roles[i] << endl;

        if (activos[i] == true) {
            cout << "  Estado:       ACTIVO" << endl;
        } else {
            cout << "  Estado:       INACTIVO" << endl;
        }

        cout << "╚════════════════════════════════════════════╝\n";
    }
}
void menuRoles() {

    int opcion;

    do {
        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║          ADMINISTRACION DE USUARIOS        ║\n"
             << "╠════════════════════════════════════════════╣\n"
             << "║  1. Registrar usuario                      ║\n"
             << "║  2. Mostrar usuarios                       ║\n"
             << "║  3. Cambiar clave de usuario               ║\n"
             << "║  4. Cambiar rol de usuario                 ║\n"
             << "║  5. Activar usuario                        ║\n"
             << "║  6. Desactivar usuario                     ║\n"
             << "║  7. Guardar usuarios                       ║\n"
             << "║  8. Cargar usuarios                        ║\n"
             << "║  0. Volver                                 ║\n"
             << "╚════════════════════════════════════════════╝\n"
             << "Seleccione una opcion: ";

        cin >> opcion;
        cin.ignore(10000, '\n');

        switch (opcion) {

            case 1: {
                string nombre;
                string clave;
                string rol;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║             REGISTRAR USUARIO              ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese nombre de usuario: ";
                getline(cin, nombre);

                cout << "Ingrese clave: ";
                getline(cin, clave);

                cout << "Ingrese rol ADMIN / INVENTARIO / CAJERO / MESERO: ";
                getline(cin, rol);

                bool resultado = registrarUsuario(nombre, clave, rol);

                if (resultado) {
                    cout << "\n[OK] Usuario registrado correctamente.\n";
                } else {
                    cout << "\n[!] No se pudo registrar el usuario.\n";
                    cout << "    Revise que el nombre no exista y que el rol sea valido.\n";
                }

                break;
            }

            case 2: {
                mostrarUsuarios();
                break;
            }

            case 3: {
                string nombre;
                string nuevaClave;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║            CAMBIAR CLAVE USUARIO           ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese nombre de usuario: ";
                getline(cin, nombre);

                cout << "Ingrese nueva clave: ";
                getline(cin, nuevaClave);

                bool resultado = cambiarClaveUsuario(nombre, nuevaClave);

                if (resultado) {
                    cout << "\n[OK] Clave actualizada correctamente.\n";
                } else {
                    cout << "\n[!] No se pudo cambiar la clave.\n";
                }

                break;
            }

            case 4: {
                string nombre;
                string nuevoRol;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║             CAMBIAR ROL USUARIO            ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese nombre de usuario: ";
                getline(cin, nombre);

                cout << "Ingrese nuevo rol ADMIN / INVENTARIO / CAJERO / MESERO: ";
                getline(cin, nuevoRol);

                bool resultado = cambiarRolUsuario(nombre, nuevoRol);

                if (resultado) {
                    cout << "\n[OK] Rol actualizado correctamente.\n";
                } else {
                    cout << "\n[!] No se pudo cambiar el rol.\n";
                    cout << "    Revise que el usuario exista y que el rol sea valido.\n";
                }

                break;
            }

            case 5: {
                string nombre;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║              ACTIVAR USUARIO               ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese nombre de usuario: ";
                getline(cin, nombre);

                bool resultado = activarUsuario(nombre);

                if (resultado) {
                    cout << "\n[OK] Usuario activo.\n";
                } else {
                    cout << "\n[!] El usuario no existe.\n";
                }

                break;
            }

            case 6: {
                string nombre;

                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║            DESACTIVAR USUARIO              ║\n"
                     << "╚════════════════════════════════════════════╝\n";

                cout << "Ingrese nombre de usuario: ";
                getline(cin, nombre);

                bool resultado = desactivarUsuario(nombre);

                if (resultado) {
                    cout << "\n[OK] Usuario inactivo.\n";
                } else {
                    cout << "\n[!] El usuario no existe.\n";
                }

                break;
            }

            case 7: {
                bool resultado = guardarUsuarios("data/usuarios.csv");

                if (resultado) {
                    cout << "\n[OK] Usuarios guardados correctamente.\n";
                } else {
                    cout << "\n[!] No se pudieron guardar los usuarios.\n";
                }

                break;
            }

            case 8: {
                bool resultado = cargarUsuarios("data/usuarios.csv");

                if (resultado) {
                    cout << "\n[OK] Usuarios cargados correctamente.\n";
                } else {
                    cout << "\n[!] No se pudieron cargar los usuarios.\n";
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
                cout << "\n[!] Opcion invalida. Intente nuevamente.\n";
                break;
            }
        }

    } while (opcion != 0);
}

