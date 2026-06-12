// GestorProductos.h - Coordina productos e inventario. Expone el menú y
// las funciones de integración para los módulos de Pedidos y Facturación.

#ifndef GESTOR_PRODUCTOS_H
#define GESTOR_PRODUCTOS_H

#include "Producto.h"
#include "Inventario.h"
#include <vector>
#include <string>
using namespace std;

class GestorProductos {
private:
    vector<Producto> productos;
    Inventario            inventario;
    string                archivoProductos;
    string                archivoInventario;

    // Auxiliares internos
    int         buscarIndicePorId(int id) const; // Retorna índice o -1
    bool        existeId(int id)          const;
    int         leerEnteroValido(const string& msg) const;
    double      leerDoubleValido(const string& msg) const;
    string leerLineaNoVacia(const string& msg) const;

public:
    GestorProductos(const string& archProd = "data/productos.csv",
                    const string& archInv  = "data/inventario.csv");

    // Punto de entrada: llama a este método desde main()
    void menuPrincipal();

    // Submenús
    void menuProductos();
    void menuInventario();

    // Operaciones sobre productos
    void agregarProducto();
    void mostrarTodos()        const;
    void buscarPorId()         const;
    void buscarPorNombre()     const;
    void modificarProducto();
    void desactivarProducto();
    void activarProducto();
    void guardarProductos()    const;
    void cargarProductos();

    // Operaciones sobre inventario
    void registrarStockInicial();
    void aumentarStock();
    void disminuirStock();
    void consultarStock()            const;
    void mostrarInventarioCompleto() const;
    void mostrarProductosAgotados()  const;
    void guardarInventario()         const;
    void cargarInventario();

    // Integración con Pedidos y Facturación
    double      getPrecioProducto  (int idProducto)              const;
    string getNombreProducto  (int idProducto)              const;
    int         getStockDisponible (int idProducto)              const;
    bool        productoEstaActivo (int idProducto)              const;
    bool        hayStockSuficiente (int idProducto, int cantidad) const;
    bool        reducirStockPorVenta(int idProducto, int cantidad);
    int         getTotalProductos  ()                            const;
    const vector<Producto>& getProductos()                  const;
};

#endif
