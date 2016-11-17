#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    int tempZero = 0;
    int minZero;
    int tempOne = 0;
    int minOne;
    char currentBit;

    // Nom du fichier
    char fileNumber[255];
    char fileName[255] = "C:\\Users\\norabbit\\Documents\\TP_Compression\\TP_Compression\\files\\";
    printf("Entrez le nom du fichier à compresser : ");
    scanf("%s", fileNumber);


    // Concaténation avec le chemin par défaut
    strcat(fileName,fileNumber);
    strcat(fileName,".txt");
    FILE* fp = fopen(fileName, "r");

    // Taille du fichier
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    printf("Size = %d\n",size);
    fseek(fp, 0, SEEK_SET);

    // Création du buffer
    char fileBuffer [size];
    fgets(fileBuffer,size,fp);
    printf("Buffer[0] : %c\n",fileBuffer[0]);

    // Initialisation des mins au max possible
    minZero = size;
    minOne = size;
    int i;
    currentBit = fileBuffer[0];
    for(i = 0; i < size; i++){
        if(currentBit == fileBuffer[i]){
            // Le bit courant correspond à celui d'avant : pas de changements et on incrémente les compteurs
            if(currentBit == '0'){
                tempZero++;
            }else{
                tempOne++;
            }
        }else{
            // Le bit courant correspond pas à celui d'avant : changements
            if(fileBuffer[i] == '1'){
                // Avant : 0 - Maintenant : 1 - reset des tempZero
                currentBit = '1';
                if(tempZero < minZero) minZero = tempZero;
                tempZero = 1;
                // Avant : 1 - Maintenant : 0 - reset des tempOne
            }else{
                currentBit = '0';
                if(tempOne < minOne) minOne = tempOne;
                tempOne = 1;
            }
        }
    }
    printf("Min0 = %d || Min1 = %d\n",minZero,minOne);

    int compressedFile[size];
    i = 0;
    int j;
    int currentCompressedIndex = 3;
    tempZero = 0;
    tempOne = 0;

    // EN-TÊTE - MINZERO | MINONE | VALEUR DU PREMIER BIT
    compressedFile[0] = minZero;
    compressedFile[1] = minOne;
    if(fileBuffer[0] == '0') compressedFile[2] = 0;
    else compressedFile[2] = 1;
    int intFileBuffer[size];
    for(i = 0; i < size; i++){
        if(fileBuffer[i] == '0') intFileBuffer[i] = 0;
        else intFileBuffer[i] = 1;
    }
    int intCurrentBit;
    intCurrentBit = intFileBuffer[0];
    while( i < size ){
        // Comptage du nomre de bits successifs
        while( intCurrentBit == intFileBuffer[i]){
            if( intCurrentBit == 0 )  tempZero++;
            else tempOne++;
            i++;
        }
        // AU SECOURS, CHANGEMENT
        if(intFileBuffer[i] == 0){
            // Calcul du nombre de blocs nécessaires : n fois le min
            int nbBlocs = tempOne/minOne;

            // Ecriture du nombre d'occurrences d'un bit
            for(j = currentCompressedIndex; j < currentCompressedIndex + nbBlocs; j++){
                compressedFile[j] = minOne;
            }
            currentCompressedIndex = j+1;
            compressedFile[currentCompressedIndex] = tempOne%minOne;
            tempZero = 1;
        }else{
            // Calcul du nombre de blocs nécessaires : n fois le min
            int nbBlocs = tempZero/minZero;

            // Ecriture du nombre d'occurrences d'un bit
            for(j = currentCompressedIndex; j < currentCompressedIndex + nbBlocs; j++){
                compressedFile[j] = minZero;
            }
            currentCompressedIndex = j+1;
            compressedFile[currentCompressedIndex] = tempZero%minZero;
            tempOne = 1;
        }
        i++;
    }
    //a supprimer la fin de compressedFile
    for(i = 0; i < size ; i ++){
        printf("%d\n",compressedFile[i]);
    }
    printf("\n");

    fclose(fp);
    free(fileBuffer);

    return 0;
}
