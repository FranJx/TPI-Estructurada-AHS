#include "vehiculos.h"
#include <stdio.h>
#include <string.h>
#include "Estructuras.h"
#include "funciones.h"

// Valida formato de patente tradicional (AAA999) o Mercosur (AA999AA)
int esPatente(char *patente) {
    if (patente == NULL) {
        return 0;
    }
    int len = strlen(patente);
    // Formato tradicional: AAA999 (longitud 6)
    if (len == 6) {
        for (int i = 0; i < 3; i++) {
            if (!esLetraMayuscula(patente[i])) {
                return 0;
            }
        }
        for (int i = 3; i < 6; i++) {
            if (!esDigito(patente[i])) {
                return 0;
            }
        }
        return 1;
    }
    // Formato Mercosur: AA999AA (longitud 7)
    if (len == 7) {
        if (!esLetraMayuscula(patente[0]) || !esLetraMayuscula(patente[1])) {
            return 0;
        }
        if (!esDigito(patente[2]) || !esDigito(patente[3]) || !esDigito(patente[4])) {
            return 0;
        }
        if (!esLetraMayuscula(patente[5]) || !esLetraMayuscula(patente[6])) {
            return 0;
        }
        return 1;
    }
    return 0;
}

// Verifica si la patente ya existe en el archivo vehiculos.dat
int existeVeh(char *patente) {
    FILE *AVeh = fopen("vehiculos.dat", "rb");
    if (AVeh == NULL) {
        return 0; // Archivo aún no existe, no hay duplicados
    }
    struct vehiculo v;
    while (fread(&v, sizeof(struct vehiculo), 1, AVeh) == 1) {
        if (strcmp(v.patVehiculo, patente) == 0) {
            fclose(AVeh);
            return 1; // Ya existe
        }
    }
    fclose(AVeh);
    return 0; // No existe
}

// Registra un nuevo vehículo en vehiculos.dat
int nuevoVehiculo(char *patente, char *marca, char *modelo, int anio, int tipo, int capacidad, float precioPorDia,int kmactual) {
    int error = 1;
    if (!esPatente(patente)) {
        printf("Error: Patente invalida (admitidas AAA999 y AA999AA).\n");
        return 1;
    }
    if (existeVeh(patente)) {
        printf("Error: Ya existe un vehiculo con la patente %s.\n", patente);
        return 1;
    }

    FILE *AVeh = fopen("vehiculos.dat", "ab");
    if (AVeh != NULL) {
        struct vehiculo v = {0};
        strcpy(v.patVehiculo, patente);
        strcpy(v.marca, marca);
        strcpy(v.modelo, modelo);
        v.anio = anio;
        v.tipo = tipo;
        v.capacidad = capacidad;
        v.precioPorDia = precioPorDia;
        v.estado = 1; // 1: Disponible (estado inicial) / 2: Alquilado / 3: en mantenimiento / 0: baja
        v.kmactual = kmactual;

        fwrite(&v, sizeof(struct vehiculo), 1, AVeh);
        fclose(AVeh);
        error = 0;
    } else {
        printf("Error al abrir el archivo vehiculos.dat\n");
    }
    return error;
}

// Busca y muestra los datos de un vehículo por patente
int buscarVehiculo(char *patente) {
    FILE *AVeh = fopen("vehiculos.dat", "rb");
    if (AVeh != NULL) {
        struct vehiculo v;
        while (fread(&v, sizeof(struct vehiculo), 1, AVeh) == 1) {
            if (strcmp(v.patVehiculo, patente) == 0) {
                printf("\nVehiculo encontrado [%s]:\n", patente);
                printf("Marca: %s\n", v.marca);
                printf("Modelo: %s\n", v.modelo);
                printf("Anio: %d\n", v.anio);
                printf("Tipo: %d\n", v.tipo);
                printf("Capacidad: %d personas\n", v.capacidad);
                printf("Precio por dia: $%.2f\n", v.precioPorDia);
                printf("Km actuales: %d\n", v.kmactual);
                printf("Estado: ");
                switch (v.estado) {
                    case 1: printf("Disponible\n"); break;
                    case 2: printf("Alquilado\n"); break;
                    case 3: printf("En mantenimiento\n"); break;
                    case 0: printf("Baja\n"); break;
                    default: printf("Desconocido (%d)\n", v.estado);
                }
                fclose(AVeh);
                return 0;
            }
        }
        printf("Vehiculo con patente %s no encontrado.\n", patente);
        fclose(AVeh);
    } else {
        printf("Error al abrir el archivo vehiculos.dat\n");
    }
    return 1;
}

