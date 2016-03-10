//
//  Window.hpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 02/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <iostream>
#include <new> 
#include <SDL2/SDL.h>

namespace ParticleMotion {
    
    class Window {
    
    private:
        typedef Uint32 Tu;
        
    public:
        const static int WINDOW_WIDTH = 800;
        const static int WINDOW_HEIGHT = 600;
        
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        Tu *allPixels1;
        Tu *allPixels2;
        void closeSDLObjects();
        template <typename T>
        void swapElements(T&, T&);
        
    public:
        Window();
        bool init() throw (std::bad_alloc);
        bool windowEvents();
        void closeWindow();
        void updateWindow();
        void setColors(int,int,Tu,Tu,Tu);
        void clearWindow();
        void createEffects();
        
    };
    
}


#endif /* Window_hpp */
