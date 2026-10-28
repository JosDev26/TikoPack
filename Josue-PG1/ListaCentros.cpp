//
// Created by Usuario on 27/10/2026.
//

#include "ListaCentros.h"
#include "CentroDistribucion.h"
#include <sstream>
using namespace std;

// ===== NodoCentro =====

NodoCentro::NodoCentro(CentroDistribucion* dato) : dato(dato), siguiente(nullptr) {
}

CentroDistribucion* NodoCentro::getDato() {
    return dato;
}

NodoCentro* NodoCentro::getSiguiente() {
    return siguiente;
}

void NodoCentro::setSiguiente(NodoCentro* siguiente) {
    this->siguiente = siguiente;
}

// ===== ListaCentros =====

ListaCentros::ListaCentros() : primero(nullptr), cantidad(0) {
}

// solo borra los nodos
ListaCentros::~ListaCentros() {
    NodoCentro* actual = primero;
    while (actual != nullptr) {
        NodoCentro* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    cantidad = 0;
}

void ListaCentros::insertarFinal(CentroDistribucion* centro) {
    NodoCentro* nuevo = new NodoCentro(centro);
    if (primero == nullptr) {
        primero = nuevo;
    } else {
        NodoCentro* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

CentroDistribucion* ListaCentros::buscar(string codigo) {
    NodoCentro* actual = primero;
    while (actual != nullptr) {
        CentroDistribucion* centro = actual->getDato();
        if (centro->getCodigo() == codigo) {
            return centro;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool ListaCentros::eliminar(CentroDistribucion* centro) {
    NodoCentro* anterior = nullptr;
    NodoCentro* actual = primero;
    while (actual != nullptr && actual->getDato() != centro) {
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
    delete actual;                            // borra el nodo, no el centro
    cantidad--;
    return true;
}

NodoCentro* ListaCentros::getPrimero() {
    return primero;
}

int ListaCentros::getCantidad() {
    return cantidad;
}

bool ListaCentros::estaVacia() {
    return primero == nullptr;
}

string ListaCentros::toString() {
    if (estaVacia()) {
        return "No hay centros de distribucion registrados.\n";
    }
    stringstream ss;
    NodoCentro* actual = primero;
    while (actual != nullptr) {
        ss << "------------------------------\n";
        ss << actual->getDato()->toString() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}
