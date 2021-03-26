#include "adminsith.h"


#define LENGTH_NOM_APE 21
#define LENGTH_EMAIL 101
#define LENGTH_FECHA 9
#define LENGTH_DESCRIPCION 51
#define LENGTH_CODIGO 11
#define ERROR -1

const char PLANETA='P';
const char SISTEMA='S';
const char SEPARADOR=';';
const char ESPACIO=' ';
const char* FILENAME_SISTEMAS_Y_PLANETAS="sistyplan.dat";
const char* FILENAME_ALUMNOS="alumnos.txt";
const char* FILENAME_MERGE="merge.txt";
const char* FILENAME_RESPUESTAS="respxalum.txt";

typedef struct respuesta{
	char codigoAlumno[LENGTH_CODIGO];
	char fecha[LENGTH_FECHA];
	char descripcionCurso[LENGTH_DESCRIPCION];
	int cantidadRespuestasLuz;
	int cantidadRespuestasOscuridad;
} tRespuesta;

typedef struct alumno{
	char codigo[LENGTH_CODIGO];
	char nombre[LENGTH_NOM_APE];
	char apellido[LENGTH_NOM_APE];
	char email[LENGTH_EMAIL];
	size_t codigoSistemaOrigen;
	size_t codigoPlanetaOrigen;
} tAlumno;

typedef struct sistemayplaneta{
	size_t codigo;
	char description[LENGTH_DESCRIPCION];
	char indicadorDeTipo;
} tSistyplan;

void cargarSistemaOPlaneta(char* descripcion, char tipo){
	tSistyplan systemAndPlanet;
	size_t indice=0;
	int seek;
	FILE* fSistyplan=fopen(FILENAME_SISTEMAS_Y_PLANETAS,"a+");
		
	if (!fSistyplan) {
		perror("Falla al abrir/leer el archivo");
		return;
	}

	seek=fseek(fSistyplan,0,SEEK_SET);
	if (seek!=0) {
		perror("ERROR:Se produjo un error al querer acceder a espacio que no nos corresponde");
		return;
	}
	fread(&systemAndPlanet, sizeof(tSistyplan),1, fSistyplan);
	while (!feof(fSistyplan)) {
		if ((strcmp(systemAndPlanet.description,descripcion))==0) {
			perror("Error: Se encontro un sistema/planeta con la misma descripcion");
            return;
		}
		fread(&systemAndPlanet, sizeof(tSistyplan),1, fSistyplan);
	}

	seek=fseek(fSistyplan,0,SEEK_SET);
	if (seek!=0) {
		perror("ERROR:Se produjo un error al querer acceder a espacio que no nos corresponde");
		return;
	}
	while (!feof(fSistyplan)) {
		indice+=fread(&systemAndPlanet,sizeof(tSistyplan),1,fSistyplan);
	}

	strcpy(systemAndPlanet.description,descripcion);
	systemAndPlanet.codigo=indice;
	if (tipo==SISTEMA) {
		systemAndPlanet.indicadorDeTipo=SISTEMA;
	} else {
		systemAndPlanet.indicadorDeTipo=PLANETA;
	}
	fwrite(&systemAndPlanet,sizeof(tSistyplan),1,fSistyplan);

	fclose(fSistyplan);
}
	
void agregarSistema(char* descripcion){
	cargarSistemaOPlaneta(descripcion,SISTEMA);
}

void agregarPlaneta(char* descripcion){
	cargarSistemaOPlaneta(descripcion,PLANETA);
}

void consultarSistemasYPlanetas(){
	tSistyplan systemAndPlanet;
	FILE* fSistyplan=fopen(FILENAME_SISTEMAS_Y_PLANETAS,"r");

	if (!fSistyplan) {
		perror("ERROR: FALLA AL LEER EL ARCHIVO");
		return;
	}
	
	fread(&systemAndPlanet, sizeof(tSistyplan), 1, fSistyplan);
	while (!feof(fSistyplan)) {
		printf("-------------------------------\n");
		printf("Codigo: %d\n", systemAndPlanet.codigo);
		printf("Descripcion: %s\n", systemAndPlanet.description);
		printf("Indicador de tipo: %c\n", systemAndPlanet.indicadorDeTipo);
		printf("-------------------------------\n");
		fread(&systemAndPlanet, sizeof(tSistyplan), 1, fSistyplan);
	}
	fclose(fSistyplan);
}

