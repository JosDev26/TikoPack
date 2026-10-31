//
// Created by Usuario on 27/10/2026.
//

#ifndef LISTABODEGAS_H
#define LISTABODEGAS_H

#include <string>

class Bodega;

class NodoBodega {
private:
    Bodega* dato;
    NodoBodega* siguiente;

public:
    NodoBodega(Bodega* dato);
    Bodega* getDato();
    NodoBodega* getSiguiente();
    void setSiguiente(NodoBodega* siguiente);
};

class ListaBodegas {
private:
    NodoBodega* primero;
    int cantidad;

public:
    ListaBodegas();
    ~ListaBodegas();

    void insertarFinal(Bodega* bodega);
    Bodega* buscar(std::string codigo);
    // solo quita el nodo, no hace delete
    bool eliminar(Bodega* bodega);

    NodoBodega* getPrimero();
    int getCantidad();
    bool estaVacia();

    std::string toString();
};

#endif
