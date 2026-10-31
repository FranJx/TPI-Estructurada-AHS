#include "alquileres.h"
#include <stdio.h>
#include <string.h>
#include "Estructuras.h"
#include "clientes.h"
#include "vehiculos.h"
#include "funciones.h"
#include "movimientos.h"

// Calcula el costo total del alquiler segun precio por dia del vehiculo
float calcularCostoTot(char *patent, float *costot, int days) {
    FILE *arch_vehiculo = fopen("vehiculos.dat", "rb");
    if (arch_vehiculo != NULL) {
        struct vehiculo v;
        while (fread(&v, sizeof(struct vehiculo), 1, arch_vehiculo) == 1) {
            if (strcmp(patent, v.patVehiculo) == 0) {
                *costot = v.precioPorDia * days;
                fclose(arch_vehiculo);
                return *costot;
            }
        }
        fclose(arch_vehiculo);
    } else {
        printf("\nError al abrir archivo de vehiculos\n");
    }
    return 0;
}

// Registra el alquiler y cambia el estado del vehiculo a alquilado (2)
void registrarAlquiler(int numal, int dnicli, char *patent, struct fechas feini, struct fechas fepre, struct fechas fereal, int days, float costot, float costpag, int state) {
    FILE *arch_alquileres = fopen("alquileres.dat", "ab");
    FILE *arch_vehiculos = fopen("vehiculos.dat", "r+b");

    if (arch_alquileres != NULL && arch_vehiculos != NULL) {
        struct alquileres al = {0};
        al.numAlq = numal;
        al.dniCliente = dnicli;
        strncpy(al.patVehiculo, patent, sizeof(al.patVehiculo) - 1);
        al.fechaInicio = feini;
        al.fechaPreDevolucion = fepre;
        al.fechaRealDevolucion = fereal;
        al.dias = days;
        al.costoTotal = costot;
        al.totalPagado = costpag;
        al.estado = state; // 1: Activo

        fwrite(&al, sizeof(struct alquileres), 1, arch_alquileres);
        fclose(arch_alquileres);

        struct vehiculo ve;
        while (fread(&ve, sizeof(struct vehiculo), 1, arch_vehiculos) == 1) {
            if (strcmp(ve.patVehiculo, patent) == 0) {
                ve.estado = 2; // Alquilado
                fseek(arch_vehiculos, -(long)sizeof(struct vehiculo), SEEK_CUR);
                fwrite(&ve, sizeof(struct vehiculo), 1, arch_vehiculos);
                break;
            }
        }
        fclose(arch_vehiculos);

        // Si el cliente abono una sena o pago inicial, se registra en movimientos
        if (costpag > 0) {
            registrarMovimiento(numal, 1, costpag, feini, dnicli, patent);
        }

        printf("\nAlquiler registrado exitosamente.\n");
    } else {
        if (arch_alquileres != NULL) fclose(arch_alquileres);
        if (arch_vehiculos != NULL) fclose(arch_vehiculos);
        printf("\nError de apertura al registrar alquiler\n");
    }
}


int obtenerSiguienteNumAlquiler(void) {
    FILE *arch_alquileres = fopen("alquileres.dat", "rb");
    if (arch_alquileres == NULL) {
        return 1;
    }
    struct alquileres al;
    int maxId = 0;
    while (fread(&al, sizeof(struct alquileres), 1, arch_alquileres) == 1) {
        if (al.numAlq > maxId) {
            maxId = al.numAlq;
        }
    }
    fclose(arch_alquileres);
    return maxId + 1;
}

int existeAlquiler(int numalquiler) {
    FILE *arch_alquileres = fopen("alquileres.dat", "rb");
    if (arch_alquileres != NULL) {
        struct alquileres al;
        while (fread(&al, sizeof(struct alquileres), 1, arch_alquileres) == 1) {
            if (al.numAlq == numalquiler) {
                fclose(arch_alquileres);
                return 1;
            }
        }
        fclose(arch_alquileres);
    }
    return 0;
}

void obtenerAlquiler(int numalquiler, struct alquileres *al) {
    if (al == NULL) return;
    FILE *arch_alquileres = fopen("alquileres.dat", "rb");
    if (arch_alquileres != NULL) {
        while (fread(al, sizeof(struct alquileres), 1, arch_alquileres) == 1) {
            if (al->numAlq == numalquiler) {
                break;
            }
        }
        fclose(arch_alquileres);
    } else {
        printf("\nError al abrir archivo de alquileres\n");
    }
}

