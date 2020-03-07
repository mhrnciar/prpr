//
//  Projekt 2
//  Matej Hrnčiar
//  Partnerom tohto projektu je Železničná spoločnosť Slovensko
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct zaznam{
    char kategoria[51];
    char mesto[51];
    char ulica[101];
    int rozloha;
    int cena;
    char popis[201];
    struct zaznam *dalsi;
} ZAZNAM;

ZAZNAM *tvorba_zoznamu(ZAZNAM *p_prvy){
    FILE *fin;
    int pzaznamov = 0, riadok = 0;
    char str[201];
    ZAZNAM *p_akt, *p_novy;
    
    p_prvy = p_akt = p_novy = NULL;
    
    if((fin = fopen("reality.txt", "r")) == NULL){
        printf("Zaznamy neboli nacitane\n");
        return NULL;
    }
    //ak zoznam nie je prazdny, postupne sa uvolnia vsetky prvky a vytvori sa novy zoznam
    if(p_prvy != NULL){
        ZAZNAM *p, *q;
        p = p_prvy;
        
        while(p != NULL){
            q = p;
            p = p->dalsi;
            free(q);
        }
        p_prvy = NULL;
    }
    
    //do str sa kopiruje po riadkoch text v subore a postupne sa riadky
    //priraduju prislusnym prvkom v zozname
    while(fgets(str, 200, fin)){
        
        riadok++;
        
        switch(riadok){
            case 2:
                p_novy = (ZAZNAM *) malloc(sizeof(ZAZNAM));
                strncpy(p_novy->kategoria, str, 50);
                break;
                
            case 3:
                strncpy(p_novy->mesto, str, 50);
                break;
                
            case 4:
                strncpy(p_novy->ulica, str, 100);
                break;
                
            case 5:
                p_novy->rozloha = atoi(str);
                break;
                
            case 6:
                p_novy->cena = atoi(str);
                break;
                
            case 7:
                strncpy(p_novy->popis, str, 200);
                riadok = 0;
                pzaznamov++;
                p_novy->dalsi = NULL;
                
                //ak je zoznam prazdny, prvy prvok sa priradi na jeho miesto
                // ostatne sa postupne pripajaju na koniec predosleho
                if(p_prvy == NULL){
                    p_akt = p_prvy = p_novy;
                    p_akt = p_prvy;
                }
                
                else{
                    p_akt->dalsi = p_novy;
                    p_akt = p_akt->dalsi;
                }
                break;
        }
    }
    //za poslednym prvkom je priradena hodnota NULL
    p_akt->dalsi = NULL;
    
    //pzaznamov pocita kolko zaznamov sa nacitalo, vzdy sa pripocita o jeden, ked
    //sa nacita posledny prvok, teda popis
    printf("Nacitalo sa %d zaznamov\n", pzaznamov);
    fclose(fin);
    
    return p_prvy;
}

void vypis_zoznamu(ZAZNAM *p_prvy){
    if(p_prvy == NULL)
        return;
    
    ZAZNAM *p_akt = p_prvy;
    int czaznamu = 1;
    
    //kym smernik, ktory sa pohybuje po zozname, neukazuje na NULL, teda sa nedostane
    //na koniec zoznamu, vypisuju sa postupne vsetky zaznamy
    //czaznamu sluzi na ocislovanie prvkov
    while(p_akt != NULL){
        printf("%d.\n", czaznamu);
        printf("kategoria ponuky: %s", p_akt->kategoria);
        printf("miesto ponuky: %s", p_akt->mesto);
        printf("ulica: %s", p_akt->ulica);
        printf("rozloha v m2: %d\n", p_akt->rozloha);
        printf("cena: %d\n", p_akt->cena);
        printf("popis: %s", p_akt->popis);
        
        p_akt = p_akt->dalsi;
        czaznamu++;
    }
    
    return;
}

