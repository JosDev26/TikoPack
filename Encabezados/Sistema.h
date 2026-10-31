//
// Created by Usuario on 27/10/2026.
//

#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "ListaCentros.h"

class CentroDistribucion;

class Sistema {
private:
    ListaCentros centros;

public:
    Sistema();
    ~Sistema();

    // si devuelve false, el centro ya fue borrado
    bool agregarCentro(CentroDistribucion* centro);
    CentroDistribucion* buscarCentro(std::string codigo);
    bool eliminarCentro(CentroDistribucion* centro);
    std::string listarCentros();
    std::string listarCodigosCentros();
    bool tieneCentros();

    // revisan en todos los centros
    bool existePaquete(std::string codigo);
    bool existeSolicitud(std::string codigo);
    bool existeDespacho(std::string codigo);

    void cargarDatosPrueba();
};

#endif
