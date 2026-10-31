//
// Created by Usuario on 27/10/2026.
//

#include "../Encabezados/Menu.h"
#include "../Encabezados/Sistema.h"
#include "../Encabezados/CentroDistribucion.h"
#include "../Encabezados/ClienteFisico.h"
#include "../Encabezados/ClienteEmpresa.h"
#include "../Encabezados/Colaborador.h"
#include "../Encabezados/Bodega.h"
#include "../Encabezados/Fecha.h"
#include "../Encabezados/Validaciones.h"
#include "../Encabezados/Reportes.h"
#include <iostream>
#include <cstdlib>
using namespace std;

const int MAXIMO_FILAS = 30;
const int MAXIMO_COLUMNAS = 10;

Menu::Menu(Sistema* sistema) {
    this->sistema = sistema;
}

void Menu::limpiarPantalla() {
    system("cls");
}

void Menu::pausar() {
    string linea;
    cout << "\nPresione Enter para continuar...";
    getline(cin, linea);
}

CentroDistribucion* Menu::pedirCentro() {
    if (!sistema->tieneCentros()) {
        cout << "Error: no hay centros de distribucion registrados." << endl;
        return nullptr;
    }
    cout << "Centros disponibles:\n" << sistema->listarCodigosCentros();
    string codigo = Validaciones::leerTexto("Codigo del centro (ejemplo C01): ", 20);
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == nullptr) {
        cout << "Error: no existe un centro con el codigo " << codigo << "." << endl;
    }
    return centro;
}

int Menu::pedirTipoBodega() {
    cout << "Tipos de bodega:" << endl;
    cout << "1. General   2. Fragil   3. Tecnologia   4. Documentos" << endl;
    return Validaciones::leerEntero("Seleccione el tipo (1-4): ", 1, 4);
}

string Menu::pedirProvincia() {
    string provincias[7] = {"San Jose", "Alajuela", "Cartago", "Heredia",
                            "Guanacaste", "Puntarenas", "Limon"};
    cout << "Provincias:" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "  " << i + 1 << ". " << provincias[i] << endl;
    }
    int opcion = Validaciones::leerEntero("Seleccione la provincia (1-7): ", 1, 7);
    return provincias[opcion - 1];
}

void Menu::ejecutar() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "===== TICOPACK LOGISTICS - MENU PRINCIPAL =====" << endl;
        cout << "1. Centros de distribucion" << endl;
        cout << "2. Clientes" << endl;
        cout << "3. Colaboradores" << endl;
        cout << "4. Bodegas y matrices" << endl;
        cout << "5. Paquetes" << endl;
        cout << "6. Solicitudes de envio" << endl;
        cout << "7. Despachos" << endl;
        cout << "8. Reportes" << endl;
        cout << "0. Salir" << endl;
        opcion = Validaciones::leerEntero("Seleccione una opcion: ", 0, 8);

        switch (opcion) {
            case 1:
                menuCentros();
                break;
            case 2:
                menuClientes();
                break;
            case 3:
                menuColaboradores();
                break;
            case 4:
                menuBodegas();
                break;
            case 5:
                // TODO Integrante 2: cambiar estas dos lineas por menuPaquetes();
                cout << "\nEl modulo de paquetes todavia no esta disponible." << endl;
                pausar();
                break;
            case 6:
                // TODO Integrante 3: cambiar estas dos lineas por menuSolicitudes();
                cout << "\nEl modulo de solicitudes todavia no esta disponible." << endl;
                pausar();
                break;
            case 7:
                // TODO Integrante 3: cambiar estas dos lineas por menuDespachos();
                cout << "\nEl modulo de despachos todavia no esta disponible." << endl;
                pausar();
                break;
            case 8:
                menuReportes();
                break;
            case 0:
                cout << "\nGracias por usar TicoPack. Saliendo del programa..." << endl;
                break;
        }
    } while (opcion != 0);
}

// ============================================
// Integrante 1: centros de distribucion
// ============================================

void Menu::menuCentros() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "===== MENU DE CENTROS DE DISTRIBUCION =====" << endl;
        cout << "1. Registrar centro" << endl;
        cout << "2. Buscar centro" << endl;
        cout << "3. Mostrar centros" << endl;
        cout << "4. Eliminar centro" << endl;
        cout << "0. Volver" << endl;
        opcion = Validaciones::leerEntero("Seleccione una opcion: ", 0, 4);

        switch (opcion) {
            case 1:
                registrarCentro();
                break;
            case 2:
                buscarCentro();
                break;
            case 3:
                mostrarCentros();
                break;
            case 4:
                eliminarCentro();
                break;
        }
        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);
}