void modificarAlquiler(int numalq, int dniCliente, char *patVehiculo, struct fechas fechaInicio, struct fechas fechaPreDevolucion, struct fechas fechaRealDevolucion, int dias, float costoTotal, float totalPagado, int estado) {
    FILE *arch_alquileres = fopen("alquileres.dat", "r+b");
    if (arch_alquileres != NULL) {
        struct alquileres alqui;
        while (fread(&alqui, sizeof(struct alquileres), 1, arch_alquileres) == 1) {
            if (alqui.numAlq == numalq) {
                alqui.dniCliente = dniCliente;
                strncpy(alqui.patVehiculo, patVehiculo, sizeof(alqui.patVehiculo) - 1);
                alqui.fechaInicio = fechaInicio;
                alqui.fechaPreDevolucion = fechaPreDevolucion;
                alqui.fechaRealDevolucion = fechaRealDevolucion;
                alqui.dias = dias;
                alqui.costoTotal = costoTotal;
                alqui.totalPagado = totalPagado;
                alqui.estado = estado;

                fseek(arch_alquileres, -(long)sizeof(struct alquileres), SEEK_CUR);
                fwrite(&alqui, sizeof(struct alquileres), 1, arch_alquileres);
                printf("\nModificacion completada exitosamente.\n");
                break;
            }
        }
        fclose(arch_alquileres);
    } else {
        printf("\nError al abrir archivo de alquileres\n");
    }
}

