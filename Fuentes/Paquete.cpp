
#include "../Encabezados/Paquete.h"
string Paquete::getNombre() const {
    return nombre;
}

string Paquete::getDescripcion() const {
    return descripcion;
}

float Paquete::getPeso() const {
    return peso;
}

string Paquete::getCategoria() const {
    return categoria;
}

Cliente Paquete::getCliente() const {
    return cliente;
}

CentroDistribucion Paquete::getCentroDistribucion() const {
    return centroDistribucion;
}

string Paquete::getEstado() const {
    return estado;
}