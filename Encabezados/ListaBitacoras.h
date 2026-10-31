#ifndef LISTABitacoraS_H
#define LISTABitacoraS_H
#include "Bitacora.h"
#include <string>


class  NodoBitacora {

private:
    Bitacora* dato;
    NodoBitacora* siguiente;

public:
    NodoBitacora(Bitacora* dato);
    ~NodoBitacora();
    Bitacora* getDato();
    NodoBitacora* getSiguiente();
    void setSiguiente(NodoBitacora* siguiente);
};

class ListaBitacoras {
private:
    NodoBitacora* primero;
    int cantidad;

public:
    ListaBitacoras();
    ~ListaBitacoras();

    void insertarFinal(Bitacora* Bitacora);
    Bitacora* buscar(std::string codigo);
    // solo quita el nodo, no hace delete
    bool eliminar(Bitacora* Bitacora);

    NodoBitacora* getPrimero();
    int getCantidad();
    bool estaVacia();

    std::string toString();
};

#endif
