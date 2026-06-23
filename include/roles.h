#pragma once

#include <string>

bool rolValido(std::string rol);
int buscarIndiceUsuarioPorNombre(std::string nombreBuscado);

bool registrarUsuario(std::string nombre, std::string clave, std::string rol);
bool usuarioActivo(std::string nombre);

bool activarUsuario(std::string nombre);
bool desactivarUsuario(std::string nombre);

bool cambiarClaveUsuario(std::string nombre, std::string nuevaClave);
bool cambiarRolUsuario(std::string nombre, std::string nuevoRol);

bool claveCorrecta(std::string nombre, std::string clave);
std::string obtenerRolUsuario(std::string nombre);

bool guardarUsuarios(std::string nombreArchivo);
bool cargarUsuarios(std::string nombreArchivo);

void mostrarUsuarios();
void menuRoles();