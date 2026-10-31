//
// Created by Usuario on 27/10/2026.
//

#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include "../Josue-PG1/Fecha.h"

class Colaborador {
private:
    std::string identificacion;
    std::string nombreCompleto;
    Fecha fechaIngreso;
    std::string puesto;

public:
    Colaborador(std::string identificacion, std::string nombreCompleto,
                Fecha fechaIngreso, std::string puesto);
    ~Colaborador();

    std::string getIdentificacion();
    std::string getNombreCompleto();
    Fecha getFechaIngreso();
    std::string getPuesto();

    std::string toString();
    void mostrar();
};

#endif
