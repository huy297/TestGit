#include <SDL.h>
#include<bits/stdc++.h>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_WIDTH = 50;
const int RECT_HEIGHT = 50;
const char* WINDOW_TITLE = "Tank Game";
void logErrorAndExit(const char* msg, const char *error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}
SDL_Window* initSDL (int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("SDL_Init", SDL_GetError());
    }
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("Create Window", SDL_GetError());
    return window;
}
SDL_Renderer* createRenderer(SDL_Window *window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("Create Renderer", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    return renderer;
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
struct Tank {
    SDL_Rect Body;
    SDL_Rect Gun;
<<<<<<< HEAD
    SDL_Surface* gunSurface;
    SDL_Texture* gunTexture;
    double GunRotation;
    Tank () {}
    Tank(SDL_Renderer* renderer, int bodyX, int bodyY, int bodyWidth, int bodyHeight) {
        //
            GunRotation = 0;
=======
    double gunRotation;
    Tank () {}
    Tank(int bodyX, int bodyY, int bodyWidth, int bodyHeight) {
>>>>>>> 5cff6701dc75f443748fba0006b0b50b2ff9e781
            // Set up the body
            Body.x = bodyX;
            Body.y = bodyY;
            Body.w = bodyWidth;
            Body.h = bodyHeight;

            // Set up the gun in the center of the body
            Gun.w = bodyWidth / 5;  // Gun width is one-fifth of the body width
            Gun.h = bodyHeight;     // Gun height is the same as the body height
            Gun.x = Body.x + Body.w/2 - Gun.w/2;
            Gun.y = Body.y + Body.h/2;
<<<<<<< HEAD
            //
            gunSurface = SDL_CreateRGBSurface(0, Gun.w, Gun.h, 32, 0, 0, 0, 0);
            SDL_FillRect(gunSurface, nullptr, SDL_MapRGB(gunSurface->format, 0, 0, 255));
            gunTexture = SDL_CreateTextureFromSurface(renderer, gunSurface);
            SDL_FreeSurface(gunSurface);

=======
>>>>>>> 5cff6701dc75f443748fba0006b0b50b2ff9e781
        }
    void draw(SDL_Window* window, SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderFillRect(renderer, &Body);
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
<<<<<<< HEAD
                // Render the gun texture at the updated angle
            SDL_Point gunCenter = {0, 0};
            SDL_RenderCopyEx(renderer, gunTexture, nullptr, &Gun, GunRotation * 180 / M_PI, &gunCenter, SDL_FLIP_NONE);
            SDL_RenderPresent(renderer);
=======
        SDL_RenderFillRect(renderer, &Gun);
>>>>>>> 5cff6701dc75f443748fba0006b0b50b2ff9e781
    }
    void Move(int deltaX, int deltaY) {
        Body.x += deltaX;
        Body.y += deltaY;
        Gun.x += deltaX;
        Gun.y += deltaY;
    }
<<<<<<< HEAD
     void RotateGun(SDL_Renderer* renderer, int mouseX, int mouseY) {
          GunRotation = atan2(mouseY - (Gun.y + Gun.h / 2), mouseX - (Gun.x + Gun.w / 2));
        GunRotation -= M_PI / 2; // Adjust for SDL's coordinate system
                // Clear the renderer
    }
}MyTank;
bool isKeyPressed(const Uint8* state, SDL_Scancode key) {
    return state[key] == 1;
}
=======
     void RotateGun(int mouseX, int mouseY) {
        // Calculate the angle between the gun's center and the mouse position
        gunRotation = atan2(static_cast<double>(mouseY - (Gun.y + Gun.h / 2)),
                            static_cast<double>(mouseX - (Gun.x + Gun.w / 2)));
    }
}MyTank;
>>>>>>> 5cff6701dc75f443748fba0006b0b50b2ff9e781
int main(int argc, char* argv[]) {
   SDL_Window* window = initSDL(SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    SDL_Event e;
<<<<<<< HEAD
    MyTank = Tank(renderer,0,0,40,50);
=======
    MyTank = Tank(0,0,100,100);
>>>>>>> 5cff6701dc75f443748fba0006b0b50b2ff9e781
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
<<<<<<< HEAD
            else if (event.type == SDL_MOUSEMOTION) {
                // Update gun rotation based on mouse movement
                MyTank.RotateGun(renderer, event.motion.x, event.motion.y);
            }
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

        int deltaX = 0;
        int deltaY = 0;

        if (isKeyPressed(currentKeyStates, SDL_SCANCODE_W)) {
            deltaY -= 5;
        }
        if (isKeyPressed(currentKeyStates, SDL_SCANCODE_S)) {
            deltaY += 5;
        }
        if (isKeyPressed(currentKeyStates, SDL_SCANCODE_A)) {
            deltaX -= 5;
        }
        if (isKeyPressed(currentKeyStates, SDL_SCANCODE_D)) {
            deltaX += 5;
=======
            else if (event.type == SDL_KEYDOWN) {
                 // Handle key events for moving the rectangle
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        MyTank.Move(0,-5);
                        break;
                    case SDLK_DOWN:
                        MyTank.Move(0,5);
                        break;
                    case SDLK_LEFT:
                        MyTank.Move(-5,0);
                        break;
                    case SDLK_RIGHT:
                        MyTank.Move(5,0);
                        break;
                }
            }
            else if (event.type == SDL_MOUSEMOTION) {
                // Update gun rotation based on mouse movement
                MyTank.RotateGun(event.motion.x, event.motion.y);
            }
>>>>>>> 5cff6701dc75f443748fba0006b0b50b2ff9e781
        }

        MyTank.Move(deltaX, deltaY);

        // Clear the renderer
         SDL_SetRenderDrawColor(renderer,0,255,0,255);
        SDL_RenderClear(renderer);
<<<<<<< HEAD
         MyTank.draw(window,renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
=======
     MyTank.draw(window,renderer);
    SDL_RenderPresent(renderer);
>>>>>>> 5cff6701dc75f443748fba0006b0b50b2ff9e781
    }
    return 0;
}
