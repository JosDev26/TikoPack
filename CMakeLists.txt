cmake_minimum_required(VERSION 4.3)
project(Josue_PG1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Josue_PG1 Fuentes/main.cpp
        Fuentes/Fecha.cpp
        Encabezados/Fecha.h
        Fuentes/Validaciones.cpp
        Encabezados/Validaciones.h
        Fuentes/Cliente.cpp
        Encabezados/Cliente.h
        Fuentes/ClienteFisico.cpp
        Encabezados/ClienteFisico.h
        Fuentes/ClienteEmpresa.cpp
        Encabezados/ClienteEmpresa.h
        Fuentes/Colaborador.cpp
        Encabezados/Colaborador.h
        Fuentes/Celda.cpp
        Encabezados/Celda.h
        Fuentes/Bodega.cpp
        Encabezados/Bodega.h
        Fuentes/ListaCentros.cpp
        Encabezados/ListaCentros.h
        Fuentes/ListaClientes.cpp
        Encabezados/ListaClientes.h
        Fuentes/ListaColaboradores.cpp
        Encabezados/ListaColaboradores.h
        Fuentes/ListaBodegas.cpp
        Encabezados/ListaBodegas.h
        Fuentes/CentroDistribucion.cpp
        Encabezados/CentroDistribucion.h
        Fuentes/Sistema.cpp
        Encabezados/Sistema.h
        Fuentes/Reportes.cpp
        Encabezados/Reportes.h
        Fuentes/Menu.cpp
        Encabezados/Menu.h
        Fuentes/RegistroBitacoras.cpp
        Encabezados/RegistroBitacoras.h
        # TODO Integrante 2: Paquete, RegistroBitacora, ListaPaquetes, ListaBitacora
        # TODO Integrante 3: Tarifas, SolicitudEnvio, Despacho, ListaSolicitudes, ListaDespachos
)

if (MINGW)
    target_compile_options(Josue_PG1 PRIVATE -mcrtdll=ucrt)
    target_link_options(Josue_PG1 PRIVATE -static -mcrtdll=ucrt)
endif()