bool existeAlumno(char* codigoAlumno,tAlumno* alumno){
	int scan;
	FILE* fOriginal=fopen(FILENAME_ALUMNOS,"r");

	if (!fOriginal) {
		perror("Error en la lectura del archivo");
		return false;
	}
	
	while (0 < (scan=fscanf(fOriginal,"%[^;];%[^;];%[^;];%[^;];%zu;%zu\n", alumno->codigo, alumno->nombre, alumno->apellido, alumno->email, &(alumno->codigoSistemaOrigen), &(alumno->codigoPlanetaOrigen)))) {
		if (scan !=6) {
			perror("Se produjo un error al cargar los datos");
			return false;
		}
		if(strcmp(alumno->codigo,codigoAlumno)==0){
			return true;
		}
	}
	return false;
	fclose(fOriginal);
}

void buscarDescripcionSisYPla(size_t codigo, tSistyplan* systemAndPlanet){
	FILE* fSistyplan=fopen(FILENAME_SISTEMAS_Y_PLANETAS,"r");
	size_t offset;
	int seek;

	if (!fSistyplan) {
		perror("Error en la lectura del archivo");
		return;
	}

	offset=codigo*sizeof(tSistyplan);
	seek=fseek(fSistyplan,(long int)offset,SEEK_SET);
	if (seek!=0) {
		perror("Se produjo un error al querer acceder a espacio que no nos corresponde");
		return;
	}
	fread(systemAndPlanet, sizeof(tSistyplan), 1, fSistyplan);

	fclose(fSistyplan);
}

void imprimirDescripcionSegunCodigo(size_t codigoSistemaOrigen, size_t codigoPlanetaOrigen){
	tSistyplan systemAndPlanet;

	buscarDescripcionSisYPla(codigoSistemaOrigen,&systemAndPlanet);
	printf("Descripcion Sistema de Origen: %s\n",systemAndPlanet.description);
	buscarDescripcionSisYPla(codigoPlanetaOrigen,&systemAndPlanet);
	printf("Descripcion Planeta de Origen: %s\n",systemAndPlanet.description);
}


void consultarDatosAlumno(char* codigoAlumno){
	tAlumno alumno;

	if (existeAlumno(codigoAlumno,&alumno)) {
		printf("-------------------------------\n");
		printf("Nombre: %s\n", alumno.nombre);
		printf("Apellido: %s\n", alumno.apellido);
		printf("Email: %s\n", alumno.email);
		imprimirDescripcionSegunCodigo(alumno.codigoSistemaOrigen,alumno.codigoPlanetaOrigen);
		printf("-------------------------------\n");
	} else {
		printf("No se encontro alumno con ese codigo\n");
		return;
	}
}

bool cargarAlumno(FILE* fArchivo, tAlumno* alumno){
	int scan;

	scan=fscanf(fArchivo,"%[^;];%[^;];%[^;];%[^;];%zu;%zu\n",alumno->codigo, alumno->nombre, alumno->apellido, alumno->email, &alumno->codigoSistemaOrigen, &alumno->codigoPlanetaOrigen);
	if (scan==6){
		return true;
	}
	return false;
}

void guardarAlumno(FILE* fArchivo, tAlumno alumno){	
	fprintf(fArchivo,"%s;%s;%s;%s;%zu;%zu\n",alumno.codigo,alumno.nombre,alumno.apellido,alumno.email,alumno.codigoSistemaOrigen,alumno.codigoPlanetaOrigen);
	return;
}