int buscarAlquilerActivoPorVehiculo(char *patent, struct alquileres *al) {
    if (patent == NULL || al == NULL) return 0;
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) return 0;

    while (fread(al, sizeof(struct alquileres), 1, arch) == 1) {
        if (strcmp(al->patVehiculo, patent) == 0 && al->estado == 1) {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int buscarAlquilerActivoPorDNI(int dniCliente, struct alquileres *al) {
    if (al == NULL) return 0;
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) return 0;

    while (fread(al, sizeof(struct alquileres), 1, arch) == 1) {
        if (al->dniCliente == dniCliente && al->estado == 1) {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int registrarDevolucion(int numAlq, struct fechas fechaReal, int kmDevolucion, float montoCobrado, struct fechas fechaPago) {
    FILE *archAlq = fopen("alquileres.dat", "r+b");
    if (archAlq == NULL) {
        printf("\nError al abrir alquileres.dat\n");
        return 1;
    }
    FILE *archVeh = fopen("vehiculos.dat", "r+b");
    if (archVeh == NULL) {
        fclose(archAlq);
        printf("\nError al abrir vehiculos.dat\n");
        return 1;
    }

    struct alquileres al;
    int encontrado = 0;
    while (fread(&al, sizeof(struct alquileres), 1, archAlq) == 1) {
        if (al.numAlq == numAlq) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        fclose(archAlq);
        fclose(archVeh);
        printf("\nAlquiler Nro %d no encontrado.\n", numAlq);
        return 1;
    }

    if (al.estado != 1) {
        fclose(archAlq);
        fclose(archVeh);
        printf("\nEl alquiler Nro %d no se encuentra activo.\n", numAlq);
        return 1;
    }

    struct vehiculo v;
    int vehEncontrado = 0;
    while (fread(&v, sizeof(struct vehiculo), 1, archVeh) == 1) {
        if (strcmp(v.patVehiculo, al.patVehiculo) == 0) {
            vehEncontrado = 1;
            break;
        }
    }

    // Calcular dias reales transcurridos
    int diasReales = diasEntreFechas(al.fechaInicio, fechaReal);
    if (diasReales < 1) diasReales = 1;

    // Si hubo demora con respecto a lo pactado
    if (diasReales > al.dias) {
        int diasExtra = diasReales - al.dias;
        float precioDia = vehEncontrado ? v.precioPorDia : (al.costoTotal / al.dias);
        float recargo = diasExtra * precioDia;
        al.costoTotal += recargo;
        printf("\n>>> Dias adicionales: %d. Recargo por mora: $%.2f. Nuevo Costo Total: $%.2f <<<\n",
               diasExtra, recargo, al.costoTotal);
        registrarMovimiento(al.numAlq, 2, recargo, fechaReal, al.dniCliente, al.patVehiculo);
    }

    // Si el cliente realiza un pago al momento de devolver
    if (montoCobrado > 0) {
        al.totalPagado += montoCobrado;
        registrarMovimiento(al.numAlq, 1, montoCobrado, fechaPago, al.dniCliente, al.patVehiculo);
    }

    // Actualizar alquiler
    al.fechaRealDevolucion = fechaReal;
    al.estado = 2; // Finalizado

    fseek(archAlq, -(long)sizeof(struct alquileres), SEEK_CUR);
    fwrite(&al, sizeof(struct alquileres), 1, archAlq);
    fclose(archAlq);

    // Actualizar vehiculo: pasa a Disponible (1) y actualiza kilometraje
    if (vehEncontrado) {
        v.estado = 1; // Disponible
        if (kmDevolucion > v.kmactual) {
            v.kmactual = kmDevolucion;
        }
        fseek(archVeh, -(long)sizeof(struct vehiculo), SEEK_CUR);
        fwrite(&v, sizeof(struct vehiculo), 1, archVeh);
    }
    fclose(archVeh);

    return 0;
}

int registrarPagoAlquiler(int numAlq, float monto, struct fechas fechaPago) {
    if (monto <= 0) {
        printf("\nError: El monto a pagar debe ser mayor a cero.\n");
        return 1;
    }

    FILE *arch = fopen("alquileres.dat", "r+b");
    if (arch == NULL) {
        printf("\nError al abrir alquileres.dat\n");
        return 1;
    }

    struct alquileres al;
    int encontrado = 0;
    while (fread(&al, sizeof(struct alquileres), 1, arch) == 1) {
        if (al.numAlq == numAlq) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        fclose(arch);
        printf("\nAlquiler Nro %d no encontrado.\n", numAlq);
        return 1;
    }

    float saldo = al.costoTotal - al.totalPagado;
    if (saldo <= 0.001f) {
        fclose(arch);
        printf("\nEl alquiler Nro %d ya esta completamente pagado (Saldo: $0.00).\n", numAlq);
        return 1;
    }

    if (monto > saldo + 0.01f) {
        fclose(arch);
        printf("\nError: El monto ($%.2f) supera el saldo pendiente ($%.2f).\n", monto, saldo);
        return 1;
    }

    al.totalPagado += monto;
    fseek(arch, -(long)sizeof(struct alquileres), SEEK_CUR);
    fwrite(&al, sizeof(struct alquileres), 1, arch);
    fclose(arch);

    registrarMovimiento(al.numAlq, 1, monto, fechaPago, al.dniCliente, al.patVehiculo);

    printf("\nPago de $%.2f registrado con exito. Nuevo saldo pendiente: $%.2f\n",
           monto, al.costoTotal - al.totalPagado);
    return 0;
}

static const char* textoEstadoAlquiler(int estado) {
    switch (estado) {
        case 1: return "Activo";
        case 2: return "Finalizado";
        case 0: return "Cancelado";
        default: return "Desconocido";
    }
}

static void imprimirSeparadorAlquileres(FILE *stream) {
    fprintf(stream, "+---------+-----------+---------+------------+------------+------------+------+------------+------------+------------+\n");
}

static void imprimirEncabezadoAlquileres(FILE *stream) {
    imprimirSeparadorAlquileres(stream);
    fprintf(stream, "| %-7s | %-9s | %-7s | %-10s | %-10s | %-10s | %-4s | %-10s | %-10s | %-10s |\n",
            "Alq Nro", "DNI Cli", "Patente", "F. Inicio", "F. Prev.", "F. Real", "Dias", "Total", "Pagado", "Estado");
    imprimirSeparadorAlquileres(stream);
}

static void imprimirFilaAlquiler(FILE *stream, struct alquileres a) {
    char strReal[12];
    if (a.fechaRealDevolucion.dia == 0) {
        strcpy(strReal, "Pendiente ");
    } else {
        sprintf(strReal, "%02d/%02d/%04d", a.fechaRealDevolucion.dia, a.fechaRealDevolucion.mes, a.fechaRealDevolucion.anio);
    }

    fprintf(stream, "| %-7d | %-9d | %-7s | %02d/%02d/%04d | %02d/%02d/%04d | %-10s | %4d | $%9.2f | $%9.2f | %-10s |\n",
            a.numAlq, a.dniCliente, a.patVehiculo,
            a.fechaInicio.dia, a.fechaInicio.mes, a.fechaInicio.anio,
            a.fechaPreDevolucion.dia, a.fechaPreDevolucion.mes, a.fechaPreDevolucion.anio,
            strReal, a.dias, a.costoTotal, a.totalPagado,
            textoEstadoAlquiler(a.estado));
}

int exportarAlquileresTxt(void) {
    FILE *archAlq = fopen("alquileres.dat", "rb");
    if (archAlq == NULL) {
        printf("\nError: No se pudo abrir 'alquileres.dat' para exportar.\n\n");
        return 1;
    }

    FILE *archTxt = fopen("reporte_alquileres.txt", "w");
    if (archTxt == NULL) {
        fclose(archAlq);
        printf("\nError al crear 'reporte_alquileres.txt'\n");
        return 1;
    }

    fprintf(archTxt, "========================================================================================================================\n");
    fprintf(archTxt, "                                             REPORTE GENERAL DE ALQUILERES                                              \n");
    fprintf(archTxt, "========================================================================================================================\n\n");

    imprimirEncabezadoAlquileres(archTxt);
    struct alquileres a;
    int total = 0;
    while (fread(&a, sizeof(struct alquileres), 1, archAlq) == 1) {
        imprimirFilaAlquiler(archTxt, a);
        total++;
    }
    imprimirSeparadorAlquileres(archTxt);
    fprintf(archTxt, "\nTotal de alquileres registrados: %d\n", total);

    fclose(archAlq);
    fclose(archTxt);
    printf("\n>>> Archivo 'reporte_alquileres.txt' generado con exito (%d registros). <<<\n\n", total);
    return 0;
}

void listarAlquileres(void) {
    FILE *archAlq = fopen("alquileres.dat", "rb");
    if (archAlq == NULL) {
        printf("\nNo hay alquileres registrados en el sistema.\n\n");
        return;
    }

    struct alquileres a;
    int total = 0;
    printf("\n=============================================== LISTADO DE ALQUILERES ===============================================\n");
    imprimirEncabezadoAlquileres(stdout);

    while (fread(&a, sizeof(struct alquileres), 1, archAlq) == 1) {
        imprimirFilaAlquiler(stdout, a);
        total++;
    }
    imprimirSeparadorAlquileres(stdout);
    printf("Total de alquileres registrados: %d\n\n", total);
    fclose(archAlq);
}

void listarVehiculosAlquiladosDetalle(void) {
    FILE *archAlq = fopen("alquileres.dat", "rb");
    if (archAlq == NULL) {
        printf("\nNo hay alquileres registrados en el sistema.\n\n");
        return;
    }

    struct alquileres a;
    int total = 0;

    printf("\n=================================== VEHICULOS ALQUILADOS ACTUALMENTE ===================================\n");
    printf("+---------+---------------------------------+-----------+-------------------------+------------+------------+\n");
    printf("| Patente | Vehiculo (Marca / Modelo)       | DNI Cli   | Cliente                 | F. Inicio  | F. Prevista|\n");
    printf("+---------+---------------------------------+-----------+-------------------------+------------+------------+\n");

    while (fread(&a, sizeof(struct alquileres), 1, archAlq) == 1) {
        if (a.estado == 1) { // 1: Alquiler Activo
            struct vehiculo v;
            struct cliente c;
            char descVeh[32] = "Desconocido";
            char nomCli[24] = "Desconocido";

            if (obtenerVehiculo(a.patVehiculo, &v)) {
                snprintf(descVeh, sizeof(descVeh), "%s %s", v.marca, v.modelo);
            }
            if (obtenerCliente(a.dniCliente, &c)) {
                snprintf(nomCli, sizeof(nomCli), "%s %s", c.nombre, c.apellido);
            }

            printf("| %-7s | %-31s | %-9d | %-23s | %02d/%02d/%04d | %02d/%02d/%04d |\n",
                   a.patVehiculo, descVeh, a.dniCliente, nomCli,
                   a.fechaInicio.dia, a.fechaInicio.mes, a.fechaInicio.anio,
                   a.fechaPreDevolucion.dia, a.fechaPreDevolucion.mes, a.fechaPreDevolucion.anio);
            total++;
        }
    }

    printf("+---------+---------------------------------+-----------+-------------------------+------------+------------+\n");
    printf("Total de vehiculos actualmente alquilados: %d\n\n", total);
    fclose(archAlq);
}

void listarAlquileresPorRangoFechas(struct fechas desde, struct fechas hasta) {
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay alquileres registrados.\n\n");
        return;
    }

    struct alquileres a;
    int total = 0;
    printf("\n================ ALQUILERES ENTRE %02d/%02d/%04d Y %02d/%02d/%04d ================\n",
           desde.dia, desde.mes, desde.anio, hasta.dia, hasta.mes, hasta.anio);
    imprimirEncabezadoAlquileres(stdout);

    while (fread(&a, sizeof(struct alquileres), 1, arch) == 1) {
        if (compararFechas(a.fechaInicio, desde) >= 0 && compararFechas(a.fechaInicio, hasta) <= 0) {
            imprimirFilaAlquiler(stdout, a);
            total++;
        }
    }

    imprimirSeparadorAlquileres(stdout);
    printf("Total de alquileres en el rango: %d\n\n", total);
    fclose(arch);
}

void listarAlquileresPorCliente(int dniCliente) {
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay alquileres registrados.\n\n");
        return;
    }

    struct cliente c;
    if (obtenerCliente(dniCliente, &c)) {
        printf("\nHistorial de alquileres del cliente: %s %s (DNI: %d)\n", c.nombre, c.apellido, dniCliente);
    } else {
        printf("\nHistorial de alquileres para el DNI: %d\n", dniCliente);
    }

    struct alquileres a;
    int total = 0;
    imprimirEncabezadoAlquileres(stdout);

    while (fread(&a, sizeof(struct alquileres), 1, arch) == 1) {
        if (a.dniCliente == dniCliente) {
            imprimirFilaAlquiler(stdout, a);
            total++;
        }
    }

    imprimirSeparadorAlquileres(stdout);
    printf("Total de alquileres del cliente: %d\n\n", total);
    fclose(arch);
}

void listarAlquileresPorVehiculo(char *patente) {
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay alquileres registrados.\n\n");
        return;
    }

    struct vehiculo v;
    if (obtenerVehiculo(patente, &v)) {
        printf("\nHistorial de alquileres del vehiculo: %s %s (Patente: %s)\n", v.marca, v.modelo, patente);
    } else {
        printf("\nHistorial de alquileres para el vehiculo con patente: %s\n", patente);
    }

    struct alquileres a;
    int total = 0;
    imprimirEncabezadoAlquileres(stdout);

    while (fread(&a, sizeof(struct alquileres), 1, arch) == 1) {
        if (strcmp(a.patVehiculo, patente) == 0) {
            imprimirFilaAlquiler(stdout, a);
            total++;
        }
    }

    imprimirSeparadorAlquileres(stdout);
    printf("Total de alquileres del vehiculo: %d\n\n", total);
    fclose(arch);
}

void listarAlquileresPorEstado(int estado) {
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay alquileres registrados.\n\n");
        return;
    }

    const char *nombreEstado = (estado == 1) ? "ACTIVOS" : (estado == 2) ? "FINALIZADOS" : (estado == 0) ? "CANCELADOS" : "DESCONOCIDO";
    printf("\n======================== ALQUILERES ESTADO: %s ========================\n", nombreEstado);
    imprimirEncabezadoAlquileres(stdout);

    struct alquileres a;
    int total = 0;
    while (fread(&a, sizeof(struct alquileres), 1, arch) == 1) {
        if (a.estado == estado) {
            imprimirFilaAlquiler(stdout, a);
            total++;
        }
    }

    imprimirSeparadorAlquileres(stdout);
    printf("Total de alquileres con estado '%s': %d\n\n", nombreEstado, total);
    fclose(arch);
}

