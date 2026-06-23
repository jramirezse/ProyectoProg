// Inventario.cpp - Implementación de la clase Inventario

#include "../include/Inventario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
using namespace std;
Inventario::Inventario() {}

void Inventario::registrarStock(int idProducto, int cantInicial) {
    if (cantInicial < 0)
        throw invalid_argument("La cantidad inicial no puede ser negativa.");
    if (stocks.count(idProducto) > 0)
        throw logic_error("El producto ID " + std::to_string(idProducto) +
                               " ya tiene stock. Use 'Aumentar Stock'.");
    stocks[idProducto] = cantInicial;
}

void Inventario::aumentarStock(int idProducto, int cantidad) {
    if (cantidad <= 0)
        throw invalid_argument("La cantidad debe ser mayor que cero.");
    if (stocks.count(idProducto) == 0)
        throw out_of_range("Producto ID " + to_string(idProducto) +
                                " no registrado en inventario.");
    stocks[idProducto] += cantidad;
}

void Inventario::disminuirStock(int idProducto, int cantidad) {
    if (cantidad <= 0)
        throw invalid_argument("La cantidad debe ser mayor que cero.");
    if (stocks.count(idProducto) == 0)
        throw out_of_range("Producto ID " + std::to_string(idProducto) +
                                " no registrado en inventario.");
    if (stocks[idProducto] < cantidad)
        throw underflow_error(
            "Stock insuficiente. Disponible: " +
            to_string(stocks.at(idProducto)) +
            ", Solicitado: " + std::to_string(cantidad));
    stocks[idProducto] -= cantidad;
}

int Inventario::consultarStock(int idProducto) const {
    try {
        return stocks.at(idProducto);
    } catch (const out_of_range&) {
        throw out_of_range("Producto ID " + to_string(idProducto) +
                                " no registrado en inventario.");
    }
}

bool Inventario::existeEnInventario(int idProducto) const {
    return stocks.count(idProducto) > 0;
}

void Inventario::mostrarInventario() const {
    if (stocks.empty()) {
        cout << "  [!] El inventario esta vacio.\n";
        return;
    }
    cout << "\n" << string(35, '-') << "\n";
    cout << left << setw(15) << "  ID Producto"
                           << setw(20) << "Stock Disponible" << "\n";
    cout << string(35, '-') << "\n";
    for (const auto& par : stocks)
        cout << left
                  << setw(15) << ("  " + to_string(par.first))
                  << setw(20) << par.second << "\n";
    cout << string(35, '-') << "\n";
    cout << "  Total: " << stocks.size() << " producto(s)\n";
}

void Inventario::mostrarAgotados() const {
    bool hayAgotados = false;
    cout << "\n" << string(35, '=') << "\n";
    cout << "  PRODUCTOS AGOTADOS (stock = 0)\n";
    cout << string(35, '=') << "\n";
    for (const auto& par : stocks) {
        if (par.second == 0) {
            cout << "  > ID: " << par.first << "\n";
            hayAgotados = true;
        }
    }
    if (!hayAgotados) cout << "  [OK] No hay productos agotados.\n";
    cout << string(35, '=') << "\n";
}

void Inventario::guardarInventario(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
        throw runtime_error("No se pudo abrir para escritura: " + nombreArchivo);
    archivo << "idProducto,stock\n";
    for (const auto& par : stocks)
        archivo << par.first << "," << par.second << "\n";
    archivo.close();
}

void Inventario::cargarInventario(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
        throw runtime_error("No se pudo abrir para lectura: " + nombreArchivo);
    stocks.clear();
    string linea;
    getline(archivo, linea);
    int numLinea = 2;
    while (getline(archivo, linea)) {
        if (linea.empty()) { numLinea++; continue; }
        stringstream ss(linea);
        string campo;
        try {
            getline(ss, campo, ','); int id    = stoi(campo);
            getline(ss, campo);      int stock = stoi(campo);
            stocks[id] = stock;
        } catch (const exception& e) {
            cerr << "  [ADVERTENCIA] Linea " << numLinea << ": " << e.what() << "\n";
        }
        numLinea++;
    }
}

bool Inventario::hayStockSuficiente(int idProducto, int cantidad) const {
    if (stocks.count(idProducto) == 0) return false;
    return stocks.at(idProducto) >= cantidad;
}

const map<int, int>& Inventario::getStocks() const {
    return stocks;
}