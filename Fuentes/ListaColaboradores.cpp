//
// Created by Usuario on 27/10/2026.
//

#include "../Encabezados/ListaColaboradores.h"
#include "../Encabezados/Colaborador.h"
#include <sstream>
using namespace std;

// ===== NodoColaborador =====

NodoColaborador::NodoColaborador(Colaborador* dato) : dato(dato), siguiente(nullptr) {
}

Colaborador* NodoColaborador::getDato() {
    return dato;
}

NodoColaborador* NodoColaborador::getSiguiente() {
    return siguiente;
}

void NodoColaborador::setSiguiente(NodoColaborador* siguiente) {
    this->siguiente = siguiente;
}

// ===== ListaColaboradores =====

ListaColaboradores::ListaColaboradores() : primero(nullptr), cantidad(0) {
}

// solo borra los nodos
ListaColaboradores::~ListaColaboradores() {
    NodoColaborador* actual = primero;
    while (actual != nullptr) {
        NodoColaborador* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    cantidad = 0;
}

void ListaColaboradores::insertarFinal(Colaborador* colaborador) {
    NodoColaborador* nuevo = new NodoColaborador(colaborador);
    if (primero == nullptr) {
        primero = nuevo;
    } else {
        NodoColaborador* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

Colaborador* ListaColaboradores::buscar(string identificacion) {
    NodoColaborador* actual = primero;
    while (actual != nullptr) {
        Colaborador* colaborador = actual->getDato();
        if (colaborador->getIdentificacion() == identificacion) {
            return colaborador;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool ListaColaboradores::eliminar(Colaborador* colaborador) {
    NodoColaborador* anterior = nullptr;
    NodoColaborador* actual = primero;
    while (actual != nullptr && actual->getDato() != colaborador) {
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
    delete actual;                            // borra el nodo, no el colaborador
    cantidad--;
    return true;
}

NodoColaborador* ListaColaboradores::getPrimero() {
    return primero;
}

int ListaColaboradores::getCantidad() {
    return cantidad;
}

bool ListaColaboradores::estaVacia() {
    return primero == nullptr;
}

string ListaColaboradores::toString() {
    if (estaVacia()) {
        return "No hay colaboradores registrados.\n";
    }
    stringstream ss;
    NodoColaborador* actual = primero;
    while (actual != nullptr) {
        ss << "------------------------------\n";
        ss << actual->getDato()->toString() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}