ZAZNAM *vkladanie_zaznamu(ZAZNAM *p_prvy){
    ZAZNAM *p_akt, *p_novy;
    int poradie, i;
    char hodnota[20];
    
    scanf("%d", &poradie);
    
    p_novy = (ZAZNAM *) malloc(sizeof(ZAZNAM));
    
    //aby sa dalo nacitat viac zaznamov naraz, musel som pomocou scanf pred kazdym riadkom
    //ukazat ze nasleduje dalsi prvok
    
    //do ciselnych zaznamov (rozloha a cena) som hodnotu nahral v dvoch krokoch: najprv
    //som si riadok prekopiroval do docasneho retazca hodnota, ktory som potom prekonvertoval
    //na int a ten som priradil do zaznamu
    scanf("\n");
    fgets(p_novy->kategoria, 50, stdin);
    
    scanf("\n");
    fgets(p_novy->mesto, 50, stdin);
    
    scanf("\n");
    fgets(p_novy->ulica, 100, stdin);
    
    scanf("\n");
    fgets(hodnota, 20, stdin);
    p_novy->rozloha = atoi(hodnota);
    
    scanf("\n");
    fgets(hodnota, 20, stdin);
    p_novy->cena = atoi(hodnota);
    
    scanf("\n");
    fgets(p_novy->popis, 200, stdin);
    
    //ak zoznam nie je vytvoreny, nacitany zaznam sa priradi na miesto prveho
    if(p_prvy == NULL){
        p_prvy = p_novy;
        p_prvy->dalsi = NULL;
        return p_prvy;
    }
    
    //ak je vytvoreny a miesto, na ktore sa ma nacitany zaznam ulozit sa rovna 1,
    //vsetky zaznamy sa posunu a novy sa priradi na miesto prveho
    else{
        if(poradie == 1){
            p_novy->dalsi = p_prvy;
            p_prvy = p_novy;
            p_prvy->dalsi = NULL;
            return p_prvy;
        }
        
        //ak ma byt ulozeny na ine miesto ako prve, iterativne sa pomocou p_akt dostanem
        //na zaznam pred nim a vlozim tam novy zaznam
        else{
            p_akt = p_prvy;
            for(i = 1; i < poradie-1; i++){
                p_akt = p_akt->dalsi;
                
                if(p_akt == NULL){
                    p_akt = p_novy;
                    p_akt->dalsi = NULL;
                    return p_prvy;
                }
            }
            
            p_novy->dalsi = p_akt->dalsi;
            p_akt->dalsi = p_novy;
        }
    }
    
    return p_prvy;
}

ZAZNAM *mazanie_zaznamov(ZAZNAM *p_prvy){
    ZAZNAM *p_akt = p_prvy, *p_pred = p_prvy;
    int vymazanych = 0, i = 0;
    char vstup[51], mesto_male[51];
    
    if(p_prvy == NULL)
        return p_prvy;
    
    //nacitam si retazec podla ktoreho sa maju vymazavat zaznamy, ale aby fungoval
    //pri vsetkych pripadoch zmenim si ho na male pismena
    scanf("%s", vstup);
    for(i = 0; vstup[i]; i++)
        vstup[i] = tolower(vstup[i]);
    
    while(p_akt != NULL){
        for(i = 0; mesto_male[i] != '\0'; i++)
            mesto_male[i] = '\0';
        
        //do docasnej premennej mesto_male skopirujem mesto zo zaznamu a tiez ho zmenim
        //na male pismena
        strcpy(mesto_male, p_prvy->mesto);
        for(i = 0; mesto_male[i] != '\0'; i++)
            mesto_male[i] = tolower(mesto_male[i]);
        
        //porovnavam prvy zaznam, ci obsahuje vstup. ak ano, presmeruju sa smerniky
        //aby som nestratil zvysok zoznamu a prvy sa vymaze
        if(strstr(mesto_male, vstup) != NULL){
            p_akt = p_prvy->dalsi;
            free(p_prvy);
            p_prvy = p_pred = p_akt;
            
            vymazanych++;
        }
        
        //ak sa prvy vstup neobsahuje, prechadzam ostatne zaznamy, az kym sa nedostanem
        //na koniec. ak najdem nejaky zaznam, ktory obsahuje vstup, presmerujem smerniky
        //a dany zaznam vymazem
        else{
            for(i = 0; mesto_male[i] != '\0'; i++)
                mesto_male[i] = '\0';
            
            strcpy(mesto_male, p_akt->mesto);
            for(i = 0; mesto_male[i] != '\0'; i++)
                mesto_male[i] = tolower(mesto_male[i]);
            
            if(strstr(mesto_male, vstup) != NULL){
                p_pred->dalsi = p_akt->dalsi;
                free(p_akt);
                p_akt = p_pred;
                
                vymazanych++;
            }
            
            else{
                p_pred = p_akt;
                p_akt = p_akt->dalsi;
            }
        }
    }
    
    //premenna vymazanych pocita kolko zaznamov sa vymazalo
    printf("Vymazalo sa %d zaznamov\n", vymazanych);
    return p_prvy;
}

