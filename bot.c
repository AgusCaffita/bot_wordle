#include <stdio.h>
#include "bot.h"

void ordenar(heapp *heap, int posicion){ 
    bdd aux;
    for(;heap->palabras[posicion].prioridad>heap->palabras[(posicion-1)/2].prioridad; posicion=(posicion-1)/2){
        
        aux = heap->palabras[(posicion-1)/2];
        heap->palabras[(posicion-1)/2] = heap->palabras[posicion];
        heap->palabras[posicion] = aux;    }
}

void armar_base_de_datos(FILE* f, heapp* heap) {
    int aux = 0;

    while(fscanf(f,"%5[^,],%d\n", heap->palabras[aux].palabra , &heap->palabras[aux].prioridad)==2){
       if(aux!=0){
            ordenar(heap,aux);
        }
        aux++;
    }
}

void eliminar(heapp *heap, int posicionpadre, int* indice_de_eliminacion){
    heap->palabras[posicionpadre] = heap->palabras[PALABRAS - (*indice_de_eliminacion)];
    (*indice_de_eliminacion)++;
    
    int size = PALABRAS - (*indice_de_eliminacion);
    int mayor = posicionpadre;
    
    while (1) {
        int izquierda = (2 * mayor) + 1;
        int derecha = (2 * mayor) + 2;
        
        if (izquierda < size && heap->palabras[izquierda].prioridad > heap->palabras[mayor].prioridad) {
            mayor = izquierda;
        }
        if (derecha < size && heap->palabras[derecha].prioridad > heap->palabras[mayor].prioridad) {
            mayor = derecha;
        }
        
        if (mayor == posicionpadre) {
            break;
        }
        
        bdd aux = heap->palabras[posicionpadre];
        heap->palabras[posicionpadre] = heap->palabras[mayor];
        heap->palabras[mayor] = aux;
        
        posicionpadre = mayor;
    }
}

void copi(char* ip, heapp *heap){
    for(int i = 0; i<MAX ; i++){
        ip[i]=heap->palabras[0].palabra[i];
    }
}

int eta_o_nueta(heapp* heap, char let){
	for(int p=0; p<MAX; p++){
		if(let == heap->palabras[0].palabra[p])
			return 1;
	}
	return 0;
}

bool chekeo_ielou(int* posicion, char ltra, char* palabra){
    for(int l=0;l<MAX;l++){
        if(posicion[l]==2){
            return palabra[l]!=ltra;
        }
    }
    
}

bool chekeo_grin(int* posicion, char ltra, char* palabra){
    for(int l=0;l<MAX;l++){
        if(posicion[l]==1){
            return palabra[l]==ltra;
        }
    }
    
}



void best_palabra(heapp* heap, letras* lts, int* indice_de_eliminacion){
    eliminar(heap, 0, indice_de_eliminacion);
    
    for(int i=0;i<26; i++){
        if(lts[i].gris==1){
        for(int k=0; k<MAX; k++){
            if(lts[i].letrita == heap->palabras[0].palabra[k]){
                eliminar(heap, 0, indice_de_eliminacion);
                i=-1;
                k=0;}
        }
        }
        else if(lts[i].verde==1){
            if(!chekeo_grin(lts[i].posicion, lts[i].letrita, heap->palabras[0].palabra)){
        		eliminar(heap, 0, indice_de_eliminacion);
        		i=-1;}
        }

        else if(lts[i].amarillo==1){
        	if(!eta_o_nueta(heap, lts[i].letrita) || !chekeo_ielou(lts[i].posicion, lts[i].letrita, heap->palabras[0].palabra)){
        		eliminar(heap, 0, indice_de_eliminacion);
                i=-1;
            }	
        }
    }
}