#include "funciones.h"
#include <string.h>
// Implementación de funciones para el módulo de movimientos
int esLetraMayuscula(char c) {
    return (c >= 'A' && c <= 'Z');
}
int esDigito(char c) {
    return (c >= '0' && c <= '9');
}
// Devuelve 1 si es valida, 0 si no lo es
