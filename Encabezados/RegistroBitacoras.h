#include <string>
#include <iostream>
#include "Colaborador.h"
#include "Paquete.h"
#include "Fecha.h"
using namespace std;
class RegistroBitacoras {
    private:
    string estadoAnterior;
    string estadoNuevo;
    Fecha fecha;
    Colaborador *colaborador;
    Paquete *paquete;
    public:
    RegistroBitacoras(string estado_anterior, string estado_nuevo, Fecha fecha,
        Colaborador* colaborador, Paquete* paquete);
    string getEstadoAnterior();
    string getEstadoNuevo();
    string getFecha();
    Colaborador getColaborador();
    Paquete getPaquete();
};


