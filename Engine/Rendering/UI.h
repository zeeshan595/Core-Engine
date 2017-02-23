#ifndef _UI
#define _UI

class UI
{
public:
    glm::vec4 rect;
    float rotation;
    std::shared_ptr<Texture> texture;

    UI(std::shared_ptr<Texture> tex, glm::vec4 ui_rect);
    ~UI();
    
    static void PreRender();
    void Render();

    static std::shared_ptr<UI> CreateUI(std::shared_ptr<Texture> tex, glm::vec4 ui_rect){
        std::shared_ptr<UI> myUI = std::shared_ptr<UI>(new UI(tex, ui_rect));
        UI::uis.push_back(myUI);
        return myUI;
    }
    static GLuint* GetVAO(){
        return &UI::VAO;
    }
    static GLuint* GetVBO(){
        return &UI::VAO;
    }
    static GLuint* GetEBO(){
        return &UI::VAO;
    }
    static std::vector<std::shared_ptr<UI>>* GetUIs(){
        return &uis;
    }

private:
    static std::shared_ptr<Shader> shader;
    static GLuint VAO;
    static GLuint VBO;
    static GLuint EBO;
    static std::vector<glm::vec2> vertices;
    static std::vector<int> indices;
    static std::vector<std::shared_ptr<UI>> uis;
    static int ui_amount;

    static void GenerateBuffers();
    glm::mat4x4 GetTransformationMatrix();
};

std::shared_ptr<Shader> UI::shader;
GLuint UI::VAO;
GLuint UI::VBO;
GLuint UI::EBO;
std::vector<glm::vec2> UI::vertices;
std::vector<int> UI::indices;
std::vector<std::shared_ptr<UI>> UI::uis;
int UI::ui_amount = 0;

#include "UI.c"

#endif