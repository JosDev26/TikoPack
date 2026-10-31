//
// Created by Usuario on 27/10/2026.
//

#include "../Encabezados/ListaClientes.h"
#include "../Encabezados/Cliente.h"
#include <sstream>
using namespace std;


NodoCliente::NodoCliente(Cliente* dato) : dato(dato), siguiente(nullptr) {
}

Cliente* NodoCliente::getDato() {
    return dato;
}

NodoCliente* NodoCliente::getSiguiente() {
    return siguiente;
}

void NodoCliente::setSiguiente(NodoCliente* siguiente) {
    this->siguiente = siguiente;
}

// ===== ListaClientes =====

ListaClientes::ListaClientes() : primero(nullptr), cantidad(0) {
}

// solo borra los nodos
ListaClientes::~ListaClientes() {
    NodoCliente* actual = primero;
    while (actual != nullptr) {
        NodoCliente* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    cantidad = 0;
}

void ListaClientes::insertarFinal(Cliente* cliente) {
    NodoCliente* nuevo = new NodoCliente(cliente);
    if (primero == nullptr) {
        primero = nuevo;
    } else {
        NodoCliente* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

Cliente* ListaClientes::buscar(string identificacion) {
    NodoCliente* actual = primero;
    while (actual != nullptr) {
        Cliente* cliente = actual->getDato();
        if (cliente->getIdentificacion() == identificacion) {
            return cliente;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool ListaClientes::eliminar(Cliente* cliente) {
    NodoCliente* anterior = nullptr;
    NodoCliente* actual = primero;
    while (actual != nullptr && actual->getDato() != cliente) {
        anterior = actual;
        actual = actual->getSiguiente();
    }
    if (actual == nullptr) {
        return false;                         // no estaba en la lista
    }
    if (anterior == nullptr) {
        primero = actual->getSiguiente();     // era el primero
    } else {
        anterior->setSiguiente(actual->getSiguiente());
    }
    delete actual;                            // borra el nodo, no el cliente
    cantidad--;
    return true;
}

NodoCliente* ListaClientes::getPrimero() {
    return primero;
}

int ListaClientes::getCantidad() {
    return cantidad;
}

bool ListaClientes::estaVacia() {
    return primero == nullptr;
}

string ListaClientes::toString() {
    if (estaVacia()) {
        return "No hay clientes registrados.\n";
    }
    stringstream ss;
    NodoCliente* actual = primero;
    while (actual != nullptr) {
        ss << "------------------------------\n";
        ss << actual->getDato()->toString() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}
