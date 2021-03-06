#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "cmake-build-debug/variables.h"
#include <time.h>


typedef struct central_store{
    int jedlo;
    int pivo;
    int ruda;
    int mince;
    int vodka;
    int palenka;
}store;

typedef struct my_player{
    int ID;
    char name[20];
    int lives;
    int hunger;
    int energy;
    int power;
    int stamina;
    int defence;
}player;

typedef struct wolf{
    int sila;
    int defence;
    int stamina;
}WOLF;

int menu(int *volba_hl_menu){
    printf("MENU:\n\t1.\tNova hra\n\t2.\tNacitat hru\n\t3.\tUlozit hru\n\t4.\tVypis hracov\n\t5.\tSprav akciu\n\t6."
                   "\tCommandPromt\n\t7.\tQuit\n");
    scanf("%d",&*volba_hl_menu);
}

void LoadFromFileDefault(FILE* fdefault, player myplayer[],int nacitany_pocet_hracov){

    char buffer[1000];


    for (int i = 0; i <nacitany_pocet_hracov; ++i) {
        fgets(buffer, 1000, fdefault);
        //puts(buffer);
        parse_file(buffer, myplayer);
        myplayer++;
    }
}

void parse_file(char *line,player myplayer[]){
    //vyuzivame strchr - najde najblizsi vyskyt znaku v retazci
    char* next = strchr(line, ',');

    next[0] = '\0';
    next++;

    myplayer->ID=atoi(line);
    line = next;

    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    strcpy(myplayer->name, line);
    line = next;
    next = strchr(line, ',');

    next[0] = '\0';
    next++;

    myplayer->lives=atoi(line);
    line = next;
    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    myplayer->hunger=atoi(line);
    line = next;
    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    myplayer->energy=atoi(line);
    line = next;
    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    myplayer->power=atoi(line);
    line = next;
    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    myplayer->stamina=atoi(line);
    line = next;

    myplayer->defence=atoi(line);
    line = next;
}

int nacitaj_saved_sklad(store sklad[]){

    int nacitany_pocet_hracov;
    FILE *fsklad;
    fsklad=fopen("/home/mysiak/CLionProjects/CV11/HRAg2_update/saveMYstore.txt","r");
    if (fsklad==NULL){
        printf("Subor s defaultnym nastavenim store sa nepodarilo otvorit");
        return NULL;
    }
    nacitany_pocet_hracov=numOFrows(fsklad);
    rewind(fsklad);
    LoadFromFileSavedSklad(fsklad,sklad,nacitany_pocet_hracov);

    printf("nacital som %d\n",nacitany_pocet_hracov);
    for (int i = 0; i <nacitany_pocet_hracov; ++i) {
        printf("%d ",sklad[i].jedlo);
        printf("%d ",sklad[i].pivo);
        printf("%d ",sklad[i].ruda);
        printf("%d ",sklad[i].mince);
        printf("%d ",sklad[i].vodka);
        printf("%d\n",sklad[i].palenka);
    }
    fflush(fsklad);
    fclose(fsklad);
}

int nacitaj_default_config(int nacitany_pocet_hracov,player myplayer[]){


    FILE *fdefault;
    fdefault=fopen("/home/mysiak/CLionProjects/CV11/HRAg2_update/default.txt","r");
    if (fdefault==NULL){
        printf("Subor s defaultnym nastavenim sa nepodarilo otvorit");
        return NULL;
    }
    rewind(fdefault);
    LoadFromFileDefault(fdefault,myplayer,nacitany_pocet_hracov);
    printf("nacital som %d\n",nacitany_pocet_hracov);
    for (int i = 0; i <nacitany_pocet_hracov; ++i) {
        printf("%d ",myplayer[i].ID);
        printf("%s ",myplayer[i].name);
        printf("%d ",myplayer[i].lives);
        printf("%d ",myplayer[i].hunger);
        printf("%d ",myplayer[i].energy);
        printf("%d ",myplayer[i].power);
        printf("%d ",myplayer[i].stamina);
        printf("%d \n",myplayer[i].defence);
    }
    fflush(fdefault);
    fclose(fdefault);
}

