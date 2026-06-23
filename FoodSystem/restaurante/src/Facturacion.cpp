#include "../include/facturacion.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

vector<Venta> ventas;


double calcularIVA(double subtotal) {

    if( subtotal <=0){
        return 0;
    }
    double IVA = subtotal * 0.19;
    return IVA;
}
double calcularDescuento(double subtotal, int descuento) {

    if(subtotal <= 0){
        return 0;
    }
    if(descuento <=0){
        return 0;
    }
    if (descuento > 100) {
    return subtotal;
    }
    double desc = subtotal * (descuento/100.0);
    return desc;
}
double calcularPropina(double subtotal, int porcentajePropina) {

    if(porcentajePropina <= 0 || subtotal <=0){
        return 0;
    }
    double propina = subtotal * (porcentajePropina/100.0);

    return propina;
}
double calcularTotal(double subtotal, double iva, double descuento, double propina) {

    if(subtotal <=0){
        return 0;
    }

    double total = subtotal+iva-descuento+propina;
    if(total <0){
        return 0;
    }
    return total;
}
int generarIdVenta() {

    if(ventas.empty()){

        return 1;
    }

    int mayor = ventas[0].idVenta;


        for(int num =1;num<ventas.size();num++){
            if(ventas[num].idVenta>mayor){
                mayor = ventas[num].idVenta;
            }
        }
        return mayor +1;

}
bool registrarVenta(
    int idPedido,
    int idCliente,
    double subtotal,
    int porcentajeDescuento,
    int porcentajePropina
) {

    if(idPedido<=0){
        return false;
    }

    if(idCliente <0){
        return false;
    }

    if(subtotal<=0){
        return false;
    }

    Venta nuevaVenta;

     nuevaVenta.idVenta = generarIdVenta();
     nuevaVenta.idPedido = idPedido;
     nuevaVenta.idCliente = idCliente;

     nuevaVenta.subtotal = subtotal;

     nuevaVenta.iva = calcularIVA(subtotal);
     double iva = calcularIVA(subtotal);
     nuevaVenta.descuento = calcularDescuento(subtotal, porcentajeDescuento);
     double descuento = calcularDescuento(subtotal, porcentajeDescuento);
     nuevaVenta.propina = calcularPropina(subtotal, porcentajePropina);
     double propina = calcularPropina(subtotal, porcentajePropina);

     nuevaVenta.total = calcularTotal(subtotal, iva, descuento, propina);

     ventas.push_back(nuevaVenta);

    return true;
}
void mostrarVentas() {

    if (ventas.empty()) {
        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║          NO HAY VENTAS REGISTRADAS         ║\n"
             << "╚════════════════════════════════════════════╝\n";

        return;
    }

    cout << fixed << setprecision(2);

    cout << "\n"
         << "╔════════════════════════════════════════════╗\n"
         << "║             VENTAS REGISTRADAS             ║\n"
         << "╚════════════════════════════════════════════╝\n";

    for (int i = 0; i < ventas.size(); i++) {

        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║                FACTURA / VENTA             ║\n"
             << "╠════════════════════════════════════════════╣\n";

        cout << "  ID venta:      " << ventas[i].idVenta << endl;
        cout << "  ID pedido:     " << ventas[i].idPedido << endl;

        if (ventas[i].idCliente == 0) {
            cout << "  ID cliente:    Sin cliente registrado" << endl;
        } else {
            cout << "  ID cliente:    " << ventas[i].idCliente << endl;
        }

        cout << "╠════════════════════════════════════════════╣\n";

        cout << "  Subtotal:      $" << ventas[i].subtotal << endl;
        cout << "  IVA:           $" << ventas[i].iva << endl;
        cout << "  Descuento:     $" << ventas[i].descuento << endl;
        cout << "  Propina:       $" << ventas[i].propina << endl;
        cout << "  Total:         $" << ventas[i].total << endl;

        cout << "╚════════════════════════════════════════════╝\n";
    }
}


void mostrarFactura(Venta venta) {

    time_t ahora = time(0);
    tm* tiempo = localtime(&ahora);

    cout << fixed << setprecision(2);

    cout << "\n";
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║              FOODSYSTEM FACTURA           ║\n";
    cout << "╠════════════════════════════════════════════╣\n";

    cout << "  Fecha:         "
         << setw(2) << setfill('0') << tiempo->tm_mday << "/"
         << setw(2) << setfill('0') << tiempo->tm_mon + 1 << "/"
         << tiempo->tm_year + 1900 << endl;

    cout << "  Hora:          "
         << setw(2) << setfill('0') << tiempo->tm_hour << ":"
         << setw(2) << setfill('0') << tiempo->tm_min << ":"
         << setw(2) << setfill('0') << tiempo->tm_sec << endl;

    cout << setfill(' ');

    cout << "  Factura No.:   " << venta.idVenta << endl;
    cout << "  Pedido No.:    " << venta.idPedido << endl;

    if (venta.idCliente == 0) {
        cout << "  Cliente:       Consumidor final" << endl;
    } else {
        cout << "  Cliente ID:    " << venta.idCliente << endl;
    }

    cout << "╠════════════════════════════════════════════╣\n";
    cout << "║              DETALLE DE PAGO              ║\n";
    cout << "╠════════════════════════════════════════════╣\n";

    cout << "  Subtotal:      $" << venta.subtotal << endl;
    cout << "  IVA 19%:       $" << venta.iva << endl;
    cout << "  Descuento:     $" << venta.descuento << endl;
    cout << "  Propina:       $" << venta.propina << endl;

    cout << "╠════════════════════════════════════════════╣\n";
    cout << "  TOTAL A PAGAR: $" << venta.total << endl;

    cout << "╠════════════════════════════════════════════╣\n";
    cout << "║          GRACIAS POR TU COMPRA            ║\n";
    cout << "║          Esperamos verte pronto           ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
}
void mostrarUltimaFactura() {

    if (ventas.empty()) {
        cout << "\n"
             << "╔════════════════════════════════════════════╗\n"
             << "║          NO HAY FACTURA PARA MOSTRAR      ║\n"
             << "╚════════════════════════════════════════════╝\n";
        return;
    }

    mostrarFactura(ventas[ventas.size() - 1]);
}
bool guardarVentas(string nombreArchivo) {

    ofstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return false;
    }

    archivo << "idVenta,idPedido,idCliente,subtotal,iva,descuento,propina,total" << endl;

    for (int i = 0; i < ventas.size(); i++) {

        archivo << ventas[i].idVenta << ","
                << ventas[i].idPedido << ","
                << ventas[i].idCliente << ","
                << ventas[i].subtotal << ","
                << ventas[i].iva << ","
                << ventas[i].descuento << ","
                << ventas[i].propina << ","
                << ventas[i].total << endl;
    }

    archivo.close();

    return true;
}
bool cargarVentas(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (archivo.is_open() == false) {
        return false;
    }

    ventas.clear();

    string linea;

    getline(archivo, linea);

    while (getline(archivo, linea)) {

        if (linea == "") {
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

        Venta venta;

        venta.idVenta = stoi(campoIdVenta);
        venta.idPedido = stoi(campoIdPedido);
        venta.idCliente = stoi(campoIdCliente);
        venta.subtotal = stod(campoSubtotal);
        venta.iva = stod(campoIva);
        venta.descuento = stod(campoDescuento);
        venta.propina = stod(campoPropina);
        venta.total = stod(campoTotal);

        ventas.push_back(venta);
    }

    archivo.close();

    return true;
}




