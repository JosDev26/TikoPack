//
// Created by Usuario on 27/10/2026.
//

#ifndef LISTACLIENTES_H
#define LISTACLIENTES_H

#include <string>

class Cliente;

class NodoCliente {
private:
    Cliente* dato;
    NodoCliente* siguiente;

public:
    NodoCliente(Cliente* dato);
    Cliente* getDato();
    NodoCliente* getSiguiente();
    void setSiguiente(NodoCliente* siguiente);
};

class ListaClientes {
private:
    NodoCliente* primero;
    int cantidad;

public:
    ListaClientes();
    ~ListaClientes();

    void insertarFinal(Cliente* cliente);
    Cliente* buscar(std::string identificacion);
    // solo quita el nodo, no hace delete
    bool eliminar(Cliente* cliente);

    NodoCliente* getPrimero();
    int getCantidad();
    bool estaVacia();

    std::string toString();
};

#endif
