#include "../Encabezados/RegistroBitacoras.h"
RegistroBitacoras::RegistroBitacoras(string estado_anterior, string estado_nuevo,
                                     Fecha fecha, Colaborador* colaborador,
                                     Paquete* paquete) {
    this->estadoAnterior = estado_anterior;
    this->estadoNuevo = estado_nuevo;
    this->fecha = fecha;
    this->colaborador = colaborador;
    this->paquete = paquete;
}

string RegistroBitacoras::getEstadoAnterior() {
    return estadoAnterior;
}

string RegistroBitacoras::getEstadoNuevo() {
    return estadoNuevo;
}

string RegistroBitacoras::getFecha() {
    return fecha;
}

Colaborador RegistroBitacoras::getColaborador() {
    return colaborador;
}

Paquete RegistroBitacoras::getPaquete() {
    return paquete;
}