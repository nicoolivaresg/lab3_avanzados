#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
	char id;
  double largo;
  double alto;
  double ancho;
	struct nodo * sig;
}NODO;

typedef struct lista{
  NODO * primero;
  NODO * ultimo;
}LISTA;


int empty(LISTA* L){
	if(L!=NULL){
		if(L->primero==NULL && L->ultimo==NULL){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

LISTA* crearLista(){
	LISTA * nueva_L = (LISTA*)malloc(sizeof(LISTA));
	nueva_L->primero =NULL;
	nueva_L->ultimo =NULL;
	return nueva_L;
}

NODO* crearNodo(char id, double largo, double alto, double ancho){
	NODO * nuevo_nodo = (NODO*)malloc(sizeof(NODO));
	nuevo_nodo->id = id;
  nuevo_nodo->largo =largo;
  nuevo_nodo->alto =alto;
  nuevo_nodo->ancho =ancho;
	nuevo_nodo->sig = NULL;
	return nuevo_nodo;
}

void verLista(LISTA* L){
	if(L !=NULL){
		if(!empty(L)){
			NODO* aux = L->primero;
			while(aux!=NULL){
				printf(" %c %.3f %.3f %.3f", aux->id, aux ->largo, aux->alto, aux->ancho);
				aux=aux->sig;
			}
			printf("\n");
		}else{
      printf("Lista vacía\n" );
    }
	}
}

void imprimirLista(FILE* file, LISTA* L){
	if(L !=NULL && file !=NULL){
		if(!empty(L)){
			NODO* aux = L->primero;
			fprintf(file,"[");
			while(aux!=NULL){
				if(aux->sig == NULL){
					fprintf(file,"%d]", aux->id);
				}else{
					fprintf(file,"%d ", aux->id);
				}
				aux=aux->sig;
			}
			fprintf(file,"\n");
		}
	}
}

LISTA* eliminar_inicio(LISTA* L){
	if(L!=NULL){
		if(empty(L)){
			return NULL;
		}else{
			NODO* aux = L->primero;
			if(aux->sig == NULL){
				L->primero=NULL;
				L->ultimo=NULL;
				free(aux);
				return L;
			}else{
				L->primero = aux->sig;
				free(aux);
				return L;
			}
		}
	}else{
		return NULL;
	}
	return NULL;
}

LISTA* eliminar_final(LISTA * L){
	if(L!=NULL){
		if(empty(L)){
			return NULL;
		}else{
			NODO* aux = L->primero;
			if(aux->sig == NULL){
				L->primero=NULL;
				L->ultimo=NULL;
				free(aux);
				return L;
			}else{
				while(aux->sig!=L->ultimo){
					aux =aux->sig;
				}
				aux->sig=NULL;
				free(L->ultimo);
				L->ultimo = aux;
				return L;
			}
		}
	}else{
		return NULL;
	}
	return NULL;
}

LISTA* insertar_final(LISTA * L, char id, double largo, double alto, double ancho){
	if(L!=NULL){
		NODO* aux = L->ultimo;
		NODO * nuevo = crearNodo(id,largo,alto,ancho);
		if(aux==NULL){
			L->ultimo = nuevo;
			L->primero = nuevo;
			return L;
		}else{
			L->ultimo->sig=nuevo;
			L->ultimo = nuevo;
			return L;
		}
	}else{
		return NULL;
	}
	return NULL;
}

LISTA* insertar_inicio(LISTA* L, char id, double largo, double alto, double ancho){
	if(L!=NULL){
		NODO* aux = L->primero;
		NODO * nuevo = crearNodo(id,largo,alto,ancho);
		if(aux==NULL){
			L->primero = nuevo;
			L->ultimo = nuevo;
		}else{
			nuevo->sig= aux;
			L->primero = nuevo;
		}
		return L;
	}else{
		return NULL;
	}
	return NULL;
}
