#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

struct EarthProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uEarthTexture;
    GLint uCloudTexture;

    EarthProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uEarthTexture = glGetUniformLocation(m_Program.getGLId(), "uEarthTexture");
        uCloudTexture = glGetUniformLocation(m_Program.getGLId(), "uCloudTexture");
    }
};

struct MoonProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    MoonProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
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

std::unique_ptr<Image> pImageEarth = loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_Projet/textures/EarthMap.jpg");
    std::unique_ptr<Image> pImageMoon = loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_Projet/textures/MoonMap.jpg");
    std::unique_ptr<Image> pImageCloud = loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_Projet/textures/CloudMap.jpg");

    if(pImageEarth == NULL || pImageMoon == NULL) {
        std::cout << "Couldn't find image." << std::endl;
    }

    GLuint textures[3];
    
    glGenTextures(3, textures);

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageEarth->getWidth(), pImageEarth->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageEarth->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageMoon->getWidth(), pImageMoon->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageMoon->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, textures[2]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImageCloud->getWidth(), pImageCloud->getHeight(), 0, GL_RGBA, GL_FLOAT, pImageCloud->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    FilePath applicationPath(argv[0]);
    EarthProgram earthProgram(applicationPath);
    MoonProgram moonProgram(applicationPath);

    glEnable(GL_DEPTH_TEST);

    glm::mat4 projMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 normalMatrix;

    projMatrix = glm::perspective(glm::radians(70.f), 800.f / 600.f , 0.1f, 100.f);
    MVMatrix = glm::translate(glm:: mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
    normalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glm::mat4 MVMatrixMoon;
    
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
            INITIALIZATION CODE
     *********************************/

    Sphere earth(1, 32, 16);

    std::cout << "Number of vertexes: " << earth.getVertexCount() << std::endl;

    // Création du VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Remplissage du VBO
    const ShapeVertex* vertices = earth.getDataPointer();

    glBufferData(GL_ARRAY_BUFFER, earth.getVertexCount() * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);

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

    std::vector<glm::vec3> rotationAxes(32);

    for(int i = 0; i < 32; i++) {
        rotationAxes[i] = glm::sphericalRand(1.f);
    }
    
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        // Rendu
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Pour mettre l'arrière-plan en gris

        earthProgram.m_Program.use();

        glUniform1i(earthProgram.uEarthTexture, 0);
        glUniform1i(earthProgram.uCloudTexture, 1);

        glm::mat4 earthMVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));

        glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * earthMVMatrix));
        glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        // glActiveTexture(GL_TEXTURE);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[2]);

        glDrawArrays(GL_TRIANGLES, 0, earth.getVertexCount());

        glActiveTexture(GL_TEXTURE0);
        
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, textures[1]);
	
        moonProgram.m_Program.use();

        for(int j = 0; j < 32; j++) {
            MVMatrixMoon = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
            MVMatrixMoon = glm::rotate(MVMatrixMoon, 23.f, rotationAxes[j]); // Rotation
            MVMatrixMoon = glm::rotate(MVMatrixMoon, windowManager.getTime(), glm::vec3(0, 1, 0)); // Rotation
            MVMatrixMoon = glm::translate(MVMatrixMoon, glm::vec3(-2, 0, 0)); // Translation
            MVMatrixMoon = glm::scale(MVMatrixMoon, glm::vec3(0.2, 0.2, 0.2)); // Scale
            glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * MVMatrixMoon));
            glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixMoon));

            glDrawArrays(GL_TRIANGLES, 0, earth.getVertexCount());
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();

    }
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, textures);

    return EXIT_SUCCESS;
}