int obtenerVehiculo(char *patente, struct vehiculo *v) {
    if (v == NULL || patente == NULL) return 0;
    FILE *AVeh = fopen("vehiculos.dat", "rb");
    if (AVeh == NULL) return 0;

    while (fread(v, sizeof(struct vehiculo), 1, AVeh) == 1) {
        if (strcmp(v->patVehiculo, patente) == 0) {
            fclose(AVeh);
            return 1;
        }
    }
    fclose(AVeh);
    return 0;
}

int modificarVehiculo(char *patente, char *marca, char *modelo, int anio, int tipo, int capacidad, float precioPorDia, int estado, int kmactual) {
    if (patente == NULL) return 1;
    FILE *AVeh = fopen("vehiculos.dat", "r+b");
    if (AVeh == NULL) {
        printf("Error: No se pudo abrir vehiculos.dat para modificar.\n");
        return 1;
    }

    struct vehiculo v;
    while (fread(&v, sizeof(struct vehiculo), 1, AVeh) == 1) {
        if (strcmp(v.patVehiculo, patente) == 0) {
            fseek(AVeh, -(long)sizeof(struct vehiculo), SEEK_CUR);

            strcpy(v.marca, marca);
            strcpy(v.modelo, modelo);
            v.anio = anio;
            v.tipo = tipo;
            v.capacidad = capacidad;
            v.precioPorDia = precioPorDia;
            v.estado = estado;
            v.kmactual = kmactual;

            fwrite(&v, sizeof(struct vehiculo), 1, AVeh);
            fclose(AVeh);
            return 0;
        }
    }

    fclose(AVeh);
    return 1;
}

int eliminarVehiculo(char *patente) {
	if (patente == NULL) return 1;
	FILE *arch_vehiculos = fopen("vehiculos.dat", "r+b");
	if (arch_vehiculos == NULL) {
		printf("\nError al abrir el archivo vehiculos.dat\n");
		return 1;
	}

	struct vehiculo v;
	while (fread(&v, sizeof(struct vehiculo), 1, arch_vehiculos) == 1) {
		if (strcmp(v.patVehiculo, patente) == 0) {
			v.estado = 0; // Baja logica
			fseek(arch_vehiculos, -(long)sizeof(struct vehiculo), SEEK_CUR);
			fwrite(&v, sizeof(struct vehiculo), 1, arch_vehiculos);
			fclose(arch_vehiculos);
			return 0; // Exito
		}
	}

	fclose(arch_vehiculos);
	return 1; // No encontrado
}
int estaDisponible(char *patent){
	FILE *arch_vehiculos;
	struct vehiculo v;
	arch_vehiculos= fopen("vehiculos.dat", "rb");
	if(arch_vehiculos != NULL){
		while((fread(&v, sizeof(struct vehiculo), 1, arch_vehiculos)) == 1){
			if(strcmp(v.patVehiculo, patent)== 0){
				if(v.estado == 1){
					fclose(arch_vehiculos);
					return 1;//si el vehiculo esta disponible para alquilarse
				}
			}
		}
	}else{
		printf("\nError de apertura del archivo de vehiculos\n");
	}
	fclose(arch_vehiculos);
	return 0; //si el vehiculo no esta disponible para alquiler
}

static const char* textoTipoVehiculo(int tipo) {
    switch (tipo) {
        case 1: return "Auto";
        case 2: return "Camioneta";
        case 3: return "Utilitario";
        default: return "Otro";
    }
}

static const char* textoEstadoVehiculo(int estado) {
    switch (estado) {
        case 1: return "Disponible";
        case 2: return "Alquilado";
        case 3: return "Mantenimiento";
        case 0: return "Baja";
        default: return "Desconocido";
    }
}

static void imprimirSeparadorVehiculos(FILE *stream) {
    fprintf(stream, "+---------+---------------+---------------+------+-------------+------+------------+---------+---------------+\n");
}

static void imprimirEncabezadoVehiculos(FILE *stream) {
    imprimirSeparadorVehiculos(stream);
    fprintf(stream, "| %-7s | %-13s | %-13s | %-4s | %-11s | %-4s | %-10s | %-7s | %-13s |\n",
            "Patente", "Marca", "Modelo", "Anio", "Tipo", "Cap.", "Precio/Dia", "Km Act.", "Estado");
    imprimirSeparadorVehiculos(stream);
}

