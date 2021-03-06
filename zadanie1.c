//
//  Projekt 1
//  Matej Hrnciar
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *vypis_hodnot(){
    char str[50];
    int riadok = 0;
    FILE *fin;
    
    if((fin = fopen("autobazar.txt", "r")) == NULL)
        printf("Neotvoreny subor\n");
    
    while(fgets(str, 50, fin) != NULL){
        
        riadok++;                           //riadky nacitavam po jednom a vzdy pri cisle riadku vypise danu hodnotu
        
        switch(riadok){
            case 1:
                printf("meno priezvisko: %s", str);
                break;
                
            case 2:
                printf("SPZ: %s", str);
                break;
                
            case 3:
                printf("typ auta: %s", str);
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

void odmeny(FILE *fin){
    char meno[50], spz[50], str[50], datum[10] = {0}, ddatum[10] = {0}, temp[10];
    int typ = 0, riadok = 0, i, mesiac, dmesiac, den, dden;
    double cena = 0, odmena = 0;
    
    if(fin == NULL)
        return;
    
    rewind(fin);
    
    scanf("%s", ddatum);
    dmesiac = atoi(strncpy(temp, 4+ddatum, 2));      //nakopirujem si hodnoty mesiaca a dna do docasneho pola ktore premenim na int
    dden = atoi(strncpy(temp, 6+ddatum, 2));
    
    while(fgets(str, 50, fin) != NULL){
        
        riadok++;
        
        switch(riadok){
            case 1:
                strncpy(meno, str, 50);
                for(i = 0; meno[i] != '\0'; i++)        //odstranim \n a \r
                    if(meno[i] == '\n' || meno[i] == '\r')
                        meno[i] = '\0';
                break;
                
            case 2:
                strncpy(spz, str, 50);
                for(i = 0; spz[i] != '\0'; i++)
                    if(spz[i] == '\n' || spz[i] == '\r')
                        spz[i] = '\0';
                break;
                
            case 3:
                typ = atoi(str);
                break;
                
            case 4:
                cena = atof(str);
                break;
                
            case 5:
                for(i = 0; i < 8; i++)
                    datum[i] = str[i];
                mesiac = atoi(strncpy(temp, 4+datum, 2));
                den = atoi(strncpy(temp, 6+datum, 2));
                
                if(strncmp(datum, ddatum, 4) < 0){      //porovnavanie dnesneho datumu a datumu kedy zamestanec zacal pracovat
                    if(mesiac < dmesiac){
                        odmena = (typ == 1) ? cena * 0.023 : cena * 0.051;
                    }
                    if(mesiac == dmesiac){
                        if(den < dden)
                            odmena = (typ == 1) ? cena * 0.023 : cena * 0.051;
                    }
                }
                break;
                
            case 6:
                riadok = 0;
                break;
        }
        if(odmena > 0){                                 //ak odmena nie je nulova, vypise to meno, spz a odmenu pre zamestnanca
            printf("%s %s %.2lf\n", meno, spz, odmena);
            odmena = 0;
            for(i = 0; i < 8; i++)                      //nulovanie hodnot
                datum[i] = 0;
        }
    }
}

char *tvorba_pola(FILE *fin, int *pzaznamov){
    int riadok = 0, j = 0, i = 0;
    char *pole = NULL, str[50];
    
    if(fin == NULL)
        return NULL;
    
    rewind(fin);
    
    while(fgets(str, 50, fin) != NULL){                //nacitanie poctu zaznamov
        
        riadok++;
        
        switch(riadok){
                
            case 6:
                *pzaznamov = *pzaznamov + 1;
                riadok = 0;
                break;
        }
    }
    
    if(pole != NULL)                                    //kontrola ci pole nie je uz vytvorene
        free(pole);
    
    pole = (char *) malloc(*pzaznamov * sizeof(char));  //alokacia pola
    
    riadok = 0;
    rewind(fin);
    
    while(fgets(str, 50, fin) != NULL){
        riadok++;
        
        switch(riadok){                                 //nacitavanie spz do pola
            case 2:
                for(j = 0; j < 7; j++)
                    *(pole+(j+i*7)) = str[j];
                i++;
                break;
                
            case 6:
                riadok = 0;
                break;
        }
    }
    return pole;
}

void vypis_spz(char *pole, int *pzaznamov){
    int i, j;
    
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    
    for(i = 0; i < *pzaznamov; i++){                     //vypisovanie spz v tvare AA BBB CC
        
        for(j = 0; j < 2; j++){
            printf("%c", *(pole+(j+i*7)));
        }
        printf(" ");
        
        for(j = 2; j < 5; j++){
            printf("%c", *(pole+(j+i*7)));
        }
        printf(" ");
        
        for(j = 5; j < 7; j++){
            printf("%c", *(pole+(j+i*7)));
        }
        printf("\n");
    }
}

void najcastejsi_znak(char *pole, int *pzaznamov){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    
    int i, j, max = 1, index[*pzaznamov*7];
    
    for(i = 0; i < *pzaznamov*7; i++){  //pole index sleduje hodnoty znakov, ak sa najdu dve zhodne tak zvysi hodnotu na
        index[i] = 1;                   //prislusnom mieste o 1
        for(j = i+1; j < *pzaznamov*7; j++){
            if(*(pole+i) == *(pole+j))
                index[i]++;
                
            if(index[i] > max)          //pocet vyskytov najcastejsieho znaku
                max = index[i];
        }
    }
    for(i = 0; i < *pzaznamov*7; i++)
        if(index[i] == max)
            printf("%c %d\n", *(pole+i), max);
}

void vypis_palindromov(char *pole, int *pzaznamov){
    if(pole == NULL){
        printf("Pole nie je vytvorene\n");
        return;
    }
    
    int i, j, l, h, vysledok;
    char arr[7];
    
    for(i = 0; i < *pzaznamov; i++){
        for(j = 0; j < 7; j++)
            arr[j] = *(pole+(j+i*7));   //nahravanie samostatnej spz do docasneho pola
        vysledok = 1;
        l = 0;
        h = 6;
        while(l <= h && vysledok){      //porovnavanie docasneho pola s povodnym ci maju rovnake hodnoty aj zpredu aj zozadu
            if(arr[l++] != arr[h--])
                vysledok = 0;
        }
        if(vysledok)
            printf("%c%c\n", arr[0], arr[1]);
    }
}

void najcastejsi_okres(char *pole, int *pzaznamov){
    if(pole == NULL)
        return;
    
    int i, j, max = 1, index[*pzaznamov];
    char arr[*pzaznamov][2];
    
    for(i = 0; i < *pzaznamov; i++){    //inicializacia dvojrozmerneho pola v ktorom su iba okresy z spz
        for(j = 0; j < 2; j++)
            arr[i][j] = *(pole+(j+i*7));
    }
    
    for(i = 0; i < *pzaznamov; i++){    //pole index sleduje hodnoty okresov, ak sa najdu dve zhodne tak zvysi hodnotu na
        index[i] = 1;                   //prislusnom mieste o 1
        for(j = i+1; j < *pzaznamov; j++){
            if(arr[i][0] == arr[j][0] && arr[i][1] == arr[j][1])
                index[i]++;
            
            if(index[i] > max)          //pocet vyskytov najcastejsieho okresu
                max = index[i];
        }
    }
    for(i = 0; i < *pzaznamov; i++)
        if(index[i] == max)
            printf("%c%c %d\n", arr[i][0], arr[i][1], max);
    }

char *mazanie_SPZ(char *pole, int *pzaznamov){
    int i, j, k = 0, pocet = 0;
    char str[*pzaznamov*7], znak;
    
    scanf("%s", &znak);
    
    for(i = 0; i < *pzaznamov; i++){
        if(pole[i*7] != znak){
            pocet++;
            
            for (j = 0; j < 7; j++) {
                str[j+k*7] = pole[j+i*7];
            }
            k++;
        }
    }
    
    if(pocet == *pzaznamov){
        printf("Zhoda nebola zistena\n");
        return pole;
    }
        
    free(pole);
    
    pole = (char *) malloc(pocet * sizeof(char));
    
    for(i = 0; i < pocet*7; i++)
        pole[i] = str[i];
    
    *pzaznamov = pocet;
    return pole;
}

void histogram_doplnkov(char *pole, int *pzaznamov){
    int i, j, k = 0, pocet = 0;
    char arr[*pzaznamov*2], hist[26];
    
    for(i = 0; i < 26; i++)
        hist[i] = 'A'+i;
    
    for(i = 0; i < *pzaznamov; i++){
        for(j = 5; j < 7; j++){
            
            arr[k+i*2] = pole[j+i*7];
            k++;
        }
        k = 0;
    }
    for(i = 0; i < 26; i++){
        for(j = 0; j < *pzaznamov*2; j++){
            if(hist[i] == arr[j]){
                pocet++;
                k++;
            }
        }
        
        if(pocet > 0){
            printf("%c:%d", hist[i], pocet);
            printf("\n");
        }
        pocet = 0;
    }
}

int main(){
    char i, *pole = NULL;
    int pzaznamov = 0;
    FILE *fin = NULL;
    
    while(scanf("%c", &i) == 1){    //citanie vstupu z klavesnice
        
        switch(i){
                
            case 'v':
                fin = vypis_hodnot();
                break;
        
            case 'o':
                odmeny(fin);
                break;
        
            case 'n':
                pole = tvorba_pola(fin, &pzaznamov);
                break;
        
            case 's':
                vypis_spz(pole, &pzaznamov);
                break;
        
            case 'm':
                najcastejsi_znak(pole, &pzaznamov);
                break;
        
            case 'p':
                vypis_palindromov(pole, &pzaznamov);
                break;
        
            case 'z':
                najcastejsi_okres(pole, &pzaznamov);
                break;
                
            case 'x':
                pole = mazanie_SPZ(pole, &pzaznamov);
                break;
                
            case 'h':
                histogram_doplnkov(pole, &pzaznamov);
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
