#include "funciones.h"
#include <string.h>

int esLetraMayuscula(char c) {
    return (c >= 'A' && c <= 'Z');
}

int esDigito(char c) {
    return (c >= '0' && c <= '9');
}

int esBisiesto(int anio) {
    return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0));
}

int esFechaValida(struct fechas f) {
    if (f.anio < 1900 || f.anio > 2100) return 0;
    if (f.mes < 1 || f.mes > 12) return 0;

    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (f.mes == 2 && esBisiesto(f.anio)) {
        diasPorMes[2] = 29;
    }

    if (f.dia < 1 || f.dia > diasPorMes[f.mes]) return 0;
    return 1;
}

int compararFechas(struct fechas f1, struct fechas f2) {
    if (f1.anio != f2.anio) return f1.anio - f2.anio;
    if (f1.mes != f2.mes) return f1.mes - f2.mes;
    return f1.dia - f2.dia;
}

long fechaADias(struct fechas f) {
    long dias = f.dia;
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int y = 1; y < f.anio; y++) {
        dias += esBisiesto(y) ? 366 : 365;
    }
    for (int m = 1; m < f.mes; m++) {
        dias += diasPorMes[m];
        if (m == 2 && esBisiesto(f.anio)) {
            dias += 1;
        }
    }
    return dias;
}

int diasEntreFechas(struct fechas inicio, struct fechas fin) {
    long dInicio = fechaADias(inicio);
    long dFin = fechaADias(fin);
    return (int)(dFin - dInicio);
}
