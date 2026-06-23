#pragma once

#include <string>


int buscarIndiceClientePorId(int idBuscado);
int generarIdClienteAleatorio();
int registrarCliente(std::string nombre, std::string telefono);
void mostrarClientes();
void mostrarClientePorId(int idBuscado);
bool modificarCliente(int idBuscado, std::string nuevoNombre, std::string nuevoTelefono);
bool desactivarCliente(int idBuscado);
bool activarCliente(int idBuscado);
bool guardarClientes(std ::string nombreArchivo);
bool cargarClientes(std ::string nombreArchivo);
void menuClientes();