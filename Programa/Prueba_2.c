//Librerias para lectura de archivos txt y cadenas
#include <stdio.h>
#include <string.h>

//Cinta con un maximo de 2000 caracteres
#define max_cinta 2000
//Estructura de la maquina de turing
typedef struct{
    //Numero de estados
    int estado;
    //Numero de simbolos
    char simbolo;
    //Direccion de la cinta
    int dir;
}TablaMT;
//Tamaño de la maquina de turing
TablaMT MT[100][100];
//Cinta maxima de entrada
char cinta[max_cinta];
//Indice de la cinta
int indice_cinta=0;
//Variables del archivo txt
int No_estado, No_simbolo, estado_inicial, estado_final, tam_in;
char Caracteres_cinta[] = "@"; //La cinta de entrada tendra espacios en blanco que seran representados por @
//Entrada del usuario
char entrada[max_cinta/4] = "@";
//Estados auxiliare
int aux_estado;

//Metodos
int busqueda(char simbolo);

//Main
int main(){
    //Abrimos un archivo de texto
    FILE *archivo;
    archivo = fopen("MT3.txt","r");
    //Si no se puede abrir el archivo
    if(archivo == NULL){
        printf("No se pudo abrir el archivo");
    }else{
        fscanf(archivo,"%d",&No_estado); //Numero de estados totales
        fscanf(archivo,"%d",&No_simbolo); //Numero de simbolos totales
        fscanf(archivo,"%s",Caracteres_cinta); //Caracteres de la cinta
        fscanf(archivo,"%d",&estado_inicial); //Estado inicial
        fscanf(archivo,"%d",&estado_final); //Estado final
        //Lemos la entrada del usuario
        fscanf(archivo,"%s",entrada);
        //Lectura de estados, simbolos y direcciones
        for(int i=0;i<No_estado;i++){
            for(int j=0;j<No_simbolo;j++){
                char aux;
                //Necesitamos un condicional despues del primer fscanf
                //Hay un error al momento de leerlo en la matriz, no se porque
                fscanf(archivo,"%d",&MT[i][j].estado);
                //Si el simbolo es un @ que simboliza un espacio en blanco tenemos que saltar esa lectura y seguir con el simbolo
                if(aux=='@'){
                    fscanf(archivo,"%c",&aux);
                }
                fscanf(archivo,"%c",&MT[i][j].simbolo);
                 if(aux=='@'){
                    fscanf(archivo,"%c",&aux);
                }
                fscanf(archivo,"%d",&MT[i][j].dir);
                 if(aux=='@'){
                    fscanf(archivo,"%c",&aux);
                }
            }
        }
    }
    //Cerramos el archivo
    fclose(archivo);
//Imprimir caracteres 

    printf("\n No. de estados: %d",No_estado);
    printf("\n No. de simbolos: %d",No_simbolo);
    printf("\n Caracteres de la cinta: %s",Caracteres_cinta);
    printf("\n Estado inicial: %d",estado_inicial);
    printf("\n Estado final: %d",estado_final);
    printf("\n Entrada: %s",entrada);

//Imprimiir la matriz
        for(int i=0;i<No_estado;i++){
        for(int j=0;j<No_simbolo;j++){
            printf("\n Estado: %d",MT[i][j].estado);
            printf("\n Simbolo: %c",MT[i][j].simbolo);
            printf("\n Direccion: %d",MT[i][j].dir);
            printf("\t");
            
        }
        printf("\n\n");
    }
   
//Por el momento veremos si podemos leer la cinta de esta manera
/*
//Recorremos tod la cinta y tenemos que llenerla con espacios en blanco
//Estos estaran representados con un @
    for(int i=0; i<max_cinta; i++){
        cinta[i] = '@';
    }
    //El indice de la cinta debe estar a la mitad de esta para que tenga espacio de movimiento
    indice_cinta = max_cinta/2;
//Copiamos la entrada del usuario a la cinta
    tam_in = strlen(entrada);
    //Variable j para copiar la entrada a la cinta
    int j=0;
    for(int i=indice_cinta; i<indice_cinta+tam_in; i++){
        cinta[i] = entrada[j];
        j++;
    }
//Ahora declaramos una bandera para hacer que nuestra maquina de turing se detenga
int bandera = 0;
//Variable aux para que vaya cambiando de estado, esta inicia en estado_inicial
aux_estado = estado_inicial; 
   //Recorremos la maquina
   do{
    int pos_simbolo=0;
    //Pos_simbolo nos devulve el simbolo en el que se encuentra la cinta
    pos_simbolo=busqueda(cinta[indice_cinta]);
    //Si el simbolo es diferente de -1 entonces el simbolo es valido
    if(pos_simbolo!=-1){
        //Cambiamos los estados de la cinta
        aux_estado=MT[aux_estado][pos_simbolo].estado;
        cinta[indice_cinta]=MT[aux_estado][pos_simbolo].simbolo;
        //La direccion tiene dos valores -1 o 1 entonces al sumarlos cambiara de direccion
        indice_cinta=indice_cinta+MT[aux_estado][pos_simbolo].dir;
    }else{
        //Si el simbolo es -1 entonces la maquina de turing se detiene
        bandera=1;
    }
    //Si el estado es -1 entonces la maquina de turing se detiene
    if(aux_estado==-1){
        bandera=1;
    }
   }while((aux_estado!=estado_final)&&(bandera==0));
}

//Metodo para buscar el simbolo en la cinta
int busqueda(char simbolo){
    //Recorremos la cinta
    for(int i=0;i<No_simbolo;i++){
        //Si el simbolo es igual al simbolo de la cinta
        if(simbolo==Caracteres_cinta[i]){
            //Entonces regresamos la posicion del simbolo
            return i;
        }
    }
    //Si no se encuentra el simbolo entonces regresamos -1
    return -1;
*/
}