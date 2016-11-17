#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    int maxZero = 0;
    int currentZero = 0;
    int maxOne = 0;
    int currentOne = 0;
    int currentNumber;

    // Nom du fichier
    char fileNumber[255];
    char fileName[255] = "C:\\Users\\norabbit\\Documents\\TP_RLE\\TP_Compression\\files\\";
    printf("Entrez l'index du fichier à compresser : ");
    scanf("%s", fileNumber);


    // Concaténation avec le chemin par défaut
    strcat(fileName,fileNumber);
    strcat(fileName,".txt");
    FILE* fp = fopen(fileName, "r");

    // Taille du fichier
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    printf("Size = %d\n",size);
    fseek(fp, size, SEEK_SET);

    // Création du buffer
    int fileBuffer[size];
    fgets(fileBuffer,size,fp);
    printf("%d",fileBuffer[0]);
    int i;
    currentNumber = fileBuffer[0];
    for(i = 0; i < size; i++){
          //  printf("%s",fileBuffer[i]);
    }
    for(i = 0; i < size; i++){
        if(currentNumber == 0){
            if(fileBuffer[i] == 0){
                currentZero++;
            }else{
                maxZero = maxZero > currentZero ? maxZero : currentZero;
                currentZero = 0;
                currentNumber = 1;
            }
        }else{
            if(fileBuffer[i] == 1){
                currentOne++;
            }else{
                maxOne = maxOne > currentOne ? maxOne : currentOne;
                currentOne = 0;
                currentNumber = 0;
            }
        }
    }
    printf("Max0 = %d || Max1 = %d",maxZero,maxOne);
    fclose(fp);
    free(fileBuffer);
}
