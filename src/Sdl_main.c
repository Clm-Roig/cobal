#include "Sdl_main.h"

int main(int argc,char* args[]) {
	// Affichage de différentes fenetres
	init();

	menu();
	SDL_Delay(6000);
	peser();
	SDL_Delay(1000);
	stock();
	SDL_Delay(3000);

	cleanup();

	// Tests Clément
	FILE* fichier = fopen("data/pesees.txt","r");

	fclose(fichier);

	return 0;
}
