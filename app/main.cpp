#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <memory>

#include "Display.h"
#include "DisplayFactory.h"

namespace {

constexpr int kInitialWidth  = 800;
constexpr int kInitialHeight = 600;

SDL_Texture* CreateFrameTexture(SDL_Renderer* renderer, int w, int h)
{
    SDL_Texture* tex = SDL_CreateTexture(renderer,
                                         SDL_PIXELFORMAT_RGBA32,
                                         SDL_TEXTUREACCESS_STREAMING,
                                         w, h);
    if (tex)
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    return tex;
}

}  // namespace

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Software3DRenderer",
                                          kInitialWidth, kInitialHeight,
                                          SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int width  = kInitialWidth;
    int height = kInitialHeight;

    auto display = SWR::DisplayFactory::GetConfiguredDisplay(width, height);
    SDL_Texture* texture = CreateFrameTexture(renderer, width, height);

    Uint64 prevTicks = SDL_GetTicks();
    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
                    width  = e.window.data1;
                    height = e.window.data2;
                    display->Resize(width, height);
                    SDL_DestroyTexture(texture);
                    texture = CreateFrameTexture(renderer, width, height);
                    break;
                }
                default:
                    break;
            }
        }

        Uint64 nowTicks = SDL_GetTicks();
        float deltaTime = static_cast<float>(nowTicks - prevTicks) / 1000.0f;
        prevTicks = nowTicks;

        display->DoDrawFrame(deltaTime);

        SDL_UpdateTexture(texture, nullptr,
                          display->GetDisplayRGBAData(),
                          width * 4);

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
