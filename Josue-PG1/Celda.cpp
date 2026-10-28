//
// Created by Usuario on 27/10/2026.
//

#include "Celda.h"
// TODO Integrante 2: descomentar cuando exista Paquete.h
// #include "Paquete.h"
using namespace std;

Celda::Celda() : paquete(nullptr) {
}

bool Celda::estaLibre() {
    return paquete == nullptr;
}

void Celda::ocupar(Paquete* paquete) {
    this->paquete = paquete;
}

void Celda::liberar() {
    paquete = nullptr;
}

Paquete* Celda::getPaquete() {
    return paquete;
}

string Celda::getCodigoPaquete() {
    if (paquete == nullptr) {
        return "LIBRE";
    }
    // TODO Integrante 2: cuando exista Paquete.h, cambiar la linea de abajo por:
    // return paquete->getCodigo();
    return "OCUPADA";
}
