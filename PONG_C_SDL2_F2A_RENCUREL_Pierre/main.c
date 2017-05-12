#include "Terrain.h" //Inclusion des fichiers connexes Terrain.h et Terrain.c




int main(int argc, char *argv[])    //Fonction main
{


     game myGame;   //Déclarations des variables
     gameState state;

     unsigned int frameLimit = SDL_GetTicks() + 16; //Affectation du framerate
     coordonnees dep;
     coordonnees dep2;

     defcircle DefCercle;
     DefCercle.BallX=(SCREEN_WIDTH/2);
     DefCercle.BallY=(SCREEN_HEIGHT/2);
     DefCercle.SpeedX=1;
     DefCercle.SpeedY=-1;

     direction Player1 = imo;
     direction Player2 = imo;

     int choix=0;


     state.g_bRunning=1;




        //Create texture for drawing in texture or load picture
        myGame.g_ptexture=SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);




        while(state.g_bRunning){



                if(choix==0){   //Lacement du jeu après consultation du joueur

                    printf("1:Lancer le PONG C facile\n");

                    scanf("%i",&choix); //Saisie du choix par le joueur


                }
                switch (choix){

                        case 1:init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame);
                                while(state.g_bRunning){    //Appel des procedures et fonctions

                                    handleEvents(&state,&dep,&dep2, &Player1, &Player2);    //Gestion des inputs
                                    MouvementRaquette (&state,&dep,&dep2 ,&Player1,&Player2 ); //Mouvement des raquettes
                                    MouvBalle(&dep, &dep2, &DefCercle); //Mouvement de la balle et gestion des collisions
                                    renderTexture(&myGame,&dep,&dep2, &DefCercle ); //Tracé des raquettes et de la balle

                                }

                                 break;


                        default:break;


                }

                 system ("cls");


             // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);  //Limitation du framerate
            frameLimit = SDL_GetTicks() + 16;



        }

        destroy(&myGame);   //Destruction de l'affichage

        SDL_Quit(); //Fin de l'utilisation de la SDL


    return 0;
}

