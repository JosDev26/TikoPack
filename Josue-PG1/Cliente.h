//
// Created by Usuario on 27/10/2026.
//

#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
protected:
    std::string identificacion;
    std::string nombre;
    std::string telefono;
    std::string correo;

public:
    Cliente(std::string identificacion, std::string nombre,
            std::string telefono, std::string correo);
    virtual ~Cliente();

    std::string getIdentificacion();
    std::string getNombre();
    std::string getTelefono();
    std::string getCorreo();

    virtual std::string getTipo() = 0;

    virtual double aplicarDescuento(double costoBase);

    virtual std::string toString();
    void mostrar();
};

#endif
