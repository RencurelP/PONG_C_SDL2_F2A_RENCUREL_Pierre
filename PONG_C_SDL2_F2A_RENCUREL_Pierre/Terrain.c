#include "Terrain.h"    //Inclusion des prototypes et types


int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame){


    myGame->g_pWindow=NULL;
    myGame->g_pRenderer=NULL;
    myGame->g_psurface=NULL;
    myGame->g_ptexture=NULL;


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_PRESENTVSYNC);


            }


    }else{


        return 0;
    }



    return 1;



}




void renderTexture(game *myGame,coordonnees *dep,coordonnees *dep2, defcircle *DefCercle ) {

        int r;
        SDL_Point balle;

        for (r=0; r<360; r++){  //Calcul du tracé de la balle via les fonctions mathématiques
            balle.x=RAYON_BALLE*cos(r) + DefCercle->BallX;
            balle.y=RAYON_BALLE*sin(r) + DefCercle->BallY;
            SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(myGame->g_pRenderer, balle.x, balle.y); //Tracé de la balle par des points sur tout le périmetre
        }

       //Définition du rectangle 1 a dessiner
        SDL_Rect rectangle;
        rectangle.x=10;//debut x
        rectangle.y=dep->y;//debut y
        rectangle.w=10; //Largeur
        rectangle.h=100; //Hauteur


        //Définition du rectangle 2 a dessiner
        SDL_Rect rectangle2;
        rectangle2.x=SCREEN_WIDTH-20;//debut x
        rectangle2.y=dep2->y;//debut y
        rectangle2.w=10; //Largeur
        rectangle2.h=100; //Hauteur

        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        //Tracé du filet

        SDL_RenderDrawLine(myGame->g_pRenderer, (SCREEN_WIDTH/2), 0, (SCREEN_WIDTH/2), SCREEN_HEIGHT);


        //Draw in texture
        SDL_SetRenderDrawColor(myGame->g_pRenderer,255,0,0,255);
        SDL_SetRenderTarget(myGame->g_pRenderer, myGame->g_ptexture); //on modifie la texture

        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle);
        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle2);

        SDL_SetRenderTarget(myGame->g_pRenderer, NULL);// Dorénavent, on modifie à nouveau le renderer

        SDL_Rect position;//position de la texture dans screen
        position.x = 0;
        position.y = 0;
        SDL_QueryTexture(myGame->g_ptexture, NULL, NULL, &position.w, &position.h);
        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,NULL,&position);


         SDL_RenderPresent(myGame->g_pRenderer);

         SDL_SetRenderDrawColor(myGame->g_pRenderer,0,0,0,255);


         SDL_DestroyTexture(myGame->g_ptexture);
         SDL_RenderClear(myGame->g_pRenderer);






}

void destroy(game *myGame){

      //Destroy render
     if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);

      //Destroy texture
     if(myGame->g_ptexture!=NULL)
        SDL_DestroyTexture(myGame->g_ptexture);

    //Destroy surface
     if(myGame->g_psurface!=NULL)
         SDL_FreeSurface(myGame->g_psurface);

    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}


void handleEvents(gameState *state,coordonnees *dep,coordonnees *dep2 , direction Player1, direction Player2 ){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {

                                case SDLK_UP:   //Utilisation des flèches pour déplacer le joueur 2 (a droite)
                                                Player2 = up;
                                                    break;
                                case SDLK_DOWN:
                                                Player2 = down;
                                                    break;

                                case SDLK_z:    //Utilisation de Z et S pour déplacer le joueur 1 (gauche)
                                                Player1 = up;
                                                    break;
                                case SDLK_s:
                                                Player1 = down;
                                                    break;
                            }
                            break;

        case SDL_KEYUP: //Lorsque l'on relache la touche affecter l'état de la raquette passe a imo (immobile)
            switch(event.key.keysym.sym)
            {

                    case SDLK_UP:
                                Player2 = imo;
                                break;
                    case SDLK_DOWN:
                                Player2 = imo;
                                break;

                    case SDLK_z:
                                Player1 = imo;
                                break;
                    case SDLK_s:
                                Player1 = imo;
                                break;

            };break;

        default:break;

        }
    }


}

