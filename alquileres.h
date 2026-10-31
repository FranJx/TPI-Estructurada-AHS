#ifndef ALQUILERES_H
#define ALQUILERES_H

#include "Estructuras.h"

// Funciones para el modulo de alquileres
float calcularCostoTot(char *patent, float *costot, int days);
void registrarAlquiler(int numal, int dnicli, char *patent, struct fechas feini, struct fechas fepre, struct fechas fereal, int days, float costot, float costpag, int state);
int obtenerSiguienteNumAlquiler(void);
int existeAlquiler(int numalquiler);
void obtenerAlquiler(int numalquiler, struct alquileres *al);
void modificarAlquiler(int numalq, int dniCliente, char *patVehiculo, struct fechas fechaInicio, struct fechas fechaPreDevolucion, struct fechas fechaRealDevolucion, int dias, float costoTotal, float totalPagado, int estado);

// Busqueda de alquileres activos
int buscarAlquilerActivoPorVehiculo(char *patent, struct alquileres *al);
int buscarAlquilerActivoPorDNI(int dniCliente, struct alquileres *al);

// Devoluciones y Pagos
int registrarDevolucion(int numAlq, struct fechas fechaReal, int kmDevolucion, float montoCobrado, struct fechas fechaPago);
int registrarPagoAlquiler(int numAlq, float monto, struct fechas fechaPago);

// Listado y reportes
void listarAlquileres(void);
int exportarAlquileresTxt(void);

// Consultas y reportes avanzados
void listarVehiculosAlquiladosDetalle(void);
void listarAlquileresPorRangoFechas(struct fechas desde, struct fechas hasta);
void listarAlquileresPorCliente(int dniCliente);
void listarAlquileresPorVehiculo(char *patente);
void listarAlquileresPorEstado(int estado);
void listarAlquileresPorImporte(float importe, int criterio);
void listarClientesConDeuda(void);
void generarEstadisticasEmpresa(void);

#endif // ALQUILERES_H
