#ifndef ALQUILERES_H
#define ALQUILERES_H
#include "Estructuras.h"

// Declaraciones de estructuras y funciones para el módulo de alquileres
float calcularCostoTot(char *patent, float *costot, int days);
void registrarAlquiler(int numal, int dnicli, char *patent, struct fechas feini, struct fechas fepre, struct fechas fereal, int days, float costot, float costpag, int state);
int existeAlquiler(int numalquiler);
void obtenerAlquiler(int numalquiler, struct alquileres *al);
void modificarAlquiler(int numalq, int dniCliente, char *patVehiculo, struct fechas fechaInicio, struct fechas fechaPreDevolucion, struct fechas fechaRealDevolucion, int dias, float costoTotal, float totalPagado, int estado);
#endif // ALQUILERES_H
