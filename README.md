# FoodSystem

**FoodSystem** es un sistema de gestión para restaurante desarrollado en **C++** mediante consola. El proyecto permite administrar productos, inventario, mesas, pedidos, clientes, facturación, ventas, estadísticas y usuarios con roles, utilizando archivos `.csv` para conservar la información del sistema.

---

## Objetivo del proyecto

El objetivo de FoodSystem es simular el funcionamiento básico de un restaurante desde consola, integrando diferentes módulos de gestión en un solo sistema. El programa permite separar el acceso entre clientes externos y usuarios internos del restaurante.

El cliente puede consultar el menú disponible, mientras que los usuarios internos acceden mediante usuario y contraseña según su rol dentro del restaurante.

---

## Funcionalidades principales

### Cliente

El cliente no necesita iniciar sesión. Desde el menú principal puede:

* Consultar el menú de productos disponibles.
* Ver únicamente productos activos y con stock.

---

### Administrador

El usuario con rol `ADMIN` tiene acceso completo al sistema:

* Gestión de productos e inventario.
* Gestión de mesas y pedidos.
* Gestión de clientes.
* Consulta de ventas.
* Estadísticas del restaurante.
* Administración de usuarios y roles.
* Guardado de datos del sistema.

---

### Inventario

El usuario con rol `INVENTARIO` puede:

* Administrar productos.
* Consultar y modificar inventario.
* Guardar datos del sistema.

---

### Mesero

El usuario con rol `MESERO` puede:

* Administrar mesas.
* Crear y gestionar pedidos.
* Agregar productos a pedidos.
* Cerrar pedidos.
* Guardar datos del sistema.

---

### Cajero

El usuario con rol `CAJERO` puede:

* Gestionar clientes.
* Consultar ventas.
* Revisar estadísticas.
* Guardar datos del sistema.

---

## Módulos del sistema

El proyecto está organizado en diferentes módulos:

* **Productos:** permite registrar, mostrar, buscar y administrar productos del restaurante.
* **Inventario:** permite controlar el stock de cada producto.
* **Mesas:** permite manejar mesas libres, ocupadas o reservadas.
* **Pedidos:** permite crear pedidos y asociarlos a mesas.
* **Clientes:** permite registrar, modificar, activar, desactivar y consultar clientes.
* **Facturación:** calcula subtotal, IVA, descuentos, propina y total de una venta.
* **Ventas:** guarda el historial de ventas realizadas.
* **Estadísticas:** calcula datos como total vendido, promedio de ventas, venta mayor, venta menor, IVA acumulado, descuentos, propinas y cliente más frecuente.
* **Roles:** permite administrar usuarios internos del restaurante y controlar permisos según el rol.

---

## Persistencia de datos

FoodSystem utiliza archivos `.csv` dentro de la carpeta `data/` para guardar y cargar información.

Archivos principales:

```text
data/productos.csv
data/inventario.csv
data/clientes.csv
data/usuarios.csv
data/ventas.csv
```

Al iniciar el programa, se cargan los datos necesarios para el funcionamiento del sistema. Al salir o guardar manualmente, los datos se escriben nuevamente en los archivos correspondientes.

---

## Estructura del proyecto

```text
FoodSystem/
└── restaurante/
    ├── data/
    │   ├── productos.csv
    │   ├── inventario.csv
    │   ├── clientes.csv
    │   ├── usuarios.csv
    │   └── ventas.csv
    │
    ├── include/
    │   ├── Producto.h
    │   ├── Inventario.h
    │   ├── GestorProductos.h
    │   ├── Mesa.h
    │   ├── Pedido.h
    │   ├── GestorRestaurante.h
    │   ├── clientes.h
    │   ├── facturacion.h
    │   ├── estadisticas.h
    │   └── roles.h
    │
    └── src/
        ├── main.cpp
        ├── Producto.cpp
        ├── Inventario.cpp
        ├── GestorProductos.cpp
        ├── Mesa.cpp
        ├── Pedido.cpp
        ├── GestorRestaurante.cpp
        ├── Clientes.cpp
        ├── Facturacion.cpp
        ├── Estadistica.cpp
        └── Roles.cpp
```

---

## Requisitos

Para compilar y ejecutar el proyecto se necesita:

* Compilador de C++, por ejemplo `g++` o `clang++`.
* Estándar C++14 o superior.
* Terminal o consola.
* Sistema operativo Windows, macOS o Linux.

---

## Compilación

Ubíquese en la carpeta `restaurante`:

```bash
cd FoodSystem/restaurante
```

Compile todos los archivos fuente juntos:

```bash
g++ -std=c++14 -I include \
src/main.cpp \
src/GestorProductos.cpp \
src/Producto.cpp \
src/Inventario.cpp \
src/GestorRestaurante.cpp \
src/Mesa.cpp \
src/Pedido.cpp \
src/Clientes.cpp \
src/Facturacion.cpp \
src/Estadistica.cpp \
src/Roles.cpp \
-o main
```

---

## Ejecución

Después de compilar, ejecute:

```bash
./main
```

En Windows, si se genera un archivo `.exe`, puede ejecutarse con:

```bash
main.exe
```

---

## Usuarios de prueba

El sistema incluye usuarios internos de prueba en `data/usuarios.csv`.

| Usuario     | Clave | Rol        |
| ----------- | ----: | ---------- |
| admin       |  0000 | ADMIN      |
| inventario1 |  1111 | INVENTARIO |
| cajero1     |  2222 | CAJERO     |
| mesero1     |  3333 | MESERO     |

También existen usuarios inactivos para probar la validación de estado.

---

## Flujo general del sistema

```text
Inicio del programa
↓
Carga de productos, inventario, clientes, usuarios y ventas
↓
Menú principal
↓
1. Cliente
   → Consulta productos disponibles

2. Usuario del restaurante
   → Login
   → Acceso según rol

0. Salir
   → Guarda datos del sistema
```

---

## Estadísticas disponibles

El módulo de estadísticas permite consultar:

* Cantidad total de ventas.
* Total vendido.
* Promedio por venta.
* Venta mayor.
* Venta menor.
* IVA acumulado.
* Descuentos acumulados.
* Propinas acumuladas.
* Cliente más frecuente.

---

## Notas importantes

El programa debe ejecutarse desde la carpeta `restaurante`, ya que las rutas de los archivos `.csv` están configuradas desde esa ubicación.

Ejemplo correcto:

```bash
FoodSystem/restaurante
```

Si se ejecuta desde otra carpeta, el sistema podría no encontrar los archivos dentro de `data/`.

---

## Tecnologías utilizadas

* C++
* Programación modular
* Archivos de cabecera `.h`
* Archivos fuente `.cpp`
* Persistencia con archivos `.csv`
* Manejo de archivos con `fstream`
* Vectores
* Funciones
* Condicionales
* Ciclos
* Menús por consola

---

## Estado del proyecto

FoodSystem se encuentra en una versión funcional. El sistema permite probar los principales procesos de un restaurante desde consola, incluyendo carga de datos, gestión de usuarios, control de inventario, pedidos, facturación y estadísticas.
