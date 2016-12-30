#ifndef DEF_ReconnaissanceV
#define DEF_ReconnaissanceV

// EN-TETE ReconnaissanceV.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "BDD.c"
#include "LecteurBMP.c"

// ---- CONSTANTES ---- //
//const char* CHEMIN_IMAGES_ALIMENTS = "data/images_aliments/";

// Cette constance est utilisée par plusieurs fonctions comme "seuil" de détection des couleurs
const int PRECISION_COULEUR = 50;

// ---- FONCTIONS ---- //

/**
	@brief Teste si la couleur de fond est clairement discernable ou pas
	@param ImageBMP* image, l'image que l'on souhaite analyser
	@return int, 1 (True) si une couleur de fond a été repérée, sinon 0 (False)
*/
int estUni(ImageBMP* image);

/**
	@brief Renvoie la couleur dominante de l'image (moyenne des 3 composantes RGB)
	@param ImageBMP* image, l'image que l'on souhaite analyser
	@return Couleur* , la couleur dominante de l'image
*/
Couleur* couleurDominante(ImageBMP* image);

/**
    @brief Renseigne sur la présence (ou non) d'au moins un aliment ayant une couleur proche du paramètre
	@param Couleur* coul, la couleur que l'on souhaite utiliser pour chercher des aliments
	@return int, 1 (True) s'il existe au moins un aliment proche de la couleur, 0 (False)
*/
int rechercheAliment(Couleur* coul);

#endif
