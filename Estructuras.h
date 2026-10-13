#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// Declaraciones de estructuras

struct fechas {
    int dia;
    int mes;
    int anio;
};

struct cliente {
    int DNI;
    char nombre[100];
    char apellido[100];
    long long int telefono;
    char email[100];
    char direccion[200];
    struct fechas fecha_alt;
    int activo;
};

struct vehiculo {
    char patVehiculo[100];
    char marca[100];
    char modelo[100];
    int anio;
    int tipo;
    int capacidad;
    float precioPorDia;
    int estado;
    int kmactual;
    
};

struct alquileres {
    int numAlq;
    int dniCliente;
    char patVehiculo[100];
    struct fechas fechaInicio;
    struct fechas fechaPreDevolucion;
    struct fechas fechaRealDevolucion;
    int dias;
    float costoTotal;
    float totalPagado;
    int estado;
};

struct movimientos {
    int numMovimiento;
    int numAlq;
    int tipoMovimiento;
    float monto;
    struct fechas fecha;
    int dniCliente;
    char patVehiculo[100];
};

#endif // ESTRUCTURAS_H
