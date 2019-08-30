/*CODIGO FUENTE DE KILLER SUDOKU
creador: Nicolas Ortiz Escobar
rut: 20.186.094-6
fecha de incio: 1/07/2019
fecha de termino: 14/07/2019*/

//se importan las librerias necesarias
#include <stdio.h>
#include <stdlib.h>

//VARIABLES GLOBALES
int sudoku[9][9];      //martriz con el sudoku y que el usuario interactua     
char adokku[9][9];     //matriz que mostrara por pontalla las jaulas con un simbolo
//int **jaulas;          // matriz que contendra las jaulas(leidas por texto)
int cantidadJaulas;    //numero que contiene la cantidad de jaulas
//int casillas[81][2];   //contiene las casillas del adokku que tienen una jaula

/*Estructura que me almacenara las jaulas para luego mostrarlas al usuario*/
typedef struct jaulas{
	//se define la cantidad de casillas que tiene la jaula
	int cantidad;
	//se define cuanto debe sumar la jaula
	int valor;
	//el simbolo que tendrá
	char simbolo;
	//se define una matriz aue almacenara las casillas de la jaula en una posicion (i,j)
	int **casillas;
	
	
}jaulas;

jaulas *lista_jaulas;

/*funcion que convierte un numero en un simbolo o letra
entrada: numero entero
salida: un caracter*/

char getSymbol(int n){
	char sym;
	//se define la lista con caractes y letras
	char caracteres[40];
	caracteres[0]='a' ;caracteres[1]='k' ;caracteres[2]='u' ;caracteres[3]='E';
	caracteres[4]='b' ;caracteres[5]='l' ;caracteres[6]='v' ;caracteres[7]='F';
	caracteres[8]='c' ;caracteres[9]='m' ;caracteres[10]='w';caracteres[11]='G';
	caracteres[12]='d';caracteres[13]='n';caracteres[14]='x';caracteres[15]='H';
	caracteres[16]='e';caracteres[17]='o';caracteres[18]='y';caracteres[19]='I';
	caracteres[20]='f';caracteres[21]='p';caracteres[22]='z';caracteres[23]='J';
	caracteres[24]='g';caracteres[25]='q';caracteres[26]='A';caracteres[27]='K';
	caracteres[28]='h';caracteres[29]='r';caracteres[30]='B';caracteres[31]='L';
	caracteres[32]='i';caracteres[33]='s';caracteres[34]='C';caracteres[35]='M';
	caracteres[36]='j';caracteres[37]='t';caracteres[38]='D';caracteres[39]='N';
	
	sym=caracteres[n];
	//se retorna el caracter según  
	return(sym);	
	
}


/*funcion de lectura del archivo que contiene las jaulas
entrada: el nombre del archivo ingresado por el usuario
salida: no posee dado que es de tipo void*/

int lectura(char *nombreArchivo){
	int i,j,k;               //iteradores
	 
	int posI,posJ;         //posicion de las casiilas
	
	
	FILE* archivo;
	char aux;              //una variable auxiliar

	archivo=fopen(nombreArchivo,"r");   //lectura byte por byte

	if(archivo==NULL){
		printf("Lectura erronea\n");
		return 1;
	}
	else{
		//la primera linea del archivo siempre es la cantidad e jaulas
		fscanf(archivo,"%d",&cantidadJaulas);
		
		lista_jaulas=(jaulas*)malloc(sizeof(jaulas)*(cantidadJaulas));
		
		//se hace un ciclo para que la lectura de los datos sea hasta que llegue al final del archivo
		//para que cada caracter ingrese a la matriz
		for(i=0;i<cantidadJaulas;i++){	          //eso es para cada fila		                     		
			if(aux != EOF){
				
				//se lee la cantidad de casillas y lo que debe sumar cada casilla
				fscanf(archivo,"%d,%d",&lista_jaulas[i].cantidad,&lista_jaulas[i].valor);
				
				//se hace el arreglo dinamico de la variable .casillas
				lista_jaulas[i].casillas=(int**)malloc(sizeof(int*)*(lista_jaulas[i].cantidad));
				
				//se le asigna el simbolo
				lista_jaulas[i].simbolo=getSymbol(i);
					
				for(j=0;j<lista_jaulas[i].cantidad;j++){	
					lista_jaulas[i].casillas[j]=(int*)malloc(sizeof(int)*(2));
					
					fscanf(archivo,"%d,%d",&posI,&posJ);
					//se almacenan las casillas de la primera jaula 
					lista_jaulas[i].casillas[j][0]=posI;
					lista_jaulas[i].casillas[j][1]=posJ;
					
					//se coloca el simbolo en la matriz del adokku
					adokku[posI][posJ]=lista_jaulas[i].simbolo;
					
				}
			} 
		}
	}

	fclose(archivo);
	return 0;
}


/*funcion de tipo void que rellena con 0's la matriz que contiene el sudoku
se hacce esto para poder imprimir bien el tablero mas adelante
como la matriz es variable global, no se necesita ingresarla como argumento*/

void llenarMatriz(){
	int i,j;   //iteradores
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			sudoku[i][j]=0;
		}
	}
}

/*fucion que verifica que las filas del sudoku sean correctas
es decir que todos los numeros de las filas sean distintos 
entrada: matriz de 9X9 que contiene el sudoku
salida: Booleano*/
int verificarFila(int matriz[9][9]){
	int i,j,k;   //iteradores
	
	//se hace un ciclo para recorrer cada fila 
	for(i=0;i<8;i++){
		//se hace un ciclo para recorrer cada elemento de la fila
		for(j=0;j<8;j++){
			//aca la idea es comparar el elemento j con los que vienen, osea un elemento k
			//cosa de que el primero (j) se compare con el 2do 3ro y asi sucesivamente, luego el 2do con el 3ro 4to etc
			for(k=j+1;k<9;k++){
				//si encuentra un elemento igual
				if(matriz[i][j]=matriz[i][k]){
					return(0);
				}
			} 
		}
	}
	//si no encuentra elementos repetidos en la fila
	return (1);	
}


/*fucion que verifica que las columnas del sudoku sean correctas
es decir que todos los numeros de las columnas sean distintos 
entrada: matriz de 9X9 que contiene el sudoku
salida: Booleano*/
int verificarColumna(int matriz[9][9]){
	int i,j,k;   //iteradores
	
	//se hace un ciclo para recorrer cada columna 
	for(j=0;j<8;j++){
		//se hace un ciclo para recorrer cada elemento de la columna
		for(i=0;i<8;i++){
			//aca la idea es comparar el elemento i con los que vienen, osea un elemento k
			//cosa de que el primero (i) se compare con el 2do 3ro y asi sucesivamente, luego el 2do con el 3ro 4to etc
			for(k=i+1;k<9;k++){
				//si encuentra un elemento igual
				if(matriz[i][j]=matriz[k][j]){
					return(0);
				}
			} 
		}
	}
	//si no encuentra elementos repetidos en la columna
	return (1);	
}


