#pragma once

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
    for (int i = 0; i<idsClientes.size();i++){
        if (i == idBuscado){
            return i;
        }
    }   
    return -1;
    
}

int generadIdClienteAleatorio(){

    if(idsClientes.size()<999){
        bool cic = true;
    bool check = true;
    srand(time(NULL));
    while (cic == true){
        check = true;
        int num = (rand()%999) + 1;
    
        for(int comp : idsClientes){
            if(comp == num){
                check = false;
            }
        }if (check == true and num >0 ){

            return num;
        }
    }


    }else{
        return -1;
    }
}

int registrarCliente(string nombre, string telefono) {

    if (nombre == "") {
        return -1;
    }

    if (telefono.size()!= 10) {
        return -1;
    }

    int id = generadIdClienteAleatorio();

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

    if (nuevoNombre.size()!= 10) {
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



 


