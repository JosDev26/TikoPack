//
// Created by Usuario on 27/10/2026.
//

#ifndef LISTACOLABORADORES_H
#define LISTACOLABORADORES_H

#include <string>

class Colaborador;

class NodoColaborador {
private:
    Colaborador* dato;
    NodoColaborador* siguiente;

public:
    NodoColaborador(Colaborador* dato);
    Colaborador* getDato();
    NodoColaborador* getSiguiente();
    void setSiguiente(NodoColaborador* siguiente);
};

class ListaColaboradores {
private:
    NodoColaborador* primero;
    int cantidad;

public:
    ListaColaboradores();
    ~ListaColaboradores();

    void insertarFinal(Colaborador* colaborador);
    Colaborador* buscar(std::string identificacion);
    // solo quita el nodo, no hace delete
    bool eliminar(Colaborador* colaborador);

    NodoColaborador* getPrimero();
    int getCantidad();
    bool estaVacia();

    std::string toString();
};

#endif
