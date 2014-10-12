/**
 * @file particle.cpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */

#include "particle.hpp"

Particle::Particle(const Vec3f &_P, const bool _fixe) : P(_P),P_1(P),P_2(P), F(Vec3f(0.f,0.f,0.f)),
                                                        V(Vec3f(0.f,0.f,0.f)),A(Vec3f(0.f,0.f,0.f)),fixe(_fixe)
{
    m = 1.0;
}

Particle::~Particle()
{}

void Particle::addForce(const Vec3f& _f)
{
    F.x += _f.x;
    F.y += _f.y;
    F.z += _f.z;
}

void Particle::integrateOneStep(const float _deltaT, const float _coeffRebond)
{
    if(!fixe )//&& P.y > 0.01)
    {
        P_2 = P_1;
        P_1 = P;

        addForce(Vec3f(0,-9.81,0));


        P =  (F/m) *pow(_deltaT,2) + (P_1*2) - P_2;

        A = accel(_deltaT);
        V = vitesse(_deltaT);
        F = Vec3f(0,0,0);

        if(P.y < 0)
        {
            Vec3f FMax = A*-m;
            P.y = 0.001;
            addForce(FMax*_coeffRebond);
        }

    }
}

Vec3f Particle::getPos() const
{
    return P;
}

Vec3f Particle::getA() const
{
    return A;
}

Vec3f Particle::getV() const
{
    return V;
}

Vec3f Particle::accel(const float _deltaT)
{
    return F * 1.f/m ;
}

Vec3f Particle::vitesse(const float _deltaT)
{
    return V + A*_deltaT;
}


bool Particle::isFixe(){return fixe;}


void Particle::setFixe(bool _f){ fixe = false;}
