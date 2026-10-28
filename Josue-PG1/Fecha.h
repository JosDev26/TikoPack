//
// Created by Usuario on 27/10/2026.
//

#ifndef FECHA_H
#define FECHA_H

#include <string>

class Fecha {
private:
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;

public:
    Fecha();
    Fecha(int dia, int mes, int anio, int hora = 0, int minuto = 0);

    int getDia();
    int getMes();
    int getAnio();
    int getHora();
    int getMinuto();

    // dd/mm/aaaa hh:mm
    std::string toString();
    // dd/mm/aaaa
    std::string toStringSinHora();
};

#endif
