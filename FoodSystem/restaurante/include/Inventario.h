// Inventario.h - Gestiona el stock disponible de cada producto

#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <map>
#include <string>

class Inventario {
private:
    std::map<int, int> stocks;

public:
    Inventario();

    void registrarStock(int idProducto, int cantInicial);
    void aumentarStock(int idProducto, int cantidad);
    void disminuirStock(int idProducto, int cantidad);

    int consultarStock(int idProducto) const;
    bool existeEnInventario(int idProducto) const;

    void mostrarInventario() const;
    void mostrarAgotados() const;

    void guardarInventario(const std::string& nombreArchivo) const;
    void cargarInventario(const std::string& nombreArchivo);

    bool hayStockSuficiente(int idProducto, int cantidad) const;

    const std::map<int, int>& getStocks() const;
};

#endif