//
//  Projekt 1
//  Matej Hrnciar
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f_v(FILE *fin, char *mp, char *spz, int *typ, int *cena, char *datum){
    char meno[25], priez[25];
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, typ, cena, datum) != EOF){
        printf("meno a priezvisko: %s %s\n", meno, priez);
        printf("SPZ: %s\n", spz);
        printf("typ auta: %d\n", *typ);
        printf("cena: %d\n", *cena);
        printf("datum: %s\n\n", datum);
    }
}

void f_o(FILE *fin, char *mp, char *spz, int *typ, int *cena, char *datum){
    char meno[25], priez[25];
    int odmena = 0;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, typ, cena, datum) != EOF){
        printf("meno a priezvisko: %s %s\n", meno, priez);
        printf("SPZ: %s\n", spz);
        printf("odmena: %d\n\n", odmena);
    }
}

void f_n(FILE *fin, int *pole, int *pzaznamov){
    
    pole = (int *) malloc(100 * sizeof(char));
    char meno[25], priez[25], mp[50], spz[7], datum[8];
    int typ, cena, i = 0;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, &typ, &cena, datum) != EOF){
        while(spz[i] != '\0'){
            pole[i] = spz[i];
            printf("%d %c %c\n", i, spz[i], pole[i]);
            i++;
        }
        pzaznamov++;
    }
}

void f_s(int *pole){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    printf("s");
}

void f_m(int *pole, int *pzaznamov){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    int i, j, k, pocet = 0, vysledok;
    for(i = 0; i < *pzaznamov; i++){
        for(j = k = 0; j < *pzaznamov; j++){
            if(pole[i] == pole[j])
                k++;
            if(pocet < k){
                pocet = k;
                vysledok = pole[i];
            }
        }
    }
    printf("%c %d", vysledok, k);
}

void f_p(int *pole){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
}

void f_z(int *pole){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
}

int main(){
    char mp[50], spz[7], datum[8], i;
    int typ, cena, sotvoreny = 0, *pole, pzaznamov;
    FILE *fin;
    
    while(scanf("%c", &i) == 1){
        switch(i){
            case 'v':
                if((fin = fopen("autobazar.txt", "r")) == NULL){
                    printf("Neotvoreny subor\n");
                    return 1;
                }
                //sotvoreny = 1;
                f_v(fin, mp, spz, &typ, &cena, datum);
                break;
        
            case 'o':
                //if(sotvoreny != 1){
                //    printf("Neotvoreny subor\n");
                //    break;
                //}
                if((fin = fopen("autobazar.txt", "r")) == NULL){
                    printf("Neotvoreny subor\n");
                    return 1;
                }
                f_o(fin, mp, spz, &typ, &cena, datum);
                break;
        
            case 'n':
                if((fin = fopen("autobazar.txt", "r")) == NULL){
                    printf("Neotvoreny subor\n");
                    return 1;
                }
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
                if(fclose(fin) == EOF){
                    printf("Subor sa nepodarilo zatvorit");
                    return 1;
                }
                return 0;
        }
    }
    return 0;
}
