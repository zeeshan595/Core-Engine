Core::Core(std::string window_title)
{
    //SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR [SDL_Init]: " << SDL_GetError() << std::endl;
        return;
    }
    std::cout << "SUCCESS [SDL_Init]" << std::endl;

    //SDL Image
    int image_init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int return_init_flags = IMG_Init(image_init_flags);
    if ((return_init_flags & image_init_flags) != image_init_flags)
    {
        std::cout << "ERROR [IMG_Init]: " << IMG_GetError() << std::endl;
        return;
    }
    std::cout << "SUCCESS [IMG_Init]" << std::endl;

    //TTF Font
    if (TTF_Init() == -1)
    {
        std::cout << "ERROR [TTF_Init]: " << TTF_GetError() << std::endl;
        return;
    }
    std::cout << "SUCCESS [TTF_Init]" << std::endl;

    //ASk for version 4.2 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Create Window
    Screen::window = SDL_CreateWindow(
        window_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Screen::width,
        Screen::height,
        SDL_WINDOW_OPENGL
    );
    
    context = SDL_GL_CreateContext(Screen::window);

    InitOpenGL();
}

Core::~Core()
{
    //Delete ui data
    glDeleteBuffers(1, UIMesh::GetEBO());
    glDeleteBuffers(1, UIMesh::GetVBO());
    glDeleteVertexArrays(1, UIMesh::GetVAO());

    //Delete skybox data
    glDeleteBuffers(1, Skybox::GetEBO());
    glDeleteBuffers(1, Skybox::GetVBO());
    glDeleteVertexArrays(1, Skybox::GetVAO());

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(Screen::window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Core::InitOpenGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_CUBE_MAP);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	//Turn on the best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "ERROR [glewInit]: " << glewGetErrorString(err) << std::endl;
        return;
    }
    std::cout << "SUCCESS [glewInit]" << std::endl;
}

void Core::Quit()
{
    is_running = false;
}

void Core::Start()
{
    if (Environment::environments.size() < 1)
    {
        std::cout << "No Environment Loaded. Exiting Core Engine" << std::endl;
        is_running = false;
    }
    else
        is_running = true;

    Environment::current_environment = 0;
    StartModules();
    while(is_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {            
            Input(&event);
        }

        Update();

        Render();

        SDL_GL_SwapWindow(Screen::window);
    }
}

void Core::Input(SDL_Event* e)
{
    //Update Mouse Input
    int x, y;
    SDL_GetMouseState(&x, &y);
    Input::mouse_position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
    SDL_GetRelativeMouseState(&x, &y);
    Input::mouse_delta = glm::vec2(static_cast<float>(x), static_cast<float>(y));

    if (e->type == SDL_QUIT || e->type == SDL_WINDOWEVENT_CLOSE)
        is_running = false;

    Input::keys_down.clear();
    Input::keys_up.clear();

    if (e->type == SDL_KEYDOWN)
    {
        if (!Input::keys[e->key.keysym.sym])
            Input::keys_down[e->key.keysym.sym] = true;

        Input::keys[e->key.keysym.sym] = true;
    }
    if (e->type == SDL_KEYUP)
    {
        Input::keys[e->key.keysym.sym] = true;
        Input::keys[e->key.keysym.sym] = false;
    }
}

void Core::StartModules()
{
    //Cameras
    for (auto i = (*Environment::environments[Environment::current_environment]->GetCameras()).begin(); i != (*Environment::environments[Environment::current_environment]->GetCameras()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Start();
        }
    }
    //Lights
    for (auto i = (*Environment::environments[Environment::current_environment]->GetLights()).begin(); i != (*Environment::environments[Environment::current_environment]->GetLights()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Start();
        }
    }
    //Entities
    for (auto i = (*Environment::environments[Environment::current_environment]->GetEntities()).begin(); i != (*Environment::environments[Environment::current_environment]->GetEntities()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Start();
        }
    }
}

void Core::Update()
{
    //compute time
    Time::last_frame_time = Time::current_time;
    Time::current_time = SDL_GetTicks();
    Time::delta_time = (Time::current_time - Time::last_frame_time) / 1000.0f;

    //Cameras
    for (auto i = (*Environment::environments[Environment::current_environment]->GetCameras()).begin(); i != (*Environment::environments[Environment::current_environment]->GetCameras()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Update();
        }
    }
    //Lights
    for (auto i = (*Environment::environments[Environment::current_environment]->GetLights()).begin(); i != (*Environment::environments[Environment::current_environment]->GetLights()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Update();
        }
    }
    //Entities
    for (auto i = (*Environment::environments[Environment::current_environment]->GetEntities()).begin(); i != (*Environment::environments[Environment::current_environment]->GetEntities()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Update();
        }
    }
}

void Core::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto i = (*Environment::environments[Environment::current_environment]->GetCameras()).begin(); i != (*Environment::environments[Environment::current_environment]->GetCameras()).end(); ++i)
    {
        glViewport((int)((*i)->viewport.x * Screen::width), (int)((*i)->viewport.y * Screen::height), (int)((*i)->viewport.z * Screen::width), (int)((*i)->viewport.w * Screen::height));
        
        //Render Skybox
        Environment::environments[Environment::current_environment]->skybox->Render((*i));

        //Cameras
        for (auto j = (*Environment::environments[Environment::current_environment]->GetCameras()).begin(); j != (*Environment::environments[Environment::current_environment]->GetCameras()).end(); ++j)
        {
            if (j != i)
            {
                for (std::shared_ptr<Module> module : (*j)->GetModules())
                {
                    module->Render((*i), Environment::environments[Environment::current_environment]->GetLights());
                }
            }
        }
        //Lights
        for (auto j = (*Environment::environments[Environment::current_environment]->GetLights()).begin(); j != (*Environment::environments[Environment::current_environment]->GetLights()).end(); ++j)
        {
            for (std::shared_ptr<Module> module : (*j)->GetModules())
            {
                module->Render((*i), Environment::environments[Environment::current_environment]->GetLights());
            }
        }
        //Entities
        for (auto j = (*Environment::environments[Environment::current_environment]->GetEntities()).begin(); j != (*Environment::environments[Environment::current_environment]->GetEntities()).end(); ++j)
        {
            for (std::shared_ptr<Module> module : (*j)->GetModules())
            {
                module->Render((*i), Environment::environments[Environment::current_environment]->GetLights());
            }
        }
    }
}