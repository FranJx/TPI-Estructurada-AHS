#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

#include "Estructuras.h"

// Funciones para gestion de movimientos economicos (pagos y ajustes)
int obtenerSiguienteNumMovimiento(void);
int registrarMovimiento(int numAlq, int tipoMovimiento, float monto, struct fechas fecha, int dniCliente, char *patVehiculo);
int listarMovimientosCliente(int dniCliente);
void listarTodosMovimientos(void);

void listarPagosPorPeriodo(struct fechas desde, struct fechas hasta);
int exportarMovimientosTxt(void);

#endif // MOVIMIENTOS_H
