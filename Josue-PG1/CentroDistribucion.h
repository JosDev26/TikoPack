//
// Created by Usuario on 27/10/2026.
//

#ifndef CENTRODISTRIBUCION_H
#define CENTRODISTRIBUCION_H

#include <string>
#include "ListaClientes.h"
#include "ListaColaboradores.h"
#include "ListaBodegas.h"
// TODO Integrante 2: #include "ListaPaquetes.h"
// TODO Integrante 3: #include "ListaSolicitudes.h" y #include "ListaDespachos.h"

class Cliente;
class Colaborador;
class Bodega;

class CentroDistribucion {
private:
    std::string codigo;
    std::string nombre;
    std::string provincia;
    std::string direccion;
    std::string telefono;

    ListaClientes clientes;
    ListaColaboradores colaboradores;
    ListaBodegas bodegas;
    // TODO Integrante 2: ListaPaquetes paquetes;
    // TODO Integrante 3: ListaSolicitudes solicitudes;
    // TODO Integrante 3: ListaDespachos despachos;

public:
    CentroDistribucion(std::string codigo, std::string nombre, std::string provincia,
                       std::string direccion, std::string telefono);
    ~CentroDistribucion();

    std::string getCodigo();
    std::string getNombre();
    std::string getProvincia();
    std::string getDireccion();
    std::string getTelefono();

    std::string toString();

    bool puedeEliminarse();

    // ============================================
    // PARTE 1 - Integrante 1: clientes, colaboradores y bodegas
    // ============================================
    // Si un agregar devuelve false, el objeto ya fue borrado.

    bool agregarCliente(Cliente* cliente);
    Cliente* buscarCliente(std::string identificacion);
    bool puedeEliminarCliente(Cliente* cliente);
    bool eliminarCliente(Cliente* cliente);
    std::string listarClientes();
    // la usa el Integrante 3 en el reporte de envios
    ListaClientes* getClientes();

    bool agregarColaborador(Colaborador* colaborador);
    Colaborador* buscarColaborador(std::string identificacion);
    bool puedeEliminarColaborador(Colaborador* colaborador);
    bool eliminarColaborador(Colaborador* colaborador);
    std::string listarColaboradores();

    bool agregarBodega(Bodega* bodega);
    Bodega* buscarBodega(std::string codigo);
    bool puedeEliminarBodega(Bodega* bodega);
    bool eliminarBodega(Bodega* bodega);
    std::string listarBodegas();
    ListaBodegas* getBodegas();

    // ============================================
    // PARTE 2 - Integrante 2: paquetes y almacenamiento
    // ============================================
    // TODO Integrante 2: agregarPaquete, buscarPaquete, eliminarPaquete,
    // recomendarBodega, almacenarPaquete, reubicarPaquete, incidencias...

    // ============================================
    // PARTE 3 - Integrante 3: solicitudes y despachos
    // ============================================
    // TODO Integrante 3: crearSolicitud, buscarSolicitud, aprobarSolicitud,
    // rechazarSolicitud, anularSolicitud, buscarDespacho, finalizarDespacho...
};

#endif
