//
// Created by Usuario on 27/10/2026.
//

#ifndef CLIENTEEMPRESA_H
#define CLIENTEEMPRESA_H

#include "Cliente.h"

class ClienteEmpresa : public Cliente {
private:
    std::string actividadEconomica;
    double porcentajeDescuento;

public:
    ClienteEmpresa(std::string identificacion, std::string nombre, std::string telefono,
                   std::string correo, std::string actividadEconomica, double porcentajeDescuento);
    ~ClienteEmpresa() override;

    std::string getActividadEconomica();
    double getPorcentajeDescuento();

    std::string getTipo() override;

    double aplicarDescuento(double costoBase) override;

    std::string toString() override;
};

#endif
