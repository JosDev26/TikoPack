//
// Created by Usuario on 27/10/2026.
//

#include "Validaciones.h"
#include <iostream>
#include <sstream>
using namespace std;

string Validaciones::quitarEspacios(string texto) {
    size_t inicio = texto.find_first_not_of(" \t\r");
    if (inicio == string::npos) {
        return "";
    }
    size_t fin = texto.find_last_not_of(" \t\r");
    return texto.substr(inicio, fin - inicio + 1);
}

int Validaciones::leerEntero(string mensaje, int minimo, int maximo) {
    string linea;
    while (true) {
        cout << mensaje;
        getline(cin, linea);
        stringstream ss(linea);
        int numero;
        char sobrante;
        if (ss >> numero && !(ss >> sobrante) && numero >= minimo && numero <= maximo) {
            return numero;
        }
        cout << "Error: digite un numero entero entre " << minimo
             << " y " << maximo << "." << endl;
    }
}

double Validaciones::leerDouble(string mensaje, double minimo) {
    string linea;
    while (true) {
        cout << mensaje;
        getline(cin, linea);
        // se cambia la coma por punto
        for (int i = 0; i < (int)linea.length(); i++) {
            if (linea[i] == ',') {
                linea[i] = '.';
            }
        }
        stringstream ss(linea);
        double numero;
        char sobrante;
        if (ss >> numero && !(ss >> sobrante) && numero > minimo) {
            return numero;
        }
        cout << "Error: digite un numero mayor que " << minimo << "." << endl;
    }
}

double Validaciones::leerDoubleRango(string mensaje, double minimo, double maximo) {
    string linea;
    while (true) {
        cout << mensaje;
        getline(cin, linea);
        for (int i = 0; i < (int)linea.length(); i++) {
            if (linea[i] == ',') {
                linea[i] = '.';
            }
        }
        stringstream ss(linea);
        double numero;
        char sobrante;
        if (ss >> numero && !(ss >> sobrante) && numero >= minimo && numero <= maximo) {
            return numero;
        }
        cout << "Error: digite un numero entre " << minimo
             << " y " << maximo << "." << endl;
    }
}

string Validaciones::leerTexto(string mensaje, int maximo) {
    string linea;
    while (true) {
        cout << mensaje;
        getline(cin, linea);
        linea = quitarEspacios(linea);
        if (linea == "") {
            cout << "Error: este dato no puede quedar vacio." << endl;
        } else if ((int)linea.length() > maximo) {
            cout << "Error: el texto no puede tener mas de " << maximo
                 << " caracteres." << endl;
        } else {
            return linea;
        }
    }
}

string Validaciones::leerTelefono(string mensaje) {
    while (true) {
        string telefono = leerTexto(mensaje, 15);
        bool soloNumeros = true;
        for (int i = 0; i < (int)telefono.length(); i++) {
            if (telefono[i] < '0' || telefono[i] > '9') {
                soloNumeros = false;
            }
        }
        if (soloNumeros && telefono.length() >= 8) {
            return telefono;
        }
        cout << "Error: el telefono solo puede tener numeros (de 8 a 15 digitos)." << endl;
    }
}

string Validaciones::leerCorreo(string mensaje) {
    while (true) {
        string correo = leerTexto(mensaje, 60);
        int cantidadArrobas = 0;
        int posicionArroba = -1;
        bool tieneEspacios = false;
        for (int i = 0; i < (int)correo.length(); i++) {
            if (correo[i] == '@') {
                cantidadArrobas++;
                posicionArroba = i;
            } else if (correo[i] == ' ' || correo[i] == '\t') {
                tieneEspacios = true;
            }
        }

        // debe haber un punto despues del @
        bool tienePunto = false;
        for (int i = posicionArroba + 1; i < (int)correo.length(); i++) {
            if (correo[i] == '.') {
                tienePunto = true;
            }
        }

        bool arrobaBien = cantidadArrobas == 1 && posicionArroba > 0;
        bool terminaBien = correo[correo.length() - 1] != '.';

        if (arrobaBien && tienePunto && terminaBien && !tieneEspacios) {
            return correo;
        }
        cout << "Error: el correo debe tener el formato usuario@dominio.com" << endl;
    }
}

int Validaciones::diasDelMes(int mes, int anio) {
    if (mes == 2) {
        // anio bisiesto
        if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
            return 29;
        }
        return 28;
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    }
    return 31;
}

Fecha Validaciones::leerFechaSinHora(string mensaje) {
    cout << mensaje << endl;
    while (true) {
        int dia = leerEntero("  Dia (1-31): ", 1, 31);
        int mes = leerEntero("  Mes (1-12): ", 1, 12);
        int anio = leerEntero("  Anio (1950-2100): ", 1950, 2100);

        if (dia <= diasDelMes(mes, anio)) {
            return Fecha(dia, mes, anio);
        }
        cout << "Error: ese mes solo tiene " << diasDelMes(mes, anio)
             << " dias. Digite la fecha de nuevo." << endl;
    }
}

Fecha Validaciones::leerFecha(string mensaje) {
    Fecha fecha = leerFechaSinHora(mensaje);
    int hora = leerEntero("  Hora (0-23): ", 0, 23);
    int minuto = leerEntero("  Minuto (0-59): ", 0, 59);
    return Fecha(fecha.getDia(), fecha.getMes(), fecha.getAnio(), hora, minuto);
}

bool Validaciones::confirmar(string pregunta) {
    string respuesta;
    while (true) {
        cout << pregunta << " (s/n): ";
        getline(cin, respuesta);
        respuesta = quitarEspacios(respuesta);
        if (respuesta == "s" || respuesta == "S") {
            return true;
        }
        if (respuesta == "n" || respuesta == "N") {
            return false;
        }
        cout << "Error: digite 's' para confirmar o 'n' para cancelar." << endl;
    }
}
