#include "BDD.h"

// ---- LECTURE ---- //

int nbLignesFichier(FILE* fichier) {
    int nbLignes = 0;
    char* a = NULL;
    a = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    while(fgets(a, TAILLE_MAX_LIGNE, fichier) != NULL) {
        nbLignes++;
    }
    fseek(fichier,0,0);
    return nbLignes;
}

char* lireLigne(FILE* fichier, int n) {
    char* res = NULL;
    res = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    int max = nbLignesFichier(fichier);
    // On cherche la ligne correspondante
    if (fichier && n <= max) {
        while(n>0) {
            fgets(res,TAILLE_MAX_LIGNE,fichier);
            n--;
        }
    }
    return res;
}

int getIdMax(char* type) {
    assert(type != NULL);
    const char* chemin = NULL;
    if (strcmp(type,"aliments") == 0) {
        chemin = CHEMIN_ALIMENTS;
    }
    else if (strcmp(type,"pesees") == 0) {
        chemin = CHEMIN_PESEES;
    }
    else {
        return -1;
    }
    FILE* fichier = fopen(chemin,"r+");
    assert(fichier != NULL);
    int nbLignes = nbLignesFichier(fichier);
    char* ligne = lireLigne(fichier,nbLignes);
    int idMax = atoi(strtok(ligne,";"));
    return idMax;
}

// TODO : � refaire. Gros souci avec fseek(fichier,0,0), se renseigner
char* lireLigneParId(FILE* fichier, int id) {
    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    int idLu = malloc(10*sizeof(int));
    int max = nbLignesFichier(fichier);
    fseek(fichier,0,0);
    // On cherche la ligne correspondante
    if (fichier) {
        int n = 0;
        fseek(fichier,0,0);
        while(n <= max && idLu != id) {
            ligneLu = lireLigne(fichier,n);
            printf("\n \n ------");
            idLu = atoi(strtok(lireLigne(fichier,n),";"));
            printf("\nidlu : %d",idLu);
            printf("\nn : %d",n);
            n++;
        }
    }
    if (idLu != id) {
        ligneLu = "ID introuvable";
    }
    return ligneLu;
}

// ---- ECRITURE ---- //
int ecrireDonneeAliment(char* nom, char* couleur) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r+");
    assert(fichier != NULL);
    fseek(fichier,0,SEEK_END);

    // Saut de ligne avant insertion et formatage des donn�es
    char buffer[TAILLE_MAX_LIGNE]="\n";

    // Obtention de l'id du nouvel aliment
    int id = getIdMax("aliment") + 1;
    char *idchar = NULL;
    idchar = malloc(10*sizeof(char));
    sprintf(idchar,"%d",id);

    strcat(buffer,idchar);
    strcat(buffer,";");
    strcat(buffer,nom);
    strcat(buffer,";");
    strcat(buffer,couleur);
    strcat(buffer,";");

    fprintf(fichier,buffer);
    fclose(fichier);
    return 1;
}

int ecrireDonneePesee(int quantite,char* description,char* date,int id_aliment) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r+");
    assert(fichier != NULL);
    fseek(fichier,0,SEEK_END);

    // Saut de ligne avant insertion et formatage des donn�es
    char buffer[TAILLE_MAX_LIGNE]="\n";

    // Obtention de l'id de la nouvelle pes�e
    int id = getIdMax("pesee") + 1;
    char *idchar = NULL;
    idchar = malloc(10*sizeof(char));
    sprintf(idchar,"%d",id);

    // Conversion des donn�es int en char
    char *quantite_char = NULL;
    quantite_char = malloc(100*sizeof(char));
    char *id_aliment_char = NULL;
    id_aliment_char = malloc(10*sizeof(char));
    sprintf(quantite_char,"%d",quantite);
    sprintf(id_aliment_char,"%d",id_aliment);

    strcat(buffer,idchar);
    strcat(buffer,";");
    strcat(buffer,quantite_char);
    strcat(buffer,";");
    strcat(buffer,description);
    strcat(buffer,";");
    strcat(buffer,date);
    strcat(buffer,";");
    strcat(buffer,id_aliment_char);

    fprintf(fichier,buffer);
    fclose(fichier);
    return 1;
}