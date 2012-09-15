#ifndef _TISSU_
#define _TISSU_

#include <vector>
#include "particle.hpp"


struct Ressort { int p1, p2; };

class Tissu
{
    public:
        Tissu();
        ~Tissu();

        /** @brief  : initialise une grille de l particules de large et de h particules de haut,
         ainsi que le maillage des ressorts (cf. le schéma du cours). */
        void init(const int l, const int h, const float t);

        /** @brief  : calcule la déformation du tissu d'un pas de temps t */
        void integrateOneStep(float t);

        /** @brief  : affiche en OpenGL le tissu */
        void draw();

        /** @brief  : accesseur particule*/
        Particle getP(const int i, const int j);

        void drawLine(const int _num);

    private:
        std::vector<Particle> tP;
        std::vector<Ressort> tR;
        int l;
        int h;
        };

#endif
