#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED
#include "References.h" //Appel des references aux biblioth�ques et constantes


//Option de build dans les linker setting mettre les libSDL2main.a libSDL2.dll.a
//Dans search directory
//Option de build compiler mettre les include
//Option de build linker mettre les lib

//mettre dans build linker -lmingw32



typedef struct game{    //Structure d�finissant les param�tres du jeu


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_ptexture;
     SDL_Surface *g_psurface;


}game;

typedef struct gameState{   //Structure v�rifiant l'�tat du jeu

    int g_bRunning;


}gameState;

typedef struct coordonnees{ //Structure g�rant la position des raquettes

    double x;
    double y;

}coordonnees;


typedef struct player{  //Structure permettant de g�rer les scores des joueurs ainsi que r�cup�rer leur noms pour stocker l'information dans un fichier

    char Name;
    int score;

}player;

typedef struct defcircle{   //Structure g�rant les coordonn�es de la balle ainsi que sa vitesse de d�placement

    double BallX;
    double BallY;
    int SpeedX;
    int SpeedY;

}defcircle;

typedef enum {imo , up , down} direction;   //Diff�rents �tats des raquettes

//prototypes
int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame);  //Initialisation de l'affichage
void destroy(game *myGame); //Destruction de l'instance du jeu
void handleEvents(gameState *state,coordonnees *dep,coordonnees *dep2, direction *Player1, direction *Player2); //Gestion des inputs
void delay(unsigned int frameLimit);    //Gestion du framerate

void renderTexture(game *myGame,coordonnees *dep,coordonnees *dep2, defcircle *DefCercle ); //Affichage du jeu
void MouvementRaquette (gameState *state,coordonnees *dep,coordonnees *dep2 , direction *Player1, direction *Player2 ); //Gestion ind�pendante et non bloquante du mouvement des raquettes
void MouvBalle(coordonnees *dep, coordonnees *dep2, defcircle *DefCercle);  //Gestion du mouvement de la balle et de ses collisions

#endif
