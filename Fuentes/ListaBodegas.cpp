#include "../Encabezados/ListaBodegas.h"
#include "../Encabezados/Bodega.h"
#include <sstream>
using namespace std;

// ===== NodoBodega =====

NodoBodega::NodoBodega(Bodega* dato) : dato(dato), siguiente(nullptr) {
}

Bodega* NodoBodega::getDato() {
    return dato;
}

NodoBodega* NodoBodega::getSiguiente() {
    return siguiente;
}

void NodoBodega::setSiguiente(NodoBodega* siguiente) {
    this->siguiente = siguiente;
}

// ===== ListaBodegas =====

ListaBodegas::ListaBodegas() : primero(nullptr), cantidad(0) {
}

// solo borra los nodos
ListaBodegas::~ListaBodegas() {
    NodoBodega* actual = primero;
    while (actual != nullptr) {
        NodoBodega* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    cantidad = 0;
}

void ListaBodegas::insertarFinal(Bodega* bodega) {
    NodoBodega* nuevo = new NodoBodega(bodega);
    if (primero == nullptr) {
        primero = nuevo;
    } else {
        NodoBodega* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

Bodega* ListaBodegas::buscar(string codigo) {
    NodoBodega* actual = primero;
    while (actual != nullptr) {
        Bodega* bodega = actual->getDato();
        if (bodega->getCodigo() == codigo) {
            return bodega;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool ListaBodegas::eliminar(Bodega* bodega) {
    NodoBodega* anterior = nullptr;
    NodoBodega* actual = primero;
    while (actual != nullptr && actual->getDato() != bodega) {
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
    delete actual;                            // borra el nodo, no la bodega
    cantidad--;
    return true;
}

NodoBodega* ListaBodegas::getPrimero() {
    return primero;
}

int ListaBodegas::getCantidad() {
    return cantidad;
}

bool ListaBodegas::estaVacia() {
    return primero == nullptr;
}

string ListaBodegas::toString() {
    if (estaVacia()) {
        return "No hay bodegas registradas.\n";
    }
    stringstream ss;
    NodoBodega* actual = primero;
    while (actual != nullptr) {
        ss << "------------------------------\n";
        ss << actual->getDato()->toString() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}
