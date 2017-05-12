#ifndef REFERENCES_H_INCLUDED
#define REFERENCES_H_INCLUDED

//Compilation des references aux biblioth�ques et constantes

#include <stdio.h>  //Inclusion des inputs et outputs standard
#include <stdlib.h> //Inclusion des librairies standards
#include <SDL2/SDL.h>   //Inclusion de la SDL2
#include <SDL2/SDL_ttf.h> //Inclusion de l'extension TTF
#include <math.h>   //Inclusion de la biblioth�que Math pour effectuer les calculs du trac� de la balle

#include <time.h>   //Inclusion de la bilbioth�que time pour calculer et limiter le framerate

#define SCREEN_WIDTH 600    //Definition par une constante de la largeur maximum de l'�cran
#define SCREEN_HEIGHT 500   //D�finition par une constante de la hauteur maximum de l'�cran
#define RAYON_BALLE 20      //D�finition par une constante du rayon de la balle

#endif
