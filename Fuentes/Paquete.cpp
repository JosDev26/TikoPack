
#include "../Encabezados/Paquete.h"
Paquete::Paquete(string nombre,string descripcion, double peso, string categoria, Cliente* cliente,
                 CentroDistribucion* centroDistribucion, string estado) {
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->peso = peso;
    this->categoria = categoria;
    this->cliente = cliente;
    this->centroDistribucion = centroDistribucion;
    this->estado = estado;
}
~Paquete() {}
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
void Paquete::setNombre(string nombre) {
    this->nombre = nombre;
}

void Paquete::setDescripcion(string descripcion) {
    this->descripcion = descripcion;
}

void Paquete::setPeso(float peso) {
    this->peso = peso;
}

void Paquete::setCategoria(string categoria) {
    this->categoria = categoria;
}

void Paquete::setCliente(Cliente cliente) {
    this->cliente = cliente;
}

void Paquete::setCentroDistribucion(CentroDistribucion centroDistribucion) {
    this->centroDistribucion = centroDistribucion;
}

void Paquete::setEstado(string estado) {
    this->estado = estado;
}