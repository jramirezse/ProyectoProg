// Inventario.cpp - Implementación de la clase Inventario

#include "Inventario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

Inventario::Inventario() {}

void Inventario::registrarStock(int idProducto, int cantInicial) {
    if (cantInicial < 0)
        throw std::invalid_argument("La cantidad inicial no puede ser negativa.");
    if (stocks.count(idProducto) > 0)
        throw std::logic_error("El producto ID " + std::to_string(idProducto) +
                               " ya tiene stock. Use 'Aumentar Stock'.");
    stocks[idProducto] = cantInicial;
}

void Inventario::aumentarStock(int idProducto, int cantidad) {
    if (cantidad <= 0)
        throw std::invalid_argument("La cantidad debe ser mayor que cero.");
    if (stocks.count(idProducto) == 0)
        throw std::out_of_range("Producto ID " + std::to_string(idProducto) +
                                " no registrado en inventario.");
    stocks[idProducto] += cantidad;
}

void Inventario::disminuirStock(int idProducto, int cantidad) {
    if (cantidad <= 0)
        throw std::invalid_argument("La cantidad debe ser mayor que cero.");
    if (stocks.count(idProducto) == 0)
        throw std::out_of_range("Producto ID " + std::to_string(idProducto) +
                                " no registrado en inventario.");
    if (stocks[idProducto] < cantidad)
        throw std::underflow_error(
            "Stock insuficiente. Disponible: " +
            std::to_string(stocks.at(idProducto)) +
            ", Solicitado: " + std::to_string(cantidad));
    stocks[idProducto] -= cantidad;
}

int Inventario::consultarStock(int idProducto) const {
    try {
        return stocks.at(idProducto);
    } catch (const std::out_of_range&) {
        throw std::out_of_range("Producto ID " + std::to_string(idProducto) +
                                " no registrado en inventario.");
    }
}

bool Inventario::existeEnInventario(int idProducto) const {
    return stocks.count(idProducto) > 0;
}

void Inventario::mostrarInventario() const {
    if (stocks.empty()) {
        std::cout << "  [!] El inventario esta vacio.\n";
        return;
    }
    std::cout << "\n" << std::string(35, '-') << "\n";
    std::cout << std::left << std::setw(15) << "  ID Producto"
                           << std::setw(20) << "Stock Disponible" << "\n";
    std::cout << std::string(35, '-') << "\n";
    for (const auto& par : stocks)
        std::cout << std::left
                  << std::setw(15) << ("  " + std::to_string(par.first))
                  << std::setw(20) << par.second << "\n";
    std::cout << std::string(35, '-') << "\n";
    std::cout << "  Total: " << stocks.size() << " producto(s)\n";
}

void Inventario::mostrarAgotados() const {
    bool hayAgotados = false;
    std::cout << "\n" << std::string(35, '=') << "\n";
    std::cout << "  PRODUCTOS AGOTADOS (stock = 0)\n";
    std::cout << std::string(35, '=') << "\n";
    for (const auto& par : stocks) {
        if (par.second == 0) {
            std::cout << "  > ID: " << par.first << "\n";
            hayAgotados = true;
        }
    }
    if (!hayAgotados) std::cout << "  [OK] No hay productos agotados.\n";
    std::cout << std::string(35, '=') << "\n";
}

void Inventario::guardarInventario(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
        throw std::runtime_error("No se pudo abrir para escritura: " + nombreArchivo);
    archivo << "idProducto,stock\n";
    for (const auto& par : stocks)
        archivo << par.first << "," << par.second << "\n";
    archivo.close();
}

void Inventario::cargarInventario(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
        throw std::runtime_error("No se pudo abrir para lectura: " + nombreArchivo);
    stocks.clear();
    std::string linea;
    std::getline(archivo, linea); // saltar encabezado
    int numLinea = 2;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) { numLinea++; continue; }
        std::stringstream ss(linea);
        std::string campo;
        try {
            std::getline(ss, campo, ','); int id    = std::stoi(campo);
            std::getline(ss, campo);      int stock = std::stoi(campo);
            stocks[id] = stock;
        } catch (const std::exception& e) {
            std::cerr << "  [ADVERTENCIA] Linea " << numLinea << ": " << e.what() << "\n";
        }
        numLinea++;
    }
}

bool Inventario::hayStockSuficiente(int idProducto, int cantidad) const {
    if (stocks.count(idProducto) == 0) return false;
    return stocks.at(idProducto) >= cantidad;
}

const std::map<int, int>& Inventario::getStocks() const {
    return stocks;
}
