//
// Created by Usuario on 27/10/2026.
//

#include "ClienteFisico.h"
using namespace std;

ClienteFisico::ClienteFisico(string identificacion, string nombre, string telefono, string correo)
    : Cliente(identificacion, nombre, telefono, correo) {
}

ClienteFisico::~ClienteFisico() {
}

string ClienteFisico::getTipo() {
    return "Fisico";
}
