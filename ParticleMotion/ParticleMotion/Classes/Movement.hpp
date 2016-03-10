//
//  Movement.hpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 02/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#ifndef Movement_hpp
#define Movement_hpp

#include "Element.hpp"

namespace ParticleMotion {
    
    class Movement {
        
    public:
        const static int NELEMENT = 5000;
        
    private:
        Element *element;
        double previousTime;
        
    public:
        Movement();
        virtual ~Movement();
        const Element * const getElement();
        void updateMovement(double);
    };
    
}


#endif /* Movement_hpp */
