//
// Created by Usuario on 27/10/2026.
//

#include "../Encabezados/Bodega.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Bodega::Bodega(string codigo, string nombre, int tipo, int filas, int columnas) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->tipo = tipo;

    if (filas <= 0 || columnas <= 0) {
        filas = 0;
        columnas = 0;
    }
    this->filas = filas;
    this->columnas = columnas;

    // arreglo de punteros (uno por fila)
    matriz = new Celda*[this->filas];
    // cada fila con sus celdas
    for (int i = 0; i < this->filas; i++) {
        matriz[i] = new Celda[this->columnas];
    }
}

Bodega::~Bodega() {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    matriz = nullptr;
}

string Bodega::getCodigo() {
    return codigo;
}

string Bodega::getNombre() {
    return nombre;
}

int Bodega::getTipo() {
    return tipo;
}

string Bodega::getNombreTipo() {
    if (tipo == 1) {
        return "General";
    } else if (tipo == 2) {
        return "Fragil";
    } else if (tipo == 3) {
        return "Tecnologia";
    } else if (tipo == 4) {
        return "Documentos";
    }
    return "Desconocido";
}

int Bodega::getFilas() {
    return filas;
}

int Bodega::getColumnas() {
    return columnas;
}

bool Bodega::posicionValida(int f, int c) {
    return f >= 0 && f < filas && c >= 0 && c < columnas;
}

bool Bodega::estaLibre(int f, int c) {
    if (!posicionValida(f, c)) {
        return false;
    }
    return matriz[f][c].estaLibre();
}

bool Bodega::asignar(int f, int c, Paquete* paquete) {
    if (!posicionValida(f, c)) {
        cout << "Error: la posicion " << f << "-" << c << " no existe en la bodega "
             << codigo << "." << endl;
        return false;
    }
    if (paquete == nullptr) {
        cout << "Error: no hay un paquete para asignar." << endl;
        return false;
    }
    if (!matriz[f][c].estaLibre()) {
        cout << "Error: la celda " << nombreCelda(f, c) << " ya esta ocupada." << endl;
        return false;
    }
    matriz[f][c].ocupar(paquete);
    return true;
}

bool Bodega::liberar(int f, int c) {
    if (!posicionValida(f, c)) {
        cout << "Error: la posicion " << f << "-" << c << " no existe en la bodega "
             << codigo << "." << endl;
        return false;
    }
    if (matriz[f][c].estaLibre()) {
        cout << "Error: la celda " << nombreCelda(f, c) << " ya estaba libre." << endl;
        return false;
    }
    matriz[f][c].liberar();
    return true;
}

Paquete* Bodega::getPaquete(int f, int c) {
    if (!posicionValida(f, c)) {
        return nullptr;
    }
    return matriz[f][c].getPaquete();
}

int Bodega::totalCeldas() {
    return filas * columnas;
}

int Bodega::celdasOcupadas() {
    int ocupadas = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (!matriz[i][j].estaLibre()) {
                ocupadas++;
            }
        }
    }
    return ocupadas;
}

int Bodega::celdasLibres() {
    return totalCeldas() - celdasOcupadas();
}

double Bodega::porcentajeOcupacion() {
    if (totalCeldas() == 0) {
        return 0;                 // evita dividir entre 0
    }
    return celdasOcupadas() * 100.0 / totalCeldas();
}

double Bodega::porcentajeDisponible() {
    if (totalCeldas() == 0) {
        return 0;
    }
    return celdasLibres() * 100.0 / totalCeldas();
}

bool Bodega::estaVacia() {
    return celdasOcupadas() == 0;
}

bool Bodega::primeraCeldaLibre(int& f, int& c) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j].estaLibre()) {
                f = i;
                c = j;
                return true;
            }
        }
    }
    return false;                 // la bodega esta llena
}

string Bodega::nombreCelda(int f, int c) {
    stringstream ss;
    ss << codigo << "-" << f << "-" << c;
    return ss.str();
}

void Bodega::mostrarMatriz() {
    cout << "Bodega " << codigo << " - " << nombre << " - " << getNombreTipo()
         << " (" << filas << " x " << columnas << ")" << endl << endl;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << nombreCelda(i, j) << "\t";
        }
        cout << endl;
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j].getCodigoPaquete() << "\t";
        }
        cout << endl << endl;
    }

    cout << "Ocupadas: " << celdasOcupadas() << "/" << totalCeldas()
         << " (" << fixed << setprecision(2) << porcentajeOcupacion() << "%)" << endl;
}

string Bodega::toString() {
    stringstream ss;
    ss << "Codigo: " << codigo
       << "\nNombre: " << nombre
       << "\nTipo: " << getNombreTipo()
       << "\nTamano: " << filas << " filas x " << columnas << " columnas"
       << "\nCeldas ocupadas: " << celdasOcupadas() << "/" << totalCeldas();
    return ss.str();
}