/*Funcion que verifica cada submatriz del sudoku, esto quere decir revisa las 9 casillas de 3x3
entrada: la matriz de 9x9
salida: valor booleano */

int verificarSubMatriz(int matriz[9][9]){
	int i,j;
	
	/*se entendera como submatriz 1,2 etc al siguiente orden
	1 2 3
	4 5 6
	7 8 9     mismo orden se entendera para los elementos de la submatriz
	para el buen entendimiento de quien lea este codigo*/
	
	//##############A LO BRUTO LA COMPARACION es decir uno a uno#####################//  
	
	//primera submatriz
	if(//se compara el primer elemento con todos los demas elementos 
	   matriz[0][0]==matriz[0][1] || matriz[0][0]==matriz[0][2] ||
	   matriz[0][0]==matriz[1][0] || matriz[0][0]==matriz[1][1] || matriz[0][0]==matriz[1][2] ||
	   matriz[0][0]==matriz[2][0] || matriz[0][0]==matriz[2][1] || matriz[0][0]==matriz[2][2] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[0][1]==matriz[0][2] ||
	   matriz[0][1]==matriz[1][0] || matriz[0][1]==matriz[1][1] || matriz[0][1]==matriz[1][2] ||
	   matriz[0][1]==matriz[2][0] || matriz[0][1]==matriz[2][1] || matriz[0][1]==matriz[2][2] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[0][2]==matriz[1][0] || matriz[0][2]==matriz[1][1] || matriz[0][2]==matriz[1][2] ||
	   matriz[0][2]==matriz[2][0] || matriz[0][2]==matriz[2][1] || matriz[0][2]==matriz[2][2] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[1][0]==matriz[1][1] || matriz[1][0]==matriz[1][2] ||
	   matriz[1][0]==matriz[2][0] || matriz[1][0]==matriz[2][1] || matriz[1][0]==matriz[2][2] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[1][1]==matriz[1][2] ||
	   matriz[1][1]==matriz[2][0] || matriz[1][1]==matriz[2][1] || matriz[1][1]==matriz[2][2] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[1][2]==matriz[2][0] || matriz[1][2]==matriz[2][1] || matriz[1][2]==matriz[2][2] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[2][0]==matriz[2][1] || matriz[2][0]==matriz[2][2] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[2][1]==matriz[2][2]){
	   
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}
	
	//segunda submatriz
	if(//se compara el primer elemento con todos los demas elementos
	   matriz[0][3]==matriz[0][4] || matriz[0][3]==matriz[0][5] ||
	   matriz[0][3]==matriz[1][3] || matriz[0][3]==matriz[1][4] || matriz[0][3]==matriz[1][5] ||
	   matriz[0][3]==matriz[2][3] || matriz[0][3]==matriz[2][4] || matriz[0][3]==matriz[2][5] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[0][4]==matriz[0][5] ||
	   matriz[0][4]==matriz[1][3] || matriz[0][4]==matriz[1][4] || matriz[0][4]==matriz[1][5] ||
	   matriz[0][4]==matriz[2][3] || matriz[0][4]==matriz[2][4] || matriz[0][4]==matriz[2][5] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[0][5]==matriz[1][3] || matriz[0][5]==matriz[1][4] || matriz[0][5]==matriz[1][5] ||
	   matriz[0][5]==matriz[2][3] || matriz[0][5]==matriz[2][4] || matriz[0][5]==matriz[2][5] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[1][3]==matriz[1][4] || matriz[1][3]==matriz[1][5] ||
	   matriz[1][3]==matriz[2][3] || matriz[1][3]==matriz[2][4] || matriz[1][3]==matriz[2][5] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[1][4]==matriz[1][5] ||
	   matriz[1][4]==matriz[2][3] || matriz[1][4]==matriz[2][4] || matriz[1][4]==matriz[2][5] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[1][5]==matriz[2][3] || matriz[1][5]==matriz[2][4] || matriz[1][5]==matriz[2][5] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[2][3]==matriz[2][4] || matriz[2][3]==matriz[2][5] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[2][4]==matriz[2][5]){
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}
	
	//tercera submatriz
	if(//se compara el primer elemento con todos los demas elementos
	   matriz[0][6]==matriz[0][7] || matriz[0][6]==matriz[0][8] ||
	   matriz[0][6]==matriz[1][6] || matriz[0][6]==matriz[1][7] || matriz[0][6]==matriz[1][8] ||
	   matriz[0][6]==matriz[2][6] || matriz[0][6]==matriz[2][7] || matriz[0][6]==matriz[2][8] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[0][7]==matriz[0][8] ||
	   matriz[0][7]==matriz[1][6] || matriz[0][7]==matriz[1][7] || matriz[0][7]==matriz[1][8] ||
	   matriz[0][7]==matriz[2][6] || matriz[0][7]==matriz[2][7] || matriz[0][7]==matriz[2][8] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[0][8]==matriz[1][6] || matriz[0][8]==matriz[1][7] || matriz[0][8]==matriz[1][8] ||
	   matriz[0][8]==matriz[2][6] || matriz[0][8]==matriz[2][7] || matriz[0][8]==matriz[2][8] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[1][6]==matriz[1][7] || matriz[1][6]==matriz[1][8] ||
	   matriz[1][6]==matriz[2][6] || matriz[1][6]==matriz[2][7] || matriz[1][6]==matriz[2][8] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[1][7]==matriz[1][8] ||
	   matriz[1][7]==matriz[2][6] || matriz[1][7]==matriz[2][7] || matriz[1][7]==matriz[2][8] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[1][8]==matriz[2][6] || matriz[1][8]==matriz[2][7] || matriz[1][8]==matriz[2][8] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[2][6]==matriz[2][7] || matriz[2][6]==matriz[2][8] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[2][7]==matriz[2][8]){
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}

	//cuarta submatriz
	if(//se compara el primer elemento con todos los demas elementos 
	   matriz[3][0]==matriz[3][1] || matriz[3][0]==matriz[3][2] ||
	   matriz[3][0]==matriz[4][0] || matriz[3][0]==matriz[4][1] || matriz[3][0]==matriz[4][2] ||
	   matriz[3][0]==matriz[5][0] || matriz[3][0]==matriz[5][1] || matriz[3][0]==matriz[5][2] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[3][1]==matriz[3][2] ||
	   matriz[3][1]==matriz[4][0] || matriz[3][1]==matriz[4][1] || matriz[3][1]==matriz[4][2] ||
	   matriz[3][1]==matriz[5][0] || matriz[3][1]==matriz[5][1] || matriz[3][1]==matriz[5][2] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[3][2]==matriz[4][0] || matriz[3][2]==matriz[4][1] || matriz[3][2]==matriz[4][2] ||
	   matriz[3][2]==matriz[5][0] || matriz[3][2]==matriz[5][1] || matriz[3][2]==matriz[5][2] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[4][0]==matriz[4][1] || matriz[4][0]==matriz[4][2] ||
	   matriz[4][0]==matriz[5][0] || matriz[4][0]==matriz[5][1] || matriz[4][0]==matriz[5][2] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[4][1]==matriz[4][2] ||
	   matriz[4][1]==matriz[5][0] || matriz[4][1]==matriz[5][1] || matriz[4][1]==matriz[5][2] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[4][2]==matriz[5][0] || matriz[4][2]==matriz[5][1] || matriz[4][2]==matriz[5][2] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[5][0]==matriz[5][1] || matriz[5][0]==matriz[5][2] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[5][1]==matriz[5][2]){
	   
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}

	//quinta submatriz
	if(//se compara el primer elemento con todos los demas elementos
	   matriz[3][3]==matriz[3][4] || matriz[3][3]==matriz[3][5] ||
	   matriz[3][3]==matriz[4][3] || matriz[3][3]==matriz[4][4] || matriz[3][3]==matriz[4][5] ||
	   matriz[3][3]==matriz[5][3] || matriz[3][3]==matriz[5][4] || matriz[3][3]==matriz[5][5] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[3][4]==matriz[3][5] ||
	   matriz[3][4]==matriz[4][3] || matriz[3][4]==matriz[4][4] || matriz[3][4]==matriz[4][5] ||
	   matriz[3][4]==matriz[5][3] || matriz[3][4]==matriz[5][4] || matriz[3][4]==matriz[5][5] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[3][5]==matriz[4][3] || matriz[3][5]==matriz[4][4] || matriz[3][5]==matriz[4][5] ||
	   matriz[3][5]==matriz[5][3] || matriz[3][5]==matriz[5][4] || matriz[3][5]==matriz[5][5] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[4][3]==matriz[4][4] || matriz[4][3]==matriz[4][5] ||
	   matriz[4][3]==matriz[5][3] || matriz[4][3]==matriz[5][4] || matriz[4][3]==matriz[5][5] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[4][4]==matriz[4][5] ||
	   matriz[4][4]==matriz[5][3] || matriz[4][4]==matriz[5][4] || matriz[4][4]==matriz[5][5] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[4][5]==matriz[5][3] || matriz[4][5]==matriz[5][4] || matriz[4][5]==matriz[5][5] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[5][3]==matriz[5][4] || matriz[5][3]==matriz[5][5] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[5][4]==matriz[5][5]){
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}

	//sexta submatriz
	if(//se compara el primer elemento con todos los demas elementos
	   matriz[3][6]==matriz[3][7] || matriz[3][6]==matriz[3][8] ||
	   matriz[3][6]==matriz[4][6] || matriz[3][6]==matriz[4][7] || matriz[3][6]==matriz[4][8] ||
	   matriz[3][6]==matriz[5][6] || matriz[3][6]==matriz[5][7] || matriz[3][6]==matriz[5][8] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[3][7]==matriz[3][8] ||
	   matriz[3][7]==matriz[4][6] || matriz[3][7]==matriz[4][7] || matriz[3][7]==matriz[4][8] ||
	   matriz[3][7]==matriz[5][6] || matriz[3][7]==matriz[5][7] || matriz[3][7]==matriz[5][8] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[3][8]==matriz[4][6] || matriz[3][8]==matriz[4][7] || matriz[3][8]==matriz[4][8] ||
	   matriz[3][8]==matriz[5][6] || matriz[3][8]==matriz[5][7] || matriz[3][8]==matriz[5][8] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[4][6]==matriz[4][7] || matriz[4][6]==matriz[4][8] ||
	   matriz[4][6]==matriz[5][6] || matriz[4][6]==matriz[5][7] || matriz[4][6]==matriz[5][8] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[4][7]==matriz[4][8] ||
	   matriz[4][7]==matriz[5][6] || matriz[4][7]==matriz[5][7] || matriz[4][7]==matriz[5][8] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[4][8]==matriz[5][6] || matriz[4][8]==matriz[5][7] || matriz[4][8]==matriz[5][8] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[5][6]==matriz[5][7] || matriz[5][6]==matriz[5][8] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[5][7]==matriz[5][8]){
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}

	//septima submatriz
	if(//se compara el primer elemento con todos los demas elementos 
	   matriz[6][0]==matriz[6][1] || matriz[6][0]==matriz[6][2] ||
	   matriz[6][0]==matriz[7][0] || matriz[6][0]==matriz[7][1] || matriz[6][0]==matriz[7][2] ||
	   matriz[6][0]==matriz[8][0] || matriz[6][0]==matriz[8][1] || matriz[6][0]==matriz[8][2] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[6][1]==matriz[6][2] ||
	   matriz[6][1]==matriz[7][0] || matriz[6][1]==matriz[7][1] || matriz[6][1]==matriz[7][2] ||
	   matriz[6][1]==matriz[8][0] || matriz[6][1]==matriz[8][1] || matriz[6][1]==matriz[8][2] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[6][2]==matriz[7][0] || matriz[6][2]==matriz[7][1] || matriz[6][2]==matriz[7][2] ||
	   matriz[6][2]==matriz[8][0] || matriz[6][2]==matriz[8][1] || matriz[6][2]==matriz[8][2] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[7][0]==matriz[7][1] || matriz[7][0]==matriz[7][2] ||
	   matriz[7][0]==matriz[8][0] || matriz[7][0]==matriz[8][1] || matriz[7][0]==matriz[8][2] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[7][1]==matriz[7][2] ||
	   matriz[7][1]==matriz[8][0] || matriz[7][1]==matriz[8][1] || matriz[7][1]==matriz[8][2] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[7][2]==matriz[8][0] || matriz[7][2]==matriz[8][1] || matriz[7][2]==matriz[8][2] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[8][0]==matriz[8][1] || matriz[8][0]==matriz[8][2] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[8][1]==matriz[8][2]){
	   
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}
	
	//octava submatriz
	if(//se compara el primer elemento con todos los demas elementos
	   matriz[6][3]==matriz[6][4] || matriz[6][3]==matriz[6][5] ||
	   matriz[6][3]==matriz[7][3] || matriz[6][3]==matriz[7][4] || matriz[6][3]==matriz[7][5] ||
	   matriz[6][3]==matriz[8][3] || matriz[6][3]==matriz[8][4] || matriz[6][3]==matriz[8][5] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[6][4]==matriz[6][5] ||
	   matriz[6][4]==matriz[7][3] || matriz[6][4]==matriz[7][4] || matriz[6][4]==matriz[7][5] ||
	   matriz[6][4]==matriz[8][3] || matriz[6][4]==matriz[8][4] || matriz[6][4]==matriz[8][5] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[6][5]==matriz[7][3] || matriz[6][5]==matriz[7][4] || matriz[6][5]==matriz[7][5] ||
	   matriz[6][5]==matriz[8][3] || matriz[6][5]==matriz[8][4] || matriz[6][5]==matriz[8][5] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[7][3]==matriz[7][4] || matriz[7][3]==matriz[7][5] ||
	   matriz[7][3]==matriz[8][3] || matriz[7][3]==matriz[8][4] || matriz[7][3]==matriz[8][5] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[7][4]==matriz[7][5] ||
	   matriz[7][4]==matriz[8][3] || matriz[7][4]==matriz[8][4] || matriz[7][4]==matriz[8][5] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[7][5]==matriz[8][3] || matriz[7][5]==matriz[8][4] || matriz[7][5]==matriz[8][5] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[8][3]==matriz[8][4] || matriz[8][3]==matriz[8][5] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[8][4]==matriz[8][5]){
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}

	//novena submatriz
	if(//se compara el primer elemento con todos los demas elementos
	   matriz[6][6]==matriz[6][7] || matriz[6][6]==matriz[6][8] ||
	   matriz[6][6]==matriz[7][6] || matriz[6][6]==matriz[7][7] || matriz[6][6]==matriz[7][8] ||
	   matriz[6][6]==matriz[8][6] || matriz[6][6]==matriz[8][7] || matriz[6][6]==matriz[8][8] ||
	   //se compara el segundo elemento con todos los demas elementos
	   matriz[6][7]==matriz[6][8] ||
	   matriz[6][7]==matriz[7][6] || matriz[6][7]==matriz[7][7] || matriz[6][7]==matriz[7][8] ||
	   matriz[6][7]==matriz[8][6] || matriz[6][7]==matriz[8][7] || matriz[6][7]==matriz[8][8] ||
	   //se compara el tercer elemento con todos los demas elementos
	   matriz[6][8]==matriz[7][6] || matriz[6][8]==matriz[7][7] || matriz[6][8]==matriz[7][8] ||
	   matriz[6][8]==matriz[8][6] || matriz[6][8]==matriz[8][7] || matriz[6][8]==matriz[8][8] ||
	   //se compara el cuarto elemento con todos los demas elementos
	   matriz[7][6]==matriz[7][7] || matriz[7][6]==matriz[7][8] ||
	   matriz[7][6]==matriz[8][6] || matriz[7][6]==matriz[8][7] || matriz[7][6]==matriz[8][8] ||
	   //se compara el quinto elemento con todos los demas elementos
	   matriz[7][7]==matriz[7][8] ||
	   matriz[7][7]==matriz[8][6] || matriz[7][7]==matriz[8][7] || matriz[7][7]==matriz[8][8] ||
	   //se compara el sexto elemento con todos los demas elementos
	   matriz[7][8]==matriz[8][6] || matriz[7][8]==matriz[8][7] || matriz[7][8]==matriz[8][8] ||
	   //se compara el septimo elemento con todos los demas elementos
	   matriz[8][6]==matriz[8][7] || matriz[8][6]==matriz[8][8] ||
	   //se compara el octavo elemento con todos los demas elementos
	   matriz[8][7]==matriz[8][8]){
	   
	   	//si encuentra uno igual dentro de la submatriz
	   	return 0;	
	}
	
	//en caso de no encontrar ningun igual en ninguna submatriz 
	return 1;	

}


