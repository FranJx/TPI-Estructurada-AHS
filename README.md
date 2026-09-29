# Sistema de Gestión de Alquiler de Vehículos

**Trabajo Práctico Integrador**  
*Programación Estructurada (2026)*  
*Ingeniería en Informática — Universidad Gastón Dachary*

---

## 👥 Integrantes
- Eckert K.
- Arias F.
- Barros G.
- Rodoni L.

*(Revisar / actualizar con Nombre, Apellido y DNI si corresponde)*

---

## 📋 Descripción del Proyecto
Aplicación de consola desarrollada en lenguaje C utilizando programación estructurada, modularización, registros (`struct`), punteros y persistencia en archivos binarios (`.dat`) y de texto (`.txt`). Permite gestionar la flota de vehículos, clientes, contratos de alquiler, devoluciones, registro de pagos y estadísticas del negocio.

---

## 📁 Organización del Proyecto (Módulos sugeridos)
- `main.c`: Menú principal y punto de entrada.
- `clientes.h` / `clientes.c`: Gestión de clientes y validaciones.
- `vehiculos.h` / `vehiculos.c`: Flota de vehículos y estados.
- `alquileres.h` / `alquileres.c`: Operaciones de alquiler y devoluciones.
- `movimientos.h` / `movimientos.c`: Registro de pagos, ajustes y archivo de texto por cliente.

---

## 🛠️ Compilación y Ejecución
Para compilar todos los módulos con GCC:
```bash
gcc -Wall -Wextra -std=c99 main.c clientes.c vehiculos.c alquileres.c movimientos.c -o sistema_alquiler.exe
```
Para ejecutar:
```bash
./sistema_alquiler.exe
```
