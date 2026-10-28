#include "../Encabezados/GestionPaquetes.h"
GestionPaquetes::GestionPaquetes() {}
GestionPaquetes::~GestionPaquetes() {}

void GestionPaquetes::subMenu() {
    int opc = 0;

    while (opc != 4) {
        system("cls");
        cout<<"Gestion Paquetes"<<endl;
        cout<<"1. Registrar"<<endl;
        cout<<"2. Buscar"<<endl;
        cout<<"3. Mostrar"<<endl;
        cout<<"4. Eliminar"<<endl;
        cout<<"5. Salir"<<endl;
        cin>>opc;

        switch (opc) {
            case 1:
                registrar();
                break;
            case 2:
                buscar();
                break;
            case 3:
                mostrar();
                break;
            case 4:
                eliminar();
                break;
            case 5:
                break;
            default:
                cout << "opcion invalida \n";
        }
        if (opc != 4) {
            cout << "\n Presione Enter para continuar... \n";
            cin.get();
        }
    }
}

void GestionPaquetes::registrar() {

}

void GestionPaquetes::buscar() {}


void GestionPaquetes::mostrar() {

}

void GestionPaquetes::eliminar() {

}