int nacitaj_default_sklad(int nacitany_pocet_hracov,store sklad[]){

    FILE *fstore;
    fstore=fopen("/home/mysiak/CLionProjects/CV11/HRAg2_update/defaultstore.txt","r");
    if (fstore==NULL){
        printf("Subor s defaultnym nastavenim store sa nepodarilo otvorit");
        return NULL;
    }
    rewind(fstore);
    LoadFromFileDefaultSklad(fstore,sklad,nacitany_pocet_hracov);
    printf("nacital som %d\n",nacitany_pocet_hracov);
    for (int i = 0; i <nacitany_pocet_hracov; ++i) {
        printf("%d ",sklad[i].jedlo);
        printf("%d ",sklad[i].pivo);
        printf("%d ",sklad[i].ruda);
        printf("%d ",sklad[i].mince);
        printf("%d ",sklad[i].vodka);
        printf("%d\n",sklad[i].palenka);
    }
    fflush(fstore);
    fclose(fstore);
}

void nacitajvlastnuhru(player myplayer[],int *nacitanyhraci){

    int nacitany_pocet_hracov;
    char *text = calloc(1, 1), buffer[BUFFERSIZE];

    printf("\nZadaj nazov suboru:\t");
    printf("\nZadajte meno suboru:\t");
    getchar();
    fgets(buffer, BUFFERSIZE, stdin);
    text = realloc(text, strlen(text) + 1 + strlen(buffer));
    if (!text)
        strcat(text, buffer);
    printf("Zadal si meno suboru %s\n", buffer);

    FILE *loadedfile;
    loadedfile=fopen(buffer,"r");
    if (loadedfile==NULL){
        printf("Subor s defaultnym nastavenim sa nepodarilo otvorit");
    }
    nacitany_pocet_hracov=numOFrows(loadedfile);
    *nacitanyhraci=nacitany_pocet_hracov;
    rewind(loadedfile);
    //myplayer=calloc(nacitany_pocet_hracov+1, sizeof(player));
    LoadFromFileDefault(loadedfile,myplayer,nacitany_pocet_hracov);
    printf("nacital som %d\n",nacitany_pocet_hracov);

    for (int i = 0; i <nacitany_pocet_hracov; ++i) {
        printf("%d ",myplayer[i].ID);
        printf("%s ",myplayer[i].name);
        printf("%d ",myplayer[i].lives);
        printf("%d ",myplayer[i].hunger);
        printf("%d ",myplayer[i].energy);
        printf("%d ",myplayer[i].power);
        printf("%d ",myplayer[i].stamina);
        printf("%d \n",myplayer[i].defence);
    }

    fflush(loadedfile);
    fclose(loadedfile);

}

void nacitajvlastnehohraca(int *vlastnyhrac){

    int buffer;
    FILE *fhrac;
    fhrac=fopen("/home/mysiak/CLionProjects/CV11/HRAg2_update/saveMYgamer.txt","r");
    if (fhrac==NULL){
        printf("Subor s defaultnym nastavenim hraca sa nepodarilo otvorit");
    }
    rewind(fhrac);

    fscanf (fhrac, "%d", &buffer);
    printf ("%d ", buffer);
    *vlastnyhrac=buffer;

    fflush(fhrac);
    fclose(fhrac);

}

void parse_file_sklad(char *line,store sklad[]){
    //vyuzivame strchr - najde najblizsi vyskyt znaku v retazci
    char* next = strchr(line, ',');

    next[0] = '\0';
    next++;

    sklad->jedlo=atoi(line);
    line = next;

    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    sklad->pivo=atoi(line);
    line = next;
    next = strchr(line, ',');

    next[0] = '\0';
    next++;

    sklad->ruda=atoi(line);
    line = next;
    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    sklad->mince=atoi(line);
    line = next;
    next = strchr(line, ',');
    next[0] = '\0';
    next++;

    sklad->vodka=atoi(line);
    line = next;

    sklad->palenka=atoi(line);
    line = next;
}

void LoadFromFileDefaultSklad(FILE* fdefault, store sklad[],int nacitany_pocet_hracov){

    char buffer[1000];

    for (int i = 0; i <nacitany_pocet_hracov; ++i) {
        fgets(buffer, 1000, fdefault);
        //puts(buffer);
        parse_file_sklad(buffer, sklad);
        sklad++;
    }
}

void LoadFromFileSavedSklad(FILE* fsklad,store sklad[],int nacitany_pocet_hracov){

    char buffer[1000];

    for (int i = 0; i <nacitany_pocet_hracov; ++i) {
        fgets(buffer, 1000, fsklad);
        //puts(buffer);
        parse_file_sklad(buffer, sklad);
        sklad++;
    }
}

