    #include "../Encabezados/ListaPaquetes.h"
#include "../Encabezados/Paquete.h"
#include <sstream>
using namespace std;

// ===== NodoPaquete =====

NodoPaquete::NodoPaquete(Paquete* dato) : dato(dato), siguiente(nullptr) {

}

Paquete* NodoPaquete::getDato() {
    return dato;
}

NodoPaquete* NodoPaquete::getSiguiente() {
    return siguiente;
}

void NodoPaquete::setSiguiente(NodoPaquete* siguiente) {
    this->siguiente = siguiente;
}

// ===== ListaPaquetes =====

ListaPaquetes::ListaPaquetes() : primero(nullptr), cantidad(0) {
}

// solo borra los nodos
ListaPaquetes::~ListaPaquetes() {
    NodoPaquete* actual = primero;
    while (actual != nullptr) {
        NodoPaquete* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    cantidad = 0;
}

void ListaPaquetes::insertarFinal(Paquete* Paquete) {
    NodoPaquete* nuevo = new NodoPaquete(Paquete);
    if (primero == nullptr) {
        primero = nuevo;
    } else {
        NodoPaquete* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

Paquete* ListaPaquetes::buscar(string codigo) {
    NodoPaquete* actual = primero;
    while (actual != nullptr) {
        Paquete* Paquete = actual->getDato();
        if (Paquete->getCodigo() == codigo) {
            return Paquete;
        }
        actual = actual->getSiguiente();

    return nullptr;
}
bool ListaPaquetes::colaboradorEnBitacoras(Colaborador* colaborador) {
    if (primero == nullptr) return false;
    NodoPaquete* actual = primero;
    while (actual != nullptr) {
        Colaborador* colaboradorPaquete = actual->getColaborador();
        if (colaboradorPaquete == colaborador) {
            return true;
        }
    }

    return false;
}
bool ListaPaquetes::tieneEnBodega(Bodega* bodega) {
    if (primero == nullptr) return false;
    NodoBodega* actual = primero;
    while (actual != nullptr) {
        Bodega* bodegaPaquete = actual->getCliente();
        if (bodegaPaquete == bodega) {
            return true;
        }
    }

    return false;
}

bool ListaPaquetes::tieneDeCliente(Cliente* cliente) {

    if (primero == nullptr) return false;
    NodoPaquete* actual = primero;
    while (actual != nullptr) {
        Cliente* clientePaquete = actual->getCliente();
        if (clientePaquete == cliente) {
            return true;
        }
    }

    return false;
}
bool ListaPaquetes::eliminar(Paquete* Paquete) {
    NodoPaquete* anterior = nullptr;
    NodoPaquete* actual = primero;
    while (actual != nullptr && actual->getDato() != Paquete) {
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
    delete actual;                            // borra el nodo, no la Paquete
    cantidad--;
    return true;
}

NodoPaquete* ListaPaquetes::getPrimero() {
    return primero;
}

int ListaPaquetes::getCantidad() {
    return cantidad;
}

bool ListaPaquetes::estaVacia() {
    return primero == nullptr;
}

string ListaPaquetes::toString() {
    if (estaVacia()) {
        return "No hay Paquetes registradas.\n";
    }
    stringstream ss;
    NodoPaquete* actual = primero;
    while (actual != nullptr) {
        ss << "------------------------------\n";
        ss << actual->getDato()->toString() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}
