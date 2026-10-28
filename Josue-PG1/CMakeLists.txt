cmake_minimum_required(VERSION 4.3)
project(Josue_PG1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Josue_PG1 main.cpp
        Fecha.cpp
        Fecha.h
        Validaciones.cpp
        Validaciones.h
        Cliente.cpp
        Cliente.h
        ClienteFisico.cpp
        ClienteFisico.h
        ClienteEmpresa.cpp
        ClienteEmpresa.h
        Colaborador.cpp
        Colaborador.h
        Celda.cpp
        Celda.h
        Bodega.cpp
        Bodega.h
        ListaCentros.cpp
        ListaCentros.h
        ListaClientes.cpp
        ListaClientes.h
        ListaColaboradores.cpp
        ListaColaboradores.h
        ListaBodegas.cpp
        ListaBodegas.h
        CentroDistribucion.cpp
        CentroDistribucion.h
        Sistema.cpp
        Sistema.h
        Reportes.cpp
        Reportes.h
        Menu.cpp
        Menu.h
        # TODO Integrante 2: Paquete, RegistroBitacora, ListaPaquetes, ListaBitacora
        # TODO Integrante 3: Tarifas, SolicitudEnvio, Despacho, ListaSolicitudes, ListaDespachos
)

if (MINGW)
    target_compile_options(Josue_PG1 PRIVATE -mcrtdll=ucrt)
    target_link_options(Josue_PG1 PRIVATE -static -mcrtdll=ucrt)
endif()
