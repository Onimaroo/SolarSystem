#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <GL/glew.h>
#include <iostream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace glimac;

class Application {
    public:
        Sphere planet = Sphere(1, 32, 16);
        SDLWindowManager _windowManager = SDLWindowManager(800, 600, "GLImac");

        GLuint vao;
        GLuint vbo;

        glm::mat4 projMatrix;
        glm::mat4 MVMatrix;
        glm::mat4 normalMatrix;
        glm::mat4 viewMatrix;

        GLuint textures[20];

        glm::mat4 sunMVMatrix;
        glm::mat4 mercuryMVMatrix;
        glm::mat4 venusMVMatrix;
        glm::mat4 earthMVMatrix;
        glm::mat4 marsMVMatrix; 

        Application(char** argv) {

            GLenum glewInitError = glewInit();
            if(GLEW_OK != glewInitError) {
                std::cerr << glewGetErrorString(glewInitError) << std::endl;
            }

            std::vector<std::unique_ptr<Image>> image_array;

            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/SunMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/MercuryMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/VenusMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/EarthMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/MarsMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/JupiterMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/SaturnMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/UranusMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/NeptuneMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/PlutoMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/MoonMap.jpg"));
            image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/CloudMap.jpg"));

            for(int i = 0; i < image_array.size(); i++) {
                if(image_array[i] == NULL) {
                    std::cout << "Couldn't find image." << std::endl;
                }
            }

            glGenTextures(image_array.size(), textures);

            for(int i = 0; i < image_array.size(); i++) {

                glBindTexture(GL_TEXTURE_2D, textures[i]);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_array[i]->getWidth(), image_array[i]->getHeight(), 0, GL_RGBA, GL_FLOAT, image_array[i]->getPixels());

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glBindTexture(GL_TEXTURE_2D, 0);

            }

            glEnable(GL_DEPTH_TEST);
            
            projMatrix = glm::perspective(glm::radians(70.f), 800.f / 600.f , 0.1f, 100.f);
            MVMatrix = glm::translate(glm:: mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
            normalMatrix = glm::transpose(glm::inverse(MVMatrix));


            /*********************************
                    INITIALIZATION CODE
            *********************************/

            std::cout << "Number of vertexes: " << planet.getVertexCount() << std::endl;

            // Création du VBO
            glGenBuffers(1, &vbo);

            // Binding du VBO
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            // Remplissage du VBO
            const ShapeVertex* vertices = planet.getDataPointer();

            glBufferData(GL_ARRAY_BUFFER, planet.getVertexCount() * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);


            // Débinding du VBO
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Création du VAO
            glGenVertexArrays(1, &vao);

            // Binding du VAO
            glBindVertexArray(vao);

            // Activation de l'attribut "position", "normal" et "texCoords" des deux shaders
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            // Spécification des attributs de vertex
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // Débinding du VAO
            glBindVertexArray(0);
        }
};