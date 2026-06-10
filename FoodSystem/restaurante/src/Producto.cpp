// Producto.cpp - Implementación de la clase Producto

#include "Producto.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
using namespace std;

Producto::Producto()
    : idProducto(0), nombre(""), categoria(""), precio(0.0), activo(true)
{}

Producto::Producto(int id, const std::string& nom, const std::string& cat,
                   double prec, bool estadoAct)
    : idProducto(id), nombre(nom), categoria(cat), precio(0.0), activo(estadoAct)
{
    setPrecio(prec);
}

int         Producto::getId()        const { return idProducto; }
string      Producto::getNombre()    const { return nombre;     }
string      Producto::getCategoria() const { return categoria;  }
double      Producto::getPrecio()    const { return precio;     }
bool        Producto::isActivo()     const { return activo;     }

void Producto::setNombre(const std::string& nom) {
    if (nom.empty()) throw invalid_argument("El nombre no puede estar vacio.");
    nombre = nom;
}

void Producto::setCategoria(const string& cat) {
    if (cat.empty()) throw std::invalid_argument("La categoria no puede estar vacia.");
    categoria = cat;
}

void Producto::setPrecio(double prec) {
    if (prec < 0.0) throw std::invalid_argument("El precio no puede ser negativo.");
    precio = prec;
}

void Producto::setActivo(bool estado) {
    activo = estado;
}

void Producto::mostrar() const {
    cout << left
              << setw(6)  << idProducto
              << setw(25) << nombre
              << setw(15) << categoria
              << right
              << fixed << std::setprecision(2)
              << setw(12) << precio
              << setw(10) << (activo ? "ACTIVO" : "INACTIVO")
              << "\n";
}

string Producto::toString() const {
    stringstream ss;
    ss << idProducto << "," << nombre << "," << categoria << ","
       << fixed << setprecision(2) << precio << ","
       << (activo ? 1 : 0);
    return ss.str();
}

void Producto::fromString(const string& linea) {
    stringstream ss(linea);
    string campo;
    try {
        getline(ss, campo, ','); idProducto = stoi(campo);
        getline(ss, campo, ','); nombre     = campo;
        getline(ss, campo, ','); categoria  = campo;
        getline(ss, campo, ','); precio     = stod(campo);
        getline(ss, campo);      activo     = (stoi(campo) == 1);
    } catch (const exception& e) {
        throw runtime_error(
            string("Error al parsear CSV: '") + linea + "'. " + e.what());
    }
}