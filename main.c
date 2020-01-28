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


void drawRectangle(void *arg, int number, int height) {
    struct Context *ctx = arg;

    SDL_Rect rect;
    rect.x = ((((ctx->iteration)*7)+height)%5800 - (number*number));
    rect.y = height;
    rect.w = number/2;
    rect.h = number/2;

    SDL_SetRenderDrawColor(ctx->renderer, number, number, number, 255);
    SDL_RenderFillRect(ctx->renderer, &rect);
}


/**
 * The loop handler, will be called repeatedly
 */ 
void mainLoop(void *arg) {
    struct Context *ctx = arg;
    printf("iteration: %d\n", ctx->iteration);

    SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 100, 255);
    SDL_RenderClear(ctx->renderer);

    for (int j=1; j<8; j++) {
        for ( int i=2; i<130; i++ ) {
            drawRectangle(ctx, i, j*100);
        }
    }


    SDL_RenderPresent(ctx->renderer);

    ctx->iteration++;

    /*
    if (ctx->iteration > 1000) {
        ctx->iteration = 0;
        emscripten_cancel_main_loop();
        printf("loop has been cancelled\n");
        return;
    } else {
        ctx->iteration++;
    }
    */
}

int main() {
    printf("Entered main, going to test SDL\n");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer* renderer;

    // The 255s are element size in pixels.
    SDL_CreateWindowAndRenderer(855, 855, 0, &window, &renderer);

    struct Context ctx;
    ctx.renderer = renderer;
    ctx.iteration = 0;

    int infinite_loop = 1;
    int fps = -1;
    emscripten_set_main_loop_arg(mainLoop, &ctx, fps, infinite_loop);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
