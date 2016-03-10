//
//  main.cpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 02/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#include <math.h>
#include <time.h>
#include <stdexcept>
#include "Window.hpp"
#include "Element.hpp"
#include "Movement.hpp"
#include "ElementException.hpp"

using namespace ParticleMotion;

using std::cout;
using std::endl;
using std::runtime_error;
using std::bad_alloc;
using std::cerr;

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Om Sairam" << std::endl;
    
    typedef unsigned char Tc;
    typedef int T;
    
    try {
        srand((unsigned int)time(NULL));
        
        //Check if the window is initialized
        Window window;
        if (window.init()==false) {
            throw runtime_error("Program terminated due to window initialization issue.");
        }
        
        Movement movement;
        const Element * const element = movement.getElement();
        
        
        while (true) {
            
            /*
             The SDL_GetTicks function  returns the number of milli-seconds elapsed since the program started
             The RGB values are passed to the window so that its color will change according to the passed values
             For the color change to be smooth, SDL_GetTicks and trigonometry finctions are utilized
             sin() or cos() returns a value between -1 to 1
             unsigned char ranges between 0 - 255 which is also the ranges of the RGB
             The formula 1 + sin(elapsed*0.0001) * 128 will generate a random number between 0-255 type casted as a unsigned char
             The 0.0001 to 0.0003 are random multipliers to create a smooth color change
             */
            
            double elapsed = SDL_GetTicks();
            Tc red=(Tc)(1 + cos(elapsed*0.0001) * 128);
            Tc green=(Tc)(1 + cos(elapsed*0.0002) * 128);
            Tc blue=(Tc)(1 + cos(elapsed*0.0003) * 128);
            
            //Clear the screen of the current values so the element movement can be initiated or the element movement to the next pixel is visible
            movement.updateMovement(elapsed);
            
            for (int i=0; i<Movement::NELEMENT; ++i) {
                
                //Create the particles by passing the position and color to the setPixel method
                Element e = element[i];
                
                //Considering the particle moves from -1 to 1
                T x = (e.postionX + 1) * Window::WINDOW_WIDTH / 2;
                
                //If we donot add Window::WINDOW_WIDTH + Window::WINDOW_HEIGHT/2 then the explosion will be in a Eliptical path
                T y = (e.positionY * (Window::WINDOW_WIDTH/2)) + (Window::WINDOW_HEIGHT/2);
                window.setColors(x, y, red, green, blue);
            }
            
            window.createEffects();
            window.updateWindow();
            
            if (window.windowEvents()==false) {
                break;
            }
        }
        
        
        window.closeWindow();
    } catch (...) {
        ElementException *e;
        e->printException();
    }

    return 0;
}
