#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(int argc, char const *argv[]) {
  /* code */
  if(argc == 3){
    FILE * in = fopen(argv[1],"r");
    FILE * out = fopen(argv[2],"w");
    if(in){
      if(out){
        double ANCHO_MAX, ALTO_MAX, LARGO_MAX;
        fscanf(in,"%lf %lf %lf\n",&LARGO_MAX,&ALTO_MAX,&ANCHO_MAX);
        printf("%lf %.lf %lf\n", LARGO_MAX, ALTO_MAX, ANCHO_MAX);
        LISTA * L = crearLista();
        verLista(L);
        L = insertar_inicio(L,'A',15,24,6);
        verLista(L);
        fclose(in);
        fclose(out);
      }else{
          printf("Error en la lectura de archivos: %s\n", argv[2]);
      }
    }else{
      printf("Error en la lectura de archivos: %s\n", argv[1]);
    }
  }else{
    printf("Faltan o sobran argumentos\n");
    return 1;
  }
  return 0;
}
