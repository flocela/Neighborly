#include "renderer.h"
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) 
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

void Renderer::poll()
{
    SDL_Event e;
    int counter = 0;
    while (SDL_WaitEvent(&e) != 0)
    {   
        counter ++;
        if (e.type == SDL_QUIT)
        {
            //_keep_polling = false;
            break;
        }
    }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

std::map<Color, ColorInfo> getColorInfo ()
{
    std::map<Color, ColorInfo> colorMap = {};
    for (ColorInfo colorInfo : _the_colors)
    {
        colorMap[colorInfo._my_color] = colorInfo;
    }
    return colorMap;
}

void Renderer::RenderCity (
  std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
  Coordinate placement
)
{
    std::map<Color, ColorInfo> colorMap = getColorInfo();
    int grid_width = 20;
    int grid_height = 20;
    SDL_Rect block;
    block.w = 12;
    block.h = 12;
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);

    for (auto const& x : coordinatesPerColor)
    {
        Color currColor = x.first;
        std::vector<Coordinate> coordinates = x.second;

        ColorInfo colorInfo = colorMap[currColor];
        std::vector<int> rgba = colorInfo.rgba;

        SDL_SetRenderDrawColor(sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
        for (Coordinate c : coordinates)
        {
            block.x = placement.getX() + c.getX() * grid_width + 4;
            block.y = placement.getY() + c.getY() * grid_height + 4;
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render()
{
  // TODO is this function ever called?
    //SDL_Rect block;
    //block.w = 50;
    //block.h = 50;

    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);

    SDL_RenderPresent(sdl_renderer);
}



void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
