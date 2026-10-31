#include "funciones.h"
#include "movimientos.h"
#include <stdio.h>
#include <string.h>

int obtenerSiguienteNumMovimiento(void) {
    FILE *arch = fopen("movimientos.dat", "rb");
    if (arch == NULL) {
        return 1;
    }
    struct movimientos m;
    int maxId = 0;
    while (fread(&m, sizeof(struct movimientos), 1, arch) == 1) {
        if (m.numMovimiento > maxId) {
            maxId = m.numMovimiento;
        }
    }
    fclose(arch);
    return maxId + 1;
}

int registrarMovimiento(int numAlq, int tipoMovimiento, float monto, struct fechas fecha, int dniCliente, char *patVehiculo) {
    FILE *archBin = fopen("movimientos.dat", "ab");
    if (archBin == NULL) {
        printf("\nError al abrir movimientos.dat\n");
        return 1;
    }

    struct movimientos m = {0};
    m.numMovimiento = obtenerSiguienteNumMovimiento();
    m.numAlq = numAlq;
    m.tipoMovimiento = tipoMovimiento; // 1: Pago, 2: Ajuste
    m.monto = monto;
    m.fecha = fecha;
    m.dniCliente = dniCliente;
    if (patVehiculo != NULL) {
        strncpy(m.patVehiculo, patVehiculo, sizeof(m.patVehiculo) - 1);
    }

    fwrite(&m, sizeof(struct movimientos), 1, archBin);
    fclose(archBin);

    // Registrar en archivo individual de texto movimientos_<DNI>.txt
    char nombreTxt[50];
    sprintf(nombreTxt, "movimientos_%d.txt", dniCliente);
    FILE *archTxt = fopen(nombreTxt, "a");
    if (archTxt != NULL) {
        const char *txtTipo = (tipoMovimiento == 1) ? "PAGO" : "AJUSTE";
        fprintf(archTxt, "%02d/%02d/%04d | Mov #%-4d | Alq #%-4d | Tipo: %-7s | Patente: %-7s | Monto: $%9.2f\n",
                fecha.dia, fecha.mes, fecha.anio,
                m.numMovimiento, numAlq,
                txtTipo, m.patVehiculo, monto);
        fclose(archTxt);
    } else {
        printf("\nAdvertencia: No se pudo actualizar el archivo %s\n", nombreTxt);
    }

    return 0;
}

int listarMovimientosCliente(int dniCliente) {
    FILE *arch = fopen("movimientos.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay movimientos registrados en el sistema.\n");
        return 1;
    }

    struct movimientos m;
    int encontrados = 0;
    printf("\n============================= MOVIMIENTOS DEL CLIENTE %d =============================\n", dniCliente);
    printf("+-------+-----------+---------+-----------+---------+--------------+\n");
    printf("| Mov # |   Fecha   | Alq Nro |   Tipo    | Patente |    Monto     |\n");
    printf("+-------+-----------+---------+-----------+---------+--------------+\n");

    while (fread(&m, sizeof(struct movimientos), 1, arch) == 1) {
        if (m.dniCliente == dniCliente) {
            const char *txtTipo = (m.tipoMovimiento == 1) ? "Pago" : "Ajuste";
            printf("| %-5d | %02d/%02d/%04d| %-7d | %-9s | %-7s | $%11.2f |\n",
                   m.numMovimiento, m.fecha.dia, m.fecha.mes, m.fecha.anio,
                   m.numAlq, txtTipo, m.patVehiculo, m.monto);
            encontrados++;
        }
    }
    printf("+-------+-----------+---------+-----------+---------+--------------+\n");
    printf("Total de movimientos del cliente: %d\n\n", encontrados);

    fclose(arch);
    return (encontrados > 0) ? 0 : 1;
}

void listarTodosMovimientos(void) {
    FILE *arch = fopen("movimientos.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay movimientos registrados en el sistema.\n\n");
        return;
    }

    struct movimientos m;
    int total = 0;
    printf("\n=================================== HISTORIAL DE MOVIMIENTOS ===================================\n");
    printf("+-------+-----------+---------+-----------+-----------+---------+--------------+\n");
    printf("| Mov # |   Fecha   | Alq Nro |    DNI    |   Tipo    | Patente |    Monto     |\n");
    printf("+-------+-----------+---------+-----------+-----------+---------+--------------+\n");

    while (fread(&m, sizeof(struct movimientos), 1, arch) == 1) {
        const char *txtTipo = (m.tipoMovimiento == 1) ? "Pago" : "Ajuste";
        printf("| %-5d | %02d/%02d/%04d| %-7d | %-9d | %-9s | %-7s | $%11.2f |\n",
               m.numMovimiento, m.fecha.dia, m.fecha.mes, m.fecha.anio,
               m.numAlq, m.dniCliente, txtTipo, m.patVehiculo, m.monto);
        total++;
    }
    printf("+-------+-----------+---------+-----------+-----------+---------+--------------+\n");
    printf("Total general de movimientos: %d\n\n", total);
    fclose(arch);
}