bool esPalabraValida(char palabra[], char caso[]){
	int i,lengthMax;
	size_t longitud;

	if (strcmp("NOMBRE",caso)==0||strcmp("APELLIDO",caso)==0) {
		lengthMax=LENGTH_NOM_APE;
	} else {
		if (strcmp("EMAIL",caso)==0) {
			lengthMax=LENGTH_EMAIL;
		}
	}
	longitud=strlen(palabra);

	if (longitud>=lengthMax || longitud==0) {
		return false;
	}
	for (i=0;i<longitud;i++) {
		if (palabra[i]==ESPACIO) {
			return false;
		}
	}
	return true;
}

bool esCodigoPSValido(size_t codigo, char tipo) {
	tSistyplan systemAndPlanet;
	FILE* fSistyplan=fopen(FILENAME_SISTEMAS_Y_PLANETAS,"r");
	int seek;
	size_t offset;

	if (!fSistyplan) {
		perror("Error en la lectura del archivo");
		return false;
	}

	offset=codigo*sizeof(tSistyplan);
	seek=fseek(fSistyplan,(long int)offset,SEEK_SET);
	if (seek!=0) {
		return false;
	}
	fread(&systemAndPlanet, sizeof(tSistyplan), 1, fSistyplan);
	if (systemAndPlanet.indicadorDeTipo!=tipo) {
		return false;
	}

	fclose(fSistyplan);
	return true;	
}

bool sistemaYPlanetaValidos(size_t sistema, size_t planeta) {
	if(!esCodigoPSValido(sistema,SISTEMA)){
		return false;
	}
	if(!esCodigoPSValido(planeta,PLANETA)){
		return false;
	}
	return true;
}

bool datosSonValidos(tAlumno alumno){
	if (!sistemaYPlanetaValidos(alumno.codigoSistemaOrigen,alumno.codigoPlanetaOrigen)) {
		return false;
	}
	if (!esPalabraValida(alumno.nombre,"NOMBRE")) {
		return false;
	}
	if (!esPalabraValida(alumno.apellido,"APELLIDO")) {
		return false;
	}
	if (!esPalabraValida(alumno.email,"EMAIL")) {
		return false;
	}
	return true;
}
/*
void actualizarAlumnos(char * archivoActu){
	tAlumno desdeOriginal;
	tAlumno desdeActualizacion;
	FILE* fOriginal=fopen(FILENAME_ALUMNOS,"r");
	FILE* fActualizacion=fopen(archivoActu,"r");
	FILE* fMerge=fopen(FILENAME_MERGE,"w");

	if (!fOriginal) {
		perror("Error al abrir el archivo");
		return;
	}
	if (!fActualizacion) {
		perror("El archivo no existe");
		return;
	}
	if (!fMerge) {
		perror("Error apertura del archivo");
		return;
	}

	bool leyoActualizaciones=cargarAlumno(fActualizacion,&desdeActualizacion);
	bool leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);

	while(leyoOriginal||leyoActualizaciones){
		if (!leyoOriginal) {
			if (datosSonValidos(desdeActualizacion)) {
				guardarAlumno(fMerge,desdeActualizacion);
			}
			leyoActualizaciones=cargarAlumno(fActualizacion,&desdeActualizacion);	
		} else {
			if (!leyoActualizaciones) {
				guardarAlumno(fMerge,desdeOriginal);
				leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);
			} else {
				if (strcmp(desdeOriginal.codigo,desdeActualizacion.codigo)<0) {
					guardarAlumno(fMerge,desdeOriginal);
					leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);
				} else {
					if (strcmp(desdeOriginal.codigo,desdeActualizacion.codigo)==0) {
						if (datosSonValidos(desdeActualizacion)) {
							guardarAlumno(fMerge,desdeActualizacion);
						} else {
							guardarAlumno(fMerge,desdeOriginal);
						}
						leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);
						leyoActualizaciones=cargarAlumno(fActualizacion,&desdeActualizacion);
					} else {
						if (strcmp(desdeOriginal.codigo,desdeActualizacion.codigo)>0) {
							if (datosSonValidos(desdeActualizacion)) {
								guardarAlumno(fMerge,desdeActualizacion);
							}
							leyoActualizaciones=cargarAlumno(fActualizacion,&desdeActualizacion);
						}
					}
				}
			}
		}	
	}

	fclose(fOriginal);
	fclose(fActualizacion);
	fclose(fMerge);
	remove(FILENAME_ALUMNOS);
	rename(FILENAME_MERGE,FILENAME_ALUMNOS);
}
*/


