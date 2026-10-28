//
// Created by Usuario on 27/10/2026.
//

#ifndef BODEGA_H
#define BODEGA_H

#include <string>
#include "Celda.h"

class Paquete;

class Bodega {
private:
    std::string codigo;
    std::string nombre;
    int tipo;              // 1 General, 2 Fragil, 3 Tecnologia, 4 Documentos
    int filas;
    int columnas;
    Celda** matriz;

public:
    Bodega(std::string codigo, std::string nombre, int tipo, int filas, int columnas);
    ~Bodega();

    std::string getCodigo();
    std::string getNombre();
    int getTipo();
    std::string getNombreTipo();
    int getFilas();
    int getColumnas();

    bool posicionValida(int f, int c);
    bool estaLibre(int f, int c);
    bool asignar(int f, int c, Paquete* paquete);
    bool liberar(int f, int c);
    Paquete* getPaquete(int f, int c);

    int totalCeldas();
    int celdasOcupadas();
    int celdasLibres();
    double porcentajeOcupacion();
    double porcentajeDisponible();

    bool estaVacia();

    // devuelve false si la bodega esta llena
    bool primeraCeldaLibre(int& f, int& c);

    // ejemplo: A-1-2
    std::string nombreCelda(int f, int c);

    void mostrarMatriz();
    std::string toString();
};

#endif
