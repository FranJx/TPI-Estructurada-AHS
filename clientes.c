#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "Estructuras.h"

int esDNI(int DNI) {
    if (DNI >= 1000000 && DNI <= 99999999) {
        return 1;
    }
    return 0;
}
int existeCliente(int DNI) {
    FILE *AClientes = fopen("clientes.dat", "rb");
    if (AClientes == NULL) {
        return 0; // Archivo aún no existe, por ende no hay duplicados
    }
    struct cliente c;
    while (fread(&c, sizeof(struct cliente), 1, AClientes) == 1) {
        if (c.DNI == DNI) {
            fclose(AClientes);
            return 1; // Ya existe
        }
    }
    fclose(AClientes);
    return 0; // No existe
}
int nuevoCliente(int DNI, char *nombre, char *apellido, char *direccion, char *email, struct fechas fecha_alt, long long int telefono, int activo) {
    int error = 1;
    if (!esDNI(DNI)) {
        printf("Error: DNI invalido.\n");
        return 1;
    }
    if (existeCliente(DNI)) {
        printf("Error: Ya existe un cliente con el DNI %d.\n", DNI);
        return 1;
    }

    FILE *AClientes = fopen("clientes.dat", "ab");
    if (AClientes != NULL) {
        struct cliente c = {0};
        c.DNI = DNI;
        strcpy(c.nombre, nombre);
        strcpy(c.apellido, apellido);
        strcpy(c.direccion, direccion);
        strcpy(c.email, email);
        c.fecha_alt = fecha_alt;
        c.telefono = telefono;
        c.activo = activo;
        fwrite(&c, sizeof(struct cliente), 1, AClientes);
        fclose(AClientes);
        error = 0;
    } else {
        printf("Error al abrir el archivo clientes.dat\n");
    }
    return error;
}
int buscarCliente(int DNI) {
    FILE *AClientes;
    AClientes = fopen("clientes.dat", "rb");
    if (AClientes != NULL) {
        struct cliente c;
        while (fread(&c, sizeof(struct cliente), 1, AClientes) == 1) {
            if (c.DNI == DNI) {
                printf("\nCliente %d encontrado:\n", DNI);
                printf("Nombre: %s\n", c.nombre);
                printf("Apellido: %s\n", c.apellido);
                printf("Direccion: %s\n", c.direccion);
                printf("Telefono: %I64d\n", c.telefono);
                printf("Email: %s\n", c.email);
                printf("Fecha de alta: %02d/%02d/%04d\n", c.fecha_alt.dia, c.fecha_alt.mes, c.fecha_alt.anio);
                printf("Activo: %d\n", c.activo);
                fclose(AClientes);
                return 0;
            }
        }
        printf("Cliente %d no encontrado\n", DNI);
        fclose(AClientes);
    }else{
        printf("Error al abrir el archivo clientes.dat\n");
    }
    return 1;
}
int obtenerCliente(int DNI, struct cliente *c) {
    if (c == NULL) return 0;
    FILE *AClientes = fopen("clientes.dat", "rb");
    if (AClientes == NULL) {
        return 0;
    }
    while (fread(c, sizeof(struct cliente), 1, AClientes) == 1) {
        if (c->DNI == DNI) {
            fclose(AClientes);
            return 1;
        }
    }
    fclose(AClientes);
    return 0;
}

int modificarCliente(int DNI, char *nombre, char *apellido, char *direccion, char *email, struct fechas fecha_alt, long long int telefono, int activo) {
    FILE *AClientes = fopen("clientes.dat", "r+b");
    if (AClientes == NULL) {
        printf("Error: No se pudo abrir clientes.dat para modificar.\n");
        return 1;
    }

    struct cliente c;
    while (fread(&c, sizeof(struct cliente), 1, AClientes) == 1) {
        if (c.DNI == DNI) {
            fseek(AClientes, -(long)sizeof(struct cliente), SEEK_CUR);

            strcpy(c.nombre, nombre);
            strcpy(c.apellido, apellido);
            strcpy(c.direccion, direccion);
            strcpy(c.email, email);
            c.fecha_alt = fecha_alt;
            c.telefono = telefono;
            c.activo = activo;

            fwrite(&c, sizeof(struct cliente), 1, AClientes);
            fclose(AClientes);
            return 0;
        }
    }

    fclose(AClientes);
    return 1;
}
int eliminarCliente(int DNI) {
	FILE *arch_clientes = fopen("clientes.dat", "r+b");
	if (arch_clientes == NULL) {
		printf("\nError al abrir clientes.dat\n");
		return 1;
	}

	struct cliente c;
	while (fread(&c, sizeof(struct cliente), 1, arch_clientes) == 1) {
		if (c.DNI == DNI) {
			c.activo = 0; // Baja logica
			fseek(arch_clientes, -(long)sizeof(struct cliente), SEEK_CUR);
			fwrite(&c, sizeof(struct cliente), 1, arch_clientes);
			fclose(arch_clientes);
			return 0; // Exito
		}
	}

	fclose(arch_clientes);
	return 1; // No encontrado
}

