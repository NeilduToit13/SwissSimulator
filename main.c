#include <stdio.h>
#include <SDL2/SDL.h>
#include <emscripten.h>
#include <stdlib.h>


/**
 * A Context structure that can be used to pass variables into the loop
 */ 
// TODO: Lookup structure variables. The last thing before the semicolon.
struct Context {
    SDL_Renderer *renderer;
    int iteration;
} Context;


/**
 * The loop handler, will be called repeatedly
 */ 
void mainLoop(void *arg) {
    struct Context *ctx = arg;
    printf("iteration: %d\n", ctx->iteration);

    SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);

    SDL_Rect rect;
    rect.x = ctx->iteration;
    rect.y = ctx->iteration;
    rect.w = 50;
    rect.h = 50;

    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(ctx->renderer, &rect);

    SDL_RenderPresent(ctx->renderer);

    if (ctx->iteration > 200) {
        ctx->iteration = 0;
        //emscripten_cancel_main_loop();
        //printf("loop has been cancelled\n");
        //return;
    } else {
        ctx->iteration++;
    }
}

int main() {
    printf("Entered main, going to test SDL\n");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer* renderer;

    // The 255s are element size in pixels.
    SDL_CreateWindowAndRenderer(255, 255, 0, &window, &renderer);

    struct Context ctx;
    ctx.renderer = renderer;
    ctx.iteration = 0;

    int infinite_loop = 1;
    int fps = -1;
    emscripten_set_main_loop_arg(mainLoop, &ctx, fps, infinite_loop);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    /* Try to create a window
    window = SDL_CreateWindow(
        "Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "Cannot created window: %s\n", SDL_GetError());
        return 1;
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect = {10, 10, 80, 80};

    SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);

    printf("Getting ready to draw rectangle\n");

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(6000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    */



    /**
    struct Context ctx;
    int simulate_infinite_loop = 1;
    ctx.iteration = 0;
    emscripten_set_main_loop_arg(mainLoop, &ctx, -1, simulate_infinite_loop);
     * if simulate_infinite_loop = 0, emscripten_set_main_loop_arg won't block
     * and this will run right away. If simulate_infinite_loop = 1 then this code
     * will not be reached.
    printf("quitting\n");
     */
}


