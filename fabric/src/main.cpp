/**
 * @file main.cpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */

#include <windows.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <cstdlib>

#include <iostream>
#include "tissu.hpp"
#include "freeflycamera.hpp"

#include <math.h>
#include <assert.h>
#include <time.h>

#define FPS 50

#ifdef _WIN32
#undef main
#endif

Tissu *tissu;
std::vector<Particle> tabP;

float k = 20000.0;      /**< Coefficient de raideur. */
float rebond = 0.1;     /**< Coefficient de rebond. */
float v = 0.9;          /**< Coefficient de viscosité. */

bool affPlan = true, affAxes = false, affTissu = true, affRessort = true, vent = false; /**< booleens de contrôle. */

//using namespace std;

/** @brief  Fonction d'affichage de la scène */
void display(void);
/** @brief Dessine le fond*/
void dessinePlan();
/** @brief Dessine les axes*/
void dessineAxes(float taille);

FreeFlyCamera * camera; /**< caméra. */

int main(int argc, char *argv[])
{
        if(argc == 4)
        {
                k = atof(argv[1]);
                rebond= atof(argv[2]);
                v = atof(argv[3]);
        }

        SDL_Event event;

        SDL_Init(SDL_INIT_VIDEO);
        atexit(SDL_Quit);
        SDL_WM_SetCaption("SDL GL Application", NULL);
        SDL_SetVideoMode(1024, 860, 32, SDL_OPENGL);

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective(70,(double)800/600,0.001,1000);
        glEnable(GL_DEPTH_TEST);

        // init tissu
                tissu = new Tissu();
                tissu->init(100,100,0.05,k,v);

        // init caméra
                camera = new FreeFlyCamera(Vec3f(0,1,2));

        bool continuer = true;

        float tempsActuel = 0;
        float tempsPrecedent = 0;

        SDL_EnableKeyRepeat(50, 50);



        while (continuer)
        {

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
                                                case SDLK_p:
                                                        if(affPlan) affPlan = false;
                                                        else        affPlan = true;
                                                break;
                                                case SDLK_a:
                                                        if(affAxes) affAxes= false;
                                                        else        affAxes = true;
                                                break;
                                                case SDLK_t:
                                                        if(affTissu) affTissu= false;
                                                        else         affTissu = true;
                                                break;
                                                case SDLK_r:
                                                        if(affRessort) affRessort= false;
                                                        else           affRessort = true;
                                                break;
                                                case SDLK_v:
                                                        if(vent) vent= false;
                                                        else     vent= true;
                                                break;
                                                case SDLK_SPACE:
                                                        delete tissu;
                                                        tissu = new Tissu();
                                                        tissu->init(30,30,0.05,k,v);
                                                break;
                                                case SDLK_l:
                                                        tissu->suppressionPointsFixes();
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

                tissu->integrateOneStep(0.001,rebond,vent);
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



void display(void)
{
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );

        camera->look();
        Vec3f posV = camera->getPosCam();

        glRotatef(90,1,0,0);

        if(affPlan)
                dessinePlan();

        if(affAxes)
                dessineAxes(0.5);

        glTranslatef(-0.5,0,-0.9);

        if(affTissu)
                tissu->draw(posV);
        if(affRessort)
                tissu->affRessorts();


        glFlush();
        SDL_GL_SwapBuffers();
}



void dessinePlan ()
{
    int x = 2;
  glColor3f(1.0, 1.0, 1.0);
  glBegin (GL_QUADS);
    glVertex3d(+x,0,-x);
    glVertex3d(+x,0,+x);
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

void drawParticles(const std::vector<Particle> &_t)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINT);

    for(unsigned int i = 0; i < _t.size(); i++)
        glVertex3f(_t[i].getPos().x, _t[i].getPos().y, _t[i].getPos().z);

    glEnd();
}