static void imprimirSeparadorClientes(FILE *stream) {
    fprintf(stream, "+-----------+---------------+---------------+--------------+----------------------+--------------------+------------+----------+\n");
}

static void imprimirEncabezadoClientes(FILE *stream) {
    imprimirSeparadorClientes(stream);
    fprintf(stream, "| %-9s | %-13s | %-13s | %-12s | %-20s | %-18s | %-10s | %-8s |\n",
            "DNI", "Nombre", "Apellido", "Telefono", "Email", "Direccion", "F. Alta", "Estado");
    imprimirSeparadorClientes(stream);
}

static void imprimirFilaCliente(FILE *stream, struct cliente c) {
    fprintf(stream, "| %9d | %-13.13s | %-13.13s | %12I64d | %-20.20s | %-18.18s | %02d/%02d/%04d | %-8s |\n",
            c.DNI, c.nombre, c.apellido, c.telefono,
            c.email, c.direccion,
            c.fecha_alt.dia, c.fecha_alt.mes, c.fecha_alt.anio,
            c.activo ? "Activo" : "Inactivo");
}

int exportarClientesTxt(void) {
    FILE *AClientes = fopen("clientes.dat", "rb");
    if (AClientes == NULL) {
        printf("\nError: No se pudo abrir 'clientes.dat' para exportar.\n\n");
        return 1;
    }

    FILE *ATxt = fopen("reporte_clientes.txt", "w");
    if (ATxt == NULL) {
        printf("\nError: No se pudo crear el archivo 'reporte_clientes.txt'.\n\n");
        fclose(AClientes);
        return 1;
    }

    fprintf(ATxt, "========================================================================================================================\n");
    fprintf(ATxt, "                                               REPORTE GENERAL DE CLIENTES                                              \n");
    fprintf(ATxt, "========================================================================================================================\n\n");

    imprimirEncabezadoClientes(ATxt);

    struct cliente c;
    int total = 0;
    while (fread(&c, sizeof(struct cliente), 1, AClientes) == 1) {
        imprimirFilaCliente(ATxt, c);
        total++;
    }

    imprimirSeparadorClientes(ATxt);
    fprintf(ATxt, "\nTotal de clientes registrados: %d\n", total);

    fclose(AClientes);
    fclose(ATxt);

    printf("\n>>> Archivo 'reporte_clientes.txt' generado exitosamente con %d registros. <<<\n\n", total);
    return 0;
}

void listarClientes(void) {
    FILE *AClientes = fopen("clientes.dat", "rb");
    if (AClientes == NULL) {
        printf("\nNo se pudo abrir 'clientes.dat' o no hay clientes cargados.\n\n");
        return;
    }

    struct cliente c;
    int contador = 0;
    int enPagina = 0;
    char opcion;

    printf("\n=================================== LISTADO DE CLIENTES ===================================\n");
    imprimirEncabezadoClientes(stdout);

    while (fread(&c, sizeof(struct cliente), 1, AClientes) == 1) {
        imprimirFilaCliente(stdout, c);
        contador++;
        enPagina++;

        if (enPagina == 5) {
            imprimirSeparadorClientes(stdout);
            enPagina = 0;
            printf("\nMostrados %d clientes.\n", contador);
            printf("[C] Continuar (siguientes 5) | [P] Imprimir a TXT | [S] Salir al menu: ");
            scanf(" %c", &opcion);

            if (opcion == 'P' || opcion == 'p') {
                exportarClientesTxt();
                printf("¿Desea seguir viendo en consola [C] o salir [S]? ");
                scanf(" %c", &opcion);
            }

            if (opcion == 'S' || opcion == 's') {
                fclose(AClientes);
                printf("\nListado finalizado.\n\n");
                return;
            }

            printf("\n");
            imprimirEncabezadoClientes(stdout);
        }
    }

    if (enPagina > 0) {
        imprimirSeparadorClientes(stdout);
    }

    if (contador == 0) {
        printf("|                                 No hay clientes registrados en el archivo.                                           |\n");
        imprimirSeparadorClientes(stdout);
    } else {
        printf("\nFin del archivo (Total: %d clientes).\n", contador);
        printf("[P] Imprimir a TXT | [Cualquier otra tecla] Volver al menu: ");
        scanf(" %c", &opcion);
        if (opcion == 'P' || opcion == 'p') {
            exportarClientesTxt();
        }
    }

    fclose(AClientes);
    printf("\n");
}

