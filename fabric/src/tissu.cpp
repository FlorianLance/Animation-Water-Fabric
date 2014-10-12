/**
 * @file tissu.cpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */


#include "tissu.hpp"
#include <GL/glut.h>

#include <iostream>


using namespace std;

Tissu::Tissu(){}
Tissu::~Tissu(){}



void Tissu::init(const int _l, const int _h, const float _t, const float _k, const float _v)
{
    l = _l;
    h = _h;

    tP.reserve(_l*_h);

    float dx = _t, dy = _t;

        for(int j = 0; j < _h; j++)
        {
            for(int i = 0; i < _l; i++)
            {
                Vec3f v(i*dx,1.f,j*dy);

                bool fixe = false;
                if(i == _l-1 && j == _h-1) fixe = true;
                else if(i == 0 && j == _h-1) fixe = true;

                // ajout des ressorts
                struct Ressort r;
                r.k = _k;
                r.v = _v;

                if(i < _l-1)
                {
                    r.type = STRUCTURE;
                    r.t = _t;
                    r.p1 = j*l + i;
                    r.p2 = j*l + i+1;
                    tR.push_back(r);
                }
                if(j < _h-1)
                {
                    r.type = STRUCTURE;
                    r.t = _t;
                    r.p1 = j*l + i;
                    r.p2 = (j+1)*l + i;
                    tR.push_back(r);
                }
                if(i < _l-1 && j < _h-1)
                {
                    r.type = CISAILLEMENT;
                    r.t = sqrt(2* _t*_t);
                    r.p1 = j*l + i;
                    r.p2 = (j+1)*l + (i+1);
                    tR.push_back(r);
                    r.p1 = j*l + i+1;
                    r.p2 = (j+1)*l + i;
                    tR.push_back(r);
                }

                Particle p(v,fixe);
                tP.push_back(p);
                if(fixe)
                    tPFixe.push_back(p);
            }
    }
}

void Tissu::integrateOneStep(const float _t, const float _coeffRebond, const bool _vent)
{
    for(unsigned int i = 0; i < tR.size(); i++)
    {
        forceElastique(tP[tR[i].p1],tP[tR[i].p2],tR[i]);

    }

    for(unsigned int i = 0; i < tP.size(); i++)
    {
        forceViscosite(tP[i],tR[0]);
        if(_vent)
                tP[i].addForce(Vec3f(0,0,10));
    }

    for(unsigned int i = 0; i < tP.size(); i++)
    {
        tP[i].integrateOneStep(_t,_coeffRebond);
    }
}

void Tissu::draw(const Vec3f &_posV)
{
    glBegin(GL_TRIANGLES);

    Vec3f p1,p2,p3,p4;
    Phong phong(Color(1.0,0.0,0.0),Vec3f(1.0,0.0,3.0),_posV,1.0);

    for(int j = 0; j < h-1; j++)
    {
        for(int i = 0; i < l-1; i++)
        {

            p1 = getP(i,j).getPos();
            p2 = getP(i+1,j).getPos();
            p3 = getP(i  ,j+1).getPos();
            p4 = getP(i+1  ,j+1).getPos();

            Color cphong = phong.calc(p1,p3,p2);
            glColor3f(cphong.r, cphong.g, cphong.b);
            glVertex3f(p1.x,p1.y,p1.z);
            glVertex3f(p2.x,p2.y,p2.z);
            glVertex3f(p3.x,p3.y,p3.z);

            cphong = phong.calc(p3,p4,p2);
            glColor3f(cphong.r, cphong.g, cphong.b);
            glVertex3f(p3.x,p3.y,p3.z);
            glVertex3f(p4.x,p4.y,p4.z);
            glVertex3f(p2.x,p2.y,p2.z);
        }
    }

    glEnd();


    for(unsigned int i = 0; i < tPFixe.size(); i++)
        affPointFixe(0.02,tPFixe[i]);

}


Particle Tissu::getP(const int i, const int j)
{
    return  tP[j*l + i];
}


void Tissu::affRessorts()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);

    for(unsigned int i = 0; i < tR.size(); i++)
    {
        Vec3f p1 = tP[tR[i].p1].getPos();
        Vec3f p2 = tP[tR[i].p2].getPos();

        glVertex3f(p1.x,p1.y,p1.z);
        glVertex3f(p2.x,p2.y,p2.z);
    }

    glEnd();
}

void Tissu::forceElastique(Particle &_p1, Particle &_p2, const Ressort &_r)
{
    Vec3f FE = _r.k * (Vec3f(_p1.getPos()-_p2.getPos()).norme() - _r.t)
                    * (_p1.getPos() - _p2.getPos())
                    / (Vec3f(_p1.getPos()-_p2.getPos()).norme());

     if(!_p1.isFixe())
        _p1.addForce(Vec3f(-FE.x,-FE.y,-FE.z));

     if(!_p2.isFixe())
        _p2.addForce(FE);
}

void Tissu::forceViscosite(Particle &_p, const Ressort &_r)
{
    Vec3f FV = -_r.v *_p.getV();

//    std::cout<< FV.x << " " << FV.y << " " << FV.z << std::endl;
     if(!_p.isFixe())
        _p.addForce(FV);

}

void Tissu::forceViscosite(Particle &_p1, Particle &_p2, const Ressort &_r)
{
    Vec3f FV = -_r.v *(_p1.getV() - _p2.getV()).norme()
                    * (_p1.getPos() - _p2.getPos())
                    / (Vec3f(_p1.getPos()-_p2.getPos()).norme());

     if(!_p1.isFixe())
        _p1.addForce(FV);

     if(!_p2.isFixe())
        _p2.addForce(FV);
}


void Tissu::suppressionPointsFixes()
{
    for(unsigned int i = 0; i < tP.size(); i++)
        tP[i].setFixe(false);
}


void Tissu::affPointFixe(const float _t, const Particle &_p) const
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    float x = _p.getPos().x;
    float y = _p.getPos().y;
    float z = _p.getPos().z;

    glVertex3d(x+_t,y+_t,z+_t);
    glVertex3d(x+_t,y+_t,z-_t);
    glVertex3d(x-_t,y+_t,z-_t);
    glVertex3d(x-_t,y+_t,z+_t);

    glVertex3d(x+_t,y-_t,z+_t);
    glVertex3d(x+_t,y-_t,z-_t);
    glVertex3d(x+_t,y+_t,z-_t);
    glVertex3d(x+_t,y+_t,z+_t);

    glVertex3d(x-_t,y-_t,z+_t);
    glVertex3d(x-_t,y-_t,z-_t);
    glVertex3d(x+_t,y-_t,z-_t);
    glVertex3d(x+_t,y-_t,z+_t);

    glVertex3d(x-_t,y+_t,z+_t);
    glVertex3d(x-_t,y+_t,z-_t);
    glVertex3d(x-_t,y-_t,z-_t);
    glVertex3d(x-_t,y-_t,z+_t);

    glVertex3d(x+_t,y+_t,z-_t);
    glVertex3d(x+_t,y-_t,z-_t);
    glVertex3d(x-_t,y-_t,z-_t);
    glVertex3d(x-_t,y+_t,z-_t);

    glVertex3d(x+_t,y-_t,z+_t);
    glVertex3d(x+_t,y+_t,z+_t);
    glVertex3d(x-_t,y+_t,z+_t);
    glVertex3d(x-_t,y-_t,z+_t);

    glEnd();
}
