// Inventario.h - Gestiona el stock disponible de cada producto

#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <map>
#include <string>
using namespace std;

class Inventario {
private:
    map<int, int> stocks; // clave: idProducto, valor: unidades disponibles

public:
    Inventario();

    // Gestión de stock
    void registrarStock(int idProducto, int cantInicial); // Alta inicial
    void aumentarStock (int idProducto, int cantidad);    // Sumar unidades
    void disminuirStock(int idProducto, int cantidad);    // Restar unidades
    int  consultarStock(int idProducto) const;            // Retorna cantidad
    bool existeEnInventario(int idProducto) const;        // true si está registrado

    // Visualización
    void mostrarInventario() const;
    void mostrarAgotados()   const;

    // Persistencia
    void guardarInventario(const std::string& nombreArchivo) const;
    void cargarInventario (const std::string& nombreArchivo);

    // Integración con otros módulos
    bool hayStockSuficiente(int idProducto, int cantidad) const;
    const std::map<int, int>& getStocks() const;
};

#endif
