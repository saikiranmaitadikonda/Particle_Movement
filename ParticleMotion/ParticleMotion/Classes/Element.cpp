//
//  Element.cpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 02/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#include "Element.hpp"

namespace ParticleMotion {
    
    Element::Element(): postionX(0.0), positionY(0.0) {
        init();
    };
    
    Element::~Element() {};
    
    
    /*
     In the init method, initializes the particles at the center of the window. In the terms of the element, the element will move between -1 to 1 on the window as x and y are further multiplied by window width and height to get the actual position. The element position and color functionality is implemented in the Window::setColors
     */
    void Element::init() {
        
        //Initialize the particle to the center of the window
        postionX = 0;
        positionY = 0;
        
        
        /*
         During an explosion the elements move from center of explosion in a spherical path 360 degrees in all directions. In terms of radians a 360 degrees is represented by 2*PI. By multiplying the 360 degrees or here 2*PI with a double between 0 and 1 will give a random angle between 0 and 360 degrees or here 0 and 2*PI
         */
        elementMotionDirection = 2*M_PI*generateRandomNumber(0, 1);
        elementSpeed = elementSpeedConstant*generateRandomNumber(0,1);
        
        //This makes the particles travel faster as they approach the edges of the screen giving an uneven distribution across the window
        elementSpeed *= elementSpeed;
    }
    
    void Element::updateElement(double elapsed) {
        /*
         The elapsed parameter is the time elapsed since the program started. This is used to generate a smooth element movement with respect to time
         Giving the elements an more angular direction as they travel with respect to the time elapsed
         */
        elementMotionDirection += elapsed*0.0005;
        
        /*
         The elementes are moving at an angle, for this to be represented in a Cartesian coordinates we use the below formula:
         The sin() and cos() functions take only one parameter: the angle. They return a number between -1 and 1, multiply this number by the length of the vector, you get the exact Cartesian coordinates of the vector. In this case the length of the vector is the distance travelled by the element in other words the speed of the element
         */
        postionX += (elementSpeed * cos(elementMotionDirection))*elapsed;
        positionY += (elementSpeed * sin(elementMotionDirection))*elapsed;
        
        //If the elements travel outside the screen have them re-emerge from the center by calling the init method
        if (postionX<-1 || postionX>1 || positionY<-1 || positionY>1) {
            init();
        }
        
        //Randomly reinitialize particles to emerge at the center
        if (rand() < RAND_MAX/100) {
            init();
        }
    }
    
    template <typename T1, typename T2>
    T1 Element::generateRandomNumber(T2 const &min,T2 const &max) const {
        //Generating a random number between 0 to 1 so we can position the element(x,y) on the window
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> d(min,max);
        return d(mt);
    }
    
}