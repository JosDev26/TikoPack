//
// Created by Usuario on 27/10/2026.
//

#ifndef MENU_H
#define MENU_H

#include <string>

class Sistema;
class CentroDistribucion;

class Menu {
private:
    Sistema* sistema;

    void limpiarPantalla();
    void pausar();
    CentroDistribucion* pedirCentro();
    int pedirTipoBodega();
    std::string pedirProvincia();

    // ===== Integrante 1 =====
    void menuCentros();
    void registrarCentro();
    void buscarCentro();
    void mostrarCentros();
    void eliminarCentro();

    void menuClientes();
    void registrarCliente(CentroDistribucion* centro);
    void buscarCliente(CentroDistribucion* centro);
    void mostrarClientes(CentroDistribucion* centro);
    void eliminarCliente(CentroDistribucion* centro);

    void menuColaboradores();
    void registrarColaborador(CentroDistribucion* centro);
    void buscarColaborador(CentroDistribucion* centro);
    void mostrarColaboradores(CentroDistribucion* centro);
    void eliminarColaborador(CentroDistribucion* centro);

    void menuBodegas();
    void registrarBodega(CentroDistribucion* centro);
    void buscarBodega(CentroDistribucion* centro);
    void mostrarBodegas(CentroDistribucion* centro);
    void consultarMatriz(CentroDistribucion* centro);
    void consultarCelda(CentroDistribucion* centro);
    void eliminarBodega(CentroDistribucion* centro);

    void menuReportes();

    // ===== Integrante 2 =====
    // TODO Integrante 2: void menuPaquetes(); y sus opciones

    // ===== Integrante 3 =====
    // TODO Integrante 3: void menuSolicitudes(); void menuDespachos(); y sus opciones

public:
    Menu(Sistema* sistema);
    void ejecutar();
};

#endif
