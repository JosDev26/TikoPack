#include "../Encabezados/Util.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

string decimal(double valor) {
    stringstream ss;
    ss << fixed << setprecision(2) << valor;
    return ss.str();
}

string pad(string valor, int longi) {
    int maxVal = longi - valor.length();
    if (maxVal > 0) {
        for (int i = 0; i < maxVal; i++) {
            valor = valor + " ";
        }
    }
    return valor.substr(0, longi);
}

string padr(string valor, int longi) {
    int maxVal = longi - valor.length();
    if (maxVal > 0) {
        for (int i = 0; i < maxVal; i++) {
            valor = " " + valor;
        }
    }
    return valor.substr(0, longi);
}

string inString(string mensaje, int longi) {
    string valor;

    do {
        cout << mensaje << endl;
        getline(cin, valor);
        //cin >> valor;
        size_t inicio = valor.find_first_not_of(" \t\n\r\f\v");

        if (inicio == string::npos) {
            valor = "";
        } else {
            size_t fin = valor.find_last_not_of(" \t\n\r\f\v");
            valor = valor.substr(inicio, fin - inicio + 1);
        }

        if (valor.length() < longi) {
            cout << "Debe digitar un valor con al menos "
                 << longi << " caracteres." << endl;
        }

    } while (valor.length() < longi);

    return valor;
}
double inDouble(string mensaje, int longi) {
    string texto;
    double valor = 0;
    (void) longi;

    do {
        cout << mensaje << endl;
        getline(cin >> ws, texto);

        size_t inicio = texto.find_first_not_of(" \t\n\r\f\v");
        if (inicio == string::npos) {
            texto = "";
        } else {
            size_t fin = texto.find_last_not_of(" \t\n\r\f\v");
            texto = texto.substr(inicio, fin - inicio + 1);
        }

        stringstream ss(texto);
        char extra;
        if (!(ss >> valor) || (ss >> extra)) {
            cout << "Debe digitar un numero valido." << endl;
            valor = 0;
        } else if (valor <= 0) {
            cout << "Debe digitar un numero mayor a cero." << endl;
        }
    } while (valor <= 0);

    return valor;
}

int inInt(string mensaje, int min, int max) {
    string texto;
    int valor = min - 1;

    do {
        cout << mensaje << " [ " << min << " <-> " << max << " ]" << endl;
        getline(cin, texto);

        size_t inicio = texto.find_first_not_of(" \t\n\r\f\v");

        if (inicio == string::npos) {
            texto = "";
        } else {
            size_t fin = texto.find_last_not_of(" \t\n\r\f\v");
            texto = texto.substr(inicio, fin - inicio + 1);
        }

        stringstream ss(texto);
        char extra;

        if (!(ss >> valor) || (ss >> extra)) {
            cout << "Debe digitar un numero entero valido." << endl;
            valor = min - 1;
        } else if (valor < min || valor > max) {
            cout << "Debe digitar un numero entre "
                 << min << " y " << max << "." << endl;
        }

    } while (valor < min || valor > max);

    return valor;
}
