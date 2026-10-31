//
// Created by Usuario on 27/10/2026.
//

#include "../Encabezados/Sistema.h"
#include "../Encabezados/CentroDistribucion.h"
#include "../Encabezados/ClienteFisico.h"
#include "../Encabezados/ClienteEmpresa.h"
#include "../Encabezados/Colaborador.h"
#include "../Encabezados/Bodega.h"
#include "../Encabezados/Fecha.h"
#include <iostream>
#include <sstream>
using namespace std;

Sistema::Sistema() {
}

Sistema::~Sistema() {
    NodoCentro* actual = centros.getPrimero();
    while (actual != nullptr) {
        delete actual->getDato();
        actual = actual->getSiguiente();
    }
}

bool Sistema::agregarCentro(CentroDistribucion* centro) {
    if (centro == nullptr) {
        return false;
    }
    // El codigo del centro es unico en todo el sistema
    if (buscarCentro(centro->getCodigo()) != nullptr) {
        cout << "Error: ya existe un centro con el codigo " << centro->getCodigo() << "." << endl;
        delete centro;           // no se guardo, entonces se borra
        return false;
    }
    centros.insertarFinal(centro);
    return true;
}

CentroDistribucion* Sistema::buscarCentro(string codigo) {
    return centros.buscar(codigo);
}

bool Sistema::eliminarCentro(CentroDistribucion* centro) {
    if (centro == nullptr) {
        return false;
    }
    if (!centro->puedeEliminarse()) {
        return false;
    }
    if (!centros.eliminar(centro)) {
        cout << "Error: el centro no esta registrado en el sistema." << endl;
        return false;
    }
    delete centro;
    return true;
}

string Sistema::listarCentros() {
    return centros.toString();
}

string Sistema::listarCodigosCentros() {
    stringstream ss;
    NodoCentro* actual = centros.getPrimero();
    while (actual != nullptr) {
        CentroDistribucion* centro = actual->getDato();
        ss << "  " << centro->getCodigo() << " - " << centro->getNombre() << "\n";
        actual = actual->getSiguiente();
    }
    return ss.str();
}

bool Sistema::tieneCentros() {
    return !centros.estaVacia();
}

bool Sistema::existePaquete(string codigo) {
    NodoCentro* actual = centros.getPrimero();
    while (actual != nullptr) {
        // TODO Integrante 2: descomentar cuando exista CentroDistribucion::buscarPaquete
        // if (actual->getDato()->buscarPaquete(codigo) != nullptr) {
        //     return true;
        // }
        actual = actual->getSiguiente();
    }
    return false;
}

bool Sistema::existeSolicitud(string codigo) {
    NodoCentro* actual = centros.getPrimero();
    while (actual != nullptr) {
        // TODO Integrante 3: descomentar cuando exista CentroDistribucion::buscarSolicitud
        // if (actual->getDato()->buscarSolicitud(codigo) != nullptr) {
        //     return true;
        // }
        actual = actual->getSiguiente();
    }
    return false;
}

bool Sistema::existeDespacho(string codigo) {
    NodoCentro* actual = centros.getPrimero();
    while (actual != nullptr) {
        // TODO Integrante 3: descomentar cuando exista CentroDistribucion::buscarDespacho
        // if (actual->getDato()->buscarDespacho(codigo) != nullptr) {
        //     return true;
        // }
        actual = actual->getSiguiente();
    }
    return false;
}

void Sistema::cargarDatosPrueba() {
    // si ya se cargaron, no se cargan otra vez
    if (buscarCentro("C01") != nullptr) {
        return;
    }

    // ===== Datos de prueba - Integrante 1 (centros, clientes, colaboradores y bodegas) =====

    CentroDistribucion* sanJose = new CentroDistribucion("C01", "Centro San Jose", "San Jose",
                                                         "Paseo Colon, 200 m norte del hospital", "22223333");
    CentroDistribucion* alajuela = new CentroDistribucion("C02", "Centro Alajuela", "Alajuela",
                                                          "Frente al parque central", "24445555");
    // centro vacio para probar eliminar centro
    CentroDistribucion* limon = new CentroDistribucion("C03", "Centro Limon", "Limon",
                                                       "Barrio Roosevelt, contiguo a la escuela", "27586666");
    agregarCentro(sanJose);
    agregarCentro(alajuela);
    agregarCentro(limon);

    // Bodegas
    sanJose->agregarBodega(new Bodega("A", "Bodega principal", 1, 4, 5));
    sanJose->agregarBodega(new Bodega("B", "Bodega de fragiles", 2, 3, 4));
    alajuela->agregarBodega(new Bodega("A", "Bodega de tecnologia", 3, 3, 3));
    alajuela->agregarBodega(new Bodega("B", "Bodega de documentos", 4, 2, 5));

    // Clientes
    sanJose->agregarCliente(new ClienteFisico("1-1111-1111", "Ana Mora Solis",
                                              "88881111", "ana.mora@correo.com"));
    sanJose->agregarCliente(new ClienteFisico("2-2222-2222", "Luis Vargas Rojas",
                                              "88882222", "luis.vargas@correo.com"));
    sanJose->agregarCliente(new ClienteEmpresa("3-101-123456", "Tecnologia Tica S.A.", "22334455",
                                               "ventas@tecnotica.com", "Venta de equipo electronico", 15));
    alajuela->agregarCliente(new ClienteFisico("1-3333-3333", "Maria Jimenez Castro",
                                               "88883333", "maria.jimenez@correo.com"));
    alajuela->agregarCliente(new ClienteEmpresa("3-101-654321", "Libreria El Saber S.A.", "24456677",
                                                "info@elsaber.com", "Venta de libros", 10));

    // Colaboradores
    sanJose->agregarColaborador(new Colaborador("COL01", "Carlos Mendez Arias",
                                                Fecha(15, 3, 2022), "Bodeguero"));
    sanJose->agregarColaborador(new Colaborador("COL02", "Sofia Ramirez Leon",
                                                Fecha(1, 8, 2023), "Supervisora"));
    alajuela->agregarColaborador(new Colaborador("COL01", "Jorge Castillo Brenes",
                                                 Fecha(10, 1, 2024), "Encargado de despachos"));
    alajuela->agregarColaborador(new Colaborador("COL02", "Daniela Rojas Quiros",
                                                 Fecha(5, 6, 2025), "Bodeguera"));

    // ===== Datos de prueba - Integrante 2 (paquetes) =====
    // TODO Integrante 2: registrar paquetes en todos los estados usando las
    // operaciones del centro (almacenarPaquete, incidencias...), no cambiando estados a mano.

    // ===== Datos de prueba - Integrante 3 (solicitudes y despachos) =====
    // TODO Integrante 3: crear solicitudes en distintos estados y algunos despachos
    // (unos finalizados y otros en proceso) usando las operaciones del centro.
}