bool hayErroresEnLinea(char* linea) {
	int i,cantidadCaracteresAntesDeLinea=0;

	for (i=0;i<strlen(linea);i++) {
		if (linea[i]==',') {
			if (cantidadCaracteresAntesDeLinea==0) {
				return true;
			}
			cantidadCaracteresAntesDeLinea=0;
		} else {
			cantidadCaracteresAntesDeLinea++;
		}
	}
	return false;
}

bool cargarLinea(FILE* fArchivo,char* linea,int longitud){
	if(fgets(linea,longitud,fArchivo)!=NULL){
		return true;
	}
	return false;
}

int cargarAlumnoDesdeLinea(char* linea,tAlumno* alumno){
	int scan;
	scan=sscanf(linea,"%[^;];%[^;];%[^;];%[^;];%zu;%zu\n",alumno->codigo, alumno->nombre, alumno->apellido, alumno->email, &alumno->codigoSistemaOrigen, &alumno->codigoPlanetaOrigen);
	return scan;
}

void actualizarAlumnos(char * archivoActu){
	tAlumno desdeOriginal;
	tAlumno desdeActualizacion;
	char linea[300];
	FILE* fOriginal=fopen(FILENAME_ALUMNOS,"r");
	FILE* fActualizacion=fopen(archivoActu,"r");
	FILE* fMerge=fopen(FILENAME_MERGE,"w");

	if (!fOriginal) {
		perror("Error al abrir el archivo");
		return;
	}
	if (!fActualizacion) {
		perror("El archivo no existe");
		return;
	}
	if (!fMerge) {
		perror("Error apertura del archivo");
		return;
	}
	int longitud=sizeof(linea);
	bool leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);
	bool leyoActualizaciones=cargarLinea(fActualizacion,linea,longitud);


	while(leyoOriginal || leyoActualizaciones){
		if (!hayErroresEnLinea(linea)) {
			if (cargarAlumnoDesdeLinea(linea,&desdeActualizacion)==6) {
			if (!leyoOriginal) {
				if (datosSonValidos(desdeActualizacion)) {
					guardarAlumno(fMerge,desdeActualizacion);
				}
				leyoActualizaciones=cargarLinea(fActualizacion,linea,longitud);	
			} else {
				if (!leyoActualizaciones) {
					guardarAlumno(fMerge,desdeOriginal);
					leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);
				} else {
					if (strcmp(desdeOriginal.codigo,desdeActualizacion.codigo)<0) {
						guardarAlumno(fMerge,desdeOriginal);
						leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);
					} else {
						if (strcmp(desdeOriginal.codigo,desdeActualizacion.codigo)==0) {
							if (datosSonValidos(desdeActualizacion)) {
								guardarAlumno(fMerge,desdeActualizacion);
							} else {
								guardarAlumno(fMerge,desdeOriginal);
							}
							leyoOriginal=cargarAlumno(fOriginal,&desdeOriginal);
							leyoActualizaciones=cargarLinea(fActualizacion,linea,longitud);
						} else {
							if (strcmp(desdeOriginal.codigo,desdeActualizacion.codigo)>0) {
								if (datosSonValidos(desdeActualizacion)) {
									guardarAlumno(fMerge,desdeActualizacion);
								}
								leyoActualizaciones=cargarLinea(fActualizacion,linea,longitud);
							}
						}
					}
				}
			}
			} else {
				leyoActualizaciones=cargarLinea(fActualizacion,linea,longitud);
			}	
		} else {
			leyoActualizaciones=cargarLinea(fActualizacion,linea,longitud);
		}
	}
	
	fclose(fOriginal);
	fclose(fActualizacion);
	fclose(fMerge);
	remove(FILENAME_ALUMNOS);
	rename(FILENAME_MERGE,FILENAME_ALUMNOS);
}