void listarAlquileresPorImporte(float importe, int criterio) {
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay alquileres registrados.\n\n");
        return;
    }

    if (criterio == 1) {
        printf("\n================= ALQUILERES CON IMPORTE SUPERIOR A $%.2f =================\n", importe);
    } else {
        printf("\n================= ALQUILERES CON IMPORTE INFERIOR A $%.2f =================\n", importe);
    }
    imprimirEncabezadoAlquileres(stdout);

    struct alquileres a;
    int total = 0;
    while (fread(&a, sizeof(struct alquileres), 1, arch) == 1) {
        int cumple = (criterio == 1) ? (a.costoTotal > importe) : (a.costoTotal < importe);
        if (cumple) {
            imprimirFilaAlquiler(stdout, a);
            total++;
        }
    }

    imprimirSeparadorAlquileres(stdout);
    printf("Total de alquileres encontrados: %d\n\n", total);
    fclose(arch);
}

void listarClientesConDeuda(void) {
    FILE *arch = fopen("alquileres.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay alquileres registrados.\n\n");
        return;
    }

    printf("\n=================================== CLIENTES CON DEUDA PENDIENTE ===================================\n");
    printf("+-----------+-------------------------+---------+------------+------------+------------+\n");
    printf("| DNI       | Cliente                 | Alq Nro | Costo Tot. | Pagado     | Saldo Pend.|\n");
    printf("+-----------+-------------------------+---------+------------+------------+------------+\n");

    struct alquileres a;
    int total = 0;
    float deudaTotal = 0.0f;

    while (fread(&a, sizeof(struct alquileres), 1, arch) == 1) {
        float saldo = a.costoTotal - a.totalPagado;
        if (saldo > 0.009f && a.estado != 0) { // Mayor a 0 y no cancelado
            struct cliente c;
            char nomCli[24] = "Desconocido";
            if (obtenerCliente(a.dniCliente, &c)) {
                snprintf(nomCli, sizeof(nomCli), "%s %s", c.nombre, c.apellido);
            }

            printf("| %-9d | %-23s | %-7d | $%9.2f | $%9.2f | $%9.2f |\n",
                   a.dniCliente, nomCli, a.numAlq, a.costoTotal, a.totalPagado, saldo);
            total++;
            deudaTotal += saldo;
        }
    }

    printf("+-----------+-------------------------+---------+------------+------------+------------+\n");
    printf("Total de alquileres con deuda: %d | Deuda total acumulada: $%.2f\n\n", total, deudaTotal);
    fclose(arch);
}

