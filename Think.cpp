#include <SDL.h>
#include<bits/stdc++.h>
struct Tank {
    SDL_Rect Body;
    SDL_Rect Gun;
    double GunAngle;  // Góc xoay của súng

    Tank(int bodyX, int bodyY, int bodyWidth, int bodyHeight)
        : GunAngle(0.0) {
        // Khởi tạo body và gun
        Body = {bodyX, bodyY, bodyWidth, bodyHeight};
        Gun = {Body.x + Body.w / 2, Body.y + Body.h / 2, Body.w / 5, Body.h};
    }

    // Di chuyển xe tăng
    void Move(int deltaX, int deltaY) {
        Body.x += deltaX;
        Body.y += deltaY;
        Gun.x += deltaX;
        Gun.y += deltaY;
    }

    // Xoay súng theo vị trí của chuột
    void RotateGunToMouse(int mouseX, int mouseY) {
        // Tính toán góc xoay giữa súng và chuột
        GunAngle = atan2(mouseY - (Gun.y + Gun.h / 2), mouseX - (Gun.x + Gun.w / 2));
    }
};

int main(int argc, char* argv[]) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1; // Xử lý lỗi khởi tạo
    }

    // Tạo cửa sổ và renderer
    SDL_Window* window = SDL_CreateWindow("Tank Movement and Gun Rotation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Khởi tạo xe tăng
    Tank myTank(100, 100, 50, 30);

    // Vòng lặp chính
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                // Xử lý sự kiện nhấn phím để di chuyển xe tăng
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        myTank.Move(0, -5);
                        break;
                    case SDLK_DOWN:
                        myTank.Move(0, 5);
                        break;
                    case SDLK_LEFT:
                        myTank.Move(-5, 0);
                        break;
                    case SDLK_RIGHT:
                        myTank.Move(5, 0);
                        break;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                // Xử lý sự kiện di chuyển chuột để xoay súng
                myTank.RotateGunToMouse(event.motion.x, event.motion.y);
            }
        }

        // Xóa renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Vẽ body xe tăng
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &myTank.Body);

        // Vẽ súng xe tăng
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &myTank.Gun);

        // Vẽ đường chỉ dẫn của súng
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer, myTank.Gun.x + myTank.Gun.w / 2, myTank.Gun.y + myTank.Gun.h / 2,
                           myTank.Gun.x + myTank.Gun.w / 2 + 30 * cos(myTank.GunAngle),
                           myTank.Gun.y + myTank.Gun.h / 2 + 30 * sin(myTank.GunAngle));

        // Hiển thị renderer
        SDL_RenderPresent(renderer);
    }

    // Giải phóng bộ nhớ và thoát SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
