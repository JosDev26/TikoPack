#ifndef LISTAPaqueteS_H
#define LISTAPaqueteS_H
#include "Paquete.h"
#include <string>


class  NodoPaquete {

private:
    Paquete* dato;
    NodoPaquete* siguiente;

public:
    NodoPaquete(Paquete* dato);
    ~NodoPaquete();
    Paquete* getDato();
    NodoPaquete* getSiguiente();
    void setSiguiente(NodoPaquete* siguiente);
};

class ListaPaquetes {
private:
    NodoPaquete* primero;
    int cantidad;

public:
    ListaPaquetes();
    ~ListaPaquetes();
    bool tieneEnBodega(Bodega* bodega);
    void insertarFinal(Paquete* Paquete);
    Paquete* buscar(std::string codigo);
    // solo quita el nodo, no hace delete
    bool eliminar(Paquete* Paquete);
    bool tieneDeCliente(Cliente* cliente);
    NodoPaquete* getPrimero();
    int getCantidad();
    bool estaVacia();
    bool colaboradorEnBitacoras(Colaborador* colaborador);
    std::string toString();
};

#endif
