#include "LecteurBMP.h"

unsigned char* getEnTete(FILE* image) {
    unsigned char* enTete = malloc(54*sizeof(unsigned char));
    unsigned char octet;

    // L'en-tête d'un fichier Bitmap fait 54 octets
    int i;
    for (i=0 ; i < 54 ; i++) {
        fread(&octet,sizeof(octet),1,image);
        enTete[i] = octet;
    }
    fseek(image,0,0);
    return enTete;
}

int getLargeurBMP(FILE* image) {
    unsigned char* enTete = getEnTete(image);
    // Pas la peine d'aller chercher plus loin que l'octet 19, la largeur ne dépassera jamais 4096 pixels (16^3)
    int largeur = enTete[18] + 16*16*enTete[19];
    return largeur;
}

long getTailleImage(FILE* image) {
    // Cette information n'est pas toujours présente dans les fichiers BMP
    // On la calcule "manuellement" en sachant que l'en-tête fait toujours 54 octetc.
    return getTailleFichier(image) - 54;
}

long getTailleFichier(FILE* image) {
    unsigned char* enTete = getEnTete(image);
    long a = enTete[2];
    long b = 16*16*enTete[3];
    long c = 16*16*16*16*enTete[4];
    long d = 16*16*16*16*16*16*enTete[5];
    long taille_fichier = a + b + c + d;
    return taille_fichier;
}

Couleur* getDonnees(FILE* image) {
    long taille_image = getTailleImage(image);
    Couleur *donnees[taille_image];
    unsigned char octet;

    // Offset contiendra le nombre octet ajouté à chaque ligne pour compléter
    // celle-ci de manière à ce que ce soit un multiple de 4
    int offset = getLargeurBMP(image)%4;

    // On se positionne au début des couleurs (octet 54)
    fseek(image,54,SEEK_SET);

    if(offset == 0) {
        // On récupère tout, aucun octet ajouté pour compléter
        // Attention : pour chaque pixel, les composantes sont stockées à l'envers en Bitmap (BGR)
        // TODO : erreur sur grosse image (bird.bmp)
        // TODO : tableau/pointeur de couleur ?
        long i=0;

        while(i < taille_image) {
            Couleur* coul = initCouleur();

            fread(&octet,sizeof(octet),1,image);
            printf(" B: %d",octet);
            setBCoul((int)octet,coul);

            fread(&octet,sizeof(octet),1,image);
            printf(" G: %d",octet);
            setGCoul((int)octet,coul);

            fread(&octet,sizeof(octet),1,image);
            printf(" R: %d\n",octet);
            setRCoul((int)octet,coul);

            donnees[i] = coul;
            i += 3;
        }
    }
    else {
   /*     while (octet != EOF) {
            if (){
                i++
            }
            else {
            }
        }
    */
    }
    return &donnees;
}