#pragma once

#include<string>

int contarVentas(std::string nombreArchivo);
double calcularTotalVendido(std::string nombreArchivo);
double calcularPromedioVenta(std::string nombreArchivo);
double buscarVentaMayor(std::string nombreArchivo);
double buscarVentaMenor(std::string nombreArchivo);
double calcularTotalIVA(std::string nombreArchivo);
double calcularTotalDescuentos(std::string nombreArchivo);
double calcularTotalPropinas(std::string nombreArchivo);

void mostrarEstadisticas(std::string nombreArchivo);
void menuEstadisticas();
int buscarClienteMasFrecuente(std::string nombreArchivo);