void Menu::registrarCentro() {
    cout << "\n--- Registrar centro de distribucion ---\n\n";

    string codigo = Validaciones::leerTexto("Codigo del centro (ejemplo C01): ", 20);
    if (sistema->buscarCentro(codigo) != nullptr) {
        cout << "Error: ya existe un centro con el codigo " << codigo << "." << endl;
        return;
    }
    string nombre = Validaciones::leerTexto("Nombre: ", 60);
    string provincia = pedirProvincia();
    string direccion = Validaciones::leerTexto("Direccion: ", 100);
    string telefono = Validaciones::leerTelefono("Telefono: ");

    CentroDistribucion* centro = new CentroDistribucion(codigo, nombre, provincia, direccion, telefono);
    cout << "\n--- Resumen del centro ---\n" << centro->toString() << endl;

    if (!Validaciones::confirmar("\nConfirma el registro del centro?")) {
        delete centro;
        cout << "\nRegistro cancelado por el usuario." << endl;
        return;
    }
    if (sistema->agregarCentro(centro)) {
        cout << "\nCentro registrado correctamente." << endl;
    }
}

void Menu::buscarCentro() {
    cout << "\n--- Buscar centro de distribucion ---\n\n";
    string codigo = Validaciones::leerTexto("Codigo del centro (ejemplo C01): ", 20);
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == nullptr) {
        cout << "Error: no existe un centro con el codigo " << codigo << "." << endl;
    } else {
        cout << "\n" << centro->toString() << endl;
    }
}

void Menu::mostrarCentros() {
    cout << "\n--- Centros de distribucion ---\n";
    cout << sistema->listarCentros();
}

void Menu::eliminarCentro() {
    cout << "\n--- Eliminar centro de distribucion ---\n\n";
    string codigo = Validaciones::leerTexto("Codigo del centro (ejemplo C01): ", 20);
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == nullptr) {
        cout << "Error: no existe un centro con el codigo " << codigo << "." << endl;
        return;
    }
    if (!centro->puedeEliminarse()) {
        return;
    }
    cout << "\n" << centro->toString() << endl;
    if (!Validaciones::confirmar("\nConfirma la eliminacion del centro?")) {
        cout << "\nEliminacion cancelada por el usuario." << endl;
        return;
    }
    if (sistema->eliminarCentro(centro)) {
        cout << "\nCentro eliminado correctamente." << endl;
    }
}

// ============================================
// Integrante 1: clientes
// ============================================

void Menu::menuClientes() {
    limpiarPantalla();
    cout << "===== MENU DE CLIENTES =====" << endl;
    CentroDistribucion* centro = pedirCentro();
    if (centro == nullptr) {
        pausar();
        return;
    }

    int opcion;
    do {
        limpiarPantalla();
        cout << "===== MENU DE CLIENTES =====" << endl;
        cout << "Centro: " << centro->getCodigo() << " - " << centro->getNombre() << endl;
        cout << "1. Registrar cliente" << endl;
        cout << "2. Buscar cliente" << endl;
        cout << "3. Mostrar clientes" << endl;
        cout << "4. Eliminar cliente" << endl;
        cout << "0. Volver" << endl;
        opcion = Validaciones::leerEntero("Seleccione una opcion: ", 0, 4);

        switch (opcion) {
            case 1:
                registrarCliente(centro);
                break;
            case 2:
                buscarCliente(centro);
                break;
            case 3:
                mostrarClientes(centro);
                break;
            case 4:
                eliminarCliente(centro);
                break;
        }
        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);
}

void Menu::registrarCliente(CentroDistribucion* centro) {
    cout << "\n--- Registrar cliente ---\n\n";
    cout << "Tipos de cliente: 1. Persona fisica   2. Empresa" << endl;
    int tipo = Validaciones::leerEntero("Seleccione el tipo (1-2): ", 1, 2);

    string identificacion = Validaciones::leerTexto("Identificacion (ejemplo 1-1111-1111): ", 30);
    if (centro->buscarCliente(identificacion) != nullptr) {
        cout << "Error: ya existe un cliente con la identificacion " << identificacion
             << " en este centro." << endl;
        return;
    }
    string nombre = Validaciones::leerTexto("Nombre: ", 60);
    string telefono = Validaciones::leerTelefono("Telefono: ");
    string correo = Validaciones::leerCorreo("Correo electronico: ");

    Cliente* cliente = nullptr;
    if (tipo == 1) {
        cliente = new ClienteFisico(identificacion, nombre, telefono, correo);
    } else {
        string actividad = Validaciones::leerTexto("Actividad economica: ", 60);
        double descuento = Validaciones::leerDoubleRango("Porcentaje de descuento (0 a 100): ", 0, 100);
        cliente = new ClienteEmpresa(identificacion, nombre, telefono, correo, actividad, descuento);
    }

    cout << "\n--- Resumen del cliente ---\n" << cliente->toString() << endl;
    if (!Validaciones::confirmar("\nConfirma el registro del cliente?")) {
        delete cliente;
        cout << "\nRegistro cancelado por el usuario." << endl;
        return;
    }
    if (centro->agregarCliente(cliente)) {
        cout << "\nCliente registrado correctamente." << endl;
    }
}