void generarEstadisticasEmpresa(void) {
    // 1. Vehiculos
    int totalVeh = 0;
    int vehDisp = 0;
    int vehAlq = 0;
    int vehOtros = 0;

    FILE *fVeh = fopen("vehiculos.dat", "rb");
    if (fVeh != NULL) {
        struct vehiculo v;
        while (fread(&v, sizeof(struct vehiculo), 1, fVeh) == 1) {
            totalVeh++;
            if (v.estado == 1) vehDisp++;
            else if (v.estado == 2) vehAlq++;
            else vehOtros++;
        }
        fclose(fVeh);
    }

    // 2. Alquileres y finanzas
    int totalAlq = 0;
    int alqActivos = 0;
    int alqFinalizados = 0;
    int alqCancelados = 0;
    float totalFacturado = 0.0f;
    float totalCobrado = 0.0f;
    float totalPendiente = 0.0f;

    FILE *fAlq = fopen("alquileres.dat", "rb");
    if (fAlq != NULL) {
        struct alquileres a;
        while (fread(&a, sizeof(struct alquileres), 1, fAlq) == 1) {
            totalAlq++;
            if (a.estado == 1) alqActivos++;
            else if (a.estado == 2) alqFinalizados++;
            else if (a.estado == 0) alqCancelados++;

            if (a.estado != 0) {
                totalFacturado += a.costoTotal;
                totalCobrado += a.totalPagado;
                float saldo = a.costoTotal - a.totalPagado;
                if (saldo > 0) totalPendiente += saldo;
            }
        }
        fclose(fAlq);
    }

    printf("\n");
    printf("================================================================================\n");
    printf("                       ESTADISTICAS GENERALES DE LA EMPRESA                     \n");
    printf("================================================================================\n");
    printf("  FLOTA DE VEHICULOS:\n");
    printf("    - Cantidad total de vehiculos:             %d\n", totalVeh);
    printf("    - Vehiculos disponibles:                   %d (%.1f%%)\n",
           vehDisp, totalVeh > 0 ? (vehDisp * 100.0f / totalVeh) : 0.0f);
    printf("    - Vehiculos alquilados:                    %d (%.1f%%)\n",
           vehAlq, totalVeh > 0 ? (vehAlq * 100.0f / totalVeh) : 0.0f);
    printf("    - En mantenimiento / fuera de servicio:    %d\n", vehOtros);
    printf("--------------------------------------------------------------------------------\n");
    printf("  OPERACIONES DE ALQUILER:\n");
    printf("    - Cantidad total de alquileres:            %d\n", totalAlq);
    printf("    - Alquileres activos en curso:             %d\n", alqActivos);
    printf("    - Alquileres finalizados:                  %d\n", alqFinalizados);
    printf("    - Alquileres cancelados:                   %d\n", alqCancelados);
    printf("--------------------------------------------------------------------------------\n");
    printf("  BALANCE ECONOMICO:\n");
    printf("    - Importe total facturado/pactado:         $%.2f\n", totalFacturado);
    printf("    - Importe total efectivamente cobrado:     $%.2f\n", totalCobrado);
    printf("    - Importe total pendiente de cobro:        $%.2f\n", totalPendiente);
    printf("================================================================================\n\n");
}
