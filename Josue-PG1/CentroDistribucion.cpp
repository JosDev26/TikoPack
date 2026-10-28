//
// Created by Usuario on 27/10/2026.
//

#include "CentroDistribucion.h"
#include "Cliente.h"
#include "Colaborador.h"
#include "Bodega.h"
#include <iostream>
#include <sstream>
using namespace std;

CentroDistribucion::CentroDistribucion(string codigo, string nombre, string provincia,
                                       string direccion, string telefono) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->provincia = provincia;
    this->direccion = direccion;
    this->telefono = telefono;
}

CentroDistribucion::~CentroDistribucion() {
    // TODO Integrante 3: borrar los despachos y las solicitudes (mismo recorrido de abajo)
    // TODO Integrante 2: borrar los paquetes (mismo recorrido de abajo)

    NodoBodega* actualBodega = bodegas.getPrimero();
    while (actualBodega != nullptr) {
        delete actualBodega->getDato();
        actualBodega = actualBodega->getSiguiente();
    }

    NodoColaborador* actualColaborador = colaboradores.getPrimero();
    while (actualColaborador != nullptr) {
        delete actualColaborador->getDato();
        actualColaborador = actualColaborador->getSiguiente();
    }

    NodoCliente* actualCliente = clientes.getPrimero();
    while (actualCliente != nullptr) {
        delete actualCliente->getDato();
        actualCliente = actualCliente->getSiguiente();
    }
}

string CentroDistribucion::getCodigo() {
    return codigo;
}

string CentroDistribucion::getNombre() {
    return nombre;
}

string CentroDistribucion::getProvincia() {
    return provincia;
}

string CentroDistribucion::getDireccion() {
    return direccion;
}

string CentroDistribucion::getTelefono() {
    return telefono;
}

string CentroDistribucion::toString() {
    stringstream ss;
    ss << "Codigo: " << codigo
       << "\nNombre: " << nombre
       << "\nProvincia: " << provincia
       << "\nDireccion: " << direccion
       << "\nTelefono: " << telefono
       << "\nClientes: " << clientes.getCantidad()
       << " | Colaboradores: " << colaboradores.getCantidad()
       << " | Bodegas: " << bodegas.getCantidad();
    return ss.str();
}

bool CentroDistribucion::puedeEliminarse() {
    if (!clientes.estaVacia()) {
        cout << "Error: el centro tiene clientes registrados." << endl;
        return false;
    }
    if (!colaboradores.estaVacia()) {
        cout << "Error: el centro tiene colaboradores registrados." << endl;
        return false;
    }
    if (!bodegas.estaVacia()) {
        cout << "Error: el centro tiene bodegas registradas." << endl;
        return false;
    }
    // TODO Integrante 2: revisar que paquetes.estaVacia() sea true
    // TODO Integrante 3: revisar que solicitudes.estaVacia() y despachos.estaVacia() sean true
    return true;
}

// ============================================
// PARTE 1 - Integrante 1: clientes, colaboradores y bodegas
// ============================================

// ----- Clientes -----

bool CentroDistribucion::agregarCliente(Cliente* cliente) {
    if (cliente == nullptr) {
        return false;
    }
    // La identificacion del cliente es unica dentro del centro
    if (buscarCliente(cliente->getIdentificacion()) != nullptr) {
        cout << "Error: ya existe un cliente con la identificacion "
             << cliente->getIdentificacion() << " en este centro." << endl;
        delete cliente;          // no se guardo, entonces se borra
        return false;
    }
    clientes.insertarFinal(cliente);
    return true;
}

Cliente* CentroDistribucion::buscarCliente(string identificacion) {
    return clientes.buscar(identificacion);
}

bool CentroDistribucion::puedeEliminarCliente(Cliente* cliente) {
    if (cliente == nullptr) {
        return false;
    }
    // Solo se elimina si no tiene paquetes, solicitudes ni despachos.
    // TODO Integrante 2:
    // if (paquetes.tieneDeCliente(cliente)) {
    //     cout << "Error: el cliente tiene paquetes registrados." << endl;
    //     return false;
    // }
    // TODO Integrante 3: lo mismo con solicitudes.tieneDeCliente(cliente)
    // y despachos.tieneDeCliente(cliente)
    return true;
}

