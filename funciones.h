#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Estructuras.h"

// Declaraciones de funciones de uso general y validación
int esLetraMayuscula(char c);
int esDigito(char c);
int esPatente(char *patente);

// Manejo y cálculo de fechas
int esBisiesto(int anio);
int esFechaValida(struct fechas f);
int compararFechas(struct fechas f1, struct fechas f2);
long fechaADias(struct fechas f);
int diasEntreFechas(struct fechas inicio, struct fechas fin);

#endif // FUNCIONES_H