/*funcion que verifica si cumple con todas las jaulas
entrada: una matriz
salida: un valor boleano*/

int verificarJaula(int matriz[9][9], jaulas *lista){
	int i,j;    //iteradores
	int suma=0;   //variable que me almacena la suma de las casillas 
	int posI,posJ;  //variables que me almacenan una posicion de la matriz
	// se deben verificar cada una de las jaulas
	for(i=0;i<cantidadJaulas;i++){
		//se recorre la cantidad de casillas que  contiene el arreglo de la jaula
		for(j=0;j<lista[i].cantidad;j++){
			posI=lista[i].casillas[j][0];
			posJ=lista[i].casillas[j][1];
			suma=suma+matriz[posI][posJ];
		}
		if(suma!=lista[i].valor){
			return 0;
		}
		
	}
	
	return 1;
	
}

/*funcion que borra un elemento de la matriz(se dice borrar pero en realidad es reemplazar)
entrada:una matriz de 9X9
salida:valor booleano*/

int borrarElemento(int matriz[9][9]){
	//variables que me almacenaran lint elementosa posicion que quiero borrar
	int posI,posJ;
	//se le pregunta al usuario que posicion quiere borrar
	printf("Ingrese la posicion en la fila y columna respectivamente que desea borrar, sepadados por un espacio\n> ");
	scanf("%d %d",&posI,&posJ);
	
	//se comprueba si el usuario ingresa una posicion correcta
	if(posI<1 || posI<9 || posJ<1 || posJ>9){
		printf("Posicion ingresada no es valida\n");
		return 0;
	}
	//se verifica si hay un elemento en la posicion que ingresa
	if(matriz[posI][posJ]==0){
		//el 0 representa que no hay elementos en la matriz
		printf("Ahi no hay elemento\n");
		return 0;
	}
	//en caso de que la posicion a borrar sea correcta
	else{
		//se "borra" el elemento
		matriz[posI-1][posJ-1]=0;
	}

	return 0;
}