bool CentroDistribucion::eliminarCliente(Cliente* cliente) {
    if (!puedeEliminarCliente(cliente)) {
        return false;
    }
    if (!clientes.eliminar(cliente)) {
        cout << "Error: el cliente no pertenece a este centro." << endl;
        return false;
    }
    delete cliente;
    return true;
}

string CentroDistribucion::listarClientes() {
    return clientes.toString();
}

ListaClientes* CentroDistribucion::getClientes() {
    return &clientes;
}

// ----- Colaboradores -----

bool CentroDistribucion::agregarColaborador(Colaborador* colaborador) {
    if (colaborador == nullptr) {
        return false;
    }
    if (buscarColaborador(colaborador->getIdentificacion()) != nullptr) {
        cout << "Error: ya existe un colaborador con la identificacion "
             << colaborador->getIdentificacion() << " en este centro." << endl;
        delete colaborador;      // no se guardo, entonces se borra
        return false;
    }
    colaboradores.insertarFinal(colaborador);
    return true;
}

Colaborador* CentroDistribucion::buscarColaborador(string identificacion) {
    return colaboradores.buscar(identificacion);
}

bool CentroDistribucion::puedeEliminarColaborador(Colaborador* colaborador) {
    if (colaborador == nullptr) {
        return false;
    }
    // Solo se elimina si no es responsable de nada.
    // TODO Integrante 2:
    // if (paquetes.colaboradorEnBitacoras(colaborador)) {
    //     cout << "Error: el colaborador aparece en la bitacora de un paquete." << endl;
    //     return false;
    // }
    // TODO Integrante 3: lo mismo con solicitudes.tieneDeResponsable(colaborador)
    // y despachos.tieneDeResponsable(colaborador)
    return true;
}

bool CentroDistribucion::eliminarColaborador(Colaborador* colaborador) {
    if (!puedeEliminarColaborador(colaborador)) {
        return false;
    }
    if (!colaboradores.eliminar(colaborador)) {
        cout << "Error: el colaborador no pertenece a este centro." << endl;
        return false;
    }
    delete colaborador;
    return true;
}

string CentroDistribucion::listarColaboradores() {
    return colaboradores.toString();
}

// ----- Bodegas -----

bool CentroDistribucion::agregarBodega(Bodega* bodega) {
    if (bodega == nullptr) {
        return false;
    }
    // El codigo de la bodega es unico dentro del centro
    if (buscarBodega(bodega->getCodigo()) != nullptr) {
        cout << "Error: ya existe una bodega con el codigo "
             << bodega->getCodigo() << " en este centro." << endl;
        delete bodega;           // no se guardo, entonces se borra
        return false;
    }
    bodegas.insertarFinal(bodega);
    return true;
}

Bodega* CentroDistribucion::buscarBodega(string codigo) {
    return bodegas.buscar(codigo);
}

bool CentroDistribucion::puedeEliminarBodega(Bodega* bodega) {
    if (bodega == nullptr) {
        return false;
    }
    if (!bodega->estaVacia()) {
        cout << "Error: la bodega tiene celdas ocupadas." << endl;
        return false;
    }
    // TODO Integrante 2:
    // if (paquetes.tieneEnBodega(bodega)) {
    //     cout << "Error: hay paquetes que tienen asignada esta bodega." << endl;
    //     return false;
    // }
    return true;
}

bool CentroDistribucion::eliminarBodega(Bodega* bodega) {
    if (!puedeEliminarBodega(bodega)) {
        return false;
    }
    if (!bodegas.eliminar(bodega)) {
        cout << "Error: la bodega no pertenece a este centro." << endl;
        return false;
    }
    delete bodega;
    return true;
}

string CentroDistribucion::listarBodegas() {
    return bodegas.toString();
}

ListaBodegas* CentroDistribucion::getBodegas() {
    return &bodegas;
}

// ============================================
// PARTE 2 - Integrante 2: paquetes y almacenamiento
// ============================================
// TODO Integrante 2: escribir aqui sus metodos.

// ============================================
// PARTE 3 - Integrante 3: solicitudes y despachos
// ============================================
// TODO Integrante 3: escribir aqui sus metodos.
