Core::Core()
{
    WIDTH = 1024;
    HEIGHT = 768;
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
    window = SDL_CreateWindow(
        "Core Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,
        768,
        SDL_WINDOW_OPENGL
    );
    
    context = SDL_GL_CreateContext(window);

    InitOpenGl();
}
Core::~Core()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Core::InitOpenGl()
{
	//Smooth shading
	glShadeModel(GL_SMOOTH);
	
	//Set clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear depth buffer
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

	//the depth test to go
	glDepthFunc(GL_LEQUAL);

	//Enable Culling
	//glEnable(GL_CULL_FACE);

	//Back face culling
	//glCullFace(GL_BACK);

	//GL_CCW for counter clock-wise
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

void Core::Start()
{
    current_time = 0;
    prev_time = 0;
    bool run = true;
    while (run)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
                run = false;
            if (event.type == SDL_KEYDOWN)
                keys_pressed[event.key.keysym.sym] = true;
            if (event.type == SDL_KEYUP)
                keys_pressed[event.key.keysym.sym] = false;

            Input(&event);
        }

        Update();

        Render();

        SDL_GL_SwapWindow(window);
    }
}

void Core::Update()
{
    //Mouse
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouse_position = glm::vec2(static_cast<float>(x), static_cast<float>(y));
    SDL_GetRelativeMouseState(&x, &y);
    mouse_delta = glm::vec2(static_cast<float>(x), static_cast<float>(y));

    //Time
    prev_time = current_time;
    current_time = SDL_GetTicks();
    delta_time = (current_time - prev_time) / 1000.0f;

    
    //Camera
    for (auto i = world->cameras.begin(); i != world->cameras.end(); ++i)
	{
		for (std::shared_ptr<NonRenderingModule> j : (*i)->GetModules())
            j->Update();
	}
    //Light
    for (auto i = world->lights.begin(); i != world->lights.end(); ++i)
	{
		for (std::shared_ptr<NonRenderingModule> j : (*i)->GetModules())
            j->Update();
	}
    //Entities
    for (auto i = world->entities.begin(); i != world->entities.end(); ++i)
	{
		for (std::shared_ptr<Module> j : (*i)->GetModules())
            j->Update();
	}
}

void Core::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto camera_ptr = world->cameras.begin(); camera_ptr < world->cameras.end(); camera_ptr++)
    {
        //Setup viewport
        glViewport((int)((*camera_ptr)->viewport_x * WIDTH), (int)((*camera_ptr)->viewport_y * HEIGHT), (GLsizei)((*camera_ptr)->viewport_size_x * WIDTH), (GLsizei)((*camera_ptr)->viewport_size_y * HEIGHT));
        for (auto i = world->entities.begin(); i != world->entities.end(); ++i)
        {
            for (std::shared_ptr<Module> j : (*i)->GetModules())
                j->Render((*camera_ptr), world->lights);
        }
    }
}

void Core::Input(SDL_Event* e)
{
    //Camera
    for (auto i = world->cameras.begin(); i != world->cameras.end(); ++i)
    {
        for (std::shared_ptr<NonRenderingModule> j : (*i)->GetModules())
            j->Input(e);
    }
    //Light
    for (auto i = world->lights.begin(); i != world->lights.end(); ++i)
    {
        for (std::shared_ptr<NonRenderingModule> j : (*i)->GetModules())
            j->Input(e);
    }
    //Entities
    for (auto i = world->entities.begin(); i != world->entities.end(); ++i)
	{
		for (std::shared_ptr<Module> j : (*i)->GetModules())
            j->Input(e);
	}
}

void Core::ChangeResolution(int w, int h, bool fullscreen)
{
    WIDTH = w;
    HEIGHT = h;
    SDL_SetWindowSize(window, WIDTH, HEIGHT);
    if (fullscreen)
        SDL_SetWindowFullscreen(window, SDL_TRUE);
    else
        SDL_SetWindowFullscreen(window, SDL_FALSE);
}