void hladanie_v_zozname(ZAZNAM *p_prvy){
    ZAZNAM *p_akt = p_prvy;
    int hcena, czaznamu = 1, vypisanych = 0;
    
    if(p_prvy == NULL)
        return;
    
    scanf("%d", &hcena);
    
    //opat sa prechadza cely zoznam a vzdy ked cena zaznamu je nizsia alebo rovna
    //zadanej hodnote, vypise sa cely zaznam
    while(p_akt != NULL){
        if(p_akt->cena <= hcena){
            printf("%d.\n", czaznamu);
            printf("kategoria ponuky: %s", p_akt->kategoria);
            printf("miesto ponuky: %s", p_akt->mesto);
            printf("ulica: %s", p_akt->ulica);
            printf("rozloha v m2: %d\n", p_akt->rozloha);
            printf("cena: %d\n", p_akt->cena);
            printf("popis: %s", p_akt->popis);
            
            p_akt = p_akt->dalsi;
            czaznamu++;
            vypisanych++;
        }
        
        else
            p_akt = p_akt->dalsi;
    }
    
    //ak sa nenajde ziaden zaznam s nizsou alebo rovnou cenou, vypise sa sprava
    if(vypisanych == 0)
        printf("V ponuke su len reality s vyssou cenou\n");
    
    return;
}

void aktualizacia_zoznamu(ZAZNAM *p_prvy){
    ZAZNAM *p_akt = p_prvy;
    int aktualizovanych = 0, i;
    char vstup[51], mesto_male[51], hodnota[20];
    
    if(p_prvy == NULL)
        return;
    
    //nacitam si retazec podla ktoreho sa maju aktualizovat zaznamy, ale aby fungoval
    //pri vsetkych pripadoch zmenim si ho na male pismena
    scanf("%s", vstup);
    for(i = 0; vstup[i]; i++)
        vstup[i] = tolower(vstup[i]);
    
    while(p_akt != NULL){
        //to iste postupne spravim aj s kazdym zaznamom a ak sa v zazname nachadza vstup
        //prepisuje sa prislusny zaznam podla vstupu
        strcpy(mesto_male, p_akt->mesto);
        for(i = 0; mesto_male[i] != '\0'; i++)
            mesto_male[i] = tolower(mesto_male[i]);
        
        if(strstr(mesto_male, vstup) != NULL){
            scanf("\n");
            fgets(p_akt->kategoria, 50, stdin);
            
            scanf("\n");
            fgets(p_akt->mesto, 50, stdin);
            
            scanf("\n");
            fgets(p_akt->ulica, 100, stdin);
            
            scanf("\n");
            fgets(hodnota, 20, stdin);
            p_akt->rozloha = atoi(hodnota);
            
            scanf("\n");
            fgets(hodnota, 20, stdin);
            p_akt->cena = atoi(hodnota);
            
            scanf("\n");
            fgets(p_akt->popis, 200, stdin);
            
            aktualizovanych++;
            for(i = 0; mesto_male[i] != '\0'; i++)
                mesto_male[i] = '\0';
        }
        p_akt = p_akt->dalsi;
    }
    
    //premenna aktualizovanych pocita kolko zaznamov sa aktualizovalo
    printf("Aktualizovalo sa %d zaznamov\n", aktualizovanych);
    return;
}

