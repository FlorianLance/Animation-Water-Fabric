/**
 * @file particle.hpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */

#ifndef _PARTICLE_
#define _PARTICLE_

#include "vec3f.hpp"


/**
* @class Classe Particle, particules utilisées par tissu dans le système de ressort.
*/
class Particle
{
        public:

                /** @brief Constructeur de la particule à partir de sa position et de son état.*/
                Particle(const Vec3f &P, const bool fixe);

                /** @brief Destructeur de la particule. */
                ~Particle();

                /** @brief retourne la position de la particule */
                Vec3f getPos() const ;

                /** @brief Renvoie la vitesse*/
                Vec3f getV()const;

                /** @brief Renvoie l'accélération*/
                Vec3f getA()const;

                /** @brief Renvoie l'état de la particule.*/
                bool isFixe();


                /** @brief Modifie l'état de la particule*/
                void setFixe(bool f);


                /** @brief Calcule l'accélération en fonction de deltaT */
                Vec3f accel(const float _deltaT);

                /** @brief Calcule la vitesse en fonction de deltaT */
                Vec3f vitesse(const float _deltaT);

                /** @brief Ajoute la force f à  F */
                void addForce(const Vec3f& f);

                /** @brief Calcule le déplacement de la particule d'un pas de temps t */
                void integrateOneStep(const float _deltaT, const float _coeffRebond);


        private:

                Vec3f P;    /**< position t */
                Vec3f P_1;  /**< position t-1 */
                Vec3f P_2;  /**< position t-2 */
                Vec3f F;    /**< forces appliquÃ©es Ã  la particule */
                Vec3f V;    /**< vecteur vitesse de la particule */
                Vec3f A;    /**< vecteur d'accÃ©lÃ©ration de la particule */

                bool fixe;  /**< indique si la particule est fixe dans l'espace */
                float m;    /**< masse */

};


#endif
