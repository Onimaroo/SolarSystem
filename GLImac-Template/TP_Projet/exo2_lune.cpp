#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

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

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
                                  applicationPath.dirPath() + "shaders/" + argv[2]);
    program.use();

    GLint MVPLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint MVLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint normalLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

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

    for(int i = 0; i <= 32; i++) {
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

        glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(projMatrix * MVMatrix));
        glUniformMatrix4fv(MVLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(normalLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, earth.getVertexCount());

        for(int j = 0; j < 32; j++) {
            MVMatrixMoon = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
            MVMatrixMoon = glm::rotate(MVMatrixMoon, 23.f, rotationAxes[j]); // Rotation
            MVMatrixMoon = glm::rotate(MVMatrixMoon, windowManager.getTime(), glm::vec3(0, 1, 0)); // Rotation
            MVMatrixMoon = glm::translate(MVMatrixMoon, glm::vec3(-2, 0, 0)); // Translation
            MVMatrixMoon = glm::scale(MVMatrixMoon, glm::vec3(0.2, 0.2, 0.2)); // Scale
            glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(projMatrix * MVMatrixMoon));
            glUniformMatrix4fv(MVLocation, 1, GL_FALSE, glm::value_ptr(MVMatrixMoon));

            glDrawArrays(GL_TRIANGLES, 0, earth.getVertexCount());
        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
