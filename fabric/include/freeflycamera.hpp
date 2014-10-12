/**
 * @file freeflycamera.hpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */


#ifndef _FREEFLYCAMERA_HPP_
#define _FREEFLYCAMERA_HPP_

#include "vec3f.hpp"
#include <windows.h>
#include <SDL/SDL.h>
#include <map>
#include <string>

class FreeFlyCamera
{
public:
        FreeFlyCamera(const Vec3f &position = Vec3f(0,0,0));

        virtual void OnMouseMotion(const SDL_MouseMotionEvent &event);
        virtual void OnMouseButton(const SDL_MouseButtonEvent &event);
        virtual void OnKeyboard(const SDL_KeyboardEvent & event);


        virtual void setSpeed(double speed);
        virtual void setSensivity(double sensivity);

        virtual void setPosition(const Vec3f &position);

        virtual void look();

        Vec3f getPosCam() const;

        virtual ~FreeFlyCamera();

protected:
        double _speed;
        double _sensivity;

        //vertical motion stuffs
        Uint32 _timeBeforeStoppingVerticalMotion;
        bool _verticalMotionActive;
        int _verticalMotionDirection;

        typedef std::map<SDLKey,bool> KeyStates;
        KeyStates _keystates;
        typedef std::map<std::string,SDLKey> KeyConf;
        KeyConf _keyconf;

        Vec3f _position;
        Vec3f _target;
        Vec3f _forward;
        Vec3f _left;
        double _theta;
        double _phi;
bool clickSouris;

        void VectorsFromAngles();
        //void Init();
};

#endif //FREEFLYCAMERA_H
