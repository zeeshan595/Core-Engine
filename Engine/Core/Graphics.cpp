void Graphics::Render()
{
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    uint32_t width, height;
    Screen::GetDisplayResolution(width, height);
    glScissor(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<Camera*> cameras = (*Environment::GetCameras());
    for (uint32_t i = 0; i < cameras.size(); i++)
    {
        cameras[i]->GetViewport(viewport.x, viewport.y, viewport.z, viewport.w);
        viewport.x *= width;
        viewport.y *= height;
        viewport.z *= width;
        viewport.w *= height;
        glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
        glScissor(viewport.x, viewport.y, viewport.z, viewport.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Environment::GetSkybox()->Render(cameras[i]);

        std::vector<Entity*> entities = (*Environment::GetEntities());
        for (uint32_t j = 0; j < entities.size(); j++)
        {
            std::vector<Module*> modules = (*entities[j]->GetModules());
            for (uint32_t k = 0; k < modules.size(); k++)
            {
                modules[k]->Render(cameras[i]);
            }
        }
    }
}

void Graphics::InitOpenGL()
{
    glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);

    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//Turn on the best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << glewGetErrorString(err) << std::endl;
        throw std::runtime_error("ERROR [glewInit]");
    }
    std::cout << "SUCCESS [glewInit]" << std::endl;
}