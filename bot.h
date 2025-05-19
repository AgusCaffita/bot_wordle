#ifndef bot_h
#define bot_h
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "maingame.h"
#define MAX 5
#define PALABRAS 220

typedef struct{
    char palabra[MAX];
    int prioridad;
}bdd;

typedef struct{
    bdd palabras[PALABRAS];
}heapp;

void copi(char* ip, heapp *heap);
void ordenar(heapp *heap, int posicion);
void armar_base_de_datos(FILE* f, heapp* heap);
int eta_o_nueta(heapp* heap, char let);
bool chekeo_ielou(int* posicion, char ltra, char* palabra);
bool chekeo_grin(int* posicion, char ltra, char* palabra);
void best_palabra(heapp* heap, letras* lts, int* indice_de_eliminacion);

#endif