static void imprimirFilaVehiculo(FILE *stream, struct vehiculo v) {
    fprintf(stream, "| %-7s | %-13.13s | %-13.13s | %4d | %-11s | %2d p | $%9.2f | %7d | %-13s |\n",
            v.patVehiculo, v.marca, v.modelo, v.anio,
            textoTipoVehiculo(v.tipo), v.capacidad,
            v.precioPorDia, v.kmactual,
            textoEstadoVehiculo(v.estado));
}

int exportarVehiculosTxt(void) {
    FILE *AVeh = fopen("vehiculos.dat", "rb");
    if (AVeh == NULL) {
        printf("\nError: No se pudo abrir 'vehiculos.dat' para exportar.\n\n");
        return 1;
    }

    FILE *ATxt = fopen("reporte_vehiculos.txt", "w");
    if (ATxt == NULL) {
        printf("\nError: No se pudo crear el archivo 'reporte_vehiculos.txt'.\n\n");
        fclose(AVeh);
        return 1;
    }

    fprintf(ATxt, "=================================================================================================================\n");
    fprintf(ATxt, "                                         REPORTE GENERAL DE VEHICULOS                                            \n");
    fprintf(ATxt, "=================================================================================================================\n\n");

    imprimirEncabezadoVehiculos(ATxt);

    struct vehiculo v;
    int total = 0;
    while (fread(&v, sizeof(struct vehiculo), 1, AVeh) == 1) {
        imprimirFilaVehiculo(ATxt, v);
        total++;
    }

    imprimirSeparadorVehiculos(ATxt);
    fprintf(ATxt, "\nTotal de vehiculos registrados: %d\n", total);

    fclose(AVeh);
    fclose(ATxt);

    printf("\n>>> Archivo 'reporte_vehiculos.txt' generado exitosamente con %d registros. <<<\n\n", total);
    return 0;
}

void listarVehiculos(void) {
    FILE *AVeh = fopen("vehiculos.dat", "rb");
    if (AVeh == NULL) {
        printf("\nNo se pudo abrir 'vehiculos.dat' o no hay vehiculos cargados.\n\n");
        return;
    }

    struct vehiculo v;
    int contador = 0;
    int enPagina = 0;
    char opcion;

    printf("\n============================= LISTADO DE VEHICULOS =============================\n");
    imprimirEncabezadoVehiculos(stdout);

    while (fread(&v, sizeof(struct vehiculo), 1, AVeh) == 1) {
        imprimirFilaVehiculo(stdout, v);
        contador++;
        enPagina++;

        if (enPagina == 5) {
            imprimirSeparadorVehiculos(stdout);
            enPagina = 0;
            printf("\nMostrados %d vehiculos.\n", contador);
            printf("[C] Continuar (siguientes 5) | [P] Imprimir a TXT | [S] Salir al menu: ");
            scanf(" %c", &opcion);

            if (opcion == 'P' || opcion == 'p') {
                exportarVehiculosTxt();
                printf("¿Desea seguir viendo en consola [C] o salir [S]? ");
                scanf(" %c", &opcion);
            }

            if (opcion == 'S' || opcion == 's') {
                fclose(AVeh);
                printf("\nListado finalizado.\n\n");
                return;
            }

            printf("\n");
            imprimirEncabezadoVehiculos(stdout);
        }
    }

    if (enPagina > 0) {
        imprimirSeparadorVehiculos(stdout);
    }

    if (contador == 0) {
        printf("|                        No hay vehiculos registrados en el archivo.                            |\n");
        imprimirSeparadorVehiculos(stdout);
    } else {
        printf("\nFin del archivo (Total: %d vehiculos).\n", contador);
        printf("[P] Imprimir a TXT | [Cualquier otra tecla] Volver al menu: ");
        scanf(" %c", &opcion);
        if (opcion == 'P' || opcion == 'p') {
            exportarVehiculosTxt();
        }
    }

    fclose(AVeh);
    printf("\n");
}


void listarVehiculosDisponibles(void) {
    FILE *AVeh = fopen("vehiculos.dat", "rb");
    if (AVeh == NULL) {
        printf("\nNo se pudo abrir 'vehiculos.dat' o no hay vehiculos cargados.\n\n");
        return;
    }

    struct vehiculo v;
    int contador = 0;

    printf("\n============================= VEHICULOS DISPONIBLES =============================\n");
    imprimirEncabezadoVehiculos(stdout);

    while (fread(&v, sizeof(struct vehiculo), 1, AVeh) == 1) {
        if (v.estado == 1) { // 1: Disponible
            imprimirFilaVehiculo(stdout, v);
            contador++;
        }
    }

    imprimirSeparadorVehiculos(stdout);
    printf("Total de vehiculos actualmente disponibles: %d\n\n", contador);
    fclose(AVeh);
}
