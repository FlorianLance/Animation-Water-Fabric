/**
 * \file array2D.hpp
 * \author Alexandre Meyer
 * \version ??
 * \date ??
 */

#ifndef _ARRAY2D_
#define _ARRAY2D_

#include <iostream>
class Array2D
{
    public:
        Array2D() { m_dimX=m_dimY=0; }

   void init(const int DIMX, const int DIMY)
    { m_dimX=DIMX; m_dimY=DIMY; m_data.resize(m_dimX*m_dimY); }

   const int dimX() const
    { return m_dimX; }

   const int dimY() const
    { return m_dimY; }

   float& operator()(const int x, const int y)
   {
      assert( x>=0 && x<m_dimX && y>=0 && y<m_dimY);
      return m_data[ y*m_dimX+x ];
   }

   float operator()(const int x, const int y) const
//    { return operator()(x,y); }
    { return m_data[ y*m_dimX+x ];}

    Array2D operator+(const Array2D &a) const
    {
        assert(m_data.size() == a.m_data.size());
           
        Array2D retour;
        retour.init(m_dimX,m_dimY);
           
        for(unsigned int i =0; i < retour.m_data.size(); i++)
            retour.m_data[i] = m_data[i] + a.m_data[i];
           
        return retour;
    }

    Array2D operator-(const Array2D &a) const
    {
        assert(m_data.size() == a.m_data.size());
           
        Array2D retour;
        retour.init(m_dimX,m_dimY);
           
        for(unsigned int i =0; i < retour.m_data.size(); i++)
            retour.m_data[i] = m_data[i] - a.m_data[i];
           
        return retour;
    }

   float interpolate(const float x, const float y) const
   {
      //std::cout << x << " " << y << " | ";
      assert( (x>=0) && (x<=m_dimX-1) && (y>=0) && (y<m_dimY-1));
      int X = int(x);
      int Y = int(y);
      if ((X+1 >= m_dimX) || (Y+1 >= m_dimY))
        return operator()(X,Y);

      float IX_b = (x-X)*operator()(X+1,Y) + (X+1-x)*operator()(X,Y);
      float IX_h = (x-X)*operator()(X+1,Y+1) + (X+1-x)*operator()(X,Y+1);
      return (y-Y)*IX_h + (Y+1-y)*IX_b;
   }

    protected:
        std::vector<float> m_data;
        int m_dimX, m_dimY;
};


#endif