void MouvementRaquette (gameState *state,coordonnees *dep,coordonnees *dep2 , direction Player1, direction Player2 ){

if (Player1 = up){ //Selon l'état de la raquette cette dernière se déplace de 4 pixels soit vers le haut soir vers le bas
    if (dep->y<0){
        dep->y++;
    }else{
        dep->y-=4;
    }
}else{
    if (Player1 = down){
        if (dep->y>SCREEN_HEIGHT){
            dep->y--;
        }else{
            dep->y+=4;
        }
    }
}

if (Player2 = up){
    if (dep2->y<0){
        dep2->y++;
    }else{
        dep2->y-=4;
    }
}else{
    if (Player2 = down){
        if (dep2->y>SCREEN_HEIGHT){
            dep2->y--;
        }else{
            dep2->y+=4;
        }
    }
}
}


void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}



void MouvBalle(coordonnees *dep, coordonnees *dep2, defcircle *DefCercle){

    /*if (DefCercle->BallY>RAYON_BALLE || DefCercle->BallY<(SCREEN_HEIGHT-RAYON_BALLE)){
        if (DefCercle->BallX>RAYON_BALLE || DefCercle->BallX<(SCREEN_WIDTH-RAYON_BALLE)){
            if((DefCercle->BallX >= dep->x + 10)      // trop à droite
            || (DefCercle->BallX + RAYON_BALLE <= dep->x) // trop à gauche
            || (DefCercle->BallY >= dep->y + 100) // trop en bas
            || (DefCercle->BallY + RAYON_BALLE <= dep->y))  // trop en haut
                {
                    DefCercle->BallX+=DefCercle->SpeedX;
                    DefCercle->BallY+=DefCercle->SpeedY;
                }else{
                    DefCercle->SpeedX*= -1;
                    DefCercle->SpeedY*= -1;
                    DefCercle->BallX+=DefCercle->SpeedX;
                    DefCercle->BallY+=DefCercle->SpeedY;
                }

            if((DefCercle->BallX >= dep2->x - 10)      // trop à droite
            || (DefCercle->BallX + RAYON_BALLE <= dep2->x) // trop à gauche
            || (DefCercle->BallY >= dep2->y + 100) // trop en bas
            || (DefCercle->BallY + RAYON_BALLE <= dep2->y))  // trop en haut
                {
                    DefCercle->BallX+=DefCercle->SpeedX;
                    DefCercle->BallY+=DefCercle->SpeedY;
                }else{
                    DefCercle->SpeedX*= -1;
                    DefCercle->SpeedY*= -1;
                    DefCercle->BallX+=DefCercle->SpeedX;
                    DefCercle->BallY+=DefCercle->SpeedY;
                }
            }else{
                DefCercle->BallX=(SCREEN_WIDTH/2);
                DefCercle->BallY=(SCREEN_HEIGHT/2);

            }
        }else{
            DefCercle->SpeedX*= -1;
            DefCercle->SpeedY*= -1;
            DefCercle->BallX+=DefCercle->SpeedX;
            DefCercle->BallY+=DefCercle->SpeedY;
        }
    }*/

    //D2 permet de définir si le point passé en paramètre (dans le premier cas SCREEN_WIDTH) n'est pas dans le cercle
    int d2 = (SCREEN_WIDTH-DefCercle->BallX)*(SCREEN_WIDTH-DefCercle->BallX) + (DefCercle->BallY-DefCercle->BallY)*(DefCercle->BallY-DefCercle->BallY);
    if (d2>RAYON_BALLE*RAYON_BALLE){    //Vérification en premier lieu que le point n'est pas dans le cercle (test par exclusion)

            d2 = (0-DefCercle->BallX)*(0-DefCercle->BallX) + (DefCercle->BallY-DefCercle->BallY)*(DefCercle->BallY-DefCercle->BallY);
            if (d2>RAYON_BALLE*RAYON_BALLE){

                    d2 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + (SCREEN_HEIGHT-DefCercle->BallY)*(SCREEN_HEIGHT-DefCercle->BallY);
                    if (d2>RAYON_BALLE*RAYON_BALLE){

                            d2 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + (0-DefCercle->BallY)*(0-DefCercle->BallY);
                            if (d2>RAYON_BALLE*RAYON_BALLE){

                                //
                                /*d2 = ((dep->x+10)-DefCercle->BallX)*((dep->x+10)-DefCercle->BallX) + (DefCercle->BallY-DefCercle->BallY)*(DefCercle->BallY-DefCercle->BallY);
                                int d3 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + ((dep->y)-DefCercle->BallY)*((dep->y)-DefCercle->BallY);
                                int d4 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + ((dep->y+100)-DefCercle->BallY)*((dep->y+100)-DefCercle->BallY);

                                if ((d2>RAYON_BALLE*RAYON_BALLE) && (d3>RAYON_BALLE*RAYON_BALLE) && (d4>RAYON_BALLE*RAYON_BALLE)){

                                    //d2 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + (dep->y-DefCercle->BallY)*(dep->y-DefCercle->BallY);
                                    //if (d2>RAYON_BALLE*RAYON_BALLE){

                                        //d2 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + ((dep->y+100)-DefCercle->BallY)*((dep->y+100)-DefCercle->BallY);
                                        //if (d2>RAYON_BALLE*RAYON_BALLE){

                                            d2 = ((dep2->x-10)-DefCercle->BallX)*((dep2->x-10)-DefCercle->BallX) + (DefCercle->BallY-DefCercle->BallY)*(DefCercle->BallY-DefCercle->BallY);
                                            d3 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + ((dep2->y)-DefCercle->BallY)*((dep2->y)-DefCercle->BallY);
                                            d4 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + ((dep2->y+100)-DefCercle->BallY)*((dep2->y+100)-DefCercle->BallY);
                                            if ((d2>RAYON_BALLE*RAYON_BALLE) && (d3>RAYON_BALLE*RAYON_BALLE) && (d4>RAYON_BALLE*RAYON_BALLE)){

                                                //d2 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + (dep2->y-DefCercle->BallY)*(dep2->y-DefCercle->BallY);
                                                //if (d2>RAYON_BALLE*RAYON_BALLE){

                                                    //d2 = (DefCercle->BallX-DefCercle->BallX)*(DefCercle->BallX-DefCercle->BallX) + ((dep2->y+100)-DefCercle->BallY)*((dep2->y+100)-DefCercle->BallY);
                                                    //if (d2>RAYON_BALLE*RAYON_BALLE){
                                                        */DefCercle->BallX+=DefCercle->SpeedX;  //Ajout a la position la valeur de la vitesse en x
                                                        DefCercle->BallY+=DefCercle->SpeedY;/*Ajout a la position la valeur de la vitesse en y
                                                        //
                                                    //}else{
                                                        //DefCercle->SpeedX*= -1;
                                                        //DefCercle->BallX+=DefCercle->SpeedX;
                                                        //DefCercle->BallY+=DefCercle->SpeedY;
                                                    //}
                                                //}else{
                                                    //DefCercle->SpeedX*= -1;
                                                    //DefCercle->BallX+=DefCercle->SpeedX;
                                                    //DefCercle->BallY+=DefCercle->SpeedY;
                                                //}

                                            }else{
                                                DefCercle->SpeedX*= -1;
                                                DefCercle->BallX+=DefCercle->SpeedX;
                                                DefCercle->BallY+=DefCercle->SpeedY;
                                            }
                                        //}else{
                                            //DefCercle->SpeedX*= -1;
                                            //DefCercle->BallX+=DefCercle->SpeedX;
                                            //DefCercle->BallY+=DefCercle->SpeedY;
                                        //}
                                    //}else{
                                        //DefCercle->SpeedX*= -1;
                                        //DefCercle->BallX+=DefCercle->SpeedX;
                                        //DefCercle->BallY+=DefCercle->SpeedY;
                                    //}

                                }else{
                                    DefCercle->SpeedX*= -1;
                                    DefCercle->BallX+=DefCercle->SpeedX;
                                    DefCercle->BallY+=DefCercle->SpeedY;
                                }*/
                                //

                                //DefCercle->BallX+=DefCercle->SpeedX;
                                //DefCercle->BallY+=DefCercle->SpeedY;
                            }else{
                                DefCercle->SpeedY*= -1; //Changement de direction en multipliant la vitesse par -1
                                DefCercle->BallX+=DefCercle->SpeedX;//Réaloccation de la vitesse
                                DefCercle->BallY+=DefCercle->SpeedY;
                            }
                        }else{
                            DefCercle->SpeedY*= -1;
                            DefCercle->BallX+=DefCercle->SpeedX;
                            DefCercle->BallY+=DefCercle->SpeedY;
                        }
                    }else{
                        DefCercle->SpeedX*= -1;
                        DefCercle->BallX = SCREEN_WIDTH / 2;    //Reset des coordonnées lorsque la balle touche le bord droit ou gauche
                        DefCercle->BallY = SCREEN_HEIGHT / 2;   //Affectation au centre de l'écran
                    }
                }else{
                    DefCercle->SpeedX*= -1;
                    DefCercle->BallX = SCREEN_WIDTH / 2;
                    DefCercle->BallY = SCREEN_HEIGHT / 2;
                }

}