void savegame(player myplayer[], int pocet_hracov_nova_hra) {

    char *text = calloc(1, 1), buffer[BUFFERSIZE];
    printf("\nZadajte meno suboru:\t");
    getchar();
    fgets(buffer, BUFFERSIZE, stdin);
    text = realloc(text, strlen(text) + 1 + strlen(buffer));
    if (!text)
       strcat(text, buffer);
    printf("Zadal si meno suboru %s\n", buffer);

    FILE *SaveGame=fopen(buffer,"w");

    for (int i = 0; i <pocet_hracov_nova_hra; ++i) {
        fprintf(SaveGame,"%d,%s,%d,%d,%d,%d,%d,%d\n",myplayer[i].ID,myplayer[i].name,myplayer[i].lives,myplayer[i].hunger,
                myplayer[i].energy,myplayer[i].power,myplayer[i].stamina,myplayer[i].defence);
    }

    fflush(SaveGame);
    fclose(SaveGame);


}

void savegamesklad(store sklad[],int pocet_hracov_nova_hra){

    FILE *SaveGame;
    SaveGame=fopen("/home/mysiak/CLionProjects/CV11/HRAg2_update/saveMYstore.txt","w");
    if (SaveGame==NULL){
        printf("Subor s defaultnym nastavenim sa nepodarilo otvorit");
    }
    for (int i = 0; i <pocet_hracov_nova_hra; ++i) {
        fprintf(SaveGame,"%d,%d,%d,%d,%d,%d\n",sklad[i].jedlo,sklad[i].pivo,sklad[i].ruda,sklad[i].mince,
                sklad[i].vodka,sklad[i].palenka);
    }

    fflush(SaveGame);
    fclose(SaveGame);
}

void savegameconfighrac(int ktorehohracachcem){
    FILE *SaveGame;
    SaveGame=fopen("/home/mysiak/CLionProjects/CV11/HRAg2_update/saveMYgamer.txt","w");
    if (SaveGame==NULL){
        printf("Subor s defaultnym nastavenim sa nepodarilo otvorit");
    } else{
    fprintf(SaveGame,"%d\n",ktorehohracachcem);
    }

    fflush(SaveGame);
    fclose(SaveGame);
}

int numOFrows(FILE *loadedfile){
    char c;
    int count = 0;

    for (c = getc(loadedfile); c != EOF; c = getc(loadedfile))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    printf("count=%d",count);
    return count;
}

void vypishracov(player myplayer[],int pocet_hracov_nova_hra, int chcem_tohto_hraca){
    printf("\nToto su vsetci hraci\n");
    for (int i = 0; i <pocet_hracov_nova_hra; ++i) {
        printf("%d ",myplayer[i].ID);
        printf("%s ",myplayer[i].name);
        printf("%d ",myplayer[i].lives);
        printf("%d ",myplayer[i].hunger);
        printf("%d ",myplayer[i].energy);
        printf("%d ",myplayer[i].power);
        printf("%d ",myplayer[i].stamina);
        printf("%d \n",myplayer[i].defence);
    }

    printf("\nToto je tvoj hrac\n");
    printf("%d ",myplayer[chcem_tohto_hraca].ID);
    printf("%s ",myplayer[chcem_tohto_hraca].name);
    printf("%d ",myplayer[chcem_tohto_hraca].lives);
    printf("%d ",myplayer[chcem_tohto_hraca].hunger);
    printf("%d ",myplayer[chcem_tohto_hraca].energy);
    printf("%d ",myplayer[chcem_tohto_hraca].power);
    printf("%d ",myplayer[chcem_tohto_hraca].stamina);
    printf("%d \n",myplayer[chcem_tohto_hraca].defence);

}

void vypisskladu(store sklad[], int pocet_hracov_nova_hra, int chcem_tohto_hraca){
    printf("\nToto su sklady vsetkych hracov\n");
    for (int i = 0; i <pocet_hracov_nova_hra; ++i) {
        printf("%d ",sklad[i].jedlo);
        printf("%d ",sklad[i].pivo);
        printf("%d ",sklad[i].ruda);
        printf("%d ",sklad[i].mince);
        printf("%d ",sklad[i].vodka);
        printf("%d\n",sklad[i].palenka);
    }

    printf("\nToto su suroviny mojho hraca\n");
    printf("%d ",sklad[chcem_tohto_hraca].jedlo);
    printf("%d ",sklad[chcem_tohto_hraca].pivo);
    printf("%d ",sklad[chcem_tohto_hraca].ruda);
    printf("%d ",sklad[chcem_tohto_hraca].mince);
    printf("%d ",sklad[chcem_tohto_hraca].vodka);
    printf("%d\n",sklad[chcem_tohto_hraca].palenka);
}

