//
// Created by Usuario on 27/10/2026.
//

#ifndef LISTACENTROS_H
#define LISTACENTROS_H

#include <string>

class CentroDistribucion;

class NodoCentro {
private:
    CentroDistribucion* dato;
    NodoCentro* siguiente;

public:
    NodoCentro(CentroDistribucion* dato);
    CentroDistribucion* getDato();
    NodoCentro* getSiguiente();
    void setSiguiente(NodoCentro* siguiente);
};

class ListaCentros {
private:
    NodoCentro* primero;
    int cantidad;

public:
    ListaCentros();
    ~ListaCentros();

    void insertarFinal(CentroDistribucion* centro);
    CentroDistribucion* buscar(std::string codigo);
    // solo quita el nodo, no hace delete
    bool eliminar(CentroDistribucion* centro);

    NodoCentro* getPrimero();
    int getCantidad();
    bool estaVacia();

    std::string toString();
};

#endif
