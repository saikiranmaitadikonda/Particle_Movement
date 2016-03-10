//
//  Movement.cpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 02/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#include "Movement.hpp"

namespace ParticleMotion {
    
    Movement::Movement(): previousTime(0) {
            
            //Create an array of elements of count NELEMENT
            element = new Element[NELEMENT];
    }
    
    Movement::~Movement() {
        //Destroy the pointer objects created in this class and de-allocate any memory assigned
        delete [] element;
    }
    
    const Element * const Movement::getElement() {return element;}
    
    void Movement::updateMovement(double elapsed) {
        
        /*
         To give the elements a smooth movement proportional to the time the window is opened, the element position is multiplied by the time spent between each update.
         */
        previousTime = elapsed - previousTime; //Time difference between each update call is calculated
        
        for (int i=0; i<NELEMENT; ++i) {
            element[i].updateElement(previousTime);
        }
        
        //New time is saved in the lastTime so this can be used to calculate the time lapsed between each update call
        previousTime = elapsed;
    }
    
}