void mining(player myplayer[],store sklad[],int chcem_vlastneho_hraca){
    printf("\nIdeme kopat\n");
    if (myplayer[chcem_vlastneho_hraca].energy>5&&myplayer[chcem_vlastneho_hraca].hunger<95) {
        if (myplayer[chcem_vlastneho_hraca].hunger > 20 && myplayer[chcem_vlastneho_hraca].energy > 20) {
            myplayer[chcem_vlastneho_hraca].hunger += 5;
            myplayer[chcem_vlastneho_hraca].energy -= 5;
            sklad[chcem_vlastneho_hraca].ruda += 10;
            printf("\nNaskrabal si 10ks rudy;");
        } else {
            myplayer[chcem_vlastneho_hraca].hunger += 5;
            myplayer[chcem_vlastneho_hraca].energy -= 5;
            sklad[chcem_vlastneho_hraca].ruda += 5;
            printf("\nNaskrabal si 5ks rudy\n");
        }
    } else printf("\nNemas dostatok energie alebo si prilis hladny na to aby si tazil\nskus to ked naberies znovu silu\n");
}

void fight(player myplayer[],WOLF thewolf[],int chcem_vlastneho_hraca){
    int randomcislo=rand()%5+1;
    printf("\nIdeme bojovat s vlkmi\n");
    if (myplayer[chcem_vlastneho_hraca].energy<10&&myplayer[chcem_vlastneho_hraca].lives<1){
        printf("\nNiesi schopny bojovat\nskus to inokedy\n");
    } else {
        if (myplayer[chcem_vlastneho_hraca].power>thewolf[randomcislo].sila&&myplayer[chcem_vlastneho_hraca].defence>
                thewolf[randomcislo].defence){
            printf("\nZvitazil si nad vlkom\n");
            myplayer[chcem_vlastneho_hraca].power+=5;
            myplayer[chcem_vlastneho_hraca].defence+=5;
            myplayer[chcem_vlastneho_hraca].stamina+=5;
            myplayer[chcem_vlastneho_hraca].lives+=1;
            myplayer[chcem_vlastneho_hraca].energy-=5;
            myplayer[chcem_vlastneho_hraca].hunger-=5;
        } else{
            printf("\nVlk ta porazil\n");
            myplayer[chcem_vlastneho_hraca].power-=5;
            myplayer[chcem_vlastneho_hraca].defence-=5;
            myplayer[chcem_vlastneho_hraca].stamina+=5;
            myplayer[chcem_vlastneho_hraca].lives-=1;
            myplayer[chcem_vlastneho_hraca].energy-=5;
            myplayer[chcem_vlastneho_hraca].hunger-=5;
        }
    }
}

void remeselnik(player myplayer[],store sklad[],int chcem_vlastneho_hraca){
    printf("\nPustil si sa do remesla\n");
    printf("\nZo skladu ti ubudne ruda a premeni sa na mince\n");
    if(myplayer[chcem_vlastneho_hraca].hunger>95||myplayer[chcem_vlastneho_hraca].energy<5){
        printf("\nKoli nedostatku energie a hladu niesi schopny pracovat\n");
        printf("HINT:chod sa posilnit do krcmy\n");
    } else{
        if(sklad[chcem_vlastneho_hraca].ruda<10){
            printf("!!NEMAS DOSTATOK RUDY!!\n");
            printf("HINT: na pracovanie s rudov potrebujes aspon 10ks rudy a ty mas len %d\n",sklad[chcem_vlastneho_hraca].ruda);
        }else{
            sklad[chcem_vlastneho_hraca].ruda-=10;
            sklad[chcem_vlastneho_hraca].mince+=20;
            myplayer[chcem_vlastneho_hraca].energy-=5;
            myplayer[chcem_vlastneho_hraca].hunger-=5;
            myplayer[chcem_vlastneho_hraca].lives+=1;
            printf("Vyrobil si nieco z rudy\n");
            if(sklad[chcem_vlastneho_hraca].pivo<10||sklad[chcem_vlastneho_hraca].palenka<10){
                printf("Za to ze si sikovny ti remeselnik daroval pivo a palenku\n");
                sklad[chcem_vlastneho_hraca].pivo+=10;
                sklad[chcem_vlastneho_hraca].palenka+=10;
                sklad[chcem_vlastneho_hraca].mince-=5;
            }
        }
    }
}

