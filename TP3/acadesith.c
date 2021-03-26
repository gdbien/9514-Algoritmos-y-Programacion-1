#include "adminsith.h"

const char AGREGAR_SISTEMA[]="-addsi";
const char AGREGAR_PLANETA[]="-addpl";
const char CONSULTAR_SISTEMAS_Y_PLANETAS[]="-consp";
const char ACTUALIZAR_ALUMNOS[]="-updal";
const char EXPULSAR_JEDI[]="-delje";
const char CONSULTAR_DATOS_ALUMNO[]="-conal";
//const char ACTUALIZAR_RESPUESTAS[]="-updre";

#define ERROR_001 "ERROR 001:Cantidad insuficiente de parametros ingresados"
#define ERROR_002 "ERROR 002:Ingreso demasiados parametros"
#define ERROR_003 "ERROR 003:La cantidad de caracteres del parametro excede el limite o es nulo"
#define ERROR_004 "ERROR 004:No realizo el llamado de una funcion existente"
#define ERROR_005 "ERROR 005:Porcentaje invalido, solo es valido un numero entre 70 y 100"

#define MAX_LARGO_DESCRIPCION 50
#define MIN_PORCENTAJE_LUZ 70
#define MAX_PORCENTAJE_LUZ 100
#define ERROR -1

bool esValidaLaDescripcion(const char* descripcion){
	size_t largoDescripcion=strlen(descripcion);
	int i,cantidadDeEspacios=0;

	if (largoDescripcion>MAX_LARGO_DESCRIPCION || largoDescripcion==0) {
		return false;
	}
	for (i=0;i<largoDescripcion;i++) {
		if (descripcion[i]==' ') {
			cantidadDeEspacios++;
		}
	}
	if (cantidadDeEspacios==largoDescripcion) {
		return false;
	}
	return true;
}

int main(int argc, char const *argv[]){
	int cantidadParametros=argc;
	int porcentajeMinimo;
	char descripcion[MAX_LARGO_DESCRIPCION];

	switch (cantidadParametros) {
		case 1:
			perror(ERROR_001);
			return ERROR;
		break;
		case 2:
			if (strcmp(argv[1],CONSULTAR_SISTEMAS_Y_PLANETAS)==0) {
				consultarSistemasYPlanetas();
			} else {
				if (strcmp(argv[1],AGREGAR_PLANETA)==0) {
					perror(ERROR_001);
					return ERROR;
				} else {
					if (strcmp(argv[1],AGREGAR_SISTEMA)==0){
						perror(ERROR_001);
						return ERROR;	
					} else { 
						if (strcmp(argv[1],CONSULTAR_DATOS_ALUMNO)==0) {
							perror(ERROR_001);
							return ERROR;	
						} else {
							if (strcmp(argv[1],ACTUALIZAR_ALUMNOS)==0) {
								perror(ERROR_001);
								return ERROR;
							} else {
								if (strcmp(argv[1],EXPULSAR_JEDI)==0) {
									perror(ERROR_001);
									return ERROR;
								} else {
									perror(ERROR_004);
									return ERROR;
								}
							}
						}
					}
				}
			}	
		break;
		case 3:
			if (strcmp(argv[1],AGREGAR_SISTEMA)==0) {
				if (esValidaLaDescripcion(argv[2])) {
					strcpy(descripcion,argv[2]);
					agregarSistema(descripcion);
				} else {
					perror(ERROR_003);
					return ERROR;
				}
			} else {
				if (strcmp(argv[1],AGREGAR_PLANETA)==0) {
					if (esValidaLaDescripcion(argv[2])) {
						strcpy(descripcion,argv[2]);
						agregarPlaneta(descripcion);
					} else {
						perror(ERROR_003);
						return ERROR;
					}
				} else {
					if (strcmp(argv[1],CONSULTAR_DATOS_ALUMNO)==0) {
						char codigoAlumno[11];
						strcpy(codigoAlumno,argv[2]);
						consultarDatosAlumno(codigoAlumno);
					} else {
						if (strcmp(argv[1],ACTUALIZAR_ALUMNOS)==0) {
							char nombreArchivo[MAX_LARGO_DESCRIPCION];
							strcpy(nombreArchivo,argv[2]);
							actualizarAlumnos(nombreArchivo);
						} else {
							if (strcmp(argv[1],EXPULSAR_JEDI)==0) {
								porcentajeMinimo=atoi(argv[2]);
								if (porcentajeMinimo>=MIN_PORCENTAJE_LUZ && porcentajeMinimo<=MAX_PORCENTAJE_LUZ) {
									expulsarJedi(porcentajeMinimo);
								} else {
									perror(ERROR_005);
									return ERROR;
								}
							} else {
								perror(ERROR_002);
								return ERROR;
							}
						}
					}
				}
			} 
		break;
		default:
			perror(ERROR_002);
			return ERROR;
		break;
	}
	return 0;
}
/*
boolpepe(int cantidadParametros){
	if (cantidadParametros==1) {
		perror("No realizo el llamado a una funcion");
	} else {
		if (cantidadParametros==2) {
			funcion(cantidadParametros,argv[2])
		}
	}
	
}

int cantidadPametrosValidos(const char* funcion){
	if (strcmp(funcion,AGREGAR_SISTEMA)==0) {
		return true;
	}
	if (strcmp(funcion,AGREGAR_PLANETA)==0) {
		return true
	}
	if (strcmp(funcion,CONSULTAR_DATOS_ALUMNO)==0) {
		return true;
	}
	if (strcmp(funcion,EXPULSAR_JEDI)==0) {
		return true;
	}
	if (strcmp(funcion,ACTUALIZAR_ALUMNOS)==0) {
		return true;
	}
	if (strcmp(funcion,CONSULTAR_SISTEMAS_Y_PLANETAS)==0) {
		return true;
	}


}
*/