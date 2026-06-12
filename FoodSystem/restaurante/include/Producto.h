// Producto.h - Clase que representa un producto del menú
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto {
private:
    int idProducto;
    std::string nombre;
    std::string categoria;
    double precio;
    bool activo;

public:
    Producto();

    Producto(
        int id,
        const std::string& nom,
        const std::string& cat,
        double prec,
        bool estadoAct = true
    );

    int getId() const;
    std::string getNombre() const;
    std::string getCategoria() const;
    double getPrecio() const;
    bool isActivo() const;

    void setNombre(const std::string& nom);
    void setCategoria(const std::string& cat);
    void setPrecio(double prec);
    void setActivo(bool estado);

    void mostrar() const;
    std::string toString() const;
    void fromString(const std::string& linea);
};

#endif