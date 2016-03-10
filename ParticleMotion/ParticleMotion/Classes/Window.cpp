//
//  Window.cpp
//  ParticleMotion
//
//  Created by SriHarsha Koka on 02/03/2016.
//  Copyright © 2016 Koka. All rights reserved.
//

#include "Window.hpp"

using std::bad_alloc;
using std::cerr;

namespace ParticleMotion {
    
    //Constructor
    //Initialize all the pointers with NULL
    Window::Window(): window(NULL), renderer(NULL), texture(NULL), allPixels1(NULL), allPixels2(NULL) {}
    
    //Initialization method for the window
    bool Window::init() throw (bad_alloc) {
        
        //Check if the SDL library is loaded properly
        if (SDL_Init(SDL_INIT_VIDEO)<0) {
            return false;
        }
        
        /*
         Create a window with position undefined
         size => width = WINDOW_WIDTH and height = WINDOW_HEIGHT
         */
        window = SDL_CreateWindow(
                                  "Particle Motion Graphics",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  WINDOW_WIDTH,
                                  WINDOW_HEIGHT,
                                  SDL_WINDOW_SHOWN
                                  );
        //Check if the window is created properly
        if (window==NULL) {
            SDL_Quit();
            return false;
        }
        
        //Create the render object. If the object is not properly created then de-allocate the window object and any memory allocated to SDL objects
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (renderer==NULL) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
        
        //Create the texture object to the render object.
        //If the object is not properly created then de-allocate the window, render objects and any memory allocated to SDL objects
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);
        if (texture==NULL) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
        
        /*
         Give the size to the allPixels objects, here the size of our window
         This allPixels object contains the pixes in the form of an array
         Fill the pixels with color using memset
         */
        try {
            //bad_alloc e; throw e;
            allPixels1 = new Tu[WINDOW_WIDTH*WINDOW_HEIGHT];
            allPixels2 = new Tu[WINDOW_WIDTH*WINDOW_HEIGHT];
        } catch (bad_alloc&) {
            closeSDLObjects();
            cerr << "Window buffer faild to instantiate." << '\n';
            throw;
        }
        
        memset(allPixels1, 0, WINDOW_WIDTH*WINDOW_HEIGHT*sizeof(Tu));
        memset(allPixels2, 0, WINDOW_WIDTH*WINDOW_HEIGHT*sizeof(Tu));
        
        return true;
    }
    
    //Capture the events for the window
    //If the window is closed by the user return false
    bool Window::windowEvents(){
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            }
        }
        
        return true;
    }
    
    
    //This finction will set the color to any given pixel position (T x,T y) using Tu r, Tu g, Tu b (is the Hex colors in RGB)
    void Window::setColors(int x, int y, Tu r, Tu g, Tu b) {
        
        //Ignore any values that are outside the window will be re-initialized
        if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT) {
            return;
        }
        
        Tu finalColor = 0;
        
        //Formulate the Hexa-decimal pattern from the given RGB values
        finalColor += r;
        finalColor <<=8;
        finalColor +=g;
        finalColor <<=8;
        finalColor +=b;
        finalColor <<=8;
        
        //Adding the opague or transperency to the Hex color pattern
        finalColor +=0xFF;
        
        /*
         The allPixels contains the entire window pixels as an array. To access a certain pixel as passed (x,y) co-ordinates. (y*WINDOW_WIDTH) -> takes to the row we need. Adding (x) to the row takes the control to the desired pixel in the array
         */
        allPixels1[(y*WINDOW_WIDTH) + x] = finalColor;
        
    }
    
    /*
     Following the box blur algorithm to implement the blur effect on the particles
     Wikipedia:
     A box blur is a spatial domain linear filter in which each pixel in the resulting image has a value equal to the average value of its neighboring pixels in the input image
     
     1 1 1
     1 1 1
     1 1 1
     
     */
    void Window::createEffects() {
        /*
         To implement the blur effect, replaceing the current particle's color with the new blurred color for the entire buffer instead of each particle. As the particles are moving changing the color of each particle will conflict with a new particle in the same position.
         
         Here everytime the screen updates with the new particle position, the previous states will get blurred.
         The Window::setColors and Window::updateWindow methods updates the allPixels1 updated the pixels at the given position.
         In this method the current state of the buffer is copied into allPixels2 and the previous state the allPixels2 already holds is copied into allPixels1 using pointers. The new average colors for the pixels are calculated. These new values are passed to Window::setColors that updates allPixels1 which contains the previous state of the buffer. Hence the previous state of the buffer particles are updated with the blurred colors
         */
        
        //swapElements(allPixels1, allPixels2);
        Tu *temp = allPixels1;
        allPixels1 = allPixels2;
        allPixels2 = temp;
        
        //Iterating through all the pixels in the window
        for (int y=0; y<WINDOW_HEIGHT; ++y) {
            for (int x=0; x<WINDOW_WIDTH; ++x) {
                
                int r=0;
                int g=0;
                int b=0;
                
                //Getting the values of all the neighbouring pixels
                for (int w=-1; w<=1; ++w) {
                    for (int h=-1; h<=1; ++h) {
                        int presentX = x+h;
                        int presentY = y+w;
                        
                        //Ignore pixels that are outside the window
                        if (presentX >= 0 && presentX < WINDOW_WIDTH && presentY >=0 && presentY < WINDOW_HEIGHT) {
                            /*
                             To convert the [x,y] set fotmat to index format and access an element at the position of (x,y) then we use the below formula:
                             (y * WINDOW_WIDTH) + x
                             here y * WINDOW_WIDTH takes the control to the respective row and adding the x gives the index value
                             
                             Each pixel in the buffer contains the color value in hexadecimal with 0xRRGGBBAA format set by the method Window::setColors.
                             To re-assign a blurred color to the current pixel, the average of each Red, Green and Blue colors from each of the neighbouring pixels needs to be extracted from the single hexadecimal value.
                             i.e from 0xRRGGBBAA
                             to get the average red color then extract RR value from 0xRRGGBBAA of each neighbouring pixel and average it.
                             */
                            
                            Tu finalColor = allPixels2[(presentY*WINDOW_WIDTH) + presentX];
                            
                            r += (finalColor & 0xFF00000000) >> 24; //Get the red value from the color
                            g += (finalColor & 0x00FF0000) >> 16; //Get the green value from the color
                            b += (finalColor & 0x0000FF00) >> 8;//Get the blue value from the color
                            
                        }
                    }
                }
                //Update the pixel values with the color average. The previous state of the buffer particles are updated with the blurred colors
                setColors(x, y, r/9, g/9, b/9);
            }
        }
    }
    
    
    //Update the Window events with the texture values
    void Window::updateWindow() {
        
        SDL_UpdateTexture(texture, NULL, allPixels1, WINDOW_WIDTH*sizeof(Tu));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    
    template <class T>
    void Window::swapElements(T& element1, T& element2)
    {
        T tempElement(std::move(element1));
        element1 = std::move(element2);
        element2 = std::move(tempElement);
    }
    
    //This method sets all the pixels to black color giving a clear window effect
    void Window::clearWindow() {
        
        memset(allPixels1, 0, WINDOW_WIDTH*WINDOW_HEIGHT*sizeof(Tu));
        memset(allPixels2, 0, WINDOW_WIDTH*WINDOW_HEIGHT*sizeof(Tu));
    }
    
    //Deallocate memory of all the objects
    void Window::closeWindow() {
        
        delete [] allPixels1;
        delete [] allPixels2;
        closeSDLObjects();
    }
    
    void Window::closeSDLObjects() {
        
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
};