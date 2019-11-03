//
//  Projekt 1
//  Matej Hrnciar
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f_v(FILE *fin){
    char meno[50], spz[7], datum[8];
    int typ, cena;
    while(fscanf(fin, "%[a-z A-Z] %s %d %d %s", meno, spz, &typ, &cena, datum) != EOF){
        printf("meno a priezvisko: %s\n", meno);
        printf("SPZ: %s\n", spz);
        printf("typ auta: %d\n", typ);
        printf("cena: %d\n", cena);
        printf("datum: %s\n\n", datum);
    }
}

void f_o(FILE *fin){
    char meno[25], priez[25], mp, spz[7], datum[8];
    int typ, cena, odmena = 0;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, &typ, &cena, datum) != EOF){
        printf("meno a priezvisko: %s %s\n", meno, priez);
        printf("SPZ: %s\n", spz);
        printf("odmena: %d\n\n", odmena);
    }
}

void f_n(FILE *fin, int **pole, int *pzaznamov){
    if(*pole != NULL)
        free(pole);
    *pole = (int *) calloc(100, sizeof(char));
    char meno[25], priez[25], mp, spz[7], datum[8], zoznam[100];
    int typ, cena, i = 0;
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, &typ, &cena, datum) != EOF){
        sprintf(zoznam, "%s", spz); //deli to alebo to dava vsetko na 0?
        i++;
        printf("%s", zoznam);
    }
    *pzaznamov = i;
    char *p = zoznam;
    while(*p != '\0'){ //
        printf ("%c ", *p  );
        p++;
    }
}

void f_s(int **pole){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    int i, j, k;
    for(i = 0; i < strlen(pole); i++){
        printf("%2s %[0-9]s %[A-Z]s", pole);
    }
}

void f_m(int **pole, int *pzaznamov){
    if(*pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    int i, j, k, pocet = 0, vysledok;
      for (i = 0; i < 14; i++){
        for (j = k = 0; j < 14; j++){
            if (pole[j] == pole[i])
                k++;
            if (pocet < k){
                pocet = k ;
                vysledok = pole[i];
            }
        }
    }
    printf("%c %d", vysledok, k);
}

void f_p(int **pole){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    int l = 0;
    int h = strlen(*pole) - 1;
    while (h > l){
        if (pole[l++] != pole[h--]){
            printf("%s is Not Palindrome", *pole);
            return;
        }
    }
}

void f_z(int **pole){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
}

int main(){
    char i;
    int *pole, pzaznamov;
    FILE *fin;
    
    while(scanf("%c", &i) == 1){
        switch(i){
            case 'v':
                fin = fopen("autobazar.txt", "r"); //kontrola spravnosti otvorenia
                f_v(fin);
                break;
        
            case 'o':
                fin = fopen("autobazar.txt", "r"); //odstranit ked prides na to ako citat z f_v
                f_o(fin);
                break;
        
            case 'n':
                fin = fopen("autobazar.txt", "r"); //odstranit ked prides na to ako citat z f_v
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
