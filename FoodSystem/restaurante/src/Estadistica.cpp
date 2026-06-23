#include "../include/estadisticas.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int contarVentas(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if(archivo.is_open() == false){
        return 0;
    }
    string linea;
    int cont = 0;
    getline(archivo, linea);
    while(getline(archivo, linea)){
        if(linea.empty()){
            continue;
        }
        cont+=1;
    }
    archivo.close();
    return cont;
}
double calcularTotalVendido(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return 0;
    }

    string linea;
    double totalVendido = 0;

    getline(archivo, linea);

    while (getline(archivo, linea)) {

        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string campoIdVenta;
        string campoIdPedido;
        string campoIdCliente;
        string campoSubtotal;
        string campoIva;
        string campoDescuento;
        string campoPropina;
        string campoTotal;

        getline(ss, campoIdVenta, ',');
        getline(ss, campoIdPedido, ',');
        getline(ss, campoIdCliente, ',');
        getline(ss, campoSubtotal, ',');
        getline(ss, campoIva, ',');
        getline(ss, campoDescuento, ',');
        getline(ss, campoPropina, ',');
        getline(ss, campoTotal, ',');

        double totalVenta = stod(campoTotal);

        totalVendido += totalVenta;
    }

    archivo.close();

    return totalVendido;
}
double calcularPromedioVenta(string nombreArchivo){
    int cantidadVentas = contarVentas(nombreArchivo);
    double totalventido = calcularTotalVendido(nombreArchivo);

    if(cantidadVentas== 0){
        return 0;
    }
    return totalventido / cantidadVentas;

}
double buscarVentaMayor(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return 0;
    }

    string linea;
    getline(archivo, linea); // saltar encabezado

    bool primeraVenta = true;
    double mayor = 0;

    while (getline(archivo, linea)) {

        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string campoIdVenta;
        string campoIdPedido;
        string campoIdCliente;
        string campoSubtotal;
        string campoIva;
        string campoDescuento;
        string campoPropina;
        string campoTotal;

        getline(ss, campoIdVenta, ',');
        getline(ss, campoIdPedido, ',');
        getline(ss, campoIdCliente, ',');
        getline(ss, campoSubtotal, ',');
        getline(ss, campoIva, ',');
        getline(ss, campoDescuento, ',');
        getline(ss, campoPropina, ',');
        getline(ss, campoTotal, ',');

        double totalVenta = stod(campoTotal);

        if (primeraVenta == true) {
            mayor = totalVenta;
            primeraVenta = false;
        } else {
            if (totalVenta > mayor) {
                mayor = totalVenta;
            }
        }
    }

    archivo.close();

    return mayor;
}
double buscarVentaMenor(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return 0;
    }

    string linea;
    getline(archivo, linea); 

    bool primeraVenta = true;
    double menor = 0;

    while (getline(archivo, linea)) {

        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string campoIdVenta;
        string campoIdPedido;
        string campoIdCliente;
        string campoSubtotal;
        string campoIva;
        string campoDescuento;
        string campoPropina;
        string campoTotal;

        getline(ss, campoIdVenta, ',');
        getline(ss, campoIdPedido, ',');
        getline(ss, campoIdCliente, ',');
        getline(ss, campoSubtotal, ',');
        getline(ss, campoIva, ',');
        getline(ss, campoDescuento, ',');
        getline(ss, campoPropina, ',');
        getline(ss, campoTotal, ',');

        double totalVenta = stod(campoTotal);

        if (primeraVenta == true) {
            menor = totalVenta;
            primeraVenta = false;
        } else {
            if (totalVenta < menor) {
                menor = totalVenta;
            }
        }
    }

    archivo.close();

    return menor;
}
double calcularTotalIVA(string nombreArchivo){
    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return 0;
    }
    double TotalIva= 0;
    string linea;
    getline(archivo, linea); 
    while(getline(archivo, linea)){
        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string campoIdVenta;
        string campoIdPedido;
        string campoIdCliente;
        string campoSubtotal;
        string campoIva;
        string campoDescuento;
        string campoPropina;
        string campoTotal;

        getline(ss, campoIdVenta, ',');
        getline(ss, campoIdPedido, ',');
        getline(ss, campoIdCliente, ',');
        getline(ss, campoSubtotal, ',');
        getline(ss, campoIva, ',');
        getline(ss, campoDescuento, ',');
        getline(ss, campoPropina, ',');
        getline(ss, campoTotal, ',');

        TotalIva+= stod(campoIva);

    }
    archivo.close();
    return TotalIva;
}
double calcularTotalDescuentos(string nombreArchivo){
    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return 0;
    }
    double totaldesc = 0;
    string linea;
    getline(archivo, linea); 
    while(getline(archivo, linea)){
        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string campoIdVenta;
        string campoIdPedido;
        string campoIdCliente;
        string campoSubtotal;
        string campoIva;
        string campoDescuento;
        string campoPropina;
        string campoTotal;

        getline(ss, campoIdVenta, ',');
        getline(ss, campoIdPedido, ',');
        getline(ss, campoIdCliente, ',');
        getline(ss, campoSubtotal, ',');
        getline(ss, campoIva, ',');
        getline(ss, campoDescuento, ',');
        getline(ss, campoPropina, ',');
        getline(ss, campoTotal, ',');

        totaldesc+= stod(campoDescuento);

    }
    archivo.close();
    return totaldesc;
}
double calcularTotalPropinas(string nombreArchivo){
    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return 0;
    }
    double totalpro= 0;
    string linea;
    getline(archivo, linea); 
    while(getline(archivo, linea)){
        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string campoIdVenta;
        string campoIdPedido;
        string campoIdCliente;
        string campoSubtotal;
        string campoIva;
        string campoDescuento;
        string campoPropina;
        string campoTotal;

        getline(ss, campoIdVenta, ',');
        getline(ss, campoIdPedido, ',');
        getline(ss, campoIdCliente, ',');
        getline(ss, campoSubtotal, ',');
        getline(ss, campoIva, ',');
        getline(ss, campoDescuento, ',');
        getline(ss, campoPropina, ',');
        getline(ss, campoTotal, ',');

        totalpro+= stod(campoPropina);

    }
    archivo.close();
    return totalpro;
}
void mostrarEstadisticas(string nombreArchivo) {

    int cantidadVentas = contarVentas(nombreArchivo);
    double totalVendido = calcularTotalVendido(nombreArchivo);
    double promedioVenta = calcularPromedioVenta(nombreArchivo);
    double ventaMayor = buscarVentaMayor(nombreArchivo);
    double ventaMenor = buscarVentaMenor(nombreArchivo);
    double totalIVA = calcularTotalIVA(nombreArchivo);
    double totalDescuentos = calcularTotalDescuentos(nombreArchivo);
    double totalPropinas = calcularTotalPropinas(nombreArchivo);
    int clienteFrecuente = buscarClienteMasFrecuente(nombreArchivo);

    cout << fixed << setprecision(2);

    cout << "\n"
         << "╔════════════════════════════════════════════╗\n"
         << "║           ESTADISTICAS DE VENTAS           ║\n"
         << "╠════════════════════════════════════════════╣\n";

    cout << "  Cantidad de ventas:      " << cantidadVentas << endl;
    cout << "  Total vendido:           $" << totalVendido << endl;
    cout << "  Promedio por venta:      $" << promedioVenta << endl;
    cout << "  Venta mayor:             $" << ventaMayor << endl;
    cout << "  Venta menor:             $" << ventaMenor << endl;
    if (clienteFrecuente == 0) {
    cout << "  Cliente mas frecuente:  Sin clientes registrados" << endl;
    } else {
    cout << "  Cliente mas frecuente:  ID " << clienteFrecuente << endl;
    }

    cout << "╠════════════════════════════════════════════╣\n";

    cout << "  Total IVA recaudado:     $" << totalIVA << endl;
    cout << "  Total descuentos dados:  $" << totalDescuentos << endl;
    cout << "  Total propinas:          $" << totalPropinas << endl;

    cout << "╚════════════════════════════════════════════╝\n";
}
void menuEstadisticas() {

    int opcion;

    do {
        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║              MENU ESTADISTICAS             ║\n"
             << "╠════════════════════════════════════════════╣\n"
             << "║  1. Ver resumen general de ventas          ║\n"
             << "║  2. Ver cantidad de ventas                 ║\n"
             << "║  3. Ver total vendido                      ║\n"
             << "║  4. Ver promedio por venta                 ║\n"
             << "║  5. Ver venta mayor y menor                ║\n"
             << "║  6. Ver IVA, descuentos y propinas         ║\n"
             << "║  0. Volver                                 ║\n"
             << "╚════════════════════════════════════════════╝\n"
             << "Seleccione una opcion: ";

        cin >> opcion;

        cout << fixed << setprecision(2);

        switch (opcion) {

            case 1:
                mostrarEstadisticas("data/ventas.csv");
                break;

            case 2:
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║             CANTIDAD DE VENTAS             ║\n"
                     << "╠════════════════════════════════════════════╣\n"
                     << "  Ventas registradas: " << contarVentas("data/ventas.csv") << endl
                     << "╚════════════════════════════════════════════╝\n";
                break;

            case 3:
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║              TOTAL VENDIDO                 ║\n"
                     << "╠════════════════════════════════════════════╣\n"
                     << "  Total vendido: $" << calcularTotalVendido("data/ventas.csv") << endl
                     << "╚════════════════════════════════════════════╝\n";
                break;

            case 4:
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║            PROMEDIO POR VENTA              ║\n"
                     << "╠════════════════════════════════════════════╣\n"
                     << "  Promedio: $" << calcularPromedioVenta("data/ventas.csv") << endl
                     << "╚════════════════════════════════════════════╝\n";
                break;

            case 5:
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║            VENTA MAYOR Y MENOR             ║\n"
                     << "╠════════════════════════════════════════════╣\n"
                     << "  Venta mayor: $" << buscarVentaMayor("data/ventas.csv") << endl
                     << "  Venta menor: $" << buscarVentaMenor("data/ventas.csv") << endl
                     << "╚════════════════════════════════════════════╝\n";
                break;

            case 6:
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║        IVA, DESCUENTOS Y PROPINAS          ║\n"
                     << "╠════════════════════════════════════════════╣\n"
                     << "  Total IVA:        $" << calcularTotalIVA("data/ventas.csv") << endl
                     << "  Descuentos:       $" << calcularTotalDescuentos("data/ventas.csv") << endl
                     << "  Propinas:         $" << calcularTotalPropinas("data/ventas.csv") << endl
                     << "╚════════════════════════════════════════════╝\n";
                break;

            case 0:
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║          VOLVIENDO AL MENU ANTERIOR        ║\n"
                     << "╚════════════════════════════════════════════╝\n";
                break;

            default:
                cout << "\n"
                     << "╔════════════════════════════════════════════╗\n"
                     << "║              OPCION INVALIDA               ║\n"
                     << "║            Intente nuevamente              ║\n"
                     << "╚════════════════════════════════════════════╝\n";
                break;
        }

    } while (opcion != 0);
}
int buscarClienteMasFrecuente(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return 0;
    }

    vector<int> idsClientes;
    vector<int> conteosClientes;

    string linea;

    getline(archivo, linea);

    while (getline(archivo, linea)) {

        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string campoIdVenta;
        string campoIdPedido;
        string campoIdCliente;
        string campoSubtotal;
        string campoIva;
        string campoDescuento;
        string campoPropina;
        string campoTotal;

        getline(ss, campoIdVenta, ',');
        getline(ss, campoIdPedido, ',');
        getline(ss, campoIdCliente, ',');
        getline(ss, campoSubtotal, ',');
        getline(ss, campoIva, ',');
        getline(ss, campoDescuento, ',');
        getline(ss, campoPropina, ',');
        getline(ss, campoTotal, ',');

        int idCliente = stoi(campoIdCliente);

        if (idCliente == 0) {
            continue;
        }

        bool encontrado = false;

        for (int i = 0; i < idsClientes.size(); i++) {

            if (idsClientes[i] == idCliente) {
                conteosClientes[i]++;
                encontrado = true;
            }
        }

        if (encontrado == false) {
            idsClientes.push_back(idCliente);
            conteosClientes.push_back(1);
        }
    }

    archivo.close();

    if (idsClientes.empty()) {
        return 0;
    }

    int indiceMayor = 0;

    for (int i = 1; i < conteosClientes.size(); i++) {

        if (conteosClientes[i] > conteosClientes[indiceMayor]) {
            indiceMayor = i;
        }
    }

    return idsClientes[indiceMayor];
}
