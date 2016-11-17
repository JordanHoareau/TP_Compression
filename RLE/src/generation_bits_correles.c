#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    FILE *P_FICHIER; /* pointeur sur FILE */
    char NOM_FICHIER[255] = "C:\\Users\\norabbit\\Documents\\TP_RLE\\TP_Compression\\files\\VAL_Cor";
    int nombre_chaines =0;
    int longueur_fichier = 0;
    int nb_suite;
    int a = 0;
    int i = 0;
    int j = 0;
    int val;


    //On demande le nombre de chaines a creer
    printf("Entrez le nombre de chaines a creer : ");
    scanf("%d", &nombre_chaines);

    // On demande la longueur du fichier
    printf("Entrez la longueur du fichier : ");
    scanf("%d", &longueur_fichier);
    printf("longueur fichier : %d\n", longueur_fichier);

    //On fait ça pour le nombre de chaines demandées
    for(a=0; a<nombre_chaines;a++){
        j = 0;
        char index[255];
        sprintf(index, "%d", a);
        char nouveau_chemin[255];
        int l =0;
        for(l=0;l<255;l++){
            nouveau_chemin[l] = NOM_FICHIER[l];
        }
        strcat(nouveau_chemin,index);
        strcat(nouveau_chemin,".txt");

        P_FICHIER = fopen(nouveau_chemin, "w");  /* write */
            //On tire la longueur de la première suite et la première valeur
            nb_suite = (rand() % 50);
            val = (rand() % 2);
            for(i=0;i<longueur_fichier;i++){
                if(j==nb_suite){ //On tire une nouvelle longueur de suite et on change la valeur de val
                    nb_suite = (rand() % 100);
                    if(val==1)  val=0;
                    else val=1;
                    j=0;
                    //printf("\n");
                }
                else j++;


                printf("%d", val);
                fprintf(P_FICHIER, "%d", val);

            }
            fclose(P_FICHIER);
    }


  return 0;
}
