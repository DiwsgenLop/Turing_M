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
}MTtabla;

MTtabla MT[100][100];//Definimos el tamaño de la maquina de turing

//Variables del archivo txt
int No_estado, No_simbolo, estado_inicial, estado_final, tam_in;//Tam_in es el tamaño de la entrada del usuario
//Los simbolos de la cinta inicial seran llenados por espacios en blanco
//Estos espacios seran representados por '_'
char Caracteres_cinta[100] = "";
//Entrada del usuario
char entrada[cinta_maxima/4] = "";
//Cinta donde se traspasa los datos de entrada y sera cambiada
char cinta[cinta_maxima];
//Indice donde apuntara hacia la cinta
int indice_cinta=cinta_maxima/2; //Tendra espacio hacia adelante o atras

//Metodo de busqueda de inidice para simbolo
int busqueda(char simbolo);

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
            fscanf(archivo,"%d",&MT[i][j].estado);
            fseek(archivo, 1, SEEK_CUR);  // Ignora el espacio o salto de línea después del estado
            fscanf(archivo,"%c",&MT[i][j].simbolo);
            fseek(archivo, 1, SEEK_CUR);  // Ignora el espacio o salto de línea después del SIMBOLO
            fscanf(archivo,"%d",&MT[i][j].dir);
            fseek(archivo, 1, SEEK_CUR);  // Ignora el espacio o salto de línea después de la direccion
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
                printf("Estado [%d][%d]: %d",i,j,MT[i][j].estado);
                printf("\n");
                printf("Simbolo: %c",MT[i][j].simbolo);
                printf("\n");
                printf("Direccion: %d",MT[i][j].dir);
                printf("\n");
            }
    }   

//Ahora queda lo siguiente
 //Tamaño de la entrada
    tam_in = strlen(entrada);  
    printf("Tamaño de la entrada: %d\n",tam_in);
//1.- Llenar la cinta con los espacios en blanco
for (int i = 0; i < cinta_maxima; i++)
    {
        cinta[i] = '_';
    }

//Llenamos la cinta desde el indice hasta el tamaño de la entrada del usuario
int x=0;
for (int j = indice_cinta; j < indice_cinta+tam_in; j++)
{
    cinta[j]=entrada[x];
    x++;
}
/*
for (int j = indice_cinta; j < indice_cinta+tam_in; j++)
{
    printf("\nLos valores de la cinta son: [%c]\n",cinta[j]);
    printf("Valor de j: %d",j);
}
*/
//2.- Ahora debemos de recorrer la cinta para que se pueda mover
//Declaramos una bandera para saber si la maquina de turing se detiene
    int bandera=0;
    //Y una variable auxiliar donde se guarda el estado inicial de la maquina de turing
    int aux_estado=estado_inicial;
    printf("Estado donde iniciara: %d\n",aux_estado);
    //Ahora recorremos la cinta con un do while mientras la bandera sea 0 y el estado no sea -1 si no se detiene
    int pos_simbolo=0;

    do{
        //Retornamos la posicion de el simbolo en la matriz
        pos_simbolo=busqueda(cinta[indice_cinta]);
        printf("Posicion del simbolo: %d\n",pos_simbolo);
        //Si el simobolo es diferente de -1 es decir un simbolo existente
        if(pos_simbolo!=-1){
            cinta[indice_cinta]=MT[aux_estado][pos_simbolo].simbolo;
            printf("Simbolo actual: %c\n",cinta[indice_cinta]);
            indice_cinta=indice_cinta+MT[aux_estado][pos_simbolo].dir;
            printf("Direccion actual: %d\n",indice_cinta);
            //El ultimo en ser cambiado sera el estado para que no altere los otros cambios
            aux_estado=MT[aux_estado][pos_simbolo].estado;
            printf("Estado actual: %d\n",aux_estado);
            
        }else{
            //Si el simbolo es -1 entonces la maquina de turing se detiene
            bandera=1;
        }
        //Si el estado es -1 entonces la maquina de turing se detiene
        if(aux_estado==-1)
            bandera=1;
            //printf("Acaba la maquina, cinta resultante: [%s]\n",cinta[indice_cinta+tam_in]);            
    }while((aux_estado!=estado_final)&&(bandera==0));
    
//Ahora queda decir si fue aceptada la cadena o no
    if((estado_final!=0) && (aux_estado==estado_final)){
        printf("\n La cadena fue aceptada\n");
    }else{
        printf("\n La cadena no fue aceptada\n");
    }
}

//Funcion para buscar el simbolo en la matriz de la maquina de turing
int busqueda(char simbolo){ 
    for(int i=0;i<No_simbolo;i++){ //Los simbolos totales de la cinta no pueden exeder a el numero de simbolos por lo que tenemos la posicion 
        if(simbolo==Caracteres_cinta[i]){ //Si el simbolo enviado coincide con el de la cinta entonces
            //Entonces regresamos la posicion del simbolo
            return i;
        }
    }
    return -1;

}
