//Lbreira para la lectura del archivo de texto
#include <stdio.h>
//Para la libreria de las cadenas 
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
//Definimos la matris de la maquina de turing
TablaMT MT[100][100];
//El maximo de la cinta char
char cinta[max_cinta];
//Un indice para ver donde va recorriendo en la cinta
int indice_cinta=0;
//Declaramos variables para guardar los datos de nuestro archivo
int No_estado, No_simbolo;
char Caracteres_cinta[] = "";
//La entrada del usuario
char entrada[max_cinta/4] = "";
//Estados iniciales y finales (int)
int estado_inicial, estado_final;
//Tam_in es para saber el tamaño de la entrada del usuario
int tam_in;
//Prueba de estado auxiliar (Para funcion busqueda)
int aux_estado;
//----------------------------------------------------------------------------------------------
//Metodo para busqueda de simbolos en la matriz de la maquina de turing
int busqueda(char simbolo);

//Main
int main(){
    //Abrimos el archivo de texto
    FILE *archivo;
    archivo = fopen("MT.txt","r");
    //Si no se puede abrir el archivo
    if(archivo == NULL){
        printf("No se pudo abrir el archivo");
    }
    //Si se puede abrir el archivo
    else{
        fscanf(archivo,"%d",&No_estado); //Numero de estados totales
        fscanf(archivo,"%d",&No_simbolo); //Numero de simbolos totales
        fscanf(archivo,"%s",&Caracteres_cinta); //Caracteres de la cinta
        fscanf(archivo,"%d",&estado_inicial); //Estado inicial
        fscanf(archivo,"%d",&estado_final); //Estado final
        //Lemos la entrada del usuario
        fscanf(archivo,"%s",&entrada);
        //Leemos los datos del archivo de texto
        for(int i=0;i<No_estado;i++){
            for(int j=0;j<No_simbolo;j++){
                fscanf(archivo,"%d",&MT[i][j].estado);
                fscanf(archivo,"%c",&MT[i][j].simbolo);
                fscanf(archivo,"%d",&MT[i][j].dir);
            }
        }

    }
    //Cerramos el archivo de texto
    fclose(archivo);
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
            printf("Estado: %d",MT[i][j].estado);
            printf("\n Simbolo: %c",MT[i][j].simbolo);
            printf("\n Direccion: %d",MT[i][j].dir);
            printf("\t");
        }
        printf("\n");
    }

//Recorremos la cinta para llenarlo con espacios en blanco
    for(int i=0;i<max_cinta;i++){
        cinta[i]=' '; //Tambien podemos representarlo como cinta[i]='\0'; \0 es para representar un espacio en blanco
    }
//El indice de la cinta apuntara a la mitad de esta
    indice_cinta=max_cinta/2;
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
    do{
        int pos_simbolo=0;
        pos_simbolo=busqueda(cinta[indice_cinta]);
        //Si el simobolo es diferente de -1 es decir un simbolo valido
        if(pos_simbolo!=-1){
            //Entonces cambiamos los simbolos de la cinta
            aux_estado=MT[aux_estado][pos_simbolo].estado;
            cinta[indice_cinta]=MT[aux_estado][pos_simbolo].simbolo;
            //Y cambiamos la direccion de la cinta
            indice_cinta=indice_cinta+MT[aux_estado][pos_simbolo].dir;
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
        printf("\n La cadena fue aceptada\n");
    }else{
        printf("\n La cadena no fue aceptada\n");
    }
    return 0;

}

//Funcion para buscar el simbolo en la matriz de la maquina de turing
int busqueda(char simbolo){ 
    int pos_simbolo=0;
    for(int i=0;i<No_simbolo;i++){
        if(MT[aux_estado][i].simbolo==simbolo){
            pos_simbolo=i;
        }
    }
    return pos_simbolo;

}
