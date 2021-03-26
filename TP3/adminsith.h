#ifndef ADMINSITH_H
#define ADMINSITH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void agregarSistema(char* descripcion);

void agregarPlaneta(char* descripcion);

void consultarSistemasYPlanetas();

void actualizarAlumnos(char * archivoActu);

int expulsarJedi(int porcentajeMinimo);

void consultarDatosAlumno(char * codigoALumno);

//int actualizarRespuestas(); // Opcional para los que vayan por la promocion

#endif