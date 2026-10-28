//
// Created by Usuario on 27/10/2026.
//

#include "ClienteEmpresa.h"
#include <sstream>
#include <iomanip>
using namespace std;

ClienteEmpresa::ClienteEmpresa(string identificacion, string nombre, string telefono,
                               string correo, string actividadEconomica, double porcentajeDescuento)
    : Cliente(identificacion, nombre, telefono, correo) {
    this->actividadEconomica = actividadEconomica;

    // el descuento debe estar entre 0 y 100
    if (porcentajeDescuento < 0) {
        porcentajeDescuento = 0;
    } else if (porcentajeDescuento > 100) {
        porcentajeDescuento = 100;
    }
    this->porcentajeDescuento = porcentajeDescuento;
}

ClienteEmpresa::~ClienteEmpresa() {
}

string ClienteEmpresa::getActividadEconomica() {
    return actividadEconomica;
}

double ClienteEmpresa::getPorcentajeDescuento() {
    return porcentajeDescuento;
}

string ClienteEmpresa::getTipo() {
    return "Empresa";
}

double ClienteEmpresa::aplicarDescuento(double costoBase) {
    return costoBase - costoBase * porcentajeDescuento / 100;
}

string ClienteEmpresa::toString() {
    stringstream ss;
    ss << Cliente::toString()
       << "\nActividad economica: " << actividadEconomica
       << "\nDescuento: " << fixed << setprecision(2) << porcentajeDescuento << "%";
    return ss.str();
}
