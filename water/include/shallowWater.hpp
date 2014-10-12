/**
 * \file shallowWater.hpp
 * \author Florian LANCE - Armand POLI
 * \version 1.0
 * \date Février 2012
 */

#ifndef _SHALLOW_WATER_
#define _SHALLOW_WATER_

#include "vec3f.hpp"
#include "array2D.hpp"

#include <iostream>

class Color
{
  public:

        Color(){}
        ~Color(){}

        Color(const float r,const float g, const float b)
        {
                Color::r = r;
                Color::g = g;
                Color::b = b;
        }

        Color* operator=(const Color& c)
        {
                r = c.r;
                g = c.g;
                b = c.b;
                return this;
        }

        float r,g,b;
};

class Phong
{
   public:
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
        Color calc(const Vec3f &p1, const Vec3f &p2, const Vec3f &p3)
        {

                Vec3f n = cross(Vec3f(p1,p3),Vec3f(p1,p2)).normalize();
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

        Color c;
        Vec3f posL,posV;
        float cDiffus;
        float cAmbiant;
        float cSpeculaire;
        float alphaSpeculaire;
        Vec3f lDiffus;
        Vec3f lAmbiant;
        Vec3f lSpeculaire;
};


class ShallowWater
{
public:
   ShallowWater(){}
   void init(const int DIMX, const int DIMY, const float _l, const float _h)
   {
        l = _l;
        h = _h;

        m_g.init(DIMX,DIMY);
        m_h.init(DIMX,DIMY);
        m_n.init(DIMX,DIMY);
        m_v1.init(DIMX,DIMY);
        m_v2.init(DIMX,DIMY);

        for(int i = 0; i < m_g.dimX(); i++)
        {
            for(int j = 0; j < m_g.dimY(); j++)
            {
                m_g(i,j) =  -0.4 - rand()%2/2.0;


                if((i ==  m_g.dimX()/2 && j == m_g.dimY()/2) || (i ==  m_g.dimX()/2 && j == m_g.dimY()/4))
                    m_h(i,j) = 100;
                else
                    m_h(i,j) = 1;

                m_n(i,j) = m_h(i,j) - m_g(i,j);
                m_v1(i,j) = 0;
                m_v2(i,j) = 0;
            }
        }

   }

   void drawArray(const Array2D &a, const Color &c, const bool maillage,const Vec3f &posV) const
   {
        if(!maillage)
                glBegin(GL_TRIANGLES);
        else
                glBegin(GL_LINES);

        Vec3f p1,p2,p3,p4;

        Phong phong(c,Vec3f(0.0,0.0,5.0),posV,1.0);

        for(int j = 0; j < a.dimY()-1; j++)
        {
            for(int i = 0; i < a.dimX()-1; i++)
            {
                p1 = Vec3f(i*l,j*h, a(i,j));
                p2 = Vec3f((i+1)*l,j*h,a(i+1,j));
                p3 = Vec3f(i*l,(j+1)*h,a(i,j+1));
                p4 = Vec3f((i+1)*l,(j+1)*h,a(i+1,j+1));

                if(!maillage)
                {
                        Color cphong = phong.calc(p1,p3,p2);
                        glColor3f(cphong.r, cphong.g, cphong.b);
                }
                else glColor3f(c.r, c.g, c.b);

                glVertex3f(p1.x,p1.y,p1.z);
                glVertex3f(p2.x,p2.y,p2.z);
                glVertex3f(p3.x,p3.y,p3.z);

                if(!maillage)
                {
                        Color cphong = phong.calc(p3,p4,p2);
                        glColor3f(cphong.r, cphong.g, cphong.b);
                }
                else glColor3f(c.r, c.g, c.b);



                glVertex3f(p3.x,p3.y,p3.z);
                glVertex3f(p4.x,p4.y,p4.z);
                glVertex3f(p2.x,p2.y,p2.z);
            }
        }

        glEnd();
   }

   void draw(const bool maillage, const Vec3f &posV) const
   {
        glEnable (GL_BLEND);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                drawArray(m_h,Color(0,0,1.0),maillage,posV);
        glDisable(GL_BLEND);
       drawArray(m_g,Color(0.5,0.5,0.0),maillage,posV);
   }


    Array2D advect(const Array2D &s, const float deltaT)
    {
        Array2D retour;
        retour.init(s.dimX(),s.dimY());

        for(int j = 1; j < s.dimY()-1 ; j++)
        {
            for(int i = 1; i < s.dimX()-1; i++)
            {
                float x = i;
                float y = j;

                x = x - (deltaT * m_v1(i,j));
                y = y - (deltaT * m_v2(i,j));
                retour(i,j) = s.interpolate(x,y);
            }
        }

        return retour;

    }

    void updateHeight(Array2D &s, const float deltaT)
    {
        for(int j = 1; j < s.dimY()-1 ; j++)
        {
            for(int i = 1; i < s.dimX()-1; i++)
            {
                s(i,j) -= s(i,j) * ((m_v1(i+1,j)-m_v1(i,j))/1.0 +
                                    (m_v2(i,j+1)-m_v2(i,j))/1.0) * deltaT;
            }
        }
    }

    void updateVelocities(const float a, const float deltaT)
    {
        for(int j = 1; j < m_h.dimY()-1; j++)
        {
            for(int i = 2; i < m_h.dimX()-1; i++)
            {
                m_v1(i,j) += a * ((m_h(i-1,j)-m_h(i,j))/1.0) * deltaT;
            }
        }

        for(int j = 2; j < m_h.dimY()-1; j++)
        {
            for(int i = 1; i < m_h.dimX()-1; i++)
            {
                m_v2(i,j) += a * ((m_h(i,j-1)-m_h(i,j))/1.0) * deltaT;
            }
        }
    }


   void computeOneStep(const float deltaT)
   {
        Array2D new_m_n = advect( m_n,deltaT);
        Array2D new_m_v1 = advect( m_v1,deltaT);
        Array2D new_m_v2 = advect( m_v2,deltaT);

        m_n = new_m_n;
        m_v1 = new_m_v1;
        m_v2 = new_m_v2;

        updateHeight(m_n,deltaT);
        m_h = m_n + m_g;

        updateVelocities(9.81,deltaT);

   }


protected:
   Array2D m_g;     // height of the ground (0 if flat)
   Array2D m_h;     // height of the water : the thing to compute and to draw
   Array2D m_n;     // m_n = m_h - m_g : amount of water above the ground
   Array2D m_v1;    // velocity along X
   Array2D m_v2;    // velocity along Y

   float l;
   float h;


};

#endif
