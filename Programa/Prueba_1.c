//Libreria para la lectura del archivo de texto
#include <stdio.h>
//Para la libreria de las cadenas 
#include <string.h>

//Cinta con un maximo de 2000 caracteres
#define cinta_maxima 2000
//Estructura de la maquina de turing
typedef struct{
    //Numero de estados
    int estado;
    //Numero de simbolos
    char simbolo;
    //Direccion de la cinta
    int dir;
}TablaMT;
//Definimos la matris de la maquina de turing
TablaMT MT[100][100];

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

//----------------------------------------------------------------------------------------------
//Metodo para busqueda de simbolos en la matriz de la maquina de turing
int busqueda(char simbolo);

//Main
int main(){
    //Abrimos el archivo de texto
    FILE *archivo;
    archivo = fopen("Lectura.txt","r");
    //Si no se puede abrir el archivo
    if(archivo == NULL){
        printf("No se pudo abrir el archivo");
    }
    //Si se puede abrir el archivo
    else{
        fscanf(archivo,"%d",&No_estado); //Numero de estados totales
        fscanf(archivo,"%d",&No_simbolo); //Numero de simbolos totales
        fscanf(archivo,"%d",&estado_inicial); //Estado inicial
        fscanf(archivo,"%d",&estado_final); //Estado final
        fscanf(archivo,"%s",entrada);        //Lemos la entrada del usuario
        fscanf(archivo,"%s",Caracteres_cinta); //Caracteres de la cinta
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
    //Cerramos el archivo de texto
    fclose(archivo);
    /* Solo veremos los caracteres de la cinta
//Imprimir caracteres 

    printf("\n No. de estados: %d",No_estado);
    printf("\n No. de simbolos: %d",No_simbolo);
    printf("\n Caracteres de la cinta: %s",Caracteres_cinta);
    printf("\n Estado inicial: %d",estado_inicial);
    printf("\n Estado final: %d",estado_final);
    printf("\n Entrada: %s",entrada);

//Imprimir matriz
    printf("\n Matriz de la maquina de turing: \n");
    for(int i=0;i<No_estado;i++){
        for(int j=0;j<No_simbolo;j++){
            printf("\n Estado: %d",MT[i][j].estado);
            printf("\n Simbolo: %c",MT[i][j].simbolo);
            printf("\n Direccion: %d",MT[i][j].dir);
            printf("\t");
            
        }
        printf("\n\n");
    }
    */
//Recorremos la cinta para llenarlo con espacios en blanco
    for(int i=0;i<cinta_maxima;i++){
        cinta[i]='_'; //Tambien podemos representarlo como cinta[i]='\0'; \0 es para representar un espacio en blanco
    }
    //Tam_in es para saber el tamaño de la entrada del usuario
    tam_in = strlen(entrada);
    int i=0;
    //Recorremos la cinta para llenarlo con la entrada del usuario
    for (int j=indice_cinta;j<indice_cinta+tam_in;j++){
        cinta[j]=entrada[i];
        i++;
    }

    //Declaramos una bandera para saber si la maquina de turing se detiene
    int bandera=0;
    //Y una variable auxiliar donde se guarda el estado inicial de la maquina de turing
    int aux_estado=estado_inicial;
    //Ahora recorremos la cinta con un do while mientras la bandera sea 0 y el estado no sea -1 si no se detiene
    int pos_simbolo=0;
    do{
        //Retornamos la posicion de el simbolo en la matriz
        pos_simbolo=busqueda(cinta[indice_cinta]);
        //Si el simobolo es diferente de -1 es decir un simbolo existente
        if(pos_simbolo!=-1){
            //Entonces cambiamos los simbolos de la cinta
            cinta[indice_cinta]=MT[aux_estado][pos_simbolo].simbolo;
            indice_cinta=indice_cinta+MT[aux_estado][pos_simbolo].dir;
            aux_estado=MT[aux_estado][pos_simbolo].estado;
        }else{
            //Si el simbolo es -1 entonces la maquina de turing se detiene
            bandera=1;
        }
        //Si el estado es -1 entonces la maquina de turing se detiene
        if(aux_estado==-1)
            bandera=1;
    }while((aux_estado!=estado_final)&&(bandera==0));

//Ahora queda decir si fue aceptada la cadena o no
    if((estado_final!=0) && (aux_estado==estado_final)){
        printf("\nLa cadena fue aceptada\nCadena final\n");
         for (int j=0;j<cinta_maxima;j++){
            if(cinta[j]!='_'){
            printf("[%c]",cinta[j]);
            }
        }
        printf("\n");
    }else{
        printf("\n La cadena no fue aceptada\n");
    }
    return 0;

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
