#pragma once
#include <string>
#include "Cliente.h"
#include "CentroDistribucion.h"
using namespace std;

class Paquete {
private:
    string nombre;
    string descripcion;
    double peso;
    string categoria;
    Cliente* cliente;
    CentroDistribucion* centroDistribucion;
    string estado;

public:
     Paquete(string nombre,string descripcion, double peso, string categoria, Cliente* cliente,
    CentroDistribucion* centroDistribucion, string estado);
     ~Paquete();

     string getNombre();

    void setNombre(const string &nombre);

     string getDescripcion();

    void setDescripcion(const string &descripcion);

     float getPeso();

    void setPeso(float peso);

     string getCategoria();

    void setCategoria(const string &categoria);

     Cliente getCliente();

    void setCliente(const Cliente &cliente);

     CentroDistribucion getCentroDistribucion();

    void setCentroDistribucion(const CentroDistribucion &centro_distribucion);

     string getEstado();

    void setEstado(const string &estado);
};
