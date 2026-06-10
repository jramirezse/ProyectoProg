#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


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
    
}

bool registrarCliente(int id, string nombre, string telefono){

    if(id >0){

    }else{
        return false;
    }
}
