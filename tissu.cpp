#include "tissu.hpp"
#include <GL/glut.h>

#include <iostream>


using namespace std;

Tissu::Tissu(){}
Tissu::~Tissu(){}




/** @brief : initialise une grille de l particules de large et de h particules de haut,
ainsi que le maillage des ressorts (cf. le schéma du cours). */
void Tissu::init(const int _l, const int _h, const float _t)
{
    l = _l;
    h = _h;

    tP.reserve(_l*_h);

    float dx = _t, dy = _t;

        for(int j = 0; j < _h; j++)
        {
            for(int i = 0; i < _l; i++)
            {
                Vec3f v(i*dx,j*dy,1+rand()%10/100.f);
                Vec3f f(1.0,0,0);

                Particle p(v,0);
                p.addForce(f);
                tP.push_back(p);
            }
        cout << endl;
    }
}

/** @brief : calcule la déformation du tissu d'un pas de temps t */
void Tissu::integrateOneStep(float t)
{

}

/** @brief : affiche en OpenGL le tissu */
void Tissu::draw()
{
    glBegin(GL_TRIANGLES);

    Vec3f p1,p2,p3,p4;

    for(int j = 0; j < h-1; j++)
    {
        for(int i = 0; i < l-1; i++)
        {
            p1 = getP(i,j).getPos();
            p2 = getP(i+1,j).getPos();
            p3 = getP(i  ,j+1).getPos();
            p4 = getP(i+1  ,j+1).getPos();

            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(p1.x,p1.y,p1.z);
            glVertex3f(p2.x,p2.y,p2.z);
            glVertex3f(p3.x,p3.y,p3.z);

            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(p3.x,p3.y,p3.z);
            glVertex3f(p4.x,p4.y,p4.z);
            glVertex3f(p2.x,p2.y,p2.z);
        }
    }

    glEnd();

}


Particle Tissu::getP(const int i, const int j)
{
    return  tP[j*l + i];
}
