#ifndef MESA_H
#define Mesa_H

class Mesa{
private:
    int idMesa;
    int capacidad;
    bool ocupada;
    int idPedidoActivo;

public:
   Mesa();
   Mesa(int id, int CapacidadMesa);

   int getIdMesa() const;
   int getCapacidad() const;
   bool estaOcupada() const;
   int getIdPedidoActivo() const;


   void ocupar (int idPedido);
   void liberar();
   void mostrar() const;

};

#endif