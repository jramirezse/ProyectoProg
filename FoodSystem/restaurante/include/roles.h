#pragma once

#include <string>

using namespace std;

bool rolValido(string rol);
int buscarIndiceUsuarioPorNombre(string nombreBuscado);

bool registrarUsuario(string nombre, string clave, string rol);
bool usuarioActivo(string nombre);

bool activarUsuario(string nombre);
bool desactivarUsuario(string nombre);

bool cambiarClaveUsuario(string nombre, string nuevaClave);
bool cambiarRolUsuario(string nombre, string nuevoRol);

bool claveCorrecta(string nombre, string clave);
string obtenerRolUsuario(string nombre);

bool guardarUsuarios(string nombreArchivo);
bool cargarUsuarios(string nombreArchivo);

void mostrarUsuarios();
void menuRoles();