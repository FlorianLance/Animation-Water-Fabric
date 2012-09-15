#ifndef _PARTICLE_
#define _PARTICLE_

#include "vec3f.hpp"


class Particle
{
  public:

    Particle(const Vec3f &P, const bool fixe);
    ~Particle();

    // ajoute la force f à F
    void addForce(const Vec3f& f);

    // calcule le déplacement de la particule d'un pas de temps t
    // (intégration la plus simple, par exemple Euler semi-implicite)
    void integrateOneStep(const float _deltaT);

    Vec3f getPos() const ;

    // calcul l'accélération
    Vec3f accel(const float _deltaT);

  private:

    Vec3f P;    // position t
    Vec3f P_1;  // position t-1
    Vec3f P_2;  // position t-2
    Vec3f F;

    bool fixe;  // indique si la particule est fixe dans l'espace
    float m;    // masse

};


#endif

//Cette partie portera sur l'écriture d'un simulateur de déformation de tissu.
//Pour ceci, écrivez la classe Particle qui comportera les données suivantes :
//
//    3 vecteurs positions P, P_1(temps-1) et P_2 (temps-2);
//    1 vecteur force F.
//
//Ainsi que les fonctions suivantes :
//
//    addForce(const Vec3f& f) : ajoute la force f à F
//    integrateOneStep(float t) : calcule le déplacement de la particule d'un pas de temps t (intégration la plus simple, par exemple Euler semi-implicite)
//
//Testez éventuellement cette classe en faisant tomber une particule (subissant juste la gravité).
//
//

//Ecrivez la classe Tissu qui comportera les données :
//
//    un tableau (stl:vector) de particules
//    un tableau de ressort.
//Un ressort pourra être une structure interne à la class Tissu,
// par exemple struct Spring { int p1, p2; } où p1 et p2 sont les indices des 2 particules reliées par le ressort.
//
//Cette classe comportera au moins les fonctions :
//
//    init(const int l, const int h) : initialise une grille de l particules
//de large et de h particules de haut, ainsi que le maillage des ressorts (cf. le schéma du cours).
//    integrateOneStep(float t) : calcule la déformation du tissu d'un pas de temps t
//    draw() : affiche en OpenGL le tissu
