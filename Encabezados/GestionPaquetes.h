#include "../Encabezados/Paquete.h"
#include "../Encabezados/Util.h"
#include "../Encabezados/ListaPaquetes.h"
#include "../Encabezados/ListaCentroDistribucion.h"
#include "../Encabezados/ListaClientes.h"
#include <iostream>
using namespace std;

class GestionPaquetes {
    private:
    ListaCentroDistribucion listaD;
    ListaClientes listaC;
    ListaPaquetes listaP;
    public:
    GestionPaquetes(ListaPaquetes listaP, ListaCentroDistribucion listaD, ListaClientes listaC );
    ~GestionPaquetes();
    void subMenu();
    void registrar();
    void eliminar();
    void mostrar();
    void buscar();
    Cliente* pedirCliente();
};
