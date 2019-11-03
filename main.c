//
//  main.c
//  Projekt 1
//
//  Created by Matej Hrnciar on 31/10/2019.
//  Copyright © 2019 Matej Hrnciar. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f_v(FILE *fin, char *mp, char *spz, int *typ, int *cena, char *datum){
    char meno[25], priez[25];
    fscanf(fin, "%s %s %s %d %d %s", &meno, &priez, spz, typ, cena, datum);
    printf("v");
}

void f_o(){
    printf("o");
}

void f_n(){
    printf("n");
}

void f_s(){
    printf("s");
}

void f_m(){
    printf("m");
}

void f_p(){
    printf("p");
}

void f_z(){
    printf("z");
}

int main(){
    FILE *fin;
    char *mp[50], *spz[7], *datum[8], i;
    int *typ, *cena;
    
    while(scanf("%c", &i) == 1){
        switch(i){
            case 'v':
                if((fin = fopen("autobazar.txt", "r")) == NULL){
                    printf("Neotvoreny subor\n");
                    return 1;
                }
                f_v(fin, &mp[50], &spz, &typ, &cena, &datum);
                break;
        
            case 'o':
                f_o();
                break;
        
            case 'n':
                f_n();
                break;
        
            case 's':
                f_s();
                break;
        
            case 'm':
                f_m();
                break;
        
            case 'p':
                f_p();
                break;
        
            case 'z':
                f_z();
                break;
        
            case 'k':
                return 0;
        }
    }
    return 0;
}
