Core::Core(const char* window_title)
{
    //SDL
    if (SDL_Init(SDL_INIT_NOPARACHUTE & SDL_INIT_EVERYTHING))
    {
        std::cout << SDL_GetError() << std::endl;
        throw std::runtime_error("ERROR [SDL_Init]");
    }
    std::cout << "SUCCESS [SDL_Init]" << std::endl;

    //SDL Image
    int image_init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int return_init_flags = IMG_Init(image_init_flags);
    if ((return_init_flags & image_init_flags) != image_init_flags)
    {
        std::cout << IMG_GetError() << std::endl;
        throw std::runtime_error("ERROR [IMG_Init]");
    }
    std::cout << "SUCCESS [IMG_Init]" << std::endl;

    //TTF Font
    if (TTF_Init() == -1)
    {
        std::cout << TTF_GetError() << std::endl;
        throw std::runtime_error("ERROR [TTF_Init]");
    }
    std::cout << "SUCCESS [TTF_Init]" << std::endl;

    //Ask for OpenGL version 4.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Colors
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    //Depth buffers
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    //Multisampling
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    //Enable Game Engine Components
    Screen::InitWindow(window_title);
    Graphics::InitOpenGL();
    Audio::InitAudio();
    Physics::InitPhysics();
}

Core::~Core()
{
    Physics::DestroyPhysics();
    Audio::DestroyAudio();
    Screen::DestroyWindow();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Core::Quit()
{
    is_running = false;
}

void Core::Start()
{
    is_running = true;
    Environment::SetEnvironment((int32_t)-1, false);
    Environment::SetEnvironment((int32_t) 0, true);
    while (is_running)
    {
        ENVIRONMENT_CHANGED = true;

        SDL_Event event;
        if (!Input::UpdateInputs(&event))
            is_running = false;

        //Update Physics
        if (Physics::GetWorld())
            Physics::GetWorld()->stepSimulation(Time::delta_time);

        Update();

        Graphics::Render();

        SDL_GL_SwapWindow(Screen::GetWindow());
    }
    Stop();
}

void Core::Stop()
{
    Environment::CleanUp();
}

void Core::Update()
{
    //compute time
    Time::last_frame_time = Time::current_time;
    Time::current_time = SDL_GetTicks();
    Time::delta_time = (Time::current_time - Time::last_frame_time) / 1000.0f;

    std::vector<Entity*> entities = (*Environment::GetEntities());
    for (uint32_t j = 0; j < entities.size(); j++)
    {
        std::vector<Module*> modules = (*entities[j]->GetModules());
        for (uint32_t k = 0; k < modules.size(); k++)
        {
            modules[k]->Update();
            if (!ENVIRONMENT_CHANGED)
                return;
        }
    }

    
}