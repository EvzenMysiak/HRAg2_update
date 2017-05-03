#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "cmake-build-debug/variables.h"


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

void commandpromt(){

}

int savegame(player myplayer[], int pocet_hracov_nova_hra) {

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

void vlastnahra(player myplayer[]){

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
    rewind(loadedfile);
    myplayer=calloc(nacitany_pocet_hracov+1, sizeof(player));
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

int numOFrows(FILE *loadedfile){
    char c;
    int count = 0;

    for (c = getc(loadedfile); c != EOF; c = getc(loadedfile))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    printf("count=%d",count);
    return count;
}

int main() {

    store *sklad;
    player *myplayer;
    WOLF *thewolf;
    int volba_hl_menu;
    int pocet_hracov_nova_hra = 0;
    int chcemhrat = 1;
    uvod();

    while (chcemhrat) {
        menu(&volba_hl_menu);
        if (volba_hl_menu > 7) {
            printf("Zadal si zlu polozku skus este raz:\n");
            menu(&volba_hl_menu);
        } else {
            switch (volba_hl_menu) {
                case 1:     //nova hra
                    printf("zadaj kolko hracov chces nacitat v rozmedzi od 1 po 10\n");
                    scanf("%d", &pocet_hracov_nova_hra);
                    if (pocet_hracov_nova_hra < 1 && pocet_hracov_nova_hra > 10) {
                        printf("zadal si zly pocet hracov skus este raz\n");
                        printf("zadaj kolko hracov chces nacitat v rozmedzi od 1 po 10\n");
                        scanf("%d", &pocet_hracov_nova_hra);
                    } else {
                        myplayer = calloc(pocet_hracov_nova_hra + 2, sizeof(player));
                        nacitaj_default_config(pocet_hracov_nova_hra, myplayer);
                    }
                    break;
                case 2:     //Nacitat hru
                        vlastnahra(myplayer);
                    break;
                case 3:     //Ulozit hru
                        savegame(myplayer,pocet_hracov_nova_hra);
                    break;
                case 4:     //vypis hracov

                    break;
                case 5:     //sprav akciu

                    break;
                case 6:     //commandpromt
                    commandpromt();
                    break;
                case 7:     //quit
                    chcemhrat=0;
                    break;

            }
        }
    }

    free(myplayer);
    return 0;
}