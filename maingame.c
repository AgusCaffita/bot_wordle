#include <stdio.h>
#include "maingame.h"
#include "bot.h"

void abc_de_abajo(letras* lts){
    printf("\n");
    for (int i = 0; i < 26; i++){
	if(lts[i].verde){
		printf("\033[0;32m");
		printf("%c ", lts[i].letrita);}
	else if(lts[i].amarillo){
		printf("\033[0;33m");
		printf("%c ", lts[i].letrita);}  
	else if(lts[i].gris){
		printf("\033[31m");
		printf("%c ", lts[i].letrita);
    }else{
        printf("\033[0m");
        printf("%c ", lts[i].letrita);}
    }
    printf("\n");
    printf("\033[0m");
}

int funcioncita(char* palabra, char letra){
    for(int i=0; i<MAX; i++){
        if(palabra[i]==letra)
            return 1;
    }
    return 0;
}

int revision(char* palabra, char* adivinacion, letras* lts){
    for(int i=0; i<MAX; i++){
        if(palabra[i] == adivinacion[i]){
            printf("\033[0;32m");
            printf("%c",adivinacion[i]);
            for(int j=0; j<26; j++){
            	if(lts[j].letrita == adivinacion[i]){
            		lts[j].verde = 1;
                    lts[j].posicion[i] = 1;
                    lts[j].amarillo = 0;
                }
            }
        }else if(funcioncita(palabra, adivinacion[i])){
            printf("\033[0;33m");
            printf("%c",adivinacion[i]); 
            for(int j=0; j<26; j++){
            	if(lts[j].letrita == adivinacion[i] && !lts[j].verde){
           		lts[j].amarillo = 1;
                lts[j].posicion[i] = 2;}
            }

        }else{
            printf("\033[0m");
            printf("%c",adivinacion[i]);
            for(int j=0; j<26; j++){
            	if(!lts[j].verde && !lts[j].amarillo && adivinacion[i]==lts[j].letrita){
            		lts[j].gris = 1;
                }
                }
        }
    }
    
    for(int i=0 ; i<MAX ; i++){
        if(adivinacion[i] != palabra[i]){
            return 0;
        }
    }
    return 1;
}


void armar_alfabeto(letras* lts){
    for(int i=0; i<26; i++){
		lts[i].letrita = 97+i;
	    lts[i].verde = 0;
	    lts[i].amarillo = 0;
	    lts[i].gris = 0;
        for(int j=0;j<MAX;j++){
            lts[i].posicion[j] = 0;
        }
    }
}



int main(int argc, char* argv[]){
    letras lts[26];
    armar_alfabeto(lts);


    heapp heapy;
    FILE* f;
    f = fopen("3.txt","r");
    if (f == NULL) {
    perror("Error al abrir el archivo");
    return 0; 
    }

    armar_base_de_datos(f, &heapy);
    
    srand(time(NULL));
    int n = rand() % 220;

    char c[MAX];
    int priori;
    int contador_de_linea = 0;
    fclose(f);  
    FILE* fi = fopen("3.txt","r");
    while(contador_de_linea != n+1 && n+1 < PALABRAS){
        c[0]='\0';
        fscanf(fi, "%5[^,],%d\n", c, &priori);
        
        contador_de_linea ++; 
    }
    printf("\npalabra secreta: %s\n\n",c);

    fclose(fi);    

    char ip[MAX];

    int intento = 1;

    copi(ip , &heapy);
    int indice_de_eliminacion = 0; 

    while(0 < intento && intento <= 6){
    	
    	if (revision(c,ip,lts) ){
        	printf("\033[0m");
            printf("\n ADIVINASTE!!!!!!!!!"); 
            return 0;}

        else{
			abc_de_abajo(lts);
            best_palabra(&heapy, lts, &indice_de_eliminacion);
            copi(ip , &heapy);
            intento++;
			 
        }  
    }
    printf("PERDISTE JAJAJA");
    
    return 0;
}
