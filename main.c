#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

LISTA ** algoritmo(LISTA * L,double largo_caja, double alto_caja, double ancho_caja,double * Vfinal){
  double Vmax = largo_caja*alto_caja*ancho_caja;
  LISTA * C = crearLista();
  LISTA * F = crearLista();
  LISTA * Lord = ordenar_por_volumen(L);
  *Vfinal = 0.0;
  double Vactual = 0.0;
  double vol = 0.0;
  NODO * aux = Lord->primero;
  while(aux != NULL){
    if(Vactual + aux->volumen < Vmax){
      C = insertar_final(C,aux->id,aux->largo,aux->alto,aux->ancho);
      Vactual = Vactual + aux->volumen;
    }else{
      F = insertar_final(F,aux->id,aux->largo,aux->alto,aux->ancho);
    }
    aux = aux->sig;
  }
  *Vfinal = Vactual;
  LISTA ** resultados = (LISTA**)malloc(2*sizeof(LISTA*));
  resultados[0] = C;
  resultados[1] = F;
  return resultados;
}

void salida(LISTA ** resultados, double Vfinal, double Vmax, FILE * file){
  NODO * aux = resultados[0]->primero;
  NODO * aux1 = resultados[1]->primero;
  fprintf(file, "En la caja:\n" );
  while(aux!=NULL){
    fprintf(file,"%s %.5f %.5f %.5f\n", aux->id, aux ->largo, aux->alto, aux->ancho);
    aux = aux->sig;
  }
  fprintf(file, "\nFuera de la caja:\n" );
  while(aux1!=NULL){
    fprintf(file,"%s %.5f %.5f %.5f\n", aux1->id, aux1 ->largo, aux1->alto, aux1->ancho);
    aux1 = aux1->sig;
  }
  fprintf(file, "Espacio libre dentro de la caja:\n%.0f centímetros cúbicos", Vmax-Vfinal);
}

int main(int argc, char const *argv[]) {
  //Definicion de variables///
  double LARGO_MAX, ALTO_MAX, ANCHO_MAX  ;
  char * ident = NULL;
  double largo,alto,ancho;
  double Vfinal;
  //Verificacion de entrada////
  if(argc == 3){
    FILE * in = fopen(argv[1],"r");
    FILE * out = fopen(argv[2],"w");
    if(in){
      if(out){
        //////////////////////PROCESAMIENTO DE DATOS//////////////
        fscanf(in,"%lf %lf %lf\n",&LARGO_MAX,&ALTO_MAX,&ANCHO_MAX);
        LARGO_MAX = LARGO_MAX*100;
        ALTO_MAX = ALTO_MAX*100;
        ANCHO_MAX = ANCHO_MAX*100;
        LISTA * L = crearLista();
        while(!feof(in)){
          ident = (char *)malloc(20*sizeof(char));
          fscanf(in,"%s %lf %lf %lf\n",ident,&largo,&alto,&ancho);
          //printf("%s\n", ident);
          L = insertar_final(L,ident,largo,alto,ancho);
        }
        //DIMENSIONES CAJA
        printf("La caja que contendrá los libros tiene las siguientes medidas:\n\t LARGO: %.3f cm.\n\t ALTO: %.3f cm.\n\t ANCHO: %.3f cm.\n\nEstos son los posibles libros a introducir en la caja:\n\n", LARGO_MAX, ALTO_MAX, ANCHO_MAX);
        verLista(L);
        printf("\n\tConsiderando que los libros son líquidos y que pueden usar todo el espacio sin problemas de sobrelapamiento entre ellos.\n");
        printf("Estos deben cumplir con cubrir el volumen máximo de la caja que es de %.3f cm³\n\n", LARGO_MAX * ALTO_MAX *ANCHO_MAX);
        LISTA ** resultados = algoritmo(L,LARGO_MAX,ALTO_MAX,ANCHO_MAX,&Vfinal);
        salida(resultados,Vfinal,LARGO_MAX * ALTO_MAX *ANCHO_MAX,out);
        printf("Revise salida.out\n");
        //printf("Estos son los libros dentro de la caja:\n" );
        //verLista(resultados[0]);
        //printf("Estos son los libros fuera de la caja:\n" );
        //verLista(resultados[1]);
        fclose(in);
        fclose(out);
      }else{
          printf("Error en la lectura de archivos: %s\n", argv[2]);
      }
    }else{
      printf("Error en la lectura de archivos: %s\n", argv[1]);
    }
  }else{
    printf("Para ejecutar ingrese:\n\n\t");
    printf("./main [nombre_entrada] [nombre_salida]\n");
    return 1;
  }
  return 0;
}
