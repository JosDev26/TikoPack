#include "../Encabezados/ListaBitacoras.h"
#include "../Encabezados/Bitacora.h"
#include <sstream>
using namespace std;

// ===== NodoBitacora =====

NodoBitacora::NodoBitacora(Bitacora* dato) : dato(dato), siguiente(nullptr) {

}

Bitacora* NodoBitacora::getDato() {
    return dato;
}

NodoBitacora* NodoBitacora::getSiguiente() {
    return siguiente;
}

void NodoBitacora::setSiguiente(NodoBitacora* siguiente) {
    this->siguiente = siguiente;
}

// ===== ListaBitacoras =====

ListaBitacoras::ListaBitacoras() : primero(nullptr), cantidad(0) {
}

// solo borra los nodos
ListaBitacoras::~ListaBitacoras() {
    NodoBitacora* actual = primero;
    while (actual != nullptr) {
        NodoBitacora* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    cantidad = 0;
}

void ListaBitacoras::insertarFinal(Bitacora* Bitacora) {
    NodoBitacora* nuevo = new NodoBitacora(Bitacora);
    if (primero == nullptr) {
        primero = nuevo;
    } else {
        NodoBitacora* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

Bitacora* ListaBitacoras::buscar(string codigo) {
    NodoBitacora* actual = primero;
    while (actual != nullptr) {
        Bitacora* Bitacora = actual->getDato();
        if (Bitacora->getCodigo() == codigo) {
            return Bitacora;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool ListaBitacoras::eliminar(Bitacora* Bitacora) {
    NodoBitacora* anterior = nullptr;
    NodoBitacora* actual = primero;
    while (actual != nullptr && actual->getDato() != Bitacora) {
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
    delete actual;                            // borra el nodo, no la Bitacora
    cantidad--;
    return true;
}

NodoBitacora* ListaBitacoras::getPrimero() {
    return primero;
}

int ListaBitacoras::getCantidad() {
    return cantidad;
}

bool ListaBitacoras::estaVacia() {
    return primero == nullptr;
}

string ListaBitacoras::toString() {
    if (estaVacia()) {
        return "No hay Bitacoras registradas.\n";
    }
    stringstream ss;
    NodoBitacora* actual = primero;
    while (actual != nullptr) {
        ss << "------------------------------\n";
        ss << actual->getDato()->toString() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}
