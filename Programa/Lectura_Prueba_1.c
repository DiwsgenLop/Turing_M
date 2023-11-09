//Prueba para solo leer datos de entrada
//Librerias necesarias para la lectura de archivos 
#include <stdio.h>
#include <string.h>

//Maximo de una cinta prueba
#define cinta_maxima 2000

//Estructura de entrada
typedef struct{
    //Numero de estados
    int estado;
    //Numero de simbolos
    char simbolo;
    //Direccion de la cinta
    int dir;
}MT;

MT tabla[100][100];//Definimos el tamaño de la maquina de turing

//Variables del archivo txt
int No_estado, No_simbolo, estado_inicial, estado_final, tam_in;//Tam_in es el tamaño de la entrada del usuario
//Los simbolos de la cinta inicial seran llenados por espacios en blanco
//Estos espacios seran representados por '_'
char Caracteres_cinta[] = "";
//Entrada del usuario
char entrada[cinta_maxima/4] = "";


int main(){
    //Abrimos un archivo de texto
    FILE *archivo;
    archivo = fopen("Lectura.txt","r");
    //Si no se puede abrir el archivo
    if(archivo == NULL){
        printf("No se pudo abrir el archivo");
    }else{
        fscanf(archivo,"%d",&No_estado);        //Numero de estados totales
        fscanf(archivo,"%d",&No_simbolo);       //Numero de simbolos totales
        fscanf(archivo,"%d",&estado_inicial);   //Estado inicial
        fscanf(archivo,"%d",&estado_final);     //Estado final
        fscanf(archivo,"%s",entrada);           //Lemos la entrada del usuario
        fscanf(archivo,"%s",Caracteres_cinta);  //Caracteres de la cinta
        
        //Lectura de estados, simbolos y direcciones
        for(int i=0;i<No_estado;i++){
            for(int j=0;j<No_simbolo;j++){
            fscanf(archivo,"%d",&tabla[i][j].estado);
            fseek(archivo, 1, SEEK_CUR);  // Ignora el espacio o salto de línea después del estado
            fscanf(archivo,"%c",&tabla[i][j].simbolo);
            fseek(archivo, 1, SEEK_CUR);  // Ignora el espacio o salto de línea después del estado
            fscanf(archivo,"%d",&tabla[i][j].dir);
            fseek(archivo, 1, SEEK_CUR);  // Ignora el espacio o salto de línea después del estado
            }
        }
    }
    
//Imprimir los caracteres en forma de lista
printf("Simbolos leidos: \n");
printf("Numero de estados: %d",No_estado);
printf("\n");
printf("Numero de simbolos: %d",No_simbolo);
printf("\n");
printf("Estado inicial: %d",estado_inicial);
printf("\n");
printf("Estado final: %d",estado_final);
printf("\n");
printf("Entrada del usuario: %s",entrada);
printf("\n");
printf("Caracteres de la cinta: %s",Caracteres_cinta);
printf("\n");

printf("Estados, simbolos y direcciones: \n");
//Imprimir los estados, simbolos y direcciones
    for (int i = 0; i < No_estado; i++)
        {
            for(int j = 0; j < No_simbolo; j++)
            {
                printf("Estado: %d",tabla[i][j].estado);
                printf("\n");
                printf("Simbolo: %c",tabla[i][j].simbolo);
                printf("\n");
                printf("Direccion: %d",tabla[i][j].dir);
                printf("\n");
            }
    }   

}