void Menu::buscarCliente(CentroDistribucion* centro) {
    cout << "\n--- Buscar cliente ---\n\n";
    string identificacion = Validaciones::leerTexto("Identificacion del cliente: ", 30);
    Cliente* cliente = centro->buscarCliente(identificacion);
    if (cliente == nullptr) {
        cout << "Error: no existe un cliente con esa identificacion en este centro." << endl;
    } else {
        cout << "\n" << cliente->toString() << endl;
    }
}

void Menu::mostrarClientes(CentroDistribucion* centro) {
    cout << "\n--- Clientes del centro " << centro->getCodigo() << " ---\n";
    cout << centro->listarClientes();
}

void Menu::eliminarCliente(CentroDistribucion* centro) {
    cout << "\n--- Eliminar cliente ---\n\n";
    string identificacion = Validaciones::leerTexto("Identificacion del cliente: ", 30);
    Cliente* cliente = centro->buscarCliente(identificacion);
    if (cliente == nullptr) {
        cout << "Error: no existe un cliente con esa identificacion en este centro." << endl;
        return;
    }
    if (!centro->puedeEliminarCliente(cliente)) {
        return;
    }
    cout << "\n" << cliente->toString() << endl;
    if (!Validaciones::confirmar("\nConfirma la eliminacion del cliente?")) {
        cout << "\nEliminacion cancelada por el usuario." << endl;
        return;
    }
    if (centro->eliminarCliente(cliente)) {
        cout << "\nCliente eliminado correctamente." << endl;
    }
}

// ============================================
// Integrante 1: colaboradores
// ============================================

void Menu::menuColaboradores() {
    limpiarPantalla();
    cout << "===== MENU DE COLABORADORES =====" << endl;
    CentroDistribucion* centro = pedirCentro();
    if (centro == nullptr) {
        pausar();
        return;
    }

    int opcion;
    do {
        limpiarPantalla();
        cout << "===== MENU DE COLABORADORES =====" << endl;
        cout << "Centro: " << centro->getCodigo() << " - " << centro->getNombre() << endl;
        cout << "1. Registrar colaborador" << endl;
        cout << "2. Buscar colaborador" << endl;
        cout << "3. Mostrar colaboradores" << endl;
        cout << "4. Eliminar colaborador" << endl;
        cout << "0. Volver" << endl;
        opcion = Validaciones::leerEntero("Seleccione una opcion: ", 0, 4);

        switch (opcion) {
            case 1:
                registrarColaborador(centro);
                break;
            case 2:
                buscarColaborador(centro);
                break;
            case 3:
                mostrarColaboradores(centro);
                break;
            case 4:
                eliminarColaborador(centro);
                break;
        }
        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);
}

void Menu::registrarColaborador(CentroDistribucion* centro) {
    cout << "\n--- Registrar colaborador ---\n\n";
    string identificacion = Validaciones::leerTexto("Identificacion (ejemplo COL01): ", 30);
    if (centro->buscarColaborador(identificacion) != nullptr) {
        cout << "Error: ya existe un colaborador con la identificacion " << identificacion
             << " en este centro." << endl;
        return;
    }
    string nombreCompleto = Validaciones::leerTexto("Nombre completo: ", 60);
    Fecha fechaIngreso = Validaciones::leerFechaSinHora("Fecha de ingreso:");
    string puesto = Validaciones::leerTexto("Puesto: ", 60);

    Colaborador* colaborador = new Colaborador(identificacion, nombreCompleto, fechaIngreso, puesto);
    cout << "\n--- Resumen del colaborador ---\n" << colaborador->toString() << endl;
    if (!Validaciones::confirmar("\nConfirma el registro del colaborador?")) {
        delete colaborador;
        cout << "\nRegistro cancelado por el usuario." << endl;
        return;
    }
    if (centro->agregarColaborador(colaborador)) {
        cout << "\nColaborador registrado correctamente." << endl;
    }
}

