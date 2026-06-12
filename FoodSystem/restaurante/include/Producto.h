// Producto.h - Clase que representa un producto del menú

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
using namespace std;

class Producto {
private:
    int         idProducto;
    string nombre;
    string categoria;
    double      precio;
    bool        activo;

public:
    Producto();
    Producto(int id, const string& nom, const string& cat,
             double prec, bool estadoAct = true);

    // Getters
    int         getId()        const;
    string      getNombre()    const;
    string      getCategoria() const;
    double      getPrecio()    const;
    bool        isActivo()     const;

    // Setters (lanzan invalid_argument si el valor es inválido)
    void setNombre(const string& nom);
    void setCategoria(const string& cat);
    void setPrecio(double prec);
    void setActivo(bool estado);

    void        mostrar()    const;          // Imprime una fila en consola
    string toString()   const;          // Convierte a línea CSV
    void        fromString(const string& linea); // Carga desde línea CSV
};

#endif
