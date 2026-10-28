# Proyecto 2
## Resumen, clases y convenciones

> **Entrega:** domingo 1 de noviembre de 2026, 11:59 p. m., por el Aula Virtual (solo un integrante entrega).
> **Valor:** 15 % 
>
> Es como el README del proyecto con indicaciones generales xd

> **Versión 3 (27 oct):** se actualizó con lo que ya programó el Integrante 1.
> - **Ya no existe `Constantes.h`.** Los estados son **textos** (`"Recibido"`, `"Pendiente"`, …), igual que los estados del Proyecto 1, y las categorías / tipos de bodega son un `int` del 1 al 4 que cada clase pasa a texto con su propio método (`Bodega::getNombreTipo()`). Ver [6.5](#65-estados-y-categorías).
> - Las funciones `agregar…` **borran el objeto si no lo pueden guardar** (como `registrarCancha` del Proyecto 1). Ver [6.4](#64-separación-menú--lógica).
> - `Validaciones` tiene funciones nuevas (`leerDoubleRango`, `leerTelefono`, `leerCorreo`, `leerFechaSinHora`, `confirmar`) y `leerFecha` ya no acepta fechas como 31/02.
> - La matriz se dibuja con tabulaciones (`\t`), sin `setw`. Ver [6.8](#68-formatos-de-salida).
> - Los comentarios del código son cortos y no mencionan el material ni el Proyecto 1. Ver [6.11](#611-comentarios).
> - Lo que falta de cada integrante quedó marcado en el código con `// TODO Integrante 2` y `// TODO Integrante 3`.

> **Versión 2 (25 oct):** se ajustó todo al nivel de lo visto en clase (semanas 9 a 15).
> Cambios principales:
> - **Sin plantillas (`template`)**: cada colección tiene su propia lista (`ListaClientes`, `ListaPaquetes`, …), como en los ejemplos del curso.
> - **Sin `enum`**: los estados y categorías eran constantes `const int` en `Constantes.h` (se quitó en la versión 3).
> - `Tarifas` corregida para que compile (los `static const double` se definen en el `.cpp`).
> - `Paquete::puedeCambiarA` usa una tabla local en vez de un atributo `static`.
> - Nueva sección de **dependencias entre integrantes** ([3.1](#31-dependencias-entre-integrantes)) y calendario actualizado.
> - Diagrama actualizado: `diagrama_clases.puml` (fuente PlantUML) y `diagrama_clases.png`. `UML Prototipo.png` es la versión vieja (con `Lista<T>` y `enum`) y se puede borrar.

---

## Índice

1. [Resumen](#1-resumen)
2. [Reglas del negocio](#2-reglas-del-negocio-lo-que-el-programa-debe-validar)
3. [División del trabajo](#3-división-del-trabajo)
4. [Explicación de cada clase](#4-explicación-de-cada-clase)
5. [Flujos importantes paso a paso](#5-flujos-importantes-paso-a-paso)
6. [Convenciones del equipo](#6-convenciones-del-equipo)
7. [Checklist antes de integrar](#7-checklist-antes-de-integrar-código)

---

## 1. Resumen

**TicoPack Logistics** es una empresa que **recibe, guarda y despacha paquetes**. Tiene varios **centros de distribución** y cada centro maneja:

- **Clientes**, que pueden ser persona física o empresa (las empresas tienen descuento).
- **Colaboradores**, los empleados que hacen los cambios.
- **Bodegas**, cada una organizada como una **matriz de celdas** (filas × columnas).
- **Paquetes**, que pasan por distintos estados y guardan una **bitácora** de esos cambios.
- **Solicitudes de envío**, que un colaborador puede aprobar, rechazar o anular.
- **Despachos**: cada solicitud aprobada genera uno, y al final se entrega el paquete.

### Evaluación

| Rubro                                            | Puntos  |
| ------------------------------------------------ | ------- |
| Centros, clientes (con herencia) y colaboradores | 10      |
| Bodegas y matriz dinámica                        | 10      |
| Paquetes, estados y bitácora                     | 15      |
| Almacenamiento y reubicación                     | 15      |
| Solicitudes de envío                             | 12      |
| Despachos                                        | 10      |
| Reportes (6 × 4 pts)                             | 24      |
| Interfaz y validaciones                          | 4       |
| **Total**                                        | **100** |

### Reglas generales obligatorias

- **Prohibido usar la STL** para colecciones u ordenamientos: nada de `vector`, `list`, `map`, `array`, `deque` ni `sort`.
- Sí se puede usar `iostream`, `string`, `sstream`, `iomanip` y bibliotecas básicas vistas en clase.
- Todas las colecciones que crecen son **listas enlazadas propias, una por tipo** (`ListaClientes`, `ListaPaquetes`, …), hechas con `new` y `delete`, igual que `ListaMateriales` (semana 12) y `ListaEstudiantes` (semana 11).
- **No usamos plantillas (`template`) ni `enum`**, porque no se vieron en el curso y el enunciado pide hacer las listas "tal como se ha trabajado en el curso".
- Cada bodega tiene una **matriz dinámica** (`Celda**`) creada con `new`, igual que `MatrizDinamica` (semana 14).
- Hay que usar **herencia**: `Cliente` → `ClienteFisico` / `ClienteEmpresa`.
- **Si el programa no compila, la nota es 0.**
- El programa **nunca debe caerse** por datos inválidos, por ejemplo si escriben letras donde va un número.
- Hay que entregar el **diagrama de clases**, el **código fuente completo** y un **.txt** con nombre completo y cédula de los 3.
- Debe existir una función que cargue **datos de prueba ("quemados")**.
- El profesor puede pedir **defensa oral**, así que cada uno debe entender el proyecto completo.

---

## 2. Reglas del negocio (lo que el programa debe validar)

### 2.1 Unicidad de códigos

| Dato | Único en… | Quién lo verifica |
|---|---|---|
| Código de centro | Todo el sistema | `Sistema` |
| Código de paquete | Todo el sistema | `Sistema::existePaquete` |
| Código de solicitud | Todo el sistema | `Sistema::existeSolicitud` |
| Código de despacho | Todo el sistema | `Sistema::existeDespacho` |
| Identificación de cliente | Su centro | `CentroDistribucion` |
| Identificación de colaborador | Su centro | `CentroDistribucion` |
| Código de bodega | Su centro | `CentroDistribucion` |

> **Convención:** los códigos **globales** (paquete, solicitud, despacho) los verifica el **Menú** llamando a `Sistema` **antes** de crear el objeto, porque `CentroDistribucion` no conoce a los otros centros.

### 2.2 Categorías, tipos de bodega y tarifas

| Código (`int`) | Categoría / tipo de bodega | Tarifa por kg |
|---|---|---|
| 1 | General | ¢1 500 |
| 2 | Frágil | ¢2 000 |
| 3 | Tecnología | ¢2 500 |
| 4 | Documentos | ¢1 000 |

- Usamos **los mismos números** para la categoría del paquete y el tipo de bodega. Así, la compatibilidad es simplemente `bodega->getTipo() == paquete->getCategoria()`.
- **Costo:** `costoBase = peso × tarifa`. Si el cliente es empresa: `costoFinal = costoBase − costoBase × descuento / 100`.

### 2.3 Estados del paquete

Camino normal:
```
Recibido ──(asignar celda)──► Almacenado ──(aprobar solicitud)──► En transito ──(finalizar despacho)──► Entregado
```
Incidencias (camino temporal):
```
Recibido     ──► Incidencia ──(almacenar normal)──► Almacenado
Almacenado   ──► Incidencia ──(resolver)──────────► Almacenado
En transito  ──► Incidencia ──(resolver)──────────► En transito
```

Tabla de transiciones permitidas (fila = estado actual, columna = nuevo estado):

| Actual \ Nuevo | Recibido | Almacenado | En tránsito | Entregado | Incidencia |
|---|---|---|---|---|---|
| **Recibido** | – | Sí | No | No | Sí |
| **Almacenado** | No | – | Sí | No | Sí |
| **En tránsito** | No | No | – | Sí | Sí |
| **Entregado** | No | No | No | – | No |
| **Incidencia** | No | Sí | Sí | No | – |

**Reglas clave:**
- **Recibido → Almacenado**: **solo** al asignar una celda.
- **Almacenado → En tránsito**: **solo** al aprobar una solicitud. En ese momento **se libera la celda**.
- **En tránsito → Entregado**: **solo** al finalizar el despacho.
- **Incidencia** es temporal:
  - Si ocurrió estando *Almacenado*, el paquete conserva su celda y al resolverse vuelve a *Almacenado*.
  - Si ocurrió en un despacho *En proceso*, el paquete no tiene celda y al resolverse vuelve a *En tránsito*.
  - Si ocurrió estando *Recibido*, el paquete no tiene celda y al resolverse se usa **almacenar** normal, que lo pasa a *Almacenado*.
- Un paquete *En tránsito* o *Entregado* **nunca** tiene celda.
- **Cada cambio de estado** se registra en la bitácora con: estado anterior, estado nuevo, fecha y colaborador del mismo centro.

### 2.4 Estados de la solicitud

```
Pendiente ──► Aprobada   (crea el despacho)
          ──► Rechazada
          ──► Anulada
```
- Estos tres estados son **finales** y no se pueden cambiar.
- Solo se crea una solicitud si el paquete está **Almacenado**.
- Solo puede haber **una solicitud Pendiente** por paquete a la vez.
- Si un paquete ya tiene una solicitud aprobada (y su despacho), **no se le pueden crear más solicitudes**.

### 2.5 Estados del despacho

`"En proceso"` → `"Finalizado"`. Para finalizar, el despacho tiene que estar *En proceso* **y** el paquete *En tránsito*. Si el paquete está en *Incidencia*, no se puede finalizar.

### 2.6 Reglas de eliminación

| Se puede eliminar… | Solo si… |
|---|---|
| Centro | No tiene clientes, colaboradores, bodegas, paquetes, solicitudes ni despachos |
| Cliente | No tiene paquetes, solicitudes ni despachos |
| Colaborador | No es responsable de ninguna solicitud, despacho ni registro de bitácora |
| Bodega | Todas sus celdas están libres y ningún paquete la tiene asignada |
| Paquete | Está *Recibido*, no tiene celda y no tiene solicitudes ni despachos |
| Solicitud, despacho, bitácora | **Nunca se eliminan** |

> Varias de estas reglas necesitan datos de otro integrante. Ver [3.1](#31-dependencias-entre-integrantes).

### 2.7 Validaciones de datos

- Los códigos, identificaciones y textos obligatorios **no pueden quedar vacíos**.
- Filas y columnas de una bodega: **enteros > 0**.
- Peso del paquete: **> 0**.
- Descuento de empresa: **entre 0 y 100**.
- Categorías, tipos y estados: **solo los valores definidos**.
- Cualquier referencia (cliente, colaborador, bodega…) debe **existir y pertenecer al mismo centro**.

---

## 3. División del trabajo

| | Integrante 1 | Integrante 2 | Integrante 3 |
|---|---|---|---|
| **Tema** | Base, centros, personas, bodegas | Paquetes y almacenamiento | Solicitudes, despachos y reportes |
| **Clases** | `Fecha`, `Validaciones`, `Sistema`, `CentroDistribucion` (parte 1), `Cliente`, `ClienteFisico`, `ClienteEmpresa`, `Colaborador`, `Bodega`, `Celda`, `Menu` (menú principal) | `Paquete`, `RegistroBitacora`, `CentroDistribucion` (parte 2) | `Tarifas`, `SolicitudEnvio`, `Despacho`, `Reportes`, `CentroDistribucion` (parte 3) |
| **Listas** | `ListaCentros`, `ListaClientes`, `ListaColaboradores`, `ListaBodegas` | `ListaPaquetes`, `ListaBitacora` | `ListaSolicitudes`, `ListaDespachos` |
| **Submenús** | Centros, Clientes, Colaboradores, Bodegas | Paquetes | Solicitudes, Despachos, Reportes |
| **Reportes** | Ocupación de bodegas | Bitácora de un paquete | Los otros 4 |
| **Puntos aprox.** | ~28 + base | ~34 | ~38 |

> ✅ **Integrante 1: listo** (27 oct). `Fecha`, `Validaciones` y **`ListaClientes`** ya están subidos. `ListaClientes` sirve de **modelo**: los otros copian ese mismo patrón para hacer sus listas (ver [4.1](#41-clases-base-integrante-1)).

### 3.1 Dependencias entre integrantes

Estos métodos los **usa** un integrante pero los **escribe** otro. Hay que acordar las firmas **antes** de programar.

| Lo necesita | Para… | Método | Lo escribe |
|---|---|---|---|
| Int. 1 | `Sistema::existePaquete` | `CentroDistribucion::buscarPaquete(codigo)` | Int. 2 |
| Int. 1 | `Sistema::existeSolicitud` / `existeDespacho` | `CentroDistribucion::buscarSolicitud(codigo)` / `buscarDespacho(codigo)` | Int. 3 |
| Int. 1 | Eliminar cliente | `ListaPaquetes::tieneDeCliente(c)` | Int. 2 |
| Int. 1 | Eliminar cliente | `ListaSolicitudes::tieneDeCliente(c)`, `ListaDespachos::tieneDeCliente(c)` | Int. 3 |
| Int. 1 | Eliminar colaborador | `ListaPaquetes::colaboradorEnBitacoras(col)` (usa `Paquete::tieneRegistroDe(col)`) | Int. 2 |
| Int. 1 | Eliminar colaborador | `ListaSolicitudes::tieneDeResponsable(col)`, `ListaDespachos::tieneDeResponsable(col)` | Int. 3 |
| Int. 1 | Eliminar bodega | `ListaPaquetes::tieneEnBodega(b)` | Int. 2 |
| Int. 2 | Almacenar / reubicar | `Bodega`: `asignar`, `liberar`, `estaLibre`, `posicionValida`, `primeraCeldaLibre`, `porcentajeDisponible`, `mostrarMatriz` | Int. 1 |
| Int. 2 | Eliminar paquete | `ListaSolicitudes::tieneDePaquete(p)` | Int. 3 |
| Int. 3 | Crear y aprobar solicitudes | `Paquete`: `getEstado`, `getPeso`, `getCategoria`, `getPropietario`, `getTieneDespacho`, `setTieneDespacho`, `quitarUbicacion`, `cambiarEstado` | Int. 2 |
| Int. 3 | Reporte clientes por envíos | `CentroDistribucion::getClientes()` (recorrer `ListaClientes`) | Int. 1 |
| Int. 2 | Mostrar el código del paquete en la matriz | `Celda::getCodigoPaquete()` (hoy devuelve `"OCUPADA"`; hay un `TODO` para cambiarlo por `paquete->getCodigo()`) | Int. 2 lo completa |

> Si alguien necesita un método que no está en esta tabla, se lo pide al dueño de la clase en el grupo.

### Calendario

| Fecha | Meta |
| --- | --- |
| Dom 25 – Lun 26 oct | Todos los `.h` escritos, acordados y subidos. Int. 1 sube `Fecha`, `Validaciones` y `ListaClientes`. Int. 2 sube `Paquete.h` (lo necesita el Int. 3). |
| Mar 27 – Jue 29 oct | Cada uno implementa su módulo, sus listas y su submenú. |
| Vie 30 oct | Integración en `main`, `cargarDatosPrueba()` completo, primeras pruebas cruzadas. |
| Sáb 31 oct | Reportes, pruebas de todos los flujos, diagrama final y `integrantes.txt`. |
| Dom 1 nov | Revisión final y entrega **antes de las 11:59 p. m.** |

---

## 4. Explicación de cada clase

> Formato: **Qué es** · **Qué guarda** · **Qué debe hacer** · **Cuidado con**

### 4.1 Clases base (Integrante 1)

#### Listas enlazadas (una por tipo)

- **Qué es:** cada colección tiene su propia lista simplemente enlazada, como `ListaMateriales` (semana 12). No usamos `template`.
- **Listas del proyecto:**

| Lista | Guarda | Busca por | Dueño |
|---|---|---|---|
| `ListaCentros` | `CentroDistribucion*` | código | Int. 1 |
| `ListaClientes` | `Cliente*` (lista **polimórfica**: físicos y empresas) | identificación | Int. 1 |
| `ListaColaboradores` | `Colaborador*` | identificación | Int. 1 |
| `ListaBodegas` | `Bodega*` | código | Int. 1 |
| `ListaPaquetes` | `Paquete*` | código | Int. 2 |
| `ListaBitacora` | `RegistroBitacora*` | — (no se busca ni se elimina) | Int. 2 |
| `ListaSolicitudes` | `SolicitudEnvio*` | código | Int. 3 |
| `ListaDespachos` | `Despacho*` | código | Int. 3 |

- **Todas tienen los mismos métodos:** `insertarFinal(x)`, `buscar(codigo)`, `eliminar(x)`, `getPrimero()`, `getCantidad()`, `estaVacia()` y `toString()` (devuelve el texto de todos los elementos, o "No hay … registrados." si está vacía). `ListaBitacora` no tiene `buscar` ni `eliminar`, porque sus registros nunca se eliminan.
- **El nodo va en el mismo archivo que su lista** (`NodoCliente` dentro de `ListaClientes.h/.cpp`), porque solo esa lista lo usa.
- **Cuidado con:**
  - El destructor de la lista **solo borra los nodos**, no los objetos a los que apuntan (agregación, como en la semana 10). Los objetos los borra su dueño (ver [6.6](#66-memoria-dinámica-quién-borra-qué)).
  - `eliminar(x)` **solo quita el nodo**. El `delete` del objeto lo hace quien llamó.
  - Insertar **al final** es importante, porque el reporte de clientes respeta "el orden en que aparecen en la lista" y la bitácora va "del más antiguo al más reciente".
  - Las búsquedas viven **dentro de la lista** (`clientes.buscar(id)`) y `CentroDistribucion` solo delega. Así respetamos la Ley de Demeter (semana 13).

**Modelo que todos copian** (`ListaClientes`):

```cpp
// ListaClientes.h
#ifndef LISTACLIENTES_H
#define LISTACLIENTES_H

#include <string>

class Cliente;   // solo usamos punteros

// Nodo de la lista: guarda un Cliente* y el siguiente nodo.
class NodoCliente {
private:
    Cliente* dato;
    NodoCliente* siguiente;

public:
    NodoCliente(Cliente* dato);
    Cliente* getDato();
    NodoCliente* getSiguiente();
    void setSiguiente(NodoCliente* siguiente);
};

// Lista simplemente enlazada de clientes (agregacion: no borra los clientes).
class ListaClientes {
private:
    NodoCliente* primero;
    int cantidad;

public:
    ListaClientes();
    ~ListaClientes();

    void insertarFinal(Cliente* cliente);
    // Devuelve el cliente con esa identificacion o nullptr si no existe.
    Cliente* buscar(std::string identificacion);
    // Quita el nodo del cliente. NO hace delete del cliente.
    bool eliminar(Cliente* cliente);

    NodoCliente* getPrimero();
    int getCantidad();
    bool estaVacia();
};

#endif
```

```cpp
// ListaClientes.cpp (partes principales)

// Libera solo los nodos. Los clientes los borra CentroDistribucion.
ListaClientes::~ListaClientes() {
    NodoCliente* actual = primero;
    while (actual != nullptr) {
        NodoCliente* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
}

// Inserta al final para respetar el orden de llegada.
void ListaClientes::insertarFinal(Cliente* cliente) {
    NodoCliente* nuevo = new NodoCliente(cliente);
    if (primero == nullptr) {
        primero = nuevo;
    } else {
        NodoCliente* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

bool ListaClientes::eliminar(Cliente* cliente) {
    NodoCliente* anterior = nullptr;
    NodoCliente* actual = primero;
    while (actual != nullptr && actual->getDato() != cliente) {
        anterior = actual;
        actual = actual->getSiguiente();
    }
    if (actual == nullptr) {
        return false;                         // no estaba en la lista
    }
    if (anterior == nullptr) {
        primero = actual->getSiguiente();     // era el primero
    } else {
        anterior->setSiguiente(actual->getSiguiente());
    }
    delete actual;                            // borra el nodo, no el cliente
    cantidad--;
    return true;
}
```

Ejemplo de recorrido (todos lo hacemos igual):
```cpp
NodoCliente* actual = clientes.getPrimero();
while (actual != nullptr) {
    Cliente* c = actual->getDato();
    // ... usar c ...
    actual = actual->getSiguiente();
}
```

#### `Fecha`
- **Qué es:** una fecha con hora.
- **Qué guarda:** `dia`, `mes`, `anio`, `hora` y `minuto`.
- **Qué debe hacer:** construirse con esos valores y devolver un texto con `toString()`. El formato está en [6.8](#68-formatos-de-salida).
- **Cuidado con:** validar que el día esté entre 1 y 31, el mes entre 1 y 12, la hora entre 0 y 23 y los minutos entre 0 y 59. Eso lo hace `Validaciones::leerFecha`.

#### `Validaciones`
- **Qué es:** funciones `static` para pedirle datos al usuario **sin que el programa se caiga**.
- **Qué tiene (ya programado):**

| Función | Qué hace |
|---|---|
| `leerEntero(msg, min, max)` | Repite la pregunta hasta que el usuario escriba un entero dentro del rango. Rechaza letras, decimales, vacíos y números que no caben en un `int`. |
| `leerDouble(msg, min)` | Repite hasta recibir un número **mayor** que `min`. Acepta coma decimal (`1,5` = `1.5`). Para el **peso**. |
| `leerDoubleRango(msg, min, max)` | Igual, pero acepta de `min` a `max` **incluidos**. Para el **descuento** (0 a 100). |
| `leerTexto(msg, maximo = 100)` | Lee con `getline`, quita espacios y tabulaciones al inicio y al final, no acepta texto vacío ni más de `maximo` caracteres. Así `" PK001 "` se toma como `"PK001"`. |
| `leerTelefono(msg)` | Solo números, de 8 a 15 dígitos. |
| `leerCorreo(msg)` | Un solo `@`, que no vaya de primero, un punto después del `@` y sin espacios. |
| `leerFecha(msg)` | Pide día, mes, año (1950–2100), hora y minuto. Revisa los días de cada mes y los años bisiestos: **no acepta 31/02**. Para bitácora, solicitudes y despachos. |
| `leerFechaSinHora(msg)` | Igual, pero sin hora (queda 00:00). La usa la fecha de ingreso del colaborador. |
| `confirmar(pregunta)` | Pregunta `(s/n)` hasta que respondan `s`/`S` o `n`/`N`. Para confirmar registros y eliminaciones, como en el Proyecto 1. |
| `quitarEspacios(texto)` y `diasDelMes(mes, anio)` | Ayudas que usan las anteriores. |

- **Cuidado con:** mezclar `cin >>` con `getline` deja un salto de línea pendiente. Por eso **todas** las lecturas se hacen con `getline` y después se convierten con `stringstream`. **Nadie usa `cin >>` directamente en los menús.**
- **Probado (pruebas del Integrante 1):** letras, decimales, vacíos, solo espacios, tabulaciones, números gigantes (`99999999999`, `1e400`), coma decimal, fin de línea de Windows (`\r\n`), textos de 100 000 caracteres, tildes y ñ. Pasan todas.
- **Limitaciones conocidas** (no estaban en el Proyecto 1, se dejan así):
  - Si se cierra la entrada (Ctrl+Z en Windows), el ciclo pregunta para siempre.
  - `leerFecha` no compara con la fecha de hoy (haría falta `<ctime>`, que no se vio), así que acepta fechas futuras.

```cpp
// Quita espacios y tabulaciones al inicio y al final del texto.
string Validaciones::quitarEspacios(string texto) {
    size_t inicio = texto.find_first_not_of(" \t\r");
    if (inicio == string::npos) {
        return "";
    }
    size_t fin = texto.find_last_not_of(" \t\r");
    return texto.substr(inicio, fin - inicio + 1);
}

// Pide un entero hasta que el usuario escriba uno valido dentro del rango.
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

// Pide un numero mayor que "minimo". Acepta coma o punto decimal.
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

// Pide un texto que no este vacio y que no pase de "maximo" caracteres.
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
```

#### Estados y categorías (ya no hay `Constantes.h`)
- **Categorías y tipos de bodega:** un `int` del **1 al 4** (1 General, 2 Frágil, 3 Tecnología, 4 Documentos). Se guarda igual en el paquete y en la bodega, así la compatibilidad es `bodega->getTipo() == paquete->getCategoria()`.
- **Para mostrarlos**, cada clase tiene su método con `if / else if`. `Bodega` ya tiene `getNombreTipo()`; el Integrante 2 hace lo mismo en `Paquete` (`getNombreCategoria()`):

```cpp
string Bodega::getNombreTipo() {
    if (tipo == 1) {
        return "General";
    } else if (tipo == 2) {
        return "Fragil";
    } else if (tipo == 3) {
        return "Tecnologia";
    } else if (tipo == 4) {
        return "Documentos";
    }
    return "Desconocido";
}
```

- **Estados:** se guardan como **texto** (`std::string`), igual que `"Esperando"`, `"Asignado"` y `"Cancelado"` en el Proyecto 1. Siempre se escriben **exactamente así** (sin tildes, primera letra en mayúscula):

| Clase | Estados |
|---|---|
| `Paquete` | `"Recibido"`, `"Almacenado"`, `"En transito"`, `"Entregado"`, `"Incidencia"` |
| `SolicitudEnvio` | `"Pendiente"`, `"Aprobada"`, `"Rechazada"`, `"Anulada"` |
| `Despacho` | `"En proceso"`, `"Finalizado"` |

- **Cuidado con:** `"Almacenado"` y `"almacenado"` son textos distintos. Si alguien escribe mal un estado, la comparación da `false` sin avisar. Copien los textos de esta tabla.

### 4.2 Núcleo (Integrante 1)

#### `Sistema`
- **Qué es:** la "empresa" TicoPack. Hay **un solo** objeto de esta clase y lo crea `main`.
- **Qué guarda:** una `ListaCentros`.
- **Qué tiene (ya programado):**
  - `agregarCentro`, `buscarCentro`, `eliminarCentro` (primero pregunta `centro->puedeEliminarse()`), `listarCentros`, `listarCodigosCentros` (lista corta que ve el usuario al escoger un centro) y `tieneCentros`.
  - `existePaquete`, `existeSolicitud` y `existeDespacho`: recorren **todos** los centros. **Pendiente:** cada una tiene comentada la línea que llama a `buscarPaquete` / `buscarSolicitud` / `buscarDespacho`; el Int. 2 y el Int. 3 la descomentan cuando existan esos métodos. Mientras tanto devuelven `false`.
  - `cargarDatosPrueba()`: ya trae la parte del Integrante 1 (ver [6.9](#69-datos-de-prueba-cargardatosprueba)). Si `C01` ya existe, no carga nada otra vez.
- **Cuidado con:** el destructor de `Sistema` borra los centros.

#### `CentroDistribucion`
- **Qué es:** un centro de distribución. Es la clase **más importante**, porque es dueña de todas las listas y ahí vive la lógica de las operaciones.
- **Qué guarda:** código, nombre, provincia, dirección, teléfono y **6 listas**: `ListaClientes`, `ListaColaboradores`, `ListaBodegas`, `ListaPaquetes`, `ListaSolicitudes` y `ListaDespachos`.
- **Qué debe hacer:** está dividida en 3 partes, una por integrante:
  - **Parte 1 (Integrante 1, listo):** para clientes, colaboradores y bodegas hay `agregarX(x)`, `buscarX(id)`, `puedeEliminarX(x)` (imprime el motivo si no se puede), `eliminarX(x)` (quita de la lista y hace `delete`) y `listarX()`. También `puedeEliminarse()`, `getClientes()` (para el Int. 3) y `getBodegas()` (para el reporte de ocupación).
  - Las revisiones que dependen de los otros (por ejemplo `paquetes.tieneDeCliente(cliente)` dentro de `puedeEliminarCliente`) ya están escritas **como comentario** con `// TODO Integrante 2` o `// TODO Integrante 3`. Solo hay que descomentarlas.
  - **Parte 2 (Integrante 2):** paquetes, almacenar, recomendar, reubicar e incidencias.
  - **Parte 3 (Integrante 3):** crear, aprobar, rechazar y anular solicitudes, y finalizar despachos.
- **Cuidado con:**
  - Como 3 personas escriben en el mismo `.cpp`, **cada quien escribe solo debajo de su comentario de sección** (ver [6.10](#610-trabajo-en-equipo-y-git)).
  - Las búsquedas solo delegan en la lista: `return clientes.buscar(id);`.
  - El destructor borra los objetos de **todas** sus listas, en este orden: despachos, solicitudes, paquetes, bodegas, colaboradores y clientes. Después, cada lista borra sus nodos sola.

```cpp
// Ejemplo: borrar los clientes en el destructor del centro
NodoCliente* actual = clientes.getPrimero();
while (actual != nullptr) {
    delete actual->getDato();   // borra el cliente (destructor virtual)
    actual = actual->getSiguiente();
}
// los nodos los borra el destructor de ListaClientes
```

### 4.3 Personas (Integrante 1)

#### `Cliente` (abstracta)
- **Qué es:** la clase padre de los dos tipos de cliente. No se pueden crear objetos `Cliente` directamente.
- **Qué guarda (`protected`):** identificación, nombre, teléfono y correo.
- **Qué debe hacer:**
  - `getTipo()`: método **virtual puro** que devuelve `"Fisico"` o `"Empresa"`.
  - `aplicarDescuento(costoBase)`: método **virtual**. Por defecto devuelve el mismo costo, sin descuento.
  - `toString()`: método **virtual** que devuelve los datos comunes. `mostrar()` lo imprime.
- **Cuidado con:** el **destructor virtual** (`virtual ~Cliente() {}`) es obligatorio. Sin él, borrar un `Cliente*` que en realidad es una `ClienteEmpresa` no libera bien la memoria (semana 9 y 15).

#### `ClienteFisico`
- **Qué es:** un cliente persona física. No agrega atributos.
- **Qué debe hacer:** implementar `getTipo()` con `override`. No necesita su propio `toString()`.

#### `ClienteEmpresa`
- **Qué es:** un cliente empresa.
- **Qué guarda (además):** actividad económica y porcentaje de descuento (0 a 100).
- **Qué debe hacer:** **sobrescribir `aplicarDescuento`** para que devuelva `costoBase - costoBase * porcentajeDescuento / 100`, y `toString()`, que llama a `Cliente::toString()` y agrega la actividad y el descuento. Si le llega un descuento fuera de 0–100, lo deja en 0 o en 100.
- **Cuidado con:** esto es **polimorfismo**. Así, `SolicitudEnvio` no necesita preguntar con un `if` ni con `dynamic_cast` si el cliente es empresa, solo llama a `cliente->aplicarDescuento(base)`. Es algo que el profesor puede preguntar en la defensa (semana 15: "cambiar un if-else por polimorfismo").

#### `Colaborador`
- **Qué es:** un empleado del centro.
- **Qué guarda:** identificación, nombre completo, fecha de ingreso y puesto.
- **Qué debe hacer:** `toString()` y `mostrar()`. Aparece como "responsable" en la bitácora, en las solicitudes y en los despachos.

### 4.4 Bodegas (Integrante 1)

#### `Celda`
- **Qué es:** una posición de la bodega.
- **Qué guarda:** un `Paquete*`. Si vale `nullptr`, la celda está **libre**.
- **Qué debe hacer:** `estaLibre()`, `ocupar(p)`, `liberar()`, `getPaquete()` y `getCodigoPaquete()` (devuelve `"LIBRE"` o el código del paquete; el Int. 2 completa esa línea cuando exista `Paquete.h`).
- **Cuidado con:** la celda **nunca** hace `delete` del paquete, solo lo apunta.

#### `Bodega`
- **Qué es:** una bodega organizada en filas y columnas.
- **Qué guarda:** código, nombre, tipo (1 a 4), filas, columnas y `Celda** matriz`. Tamaño permitido en el menú: **1 a 30 filas** y **1 a 10 columnas** (para que la matriz quepa en la consola).
- **Qué debe hacer:**
  - **Constructor:** reservar la matriz con `new` (ver el código abajo).
  - **Destructor:** liberar la matriz con `delete[]`, primero las filas y luego el arreglo de punteros.
  - `posicionValida(f, c)`: `0 <= f < filas` y `0 <= c < columnas`.
  - `estaLibre`, `asignar`, `liberar` y `getPaquete` sobre una posición.
  - `totalCeldas()`, `celdasOcupadas()`, `celdasLibres()`, `porcentajeOcupacion()`, `porcentajeDisponible()` y `estaVacia()` (todas las celdas libres).
  - `primeraCeldaLibre(f, c)`: recorre fila por fila y devuelve la primera celda libre (por referencia). Devuelve `false` si está llena.
  - `getNombreTipo()`, `nombreCelda(f, c)` (`"A-1-2"`) y `mostrarMatriz()`, que dibuja la bodega en consola (formato en [6.8](#68-formatos-de-salida)).
- **Cuidado con:**
  - `asignar` y `liberar` **siempre** validan primero la posición.
  - **Regla de los Tres (semana 14):** como `Bodega` maneja memoria dinámica, una copia por defecto haría que dos bodegas compartan la misma matriz y se borre dos veces. Las bodegas **siempre se manejan por puntero (`Bodega*`) y nunca se copian**. Si el profe pregunta, eso es lo que hay que explicar.

```cpp
// Constructor
matriz = new Celda*[filas];
for (int i = 0; i < filas; i++)
    matriz[i] = new Celda[columnas];

// Destructor
for (int i = 0; i < filas; i++)
    delete[] matriz[i];
delete[] matriz;
matriz = nullptr;
```

### 4.5 Paquetes (Integrante 2)

#### `Paquete`
- **Qué es:** un paquete que la empresa recibe.
- **Qué guarda:** código, descripción, peso, categoría (`int` 1 a 4), estado (`string`), código del centro, `propietario` (Cliente\*), `bodega` (Bodega\*, `nullptr` si no está guardado), `fila`, `columna` (−1 si no tiene), la `bitacora` (`ListaBitacora`) y `tieneDespacho`.
- **Qué debe hacer:**
  - `puedeCambiarA(nuevo)`: revisa la tabla de transiciones con `if` (ver el código abajo).
  - `cambiarEstado(nuevo, fecha, responsable)`: si la transición es válida, crea un `RegistroBitacora`, lo agrega a la bitácora y cambia el estado. **No mueve celdas**, eso lo hacen las operaciones.
  - `asignarUbicacion(b, f, c)`: guarda dónde está el paquete.
  - `quitarUbicacion()`: **libera la celda en la bodega** (`bodega->liberar(fila, columna)`) y pone `bodega = nullptr`, `fila = columna = -1`.
  - `tieneUbicacion()`: devuelve `bodega != nullptr`.
  - `tieneRegistroDe(col)`: dice si el colaborador aparece en la bitácora (lo usa el Int. 1 para eliminar colaboradores).
  - `getNombreCategoria()`, `mostrar()` y `mostrarBitacora()`.
- **Cuidado con:**
  - El destructor borra los registros de su bitácora (el `Paquete` es dueño de sus registros).
  - Un paquete nuevo empieza en `"Recibido"`, sin bodega y **sin registros en la bitácora**, porque todavía no hubo un cambio de estado.

```cpp
// Revisa la tabla de transiciones del enunciado.
bool Paquete::puedeCambiarA(string nuevo) {
    if (estado == "Recibido") {
        return nuevo == "Almacenado" || nuevo == "Incidencia";
    } else if (estado == "Almacenado") {
        return nuevo == "En transito" || nuevo == "Incidencia";
    } else if (estado == "En transito") {
        return nuevo == "Entregado" || nuevo == "Incidencia";
    } else if (estado == "Incidencia") {
        return nuevo == "Almacenado" || nuevo == "En transito";
    }
    return false;          // "Entregado" ya no cambia
}
```

#### `RegistroBitacora`
- **Qué es:** una línea del historial de un paquete.
- **Qué guarda:** estado anterior, estado nuevo, fecha y colaborador responsable.
- **Qué debe hacer:** `mostrar()`.
- **Cuidado con:** **nunca** se modifica ni se elimina. Solo tiene getters, sin setters.

#### `ListaPaquetes` y `ListaBitacora`
- Siguen el modelo de `ListaClientes` ([4.1](#41-clases-base-integrante-1)).
- `ListaPaquetes` agrega los métodos que necesita el Int. 1: `tieneDeCliente(c)`, `tieneEnBodega(b)` y `colaboradorEnBitacoras(col)`.
- `ListaBitacora` solo tiene `insertarFinal`, `getPrimero`, `getCantidad` y `tieneRegistroDe(col)`, que usa `Paquete::tieneRegistroDe`.

### 4.6 Solicitudes y despachos (Integrante 3)

#### `Tarifas`
- **Qué es:** una clase que solo tiene datos compartidos (`static`), como pide el enunciado.
- **Qué guarda:** las cuatro tarifas como `static const double`.
- **Qué debe hacer:** `obtener(categoria)` devuelve la tarifa que corresponde.
- **Cuidado con:**
  - El enunciado exige que **nadie escriba 1500 u otra tarifa directamente** en otro lugar del código.
  - En C++ un `static const double` **no se puede inicializar dentro de la clase**: se declara en el `.h` y se le da valor en el `.cpp`. Si se escribe `static const double GENERAL = 1500;` dentro de la clase, **no compila**.
  - Se llaman `TARIFA_…` para no confundirlas con las constantes de categoría.

```cpp
// Tarifas.h
class Tarifas {
public:
    static const double TARIFA_GENERAL;
    static const double TARIFA_FRAGIL;
    static const double TARIFA_TECNOLOGIA;
    static const double TARIFA_DOCUMENTOS;

    // Devuelve la tarifa por kilogramo de una categoria.
    static double obtener(int categoria);
};

// Tarifas.cpp
const double Tarifas::TARIFA_GENERAL = 1500;
const double Tarifas::TARIFA_FRAGIL = 2000;
const double Tarifas::TARIFA_TECNOLOGIA = 2500;
const double Tarifas::TARIFA_DOCUMENTOS = 1000;
```

#### `SolicitudEnvio`
- **Qué es:** el pedido para enviar un paquete.
- **Qué guarda:** código, cliente, paquete, responsable, código del centro de origen, destino (texto), fecha, costo estimado y estado.
- **Qué debe hacer:**
  - `calcularCosto()`: calcula `base = peso * Tarifas::obtener(categoria)` y devuelve `cliente->aplicarDescuento(base)`. El resultado se guarda en `costoEstimado` al crear la solicitud.
  - `cambiarEstado(nuevo)`: solo permite pasar de `"Pendiente"` a otro estado.
  - `mostrar()`.

#### `Despacho`
- **Qué es:** el envío real del paquete. Se crea **solo** al aprobar una solicitud.
- **Qué guarda:** código, solicitud, paquete, cliente, responsable, centro de origen, destino, fecha con hora y estado.
- **Qué debe hacer:** `finalizar()`, que cambia el estado a `"Finalizado"`, y `mostrar()`.
- **Cuidado con:** el cliente, el paquete, el responsable y el destino se copian de la solicitud **al crearlo**, para no tener que hacer cadenas como `d->getSolicitud()->getPaquete()->...` (Ley de Demeter).

#### `ListaSolicitudes` y `ListaDespachos`
- Siguen el modelo de `ListaClientes` ([4.1](#41-clases-base-integrante-1)).
- Agregan los métodos que necesitan los demás: `tieneDeCliente(c)`, `tieneDeResponsable(col)` y, en `ListaSolicitudes`, `tieneDePaquete(p)` y `tienePendiente(p)`.

#### `Reportes`
- **Qué es:** funciones `static` que imprimen los 6 reportes.

| Reporte | Quién | Qué hace |
|---|---|---|
| `historialCliente` | Int. 3 | Recorre las solicitudes y los despachos del centro y muestra los de ese cliente: código, paquete, fecha y estado. |
| `clientesPorEnvios` | Int. 3 | Cuenta los despachos **finalizados** de cada cliente y los ordena de mayor a menor con **burbuja** (ver abajo). |
| `bitacoraPaquete` | Int. 2 | Muestra la bitácora en orden: anterior, nuevo, fecha y colaborador. |
| `despachoDePaquete` | Int. 3 | Busca la solicitud *Aprobada* y el despacho de ese paquete. Si no tiene, lo indica. |
| `ocupacionBodegas` | Int. 1 (listo) | Para cada bodega del centro: total de celdas, ocupadas, libres y % de ocupación, más el total del centro. |
| `despachosPorColaborador` | Int. 3 | Muestra los despachos donde ese colaborador es el responsable. |

**Ordenamiento de `clientesPorEnvios`:** copiar los clientes a un arreglo dinámico (`Cliente** arr = new Cliente*[n]`) junto con un arreglo `int* cant = new int[n]`. Después se aplica **burbuja** con comparación **estricta** (`if (cant[j] < cant[j+1])` → intercambiar). Así, cuando hay empate, se mantiene el orden original. Al final se hace `delete[]` de ambos arreglos.

### 4.7 Interfaz (Integrante 1 + cada uno su submenú)

#### `Menu`
- **Qué es:** toda la interacción con el usuario.
- **Qué guarda:** un puntero a `Sistema`.
- **Qué debe hacer:** mostrar el menú principal y llamar a cada submenú. Cada integrante programa **sus** submenús.
- **Ya está (Integrante 1):** menú principal, submenús de centros, clientes, colaboradores y bodegas, y el menú de reportes con la opción 5. Las opciones 5, 6 y 7 del menú principal dicen "todavía no está disponible" y tienen un `// TODO` para cambiarlas por `menuPaquetes()`, `menuSolicitudes()` y `menuDespachos()`.
- **Ayudas que pueden usar todos:** `pedirCentro()` (muestra los centros y devuelve `nullptr` si el código no existe), `pedirTipoBodega()`, `pedirProvincia()`, `pausar()` y `limpiarPantalla()`.
- Los submenús de clientes, colaboradores y bodegas piden el centro **una vez al entrar** y trabajan sobre ese centro. Hagan lo mismo en sus submenús.
- **Cuidado con:** el menú **pide y muestra datos**. La lógica (validar reglas, cambiar estados, mover celdas) está en las clases. Ver [6.4](#64-separación-menú--lógica).

#### `main.cpp`
Debe quedar así de corto:
```cpp
int main() {
    Sistema sistema;
    sistema.cargarDatosPrueba();
    Menu menu(&sistema);
    menu.ejecutar();
    return 0;
}
```

---

## 5. Flujos importantes paso a paso

Estos flujos conectan el trabajo de varios integrantes. **Respétenlos tal cual** para que las piezas encajen.

### 5.1 Registrar un paquete (Int. 2)
1. El menú pide el centro y verifica que exista.
2. Pide el código y verifica que `sistema->existePaquete(codigo)` sea `false`.
3. Pide descripción (no vacía), peso (> 0), categoría (1–4) y el cliente, que debe existir **en ese centro**.
4. Crea `new Paquete(...)` con estado `"Recibido"`, sin bodega y con la bitácora vacía.
5. `centro->agregarPaquete(p)`.

### 5.2 Almacenar un paquete (Int. 2, usa `Bodega` del Int. 1)
1. Solo se permite si el paquete está `"Recibido"`, o en `"Incidencia"` sin ubicación y sin despacho.
2. `centro->recomendarBodega(categoria)`: entre las bodegas **del mismo tipo** que tengan al menos una celda libre, elige la de **mayor `porcentajeDisponible()`**. Si hay empate, gana la primera de la lista.
3. Si no hay ninguna, se informa al usuario y **no se cambia nada**.
4. Se recomienda `bodega->primeraCeldaLibre(f, c)` y se muestra la matriz.
5. El usuario acepta la recomendación o escoge otra bodega compatible y otra celda libre.
6. Se pide el colaborador responsable, que debe ser del mismo centro.
7. `bodega->asignar(f, c, p)` → `p->asignarUbicacion(b, f, c)` → `p->cambiarEstado("Almacenado", fecha, colaborador)`.

### 5.3 Reubicar un paquete (Int. 2)
1. El paquete tiene que estar `"Almacenado"`.
2. Se valida el destino: la bodega existe en el centro, es compatible, la posición es válida, la celda está libre y no es la misma celda actual.
3. **Solo si todo es válido:** `p->quitarUbicacion()` → `nueva->asignar(f, c, p)` → `p->asignarUbicacion(nueva, f, c)`.
4. Si algo falla, **no se toca nada**. El estado no cambia y no se escribe en la bitácora.

### 5.4 Crear una solicitud (Int. 3)
1. Verificar que el código no exista (`sistema->existeSolicitud`).
2. El paquete tiene que estar `"Almacenado"`, sin solicitud `"Pendiente"` (`centro->tieneSolicitudPendiente(p)`) y con `!p->getTieneDespacho()`.
3. El cliente es el propietario del paquete (se toma de `p->getPropietario()`). El responsable debe ser del mismo centro.
4. Se crea la solicitud con estado `"Pendiente"` y se calcula el costo con `calcularCosto()`.

### 5.5 Aprobar una solicitud (Int. 3, usa `Paquete` del Int. 2)
1. Validar: la solicitud está `"Pendiente"`, el paquete está `"Almacenado"` y `!p->getTieneDespacho()`.
2. Verificar que el código de despacho no exista (`sistema->existeDespacho`).
3. `s->cambiarEstado("Aprobada")`.
4. Crear `new Despacho(...)` con estado `"En proceso"` y agregarlo a la lista del centro.
5. `p->quitarUbicacion()`, que libera la celda.
6. `p->cambiarEstado("En transito", fecha, s->getResponsable())`.
7. `p->setTieneDespacho(true)`.

### 5.6 Finalizar un despacho (Int. 3)
1. Validar: el despacho está `"En proceso"` y el paquete está `"En transito"`.
2. `d->finalizar()` → `p->cambiarEstado("Entregado", fecha, d->getResponsable())`.

### 5.7 Incidencias (Int. 2)
- **Registrar:** se permite desde `"Recibido"`, `"Almacenado"` o `"En transito"`. Se llama a `p->cambiarEstado("Incidencia", ...)` y **no se toca la celda**.
- **Resolver:**
  - Si `p->tieneUbicacion()`, pasa a `"Almacenado"`.
  - Si no, y `p->getTieneDespacho()`, pasa a `"En transito"`.
  - Si no tiene ninguna de las dos, se avisa: *"Use la opción Almacenar paquete"*.
- La opción general de "cambiar estado" del menú de paquetes **solo** permite registrar y resolver incidencias. Así no se pueden saltar las operaciones obligatorias.

---

## 6. Convenciones del equipo

### 6.1 Nombres

| Elemento | Estilo | Ejemplo |
|---|---|---|
| Clases | `PascalCase` | `CentroDistribucion`, `SolicitudEnvio` |
| Listas y nodos | `Lista` / `Nodo` + tipo | `ListaPaquetes`, `NodoPaquete` |
| Métodos y funciones | `camelCase`, empiezan con verbo | `buscarCliente()`, `calcularCosto()` |
| Atributos y variables | `camelCase` | `porcentajeDescuento`, `codigoCentro` |
| Constantes | `MAYUSCULAS_CON_GUION` | `TARIFA_FRAGIL`, `MAXIMO_FILAS` |
| Getters / setters | `getX()` / `setX()` | `getCodigo()`, `setEstado()` |
| Booleanos | `es…`, `esta…`, `tiene…`, `puede…` | `estaLibre()`, `tieneDespacho`, `puedeEliminarse()` |
| Archivos | Igual que la clase | `ClienteEmpresa.h`, `ClienteEmpresa.cpp` |

- Todo el código va en **español y sin tildes ni ñ** en los identificadores: `anio`, no `año`.
- Usen nombres claros, nada de `x`, `aux2` ni `temp3`. Las únicas excepciones son `i` y `j` en los `for`, y `f` y `c` para fila y columna.

### 6.2 Estructura de archivos

```
TicoPack/
├── main.cpp
├── Fecha.h / .cpp
├── Validaciones.h / .cpp
├── Sistema.h / .cpp
├── CentroDistribucion.h / .cpp
├── Cliente.h / .cpp
├── ClienteFisico.h / .cpp
├── ClienteEmpresa.h / .cpp
├── Colaborador.h / .cpp
├── Celda.h / .cpp
├── Bodega.h / .cpp
├── Paquete.h / .cpp
├── RegistroBitacora.h / .cpp
├── Tarifas.h / .cpp
├── SolicitudEnvio.h / .cpp
├── Despacho.h / .cpp
├── Reportes.h / .cpp
├── Menu.h / .cpp
├── ListaCentros.h / .cpp        (incluye NodoCentro)
├── ListaClientes.h / .cpp       (incluye NodoCliente)
├── ListaColaboradores.h / .cpp  (incluye NodoColaborador)
├── ListaBodegas.h / .cpp        (incluye NodoBodega)
├── ListaPaquetes.h / .cpp       (incluye NodoPaquete)
├── ListaBitacora.h / .cpp       (incluye NodoBitacora)
├── ListaSolicitudes.h / .cpp    (incluye NodoSolicitud)
├── ListaDespachos.h / .cpp      (incluye NodoDespacho)
└── docs/
    ├── diagramas (.puml y .png)
    ├── GUIA_EQUIPO.md
    └── integrantes.txt
```

- **Una clase = un `.h` + un `.cpp`.** La única excepción son los nodos, que van junto a su lista.
- El `.h` tiene la declaración (atributos y firmas). El `.cpp` tiene el código.

### 6.3 Plantilla de un `.h`

```cpp
#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>
#include "Fecha.h"
#include "ListaBitacora.h"

class Cliente;      // declaraciones adelantadas: solo usamos punteros
class Bodega;
class Colaborador;

class Paquete {
private:
    std::string codigo;
    // ...
    ListaBitacora bitacora;

public:
    Paquete(std::string codigo, std::string descripcion, double peso,
            int categoria, Cliente* propietario, std::string codigoCentro);
    ~Paquete();

    // Getters
    std::string getCodigo();
    // ...

    // Cambia el estado si la tabla lo permite y lo registra en la bitacora.
    bool cambiarEstado(std::string nuevo, Fecha fecha, Colaborador* responsable);
};

#endif
```

**Reglas de los `.h`:**
- Siempre llevan **include guards** (`#ifndef NOMBRE_H` / `#define` / `#endif`).
- **No ponemos `using namespace std;` en los `.h`**: ahí escribimos `std::string`. En los `.cpp` sí se puede usar.
- Si solo se usa un **puntero** a otra clase, se pone `class OtraClase;` en el `.h` y el `#include` en el `.cpp`. Así se evitan los includes circulares (`Celda` ↔ `Paquete`, `Paquete` ↔ `Bodega`).
- Si se guarda un **objeto completo** (como `ListaBitacora bitacora;` dentro de `Paquete`), sí hay que hacer el `#include` en el `.h`.
- Los atributos son **`private`**. En `Cliente` son `protected` por la herencia.
- Va una línea de comentario arriba de cada método que no sea obvio.

### 6.4 Separación menú / lógica

| El **Menú** se encarga de… | Las **clases** se encargan de… |
|---|---|
| Pedir datos con `Validaciones::leer…` | Validar las reglas del negocio |
| Verificar códigos globales con `Sistema` | Cambiar estados y escribir en la bitácora |
| Buscar los objetos (centro, cliente…) y avisar si no existen | Mover paquetes entre celdas |
| Mostrar mensajes de éxito | Crear y borrar objetos de sus listas |

**Convención de retorno:**
- Las operaciones que pueden fallar devuelven **`bool`**: `true` si salió bien y `false` si no.
- Si fallan, **el mismo método imprime el motivo** con el formato `Error: <motivo>`.
- Las búsquedas devuelven un **puntero**, o **`nullptr`** si no encuentran nada. Las búsquedas **no imprimen nada**.
- Las funciones **`agregar…`** (`agregarCentro`, `agregarCliente`, `agregarBodega`, …) devuelven `false` si el código ya existe y en ese caso **hacen `delete` del objeto** (igual que `registrarCancha` del Proyecto 1). Después de un `false`, **no vuelvan a usar ese puntero**. Hagan lo mismo en `agregarPaquete`, `crearSolicitud`, etc.
- Antes de eliminar, el menú llama a `puedeEliminarX(x)`, muestra los datos, pide `Validaciones::confirmar(...)` y solo entonces llama a `eliminarX(x)`.

```cpp
// En Menu
Paquete* p = centro->buscarPaquete(codigo);
if (p == nullptr) {
    cout << "Error: no existe un paquete con ese codigo." << endl;
} else if (centro->almacenarPaquete(p, b, fila, columna, fecha, col)) {
    cout << "Paquete almacenado correctamente." << endl;
}
```

**Ley de Demeter (semana 13):** cada objeto le habla solo a sus "amigos directos". Evitamos cadenas largas como `despacho->getSolicitud()->getPaquete()->getPropietario()->getNombre()`. Si hace falta un dato lejano, se agrega un método que lo dé directo o se guarda una copia del puntero al crear el objeto.

### 6.5 Estados y categorías

- **Estados = texto**, escrito exactamente como en la tabla de [4.1](#estados-y-categorías-ya-no-hay-constantesh): `p->getEstado() == "Almacenado"`.
- **Categorías y tipos = `int` del 1 al 4**, y cada clase los pasa a texto con su método (`getNombreTipo()`, `getNombreCategoria()`).
- Al pedirle una categoría o tipo al usuario, se muestra la lista numerada (ya lo hace `Menu::pedirTipoBodega()`):
  ```
  1. General   2. Fragil   3. Tecnologia   4. Documentos
  ```

### 6.6 Memoria dinámica: quién borra qué

> **Regla de oro:** **solo el dueño hace `delete`.** Quien solo apunta, nunca borra.

| Dueño | Borra en su destructor |
|---|---|
| `Sistema` | Los `CentroDistribucion` |
| `CentroDistribucion` | Despachos, solicitudes, paquetes, bodegas, colaboradores y clientes (en ese orden) |
| `Bodega` | Su matriz (`delete[]`) |
| `Paquete` | Sus `RegistroBitacora` |
| Cada `ListaX` | Solo sus **nodos** |

- `Celda`, `SolicitudEnvio`, `Despacho` y `RegistroBitacora` **solo apuntan**: nunca hacen `delete` de lo que apuntan.
- Al eliminar un elemento por el menú (por ejemplo, un cliente): primero se quita de la lista con `eliminar(x)` y después se hace `delete` del objeto.
- Todo `new X[n]` termina con `delete[]`, y todo `new X` con `delete`.
- Un puntero que ya no apunta a nada debe quedar en **`nullptr`**.
- **Regla de los Tres:** las listas, las bodegas, los paquetes y los centros **nunca se copian**; siempre se pasan por puntero. Así no hace falta escribir constructor copia ni `operator=`, y no hay riesgo de borrar la misma memoria dos veces.

### 6.7 Entrada de datos

- **Siempre** se usan las funciones de `Validaciones`. Nunca `cin >>` directo.
- Los textos se leen con `getline`, porque pueden tener espacios ("San José centro").
- Los códigos se comparan **tal cual**: `"PK001"` es distinto de `"pk001"`. Al pedirlos, se recuerda el formato al usuario.

### 6.8 Formatos de salida

| Dato | Formato | Ejemplo |
|---|---|---|
| Fecha | `dd/mm/aaaa` | `05/10/2026` |
| Fecha con hora | `dd/mm/aaaa hh:mm` | `05/10/2026 14:30` |
| Dinero | `CRC` + monto con 2 decimales | `CRC 7500.00` |
| Porcentaje | 2 decimales + `%` | `33.33%` |
| Celda | `BODEGA-fila-columna` | `A-1-2`, `A-10-3` |

- Usamos `A-1-2` en lugar de `A-12` porque el enunciado pide distinguir fila y columna cuando hay índices de 2 dígitos.
- Para los decimales: `#include <iomanip>` y `cout << fixed << setprecision(2);`.
- **Evitamos tildes, ñ y el símbolo ¢ en los mensajes de consola**, porque en Windows salen caracteres raros. Escribimos `Fragil`, `Tecnologia`, `CRC`.

**Matriz de bodega** (así la dibuja `Bodega::mostrarMatriz()`, con `\t` entre celdas y una línea en blanco entre filas, como el ejemplo del enunciado):
```
Bodega A - Bodega principal - General (4 x 5)

A-0-0	A-0-1	A-0-2	A-0-3	A-0-4
LIBRE	PK101	LIBRE	LIBRE	LIBRE

A-1-0	A-1-1	A-1-2	A-1-3	A-1-4
LIBRE	LIBRE	LIBRE	PK208	LIBRE
...
Ocupadas: 2/20 (10.00%)
```
- No usamos `setw` ni tablas alineadas. Los reportes muestran cada dato en su propia línea (`Total de celdas: 20`), como en el `Reporte` del Proyecto 1.

**Menús:** todos siguen el mismo formato.
```
===== MENU DE PAQUETES =====
1. Registrar paquete
2. Buscar paquete
3. Mostrar paquetes
4. Almacenar paquete
5. Reubicar paquete
6. Registrar / resolver incidencia
7. Eliminar paquete
0. Volver
Seleccione una opcion:
```
- La opción **`0`** siempre es *Volver* (o *Salir* en el menú principal).
- Después de cada operación se muestra `Presione Enter para continuar...`.
- Si un submenú necesita un centro, se pide el **código del centro** primero.

**Menú principal** (los grupos que exige el enunciado; ya está programado):
```
===== TICOPACK LOGISTICS - MENU PRINCIPAL =====
1. Centros de distribucion
2. Clientes
3. Colaboradores
4. Bodegas y matrices
5. Paquetes
6. Solicitudes de envio
7. Despachos
8. Reportes
0. Salir
```

### 6.9 Datos de prueba (`cargarDatosPrueba`)

Usamos los mismos formatos de código en todo el proyecto:

| Entidad | Formato | Ejemplos |
|---|---|---|
| Centro | `C` + 2 dígitos | `C01`, `C02` |
| Bodega | Letra | `A`, `B`, `C` |
| Cliente | Cédula / jurídica | `1-1111-1111`, `3-101-123456` |
| Colaborador | `COL` + 2 dígitos | `COL01` |
| Paquete | `PK` + 3 dígitos | `PK001` |
| Solicitud | `SO` + 3 dígitos | `SO001` |
| Despacho | `DE` + 3 dígitos | `DE001` |

**Lo que ya carga el Integrante 1:**

| Centro | Bodegas | Clientes | Colaboradores |
|---|---|---|---|
| `C01` Centro San Jose | `A` General 4×5, `B` Frágil 3×4 | `1-1111-1111` Ana Mora (físico), `2-2222-2222` Luis Vargas (físico), `3-101-123456` Tecnologia Tica S.A. (empresa, 15 %) | `COL01` Carlos Mendez, `COL02` Sofia Ramirez |
| `C02` Centro Alajuela | `A` Tecnología 3×3, `B` Documentos 2×5 | `1-3333-3333` Maria Jimenez (físico), `3-101-654321` Libreria El Saber S.A. (empresa, 10 %) | `COL01` Jorge Castillo, `COL02` Daniela Rojas |
| `C03` Centro Limon | — | — | — (vacío, para probar "eliminar centro") |

**Mínimo que deben cargar:**
- 2 centros, cada uno con 2 bodegas de tipos distintos.
- 2 clientes físicos y 1 empresa.
- 2 colaboradores.
- Paquetes en **todos** los estados, para poder probar todo de una vez.
- Algunas solicitudes en distintos estados.
- Algunos despachos, unos finalizados y otros en proceso.

> Los datos de prueba deben crearse **usando las mismas operaciones del sistema** (`almacenarPaquete`, `aprobarSolicitud`, …), no cambiando estados a mano. Así la bitácora y las celdas quedan consistentes.

Cada integrante escribe su bloque dentro de `cargarDatosPrueba()` y lo marca con un comentario:
```cpp
// ===== Datos de prueba - Integrante 2 (paquetes) =====
```

### 6.10 Trabajo en equipo y Git

- Usen **un repositorio en GitHub** (puede ser privado).
- Cada integrante trabaja en **su rama** (`integrante1`, `integrante2`, `integrante3`) y une sus cambios a `main` **solo si compila**.
- Mensajes de commit cortos y en español, con verbo: `Agrega reubicacion de paquetes`, `Corrige validacion de peso`.
- **No modifiquen archivos de otro integrante sin avisarle.** Si necesitan un método nuevo en una clase ajena, se lo piden al dueño o lo hablan antes (ver [3.1](#31-dependencias-entre-integrantes)).
- `CentroDistribucion.cpp` lo comparten los tres, separado así:
  ```cpp
  // ============================================
  // PARTE 2 - Integrante 2: paquetes y almacenamiento
  // ============================================
  ```
- Si cambian **la firma de un método** que otros usan, avisen en el grupo **antes** de subirlo.
- **Nunca suban código que no compila a `main`.**

### 6.11 Comentarios

- Los comentarios van en español y son **cortos**: solo donde algo no se entiende con leer el código (`// era el primero`, `// evita dividir entre 0`).
- **No** escriban párrafos explicando la clase, **no** pongan "Paso 1, Paso 2" y **no** mencionen el material ni el Proyecto 1 ("como en la semana 13").
- Lo que le toca a otro integrante se marca con `// TODO Integrante N: ...` justo donde va.
- Las reglas importantes del enunciado se comentan donde se aplican:
  ```cpp
  // Regla 9: solo se aprueba si la solicitud sigue Pendiente
  // y el paquete esta Almacenado sin despacho previo.
  ```
- No dejen código comentado "por si acaso". Para eso existe Git.

---

## 7. Checklist antes de integrar código

Antes de unir su parte a `main`, revisen:

- [ ] Compila sin errores.
- [ ] Ningún `vector`, `list`, `map`, `sort` ni nada parecido de la STL.
- [ ] Ningún `template`, `enum` ni `setw`.
- [ ] Los estados se escriben igual que en la tabla de [4.1](#estados-y-categorías-ya-no-hay-constantesh).
- [ ] Mis listas siguen el modelo de `ListaClientes` (mismos nombres de métodos).
- [ ] Cada `new` tiene su `delete` (o `delete[]`) en el lugar correcto.
- [ ] Todas las entradas usan `Validaciones`.
- [ ] Probé meter letras donde van números, textos vacíos y números negativos.
- [ ] Probé códigos repetidos y referencias que no existen.
- [ ] Los estados se cambian **solo** por las operaciones correctas.
- [ ] Cada cambio de estado de paquete quedó en la bitácora.
- [ ] No hay cadenas largas de `->get…()->get…()` (Ley de Demeter).
- [ ] Los nombres siguen las convenciones de la sección 6.1.
- [ ] Agregué mis datos de prueba en `cargarDatosPrueba()`.
- [ ] Hice los métodos que otros me pidieron en la tabla [3.1](#31-dependencias-entre-integrantes).
- [ ] Descomenté los `// TODO` con mi nombre en los archivos de los demás.
- [ ] Le expliqué a los otros dos lo que hice (por la defensa oral).

### Checklist final de entrega
- [ ] El código fuente completo compila desde cero.
- [ ] El diagrama de clases (`diagrama_clases.puml` y su PNG) coincide con el código final.
- [ ] Está el `integrantes.txt` con el nombre completo y la cédula de los 3.
- [ ] Probamos los **6 reportes**.
- [ ] Probamos los flujos completos: registrar → almacenar → reubicar → solicitar → aprobar → incidencia → resolver → finalizar.
- [ ] Probamos eliminar con dependencias (debe rechazarse) y sin ellas (debe funcionar).
- [ ] Revisamos que el archivo subido al Aula Virtual sea la **versión correcta**.
