//
// Created by Usuario on 27/10/2026.
//

#include "../Encabezados/Cliente.h"
#include <iostream>
#include <sstream>
using namespace std;

Cliente::Cliente(string identificacion, string nombre, string telefono, string correo) {
    this->identificacion = identificacion;
    this->nombre = nombre;
    this->telefono = telefono;
    this->correo = correo;
}

Cliente::~Cliente() {
}

string Cliente::getIdentificacion() {
    return identificacion;
}

string Cliente::getNombre() {
    return nombre;
}

string Cliente::getTelefono() {
    return telefono;
}

string Cliente::getCorreo() {
    return correo;
}

double Cliente::aplicarDescuento(double costoBase) {
    return costoBase;
}

string Cliente::toString() {
    stringstream ss;
    ss << "Tipo: " << getTipo()
       << "\nIdentificacion: " << identificacion
       << "\nNombre: " << nombre
       << "\nTelefono: " << telefono
       << "\nCorreo: " << correo;
    return ss.str();
}

void Cliente::mostrar() {
    cout << toString() << endl;
}
