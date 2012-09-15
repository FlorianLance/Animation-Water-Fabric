#include "particle.hpp"

#include <iostream>
using namespace std;

Particle::Particle(const Vec3f &_P, const bool _fixe) : P(_P),P_1(P),P_2(P), F(Vec3f(0.f,0.f,0.f)), fixe(_fixe)
{
    m = 0.01;
    F = Vec3f(0,-9.81,0);//*9.81
}

Particle::~Particle()
{}

void Particle::addForce(const Vec3f& _f)
{
    F.x += _f.x;
    F.y += _f.y;
    F.z += _f.z;
}

void Particle::integrateOneStep(const float _deltaT)
{
    if(!fixe)
    {//accel(_deltaT)
//        float F =

        Vec3f temp(P);
        P_2 = P_1;
        P_1 = P;
        P =  (F/m) *pow(_deltaT,2) + (P_1*2) - P_2;
//        P_2 = P_1;
//        P_1 = temp;

        cout << "F/m " << (F/m).x << " " << (F/m).y  << " " << (F/m).z << endl;
        cout << "(P_1*2) - P_2" << ((P_1*2) - P_2).x << " " << ((P_1*2) - P_2).y << " " << ((P_1*2) - P_2).z << endl;
        cout << "P_2 " << P_2.x << " " << P_2.y << " " << P_2.z << endl;
        cout << "P_1 " << P_1.x << " " << P_1.y << " " << P_1.z << endl;
        cout << "P " << P.x << " " << P.y << " " << P.z << endl;
//        addForce();

//        if(P.z < 0) P.z = 0;
    }
}

Vec3f Particle::getPos() const
{
    return P;
}

Vec3f Particle::accel(const float _deltaT)
{
    return  (P - P_1*2 + P_2)/ pow(_deltaT,2);
}