void pivovarnik(player myplayer[],store sklad[],int chcem_vlastne_hraca){
    printf("\nKonecne nejaka poriadna praca\nPodme teda varit pivko\n");
    if (sklad[chcem_vlastne_hraca].pivo<10||sklad[chcem_vlastne_hraca].palenka<10){
        printf("\nNemas dostatok surovin na vyrobu a pripravu piva\n");
        printf("\nHINT: Zastav sa u remeselnika mozno ti pomoze\n");
    } else{
        printf("Vyrobil si si nejake pivo\n");
        myplayer[chcem_vlastne_hraca].lives+=10;
        myplayer[chcem_vlastne_hraca].hunger+=20;
        myplayer[chcem_vlastne_hraca].energy+=20;
        myplayer[chcem_vlastne_hraca].power+=5;
        sklad[chcem_vlastne_hraca].palenka-=10;
        sklad[chcem_vlastne_hraca].pivo-=10;
    }
}

void oddych(player myplayer[],int chcem_vlastneho_hraca){
    int doplnenie;
    printf("\nPrisiel cas na to aby si si oddychol\n");
    printf("Oddych ti dobije zopar funkcii aby si mohol dalej hrat\n");
    doplnenie=myplayer[chcem_vlastneho_hraca].energy;
    if (doplnenie>100){
        printf("nieje ti treba doplnit energiu\n");
    } else {
        doplnenie = 100 - doplnenie;
        myplayer[chcem_vlastneho_hraca].energy+=doplnenie;
        printf("doplniko sa ti %d energie\n",doplnenie);
     }
    doplnenie=myplayer[chcem_vlastneho_hraca].lives;
    if (doplnenie>100){
        printf("nieje ti treba doplnit zivoty\n");
    } else {
        doplnenie = 100 - doplnenie;
        myplayer[chcem_vlastneho_hraca].lives+=doplnenie;
        printf("doplniko sa ti %d zivotov\n",doplnenie);
    }
}

void gameOFtrons(player myplayer[],store sklad[],WOLF thewolf[],int pocet_hracov_nova_hra, int chcem_vlastneho_hraca){
    int volba;
    int idemdalej=1;
    printf("\nVitaj\nvyber si z ponuky co by si chcel spravit\n\t");
    while (idemdalej) {
        printf("\t1.\tMining\n\t2.\tBoj s pseudovlkmi\n\t3.\tRemeselnik\n\t4.\tPivovarnik\n\t5.\tOddych\n\t6.\tBack to menu");
        scanf("%d", &volba);

        switch (volba) {
            case 1:
                mining(myplayer,sklad,chcem_vlastneho_hraca);
                break;
            case 2:
                fight(myplayer,thewolf,chcem_vlastneho_hraca);
                break;
            case 3:
                remeselnik(myplayer,sklad,chcem_vlastneho_hraca);
                break;
            case 4:
                pivovarnik(myplayer,sklad,chcem_vlastneho_hraca);
                break;
            case 5:
                oddych(myplayer,chcem_vlastneho_hraca);
                break;
            case 6:
                idemdalej=0;
                break;
        }
    }


}

void generujvlka(WOLF thewolf[]){
    int silaGEN;
    int defenceGEN;
    int staminaGEN;

    for (int i = 0; i <5; ++i) {
        silaGEN=rand()%100+1;
        defenceGEN=rand()%100+1;
        staminaGEN=rand()%100+1;
        thewolf[i].sila=silaGEN;
        thewolf[i].defence=defenceGEN;
        thewolf[i].stamina=staminaGEN;
    }
}

