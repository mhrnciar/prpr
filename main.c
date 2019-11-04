//
//  Projekt 1
//  Matej Hrnciar
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f_v(FILE *fin){
    char meno[50], priez[50], spz[7], datum[8];
    int typ, cena;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, &typ, &cena, datum) != EOF){
        printf("meno a priezvisko: %s %s\n", meno, priez);
        printf("SPZ: %s\n", spz);
        printf("typ auta: %d\n", typ);
        printf("cena: %d\n", cena);
        printf("datum: %s\n\n", datum);
    }
}

void f_o(FILE *fin){
    char meno[25], priez[25], spz[7], datum[8], dnesdatum[8];
    int typ, cena, odmena = 0;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, &typ, &cena, datum) != EOF){
        if(dnesdatum[0,3]<datum[0,3]){
            if(dnesdatum[0,3] == datum[0,3]-1){
                if(dnesdatum[4,5]<datum[4,5]){
                    
                }
            }
            printf("meno a priezvisko: %s %s\n", meno, priez);
            printf("SPZ: %s\n", spz);
            printf("odmena: %d\n\n", odmena);
        }
    }
}

void f_n(FILE *fin, int **pole, int *pzaznamov){
    char meno[25], priez[25], spz[7], datum[8];
    int typ, cena, j = 0, k, i;
    *pole = (char *) calloc(100, sizeof(char));
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, &typ, &cena, datum) != EOF){
        for(k = 0; k < 7; k++)
            pole[k+j*7] = spz[k];
        j++; //pripocitavam pocet zaznamov pomocou j
    }
    *pzaznamov = j; //priradim si j do pzaznamov
}                   //tu sa mi ta hodnota straca

void f_s(int **pole, int *pzaznamov){
    int i, j, k;
    if(*pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++){
            printf("%c", pole[j+i*7]);
        }
        printf(" ");
        for(j = 2; j < 5; j++){
            printf("%c", pole[j+i*7]);
        }
        printf(" ");
        for(j = 5; j < 7; j++){
            printf("%c", pole[j+i*7]);
        }
        printf("\n");
    }
}

void f_m(int **pole, int *pzaznamov){
    if(*pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    printf("%d", *pzaznamov);
    int i, j, k = 0, pocet = 0, vysledok = 0;
      for (i = 0; i < 14; i++){         //!!!!!!
        for (j = k = 0; j < 14; j++){   //!!!!!!
            if (pole[j] == pole[i])
                k++;
            if (pocet < k){
                pocet = k ;
                vysledok = pole[i];
            }
        }
    }
    printf("%c %d\n", vysledok, k);
}

void f_p(int **pole){
    if(*pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    int i, j, l = 0, h = 6;
    for(i = 1; i <= 2; i++){
        while (h*i > l*i){
            if (pole[l++] != pole[h--]){
                printf("%s is Not Palindrome", pole);
                return;
            }
        }
        printf("%s is palindrome", pole);
    }
}

void f_z(int **pole){
    if(*pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
}

int main(){
    char i;
    int *pole, *pzaznamov, pocet; //definujem si premennu do ktorej chcem ulozit pocet zaznamov
    FILE *fin;
    pzaznamov = &pocet;
    while(scanf("%c", &i) == 1){
        switch(i){
            case 'v':
                fin = fopen("autobazar.txt", "r");
                f_v(fin);
                break;
        
            case 'o':
                fin = fopen("autobazar.txt", "r");
                f_o(fin);
                break;
        
            case 'n':
                fin = fopen("autobazar.txt", "r");
                f_n(fin, pole, &pzaznamov); //zavolam funkciu n
                break;
        
            case 's':
                f_s(pole, &pzaznamov);
                break;
        
            case 'm':
                f_m(pole, &pzaznamov);
                break;
        
            case 'p':
                f_p(pole);
                break;
        
            case 'z':
                f_z(pole);
                break;
        
            case 'k':
                if(fclose(fin) == EOF){
                    printf("Subor sa nepodarilo zatvorit");
                    return 1;
                }
                return 0;
        }
    }
    return 0;
}
