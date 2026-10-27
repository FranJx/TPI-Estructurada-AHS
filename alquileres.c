#include "alquileres.h"
#include <stdio.h>
#include <string.h>
#include "Estructuras.h"
#include "clientes.h"

// Implementación de funciones para el módulo de alquileres
float calcularCostoTot(char *patent, float *costot, int days){//calcula el costo total del alquiler
	FILE *arch_vehiculo;
	struct vehiculo v;
	arch_vehiculo= fopen("vehiculos.dat", "rb");
	if(arch_vehiculo != NULL){
		while((fread(&v, sizeof(struct vehiculo), 1, arch_vehiculo)) == 1){
			if(strcmp(patent, v.patVehiculo) == 0){
				*costot = v.precioPorDia * days;
				fclose(arch_vehiculo);
				break;
			}
		}
	}else{
		printf("\nError de apertura de archivo de vehiculos\n");
	}
	fclose(arch_vehiculo);
	return *costot;
}
//se usa para registrar el alquiler y cambiar el estado del vehiculo a alquilado
void registrarAlquiler(int numal, int dnicli, char *patent, struct fechas feini, struct fechas fepre, struct fechas fereal, int days, float costot, float costpag, int state){
	FILE *arch_alquileres;
	FILE *arch_vehiculos;
	struct alquileres al;
	struct vehiculo ve;
	arch_alquileres = fopen("alquileres.dat", "ab");
	arch_vehiculos = fopen("vehiculos.dat", "r+b");
	if(arch_alquileres != NULL){
		if(arch_vehiculos != NULL){
			al.numAlq = numal;
			al.dniCliente = dnicli;
			strcpy(al.patVehiculo, patent);
			al.fechaInicio = feini;
			al.fechaPreDevolucion = fepre;
			al.fechaRealDevolucion = fereal;
			al.dias = days;
			al.costoTotal = costot;
			al.totalPagado = costpag;
			al.estado = state;
			fwrite(&al, sizeof(struct alquileres), 1 , arch_alquileres);
			fclose(arch_alquileres);
			while((fread(&ve, sizeof(struct vehiculo), 1, arch_vehiculos)) == 1){
				if((strcmp(ve.patVehiculo, patent)) == 0){
					ve.estado = 2;
					fseek(arch_vehiculos, -sizeof(struct vehiculo), SEEK_CUR);
					fwrite(&ve, sizeof(struct vehiculo), 1, arch_vehiculos);
					printf("\nAlquiler registrado exitosamente\n");
					break;
				}
			}
			fclose(arch_vehiculos);
		}else{
			printf("\nError de apertura del archivo de vehiculos\n");
		}
		fclose(arch_vehiculos);
	}else{
		printf("\nError de apertura del archivo de alquileres\n");
	}
}
int existeAlquiler(int numalquiler){// se usa para ver si el numero de alquiler ingresado existe
	FILE *arch_alquileres;
	struct alquileres al;
	arch_alquileres = fopen("alquileres.dat", "rb");
	if(arch_alquileres != NULL){
		while((fread(&al, sizeof(struct alquileres), 1, arch_alquileres)) == 1){
			if(al.numAlq == numalquiler){
				return 1;// si existe
				break;
			}
		}
	}else{
		printf("\nError de apertura de archivo de alquileres\n");
	}
	fclose(arch_alquileres);
	return 0;// si no existe
}
void obtenerAlquiler(int numalquiler, struct alquileres *al){// aca se mandan los datos del alquiler buscado hacia el main
	FILE *arch_alquileres;
	arch_alquileres = fopen("alquileres.dat", "rb");
	if(arch_alquileres != NULL){
		while((fread(al, sizeof(struct alquileres), 1, arch_alquileres)) == 1){
			if(al->numAlq == numalquiler){
				break;
			}
		}
		fclose(arch_alquileres);
	}else{
		printf("\nError de aapertura del archivo de alquileres\n");
	}
}
//aca se modifica el alquiler y se cambia el estado del vehiculo a alquilado
void modificarAlquiler(int numalq, int dniCliente, char *patVehiculo, struct fechas fechaInicio, struct fechas fechaPreDevolucion, struct fechas fechaRealDevolucion, int dias, float costoTotal, float totalPagado, int estado){
	FILE *arch_alquileres;
	FILE *arch_vehiculos;
	struct alquileres alqui;
	struct vehiculo vehi;
	arch_alquileres = fopen("alquileres.dat", "r+b");
	arch_vehiculos = fopen("vehiculos.dat", "r+b");
	if(arch_alquileres != NULL){
		while((fread(&alqui, sizeof(struct alquileres), 1, arch_alquileres)) == 1){
			if(alqui.numAlq == numalq){
				alqui.dniCliente = dniCliente;
				strcpy(alqui.patVehiculo, patVehiculo);
				alqui.fechaInicio = fechaInicio;
				alqui.fechaPreDevolucion = fechaPreDevolucion;
				alqui.fechaRealDevolucion = fechaRealDevolucion;
				alqui.dias = dias;
				alqui.costoTotal = costoTotal;
				alqui.totalPagado = totalPagado;
				alqui.estado = estado;
				fseek(arch_alquileres, -sizeof(struct alquileres), SEEK_CUR);
				fwrite(&alqui, sizeof(struct alquileres), 1, arch_alquileres);
				while((fread(&vehi, sizeof(struct vehiculo), 1, arch_vehiculos)) == 1){
					if((strcmp(vehi.patVehiculo, patVehiculo)) == 0){
						vehi.estado = 2;
					}
				}
				printf("\nModificacion completada\n");
			}
		}
	}else{
		printf("\nError de apertura de archivo de alquileres\n");
	}
	fclose(arch_alquileres);
}