void usporiadanie_zoznamu(ZAZNAM *p_prvy){
    if(p_prvy == NULL){
        printf("Zoznam nie je mozne usporiadat\n");
        return;
    }
    
    ZAZNAM *p_tmpX, *p_tmpY, *p_tmpXpred, *p_tmpYpred;
    p_tmpXpred = p_tmpX = p_prvy;
    p_tmpYpred = p_tmpY = p_prvy->dalsi;
    
    /*najprv prechadzam prvy zaznam a ak sa najde zaznam ktoreho mesto alebo pripadne
    cena je nizsia, tak sa vymenia. nedochadza vsak k vymene hodnot, ale iba presmerovaniu
    smernikov tak, aby sa prehodil zaznamy v zozname. smernik sa vrati na pociatocnu
    poziciu a pokracuje tak ako predtym, az kym nie je na prvom mieste zaznam s najnizsou
    lexikografickou hodnotou mesta alebo najnizsou cenou*/
    for(p_tmpY = p_prvy->dalsi; p_tmpY != NULL; p_tmpY = p_tmpY->dalsi){
        if(strcmp(p_tmpY->mesto, p_tmpX->mesto) == 0){
            if(p_tmpY->cena < p_tmpX->cena){
                p_tmpYpred->dalsi = p_tmpY->dalsi;
                p_tmpY->dalsi = p_prvy->dalsi;
                p_prvy->dalsi = p_tmpYpred->dalsi;
                p_tmpYpred->dalsi = p_prvy;
                p_prvy = p_tmpY;
                
                p_tmpY = p_prvy->dalsi;
            }
        }
        
        else{
            if(strcmp(p_tmpY->mesto, p_tmpX->mesto) < 0){
                p_tmpYpred->dalsi = p_tmpY->dalsi;
                p_tmpY->dalsi = p_prvy->dalsi;
                p_prvy->dalsi = p_tmpYpred->dalsi;
                p_tmpYpred->dalsi = p_prvy;
                p_prvy = p_tmpY;
                
                p_tmpY = p_prvy->dalsi;
            }
        }
    }
    
    p_tmpYpred = p_tmpY = NULL;
    /*po tom ako zoradim hodnoty podla prveho zaznamu, pokracujem dalsimi az kym nie je
     cely zoznam usporiadany. vzdy ked dojde k vymene zaznamov, smerniky sa vratia na
     povodne pozicie a cyklus zacina odznova. to sice moze predlzit cas vykonavania funkcie,
     ale po vymene treba znova porovnat vymeneny zaznam so vsetkymi ostatnymi ci sa nenajde
     nejaky s lexikograficky nizsim mestom alebo cenou*/
    for(p_tmpX = p_prvy; p_tmpX != NULL; p_tmpX = p_tmpX->dalsi){
        for(p_tmpY = p_tmpX->dalsi; p_tmpY != NULL; p_tmpY = p_tmpY->dalsi){
            if(strcmp(p_tmpY->mesto, p_tmpX->mesto) == 0){
                if(p_tmpY->cena < p_tmpX->cena){
                    p_tmpXpred->dalsi = p_tmpY;
                    p_tmpX->dalsi = p_tmpY->dalsi;
                    p_tmpY->dalsi = p_tmpX;
                    
                    p_tmpX = p_prvy;
                    p_tmpY = p_tmpX->dalsi;
                }
            }
            
            else{
                if(strcmp(p_tmpY->mesto, p_tmpX->mesto) < 0){
                    p_tmpXpred->dalsi = p_tmpY;
                    p_tmpX->dalsi = p_tmpY->dalsi;
                    p_tmpY->dalsi = p_tmpX;
                    
                    p_tmpX = p_prvy;
                    p_tmpY = p_tmpX->dalsi;
                }
            }
        }
        p_tmpXpred = p_tmpX;
    }
    printf("Zaznamy boli usporiadane\n");
    return;
}

int main(){
    char c;
    ZAZNAM *p_prvy = NULL;
    
    //citanie vstupu z klavesnice
    while(scanf("%c", &c) == 1){
        
        switch(c){
               
            case 'n':
                p_prvy = tvorba_zoznamu(p_prvy);
                break;
                
            case 'v':
                vypis_zoznamu(p_prvy);
                break;
                
            case 'p':
                p_prvy = vkladanie_zaznamu(p_prvy);
                break;
        
            case 'z':
                p_prvy = mazanie_zaznamov(p_prvy);
                break;
        
            case 'h':
                hladanie_v_zozname(p_prvy);
                break;
                
            case 'a':
                aktualizacia_zoznamu(p_prvy);
                break;
                
            case 'u':
                usporiadanie_zoznamu(p_prvy);
                break;
        
            case 'k':
                //ak zoznam nie je prazdny, postupne sa uvolnia vsetky prvky a program sa ukonci
                if(p_prvy != NULL){
                    ZAZNAM *p, *q;
                    p = p_prvy;
                    
                    while(p != NULL){
                        q = p;
                        p = p->dalsi;
                        free(q);
                    }
                    p_prvy = NULL;
                }
                return 0;
        }
    }
    return 0;
}
