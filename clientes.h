#ifndef CLIENTES_H
#define CLIENTES_H
#include "Estructuras.h"
// Declaraciones de estructuras y funciones para el módulo de clientes
int esDNI(int DNI);
int existeCliente(int DNI);
int nuevoCliente(int DNI, char *nombre, char *apellido, char *direccion, char *email, struct fechas fecha_alt, long long int telefono, int activo);
int buscarCliente(int DNI);
int obtenerCliente(int DNI, struct cliente *c);
int modificarCliente(int DNI, char *nombre, char *apellido, char *direccion, char *email, struct fechas fecha_alt, long long int telefono, int activo);
int eliminarCliente(int DNI);
void listarClientes(void);
int exportarClientesTxt(void);

#endif // CLIENTES_H
