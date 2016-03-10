//
//  Element.hpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 02/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <random>

namespace ParticleMotion {
    
    struct Element {
        
    public:
        double postionX, positionY;
        
        void updateElement(double);
        Element();
        virtual ~Element();
        
    private:
        double elementSpeed;
        const double elementSpeedConstant=0.05;
        double elementMotionDirection;
        
        
        void init();
        template <typename T1 = double, typename T2>
        T1 generateRandomNumber(T2 const&,T2 const&) const;
    };
    
}

#endif /* Element_hpp */
