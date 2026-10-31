#include "Sistema.h"
#include "Menu.h"

int main() {
    Sistema sistema;
    sistema.cargarDatosPrueba();
    Menu menu(&sistema);
    menu.ejecutar();
    return 0;
}
