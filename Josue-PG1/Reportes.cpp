//
// Created by Usuario on 27/10/2026.
//

#include "Reportes.h"
#include "CentroDistribucion.h"
#include "Bodega.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Reportes::ocupacionBodegas(CentroDistribucion* centro) {
    if (centro == nullptr) {
        return;
    }

    cout << "\n==========================================\n";
    cout << "        Ocupacion de bodegas\n";
    cout << "==========================================\n";
    cout << "Centro: " << centro->getCodigo() << " - " << centro->getNombre() << endl;

    ListaBodegas* bodegas = centro->getBodegas();
    if (bodegas->estaVacia()) {
        cout << "\nEl centro no tiene bodegas registradas." << endl;
        return;
    }

    int totalCentro = 0;
    int ocupadasCentro = 0;

    NodoBodega* actual = bodegas->getPrimero();
    while (actual != nullptr) {
        Bodega* bodega = actual->getDato();
        cout << "\nBodega " << bodega->getCodigo() << " - " << bodega->getNombre()
             << " (" << bodega->getNombreTipo() << ")" << endl;
        cout << "  Total de celdas: " << bodega->totalCeldas() << endl;
        cout << "  Celdas ocupadas: " << bodega->celdasOcupadas() << endl;
        cout << "  Celdas disponibles: " << bodega->celdasLibres() << endl;
        cout << "  Porcentaje de ocupacion: " << fixed << setprecision(2)
             << bodega->porcentajeOcupacion() << "%" << endl;

        totalCentro = totalCentro + bodega->totalCeldas();
        ocupadasCentro = ocupadasCentro + bodega->celdasOcupadas();
        actual = actual->getSiguiente();
    }

    double porcentajeCentro = 0;
    if (totalCentro > 0) {
        porcentajeCentro = ocupadasCentro * 100.0 / totalCentro;
    }
    cout << "\n------------------------------------------\n";
    cout << "Total del centro" << endl;
    cout << "  Total de celdas: " << totalCentro << endl;
    cout << "  Celdas ocupadas: " << ocupadasCentro << endl;
    cout << "  Celdas disponibles: " << totalCentro - ocupadasCentro << endl;
    cout << "  Porcentaje de ocupacion: " << fixed << setprecision(2) << porcentajeCentro << "%" << endl;
}

// TODO Integrante 2: Reportes::bitacoraPaquete
// TODO Integrante 3: los otros 4 reportes