void commandpromt(player myplayer[],store sklad[],WOLF thewolf[],int pocet_hracov_nova_hra, int chcem_tohto_hraca){

    char com[6];
    char par[10];
    int komandy=1;
    int priradenie=0;
    com[0]='\0';
    par[0]='\0';
    char *text = calloc(1, 1), buffer[BUFFERSIZE];
    printf("\nprikazy:\n\tprint\n\takcia\n\tload\n\tsave\n\tquit\n");
    printf("\nZadaj prikaz a potvrd enterom\t");
    while(komandy) {
        getchar();
        fgets(buffer, BUFFERSIZE, stdin);
        text = realloc(text, strlen(text) + 1 + strlen(buffer));
        if (!text)
            strcat(text, buffer);
        sscanf(buffer, "%s %s", com, par);
        if (strcmp(com, "print")==0) {
            priradenie = 1;
        } else if (strcmp(com, "akcia")==0) {
            priradenie = 2;
        } else if (strcmp(com, "load")==0) {
            priradenie = 3;
        } else if (strcmp(com, "save")==0) {
            priradenie = 4;
        } else if (strcmp(com, "quit")==0) {
            priradenie = 5;
        }else printf("zadal si zly prikaz\n");


        switch (priradenie) {
            case 1:
                printf("1 %s\n",par);
                break;
            case 2:
                printf("2\n");
                break;
            case 3:
                printf("3\n");
                break;
            case 4:
                printf("4\n");
                break;
            case 5:
                komandy=0;
                break;
        }
    }
}

int main() {

    srand(time(NULL));
    store *sklad;
    player *myplayer;
    WOLF *thewolf;

    int volba_hl_menu;
    int pocet_hracov_nova_hra = 0;
    int chcemhrat = 1;
    int chcem_tohto_hraca;
    int newgame=0;
    int prvykrat=0;
    uvod();

    while (chcemhrat) {
        menu(&volba_hl_menu);
        if (volba_hl_menu > 7) {
            printf("Zadal si zlu polozku skus este raz:\n");
            menu(&volba_hl_menu);
        } else {
            switch (volba_hl_menu) {
                case 1:     //nova hra
                    prvykrat=1;
                    printf("zadaj kolko hracov chces nacitat v rozmedzi od 1 po 10\n");
                    scanf("%d", &pocet_hracov_nova_hra);
                    if (pocet_hracov_nova_hra < 1 && pocet_hracov_nova_hra > 10) {
                        printf("zadal si zly pocet hracov skus este raz\n");
                        printf("zadaj kolko hracov chces nacitat v rozmedzi od 1 po 10\n");
                        scanf("%d", &pocet_hracov_nova_hra);
                    } else {
                        newgame=1;
                        myplayer = calloc(pocet_hracov_nova_hra + 2, sizeof(player));
                        sklad =calloc(pocet_hracov_nova_hra+2, sizeof(store));
                        nacitaj_default_sklad(pocet_hracov_nova_hra,sklad);
                        nacitaj_default_config(pocet_hracov_nova_hra, myplayer);
                        printf("\nZadaj ktoreho hraca chces.\n");
                        scanf("%d",&chcem_tohto_hraca);
                        chcem_tohto_hraca=chcem_tohto_hraca-1;
                    }
                    break;
                case 2:     //Nacitat hru

                    if(prvykrat==0){
                        myplayer=calloc(10+1, sizeof(player));
                        sklad =calloc(10+2, sizeof(store));
                    }
                    nacitajvlastnuhru(myplayer,&pocet_hracov_nova_hra);
                    nacitaj_saved_sklad(sklad);
                    nacitajvlastnehohraca(&chcem_tohto_hraca);
                    break;
                case 3:     //Ulozit hru
                    savegame(myplayer,pocet_hracov_nova_hra);
                    savegamesklad(sklad,pocet_hracov_nova_hra);
                    savegameconfighrac(chcem_tohto_hraca);
                    break;
                case 4:     //vypis hracov
                    vypishracov(myplayer,pocet_hracov_nova_hra,chcem_tohto_hraca);
                    vypisskladu(sklad,pocet_hracov_nova_hra,chcem_tohto_hraca);
                    break;
                case 5:     //sprav akciu
                    thewolf = calloc(5, sizeof(WOLF));
                    generujvlka(thewolf);
                    gameOFtrons(myplayer,sklad,thewolf,pocet_hracov_nova_hra,chcem_tohto_hraca);
                    free(thewolf);
                    break;
                case 6:     //commandpromt
                    commandpromt(myplayer,sklad,thewolf,pocet_hracov_nova_hra,chcem_tohto_hraca);
                    break;
                case 7:     //quit
                    chcemhrat=0;
                    break;

            }
        }
        if (myplayer[chcem_tohto_hraca].lives<1){
            printf("Tvoj hrac zomrel\n GAME OVER\n");
            chcemhrat=0;
        }
    }
    free(sklad);
    free(myplayer);
    return 0;
}

//TODO vo funkcii commandpromt zrus while aby to nerobilo sarapatu a vzdy budes moct
//zadat len jeden prikaz a vzdy sa vratis do hlavneho menu