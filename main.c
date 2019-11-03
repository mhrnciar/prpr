//
//  Projekt 1
//  Matej Hrnciar
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f_v(FILE *fin){
    char meno[25], priez[25], mp[50], spz[7], datum[8];
    int *typ, *cena;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, typ, cena, datum) != EOF){
        printf("meno a priezvisko: %s %s\n", meno, priez);
        printf("SPZ: %s\n", spz);
        printf("typ auta: %d\n", *typ);
        printf("cena: %d\n", *cena);
        printf("datum: %s\n\n", datum);
    }
}

void f_o(FILE *fin, *sotvoreny){
    if(*sotvoreny != 1){
        printf("Neotvoreny subor\n");
        return;
    }
    char meno[25], priez[25], mp[50], spz[7], datum[8];
    int *typ, *cena, odmena = 0;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, typ, cena, datum) != EOF){
        printf("meno a priezvisko: %s %s\n", meno, priez);
        printf("SPZ: %s\n", spz);
        printf("odmena: %d\n\n", odmena);
    }
}

void f_n(FILE *fin, int *pole, int *pzaznamov){
    
    pole = (int *) malloc(100 * sizeof(char));
    char meno[25], priez[25], mp[50], spz[7], datum[8];
    int *typ, *cena;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, typ, cena, datum) != EOF){
        printf("meno a priezvisko: %s %s\n", meno, priez);
        printf("SPZ: %s\n", spz);
        pzaznamov++;
    }
}

void f_s(int *pole){
    if(pole == NULL)
        printf("Pole nie je vytvorene\n");
}

void f_m(int *pole, int *pzaznamov){
    if(pole == NULL)
        printf("Pole nie je vytvorene\n");
    int i, j, k, pocet = 0, vysledok;
    for(i = 0; i < *pzaznamov; i++){
        for(j = k = 0; j < *pzaznamov; j++){
            if( *(pole + i) == *(pole + j))
                k++;
            if(pocet < k){
                pocet = k;
                vysledok = *(pole + i);
            }
        }
    }
    printf("%c %d", vysledok, k);
}

void f_p(int *pole){
    if(pole == NULL)
        printf("Pole nie je vytvorene\n");
}

void f_z(int *pole){
    if(pole == NULL)
        printf("Pole nie je vytvorene\n");
}

int main(){
    FILE *fin;
    char i;
    int sotvoreny = 0, *pole, pzaznamov;
    
    while(scanf("%c", &i) == 1){
        switch(i){
            case 'v':
                if((fin = fopen("autobazar.txt", "r")) == NULL){
                    printf("Neotvoreny subor\n");
                    return 1;
                }
                sotvoreny = 1;
                f_v(fin);
                break;
        
            case 'o':
                f_o(fin, &sotvoreny);
                break;
        
            case 'n':
                f_n(fin, pole, &pzaznamov);
                break;
        
            case 's':
                f_s(pole);
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
                return 0;
        }
    }
    return 0;
}
