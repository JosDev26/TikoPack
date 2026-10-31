//
// Created by Usuario on 27/10/2026.
//

#include "../Encabezados/Colaborador.h"
#include <iostream>
#include <sstream>
using namespace std;

Colaborador::Colaborador(string identificacion, string nombreCompleto,
                         Fecha fechaIngreso, string puesto)
    : identificacion(identificacion), nombreCompleto(nombreCompleto),
      fechaIngreso(fechaIngreso), puesto(puesto) {
}

Colaborador::~Colaborador() {
}

string Colaborador::getIdentificacion() {
    return identificacion;
}

string Colaborador::getNombreCompleto() {
    return nombreCompleto;
}

Fecha Colaborador::getFechaIngreso() {
    return fechaIngreso;
}

string Colaborador::getPuesto() {
    return puesto;
}

string Colaborador::toString() {
    stringstream ss;
    ss << "Identificacion: " << identificacion
       << "\nNombre completo: " << nombreCompleto
       << "\nFecha de ingreso: " << fechaIngreso.toStringSinHora()
       << "\nPuesto: " << puesto;
    return ss.str();
}

void Colaborador::mostrar() {
    cout << toString() << endl;
}
