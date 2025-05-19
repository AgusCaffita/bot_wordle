#ifndef maingame_h
#define maingame_h
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 5
#define PALABRAS 220

typedef struct{
    char letrita;
    int verde;
    int amarillo;
    int gris;
    int posicion[MAX];  //0 si no se chequeo, -1 si no esta y 1 si esta
}letras;

void abc_de_abajo(letras* lts);
int funcioncita(char* palabra, char letra);
int revision(char* palabra, char* adivinacion, letras* lts);
void armar_alfabeto(letras* lts);

#endif
