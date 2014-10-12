/**
 * @file tissu.hpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */


#ifndef _TISSU_
#define _TISSU_

#include <vector>
#include "particle.hpp"

 enum type_ressort {CISAILLEMENT, STRUCTURE};

 /**
* @struct structue ressort.
*/
struct Ressort
{
    int p1, p2; /**< Points du ressort */
    type_ressort type; /**< Type du ressort */
    float k; /**< Coefficient de raideur. */
    float v; /**< Coefficient de viscosité. */
    float t;
};

/**
* @class Classe Couleur.
*/
class Color
{
  public:

        /** @brief Constructeur par défaut.*/
        Color(){}
        /** @brief Destructeur. */
        ~Color(){}

        /** @brief Constructeur par 3 float.*/
        Color(const float r,const float g, const float b)
        {
                Color::r = r;
                Color::g = g;
                Color::b = b;
        }

        /** @brief Surchage d'affectation de la couleur. */
        Color* operator=(const Color& c)
        {
                r = c.r;
                g = c.g;
                b = c.b;
                return this;
        }

        float r,g,b; /**< Composantes rgb */
};

/**
* @class Classe Phong, calcule la luminosité d'un triangle selon phong.
*/
class Phong
{
        public:
                /** @brief Constructeur à partir de la luminosité ambiante, de la position de la lumière, de la position de la caméra et du coefficient  de diffusion. */
                Phong(const Color &c, const Vec3f &posL, const Vec3f &posV, const float cDiffus)
                {
                        Phong::c = c;
                        Phong::posL = posL;
                        Phong::posV = posV;
                        Phong::cDiffus = cDiffus;
                        Phong::cAmbiant = 1.0;
                        Phong::cSpeculaire = 0.05;
                        Phong::alphaSpeculaire = 1.0;
                        lDiffus  = Vec3f(1.0,1.0,1.0);
                        lSpeculaire  = Vec3f(1.0,1.0,1.0);
                        lAmbiant  = Vec3f(c.r,c.g,c.b);
                }
                /** @brief Calcule et renvoie la luminosté à du triangle formé par les les points en paramètres. */
                Color calc(const Vec3f &p1, const Vec3f &p2, const Vec3f &p3)
                {

                        Vec3f n = cross(Vec3f(p1,p3),Vec3f(p1,p2)).normalize();
                        if(n.x < 0)n.x *= -1;
                        if(n.y < 0)n.y *= -1;
                        if(n.z < 0)n.z *= -1;
                        Vec3f m = (p1 + p2)/4 + p3/2;
                        Vec3f l = Vec3f(posL,m).normalize();

                        Vec3f r = n*2*dot(n,l) - l;

                        float alpha = dot(-n,l);

                        float distance = (m-posL).norme();


                        Vec3f diffusL = lDiffus * alpha * cDiffus / distance;
                        Vec3f ambiantL = lAmbiant * cAmbiant /distance;
                        Vec3f speculaireL = lSpeculaire*cSpeculaire*pow(dot(r,Vec3f(posV,m)),alphaSpeculaire);///distance;
                        Vec3f L = diffusL + ambiantL + speculaireL;

                        return Color(L.x,L.y,L.z);
                }

                Color c;                /**< Couleur ambiante */
                Vec3f posL,posV;        /**< Positions de la luminère et de la caméra*/
                float cDiffus;          /**< Coefficient diffus*/
                float cAmbiant;         /**< Coefficient ambiant*/
                float cSpeculaire;      /**< Coefficient spéculaire*/
                float alphaSpeculaire;  /**< Alpha spéculaire */
                Vec3f lDiffus;          /**< Luminosité diffuse */
                Vec3f lAmbiant;         /**< Luminosité ambiante */
                Vec3f lSpeculaire;      /**< Luminosité spéculaire */
};

/**
* @class Classe Tissu, système de ressort-particule
*/
class Tissu
{
        public:

                /** @brief Constructeur par défaut. */
                Tissu();
                /** @brief Desctructeur. */
                ~Tissu();

                /** @brief  : initialise une grille de l particules de large et de h particules de haut,
                ainsi que le maillage des ressorts (cf. le schÃ©ma du cours). */
                void init(const int l, const int h, const float t, const float k, const float v);

                /// ACCESSEURS

                        /** @brief  : accesseur particule */
                        Particle getP(const int i, const int j);

                /// AFFICHAGE

                        /** @brief  : affiche en OpenGL le tissu */
                        void draw(const Vec3f &posV);

                        /** @brief  : affiche une ligne du tissu */
                        void drawLine(const int _num);

                        /** @brief  : affiche les ressorts du tissu */
                        void affRessorts();

                        /** @brief  : affiche le point fixe du tissu en paramÃ¨tre avec un cube de rayon t */
                        void affPointFixe(const float t, const Particle &p) const;

                /// PHYSIQUE

                        /** @brief  : suppression des particules fixes */
                        void suppressionPointsFixes();

                        /** @brief  : calcule et applique les forces Ã©lastiques entre 2 particules reliÃ©es par un ressort */
                        void forceElastique(Particle &_p1, Particle &_p2, const Ressort &_r);

                        /** @brief  : calcule et applique les forces de viscositÃ© entre 2 particules reliÃ©es par un ressort */
                        void forceViscosite(Particle &_p1, Particle &_p2, const Ressort &_r);
                        void forceViscosite(Particle &_p, const Ressort &_r);

                        /** @brief  : calcule la dÃ©formation du tissu d'un pas de temps t */
                        void integrateOneStep(const float _t, const float _coeffRebond, const bool _vent);

        private:
                std::vector<Particle> tP;       /** < tableau de particules */
                std::vector<Particle> tPFixe;   /** < tableau de particules fixes */
                std::vector<Ressort> tR;        /** < tableau de ressorts */
                int l;                          /** < longueur  */
                int h;                          /** < hauteur */
};

#endif

