SDL_Window*         Screen::window                  = NULL;
SDL_GLContext       Screen::context                 = NULL;
bool                Screen::is_fullscreen           = false;
uint32_t            Screen::WIDTH                   = 1024;
uint32_t            Screen::HEIGHT                  = 720;

void Screen::InitWindow(const char* title)
{
    if (window != NULL)
        throw std::runtime_error("ERROR: InitWindow is called more then once, you can only have one window");

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL
    );
    context = SDL_GL_CreateContext(window);
}

void Screen::DestroyWindow()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

void Screen::SetWindowTitle(const char* title)
{
    SDL_SetWindowTitle(window, title);
}

void Screen::SetResolution ( uint32_t w , uint32_t h , bool full_screen )
{
    is_fullscreen = full_screen;
    SDL_SetWindowSize(window, w, h);
    if (is_fullscreen)
    {
        SDL_SetWindowFullscreen(window, SDL_TRUE);
    }
    else
    {
        SDL_SetWindowFullscreen(window, SDL_FALSE);
    }
    WIDTH = w;
    HEIGHT = h;
}
void Screen::SetScreenPosition ( uint32_t x , uint32_t y )
{
    SDL_SetWindowPosition(window, x, y);
}
void Screen::GetDisplayResolution ( uint32_t &width , uint32_t &height )
{
    width = WIDTH;
    height = HEIGHT;
}
void Screen::GetWindowPosition ( uint32_t &x , uint32_t &y )
{
    int _x, _y;
    SDL_GetWindowPosition(window, &_x, &_y);
    x = (uint32_t)_x;
    y = (uint32_t)_y;
}

SDL_Window*         Screen::GetWindow()
{
    return window;
}
SDL_GLContext       Screen::GetContext()
{
    return context;
}

void Screen::LockCursor(bool lock)
{
    if (lock)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}