#pragma once

#include <string>

struct Usuario {
    std::string nombre;
    std::string clave;
    std::string rol;
    bool activo;
};

int buscarIndiceUsuarioPorNombre(std::string nombreBuscado);

bool rolValido(std::string rol);
bool registrarUsuario(std::string nombre, std::string clave, std::string rol);

void mostrarUsuarios();

bool cambiarClaveUsuario(std::string nombreBuscado, std::string nuevaClave);
bool cambiarRolUsuario(std::string nombreBuscado, std::string nuevoRol);
bool desactivarUsuario(std::string nombreBuscado);
bool activarUsuario(std::string nombreBuscado);

bool cargarUsuarios(std::string nombreArchivo);
bool guardarUsuarios(std::string nombreArchivo);

std::string iniciarSesion();

void menuRoles();