bool cambio(char* palabra1, char* palabra2){
	if (strcmp(palabra1,palabra2)!=0) {
		return true;
	}
	return false;
}

bool cargarDatosRespuesta(FILE* fArchivo, tRespuesta* respuesta){
	int scan;

	scan=fscanf(fArchivo,"%[^;];%[^;];%[^;];%d;%d\n",respuesta->codigoAlumno, respuesta->fecha, respuesta->descripcionCurso, &respuesta->cantidadRespuestasLuz, &respuesta->cantidadRespuestasOscuridad);
	if (scan==5) {
		return true;
	}
	return false;
}

void eliminarAlumno(char* codigoAlumno){
	tAlumno alumno;
	FILE* fAlumno=fopen(FILENAME_ALUMNOS,"r");
	FILE* fMerge=fopen(FILENAME_MERGE,"w");

	if (!fAlumno) {
		perror("Error en la lectura del archivo");
		return;
	}
	if (!fMerge) {
		perror("Error en la lectura del archivo");
		return;
	}

	bool leiUnAlumno=cargarAlumno(fAlumno,&alumno);

	while (leiUnAlumno) {
		if (strcmp(codigoAlumno,alumno.codigo)!=0) {
			guardarAlumno(fMerge,alumno);
		}
		leiUnAlumno=cargarAlumno(fAlumno,&alumno);
	}

	fclose(fMerge);
	fclose(fAlumno);
	remove(FILENAME_ALUMNOS);
	rename(FILENAME_MERGE,FILENAME_ALUMNOS);
}

int expulsarJedi(int porcentajeMinimo){
	tRespuesta respuesta;
	int cantidadExpulsados=0,totalRespuestas=0,cantRespLuminosas=0,porcentajeLuminoso;
	char codigoAlumnoActual[]="12345678910";
	FILE* fResp=fopen(FILENAME_RESPUESTAS,"r");

	if (!fResp) {
		perror("Error al intentar leer el archivo");
		return ERROR;
	}

	bool leiUnaRespuesta=cargarDatosRespuesta(fResp,&respuesta);

	while (leiUnaRespuesta) {
		if (!cambio(codigoAlumnoActual,respuesta.codigoAlumno)) {
			totalRespuestas+=respuesta.cantidadRespuestasLuz+respuesta.cantidadRespuestasOscuridad;
			cantRespLuminosas+=respuesta.cantidadRespuestasLuz;
		} else {
			if (strcmp(codigoAlumnoActual,"12345678910")!=0) { //No chequeo la division por 0 porque eso seria que no tiene respuestas(no aparece en el archivo).
				porcentajeLuminoso=cantRespLuminosas*100/totalRespuestas;		
				if (porcentajeLuminoso>=porcentajeMinimo) {
					eliminarAlumno(codigoAlumnoActual);
					cantidadExpulsados++;
				}
			}
			totalRespuestas=0;
			cantRespLuminosas=0;
			strcpy(codigoAlumnoActual,respuesta.codigoAlumno);
			totalRespuestas+=respuesta.cantidadRespuestasLuz+respuesta.cantidadRespuestasOscuridad;
			cantRespLuminosas+=respuesta.cantidadRespuestasLuz;
		}
		leiUnaRespuesta=cargarDatosRespuesta(fResp,&respuesta);
	}
	if (totalRespuestas!=0) {
		porcentajeLuminoso=cantRespLuminosas*100/totalRespuestas;	
	} else {
		porcentajeLuminoso=0;	
	}
	if (porcentajeLuminoso>=porcentajeMinimo) {
		eliminarAlumno(codigoAlumnoActual);
		cantidadExpulsados++;
	}
	printf("La cantidad de alumnos expulsados es: %d\n",cantidadExpulsados);
	return cantidadExpulsados;

	fclose(fResp);
}


