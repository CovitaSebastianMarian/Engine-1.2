#include "Engine/Window.h"
#include "Engine/Model.h"
#include "Engine/Object.h"
#include "Engine/Materials.h"

#define PI 3.14159265359
#define uint unsigned int
using namespace std;

void key(GLFWwindow* window, int key, int scanmode, int state, int mods);

vector<float> pos;
vector <Object> obj;

int main() {
    Window window;
    window.Create(1200, 700, "Engine", nullptr, nullptr);
    window.setIcon("Textures/grass.jpg");
    window.ConfigImGui();
    glfwSetKeyCallback(window.window, key);
    float width, height;
    width = window.width;
    height = window.height;
    
   
    
    Shader shader("Shaders/model.vs", "Shaders/model.fs");

    Model gun("Models/Lowpoly_tree_sample.obj");

    



    while (window.Open()) {
        window.Begin(0.1, 0.1, 0.2);
        width = window.width;
        height = window.height;



        for (unsigned int i = 0; i < gun.meshes.size(); ++i) {
            glUseProgram(shader.ID);
            glm::mat4 projection = glm::perspective<float>(glm::radians(85.0), 1, 0.1, 100);
            shader.setMat4("projection", projection);
            glm::mat4 camera = glm::lookAt<float>(glm::vec3(0, 3, 20), glm::vec3(0, 3, 1), glm::vec3(0, 1, 0));
            shader.setMat4("view", camera);

            glm::mat4 model(1.0);
            model = glm::ortho<float>(0, width, height, 0, width, 0);
            model = glm::translate<float>(model, glm::vec3(width / 2, height / 2, 0));
            model = glm::scale<float>(model, glm::vec3(100, 100, 100));
            model = glm::rotate<float>(model, glm::radians(180.0), glm::vec3(1, 0, 0));
            model = glm::rotate<float>(model, glm::radians(glfwGetTime() * 50), glm::vec3(0, 1, 0));
            shader.setMat4("model", model);


            shader.setVec3("light.lightColor", 0.5, 0.5, 0.5);
            shader.setVec3("light.lightPos", 0, 700, 0);
            shader.setVec3("light.viewPos", 0, 0, 1);


            shader.setVec3("material.ambient", gun.meshes[i].material.ambient);
            shader.setVec3("material.diffuse", gun.meshes[i].material.diffuse);
            shader.setVec3("material.specular", gun.meshes[i].material.specular);
            shader.setFloat("material.shininess", gun.meshes[i].material.shininess);


            

            gun.meshes[i].Draw(shader);
        }        
    
        window.End();
    }
    window.ShutDown();
    return 0;
}


void key(GLFWwindow* window, int key, int scanmode, int state, int mods) {
    if (key == GLFW_KEY_ESCAPE && state == GLFW_PRESS) {
        exit(0);
    }
}