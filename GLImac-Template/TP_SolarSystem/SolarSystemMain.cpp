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

enum PlanetTexture { Sun = 0,
                     Mercury = 1, 
                     Venus = 2, 
                     Earth = 3, 
                     Mars = 4, 
                     Jupiter = 5, 
                     Saturn = 6, 
                     Uranus = 7, 
                     Neptune = 8, 
                     Pluto = 9, 
                     Moon = 10, 
                     Cloud = 11
                   };

struct UniTexturePlanetProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    UniTexturePlanetProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

struct MultiTextureProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uFirstTexture;
    GLint uSecondTexture;

    MultiTextureProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uFirstTexture = glGetUniformLocation(m_Program.getGLId(), "uFirstTexture");
        uSecondTexture = glGetUniformLocation(m_Program.getGLId(), "uSecondTexture");
    }
};

int main(int argc, char** argv) {

    // uint32_t windowWidth = 800;
    // uint32_t windowHeight = 600;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
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

    GLuint textures[image_array.size()];
    
    glGenTextures(image_array.size(), textures);

    for(int i = 0; i < image_array.size(); i++) {

        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_array[i]->getWidth(), image_array[i]->getHeight(), 0, GL_RGBA, GL_FLOAT, image_array[i]->getPixels());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

    }

    FilePath applicationPath(argv[0]);
    UniTexturePlanetProgram sunProgram(applicationPath);
    UniTexturePlanetProgram mercuryProgram(applicationPath);
    UniTexturePlanetProgram venusProgram(applicationPath);
    MultiTextureProgram earthProgram(applicationPath);  
    UniTexturePlanetProgram marsProgram(applicationPath);

    glEnable(GL_DEPTH_TEST);

    FreeflyCamera camera = FreeflyCamera();
    glm::mat4 projMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 normalMatrix;
    glm::mat4 viewMatrix;

    projMatrix = glm::perspective(glm::radians(70.f), 800.f / 600.f , 0.1f, 100.f);
    MVMatrix = glm::translate(glm:: mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
    normalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glm::mat4 mercuryMVMatrix;
    glm::mat4 venusMVMatrix;
    glm::mat4 earthMVMatrix;
    glm::mat4 marsMVMatrix;
    
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
            INITIALIZATION CODE
     *********************************/

    Sphere sun(1, 32, 16);

    std::cout << "Number of vertexes: " << sun.getVertexCount() << std::endl;

    // Création du VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Remplissage du VBO
    const ShapeVertex* vertices = sun.getDataPointer();

    glBufferData(GL_ARRAY_BUFFER, sun.getVertexCount() * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);

    // Débinding du VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Création du VAO
    GLuint vao;
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

    // Application loop:
    bool done = false;

    int currentX = windowManager.getMousePosition().x;
    int currentY = windowManager.getMousePosition().y;
    int lastX = 0;
    int lastY = 0;
    int click = 0;
    float speed = 1;
    
    camera.rotateLeft(90); // Pour commencer dans la vue de dessus

    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_RIGHT)) {
                speed *= 1.25;     
                std::cout << "Vitesse accélérée. Vitesse désormais à " << speed << "x." << std::endl;
            }
            if(windowManager.isKeyPressed(SDLK_LEFT)) {
                speed /= 1.25;
                std::cout << "Vitesse ralentie. Vitesse désormais à " << speed << "x." << std::endl;
            }
        }

        if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
            currentY = windowManager.getMousePosition().y;
            camera.rotateLeft(currentY - lastY);
            if(click % 2 == 0) {
                lastY = currentY;
            }

            currentX = windowManager.getMousePosition().x;
            camera.rotateUp(currentX - lastX);
            if(click % 2 == 0) {
                lastX = currentX;
            }

            click++;
        }
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_MIDDLE)) {
            currentY = windowManager.getMousePosition().y;
            camera.moveFront(currentY - lastY);
            
            lastY = currentY;
        }
        if(windowManager.isKeyPressed(SDLK_z)) {
            camera.moveFront(0.1);
        }
        if(windowManager.isKeyPressed(SDLK_q)) {
            camera.moveLeft(0.1);
        }
        if(windowManager.isKeyPressed(SDLK_s)) {
            camera.moveFront(-0.1);       
        }
        if(windowManager.isKeyPressed(SDLK_d)) {
            camera.moveLeft(-0.1);
        }

        viewMatrix = camera.getViewMatrix();

        auto initial_projMatrix = projMatrix * viewMatrix;
        auto initial_MVMAtrix = MVMatrix * viewMatrix;

        // Rendu
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Pour mettre l'arrière-plan en gris

        sunProgram.m_Program.use();

        glm::mat4 sunMVMatrix = glm::rotate(initial_MVMAtrix, speed * windowManager.getTime(), glm::vec3(0, 1, 0));

        glUniformMatrix4fv(sunProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * sunMVMatrix));
        glUniformMatrix4fv(sunProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(sunMVMatrix));
        glUniformMatrix4fv(sunProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);

        // Draw the Sun

        glBindTexture(GL_TEXTURE_2D, textures[Sun]);

        glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

        glBindTexture(GL_TEXTURE_2D, 0);

        // Draw Mercury

        glBindTexture(GL_TEXTURE_2D, textures[Mercury]);

        mercuryProgram.m_Program.use();
        
        mercuryMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        mercuryMVMatrix = glm::rotate(initial_MVMAtrix, speed * windowManager.getTime(), glm::vec3(0, 1, 0));
        mercuryMVMatrix = glm::translate(mercuryMVMatrix, glm::vec3(-2, 0, 0));
        mercuryMVMatrix = glm::scale(mercuryMVMatrix, glm::vec3(0.2, 0.2, 0.2));
        glUniformMatrix4fv(mercuryProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * mercuryMVMatrix));
        glUniformMatrix4fv(sunProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(mercuryMVMatrix));

        glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

        glBindTexture(GL_TEXTURE_2D, 0);

        // Draw Venus

        glBindTexture(GL_TEXTURE_2D, textures[Venus]);

        venusProgram.m_Program.use();
        
        venusMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
        venusMVMatrix = glm::rotate(initial_MVMAtrix, speed * (-windowManager.getTime()), glm::vec3(0, 1, 0));
        venusMVMatrix = glm::translate(venusMVMatrix, glm::vec3(-3.5, 0, 0));
        venusMVMatrix = glm::scale(venusMVMatrix, glm::vec3(0.5, 0.5, 0.5));
        glUniformMatrix4fv(venusProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * venusMVMatrix));
        glUniformMatrix4fv(sunProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(venusMVMatrix));

        glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

        glBindTexture(GL_TEXTURE_2D, 0);

        // Draw the Earth

        glBindTexture(GL_TEXTURE_2D, textures[Earth]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[Cloud]);
	
        earthProgram.m_Program.use();

        glUniform1i(earthProgram.uFirstTexture, 0);
        glUniform1i(earthProgram.uSecondTexture, 1);

        earthMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
        earthMVMatrix = glm::rotate(initial_MVMAtrix, speed * windowManager.getTime(), glm::vec3(0, 1, 0)); // Rotation around the orbit
        earthMVMatrix = glm::translate(earthMVMatrix, glm::vec3(-6, 0, 0)); // Translation
        earthMVMatrix = glm::scale(earthMVMatrix, glm::vec3(0.6, 0.6, 0.6)); // Scale
        // earthMVMatrix = glm::rotate(earthMVMatrix, 0.100f * SDL_GetTicks(), glm::vec3(0, 1, 0)); // Rotation around itself
        glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * earthMVMatrix));
        glUniformMatrix4fv(sunProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));

        glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();

    }

    // Clear everything after exiting
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, textures);

    return EXIT_SUCCESS;
}
