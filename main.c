#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "Estructuras.h"
#include "clientes.h"
#include "vehiculos.h"
#include "alquileres.h"
#include "movimientos.h"

int main(void) {
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
						printf("¿Desea confirmar el registro [Y/N]? ");
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
						printf("¿Desea confirmar las modificaciones [Y/N]? ");
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
						printf("¿Desea confirmar el registro [Y/N]? ");
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
						printf("¿Desea confirmar las modificaciones [Y/N]? ");
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
			case 3: { // Gestion de Alquileres
				int quehacer = 0;
				char quehacer2;
				printf("\n================ GESTION DE ALQUILERES ================\n");
				printf("1. Registrar alquiler\n");
				printf("2. Modificar alquiler\n");
				printf("3. Listar alquileres\n");
				printf("0. Volver\n");
				printf("Seleccione una opcion: ");
				if (scanf("%d", &quehacer) != 1 || quehacer == 0) {
					while (getchar() != '\n');
					break;
				}

				switch (quehacer) {
					case 1: { // Registrar nuevo alquiler
						int numal = obtenerSiguienteNumAlquiler();
						printf("\n================ REGISTRAR ALQUILER ================\n");
						printf("Numero de alquiler asignado: %d (Automatico)\n\n", numal);

						// 1. Validar Cliente
						int dnicli;
						printf("Ingrese el DNI del cliente: ");
						if (scanf("%d", &dnicli) != 1) {
							printf("\nError: Debe ingresar un numero entero para el DNI.\n\n");
							while (getchar() != '\n');
							break;
						}
						if (!esDNI(dnicli)) {
							printf("\nError: DNI invalido (debe tener entre 7 y 8 digitos numericos).\n\n");
							break;
						}
						if (!existeCliente(dnicli)) {
							printf("\nError: El cliente con DNI %d no existe en el sistema.\n\n", dnicli);
							break;
						}
						struct cliente cCli;
						obtenerCliente(dnicli, &cCli);
						if (cCli.activo != 1) {
							printf("\nError: El cliente %s %s se encuentra inactivo/dado de baja.\n\n", cCli.nombre, cCli.apellido);
							break;
						}
						printf("Cliente seleccionado: %s %s (DNI: %d)\n\n", cCli.nombre, cCli.apellido, dnicli);

						// 2. Validar Vehiculo
						char patent[10];
						printf("Ingrese la patente del vehiculo a alquilar: ");
						scanf(" %s", patent);
						if (!esPatente(patent)) {
							printf("\nError: Formato de patente invalido (debe ser AAA999 o AA999AA).\n\n");
							break;
						}
						if (!existeVeh(patent)) {
							printf("\nError: El vehiculo con patente %s no existe en el sistema.\n\n", patent);
							break;
						}
						if (!estaDisponible(patent)) {
							printf("\nError: El vehiculo con patente %s no esta disponible para alquilar.\n\n", patent);
							break;
						}
						struct vehiculo vVeh;
						obtenerVehiculo(patent, &vVeh);
						printf("Vehiculo seleccionado: %s %s (Patente: %s) - Tarifa: $%.2f/dia\n\n",
						       vVeh.marca, vVeh.modelo, patent, vVeh.precioPorDia);

						// 3. Validar Fechas y calcular duracion en dias de forma automatica
						struct fechas feini, fepre;
						printf("Ingrese la fecha inicial del alquiler (dia mes anio separados por espacio): ");
						if (scanf("%d %d %d", &feini.dia, &feini.mes, &feini.anio) != 3 || !esFechaValida(feini)) {
							printf("\nError: Fecha inicial invalida.\n\n");
							while (getchar() != '\n');
							break;
						}
						printf("Ingrese la fecha prevista de devolucion (dia mes anio separados por espacio): ");
						if (scanf("%d %d %d", &fepre.dia, &fepre.mes, &fepre.anio) != 3 || !esFechaValida(fepre)) {
							printf("\nError: Fecha prevista de devolucion invalida.\n\n");
							while (getchar() != '\n');
							break;
						}
						if (compararFechas(feini, fepre) > 0) {
							printf("\nError: La fecha prevista de devolucion no puede ser anterior a la fecha inicial.\n\n");
							break;
						}

						// Cantidad de dias automatica a partir de las fechas
						int days = diasEntreFechas(feini, fepre);
						if (days <= 0) {
							days = 1; // Si retira y devuelve el mismo dia se cuenta como al menos 1 jornada
						}

						// La fecha real de devolucion queda pendiente hasta el momento de la devolucion
						struct fechas fereal = {0, 0, 0};

						// 4. Calcular precio automaticamente en base a la tarifa del vehiculo y los dias
						float costot = days * vVeh.precioPorDia;
						printf("\nDuracion calculada:       %d dia(s)\n", days);
						printf("Costo total del alquiler: $%.2f (%d dias x $%.2f/dia)\n\n", costot, days, vVeh.precioPorDia);

						// 5. Monto inicial que abona el cliente (opcional: total, parcial o $0)
						float costpag = 0.0f;
						printf("Ingrese el monto abonado por el cliente al retirar (0 a $%.2f): $", costot);
						if (scanf("%f", &costpag) != 1 || costpag < 0 || costpag > costot + 0.01f) {
							printf("Monto invalido o superior al total pactado. Se establece en $0.00.\n");
							costpag = 0.0f;
							while (getchar() != '\n');
						}

						int state = 1; // 1: Activo

						// 6. Resumen y confirmacion
						printf("\n-------------------- Resumen del Alquiler --------------------\n");
						printf("Numero de alquiler:           %d (Asignado automaticamente)\n", numal);
						printf("Cliente:                      %s %s (DNI: %d)\n", cCli.nombre, cCli.apellido, dnicli);
						printf("Vehiculo:                     %s %s (Patente: %s)\n", vVeh.marca, vVeh.modelo, patent);
						printf("Fecha de inicio:              %02d/%02d/%04d\n", feini.dia, feini.mes, feini.anio);
						printf("Fecha prevista devolucion:    %02d/%02d/%04d\n", fepre.dia, fepre.mes, fepre.anio);
						printf("Fecha devolucion real:        Pendiente (al registrar la devolucion)\n");
						printf("Duracion:                     %d dia(s)\n", days);
						printf("Tarifa por dia:               $%.2f\n", vVeh.precioPorDia);
						printf("Costo total:                  $%.2f\n", costot);
						printf("Monto abonado al retirar:     $%.2f\n", costpag);
						printf("Saldo pendiente:              $%.2f\n", costot - costpag);
						printf("Estado inicial:               1 (Activo)\n");
						printf("--------------------------------------------------------------\n");

						printf("\n¿Desea confirmar el registro del alquiler? [Y/N]: ");
						scanf(" %c", &quehacer2);
						if (quehacer2 == 'y' || quehacer2 == 'Y' || quehacer2 == 's' || quehacer2 == 'S') {
							registrarAlquiler(numal, dnicli, patent, feini, fepre, fereal, days, costot, costpag, state);
						} else {
							printf("\nOperacion cancelada por el usuario.\n\n");
						}
						break;
					}
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
						printf("\n�Desea confirmar la modificacion? (Y/N):      \t");
						scanf(" %c", &decision);
						if((decision == 'Y') || (decision == 'y') || (decision == 'S') || (decision == 's')){
							modificarAlquiler(al.numAlq, al.dniCliente, al.patVehiculo, al.fechaInicio, al.fechaPreDevolucion, al.fechaRealDevolucion, al.dias, al.costoTotal, al.totalPagado, al.estado);
						}else{
							printf("\nModificacion cancelada por el usuario\n");
							break;
						}
						break;
					}
					case 3: { // Listar alquileres
						listarAlquileres();
						break;
					}
					case 0:
						break;
					default:
						printf("\nOpcion invalida.\n\n");
						break;
				}
				break;
			}
			case 4: { // Devoluciones
				int criterioDev = 0;
				printf("\n================ REGISTRAR DEVOLUCION ================\n");
				printf("Buscar alquiler activo por:\n");
				printf("1. Numero de alquiler\n");
				printf("2. Patente del vehiculo\n");
				printf("0. Volver\n");
				printf("Seleccione una opcion: ");
				if (scanf("%d", &criterioDev) != 1 || criterioDev == 0) {
					while (getchar() != '\n');
					break;
				}

				struct alquileres alDev = {0};
				int encontradoDev = 0;

				if (criterioDev == 1) {
					int numAlqDev;
					printf("Ingrese el numero de alquiler: ");
					if (scanf("%d", &numAlqDev) == 1) {
						if (existeAlquiler(numAlqDev)) {
							obtenerAlquiler(numAlqDev, &alDev);
							if (alDev.estado == 1) {
								encontradoDev = 1;
							} else {
								printf("\nEl alquiler Nro %d no esta activo (Estado actual: %d).\n\n", numAlqDev, alDev.estado);
							}
						} else {
							printf("\nEl alquiler Nro %d no existe.\n\n", numAlqDev);
						}
					} else {
						while (getchar() != '\n');
						printf("\nNumero invalido.\n\n");
					}
				} else if (criterioDev == 2) {
					char patDev[10];
					printf("Ingrese la patente del vehiculo: ");
					scanf(" %s", patDev);
					if (buscarAlquilerActivoPorVehiculo(patDev, &alDev)) {
						encontradoDev = 1;
					} else {
						printf("\nNo se encontro ningun alquiler activo con la patente %s.\n\n", patDev);
					}
				}

				if (encontradoDev) {
					struct cliente cDev;
					obtenerCliente(alDev.dniCliente, &cDev);
					struct vehiculo vDev;
					obtenerVehiculo(alDev.patVehiculo, &vDev);

					printf("\n--- Datos del Alquiler Activo ---\n");
					printf("Numero de alquiler:       %d\n", alDev.numAlq);
					printf("Cliente:                  %s %s (DNI: %d)\n", cDev.nombre, cDev.apellido, alDev.dniCliente);
					printf("Vehiculo:                 %s %s (Patente: %s)\n", vDev.marca, vDev.modelo, alDev.patVehiculo);
					printf("Km actuales registrados:  %d\n", vDev.kmactual);
					printf("Fecha de inicio:          %02d/%02d/%04d\n", alDev.fechaInicio.dia, alDev.fechaInicio.mes, alDev.fechaInicio.anio);
					printf("Fecha prevista dev.:      %02d/%02d/%04d\n", alDev.fechaPreDevolucion.dia, alDev.fechaPreDevolucion.mes, alDev.fechaPreDevolucion.anio);
					printf("Dias contratados:         %d dias\n", alDev.dias);
					printf("Costo inicial pactado:    $%.2f\n", alDev.costoTotal);
					printf("Total abonado hasta hoy:  $%.2f\n", alDev.totalPagado);
					printf("----------------------------------\n");

					struct fechas fReal;
					printf("\nIngrese la fecha real de devolucion (dia mes anio separados por espacio): ");
					if (scanf("%d %d %d", &fReal.dia, &fReal.mes, &fReal.anio) != 3 || !esFechaValida(fReal)) {
						printf("\nError: Fecha invalida.\n\n");
						while (getchar() != '\n');
						break;
					}

					if (compararFechas(fReal, alDev.fechaInicio) < 0) {
						printf("\nError: La fecha de devolucion no puede ser anterior a la fecha de inicio.\n\n");
						break;
					}

					int kmDevolucion = vDev.kmactual;
					printf("Ingrese el kilometraje final del vehiculo: ");
					if (scanf("%d", &kmDevolucion) != 1 || kmDevolucion < vDev.kmactual) {
						printf("Aviso: Kilometraje no valido o menor al anterior. Se conserva %d km.\n", vDev.kmactual);
						kmDevolucion = vDev.kmactual;
					}

					int diasReales = diasEntreFechas(alDev.fechaInicio, fReal);
					if (diasReales < 1) diasReales = 1;

					float costoFinal = alDev.costoTotal;
					if (diasReales > alDev.dias) {
						int diasExtra = diasReales - alDev.dias;
						float recargo = diasExtra * vDev.precioPorDia;
						costoFinal += recargo;
						printf("\n>>> ENTREGA CON DEMORA: %d dias de retraso. Recargo: $%.2f. <<<\n", diasExtra, recargo);
					}

					float saldoPendiente = costoFinal - alDev.totalPagado;
					if (saldoPendiente < 0) saldoPendiente = 0;

					printf("\n--- Liquidacion Final ---\n");
					printf("Costo total final:  $%.2f\n", costoFinal);
					printf("Total ya abonado:   $%.2f\n", alDev.totalPagado);
					printf("Saldo pendiente:    $%.2f\n", saldoPendiente);
					printf("-------------------------\n");

					float pagoDev = 0;
					struct fechas fPago = fReal;
					if (saldoPendiente > 0.001f) {
						char deseaPagar;
						printf("¿Desea registrar el pago total o parcial ahora mismo [Y/N]? ");
						scanf(" %c", &deseaPagar);
						if (deseaPagar == 'Y' || deseaPagar == 'y' || deseaPagar == 'S' || deseaPagar == 's') {
							printf("Ingrese el monto a abonar (Saldo pendiente: $%.2f): ", saldoPendiente);
							if (scanf("%f", &pagoDev) != 1 || pagoDev <= 0 || pagoDev > saldoPendiente + 0.01f) {
								printf("Monto invalido o superior al saldo. No se registrara pago en este paso.\n");
								pagoDev = 0;
							}
						}
					}

					char confDev;
					printf("\n¿Confirmar devolucion del vehiculo [Y/N]? ");
					scanf(" %c", &confDev);
					if (confDev == 'Y' || confDev == 'y' || confDev == 'S' || confDev == 's') {
						if (registrarDevolucion(alDev.numAlq, fReal, kmDevolucion, pagoDev, fPago) == 0) {
							printf("\nVehiculo devuelto con exito. Estado del vehiculo actualizado a DISPONIBLE.\n");
							if (saldoPendiente - pagoDev > 0.001f) {
								printf("NOTA: El cliente aun adeuda $%.2f (puede abonarlo en el menu de Pagos).\n\n", saldoPendiente - pagoDev);
							} else {
								printf("El alquiler ha quedado 100%% saldado.\n\n");
							}
						} else {
							printf("\nError al registrar la devolucion.\n\n");
						}
					} else {
						printf("\nDevolucion cancelada por el usuario.\n\n");
					}
				}
				break;
			}
			case 5: { // Pagos
				int opcPagos = 0;
				printf("\n================ GESTION DE PAGOS ================\n");
				printf("1. Registrar pago de un alquiler\n");
				printf("2. Consultar historial de movimientos/pagos de un cliente\n");
				printf("3. Listar todos los movimientos registrados\n");
				printf("0. Volver\n");
				printf("Seleccione una opcion: ");
				if (scanf("%d", &opcPagos) != 1 || opcPagos == 0) {
					while (getchar() != '\n');
					break;
				}

				if (opcPagos == 1) {
					int numAlqPago;
					printf("\nIngrese el numero de alquiler a pagar: ");
					if (scanf("%d", &numAlqPago) != 1) {
						printf("\nError: Debe ingresar un numero valido.\n\n");
						while (getchar() != '\n');
						break;
					}
					if (!existeAlquiler(numAlqPago)) {
						printf("\nEl alquiler Nro %d no existe.\n\n", numAlqPago);
						break;
					}

					struct alquileres alPago;
					obtenerAlquiler(numAlqPago, &alPago);
					float saldo = alPago.costoTotal - alPago.totalPagado;

					struct cliente cPago;
					obtenerCliente(alPago.dniCliente, &cPago);

					printf("\n--- Detalle del Alquiler Nro %d ---\n", alPago.numAlq);
					printf("Cliente:            %s %s (DNI: %d)\n", cPago.nombre, cPago.apellido, alPago.dniCliente);
					printf("Vehiculo:           %s\n", alPago.patVehiculo);
					printf("Estado alquiler:    %s\n", (alPago.estado == 1) ? "Activo" : (alPago.estado == 2) ? "Finalizado" : "Cancelado");
					printf("Costo total:        $%.2f\n", alPago.costoTotal);
					printf("Total abonado:      $%.2f\n", alPago.totalPagado);
					printf("Saldo pendiente:    $%.2f\n", saldo);
					printf("----------------------------------\n");

					if (saldo <= 0.001f) {
						printf("\nEste alquiler ya se encuentra totalmente saldado.\n\n");
						break;
					}

					float montoAbonar;
					printf("Ingrese el monto a abonar (Maximo $%.2f): ", saldo);
					if (scanf("%f", &montoAbonar) != 1 || montoAbonar <= 0 || montoAbonar > saldo + 0.01f) {
						printf("\nError: Monto invalido o superior al saldo adeudado.\n\n");
						while (getchar() != '\n');
						break;
					}

					struct fechas fPago;
					printf("Ingrese la fecha del pago (dia mes anio separados por espacio): ");
					if (scanf("%d %d %d", &fPago.dia, &fPago.mes, &fPago.anio) != 3 || !esFechaValida(fPago)) {
						printf("\nError: Fecha invalida.\n\n");
						while (getchar() != '\n');
						break;
					}

					char confPago;
					printf("Confirma registrar el pago de $%.2f [Y/N]? ", montoAbonar);
					scanf(" %c", &confPago);
					if (confPago == 'Y' || confPago == 'y' || confPago == 'S' || confPago == 's') {
						registrarPagoAlquiler(alPago.numAlq, montoAbonar, fPago);
					} else {
						printf("\nPago cancelado por el usuario.\n\n");
					}
				} else if (opcPagos == 2) {
					int dniHist;
					printf("\nIngrese el DNI del cliente para ver su historial: ");
					if (scanf("%d", &dniHist) == 1 && esDNI(dniHist)) {
						listarMovimientosCliente(dniHist);
					} else {
						printf("\nDNI invalido.\n\n");
						while (getchar() != '\n');
					}
				} else if (opcPagos == 3) {
					listarTodosMovimientos();
				}
				break;
			}
			case 6: { // Consultas y reportes
				int opcRep = 0;
				do {
					printf("\n======================= MENU DE CONSULTAS Y REPORTES =======================\n");
					printf("1.  Vehiculos disponibles\n");
					printf("2.  Vehiculos alquilados actualmente (con detalle del alquiler)\n");
					printf("3.  Alquileres por rango de fechas de inicio\n");
					printf("4.  Alquileres por cliente (DNI)\n");
					printf("5.  Alquileres por vehiculo (Patente)\n");
					printf("6.  Alquileres por estado (Activos / Finalizados / Cancelados)\n");
					printf("7.  Alquileres por importe (Mayores o menores a un valor)\n");
					printf("8.  Pagos realizados en un periodo determinado\n");
					printf("9.  Clientes con deuda pendiente\n");
					printf("10. Estadisticas generales de la empresa\n");
					printf("11. Exportar todos los reportes a archivos de texto (.txt)\n");
					printf("0.  Volver al menu principal\n");
					printf("Seleccione una opcion: ");

					if (scanf("%d", &opcRep) != 1) {
						while (getchar() != '\n');
						printf("\nOpcion invalida.\n\n");
						continue;
					}

					switch (opcRep) {
						case 1: {
							listarVehiculosDisponibles();
							break;
						}
						case 2: {
							listarVehiculosAlquiladosDetalle();
							break;
						}
						case 3: {
							struct fechas fDesde, fHasta;
							printf("\nIngrese fecha inicial (dia mes anio separados por espacio): ");
							if (scanf("%d %d %d", &fDesde.dia, &fDesde.mes, &fDesde.anio) != 3 || !esFechaValida(fDesde)) {
								printf("\nError: Fecha inicial invalida.\n\n");
								while (getchar() != '\n');
								break;
							}
							printf("Ingrese fecha final (dia mes anio separados por espacio): ");
							if (scanf("%d %d %d", &fHasta.dia, &fHasta.mes, &fHasta.anio) != 3 || !esFechaValida(fHasta)) {
								printf("\nError: Fecha final invalida.\n\n");
								while (getchar() != '\n');
								break;
							}
							if (compararFechas(fDesde, fHasta) > 0) {
								printf("\nError: La fecha inicial no puede ser posterior a la fecha final.\n\n");
								break;
							}
							listarAlquileresPorRangoFechas(fDesde, fHasta);
							break;
						}
						case 4: {
							int dniCli;
							printf("\nIngrese el DNI del cliente: ");
							if (scanf("%d", &dniCli) != 1 || !esDNI(dniCli)) {
								printf("\nError: DNI invalido.\n\n");
								while (getchar() != '\n');
								break;
							}
							listarAlquileresPorCliente(dniCli);
							break;
						}
						case 5: {
							char pat[10];
							printf("\nIngrese la patente del vehiculo: ");
							scanf(" %s", pat);
							listarAlquileresPorVehiculo(pat);
							break;
						}
						case 6: {
							int est = 0;
							printf("\nSeleccione estado a consultar:\n");
							printf("1. Activos\n");
							printf("2. Finalizados\n");
							printf("0. Cancelados\n");
							printf("Opcion: ");
							if (scanf("%d", &est) != 1 || (est != 0 && est != 1 && est != 2)) {
								printf("\nEstado invalido.\n\n");
								while (getchar() != '\n');
								break;
							}
							listarAlquileresPorEstado(est);
							break;
						}
						case 7: {
							int crit = 0;
							float val = 0;
							printf("\nSeleccione criterio:\n");
							printf("1. Alquileres con importe MAYOR a un valor\n");
							printf("2. Alquileres con importe MENOR a un valor\n");
							printf("Opcion: ");
							if (scanf("%d", &crit) != 1 || (crit != 1 && crit != 2)) {
								printf("\nCriterio invalido.\n\n");
								while (getchar() != '\n');
								break;
							}
							printf("Ingrese el valor del importe: $");
							if (scanf("%f", &val) != 1 || val < 0) {
								printf("\nImporte invalido.\n\n");
								while (getchar() != '\n');
								break;
							}
							listarAlquileresPorImporte(val, crit);
							break;
						}
						case 8: {
							struct fechas fDesde, fHasta;
							printf("\nIngrese fecha inicial del periodo (dia mes anio separados por espacio): ");
							if (scanf("%d %d %d", &fDesde.dia, &fDesde.mes, &fDesde.anio) != 3 || !esFechaValida(fDesde)) {
								printf("\nError: Fecha inicial invalida.\n\n");
								while (getchar() != '\n');
								break;
							}
							printf("Ingrese fecha final del periodo (dia mes anio separados por espacio): ");
							if (scanf("%d %d %d", &fHasta.dia, &fHasta.mes, &fHasta.anio) != 3 || !esFechaValida(fHasta)) {
								printf("\nError: Fecha final invalida.\n\n");
								while (getchar() != '\n');
								break;
							}
							if (compararFechas(fDesde, fHasta) > 0) {
								printf("\nError: La fecha inicial no puede ser posterior a la fecha final.\n\n");
								break;
							}
							listarPagosPorPeriodo(fDesde, fHasta);
							break;
						}
						case 9: {
							listarClientesConDeuda();
							break;
						}
						case 10: {
							generarEstadisticasEmpresa();
							break;
						}
						case 11: {
							printf("\nExportando todos los reportes a disco...\n");
							exportarClientesTxt();
							exportarVehiculosTxt();
							exportarAlquileresTxt();
							exportarMovimientosTxt();
							printf("Todos los reportes .txt fueron generados exitosamente.\n\n");
							break;
						}
						case 0:
							break;
						default:
							printf("\nOpcion no reconocida.\n\n");
							break;
					}

					if (opcRep != 0) {
						system("pause");
					}
				} while (opcRep != 0);

				break;
			}
			case 0: // Salir
				printf("\nSaliendo del sistema...\n\n");
				break;
			default:
				printf("\nOpcion invalida.\n\n");
				opcion = -1;
		}
		fflush(stdin);
		system("pause");

	} while (opcion != 0);

	return 0;
}
