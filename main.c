#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

int main(int argc, char *argv[]) {
    // initiazation of sdl
    // SDL_Init() retur => positive/Zero or NegativeNumber
    // 0 or Positive number => Success
    // -1 or anyNegative Number => Failure

    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        SDL_Log("unable to Initialize , error: %S", SDL_GetError());
        return -1;
    }


    float screenHeight= 400;
    float screenWidth= 800;
    SDL_Window* window = SDL_CreateWindow("Abe's window",screenWidth,screenHeight, 0 );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    //the initialization of SDL_ttf

    if (!(TTF_Init())) {
        SDL_Log("TTF initialization failed %s", SDL_GetError());
        return -1;
    }


    // TTF Engine
    TTF_TextEngine* engine = TTF_CreateRendererTextEngine(renderer);
    // TTF Font
    TTF_Font* font = TTF_OpenFont ("/Users/abrahamkonate/Documents/C_executable_Code/SDLTTF/Fonts/myfont.ttf", 20);
    TTF_Text * textObj =TTF_CreateText(engine, font, 0,0);
    ///

    int score = 0;
    bool running = true;
    SDL_Event event;
    while (running) {
        //check for the events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type== SDL_EVENT_KEY_DOWN){
                switch (event.key.scancode) {
                    case SDL_SCANCODE_A:
                        score+=5;
                        SDL_Log("Score: %d", score);
                        char stringBuffer [40];
                        snprintf(stringBuffer, sizeof(stringBuffer),"Score: %d", score);
                        TTF_SetTextString(textObj,stringBuffer, 0);
                        break;
                    default:
                        // SDL_Log("this key is not valid please use AWSD for movement");
                }


            }

        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        //Text
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        TTF_DrawRendererText(textObj, 50.0f, 50.0f);
        //Typecasting int to String
        //snprintf(buffer, size, data/string/format)
        char stringBuffer [40];
        snprintf(stringBuffer, sizeof(stringBuffer), "score:%d,", score);
        SDL_RenderDebugText(renderer,50.0f, 50.0f, stringBuffer);

        //Presenter
        SDL_RenderPresent(renderer);
    }
    //close the SDL WINDOW
    SDL_DestroyWindow(window);
    //Quit SDL
    SDL_Quit();
}// Created by Abraham Konaté on 4/7/26.

// 15:05 does sdl remebers the background color? Because when you delete, it still works.