//
//  ElementException.hpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 05/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#ifndef ElementException_hpp
#define ElementException_hpp

#include <stdio.h>
#include <iostream>
#include <exception>
#include <system_error>
#include <future>

namespace ParticleMotion {
    
    class ElementException : public std::exception {
        
    public:
        ElementException();
        virtual ~ElementException();
        template <typename T>
        void buildException(const T&);
        void printException();
        
    };
}

#endif /* ElementException_hpp */
