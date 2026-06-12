#include "Mesa.h"

#include <iostream>
#include <stdexcept>

using namespace std;

Mesa:: Mesa()
   : idMesa(0),
     capacidad(0),
     ocupada(false),
     idPedidoActivo(-1){

     }
Mesa:: Mesa(int id, int capacidadMesa)
     :idMesa(id),
      capacidad(capacidadMesa),
      ocupada(false),
      idPedidoActivo(-1){
      if(id<=0){
        throw invalid_argument("El ID de la mesa debe de ser positivo.");

      }
      if(capacidadMesa<=0){
        throw invalid_argument("La capacidad de la mesa debe ser positiva");
      }
    }
int Mesa::getIdMesa() const{
  return idMesa;
}

int Mesa::getCapacidad() const{
  return capacidad;
}

bool Mesa::estaOcupada() const{
  return ocupada;
}

int Mesa::getIdPedidoActivo() const{
  return idPedidoActivo;
}

void Mesa::ocupar(int idPedido){
  if(ocupada){
    throw logic_error("La mesa ya esta ocupada.");
  }
  if(idPedido<=0){
    throw invalid_argument("El ID del pedido debe ser positivo.");
  }
  ocupada=true;
  idPedidoActivo=idPedido;
}
void Mesa::liberar() {
    ocupada = false;
    idPedidoActivo = -1;
}
void Mesa::mostrar() const {
    cout << "Mesa " << idMesa
         << " | Capacidad: " << capacidad
         << " | Estado: " << (ocupada ? "OCUPADA" : "LIBRE");

    if (ocupada) {
        cout << " | Pedido activo: " << idPedidoActivo;
    }

    cout << "\n";
}