//
// Created by Usuario on 27/10/2026.
//

#include "Fecha.h"
#include <sstream>
using namespace std;

Fecha::Fecha() : dia(1), mes(1), anio(2026), hora(0), minuto(0) {
}

Fecha::Fecha(int dia, int mes, int anio, int hora, int minuto) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
    this->hora = hora;
    this->minuto = minuto;
}

int Fecha::getDia() {
    return dia;
}

int Fecha::getMes() {
    return mes;
}

int Fecha::getAnio() {
    return anio;
}

int Fecha::getHora() {
    return hora;
}

int Fecha::getMinuto() {
    return minuto;
}

string Fecha::toString() {
    stringstream ss;
    ss << toStringSinHora() << " ";

    if (hora < 10) {
        ss << "0";
    }
    ss << hora << ":";

    if (minuto < 10) {
        ss << "0";
    }
    ss << minuto;
    return ss.str();
}

string Fecha::toStringSinHora() {
    stringstream ss;
    if (dia < 10) {
        ss << "0";
    }
    ss << dia << "/";

    if (mes < 10) {
        ss << "0";
    }
    ss << mes << "/" << anio;
    return ss.str();
}
