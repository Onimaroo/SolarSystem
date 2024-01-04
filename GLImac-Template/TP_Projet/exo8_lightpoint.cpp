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
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/3D.vs.glsl",
        applicationPath.dirPath() + "shaders/pointlight.fs.glsl"
    );

    program.use();

    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
    GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
    GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    GLint uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
    GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
    
    glEnable(GL_DEPTH_TEST);

    TrackballCamera camera = TrackballCamera();
    glm::mat4 projMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 normalMatrix;
    glm::mat4 viewMatrix;

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

    int currentX = windowManager.getMousePosition().x;
    int currentY = windowManager.getMousePosition().y;
    int lastX = 0;
    int lastY = 0;
    int click = 0;
    
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
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
            
            if(click % 2 == 0) {
                lastY = currentY;
            }
            click++;
        }

        viewMatrix = camera.getViewMatrix();

        auto initial_projMatrix = projMatrix * viewMatrix;
        auto initial_MVMAtrix = MVMatrix * viewMatrix;

        // Rendu
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Pour mettre l'arrière-plan en gris

        glUniform3f(uKd, 0.1, 0.2, 0.3); //Couleur des boules
        glUniform3f(uKs, 0.5, 0.0, 0.0);
        glUniform1f(uShininess, 32.0);
        glm::vec4 LightPos = camera.getViewMatrix() * glm::vec4(1.0, 1.0, 1.0, 0.0);
        glUniform3f(uLightPos_vs, LightPos.x, LightPos.y, LightPos.z);
        glUniform3f(uLightIntensity, 2.0, 2.0, 2.0);


        glm::mat4 earthMVMatrix = glm::rotate(initial_MVMAtrix, windowManager.getTime(), glm::vec3(0, 1, 0));

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * earthMVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, earth.getVertexCount());

        for(int j = 0; j < 32; j++) {
            MVMatrixMoon = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
            MVMatrixMoon = glm::rotate(initial_MVMAtrix, 23.f, rotationAxes[j]); // Rotation
            MVMatrixMoon = glm::rotate(MVMatrixMoon, windowManager.getTime(), glm::vec3(0, 1, 0)); // Rotation
            MVMatrixMoon = glm::translate(MVMatrixMoon, glm::vec3(-2, 0, 0)); // Translation
            MVMatrixMoon = glm::scale(MVMatrixMoon, glm::vec3(0.2, 0.2, 0.2)); // Scale

            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * MVMatrixMoon));
            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixMoon));

            glDrawArrays(GL_TRIANGLES, 0, earth.getVertexCount());
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();

    }
    glDeleteBuffers(1, &vbo);

    return EXIT_SUCCESS;
}
