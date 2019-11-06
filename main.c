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
    int typ, cena, j, riadok = 0, odmena = 0, rok, drok, mesiac, dmesiac, den, dden;
    scanf("%s", dnesdatum);
    
    while(fgets(spz, 50, fin) != NULL){
        riadok++;
        
        switch(riadok){
            case 5:
                for(j = 0; j < 8; j++)
                    datum[j] = spz[j];
                if(dnesdatum[0,3] > datum[0,3]){
                    if(typ == 1)
                        odmena = cena*0.023;
                    if(typ == 0)
                        odmena = cena*0.051;
                }
                if(dnesdatum[0,3]-1 == datum[0,3]){
                    if(dnesdatum[4,5] > datum[4,5]){
                        if(typ == 1)
                            odmena = cena*0.023;
                        if(typ == 0)
                            odmena = cena*0.051;
                    }
                    if(dnesdatum[4,5] == datum[4,5]){
                        if(dnesdatum[6,7] > datum[6,7]){
                            if(typ == 1)
                                odmena = cena*0.023;
                            if(typ == 0)
                                odmena = cena*0.051;
                        }
                    }
                }
                if(odmena > 0){
                    printf("meno a priezvisko: %s %s\n", meno, priez);
                    printf("SPZ: %s\n", spz);
                    printf("odmena: %d\n\n", odmena);
                }
                break;
            case 6:
                riadok = 0;
                break;
        }
    }
}

char *f_n(FILE *fin, int *pzaznamov){
    int riadok = 0, j = 0, i = 0;
    char *pole = NULL, str[50];
    
    if(fin == NULL)
        return NULL;
    
    rewind(fin);
    
    while(fgets(str, 50, fin) != NULL){
        
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
    
    while(fgets(str, 50, fin) != NULL){
        riadok++;
        
        switch(riadok){
            case 2:
                for(j = 0; j < 7; j++)
                    pole[j+i*7] = str[j];
                i++;
                break;
            case 6:
                riadok = 0;
                break;
        }
    }
    return pole;
}

void f_s(char *pole, int *pzaznamov){
    int i, j;
    if(pole == NULL){
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

void f_m(char *pole, int *pzaznamov){
    int i, j, k = 0, pocet = 0, vysledok = 0;
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
      for (i = 0; i < *pzaznamov*7; i++){         //!!!!!!
        for (j = k = 0; j < *pzaznamov*7; j++){   //!!!!!!
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

void f_p(char *pole){
    int i, l = 0, h = 6;
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
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

void f_z(char *pole){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
}

int main(){
    char i, *pole = NULL;
    int pzaznamov;
    FILE *fin = NULL;
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
                f_m(pole, &pzaznamov); //nenacitava spravne pole
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
