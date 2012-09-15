#ifndef _Vec3f_
#define _Vec3f_

#include <math.h>

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

        Vec3f operator*(const float _val)
        {
            return Vec3f(x*_val, y *_val, z * _val);
        }

        Vec3f operator-(const Vec3f _v)
        {
            return Vec3f(x -_v.x, y -_v.y, z - _v.z);
        }

        Vec3f operator+(const Vec3f _v)
        {
            return Vec3f(x +_v.x, y +_v.y, z + _v.z);
        }

        Vec3f operator/(const float _val)
        {
            return Vec3f(x / _val, y /_val, z / _val);
        }

        float dot(Vec3f vec){return (x*vec.x)+(y*vec.y)+(z*vec.z);}

        void normalize()
        {
            float dist = norme();
            x = x / dist;
            y = y / dist;
            z = z / dist;
        }

        float norme()
        {
            // N(a) = sqrt(ax² + ay²)
            return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
        }

        float x;
        float y;
        float z;
};

inline Vec3f normalize(Vec3f v)
{
    float dist = v.norme();
        v.x = v.x / dist;
        v.y = v.y / dist;
        v.z = v.z / dist;
        return v;
}

#endif
