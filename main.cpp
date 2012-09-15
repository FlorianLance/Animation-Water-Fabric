
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include <iostream>
#include "tissu.hpp"
//
#include <math.h>
#include <assert.h>
#include <time.h>

Tissu *tissu;
std::vector<Particle> tabP;

using namespace std;


void display(void);
void dessinePlan ();
void dessineAxes(float taille);
void drawParticles(const std::vector<Particle> &t);



int main(int argc, char *argv[])
{
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)800/600,1,1000);

    glEnable(GL_DEPTH_TEST);

    tissu = new Tissu();
    tissu->init(10,10,0.1);

    for(int i = 0; i < 1; i ++)
    {
        Particle p1(Vec3f(0.f,1.f,0.f),0);
        tabP.push_back(p1);
    }

    bool continuer = true;


    while (continuer)
    {

        for(int i = 0; i < tabP.size(); i++)
            tabP[i].integrateOneStep(0.0001);

        display();

        SDL_WaitEvent(&event);
        std::cout  << "next " << std::endl;
        switch(event.type)
        {

            case SDL_QUIT:
                continuer = false;
        }
    }

    SDL_Quit();

    return 0;
}


/** implémentation de display(void) */
void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    gluLookAt(3,1,2,0,0,0,0,0,1);

    glRotatef(90,1,0,0);
//    glRotatef(20,0,0,1);

    dessinePlan();
//    dessineAxes(1.0);
    drawParticles(tabP);

//    glRotatef(60,1,0,0);
//    tissu->draw();
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
        glVertex3f(0, 0, 0); // x
        glVertex3f(taille, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, 0, 0);// y
        glVertex3f(0, taille, 0);

    glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, 0); // Z
        glVertex3f(0, 0, taille);
    glEnd();
}

void drawParticles(const std::vector<Particle> &_t)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINT);

    for(unsigned int i = 0; i < _t.size(); i++)
    {
        glVertex3f(_t[i].getPos().x, _t[i].getPos().y, _t[i].getPos().z);// y
    }

    glEnd();
}