void listarPagosPorPeriodo(struct fechas desde, struct fechas hasta) {
    FILE *arch = fopen("movimientos.dat", "rb");
    if (arch == NULL) {
        printf("\nNo hay movimientos registrados en el sistema.\n\n");
        return;
    }

    struct movimientos m;
    int total = 0;
    float montoTotal = 0.0f;

    printf("\n=================== PAGOS REGISTRADOS (%02d/%02d/%04d al %02d/%02d/%04d) ===================\n",
           desde.dia, desde.mes, desde.anio, hasta.dia, hasta.mes, hasta.anio);
    printf("+-------+-----------+---------+-----------+---------+--------------+\n");
    printf("| Mov # |   Fecha   | Alq Nro |    DNI    | Patente |    Monto     |\n");
    printf("+-------+-----------+---------+-----------+---------+--------------+\n");

    while (fread(&m, sizeof(struct movimientos), 1, arch) == 1) {
        if (m.tipoMovimiento == 1) { // 1: Pago
            if (compararFechas(m.fecha, desde) >= 0 && compararFechas(m.fecha, hasta) <= 0) {
                printf("| %-5d | %02d/%02d/%04d| %-7d | %-9d | %-7s | $%11.2f |\n",
                       m.numMovimiento, m.fecha.dia, m.fecha.mes, m.fecha.anio,
                       m.numAlq, m.dniCliente, m.patVehiculo, m.monto);
                total++;
                montoTotal += m.monto;
            }
        }
    }

    printf("+-------+-----------+---------+-----------+---------+--------------+\n");
    printf("Total de pagos en el periodo: %d | Monto acumulado: $%.2f\n\n", total, montoTotal);
    fclose(arch);
}

int exportarMovimientosTxt(void) {
    FILE *archBin = fopen("movimientos.dat", "rb");
    if (archBin == NULL) {
        printf("\nNo hay movimientos registrados para exportar.\n\n");
        return 1;
    }

    FILE *archTxt = fopen("reporte_movimientos.txt", "w");
    if (archTxt == NULL) {
        fclose(archBin);
        printf("\nError al crear 'reporte_movimientos.txt'.\n\n");
        return 1;
    }

    fprintf(archTxt, "========================================================================================\n");
    fprintf(archTxt, "                             REPORTE GENERAL DE MOVIMIENTOS                             \n");
    fprintf(archTxt, "========================================================================================\n\n");
    fprintf(archTxt, "+-------+-----------+---------+-----------+-----------+---------+--------------+\n");
    fprintf(archTxt, "| Mov # |   Fecha   | Alq Nro |    DNI    |   Tipo    | Patente |    Monto     |\n");
    fprintf(archTxt, "+-------+-----------+---------+-----------+-----------+---------+--------------+\n");

    struct movimientos m;
    int total = 0;
    float sumPagos = 0, sumAjustes = 0;
    while (fread(&m, sizeof(struct movimientos), 1, archBin) == 1) {
        const char *txtTipo = (m.tipoMovimiento == 1) ? "Pago" : "Ajuste";
        fprintf(archTxt, "| %-5d | %02d/%02d/%04d| %-7d | %-9d | %-9s | %-7s | $%11.2f |\n",
                m.numMovimiento, m.fecha.dia, m.fecha.mes, m.fecha.anio,
                m.numAlq, m.dniCliente, txtTipo, m.patVehiculo, m.monto);
        if (m.tipoMovimiento == 1) sumPagos += m.monto;
        else sumAjustes += m.monto;
        total++;
    }
    fprintf(archTxt, "+-------+-----------+---------+-----------+-----------+---------+--------------+\n");
    fprintf(archTxt, "\nTotal de movimientos: %d | Total Pagos: $%.2f | Total Ajustes: $%.2f\n", total, sumPagos, sumAjustes);

    fclose(archBin);
    fclose(archTxt);
    printf("\n>>> Archivo 'reporte_movimientos.txt' generado exitosamente (%d registros). <<<\n\n", total);
    return 0;
}
