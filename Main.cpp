

// testOpenGL.cpp : extrait SDL/OpenGL application console.
//
// 
//#include <windows.h>
//#include <iostream>
//#include <exception>
//#include <SDL.h>
//#include <GL/glew.h>
//#include<math.h>
#include "CDessine.h"
#include <cmath>

using namespace std;
// Obligatoire argv / argc !!!!!

int anglex = 0;
int angley = 0;
int anglez = 0;

int main(int argc, char* argv[])
{
    CDessine dessin;
    SDL_Window* mafenetre(0);
    SDL_GLContext moncontexteGL(0);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        cout << "erreur init SDL2.0 : " << SDL_GetError() << endl;
        return -1;
    }
    // Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
    try {
        mafenetre = SDL_CreateWindow("Test SDL/OpenGL (nov.2017 version 1.0)", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL /*| SDL_WINDOW_RESIZABLE*/);
    }

    catch (...)
    {
        cout << "Erreur lors de la création de la fenetre SDL" << endl;
    }
    // double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // Create an OpenGL context associated with the window.
    moncontexteGL = SDL_GL_CreateContext(mafenetre);
    if (moncontexteGL == 0) {
        cout << "impossible de creer le contexte SDL" << SDL_GetError() << endl;
        SDL_DestroyWindow(mafenetre);
        SDL_Quit();
    }
    GLenum initialisationGLEW(glewInit());
    if (initialisationGLEW != GLEW_OK) {
        cout << "Erreur initialisation de GLEW" << glewGetErrorString(initialisationGLEW) << endl;
        SDL_GL_DeleteContext(moncontexteGL);
        SDL_DestroyWindow(mafenetre);
        SDL_Quit();
    }
    bool continuer = true;
    SDL_Event un_evenement;
    
    dessin.config();

    
    
    
    
    dessin.Forme3D();



    while (continuer)
    {
        SDL_PollEvent(&un_evenement);
        if (un_evenement.window.event == SDL_WINDOWEVENT_CLOSE)
            continuer = false;
        else
            continuer = true;
        // Nettoyage fentre
        /* glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(1);*/
        glColor3f(0, 1, 0);

        for (int i = 0; i < Ligne3D.size(); i++)
        {
            dessin.rotationPoint3D(Ligne3D.at(i).x, Ligne3D.at(i).y, Ligne3D.at(i).z, angleX, angleY, angleZ);
        }



        //dessin.db_ligne(-128, 0, 0, 200);
        //dessin.db_ligne(0, 200, 128, 0);
        //dessin.db_ligne(128, 0, 0, -200);
        //dessin.db_ligne(0, -200, -128, 0);
        ////diagonale
        //dessin.db_ligne(-128, 0, 128, 0);  
        //dessin.db_ligne(0, 200, 0, -200);  
        //dessin.dessineUnObjet3D(0, 0, 0);
        

       



         // Dessiner le cube après rotation

        // Remettez les angles de rotation à zéro pour éviter une rotation continue
        /*dessin.db_ligne(-128, -128, 128, -128);
        dessin.db_ligne(128, -128, 128, 128);
        dessin.db_ligne(128, 128, -128, 128);
        dessin.db_ligne(-128, 128, -128, -128);*/

        //glEnable(GL_POINT_SMOOTH);
        //glPointSize(50);
        //glColor3f(0, 1, 0);
        //glBegin(GL_POINTS);
        //{
        //    //glVertex2i(0, 0); glVertex2i(0, 1);
        //    glVertex2i(0, 0); glVertex2i(0, 0);
        //    //glVertex2i(0, 0); glVertex3i(0, 0, 1);


        //}
        //glEnd();

        // TODO : dessiner dans la fenêtre SDL/OpenGL
        // actualisation de la fenetre
        SDL_GL_SwapWindow(mafenetre);
    }
    // Once finished with OpenGL functions, the SDL_GLContext can be deleted.
    SDL_GL_DeleteContext(moncontexteGL);
    SDL_DestroyWindow(mafenetre);
    SDL_Quit();
    return 0;
}
