//
// Created by Usuario on 27/10/2026.
//

#ifndef CELDA_H
#define CELDA_H

#include <string>

class Paquete;

class Celda {
private:
    Paquete* paquete;

public:
    Celda();

    bool estaLibre();
    void ocupar(Paquete* paquete);
    void liberar();
    Paquete* getPaquete();

    std::string getCodigoPaquete();
};

#endif
