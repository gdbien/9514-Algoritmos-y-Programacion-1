#include <stdio.h>

const float CIEN_PORCIENTO=100;	//Para calcular el porcentaje restante(maligno)

/*
-----------------------------------------------------------------------------------------------------------------------------
	ALUMNO: SCHISCHLO, FRANCO DANIEL,	TP1,	FECHA DE ENTREGA 5/4                                                        
-----------------------------------------------------------------------------------------------------------------------------
PRECONDICIONES:																												
 1)El usuario va a ingresar numeros ENTEROS POSITIVOS, ya que no tiene sentido lógico ingresar una acción negativa,	         
 y tampoco podria definir que es hacer una acción y media (1.5), por ejemplo.

 2)EL usuario tampoco ingresará caracteres tales como; símbolos, letras,etc (validación).
-----------------------------------------------------------------------------------------------------------------------------
 ṔOSTCONDICIONES:
 1)Ser analizado, con su lado correspondiente asignado.
-----------------------------------------------------------------------------------------------------------------------------
 CASOS: I(Input):en orden O(Output)
 1)I:0	O:Neutral	   	2)I:60	O:Neutral		3)I:60	O:Lado luminoso		4)I:30	O:Lado oscuro
   I:0					  I:40                    I:39                        I:100		
-----------------------------------------------------------------------------------------------------------------------------
 COMENTARIO GENERAL:
 Además de hacer lo que se pedía(asignar el bando), me pareció copada la idea de agregarle los porcentajes correspondientes,
 para tener una noción de cuánto eran a simple vista(Lo hable con Fer y me dijo que no habia problema).
 ----------------------------------------------------------------------------------------------------------------------------
*/

int main() {
	float accionesTotales;  // Las definí como float a todas, sólo para calcular el porcentaje con 2 decimales y no me tire warning, 
	float accionesMalignas; // por estar manipulando enteros y reales. Sino, lo mas coherente sería usar un int, unsigned int, si quiero muuuchas acciones.
	float accionesBondadosas;
	float calculoPorcentaje; 

	printf("Prepárese para ser analizado y ver a que lado pertenece.\n\n");
	printf("Ingrese la cantidad de acciones bondadosas realizadas.\n");
	scanf("%f",&accionesBondadosas);
	printf("Ingrese la cantidad de acciones malignas realizadas.\n");
	scanf("%f",&accionesMalignas);

	accionesTotales = accionesBondadosas+accionesMalignas;

	if (accionesTotales>0) {
		calculoPorcentaje = (accionesBondadosas*100)/accionesTotales; //calculoPorcentaje siempre va a ser mi porcentaje bondadoso, que luego opero con CIEN_PORCIENTO para saber el restante(maligno)			 
		if (calculoPorcentaje>60) {
			printf("Su lado es: Lado luminoso, del total de acciones; %.2f%% son bondadosas y %.2f%% son malignas.\n",calculoPorcentaje,CIEN_PORCIENTO-calculoPorcentaje); 
		} else {													 //.2 para que me imprima con 2 decimales(con porcentajes MUY pequeños me va a mostrar 0%).																							        
			if (calculoPorcentaje<40) {
				printf("Su lado es: Lado oscuro, del total de acciones; %.2f%% son bondadosas y %.2f%% son malignas.\n",calculoPorcentaje,CIEN_PORCIENTO-calculoPorcentaje);	
			} else {
				if ((calculoPorcentaje>=40)&&(calculoPorcentaje<=60)) {
					printf("Su lado es: Neutral, del total de acciones; %.2f%% son bondadosas y %.2f%% son malignas.\n",calculoPorcentaje,CIEN_PORCIENTO-calculoPorcentaje);
				}
			}
		}
	} else {
		printf("Su lado es: Neutral, ya que usted no realizó ninguna acción.\n");
	}
	return 0;
}