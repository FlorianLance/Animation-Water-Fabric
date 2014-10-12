/**
 * \file main.cpp
 * \author Florian LANCE - Armand POLI
 * \version 1.0
 * \date Février 2012
 */

#include <Windows.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include <iostream>

#include <math.h>
#include <assert.h>
#include <time.h>
#include <vector>

#include "shallowWater.hpp"
#include "array2D.hpp"
#include "freeflycamera.hpp"

#define FPS 50

#ifdef _WIN32
#undef main
#endif

bool affAxes = false, affMaillage = false;
ShallowWater *sw;


using namespace std;

void display(void);
void dessinePlan ();
void dessineAxes(float taille);


FreeFlyCamera * camera; /**< caméra. */

int main(int argc, char *argv[])
{

        // init SDL
                SDL_Event event;

                SDL_Init(SDL_INIT_VIDEO);
                atexit(SDL_Quit);
                SDL_WM_SetCaption("SDL GL Application", NULL);
                SDL_SetVideoMode(1024, 800, 32, SDL_OPENGL);
                SDL_EnableKeyRepeat(50, 50);

        // init GL
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective(70,(double)800/600,1,1000);

                glEnable(GL_DEPTH_TEST);

        // init water
                sw = new ShallowWater();
                sw->init(100,100,0.05,0.05);
                //    sw->init(50,50,0.4,0.4);

        // init caméra
                camera = new FreeFlyCamera(Vec3f(0,0,2));

        // init boucle
                bool continuer = true;

                float tempsActuel = 0;
                float tempsPrecedent = 0;


        while (continuer)
        {
                // continuer = false;
                while(SDL_PollEvent(&event))
                {


                        switch(event.type)
                        {
                                case SDL_QUIT:
                                continuer = 0;
                                break;
                                case SDL_KEYDOWN:
                                        switch (event.key.keysym.sym)
                                        {
                                                case SDLK_ESCAPE:
                                                        continuer = 0;
                                                break;
                                                case SDLK_a:
                                                        if(affAxes) affAxes= false;
                                                        else        affAxes = true;
                                                break;
                                                case SDLK_m:
                                                        if(affMaillage) affMaillage= false;
                                                        else            affMaillage = true;
                                                break;
                                                case SDLK_SPACE:
                                                        delete sw;
                                                        sw = new ShallowWater();
                                                        sw->init(100,100,0.05,0.05);
                                                break;
                                                default:
                                                        camera->OnKeyboard(event.key);
                                        }
                                break;
                                case SDL_KEYUP:
                                case SDL_MOUSEMOTION:
                                        camera->OnMouseMotion(event.motion);
                                break;
                                case SDL_MOUSEBUTTONUP:
                                        camera->OnMouseButton(event.button);
                                case SDL_MOUSEBUTTONDOWN:
                                break;
                        }
                }

                sw->computeOneStep(0.02);
                display();

                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tempsPrecedent < 1000/FPS)
                {
                        tempsPrecedent = tempsActuel;
                        SDL_Delay(1000/FPS - (tempsActuel - tempsPrecedent));
                }
        }

        delete camera;
        SDL_Quit();

        return 0;
}


/** implÃ©mentation de display(void) */
void display(void)
{
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );

        camera->look();
        Vec3f posV = camera->getPosCam();
        //gluLookAt(1,1,2,0,0,0,0,0,1);

        glTranslatef(-0.5,0,-0.9);

        if(affAxes)
                dessineAxes(0.5);

        sw->draw(affMaillage,posV);

        glFlush();
        SDL_GL_SwapBuffers();
}



void dessinePlan ()
{
        int x = 2;
        glColor3f(1.0, 1.0, 1.0);
        glBegin (GL_QUADS);
        glVertex3d(+x,0,-x); //with our vertices we have to assign a texcoord
        glVertex3d(+x,0,+x); //so that our texture has some points to draw to
        glVertex3d(-x,0,+x);
        glVertex3d(-x,0,-x);
        glEnd();
}


void dessineAxes(float taille)
{
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
                glVertex3f(0, 0, 0);
                glVertex3f(taille, 0, 0);

                glColor3f(0.0, 1.0, 0.0);
                glVertex3f(0, 0, 0);
                glVertex3f(0, taille, 0);

                glColor3f(0.0, 0.0, 1.0);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0, taille);
        glEnd();
}

