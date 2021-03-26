#include <stdio.h>
#include "sithvsjedi.h"

const int MAX=20;
const char JEDI='J';
const char SITH='S';
const char PISO_CORROMPIDO='c';
const char PISO_PURIFICADO=' ';
const char EMPATE='E';
const char FUNCION_AVANZAR='A';
const char FUNCION_TRASLADAR='T';

/*
-----------------------------------------------------------------------------------------------------------------------------
	ALUMNO: SCHISCHLO, FRANCO DANIEL,	TP2,	FECHA DE ENTREGA 3/5                                                        
-----------------------------------------------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------------------------------------------
 COMENTARIO GENERAL:
 
 ----------------------------------------------------------------------------------------------------------------------------
*/

bool validarCoordenadas(int filDesde, int colDesde, int filHasta, int colHasta) {
	if ((filDesde>=0) && (filDesde<MAX)) {               
		if ((colDesde>=0) && (colDesde<MAX)) { 			 
			if ((filHasta>=0) && (filHasta<MAX)) {		
				if ((colHasta>=0) && (colHasta<MAX)) { 
					if ((filDesde!=filHasta) || (colDesde!=colHasta)) {	//En el caso del trasladar deberia ser un &,
						return true;									//ya que sino seria estar avanzando, pero se								
					}													//soluciona evaluando la diferencia de coorde
				} 														//nadas.
			} 
		} 
	}
	return false; 
}

bool validarDistancia(int filDesde, int colDesde, int filHasta, int colHasta, char queFuncionEs) {
	int difFilHastaDesde=filHasta-filDesde;
	int difColHastaDesde=colHasta-colDesde;	

	if (queFuncionEs==FUNCION_AVANZAR) {
		if ((difFilHastaDesde==0) || (difFilHastaDesde==1) || (difFilHastaDesde==-1)) {     
			if ((difColHastaDesde==0) || (difColHastaDesde==1) || (difColHastaDesde==-1)) { 
				return true;				
			} 
		}
		return false;
	} else {
		if ((difFilHastaDesde!=0) || (difFilHastaDesde!=1) || (difFilHastaDesde!=-1)) {     
			if ((difColHastaDesde!=0) || (difColHastaDesde!=1) || (difColHastaDesde!=-1)) { 
				return true;		
			} 
		} 
		return false;
	}
}

void corromperYPurificar(char campo[MAX][MAX], char faccion, int filHasta, int colHasta) {
	int i=filHasta-1;
	int j=colHasta-1; //Me voy una fila arriba y una columna a izquierda respecto de mi coordenada de llegada

	for (; i<(filHasta)+2; i++) {        
		for (; j<(colHasta)+2; j++) {
			if ((i>=0 && i<MAX) && (j>=0 && j<MAX)) {
				if (faccion==JEDI) {
					if (campo[i][j]!=JEDI) {
						campo[i][j]=PISO_PURIFICADO;																								
					}
				} else {											
					if (campo[i][j]!=SITH) {
						campo[i][j]=PISO_CORROMPIDO;																											
					}					
				}
			}
		}
	}
}

void inicializarCampoBatalla(char campo[MAX][MAX]) {
	int i,j;
	
	for (i=0;i<MAX;i++) {
		for (j=0;j<MAX;j++) {
			campo[i][j]=PISO_PURIFICADO;
		}
	}
	for (i=0;i<2;i++) {
		for (j=0;j<MAX;j++) {
			campo[i][j]=JEDI;
		}
	}
	for (i=MAX-2;i<MAX;i++) {
		for (j=0;j<MAX;j++) {
			campo[i][j]=SITH;
		}
	}
}

bool avanzar(char campo[MAX][MAX], char faccion, int filDesde, int colDesde, int filHasta, int colHasta) {       
	char queFuncionEs=FUNCION_AVANZAR;

	filDesde--;
	colDesde--;
	filHasta--;
	colHasta--;
					
	if (validarCoordenadas(filDesde,colDesde,filHasta,colHasta)==true) {
		if (validarDistancia(filDesde,colDesde,filHasta,colHasta,queFuncionEs)==true) { 
			if (faccion==JEDI || faccion==SITH) {
				if (faccion==campo[filDesde][colDesde]) {
					if (faccion==JEDI) {           //Avanzo                        
						if (campo[filHasta][colHasta]==JEDI) {                
							return false;
						} else {
							campo[filHasta][colHasta]=JEDI;				
							campo[filDesde][colDesde]=PISO_PURIFICADO;								
						}
					} else { 
						if (campo[filHasta][colHasta]==SITH) {
							return false;
						} else {
							campo[filHasta][colHasta]=SITH;
							campo[filDesde][colDesde]=PISO_CORROMPIDO;																		
						}
					}
					corromperYPurificar(campo,faccion,filHasta,colHasta);
					return true;
				} 
			} 
		} 							
	}
	return false;
}

bool trasladar(char campo[MAX][MAX], char faccion, int filDesde, int colDesde, int filHasta, int colHasta) {                              
	char queFuncionEs=FUNCION_TRASLADAR;

	filDesde--;
	colDesde--;
	filHasta--;
	colHasta--;

	if (validarCoordenadas(filDesde,colDesde,filHasta,colHasta)==true) {
		if (validarDistancia(filDesde,colDesde,filHasta,colHasta,queFuncionEs)==true) {
			if (faccion==JEDI || faccion==SITH) {
				if (faccion==campo[filDesde][colDesde]) { 
					if ((campo[filHasta][colHasta]==PISO_PURIFICADO) || (campo[filHasta][colHasta]==PISO_CORROMPIDO)) {
						if (faccion==JEDI) {
							campo[filHasta][colHasta]=JEDI;
							campo[filDesde][colDesde]=PISO_PURIFICADO;
							return true;
						} else { 
							campo[filHasta][colHasta]=SITH;
							campo[filDesde][colDesde]=PISO_CORROMPIDO;
							return true;
						}																
					} 																				
				} 
			} 
		} 	
	}
	return false; 
}

char faccionVictoriosa(char campo[MAX][MAX]) {
	int i,j;
	int contadorJedi=0,contadorSith=0;
	int calculoPorcentajeJedi;
	
	for (i=0;i<MAX;i++) {
		for (j=0;j<MAX;j++) {
			if ((campo[i][j]==JEDI) || (campo[i][j]==PISO_PURIFICADO)) {
				contadorJedi++;
			} else {  
				contadorSith++;
			}
		}
	}

	calculoPorcentajeJedi=(contadorJedi*100)/(MAX*MAX); //"100"(cien porciento)
												  	  //MAX*MAX -> total unidades en este caso 20*20 =400
	if (calculoPorcentajeJedi>=75) {
		return JEDI;
	} else {
		if (calculoPorcentajeJedi<=25) {
			return SITH;
		} else {
			return EMPATE;
		}
	}
}

