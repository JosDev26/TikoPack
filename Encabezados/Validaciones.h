//
// Created by Usuario on 27/10/2026.
//

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include "Fecha.h"

class Validaciones {
public:
    static std::string quitarEspacios(std::string texto);

    static int leerEntero(std::string mensaje, int minimo, int maximo);

    // acepta coma decimal (1,5)
    static double leerDouble(std::string mensaje, double minimo);

    static double leerDoubleRango(std::string mensaje, double minimo, double maximo);

    static std::string leerTexto(std::string mensaje, int maximo = 100);

    static std::string leerTelefono(std::string mensaje);

    static std::string leerCorreo(std::string mensaje);

    static Fecha leerFecha(std::string mensaje);

    static Fecha leerFechaSinHora(std::string mensaje);

    static bool confirmar(std::string pregunta);

    static int diasDelMes(int mes, int anio);
};

#endif
