
/**
 * @file freeflycamera.cpp
 * @author Florian LANCE - Armand POLI
 * @version 1.0
 * @date Février 2012
 */


#include "freeflycamera.hpp"

#include <cmath>
#include <GL/glu.h>
#include <iostream>

#define M_PI 3.14159265359

FreeFlyCamera::FreeFlyCamera(const Vec3f &position)
{
    _position = position;
    _phi = 0;
    _theta = 0;
    VectorsFromAngles();

    _speed = 0.01;
    _sensivity = 0.2;
    _verticalMotionActive = false;
    _keyconf["forward"] = SDLK_z;
    _keyconf["backward"] = SDLK_s;
    _keyconf["strafe_left"] = SDLK_q;
    _keyconf["strafe_right"] = SDLK_d;
    _keyconf["boost"] = SDLK_LSHIFT;
    _keystates[_keyconf["forward"]] = false;
    _keystates[_keyconf["backward"]] = false;
    _keystates[_keyconf["strafe_left"]] = false;
    _keystates[_keyconf["strafe_right"]] = false;
    _keystates[_keyconf["boost"]] = false;


}


void FreeFlyCamera::OnMouseMotion(const SDL_MouseMotionEvent & event)
{
        if(clickSouris)
        {
            _theta -= event.xrel*_sensivity;
            _phi -= event.yrel*_sensivity;
            VectorsFromAngles();
        }
}

void FreeFlyCamera::OnMouseButton(const SDL_MouseButtonEvent & event)
{

        if(clickSouris) clickSouris = false;
        else            clickSouris = true;
}

void FreeFlyCamera::OnKeyboard(const SDL_KeyboardEvent & event)
{
        switch(event.keysym.sym)
        {
                case SDLK_z: setPosition(_position + (_forward/_forward.norme())*0.1);
                break;
                case SDLK_s: setPosition(_position - (_forward/_forward.norme())*0.1);
                break;
                case SDLK_q: setPosition(_position + (_left/_left.norme())*0.1);
                break;
                case SDLK_d: setPosition(_position - (_left/_left.norme())*0.1);
                break;
                default:
                break;
        }
}


void FreeFlyCamera::setSpeed(double speed)
{
    _speed = speed;
}

void FreeFlyCamera::setSensivity(double sensivity)
{
    _sensivity = sensivity;
}

void FreeFlyCamera::setPosition(const Vec3f &position)
{
    _position = position;
    _target = _position + _forward;
}

void FreeFlyCamera::VectorsFromAngles()
{
    static const Vec3f up(0,0,1);
    if (_phi > 89)
        _phi = 89;
    else if (_phi < -89)
        _phi = -89;
    double r_temp = cos(_phi*M_PI/180);
    _forward.z = sin(_phi*M_PI/180);
    _forward.x = r_temp*cos(_theta*M_PI/180);
    _forward.y = r_temp*sin(_theta*M_PI/180);

    _left = cross(up,_forward);
    _left.normalize();

    _target = _position + _forward;
}

void FreeFlyCamera::look()
{
    gluLookAt(_position.x,_position.y,_position.z,
              _target.x,_target.y,_target.z,
              0,0,1);
}

Vec3f FreeFlyCamera::getPosCam() const
{
        return Vec3f(_position.x,_position.y,_position.z);
}


FreeFlyCamera::~FreeFlyCamera()
{}
