#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "Estructuras.h"
#include "clientes.h"
#include "vehiculos.h"
#include "alquileres.h"

int main(void) {
	char patente[8];
	int opcion = -1;
	
    
    
	do{
		system("cls");
		
		printf("\n------------------------------------\n  Sistema de Alquiler de Vehiculos   \n------------------------------------\n");

		printf("1. Clientes	2.Vehiculos\n");
		printf("3. Alquileres	4.Devoluciones\n");
		printf("5. Pagos	6.Consultas y reportes\n");
		printf("0. Salir\n");
        printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		switch(opcion){
			case 1: //Clientes
				printf("\n1. Nuevo cliente\n2. Buscar cliente\n3. Modificar cliente\n4. Eliminar cliente\n5. Listar clientes\n6. Volver\n");
				scanf("%d", &opcion);
				switch(opcion){
					case 1: { //Nuevo cliente
						int DNI, activo;
						long long int telefono;
						char nombre[100], apellido[100], direccion[200], email[100];
						struct fechas fecha_alt;

						printf("Ingrese el DNI del cliente: ");
						if (scanf("%d", &DNI) != 1) {
							printf("\nError: Debe ingresar un numero entero para el DNI.\n\n");
							while (getchar() != '\n');
							break;
						}
						if (!esDNI(DNI)) {
							printf("\nError: DNI invalido (debe tener entre 7 y 8 digitos numericos).\n\n");
							break;
						}
						if (existeCliente(DNI)) {
							printf("\nEl cliente ya existe.\n\n");
							break;
						}
						printf("Ingrese el nombre del cliente: ");
						scanf(" %[^\n]", nombre);
						printf("Ingrese el apellido del cliente: ");
						scanf(" %[^\n]", apellido);
						printf("Ingrese la direccion del cliente: ");
						
						scanf(" %[^\n]", direccion);
						printf("Ingrese el email del cliente: ");
						scanf(" %[^\n]", email);
						printf("Ingrese la fecha de alta del cliente (dia mes anio separados por espacio): ");
						scanf("%d %d %d", &fecha_alt.dia, &fecha_alt.mes, &fecha_alt.anio);
						printf("Ingrese el telefono del cliente: ");
						scanf("%I64d", &telefono);
						activo = 1;

						printf("\n--- Resumen del Cliente ---\n");
						printf("DNI:           %d\n", DNI);
						printf("Nombre:        %s\n", nombre);
						printf("Apellido:      %s\n", apellido);
						printf("Direccion:     %s\n", direccion);
						printf("Email:         %s\n", email);
						printf("Fecha de alta: %02d/%02d/%04d\n", fecha_alt.dia, fecha_alt.mes, fecha_alt.anio);
						printf("Telefono:      %I64d\n", telefono);
						printf("---------------------------\n");

						char confirma;
						printf("Â¿Desea confirmar el registro [Y/N]? ");
						scanf(" %c", &confirma);

						if (confirma == 'Y' || confirma == 'y' || confirma == 'S' || confirma == 's') {
							if(nuevoCliente(DNI, nombre, apellido, direccion, email, fecha_alt, telefono, activo) == 0){
								printf("\nCliente agregado exitosamente.\n\n");
							}else{
								printf("\nError al agregar cliente.\n\n");
							}
						} else {
							printf("\nOperacion cancelada por el usuario.\n\n");
						}
						break;
					}
					case 2:{ //Buscar cliente
						int DNI;
						printf("Ingrese el DNI del cliente: ");
						if (scanf("%d", &DNI) != 1) {
							printf("\nError: Debe ingresar un numero entero para el DNI.\n\n");
							while (getchar() != '\n');
							break;
						}
						if (!esDNI(DNI)) {
							printf("\nError: DNI invalido (debe tener entre 7 y 8 digitos numericos).\n\n");
							break;
						}
						buscarCliente(DNI);
						break;}
					case 3: { //Modificar cliente
						int DNI;
						printf("Ingrese el DNI del cliente a modificar: ");
						if (scanf("%d", &DNI) != 1) {
							printf("\nError: Debe ingresar un numero entero para el DNI.\n\n");
							while (getchar() != '\n');
							break;
						}
						if (!esDNI(DNI)) {
							printf("\nError: DNI invalido (debe tener entre 7 y 8 digitos numericos).\n\n");
							break;
						}

						struct cliente c;
						if (!obtenerCliente(DNI, &c)) {
							printf("\nError: Cliente con DNI %d no encontrado.\n\n", DNI);
							break;
						}

						printf("\n--- Datos Actuales del Cliente ---\n");
						printf("DNI:           %d\n", c.DNI);
						printf("Nombre:        %s\n", c.nombre);
						printf("Apellido:      %s\n", c.apellido);
						printf("Direccion:     %s\n", c.direccion);
						printf("Email:         %s\n", c.email);
						printf("Telefono:      %I64d\n", c.telefono);
						printf("Fecha de alta: %02d/%02d/%04d\n", c.fecha_alt.dia, c.fecha_alt.mes, c.fecha_alt.anio);
						printf("Estado:        %s\n", c.activo ? "Activo" : "Inactivo");
						printf("----------------------------------\n");

						int opcMod = -1;
						printf("Seleccione que desea modificar:\n");
						printf("1. Nombre y Apellido\n");
						printf("2. Telefono\n");
						printf("3. Email\n");
						printf("4. Direccion\n");
						printf("5. Estado (1: Activo, 0: Inactivo)\n");
						printf("6. Todos los datos\n");
						printf("0. Cancelar\n");
						printf("Opcion: ");
						scanf("%d", &opcMod);

						if (opcMod == 0) {
							printf("\nModificacion cancelada.\n\n");
							break;
						}

						if (opcMod == 1 || opcMod == 6) {
							printf("Nuevo Nombre: ");
							scanf(" %[^\n]", c.nombre);
							printf("Nuevo Apellido: ");
							scanf(" %[^\n]", c.apellido);
						}
						if (opcMod == 2 || opcMod == 6) {
							printf("Nuevo Telefono: ");
							scanf("%I64d", &c.telefono);
						}
						if (opcMod == 3 || opcMod == 6) {
							printf("Nuevo Email: ");
							scanf(" %[^\n]", c.email);
						}
						if (opcMod == 4 || opcMod == 6) {
							printf("Nueva Direccion: ");
							scanf(" %[^\n]", c.direccion);
						}
						if (opcMod == 5 || opcMod == 6) {
							printf("Nuevo Estado (1: Activo, 0: Inactivo): ");
							scanf("%d", &c.activo);
						}

						printf("\n--- Resumen con Nuevos Datos ---\n");
						printf("DNI:           %d\n", c.DNI);
						printf("Nombre:        %s\n", c.nombre);
						printf("Apellido:      %s\n", c.apellido);
						printf("Direccion:     %s\n", c.direccion);
						printf("Email:         %s\n", c.email);
						printf("Telefono:      %I64d\n", c.telefono);
						printf("Estado:        %s\n", c.activo ? "Activo" : "Inactivo");
						printf("--------------------------------\n");

						char confirma;
						printf("Â¿Desea confirmar las modificaciones [Y/N]? ");
						scanf(" %c", &confirma);

						if (confirma == 'Y' || confirma == 'y' || confirma == 'S' || confirma == 's') {
							if (modificarCliente(c.DNI, c.nombre, c.apellido, c.direccion, c.email, c.fecha_alt, c.telefono, c.activo) == 0) {
								printf("\nCliente modificado exitosamente.\n\n");
							} else {
								printf("\nError al guardar las modificaciones.\n\n");
							}
						} else {
							printf("\nModificacion cancelada por el usuario.\n\n");
						}
						break;
					}
					case 4: { //Eliminar cliente
						int DNI;
						printf("\nIngrese el DNI del cliente al que desea eliminar: \t");
						if (scanf("%d", &DNI) != 1) {
							printf("\nError: Debe ingresar un numero entero para el DNI.\n\n");
							while (getchar() != '\n');
							break;
						}
						if (!esDNI(DNI)) {
							printf("\nError: DNI invalido (debe tener entre 7 y 8 digitos numericos).\n\n");
							break;
						}
						eliminarCliente(DNI);
						break;
					}
					case 5: { //Listar clientes
						listarClientes();
						break;
					}
					case 6: //Volver
						break;
					default:
						printf("Opcion invalida\n");
						opcion = 1;
				}
				break;
			case 2: //Vehiculos
				printf("\n1. Nuevo vehiculo\n2. Buscar vehiculo\n3. Modificar vehiculo\n4. Eliminar vehiculo\n5. Listar vehiculos\n6. Volver\n");
				scanf("%d", &opcion);
				switch(opcion){
					case 1: { //Nuevo vehiculo
						char pat[10];
						char marca[100], modelo[100];
						int anio, tipo, capacidad, kmactual;
						float precioPorDia;

						printf("Ingrese la patente del vehiculo (AAA999 o AA999AA): ");
						scanf(" %s", pat);
						if (!esPatente(pat)) {
							printf("\nFormato de patente invalido.\n\n");
							break;
						}
						if (existeVeh(pat)) {
							printf("\nEl vehiculo con esa patente ya existe.\n\n");
							break;
						}
						printf("Ingrese la marca: ");
						scanf(" %[^\n]", marca);
						printf("Ingrese el modelo: ");
						scanf(" %[^\n]", modelo);
						printf("Ingrese el anio: ");
						scanf("%d", &anio);
						printf("Ingrese el tipo (1. Auto, 2. Camioneta, 3. Utilitario): ");
						scanf("%d", &tipo);
						printf("Ingrese la capacidad (pasajeros): ");
						scanf("%d", &capacidad);
						printf("Ingrese el precio por dia: ");
						scanf("%f", &precioPorDia);
						printf("Ingrese los km actuales: ");
						scanf("%d", &kmactual);

						printf("\n--- Resumen del Vehiculo ---\n");
						printf("Patente:        %s\n", pat);
						printf("Marca:          %s\n", marca);
						printf("Modelo:         %s\n", modelo);
						printf("Anio:           %d\n", anio);
						printf("Tipo:           %d\n", tipo);
						printf("Capacidad:      %d personas\n", capacidad);
						printf("Precio por dia: $%.2f\n", precioPorDia);
						printf("Km actuales:    %d\n", kmactual);
						printf("----------------------------\n");

						char confirma;
						printf("Â¿Desea confirmar el registro [Y/N]? ");
						scanf(" %c", &confirma);

						if (confirma == 'Y' || confirma == 'y' || confirma == 'S' || confirma == 's') {
							if (nuevoVehiculo(pat, marca, modelo, anio, tipo, capacidad, precioPorDia, kmactual) == 0) {
								printf("\nVehiculo agregado exitosamente.\n\n");
							} else {
								printf("\nError al agregar el vehiculo.\n\n");
							}
						} else {
							printf("\nOperacion cancelada por el usuario.\n\n");
						}
						break;
					}
					case 2: { //Buscar vehiculo
						char pat[10];
						printf("Ingrese la patente a buscar: ");
						scanf(" %s", pat);
						buscarVehiculo(pat);
						break;
					}
					case 3: { //Modificar vehiculo
						char pat[10];
						printf("Ingrese la patente del vehiculo a modificar: ");
						scanf(" %s", pat);

						struct vehiculo v;
						if (!obtenerVehiculo(pat, &v)) {
							printf("\nError: Vehiculo con patente %s no encontrado.\n\n", pat);
							break;
						}

						printf("\n--- Datos Actuales del Vehiculo ---\n");
						printf("Patente:        %s\n", v.patVehiculo);
						printf("Marca:          %s\n", v.marca);
						printf("Modelo:         %s\n", v.modelo);
						printf("Anio:           %d\n", v.anio);
						printf("Tipo:           %d\n", v.tipo);
						printf("Capacidad:      %d personas\n", v.capacidad);
						printf("Precio por dia: $%.2f\n", v.precioPorDia);
						printf("Km actuales:    %d\n", v.kmactual);
						printf("Estado:         %d\n", v.estado);
						printf("-----------------------------------\n");

						int opcMod = -1;
						printf("Seleccione que desea modificar:\n");
						printf("1. Precio por dia\n");
						printf("2. Kilometraje actual\n");
						printf("3. Estado (1: Disponible, 2: Alquilado, 3: Mantenimiento, 0: Baja)\n");
						printf("4. Capacidad de personas\n");
						printf("5. Datos tecnicos (Marca, Modelo, Anio, Tipo)\n");
						printf("6. Todos los campos\n");
						printf("0. Cancelar\n");
						printf("Opcion: ");
						scanf("%d", &opcMod);

						if (opcMod == 0) {
							printf("\nModificacion cancelada.\n\n");
							break;
						}

						if (opcMod == 1 || opcMod == 6) {
							printf("Nuevo Precio por dia: ");
							scanf("%f", &v.precioPorDia);
						}
						if (opcMod == 2 || opcMod == 6) {
							printf("Nuevo Kilometraje actual: ");
							scanf("%d", &v.kmactual);
						}
						if (opcMod == 3 || opcMod == 6) {
							printf("Nuevo Estado (1: Disponible, 2: Alquilado, 3: Mantenimiento, 0: Baja): ");
							scanf("%d", &v.estado);
						}
						if (opcMod == 4 || opcMod == 6) {
							printf("Nueva Capacidad: ");
							scanf("%d", &v.capacidad);
						}
						if (opcMod == 5 || opcMod == 6) {
							printf("Nueva Marca: ");
							scanf(" %[^\n]", v.marca);
							printf("Nuevo Modelo: ");
							scanf(" %[^\n]", v.modelo);
							printf("Nuevo Anio: ");
							scanf("%d", &v.anio);
							printf("Nuevo Tipo (1. Auto, 2. Camioneta, 3. Utilitario): ");
							scanf("%d", &v.tipo);
						}

						printf("\n--- Resumen con Nuevos Datos ---\n");
						printf("Patente:        %s\n", v.patVehiculo);
						printf("Marca:          %s\n", v.marca);
						printf("Modelo:         %s\n", v.modelo);
						printf("Anio:           %d\n", v.anio);
						printf("Tipo:           %d\n", v.tipo);
						printf("Capacidad:      %d personas\n", v.capacidad);
						printf("Precio por dia: $%.2f\n", v.precioPorDia);
						printf("Km actuales:    %d\n", v.kmactual);
						printf("Estado:         %d\n", v.estado);
						printf("--------------------------------\n");

						char confirma;
						printf("Â¿Desea confirmar las modificaciones [Y/N]? ");
						scanf(" %c", &confirma);

						if (confirma == 'Y' || confirma == 'y' || confirma == 'S' || confirma == 's') {
							if (modificarVehiculo(v.patVehiculo, v.marca, v.modelo, v.anio, v.tipo, v.capacidad, v.precioPorDia, v.estado, v.kmactual) == 0) {
								printf("\nVehiculo modificado exitosamente.\n\n");
							} else {
								printf("\nError al guardar las modificaciones.\n\n");
							}
						} else {
							printf("\nModificacion cancelada por el usuario.\n\n");
						}
						break;
					}
					case 4: {//Eliminar vehiculo
						char pat[10];
						printf("\nIngrese la patente del vehiculo que desea eliminar: \t");
						scanf("%s", pat);
						eliminarVehiculo(pat);
						break;
					}
					case 5: { //Listar vehiculos
						listarVehiculos();
						break;
					}
					case 6: //Volver
						break;
					default:
						printf("Opcion invalida\n");
						opcion = 2;
				}
				break;
			case 3: {//alquileres
				int quehacer;
				char quehacer2;
				printf("\n¿Que desea hacer?\n1_Registrar alquiler\n2_Modificar alquiler\n");
				scanf("%d", &quehacer);
				switch(quehacer){
					case 1: {// se registra un alquiler
						int numal, dnicli,days, state;
						char patent[10];
						float costot, costpag;
						struct fechas feini;
						struct fechas fepre;
						struct fechas fereal;
						printf("\nIngrese numero de alquiler: \t");
						scanf("%d", &numal);
						if((existeAlquiler (numal)) == 1){
							printf("\nNo se puede ingresar un numero de alquiler duplicado\n");
							break;
						}
						printf("\nIngrese el DNI del cliente que va a realizar el alquiler: \t");
						scanf("%d", &dnicli);
						if((existeCliente(dnicli)) != 1){//se verifica que el cliente exista
							printf("\nEl cliente no existe\n");
							break;
						}
						printf("\nIngrese la patente del vehiculo que se desea alquilar: \t");
						scanf("%s", patent);
						if(existeVeh(patent) != 1){//se verifica que el vehiculo que se quiere alquilar exista
							printf("\nEl vehiculo que se desea alquilar no existe\n");
							break;
						}
						if(estaDisponible(patent) != 1){
							printf("\nEl vehiculo que se desea alquilar no esta disponible\n");
							break;
						}
						printf("\nIngrese la fecha inicial del alquiler(separada por espacios y en formato numerico): \t");
						scanf("%d %d %d", &feini.dia, &feini.mes, &feini.anio);
						printf("\nIngrese la fecha prevista de devolucion del vehiculo: \t");
						scanf("%d %d %d", &fepre.dia, &fepre.mes, &fepre.anio);
						printf("\nIngrese fecha de devolucion real: \t");
						scanf("%d %d %d", &fereal.dia, &fereal.mes, &fereal.anio);
						printf("\nIngrese los dias que durara el alquiler: \t");
						scanf("%d", &days);
						calcularCostoTot(patent, &costot, days);
						printf("\nIngrese la cantidad que pago el cliente: \t");
						scanf("%f", &costpag);
						state= 1;
						printf("\n----------Resumen del alquiler----------\n");
						printf("\nNumero de alquiler:        %d\n", numal);
						printf("\nDNI del cliente:           %d\n", dnicli);
						printf("\nPatente del vehiculo:      %s\n", patent);
						printf("\nFecha inicial:             %d %d %d\n", feini.dia, feini.mes, feini.anio);
						printf("\nFecha prevista de devolucion:  %d %d %d\n", fepre.dia, fepre.mes, fepre.anio);
						printf("\nFecha de devolucion real:  %d %d %d\n", fereal.dia, fereal.mes, fereal.anio);
						printf("\nDuracion:                  %d dias\n", days);
						printf("\nCosto total:               %f $\n", costot);
						printf("\nCosto pagado:              %f\n", costpag);
						printf("\nEstado:                    %d\n", state);
						printf("\n----------------------------------------\n");
						printf("\n¿Desea confimar el registro del alquiler? (Y/N)\n");
						scanf("%s", &quehacer2);
						if((quehacer2 == 'y') || (quehacer2 == 'Y') || (quehacer2 == 's') || (quehacer2 == 'S')){
							registrarAlquiler(numal, dnicli, patent, feini, fepre, fereal, days, costot, costpag, state);
							
						}else{
							printf("\nOperacion cancelada por el usuario\n");
						}
						break;
					case 2:{
						//se modifica un alquiler
						int opermod, numalquiler;
						struct alquileres al;
						printf("\nIngrese el numero del alquiler que se desea modificar: \t");
						scanf("%d", &numalquiler);
						if(existeAlquiler(numalquiler) != 1){
							printf("\nEl numero de alquiler ingresado no existe\n");
							break;
						}
						obtenerAlquiler(numalquiler, &al);
						printf("\n----------Datos actuales del alquiler----------\n");
						printf("\nNumero del alquiler:         %d\n", al.numAlq);
						printf("\nDNI del cliente:             %d\n", al.dniCliente);
						printf("\nPatente del vehiculo:        %s\n", al.patVehiculo);
						printf("\nFecha de inicio:             %d %d %d\n", al.fechaInicio.dia, al.fechaInicio.mes, al.fechaInicio.anio);
						printf("\nFecha prevista de devolcucion:     %d %d %d\n", al.fechaPreDevolucion.dia, al.fechaPreDevolucion.mes, al.fechaPreDevolucion.anio);
						printf("\nFecha real de devolucion:    %d %d %d\n", al.fechaRealDevolucion.dia, al.fechaRealDevolucion.mes, al.fechaRealDevolucion.anio);
						printf("\nDuracion del alquiler:       %d dias\n", al.dias);
						printf("\nCosto total del alquiler:    %f $\n", al.costoTotal);
						printf("\nCosto pagado:                %f $\n", al.totalPagado);
						printf("\nEstado:                      %d\n", al.estado);
						printf("\n-----------------------------------------------\n");
						printf("\n1_DNI del cliente\n2_Patente del vehiculo\n3_Fecha de inicio\n4_Fecha prevista de devolucion\n5_Fecha real de devolucion\n6_Duracion del alquiler\n7_Costo pagado\n8_Estado\n9_Todo\n0_Cancelar modificacion\n");
						scanf("%d", &opermod);
						if(opermod == 0){
							printf("\nOperacion cancelada por el usuario\n");
							break;
						}
						if((opermod == 1) || (opermod == 9)){
							printf("\nIngrese DNI del cliente: \t");
							scanf("%d", &al.dniCliente);
							int DNI= al.dniCliente;
							if((existeCliente(DNI)) != 1){// se verifica que el dni del cliente exista
								printf("\nEl cliente no existe\n");
								break;
							}
						}
						if((opermod == 2) || (opermod == 9)){
							printf("\nIngrese la patente del vehiculo: \t");
							scanf("%s", al.patVehiculo);
							char patent[10];
							strcpy(patent, al.patVehiculo);
							if((existeVeh(patent)) != 1){// se verfica que la patente del vehiculo exista
								printf("\nEl vehiculo no existe\n");
								break;
							}
							if((estaDisponible(patent)) != 1){
								printf("\nEl vehiculo no esta disponible\n");
								break;
							}
						}
						if((opermod == 3) || (opermod == 9)){
							printf("\nIngrese fecha de inicio del alquiler (en formato numerico y separada por espacios): \t");
							scanf("%d %d %d", &al.fechaInicio.dia, &al.fechaInicio.mes, &al.fechaInicio.anio);
						}
						if((opermod == 4) || (opermod == 9)){
							printf("\nIngrese la fecha prevista de devolucion (en formato numerico y separada por espacios): \t");
							scanf("%d %d %d", &al.fechaPreDevolucion.dia, &al.fechaPreDevolucion.mes, &al.fechaPreDevolucion.anio);
						}
						if((opermod == 5) || (opermod == 9)){
							printf("\nIngrese la fecha de devolucion real (en formato numerico y separada por espacios): \t");
							scanf("%d %d %d", &al.fechaRealDevolucion.dia, &al.fechaRealDevolucion.mes, &al.fechaRealDevolucion.anio);
						}
						if((opermod == 6) || (opermod == 9)){
							printf("\nIngrese la duracion del alquiler: \t");
							scanf("%d", &al.dias);
						}
						if((opermod == 7) || (opermod == 9)){
							printf("\nIngrese el costo pagado: \t");
							scanf("%f", &al.totalPagado);
						}
						if((opermod == 8) || (opermod == 9)){
							printf("\nIngrese el estado: \t");
							scanf("%d", &al.estado);
						}
						printf("\n-----------------------------------------------\n");
						printf("\n----------Resumen con nuevos datos-------------\n");
						printf("\nNumero de alquiler:               %d\n", al.numAlq);
						printf("\nDNI del cliente:                  %d\n", al.dniCliente);
						printf("\nPatente del vehiculo:             %s\n", al.patVehiculo);
						printf("\nFecha de inicio del alquiler:     %d %d %d\n", al.fechaInicio.dia, al.fechaInicio.mes, al.fechaInicio.anio);
						printf("\nFecha de devolucion prevista:     %d %d %d\n", al.fechaPreDevolucion.dia, al.fechaPreDevolucion.mes, al.fechaPreDevolucion.anio);
						printf("\nFecha de devolucion real:         %d %d %d\n", al.fechaRealDevolucion.dia, al.fechaRealDevolucion.mes, al.fechaRealDevolucion.anio);
						printf("\nDuracion del alquiler:            %d dias\n", al.dias);
						int d= al.dias;
						char p[10];
						float costototl;
						strcpy(p, al.patVehiculo);
						calcularCostoTot(p, &costototl, d);//se calcula el costo total nuevo
						al.costoTotal = costototl;
						printf("\nCosto total:                      %f $\n", al.costoTotal);
						printf("\nCosto pagado:                     %f $\n", al.totalPagado);
						printf("\nEstado:                           %d\n", al.estado);
						printf("\n-----------------------------------------------\n");
						char decision;
						printf("\n¿Desea confirmar la modificacion? (Y/N):      \t");
						scanf(" %c", &decision);
						if((decision == 'Y') || (decision == 'y') || (decision == 'S') || (decision == 's')){
							modificarAlquiler(al.numAlq, al.dniCliente, al.patVehiculo, al.fechaInicio, al.fechaPreDevolucion, al.fechaRealDevolucion, al.dias, al.costoTotal, al.totalPagado, al.estado);
						}else{
							printf("\nModificacion cancelada por el usuario\n");
							break;
						}
						break;
					}
				break;
				}
			}
			}
			case 4: //Devoluciones
				
				break;
			case 5: //Pagos
				
				break;
			case 6: //Consultas y reportes
				fflush(stdin);
				printf("Ingrese su patente: ");
                scanf("%s", patente);
				if(esPatente(patente)){
				printf("patente valida\n");
				if (existeVeh(patente)){
					printf("Existe ya esta patente registrada");
				}else{
				printf("No existe esta patente en el registro");
					
				}
				}else{
					printf("patente invalida\n");
				}	
                
				break;
			case 0: //Salir
				
				break;
			default:
				printf("Opcion invalida\n");
                opcion = -1;
		}
		fflush(stdin);
		system("pause"); // Muestra "Presione una tecla para continuar . . ."
		
	}while(opcion!=0);
	
	
	return 0;
}