/*funcion que ingresa el elemento a la matriz
entrada: una matriz
salida: valor entero*/
int ingresarElemento(int matriz[9][9]){
	//se almacena la posicion que quiere ingresar
	int posI,posJ;
	//el elemento que quiere ingresar
	int elemento;
	
	//se le pregunta al usuario que numero quiere ingresar
	printf("Que numero desea ingresar?: ");
	scanf("%d",&elemento);
	
	//se comprueba que elemento ingresado sea valido
	if(elemento<1 || elemento>9){
		printf("\nEl elemento ingresado no es valido\n");
		return 0;
	}
	
	//se le pregunta al usuario en que posicion va a ingresar el elemento 
	printf("Ingrese la posicion en la fila y columna respectivamente que desea ingresar el elemento, sepadados por un espacio\n> ");
	scanf("%d %d",&posI,&posJ);
	
	//se comprueba si el usuario ingresa una posicion correcta
	if(posI<1 || posI>9 || posJ<1 || posJ>9){
		printf("Posicion ingresada no es valida\n");
		return 0;
	}
	else{
		matriz[posI-1][posJ-1]=elemento;
	}
	return 0;
}

/*funcion que me imprime la matriz con las jaulas
entrada: la matriz con las jaulas
salida: no posee dado que es de tipo void*/
void imprimirAdokku(char matriz[9][9]){
	int i,j;   //iteradores
	for(i=0;i<9;i++){
		//para separar por submatrices cada 3 filas
		if(i==3 || i==6){
			printf("\n");
		}
		for(j=0;j<9;j++){
			//para separar por submatrices por cada 3 columnas
			if(j==3 || j==6){
				printf(" ");
			}
			printf("%c",matriz[i][j]);
		}
		//separacion
		printf("\n");
	}	
}


