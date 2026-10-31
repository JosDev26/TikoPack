//
// Created by Usuario on 27/10/2026.
//

#ifndef CLIENTEFISICO_H
#define CLIENTEFISICO_H

#include "Cliente.h"

class ClienteFisico : public Cliente {
public:
    ClienteFisico(std::string identificacion, std::string nombre,
                  std::string telefono, std::string correo);
    ~ClienteFisico() override;

    std::string getTipo() override;
};

#endif
