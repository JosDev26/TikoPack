#include "../Encabezados/GestionPaquetes.h"
#include "../Encabezados/Validaciones.h"
GestionPaquetes::GestionPaquetes(ListaPaquetes listaP, ListaCentroDistribucion listaD, ListaClientes listaC)
    : listaP(listaP), listaD(listaD), listaC(listaC) {
}

GestionPaquetes::~GestionPaquetes() {
}

void GestionPaquetes::subMenu() {
    int opc = 0;

    while (opc != 5) {
        system("cls");
        cout << "Gestion Paquetes" << endl;
        cout << "1. Registrar" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Mostrar" << endl;
        cout << "4. Eliminar" << endl;
        cout << "0. Salir" << endl;
        Validaciones::leerEntero("Seleccione una opcion: ", 0, 4);

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
    string nombre = leerTexto("Nombre:", 3, 20);
    string descripcion = leerTexto("Descripción:", 1, 50);
    doble peso = inDouble("Descripción:", 1, 50);
    string categoria = leerTexto("Categoria:", 1, 50);
    Cliente *cliente = pedirCliente();
    CentroDistribucion *centroDistribucion = pedirCentro();
    //recordar ponerle un estado
    Paquete *paquete = new Paquete(nombre, descripcion, peso, categoria, cliente, centroDistribucion, "Activo");
    listaP->insertarFinal(paquete);
}

void GestionPaquetes::buscar() {
    string nombre;
    Paquete *paquete;
    while (true) {
        nombre = leerTexto("Nombre:", 3, 20);
        paquete = listaP->buscar(nombre);
        if (paquete == nullptr)cout << "\nCliente no existe\n";
        else break;
    }
    cout << "-----Informacion Del Paquete-----";
    cout << "\nNombre: ";
    cout << paquete->getNombre() << endl;
    cout << "\nDescripcion: ";
    cout << paquete->getDescripcion() << endl;
    cout << "\n Peso: ";
    cout << paquete->getPeso() << endl;
    cout << "\n Categoria: ";
    cout << paquete->getCategoria() << endl;
    cout << "\n Cliente: ";
    cout << paquete->getCliente().getNombre() << endl;
    cout << "\n Centro: ";
    cout << paquete->getCentro().getNombre() << endl;
}

    void GestionPaquetes::mostrar()
    {
        NodoPaquete *nodo = listaP.getPrimero();

        while (nodo != nullptr) {
            Paquete paquete = nodo->getPaquete();

            cout <<
                    "+----------------+------------------------------------------+------------------------+----------------+--------+-----------+\n";
            cout <<
                    "| Nombre |                  Descripcion                  |        Peso          | Categoria | Cliente |   Centro   |\n";
            cout <<
                    "+----------------+------------------------------------------+------------------------+----------------+--------+-----------+\n";
            cout << pad(paquete.getNombre(), 16) <<"|"; //16 42 24 8 11
            cout << pad(paquete.getDescripcion(),42) <<"|";
            cout << pad(paquete.getPeso(), 24)<< "|";
            cout << pad(paquete.getCategoria(),8 )<<"|" ;
            cout << pad(paquete.getCliente().getNombre(),16 )<< "|" ;
            cout << pad(paquete.getCentro().getNombre(),13 )<< "|"<<endl;

            nodo = nodo->getSiguiente();
        }
        cout <<
            "+----------------+------------------------------------------+------------------------+----------------+--------+-----------+\n";
    }

    void GestionPaquetes::eliminar() {
        string nombre;
        Paquete *paquete;
        while (true) {
            nombre = leerTexto("Nombre:", 3, 20);
            paquete = listaP->buscar(nombre);
            if (paquete == nullptr)cout << "\nCliente no existe\n";
            else break;
        }
        listaP.eliminar(paquete);
    }

    Cliente GestionPaquetes::pedirCliente()
    {
        Cliente *cliente;
        string cedula;
        while (true) {
            cedula = leerTexto("Cedula de cliente:", 1, 12);

            cliente = listaC->buscar(cedula);
            if (cliente == nullptr)cout << "\nCliente no existe\n";
            else break;
        }

        return cliente;
    }

    CentroDistribucion GestionPaquetes::pedirCentro()
    {
        CentroDistribucion *distri;
        string codigo;
        while (true) {
            cedula = leerTexto("Codigo de Centro de Distribucion:", 1);
            distri = listaD->buscar(codigo);
            if (distri == nullptr)cout << "\nCliente no existe\n";
            else break;
        }

        return distri;
    }
