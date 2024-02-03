#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("Image Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load images
    SDL_Surface* imgBikiniBottom = IMG_Load("bikinibottom.jpg");
    SDL_Surface* imgSpongebob = IMG_Load("spongebob.png");

    if (!imgBikiniBottom || !imgSpongebob) {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Create textures from surfaces
    SDL_Texture* texBikiniBottom = SDL_CreateTextureFromSurface(renderer, imgBikiniBottom);
    SDL_Texture* texSpongebob = SDL_CreateTextureFromSurface(renderer, imgSpongebob);

    // Free surfaces as they are no longer needed
    SDL_FreeSurface(imgBikiniBottom);
    SDL_FreeSurface(imgSpongebob);

    // Main loop
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the textures
        SDL_RenderCopy(renderer, texBikiniBottom, NULL, NULL);
        SDL_RenderCopy(renderer, texSpongebob, NULL, NULL);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(texBikiniBottom);
    SDL_DestroyTexture(texSpongebob);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