/*funcion que me imprime los numeros del sudoku
entrada:matriz de 9X9
salida: no posee dado que es de tipo void*/

void imprimirSudoku(int matriz[9][9]){
	int i,j;   //iteradores
	for(i=0;i<9;i++){
		//para separar por submatrices cada 3 filas
		if(i==3 || i==6){
			printf("\n");
		}
		for(j=0;j<9;j++){
			//para separar por submatrices por cada 3 columnas
			if(j==3 || j==6){
				printf(" ");
			}
			if(matriz[i][j]==0){
				printf("_");
			}
			else{
				printf("%d",matriz[i][j]);
			}
		}
		//separacion
		printf("\n");
	}
}


int main(){
	//opciones 
	int opcion;
	int validacion=1;   //valida si la opcion es valida cuando cambia a 0
	int i,j;            //iteradores
	int lect=1;         //verifica si la lectura es correcta o no 
	int jugar=1;        //variable que me permite jugar
	
	int ingresa,borra;   //para el buen funcionamiento de las funciones
	
	int verFila=0,verColum=0,verJau=0,verSM=0;    //variables que verifican las filas columnas y jaulas respectivamente
	int modoJ=1, modoA=1;  //variables que me permiten hacer un ciclo para el modo jugador o modo automatico
	
	int elementos=0;   //un contador que sirve para saber cuantas casillas hay ocupadas
	
	char nombreArchivo[100];   //contiene el nombre del archivo ingresado por el usuario
	
	
	//######################################## MENU #################################################
	printf("Bienvenido al KILLER SUDOKU\n##################################################\n");
	printf("INSTRUCCIONES:\n-Primero ingrese el nombre del archivo de su killer sudoku\n-LAS POSICIONES QUE INGRESE SON SOLO DEL 1 AL 9\n");
	printf("-Las jaulas se mostraran al principio de esta ventana y luego su respectiva distribucion\n-Sin mas A JUGAR!!\n##########################################\n\n");
	
	//al finalizar si no quiere volver a jugar se rompe este ciclo
	while(jugar==1){
		
		//se hace un ciclo para la correcta lectura del archivo
		while(lect==1){
			printf("\nIngrese el nombre del archivo\n>>>>>>>>>>>> ");
			scanf("%s",nombreArchivo);
		
			lect=lectura(nombreArchivo);
	
		}
	
		//####VALIDACION PARA INGRESAR A UN MODO VALIDO DE JUEGO
		while(validacion==1){
	
			printf("\nIngrese una modalidad\n1)Modo Jugador\n2)Modo Automatico(por busqueda de espacio-soluciones)\n3)Salir\n>>>>>> ");
			scanf("%d",&opcion);
	
			if(opcion==1){
				printf("\nHas escogido el 'Modo Jugador'\n\n");
				validacion=0;
			}
			else if(opcion==2){
				printf("\nHas escogido el 'Modo Automatico (por busqueda de espacio-soluciones)'\n\n");
				validacion=0;
			}
			else if(opcion==3){
				printf("\nHasta pronto");
				return 0;
			}
			else{
				printf("\nOpcion ingresada no es valida\n");
			}
	
		}//while de validacion
	
	
		//En caso de que el usuario escoja el modo jugador
		if(opcion==1){
			printf("Se te mostraran por pantalla las jaulas de %s y su valor\n",nombreArchivo);
			for(i=0;i<cantidadJaulas;i++){
				printf("La Jaula: %c tiene valor: %d\n",lista_jaulas[i].simbolo,lista_jaulas[i].valor);
			}
			printf("\n\nSe mostraran por pantalla la distribucion de las Jaulas\n\n");
			imprimirAdokku(adokku);
			printf("\n\n");
		
			//Se hace un ciclo que sus condiciones son que que hayan menos de 81 elementos y que las filas, columnas y jaulas no esten compliendo las condiciones 
			while(elementos!=81 || verFila!=1 || verColum!=1 || verJau!=1 || verSM!=1){
				//se define un numero para verificar la opcion del usuario
				int op;
				//para formar un ciclo para que ingrese correctamente una opcion
				int verificador=1;
				
				
				//un separador visual
				printf("##############################################################################################################################\n");
				//se imprime el sudoku actualmente
				imprimirSudoku(sudoku);
				printf("\n\n");
				//se forma el ciclo hasta que el usuario ingrese un opcion valida
				while(verificador){
					//Se le pregunta al usuario que desea hacer
					printf("Elija una opcion \n");
					//Si no hay 81 elementos en la matriz
					if(elementos!=81){
						printf("1) Ingresar numero\n");
					}
					//si hay por lo menos 1 elemento en el sudoku
					if(elementos!=0){
						printf("2)Borrar numero\n");
					}
					printf("3) Rendirse\n");
					printf(">");
					scanf("%d",&op);
					
					//si elige una opcion que no es valida
					if(op<1 || op>3){
						printf("opcion ingresada no es valida\n");
					}
					else{
						verificador=0;
					}
									
				}//while verificador
				
				//si la opcion fue 1
				if(op==1){
					ingresa=ingresarElemento(sudoku);
					elementos=elementos+1;
				}
				//si la opcion fue 2
				else if(op==2){
					borra=borrarElemento(sudoku);
					elementos=elementos-1;
				}
				//si la opcion fue 3
				else if(op==3){
					printf("Ud. se Rindio :c");
					return 0;
				}
				
				if(elementos==81){
					verFila  =verificarFila(sudoku);
					verColum =verificarColumna(sudoku);
					verJau   =verificarJaula(sudoku,lista_jaulas);
					verSM    =verificarSubMatriz(sudoku);
					if(verFila!=1){
						printf("Hay un error en las Filas\n");
					}
					if(verColum!=1){
						printf("Hay un error en las Columnas\n");	
					}
					if(verJau!=1){
						printf("Hay un error en las Jaulas\n");
					}
					if(verSM!=1){
						printf("Hay un error en los cuadros de 3X3\n");
					}
				}
			
			}//while de elemento verificar fila ETC.
			//si se rompe el ciclo quiere decir que ganó
			printf("FELICITACIONES HAS COMPLETADO EL KILLER SUDOKU :)\n");
			//se le pregunta al usuario si desea volver a jugar
			printf("Deseas volver a jugar:\n1)Si\n2)No:\n>> ");
			scanf("%d",&jugar);	
			
			if(jugar==2){
				printf("Hasta pronto :)");
			}
					
		}//if opcion 1
		
		else if(opcion==2){
			//FUERZA BRUTA NOMAS SI EL PC SE REVIENTA YOLO BB!!
			//Eso implica que son 81 for anidados, la ram va a morir de seguro pero cumple con BES 
			//entonces se definen 81 variables(esto lo vi de un compañero de seccion asi que credito para él)
			int i1,i2,i3,i4,i5,i6,i7,i8,i9;
			int j1,j2,j3,j4,j5,j6,j7,j8,j9;
			int k1,k2,k3,k4,k5,k6,k7,k8,k9;
			int l1,l2,l3,l4,l5,l6,l7,l8,l9;
			int m1,m2,m3,m4,m5,m6,m7,m8,m9;
			int n1,n2,n3,n4,n5,n6,n7,n8,n9;
			int p1,p2,p3,p4,p5,p6,p7,p8,p9;
			int r1,r2,r3,r4,r5,r6,r7,r8,r9;
			int s1,s2,s3,s4,s5,s6,s7,s8,s9;
			
		while(modoA==1){
			//ahora que tenemos nuestras 81 varibles se hacen los ciclos
			for(i1=0;i1<10;i1++){
				//se reemplaza ese elemento de la matriz por la variable del ciclo y asi para los restantes
				sudoku[0][0]=i1;
				
				for(i2=0;i2<10;i2++){
					sudoku[0][1]=i2;
					for(i3=0;i3<10;i3++){
						sudoku[0][2]=i3;
						for(i4=0;i4<10;i4++){
							sudoku[0][3]=i4;
								for(i5=0;i5<10;i5++){
									sudoku[0][4]=i5;
									for(i6=0;i6<10;i6++){
										sudoku[0][5]=i6;
										for(i7=0;i7<10;i7++){
											sudoku[0][6]=i7;
											for(i8=0;i8<10;i8++){
												sudoku[0][7]=i8;
												for(i9=0;i9<10;i9++){
													sudoku[0][8]=i9;
													for(j1=0;j1<10;j1++){
														sudoku[1][0]=j1;
														for(j2=0;j2<10;j2++){
															sudoku[1][1]=j2;
															for(j3=0;j3<10;j3++){
																sudoku[1][2]=j3;
																for(j4=0;j4<10;j4++){
																	sudoku[1][3]=j4;
																	for(j5=0;j5<10;j5++){
																		sudoku[1][4]=j5;
																		for(j6=0;j6<10;j6++){
																			sudoku[1][5]=j6;
																			for(j7=0;j7<10;j7++){
																				sudoku[1][6]=j7;
																				for(j8=0;j8<10;j8++){
																					sudoku[1][7]=j8;
																					for(j9=0;j9<10;j9++){
																						sudoku[1][8]=j9;
																						for(k1=0;k1<10;k1++){
																							sudoku[2][0]=k1;
																							for(k2=0;k2<10;k2++){
																								sudoku[2][1]=k2;
																								for(k3=0;k3<10;k3++){
																									sudoku[2][2]=k3;
																									for(k4=0;k4<10;k4++){
																										sudoku[2][3]=k4;
																										for(k5=0;k5<10;k5++){
																											sudoku[2][4]=k5;
																											for(k6=0;k6<10;k6++){
																												sudoku[2][5]=k6;
																												for(k7=0;k7<10;k7++){
																													sudoku[2][6]=k7;
																													for(k8=0;k8<10;k8++){
																														sudoku[2][7]=k8;
																														for(k9=0;k9<10;k9++){
																															sudoku[2][8]=k9;
																															for(l1=0;l1<10;l1++){
																																sudoku[3][0]=l1;
																																for(l2=0;l2<10;l2++){
																																	sudoku[3][1]=l2;
																																	for(l3=0;l3<10;l3++){
																																		sudoku[3][2]=l3;
																																		for(l4=0;l4<10;l4++){
																																			sudoku[3][3]=l4;
																																			for(l5=0;l5<10;l5++){
																																				sudoku[3][4]=l5;
																																				for(l6=0;l6<10;l6++){
																																					sudoku[3][5]=l6;
																																					for(l7=0;l7<10;l7++){
																																						sudoku[3][6]=l7;
																																						for(l8=0;l8<10;l8++){
																																							sudoku[3][7]=l8;
																																							for(l9=0;l9<10;l9++){
																																								sudoku[3][8]=l9;
																																								for(m1=0;m1<10;m1++){
																																									sudoku[4][0]=m1;
																																									for(m2=0;m2<10;m2++){
																																										sudoku[4][1]=m2;
																																										for(m3=0;m3<10;m3++){
																																											sudoku[4][2]=m3;
																																											for(m4=0;m4<10;m4++){
																																												sudoku[4][3]=m4;
																																												for(m5=0;m5<10;m5++){
																																													sudoku[4][4]=m5;
																																													for(m6=0;m6<10;m6++){
																																														sudoku[4][5]=m6;
																																														for(m7=0;m7<10;m7++){
																																															sudoku[4][6]=m7;
																																															for(m8=0;m8<10;m8++){
																																																sudoku[4][7]=m8;
																																																for(m9=0;m9<10;m9++){
																																																	sudoku[4][8]=m9;
																																																	for(n1=0;n1<10;n1++){
																																																		sudoku[5][0]=n1;
																																																		for(n2=0;n2<10;n2++){
																																																			sudoku[5][1]=n2;
																																																			for(n3=0;n3<10;n3++){
																																																				sudoku[5][2]=n3;
																																																				for(n4=0;n4<10;n4++){
																																																					sudoku[5][3]=n4;
																																																					for(n5=0;n5<10;n5++){
																																																						sudoku[5][4]=n5;
																																																						for(n6=0;n6<10;n6++){
																																																							sudoku[5][5]=n6;
																																																							for(n7=0;n7<10;n7++){
																																																								sudoku[5][6]=n7;
																																																								for(n8=0;n8<10;n8++){
																																																									sudoku[5][7]=n8;
																																																									for(n9=0;n9<10;n9++){
																																																										sudoku[5][8]=n9;
																																																										for(p1=0;p1<10;p1++){
																																																											sudoku[6][0]=p1;
																																																											for(p2=0;p2<10;p2++){
																																																												sudoku[6][1]=p2;
																																																												for(p3=0;p3<10;p3++){
																																																													sudoku[6][2]=p3;
																																																													for(p4=0;p4<10;p4++){
																																																														sudoku[6][3]=p4;
																																																														for(p5=0;p5<10;p5++){
																																																															sudoku[6][4]=p5;
																																																															for(p6=0;p6<10;p6++){
																																																																sudoku[6][5]=p6;
																																																																for(p7=0;p7<10;p7++){
																																																																	sudoku[6][6]=p7;
																																																																	for(p8=0;p8<10;p8++){
																																																																		sudoku[6][7]=p8;
																																																																		for(p9=0;p9<10;p9++){
																																																																			sudoku[6][8]=p9;
																																																																			for(r1=0;r1<10;r1++){
																																																																				sudoku[7][0]=r1;							
																																																																				for(r2=0;r2<10;r2++){
																																																																					sudoku[7][1]=r2;
																																																																					for(r3=0;r3<10;r3++){
																																																																						sudoku[7][2]=r3;
																																																																						for(r4=0;r4<10;r4++){
																																																																							sudoku[7][3]=r4;
																																																																							for(r5=0;r5<10;r5++){
																																																																								sudoku[7][4]=r5;
																																																																								for(r6=0;r6<10;r6++){
																																																																									sudoku[7][5]=r6;
																																																																									for(r7=0;r7<10;r7++){
																																																																										sudoku[7][6]=r7;
																																																																										for(r8=0;r8<10;r8++){
																																																																											sudoku[7][7]=r8;
																																																																											for(r9=0;r9<10;r9++){
																																																																												sudoku[7][8]=r9;
																																																																												for(s1=0;s1<10;s1++){
																																																																													sudoku[8][0]=s1;			
																																																																													for(s2=0;s2<10;s2++){
																																																																														sudoku[8][1]=s2;
																																																																														for(s3=0;s3<10;s3++){
																																																																															sudoku[8][2]=s3;
																																																																															for(s4=0;s4<10;s4++){
																																																																																sudoku[8][3]=s4;
																																																																																for(s5=0;s5<10;s5++){
																																																																																	sudoku[8][4]=s5;
																																																																																	for(s6=0;s6<10;s6++){
																																																																																		sudoku[8][5]=s6;
																																																																																		for(s7=0;s7<10;s7++){
																																																																																			sudoku[8][6]=s7;
																																																																																			for(s8=0;s8<10;s8++){
																																																																																				sudoku[8][7]=s8;
																																																																																				for(s9=0;s9<10;s9++){
																																																																																					sudoku[8][8]=s9;
																																																																																					//si las varianbles por filas son iguales
																																																																																					if(
																																																																																					i1!=i2 && i1!=i3 && i1!=i4 && i1!=i5 && i1!=i6 && i1!=i7 && i1!=i8 && i1!=i9 &&
																																																																																					i2!=i3 && i2!=i4 && i2!=i5 && i2!=i6 && i2!=i7 && i2!=i8 && i2!=i9 &&
																																																																																					i3!=i4 && i3!=i5 && i3!=i6 && i3!=i7 && i3!=i8 && i3!=i9 && 
																																																																																					i4!=i5 && i4!=i6 && i4!=i7 && i4!=i8 && i4!=i9 && 
																																																																																					i5!=i6 && i5!=i7 && i5!=i8 && i5!=i9 &&
																																																																																					i6!=i7 && i6!=i8 && i1!=i9 &&
																																																																																					i7!=i8 && i7!=i9 &&
																																																																																					i8!=i9 &&
																																																																																					j1!=j2 && j1!=j3 && j1!=j4 && j1!=j5 && j1!=j6 && j1!=j7 && j1!=j8 && j1!=j9 &&
																																																																																					j2!=j3 && j2!=j4 && j2!=j5 && j2!=j6 && j2!=j7 && j2!=j8 && j2!=j9 &&
																																																																																					j3!=j4 && j3!=j5 && j3!=j6 && j3!=j7 && j3!=j8 && j3!=j9 &&
																																																																																					j4!=j5 && j4!=j6 && j4!=j7 && j4!=j8 && j4!=j9 &&
																																																																																					j5!=j6 && j5!=j7 && j5!=j8 && j5!=j9 &&
																																																																																					j6!=j7 && j6!=j8 && j6!=j9 &&
																																																																																					j7!=j8 && j7!=j9 && 
																																																																																					j8!=j9 &&
																																																																																					k1!=k2 && k1!=k3 && k1!=k4 && k1!=k5 && k1!=k6 && k1!=k7 && k1!=k8 && k1!=k9 &&
																																																																																					k2!=k3 && k2!=k4 && k2!=k5 && k2!=k6 && k2!=k7 && k2!=k8 && k2!=k9 && 
																																																																																					k3!=k4 && k3!=k5 && k3!=k6 && k3!=k7 && k3!=k8 && k3!=k9 &&
																																																																																					k4!=k5 && k4!=k6 && k4!=k7 && k4!=k8 && k4!=k9 && 
																																																																																					k5!=k6 && k5!=k7 && k5!=k8 && k5!=k9 && 
																																																																																					k6!=k7 && k6!=k8 && k6!=k9 &&
																																																																																					k7!=k8 && k7!=k9 &&
																																																																																					k8!=k9 &&
																																																																																					l1!=l2 && l1!=l3 && l1!=l4 && l1!=l5 && l1!=l6 && l1!=l7 && l1!=l8 && l1!=l9 &&
																																																																																					l2!=l3 && l2!=l4 && l2!=l5 && l2!=l6 && l2!=l7 && l2!=l8 && l2!=l9 &&
																																																																																					l3!=l4 && l3!=l5 && l3!=l6 && l3!=l7 && l3!=l8 && l3!=l9 &&
																																																																																					l4!=l5 && l4!=l6 && l4!=l7 && l4!=l8 && l4!=l9 &&
																																																																																					l5!=l6 && l5!=l7 && l5!=l8 && l5!=l9 &&
																																																																																					l6!=l7 && l6!=l8 && l6!=l9 &&
																																																																																					l7!=l8 && l7!=l9 &&
																																																																																					l8!=l9 &&
																																																																																					m1!=m2 && m1!=m3 && m1!=m4 && m1!=m5 && m1!=m6 && m1!=m7 && m1!=m8 && m1!=m9 &&
																																																																																					m2!=m3 && m2!=m4 && m2!=m5 && m2!=m6 && m2!=m7 && m2!=m8 && m2!=m9 &&
																																																																																					m3!=m4 && m3!=m5 && m3!=m6 && m3!=m7 && m3!=m8 && m3!=m9 &&
																																																																																					m4!=m5 && m4!=m6 && m4!=m7 && m4!=m8 && m4!=m9 &&
																																																																																					m5!=m6 && m5!=m7 && m5!=m8 && m5!=m9 &&
																																																																																					m6!=m7 && m6!=m8 && m6!=m9 &&
																																																																																					m7!=m8 && m7!=m9 &&
																																																																																					m8!=m9 &&
																																																																																					n1!=n2 && n1!=n3 && n1!=n4 && n1!=n5 && n1!=n6 && n1!=n7 && n1!=n8 && n1!=n9 && 
																																																																																					n2!=n3 && n2!=n4 && n2!=n5 && n2!=n6 && n2!=n7 && n2!=n8 && n2!=n9 && 
																																																																																					n3!=n4 && n3!=n5 && n3!=n6 && n3!=n7 && n3!=n8 && n3!=n9 &&
																																																																																					n4!=n5 && n4!=n6 && n4!=n7 && n4!=n8 && n4!=n9 &&
																																																																																					n5!=n6 && n5!=n7 && n5!=n8 && n5!=n9 &&
																																																																																					n6!=n7 && n6!=n8 && n6!=n9 &&
																																																																																					n7!=n8 && n7!=n9 &&
																																																																																					n8!=n9 &&
																																																																																					p1!=p2 && p1!=p3 && p1!=p4 && p1!=p5 && p1!=p6 && p1!=p7 && p1!=p8 && p1!=p9 &&
																																																																																					p2!=p3 && p2!=p4 && p2!=p5 && p2!=p6 && p2!=p7 && p2!=p8 && p2!=p9 && 
																																																																																					p3!=p4 && p3!=p5 && p3!=p6 && p3!=p7 && p3!=p8 && p3!=p9 && 
																																																																																					p4!=p5 && p4!=p6 && p4!=p7 && p4!=p8 && p4!=p9 && 
																																																																																					p5!=p6 && p5!=p7 && p5!=p8 && p5!=p9 && 
																																																																																					p6!=p7 && p6!=p8 && p6!=p9 && 
																																																																																					p7!=p8 && p7!=p9 && 
																																																																																					p8!=p9 && 
																																																																																					r1!=r2 && r1!=r3 && r1!=r4 && r1!=r5 && r1!=r6 && r1!=r7 && r1!=r8 && r1!=r9 &&
																																																																																					r2!=r3 && r2!=r4 && r2!=r5 && r2!=r6 && r2!=r7 && r2!=r8 && r2!=r9 &&
																																																																																					r3!=r4 && r3!=r5 && r3!=r6 && r3!=r7 && r3!=r8 && r3!=r9 && 
																																																																																					r4!=r5 && r4!=r6 && r4!=r7 && r4!=r8 && r4!=r9 && 
																																																																																					r5!=r6 && r5!=r7 && r5!=r8 && r5!=r9 && 
																																																																																					r6!=r7 && r6!=r8 && r6!=r9 && 
																																																																																					r7!=r8 && r7!=r9 &&
																																																																																					r8!=r9 &&
																																																																																					s1!=s2 && s1!=s3 && s1!=s4 && s1!=s5 && s1!=s6 && s1!=s7 && s1!=s8 && s1!=s9 &&
																																																																																					s2!=s3 && s2!=s4 && s2!=s5 && s2!=s6 && s2!=s7 && s2!=s8 && s2!=s9 &&
																																																																																					s3!=s4 && s3!=s5 && s3!=s6 && s3!=s7 && s3!=s8 && s3!=s9 &&
																																																																																					s4!=s5 && s4!=s6 && s4!=s7 && s4!=s8 && s4!=s9 &&
																																																																																					s5!=s6 && s5!=s7 && s5!=s8 && s5!=s9 &&
																																																																																					s6!=s7 && s6!=s8 && s6!=s9 &&
																																																																																					s7!=s8 && s7!=s9 &&
																																																																																					s8!=s9 ){
																																																																																						
																																																																																						//separador visual
																																																																																						printf("##############################################################################################################################\n");
																																																																																						//se imprime el sudoku actual
																																																																																						imprimirSudoku(sudoku);
																																																																																						printf("\n\n");
																																																																																					}
																																																																																					
																																																																																					
																																																																																					verFila=verificarFila(sudoku);
																																																																																					verColum=verificarColumna(sudoku);
																																																																																					verSM=verificarSubMatriz(sudoku);
																																																																																					verJau=verificarJaula(sudoku,lista_jaulas);
																																																																																					
																																																																																					if(verFila==1 && verColum==1 && verSM==1 &&verJau==1){
																																																																																						printf("Has llegado a la solucion\n");
																																																																																						printf("Deseas volver a jugar:\n1)Si\n2)No:\n>> ");
																																																																																						scanf("%d",&jugar);
																																																																																					}
																																																																																					if(jugar==2){
																																																																																						printf("Hasta pronto");
																																																																																					}
																																																																																					
																																																																																					
																																																																																				}
																																																																																				
																																																																																			}
																																																																																		}
																																																																																	}
																																																																																}
																																																																															}
																																																																														}
																																																																													}
																																																																												}
																																																																											}
																																																																										}
																																																																									}
																																																																								}
																																																																							}
																																																																						}
																																																																					}
																																																																				}
																																																																			}
																																																																		}
																																																																	}
																																																																}
																																																															}
																																																														}
																																																													}
																																																												}
																																																											}
																																																										}                                                                          
																																																									}
																																																								}
																																																							}
																																																						}
																																																					}
																																																				}
																																																			}
																																																		}
																																																	}
																																																}
																																															}
																																														}
																																													}
																																												}
																																											}
																																										}
																																									}	                                                                                            
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}		
				}
			}
			
		
			
			
			
			
			
			
		}//opcion==2
	}//while de jugar	

	return 0;
}// corchete del main
