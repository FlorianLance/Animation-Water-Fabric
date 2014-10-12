/**
 * @file vec3f.cpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */

#ifndef _Vec3f_
#define _Vec3f_

#include <math.h>
#include <cassert>
#include <ostream>

class Vec3f
{
    public:
        Vec3f(){x=0;y=0;z=0;}
        Vec3f(const Vec3f &_v1,const Vec3f &_v2)
        {
            x = _v2.x - _v1.x;
            y = _v2.y - _v1.y;
            z = _v2.z - _v1.z;
        }

        Vec3f(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)
        {}

        //! produit par un reel, w= k * u, renvoie w.
        Vec3f operator*(const float _val) const
        {
            return Vec3f(x*_val, y *_val, z * _val);
        }

        //! produit par un reel, u= k * u.
        Vec3f& operator*=(const float _val)
        {
            x *= _val;
            y *= _val;
            z *= _val;
            return *this;
        }

        //! soustraction de 2 vecteurs, w = u - v, renvoie w.
        Vec3f operator-(const Vec3f &_v) const
        {
            return Vec3f(x -_v.x, y -_v.y, z - _v.z);
        }

        //! soustraction de 2 vecteurs, u= u - v.
        Vec3f& operator-=(const Vec3f &_v)
        {
            x -= _v.x;
            y -= _v.y;
            z -= _v.z;
            return *this;
        }

        //! addition de 2 vecteurs, w= u + v, renvoie w.
        Vec3f operator+(const Vec3f &_v) const
        {
            return Vec3f(x +_v.x, y +_v.y, z + _v.z);
        }

        //! addition de 2 vecteurs, u= u + v.
        Vec3f& operator+=(const Vec3f &_v)
        {
            x += _v.x;
            y += _v.y;
            z += _v.z;
            return *this;
        }

        //! division par un reel, w= u / k, renvoie w.
        Vec3f operator/(const float _val) const
        {
            assert(_val != 0);
            float inv = 1.f / _val;
            return Vec3f(x * inv, y * inv, z * inv);
        }

        //! division par un reel, u= u / k.
        Vec3f &operator/=(const float _val)
        {
            assert(_val != 0);
            float inv = 1.f / _val;
            x *= inv;
            y *= inv;
            z *= inv;

            return *this;
        }

        //! comparaison de 2 vecteurs.
        bool operator==(const Vec3f &_v) const
        {
            return (x == _v.x && y == _v.y && z == _v.z);
        }

        //! negation d'un vecteur, w= -u, renvoie w.
        Vec3f operator-() const
        {
            return Vec3f(-x,-y,-z);
        }

        //! renvoie une composante du vecteur.
        const float& operator[](const unsigned int i) const
        {
            return (&x)[i];
        }

        //! renvoie reference sur une composante du vecteur.
        float &operator[](const unsigned int i)
        {
            return (&x)[i];
        }

        float dot(const Vec3f &_v){return (x*_v.x)+(y*_v.y)+(z*_v.z);}

        Vec3f normalize() const
        {
            float dist = norme();
            float inv = 1.f/dist;
            return Vec3f(x*inv,y*inv,z*inv);
        }

        Vec3f& normalize()
        {
            float dist = norme();
            float inv = 1.f/dist;
            x = x * inv;
            y = y * inv;
            z = z * inv;

            return *this;
        }

        float norme() const
        {
            return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
        }

        float x;
        float y;
        float z;
};

inline float dot(const Vec3f &_v1, const Vec3f &_v2)
{
        return (_v1.x*_v2.x)+(_v1.y*_v2.y)+(_v1.z*_v2.z);
}

inline Vec3f cross(const Vec3f &_v1, const Vec3f &_v2)
{
        return Vec3f((_v1.y*_v2.z) - (_v1.z*_v2.y),
                     (_v1.z*_v2.x) - (_v1.x*_v2.z),
                     (_v1.x*_v2.y) - (_v1.y*_v2.x));
}

inline Vec3f normalize(Vec3f &v)
{
    float dist = v.norme();
        v.x = v.x / dist;
        v.y = v.y / dist;
        v.z = v.z / dist;
        return v;
}


inline Vec3f operator*(const float _f, const Vec3f &_v)
{
    return Vec3f(_v.x *_f, _v.y *_f, _v.z *_f);
}


#endif