void Menu::buscarColaborador(CentroDistribucion* centro) {
    cout << "\n--- Buscar colaborador ---\n\n";
    string identificacion = Validaciones::leerTexto("Identificacion del colaborador: ", 30);
    Colaborador* colaborador = centro->buscarColaborador(identificacion);
    if (colaborador == nullptr) {
        cout << "Error: no existe un colaborador con esa identificacion en este centro." << endl;
    } else {
        cout << "\n" << colaborador->toString() << endl;
    }
}

void Menu::mostrarColaboradores(CentroDistribucion* centro) {
    cout << "\n--- Colaboradores del centro " << centro->getCodigo() << " ---\n";
    cout << centro->listarColaboradores();
}

void Menu::eliminarColaborador(CentroDistribucion* centro) {
    cout << "\n--- Eliminar colaborador ---\n\n";
    string identificacion = Validaciones::leerTexto("Identificacion del colaborador: ", 30);
    Colaborador* colaborador = centro->buscarColaborador(identificacion);
    if (colaborador == nullptr) {
        cout << "Error: no existe un colaborador con esa identificacion en este centro." << endl;
        return;
    }
    if (!centro->puedeEliminarColaborador(colaborador)) {
        return;
    }
    cout << "\n" << colaborador->toString() << endl;
    if (!Validaciones::confirmar("\nConfirma la eliminacion del colaborador?")) {
        cout << "\nEliminacion cancelada por el usuario." << endl;
        return;
    }
    if (centro->eliminarColaborador(colaborador)) {
        cout << "\nColaborador eliminado correctamente." << endl;
    }
}

// ============================================
// Integrante 1: bodegas y matrices
// ============================================

void Menu::menuBodegas() {
    limpiarPantalla();
    cout << "===== MENU DE BODEGAS =====" << endl;
    CentroDistribucion* centro = pedirCentro();
    if (centro == nullptr) {
        pausar();
        return;
    }

    int opcion;
    do {
        limpiarPantalla();
        cout << "===== MENU DE BODEGAS =====" << endl;
        cout << "Centro: " << centro->getCodigo() << " - " << centro->getNombre() << endl;
        cout << "1. Registrar bodega" << endl;
        cout << "2. Buscar bodega" << endl;
        cout << "3. Mostrar bodegas" << endl;
        cout << "4. Consultar matriz de una bodega" << endl;
        cout << "5. Consultar una celda" << endl;
        cout << "6. Eliminar bodega" << endl;
        cout << "0. Volver" << endl;
        opcion = Validaciones::leerEntero("Seleccione una opcion: ", 0, 6);

        switch (opcion) {
            case 1:
                registrarBodega(centro);
                break;
            case 2:
                buscarBodega(centro);
                break;
            case 3:
                mostrarBodegas(centro);
                break;
            case 4:
                consultarMatriz(centro);
                break;
            case 5:
                consultarCelda(centro);
                break;
            case 6:
                eliminarBodega(centro);
                break;
        }
        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);
}

void Menu::registrarBodega(CentroDistribucion* centro) {
    cout << "\n--- Registrar bodega ---\n\n";
    string codigo = Validaciones::leerTexto("Codigo de la bodega (ejemplo A): ", 10);
    if (centro->buscarBodega(codigo) != nullptr) {
        cout << "Error: ya existe una bodega con el codigo " << codigo << " en este centro." << endl;
        return;
    }
    string nombre = Validaciones::leerTexto("Nombre: ", 60);
    int tipo = pedirTipoBodega();
    int filas = Validaciones::leerEntero("Cantidad de filas (1 a 30): ", 1, MAXIMO_FILAS);
    int columnas = Validaciones::leerEntero("Cantidad de columnas (1 a 10): ", 1, MAXIMO_COLUMNAS);

    Bodega* bodega = new Bodega(codigo, nombre, tipo, filas, columnas);
    cout << "\n--- Resumen de la bodega ---\n" << bodega->toString() << endl;
    if (!Validaciones::confirmar("\nConfirma el registro de la bodega?")) {
        delete bodega;
        cout << "\nRegistro cancelado por el usuario." << endl;
        return;
    }
    if (centro->agregarBodega(bodega)) {
        cout << "\nBodega registrada correctamente." << endl;
    }
}

void Menu::buscarBodega(CentroDistribucion* centro) {
    cout << "\n--- Buscar bodega ---\n\n";
    string codigo = Validaciones::leerTexto("Codigo de la bodega: ", 10);
    Bodega* bodega = centro->buscarBodega(codigo);
    if (bodega == nullptr) {
        cout << "Error: no existe una bodega con el codigo " << codigo << " en este centro." << endl;
    } else {
        cout << "\n" << bodega->toString() << endl;
    }
}

