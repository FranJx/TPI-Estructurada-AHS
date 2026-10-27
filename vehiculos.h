#ifndef VEHICULOS_H
#define VEHICULOS_H

#include "Estructuras.h"

// Declaraciones de funciones para el módulo de vehículos
int esPatente(char *patente);
int existeVeh(char *patente);
int nuevoVehiculo(char *patente, char *marca, char *modelo, int anio, int tipo, int capacidad, float precioPorDia,int kmactual);
int buscarVehiculo(char *patente);
int obtenerVehiculo(char *patente, struct vehiculo *v);
int modificarVehiculo(char *patente, char *marca, char *modelo, int anio, int tipo, int capacidad, float precioPorDia, int estado, int kmactual);
int eliminarVehiculo(char *patente);
void listarVehiculos(void);
int exportarVehiculosTxt(void);
int estaDisponible(char *patente);

#endif // VEHICULOS_H
