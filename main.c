//
//  Projekt 1
//  Matej Hrnciar
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *f_v(){
    char str[50];
    int riadok = 0;
    FILE *fin;
    
    if((fin = fopen("autobazar.txt", "r")) == NULL)
        printf("Neotvoreny subor\n");
    
    while(fgets(str, 50, fin) != NULL){
        riadok++;
        
        switch(riadok){
            case 1:
                printf("meno a priezvisko: %s", str);
                break;
                
            case 2:
                printf("SPZ: %s", str);
                break;
                
            case 3:
                printf("typ: %s", str);
                break;
                
            case 4:
                printf("cena: %s", str);
                break;
                
            case 5:
                printf("datum: %s", str);
                break;
                
            case 6:
                printf("\n");
                riadok = 0;
                break;
        }
    }
    return fin;
}

void f_o(FILE *fin){
    char meno[25], priez[25], spz[7], datum[8], dnesdatum[8];
    int typ, cena, odmena = 0, rok, drok, mesiac, dmesiac, den, dden;
    scanf("%s", dnesdatum);
    
    while(fscanf(fin, "%s %s %s %d %d %s", meno, priez, spz, &typ, &cena, datum) != EOF){
        
        
        if(dnesdatum[0,3] > datum[0,3]){
            if(typ == 1)
                odmena = cena;
            if(typ == 0)
                odmena = cena;
        }
        if(dnesdatum[0,3]-1 == datum[0,3]){
            if(dnesdatum[4,5] > datum[4,5]){
                if(typ == 1)
                    odmena = cena;
                if(typ == 0)
                    odmena = cena;
            }
            if(dnesdatum[4,5] == datum[4,5]){
                if(dnesdatum[6,7] > datum[6,7]){
                    if(typ == 1)
                        odmena = cena;
                    if(typ == 0)
                        odmena = cena;
                }
            }
        }
        if(odmena > 0)
            printf("meno a priezvisko: %s %s\n", meno, priez);
            printf("SPZ: %s\n", spz);
            printf("odmena: %d\n\n", odmena);
    }
}

char *f_n(FILE *fin, int *pzaznamov){
    int riadok = 0, j = 0, i = 0;
    char *pole = NULL, spz[50];
    
    rewind(fin);
    
    while(fgets(spz, 50, fin) != NULL){
        
        riadok++;
        
        switch(riadok){
            case 2:
                *pzaznamov = *pzaznamov + 1;
                break;
            case 6:
                riadok = 0;
                break;
        }
    }
    
    if(pole != NULL)
        free(pole);
    
    pole = (char *) malloc(*pzaznamov * sizeof(char));
    
    riadok = 0;
    rewind(fin);
    
    while(fgets(spz, 50, fin) != NULL){
        riadok++;
        
        switch(riadok){
            case 2:
                for(j = 0; j < 7; j++)
                    pole[j+i*7] = spz[j];
                i++;
                break;
            case 6:
                riadok = 0;
                break;
        }
    }
    return pole;
}

void f_s(int *pole, int *pzaznamov){
    int i, j;
    if(*pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    for(i = 0; i < *pzaznamov; i++){
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

void f_m(int *pole, int *pzaznamov){
    if(*pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    printf("%d", *pzaznamov);
    int i, j, k = 0, pocet = 0, vysledok = 0;
      for (i = 0; i < *pzaznamov; i++){         //!!!!!!
        for (j = k = 0; j < 7; j++){   //!!!!!!
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

void f_p(int *pole){
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

void f_z(int *pole){

}

int main(){
    char i, *pole;
    int *pzaznamov;
    FILE *fin;
    while(scanf("%c", &i) == 1){
        switch(i){
            case 'v':
                fin = f_v();
                break;
        
            case 'o':
                f_o(fin);
                break;
        
            case 'n':
                pole = f_n(fin, &pzaznamov);
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
