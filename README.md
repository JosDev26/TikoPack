# Proyecto 2
## Resumen, clases y convenciones

> **Entrega:** domingo 1 de noviembre de 2026, 11:59 p. m., por el Aula Virtual (solo un integrante entrega).
> **Valor:** 15 % 
>
> Es como el README del proyecto con indicaciones generales xd

---

## Índice

1. [Resumen](#1-resumen-del-enunciado)
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
- Sí se puede usar `iostream`, `string` y bibliotecas básicas vistas en clase.
- Todas las colecciones que crecen son **listas enlazadas propias**, hechas con `new` y `delete`.
- Cada bodega tiene una **matriz dinámica** (`Celda**`) creada con `new`.
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

| Código | Categoría / tipo de bodega | Tarifa por kg |
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
RECIBIDO ──(asignar celda)──► ALMACENADO ──(aprobar solicitud)──► EN_TRANSITO ──(finalizar despacho)──► ENTREGADO
```
Incidencias (camino temporal):
```
RECIBIDO     ──► INCIDENCIA ──(almacenar normal)──► ALMACENADO
ALMACENADO   ──► INCIDENCIA ──(resolver)──────────► ALMACENADO
EN_TRANSITO  ──► INCIDENCIA ──(resolver)──────────► EN_TRANSITO
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
PENDIENTE ──► APROBADA   (crea el despacho)
          ──► RECHAZADA
          ──► ANULADA
```
- Estos tres estados son **finales** y no se pueden cambiar.
- Solo se crea una solicitud si el paquete está **Almacenado**.
- Solo puede haber **una solicitud Pendiente** por paquete a la vez.
- Si un paquete ya tiene una solicitud aprobada (y su despacho), **no se le pueden crear más solicitudes**.

### 2.5 Estados del despacho

`EN_PROCESO` → `FINALIZADO`. Para finalizar, el despacho tiene que estar *En proceso* **y** el paquete *En tránsito*. Si el paquete está en *Incidencia*, no se puede finalizar.

### 2.6 Reglas de eliminación

| Se puede eliminar… | Solo si… |
|---|---|
| Centro | No tiene clientes, colaboradores, bodegas, paquetes, solicitudes ni despachos |
| Cliente | No tiene paquetes, solicitudes ni despachos |
| Colaborador | No es responsable de ninguna solicitud, despacho ni registro de bitácora |
| Bodega | Todas sus celdas están libres |
| Paquete | Está *Recibido*, no tiene celda y no tiene solicitudes ni despachos |
| Solicitud, despacho, bitácora | **Nunca se eliminan** |

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
| **Clases** | `Lista<T>`, `Nodo<T>`, `Fecha`, `Validaciones`, `Constantes.h`, `Sistema`, `CentroDistribucion` (parte 1), `Cliente`, `ClienteFisico`, `ClienteEmpresa`, `Colaborador`, `Bodega`, `Celda`, `Menu` (menú principal) | `Paquete`, `RegistroBitacora`, `CentroDistribucion` (parte 2) | `Tarifas`, `SolicitudEnvio`, `Despacho`, `Reportes`, `CentroDistribucion` (parte 3) |
| **Submenús** | Centros, Clientes, Colaboradores, Bodegas | Paquetes | Solicitudes, Despachos, Reportes |
| **Reportes** | Ocupación de bodegas | Bitácora de un paquete | Los otros 4 |
| **Puntos aprox.** | ~28 + base | ~34 | ~38 |

> ⏰ **Prioridad del Integrante 1:** `Lista`, `Nodo`, `Fecha`, `Validaciones` y `Constantes.h` tienen que estar listos **primero**, porque los otros dos los necesitan.

### Calendario sugerido
| Fechas      | Meta                                                                                 |
| ----------- | ------------------------------------------------------------------------------------ |
| 9 – 15 oct  | Todos los `.h` escritos y acordados. Lista, Fecha y Validaciones funcionando.        |
| 16 – 25 oct | Cada uno implementa su módulo.                                                       |
| 26 – 31 oct | Reportes, datos de prueba, pruebas cruzadas, diagrama final y `.txt` de integrantes. |
| 1 nov       | Entrega                                                                              |

---

## 4. Explicación de cada clase

> Formato: **Qué es** · **Qué guarda** · **Qué debe hacer** · **Cuidado con**

### 4.1 Clases base (Integrante 1)

#### `Nodo<T>` y `Lista<T>`
- **Qué es:** la lista enlazada que usamos para **todas** las colecciones.
- **Qué guarda:** `Nodo` guarda un `dato` y un puntero `siguiente`. `Lista` guarda el puntero `primero` y la `cantidad`.
- **Qué debe hacer:** insertar al final, eliminar un dato, recorrer (con `getPrimero()` y `getSiguiente()`), contar y decir si está vacía.
- **Cuidado con:**
  - Con plantillas (`template`), **todo el código va en el `.h`**. Una plantilla no se puede separar en `.cpp` sin complicarse.
  - El destructor de `Lista` **solo borra los nodos**, no los objetos a los que apuntan. Los objetos los borra su dueño (ver [6.6](#66-memoria-dinámica-quién-borra-qué)).
  - Si el profesor no enseñó plantillas, hagan una lista por tipo (`ListaClientes`, `ListaBodegas`, …) con **los mismos nombres de métodos**.
  - Insertar **al final** es importante, porque el reporte de clientes respeta "el orden en que aparecen en la lista" y la bitácora va "del más antiguo al más reciente".

Ejemplo de recorrido (todos lo hacemos igual):
```cpp
Nodo<Cliente*>* actual = clientes.getPrimero();
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
- **Qué debe hacer:**
  - `leerEntero(msg, min, max)`: repite la pregunta hasta que el usuario escriba un entero dentro del rango.
  - `leerDouble(msg, min)`: repite hasta recibir un número válido.
  - `leerTexto(msg)`: lee con `getline` y no acepta texto vacío.
  - `leerFecha(msg)`: pide día, mes, año, hora y minuto válidos.
- **Cuidado con:** mezclar `cin >>` con `getline` deja un salto de línea pendiente. Por eso **todas** las lecturas se hacen con `getline` y después se convierten. **Nadie usa `cin >>` directamente en los menús.**

#### `Constantes.h`
- **Qué es:** el archivo con los `enum` de categorías y estados, más funciones para pasarlos a texto.
- **Qué contiene:** `Categoria`, `EstadoPaquete`, `EstadoSolicitud` y `EstadoDespacho`, más `textoCategoria(int)`, `textoEstadoPaquete(int)`, `textoEstadoSolicitud(int)` y `textoEstadoDespacho(int)`.
- **Quién:** el Integrante 1 crea el archivo con `Categoria`. Cada integrante agrega **sus** enums y funciones de texto.

### 4.2 Núcleo (Integrante 1)

#### `Sistema`
- **Qué es:** la "empresa" TicoPack. Hay **un solo** objeto de esta clase y lo crea `main`.
- **Qué guarda:** la lista de centros.
- **Qué debe hacer:**
  - Agregar, buscar y eliminar centros. Para eliminar, primero pregunta `centro->puedeEliminarse()`.
  - `existePaquete`, `existeSolicitud` y `existeDespacho`: recorren **todos** los centros para verificar que un código global no esté repetido.
  - `cargarDatosPrueba()`: llena el sistema con datos de ejemplo. Cada integrante agrega su parte.
- **Cuidado con:** el destructor de `Sistema` borra los centros.

#### `CentroDistribucion`
- **Qué es:** un centro de distribución. Es la clase **más importante**, porque es dueña de todas las listas y ahí vive la lógica de las operaciones.
- **Qué guarda:** código, nombre, provincia, dirección, teléfono y **6 listas**: clientes, colaboradores, bodegas, paquetes, solicitudes y despachos.
- **Qué debe hacer:** está dividida en 3 partes, una por integrante:
  - **Parte 1 (Integrante 1):** agregar, buscar y eliminar clientes, colaboradores y bodegas, más `puedeEliminarse()`.
  - **Parte 2 (Integrante 2):** paquetes, almacenar, recomendar, reubicar e incidencias.
  - **Parte 3 (Integrante 3):** crear, aprobar, rechazar y anular solicitudes, y finalizar despachos.
- **Cuidado con:**
  - Como 3 personas escriben en el mismo `.cpp`, **cada quien escribe solo debajo de su comentario de sección** (ver [6.10](#610-trabajo-en-equipo-y-git)).
  - El destructor borra los objetos de **todas** sus listas, en este orden: despachos, solicitudes, paquetes, bodegas, colaboradores y clientes.

### 4.3 Personas (Integrante 1)

#### `Cliente` (abstracta)
- **Qué es:** la clase padre de los dos tipos de cliente. No se pueden crear objetos `Cliente` directamente.
- **Qué guarda (`protected`):** identificación, nombre, teléfono y correo.
- **Qué debe hacer:**
  - `getTipo()`: método **virtual puro** que devuelve `"Fisico"` o `"Empresa"`.
  - `aplicarDescuento(costoBase)`: método **virtual**. Por defecto devuelve el mismo costo, sin descuento.
  - `mostrar()`: imprime los datos comunes.
- **Cuidado con:** el **destructor virtual** (`virtual ~Cliente() {}`) es obligatorio. Sin él, borrar un `Cliente*` que en realidad es una `ClienteEmpresa` no libera bien la memoria.

#### `ClienteFisico`
- **Qué es:** un cliente persona física. No agrega atributos.
- **Qué debe hacer:** implementar `getTipo()` y `mostrar()`.

#### `ClienteEmpresa`
- **Qué es:** un cliente empresa.
- **Qué guarda (además):** actividad económica y porcentaje de descuento (0 a 100).
- **Qué debe hacer:** **sobrescribir `aplicarDescuento`** para que devuelva `costoBase - costoBase * porcentajeDescuento / 100`.
- **Cuidado con:** esto es **polimorfismo**. Así, `SolicitudEnvio` no necesita preguntar con un `if` si el cliente es empresa, solo llama a `cliente->aplicarDescuento(base)`. Es algo que el profesor puede preguntar en la defensa.

#### `Colaborador`
- **Qué es:** un empleado del centro.
- **Qué guarda:** identificación, nombre completo, fecha de ingreso y puesto.
- **Qué debe hacer:** mostrarse. Aparece como "responsable" en la bitácora, en las solicitudes y en los despachos.

### 4.4 Bodegas (Integrante 1)

#### `Celda`
- **Qué es:** una posición de la bodega.
- **Qué guarda:** un `Paquete*`. Si vale `nullptr`, la celda está **libre**.
- **Qué debe hacer:** `estaLibre()`, `ocupar(p)`, `liberar()` y `getPaquete()`.
- **Cuidado con:** la celda **nunca** hace `delete` del paquete, solo lo apunta.

#### `Bodega`
- **Qué es:** una bodega organizada en filas y columnas.
- **Qué guarda:** código, nombre, tipo (1 a 4), filas, columnas y `Celda** matriz`.
- **Qué debe hacer:**
  - **Constructor:** reservar la matriz con `new` (ver el código abajo).
  - **Destructor:** liberar la matriz con `delete[]`.
  - `posicionValida(f, c)`: `0 <= f < filas` y `0 <= c < columnas`.
  - `estaLibre`, `asignar`, `liberar` y `getPaquete` sobre una posición.
  - `totalCeldas()`, `celdasOcupadas()`, `porcentajeOcupacion()` y `porcentajeDisponible()`.
  - `primeraCeldaLibre(f, c)`: recorre fila por fila y devuelve la primera celda libre (por referencia). Devuelve `false` si está llena.
  - `mostrarMatriz()`: dibuja la bodega en consola.
- **Cuidado con:** `asignar` y `liberar` **siempre** validan primero la posición.

```cpp
// Constructor
matriz = new Celda*[filas];
for (int i = 0; i < filas; i++)
    matriz[i] = new Celda[columnas];

// Destructor
for (int i = 0; i < filas; i++)
    delete[] matriz[i];
delete[] matriz;
```

### 4.5 Paquetes (Integrante 2)

#### `Paquete`
- **Qué es:** un paquete que la empresa recibe.
- **Qué guarda:** código, descripción, peso, categoría, estado, código del centro, `propietario` (Cliente\*), `bodega` (Bodega\*, `nullptr` si no está guardado), `fila`, `columna` (−1 si no tiene), la `bitacora` (lista de `RegistroBitacora*`) y `tieneDespacho`.
- **Qué debe hacer:**
  - `puedeCambiarA(nuevo)`: consulta la matriz `static const bool TRANSICIONES[5][5]`.
  - `cambiarEstado(nuevo, fecha, responsable)`: si la transición es válida, crea un `RegistroBitacora`, lo agrega a la bitácora y cambia el estado. **No mueve celdas**, eso lo hacen las operaciones.
  - `asignarUbicacion(b, f, c)`: guarda dónde está el paquete.
  - `quitarUbicacion()`: **libera la celda en la bodega** (`bodega->liberar(fila, columna)`) y pone `bodega = nullptr`, `fila = columna = -1`.
  - `tieneUbicacion()`: devuelve `bodega != nullptr`.
  - `mostrar()` y `mostrarBitacora()`.
- **Cuidado con:**
  - El destructor borra los registros de su bitácora.
  - Un paquete nuevo empieza en `RECIBIDO`, sin bodega y **sin registros en la bitácora**, porque todavía no hubo un cambio de estado.

#### `RegistroBitacora`
- **Qué es:** una línea del historial de un paquete.
- **Qué guarda:** estado anterior, estado nuevo, fecha y colaborador responsable.
- **Qué debe hacer:** `mostrar()`.
- **Cuidado con:** **nunca** se modifica ni se elimina. Solo tiene getters, sin setters.

### 4.6 Solicitudes y despachos (Integrante 3)

#### `Tarifas`
- **Qué es:** una clase que solo tiene datos compartidos (`static`).
- **Qué guarda:** `static const double GENERAL = 1500`, `FRAGIL = 2000`, `TECNOLOGIA = 2500` y `DOCUMENTOS = 1000`.
- **Qué debe hacer:** `obtener(categoria)` devuelve la tarifa que corresponde.
- **Cuidado con:** el enunciado exige que **nadie escriba 1500 u otra tarifa directamente** en otro lugar del código.

#### `SolicitudEnvio`
- **Qué es:** el pedido para enviar un paquete.
- **Qué guarda:** código, cliente, paquete, responsable, código del centro de origen, destino (texto), fecha, costo estimado y estado.
- **Qué debe hacer:**
  - `calcularCosto()`: calcula `base = peso * Tarifas::obtener(categoria)` y devuelve `cliente->aplicarDescuento(base)`. El resultado se guarda en `costoEstimado` al crear la solicitud.
  - `cambiarEstado(nuevo)`: solo permite pasar de `PENDIENTE` a otro estado.
  - `mostrar()`.

#### `Despacho`
- **Qué es:** el envío real del paquete. Se crea **solo** al aprobar una solicitud.
- **Qué guarda:** código, solicitud, paquete, cliente, responsable, centro de origen, destino, fecha con hora y estado.
- **Qué debe hacer:** `finalizar()`, que cambia el estado a `FINALIZADO`, y `mostrar()`.
- **Cuidado con:** el cliente, el paquete, el responsable y el destino se copian de la solicitud.

#### `Reportes`
- **Qué es:** funciones `static` que imprimen los 6 reportes.

| Reporte | Quién | Qué hace |
|---|---|---|
| `historialCliente` | Int. 3 | Recorre las solicitudes y los despachos del centro y muestra los de ese cliente: código, paquete, fecha y estado. |
| `clientesPorEnvios` | Int. 3 | Cuenta los despachos **finalizados** de cada cliente y los ordena de mayor a menor con **burbuja** (ver abajo). |
| `bitacoraPaquete` | Int. 2 | Muestra la bitácora en orden: anterior, nuevo, fecha y colaborador. |
| `despachoDePaquete` | Int. 3 | Busca la solicitud *Aprobada* y el despacho de ese paquete. Si no tiene, lo indica. |
| `ocupacionBodegas` | Int. 1 | Para cada bodega del centro: total de celdas, ocupadas, libres y % de ocupación. |
| `despachosPorColaborador` | Int. 3 | Muestra los despachos donde ese colaborador es el responsable. |

**Ordenamiento de `clientesPorEnvios`:** copiar los clientes a un arreglo dinámico (`Cliente** arr = new Cliente*[n]`) junto con un arreglo `int* cant = new int[n]`. Después se aplica **burbuja** con comparación **estricta** (`if (cant[j] < cant[j+1])` → intercambiar). Así, cuando hay empate, se mantiene el orden original. Al final se hace `delete[]` de ambos arreglos.

### 4.7 Interfaz (Integrante 1 + cada uno su submenú)

#### `Menu`
- **Qué es:** toda la interacción con el usuario.
- **Qué guarda:** un puntero a `Sistema`.
- **Qué debe hacer:** mostrar el menú principal y llamar a cada submenú. Cada integrante programa **sus** submenús.
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
4. Crea `new Paquete(...)` con estado `RECIBIDO`, sin bodega y con la bitácora vacía.
5. `centro->agregarPaquete(p)`.

### 5.2 Almacenar un paquete (Int. 2, usa `Bodega` del Int. 1)
1. Solo se permite si el paquete está `RECIBIDO`, o en `INCIDENCIA` sin ubicación y sin despacho.
2. `centro->recomendarBodega(categoria)`: entre las bodegas **del mismo tipo** que tengan al menos una celda libre, elige la de **mayor `porcentajeDisponible()`**. Si hay empate, gana la primera de la lista.
3. Si no hay ninguna, se informa al usuario y **no se cambia nada**.
4. Se recomienda `bodega->primeraCeldaLibre(f, c)` y se muestra la matriz.
5. El usuario acepta la recomendación o escoge otra bodega compatible y otra celda libre.
6. Se pide el colaborador responsable, que debe ser del mismo centro.
7. `bodega->asignar(f, c, p)` → `p->asignarUbicacion(b, f, c)` → `p->cambiarEstado(ALMACENADO, fecha, colaborador)`.

### 5.3 Reubicar un paquete (Int. 2)
1. El paquete tiene que estar `ALMACENADO`.
2. Se valida el destino: la bodega existe en el centro, es compatible, la posición es válida, la celda está libre y no es la misma celda actual.
3. **Solo si todo es válido:** `p->quitarUbicacion()` → `nueva->asignar(f, c, p)` → `p->asignarUbicacion(nueva, f, c)`.
4. Si algo falla, **no se toca nada**. El estado no cambia y no se escribe en la bitácora.

### 5.4 Crear una solicitud (Int. 3)
1. Verificar que el código no exista (`sistema->existeSolicitud`).
2. El paquete tiene que estar `ALMACENADO`, sin solicitud `PENDIENTE` (`centro->tieneSolicitudPendiente(p)`) y con `!p->getTieneDespacho()`.
3. El cliente es el propietario del paquete (se toma de `p->getPropietario()`). El responsable debe ser del mismo centro.
4. Se crea la solicitud con estado `PENDIENTE` y se calcula el costo con `calcularCosto()`.

### 5.5 Aprobar una solicitud (Int. 3, usa `Paquete` del Int. 2)
1. Validar: la solicitud está `PENDIENTE`, el paquete está `ALMACENADO` y `!p->getTieneDespacho()`.
2. Verificar que el código de despacho no exista (`sistema->existeDespacho`).
3. `s->cambiarEstado(APROBADA)`.
4. Crear `new Despacho(...)` con estado `EN_PROCESO` y agregarlo a la lista del centro.
5. `p->quitarUbicacion()`, que libera la celda.
6. `p->cambiarEstado(EN_TRANSITO, fecha, s->getResponsable())`.
7. `p->setTieneDespacho(true)`.

### 5.6 Finalizar un despacho (Int. 3)
1. Validar: el despacho está `EN_PROCESO` y el paquete está `EN_TRANSITO`.
2. `d->finalizar()` → `p->cambiarEstado(ENTREGADO, fecha, d->getResponsable())`.

### 5.7 Incidencias (Int. 2)
- **Registrar:** se permite desde `RECIBIDO`, `ALMACENADO` o `EN_TRANSITO`. Se llama a `p->cambiarEstado(INCIDENCIA, ...)` y **no se toca la celda**.
- **Resolver:**
  - Si `p->tieneUbicacion()`, pasa a `ALMACENADO`.
  - Si no, y `p->getTieneDespacho()`, pasa a `EN_TRANSITO`.
  - Si no tiene ninguna de las dos, se avisa: *"Use la opción Almacenar paquete"*.
- La opción general de "cambiar estado" del menú de paquetes **solo** permite registrar y resolver incidencias. Así no se pueden saltar las operaciones obligatorias.

---

## 6. Convenciones del equipo

### 6.1 Nombres

| Elemento | Estilo | Ejemplo |
|---|---|---|
| Clases | `PascalCase` | `CentroDistribucion`, `SolicitudEnvio` |
| Métodos y funciones | `camelCase`, empiezan con verbo | `buscarCliente()`, `calcularCosto()` |
| Atributos y variables | `camelCase` | `porcentajeDescuento`, `codigoCentro` |
| Constantes y valores de enum | `MAYUSCULAS_CON_GUION` | `EN_TRANSITO`, `GENERAL` |
| Getters / setters | `getX()` / `setX()` | `getCodigo()`, `setEstado()` |
| Booleanos | `es…`, `esta…`, `tiene…`, `puede…` | `estaLibre()`, `tieneDespacho`, `puedeEliminarse()` |
| Archivos | Igual que la clase | `ClienteEmpresa.h`, `ClienteEmpresa.cpp` |

- Todo el código va en **español y sin tildes ni ñ** en los identificadores: `anio`, no `año`.
- Usen nombres claros, nada de `x`, `aux2` ni `temp3`. Las únicas excepciones son `i` y `j` en los `for`, y `f` y `c` para fila y columna.

### 6.2 Estructura de archivos

```
TicoPack/
├── main.cpp
├── Constantes.h
├── Lista.h            (Lista<T> y Nodo<T>, todo en el .h)
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
└── docs/
    ├── diagramas (.puml y .png)
    ├── GUIA_EQUIPO.md
    └── integrantes.txt
```

- **Una clase = un `.h` + un `.cpp`.**
- El `.h` tiene la declaración (atributos y firmas). El `.cpp` tiene el código.

### 6.3 Plantilla de un `.h`

```cpp
#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>
#include "Lista.h"
#include "Fecha.h"
#include "Constantes.h"

class Cliente;      // declaraciones adelantadas: solo usamos punteros
class Bodega;
class Colaborador;
class RegistroBitacora;

class Paquete {
private:
    std::string codigo;
    // ...

public:
    Paquete(std::string codigo, std::string descripcion, double peso,
            int categoria, Cliente* propietario, std::string codigoCentro);
    ~Paquete();

    // Getters
    std::string getCodigo();
    // ...

    // Cambia el estado si la tabla lo permite y lo registra en la bitacora.
    bool cambiarEstado(int nuevo, Fecha fecha, Colaborador* responsable);
};

#endif
```

**Reglas de los `.h`:**
- Siempre llevan **include guards** (`#ifndef NOMBRE_H` / `#define` / `#endif`).
- **No ponemos `using namespace std;` en los `.h`**: ahí escribimos `std::string`. En los `.cpp` sí se puede usar.
- Si solo se usa un **puntero** a otra clase, se pone `class OtraClase;` en el `.h` y el `#include` en el `.cpp`. Así se evitan los includes circulares (`Celda` ↔ `Paquete`, `Paquete` ↔ `Bodega`).
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

```cpp
// En Menu
Paquete* p = centro->buscarPaquete(codigo);
if (p == nullptr) {
    cout << "Error: no existe un paquete con ese codigo." << endl;
} else if (centro->almacenarPaquete(p, b, f, c, col)) {
    cout << "Paquete almacenado correctamente." << endl;
}
```

### 6.5 Estados y categorías

- Siempre se usan los **enum de `Constantes.h`** y **nunca números sueltos**: `p->getEstado() == ALMACENADO`, no `== 1`.
- En los atributos, los estados y categorías se guardan como `int`.
- Para mostrarlos se usa `textoEstadoPaquete(estado)`, etc.
- Al pedirle una categoría o tipo al usuario, se muestra la lista numerada:
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
| `Lista<T>` | Solo sus **nodos** |

- `Celda`, `SolicitudEnvio`, `Despacho` y `RegistroBitacora` **solo apuntan**: nunca hacen `delete` de lo que apuntan.
- Al eliminar un elemento por el menú (por ejemplo, un cliente): primero se quita de la lista y después se hace `delete` del objeto.
- Todo `new X[n]` termina con `delete[]`, y todo `new X` con `delete`.
- Un puntero que ya no apunta a nada debe quedar en **`nullptr`**.

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

**Matriz de bodega:**
```
Bodega A - General (5 x 6)
          Col 0     Col 1     Col 2     Col 3
Fila 0   [LIBRE ]  [PK101 ]  [LIBRE ]  [LIBRE ]
Fila 1   [LIBRE ]  [LIBRE ]  [LIBRE ]  [PK208 ]
...
Ocupadas: 4/30 (13.33%)
```

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

**Menú principal** (los grupos que exige el enunciado):
```
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

**Mínimo que deben cargar:**
- 2 centros, cada uno con 2 bodegas de tipos distintos.
- 2 clientes físicos y 1 empresa.
- 2 colaboradores.
- Paquetes en **todos** los estados, para poder probar todo de una vez.
- Algunas solicitudes en distintos estados.
- Algunos despachos, unos finalizados y otros en proceso.

Cada integrante escribe su bloque dentro de `cargarDatosPrueba()` y lo marca con un comentario:
```cpp
// ===== Datos de prueba - Integrante 2 (paquetes) =====
```

### 6.10 Trabajo en equipo y Git

- Usen **un repositorio en GitHub** (puede ser privado).
- Cada integrante trabaja en **su rama** (`integrante1`, `integrante2`, `integrante3`) y une sus cambios a `main` **solo si compila**.
- Mensajes de commit cortos y en español, con verbo: `Agrega reubicacion de paquetes`, `Corrige validacion de peso`.
- **No modifiquen archivos de otro integrante sin avisarle.** Si necesitan un método nuevo en una clase ajena, se lo piden al dueño o lo hablan antes.
- `CentroDistribucion.cpp` lo comparten los tres, separado así:
  ```cpp
  // ============================================
  // PARTE 2 - Integrante 2: paquetes y almacenamiento
  // ============================================
  ```
- Si cambian **la firma de un método** que otros usan, avisen en el grupo **antes** de subirlo.
- **Nunca suban código que no compila a `main`.**

### 6.11 Comentarios

- Los comentarios van en español y son breves.
- Pongan una línea arriba de cada método explicando **qué hace**, no cómo lo hace.
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
- [ ] Cada `new` tiene su `delete` (o `delete[]`) en el lugar correcto.
- [ ] Todas las entradas usan `Validaciones`.
- [ ] Probé meter letras donde van números, textos vacíos y números negativos.
- [ ] Probé códigos repetidos y referencias que no existen.
- [ ] Los estados se cambian **solo** por las operaciones correctas.
- [ ] Cada cambio de estado de paquete quedó en la bitácora.
- [ ] Los nombres siguen las convenciones de la sección 6.1.
- [ ] Agregué mis datos de prueba en `cargarDatosPrueba()`.
- [ ] Le expliqué a los otros dos lo que hice (por la defensa oral).

### Checklist final de entrega
- [ ] El código fuente completo compila desde cero.
- [ ] El diagrama de clases está actualizado (`5_completo.png`) y coincide con el código.
- [ ] Está el `integrantes.txt` con el nombre completo y la cédula de los 3.
- [ ] Probamos los **6 reportes**.
- [ ] Probamos los flujos completos: registrar → almacenar → reubicar → solicitar → aprobar → incidencia → resolver → finalizar.
- [ ] Probamos eliminar con dependencias (debe rechazarse) y sin ellas (debe funcionar).
- [ ] Revisamos que el archivo subido al Aula Virtual sea la **versión correcta**.
