// testOpenGL.cpp : extrait SDL/OpenGL application console.
//
#include <windows.h>
#include <iostream>
#include <exception>
#include <SDL.h>
#include <GL/glew.h>

#include "CDessine.h"
using namespace std;


// Obligatoire argv / argc !!!!!
int main(int argc, char* argv[])
{
    SDL_Window* mafenetre(0);
    SDL_GLContext moncontexteGL(0);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        cout << "erreur init SDL2.0 : " << SDL_GetError() << endl;
        return -1;
    }
    // Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
    try {
        mafenetre = SDL_CreateWindow("Test SDL/OpenGL (nov.2017 version 1.0)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL /*| SDL_WINDOW_RESIZABLE*/);
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
    CDessine dessine;
#ifdef NIDAQ
    dessine.config();
#endif // NIDAQ


    dessine.Forme3D();
    int anglex = 0;
    int angley = 0;
    int anglez = 0;

    while (continuer)
    {
        SDL_PollEvent(&un_evenement);
        if (un_evenement.window.event == SDL_WINDOWEVENT_CLOSE)
            continuer = false;
        else
            continuer = true;
        // Nettoyage fentre
        glClear(GL_COLOR_BUFFER_BIT);
        // TODO : dessiner dans la fenêtre SDL/OpenGL


        /*dessine.db_ligne(-128, -128, -128, 128);
        dessine.db_ligne(-128, 128,128, 128);
        dessine.db_ligne(128, 128, 128, -128);
        dessine.db_ligne(128, -128, -128, -128);*/
        dessine.dessineUnObjet3D(anglex, angley, anglez);
        switch (un_evenement.type) {
        case SDL_KEYDOWN:
            switch (un_evenement.key.keysym.sym) {
            case SDLK_LEFT:
                angley = angley - 1;
                if (angley < 0) {
                    angley = 360;
                }
                break;

            case SDLK_RIGHT:
                angley = angley + 1;
                if (angley > 360) {
                    angley = 0;
                }
                break;
            case SDLK_UP:
                anglex = anglex - 1;
                if (anglex < 0) {
                    anglex = 360;
                }
                break;
            case SDLK_DOWN:
                anglex = anglex + 1;
                if (anglex > 360) {
                    anglex = 0;
                }
                break;
            default:
                break;
            }
        }


        // actualisation de la fenetre
        SDL_GL_SwapWindow(mafenetre);
    }
    // Once finished with OpenGL functions, the SDL_GLContext can be deleted.
    SDL_GL_DeleteContext(moncontexteGL);
    SDL_DestroyWindow(mafenetre);
    SDL_Quit();
    return 0;
}