void Menu::mostrarBodegas(CentroDistribucion* centro) {
    cout << "\n--- Bodegas del centro " << centro->getCodigo() << " ---\n";
    cout << centro->listarBodegas();
}

void Menu::consultarMatriz(CentroDistribucion* centro) {
    cout << "\n--- Consultar matriz de una bodega ---\n\n";
    string codigo = Validaciones::leerTexto("Codigo de la bodega: ", 10);
    Bodega* bodega = centro->buscarBodega(codigo);
    if (bodega == nullptr) {
        cout << "Error: no existe una bodega con el codigo " << codigo << " en este centro." << endl;
        return;
    }
    cout << endl;
    bodega->mostrarMatriz();
}

void Menu::consultarCelda(CentroDistribucion* centro) {
    cout << "\n--- Consultar una celda ---\n\n";
    string codigo = Validaciones::leerTexto("Codigo de la bodega: ", 10);
    Bodega* bodega = centro->buscarBodega(codigo);
    if (bodega == nullptr) {
        cout << "Error: no existe una bodega con el codigo " << codigo << " en este centro." << endl;
        return;
    }
    cout << endl;
    bodega->mostrarMatriz();
    cout << endl;

    int fila = Validaciones::leerEntero("Fila (0 a " + to_string(bodega->getFilas() - 1) + "): ",
                                        0, bodega->getFilas() - 1);
    int columna = Validaciones::leerEntero("Columna (0 a " + to_string(bodega->getColumnas() - 1) + "): ",
                                           0, bodega->getColumnas() - 1);

    if (bodega->estaLibre(fila, columna)) {
        cout << "\nLa celda " << bodega->nombreCelda(fila, columna) << " esta LIBRE." << endl;
    } else {
        cout << "\nLa celda " << bodega->nombreCelda(fila, columna) << " esta OCUPADA." << endl;
        // TODO Integrante 2: incluir Paquete.h en este archivo y mostrar el paquete:
        // Paquete* paquete = bodega->getPaquete(fila, columna);
        // paquete->mostrar();
    }
}

void Menu::eliminarBodega(CentroDistribucion* centro) {
    cout << "\n--- Eliminar bodega ---\n\n";
    string codigo = Validaciones::leerTexto("Codigo de la bodega: ", 10);
    Bodega* bodega = centro->buscarBodega(codigo);
    if (bodega == nullptr) {
        cout << "Error: no existe una bodega con el codigo " << codigo << " en este centro." << endl;
        return;
    }
    if (!centro->puedeEliminarBodega(bodega)) {
        return;
    }
    cout << "\n" << bodega->toString() << endl;
    if (!Validaciones::confirmar("\nConfirma la eliminacion de la bodega?")) {
        cout << "\nEliminacion cancelada por el usuario." << endl;
        return;
    }
    if (centro->eliminarBodega(bodega)) {
        cout << "\nBodega eliminada correctamente." << endl;
    }
}

// ============================================
// Reportes
// ============================================

void Menu::menuReportes() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "===== MENU DE REPORTES =====" << endl;
        cout << "1. Historial de un cliente" << endl;
        cout << "2. Clientes por cantidad de envios" << endl;
        cout << "3. Bitacora de un paquete" << endl;
        cout << "4. Consulta de despacho de un paquete" << endl;
        cout << "5. Ocupacion de bodegas" << endl;
        cout << "6. Despachos por colaborador" << endl;
        cout << "0. Volver" << endl;
        opcion = Validaciones::leerEntero("Seleccione una opcion: ", 0, 6);

        if (opcion == 5) {
            CentroDistribucion* centro = pedirCentro();
            if (centro != nullptr) {
                Reportes::ocupacionBodegas(centro);
            }
        } else if (opcion == 3) {
            // TODO Integrante 2: pedir el centro y el paquete y llamar a Reportes::bitacoraPaquete
            cout << "\nEste reporte todavia no esta disponible." << endl;
        } else if (opcion != 0) {
            // TODO Integrante 3: reportes 1, 2, 4 y 6
            cout << "\nEste reporte todavia no esta disponible." << endl;
        }

        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);
}

// ============================================
// Integrante 2: paquetes
// ============================================
// TODO Integrante 2: escribir aqui menuPaquetes() y sus opciones.

// ============================================
// Integrante 3: solicitudes y despachos
// ============================================
// TODO Integrante 3: escribir aqui menuSolicitudes(), menuDespachos() y sus opciones.
