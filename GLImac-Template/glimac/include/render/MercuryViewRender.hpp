#pragma once

#include <render/ProfileViewRender.hpp>

using namespace glimac;

void mercuryViewRender(FilePath applicationPath, 
            SDLWindowManager windowManager, 
            float &speed,
            GLuint vao,
            GLuint vbo,
            GLuint* textures,
            Sphere mercury) {

    bool done = false;

    UniTexturePlanetProgram mercuryProgram(applicationPath);

    std::vector<glm::vec3> rotationAxes(32);

    for(int i = 0; i < 32; i++) {
        rotationAxes[i] = glm::sphericalRand(1.f);
    }

    while(!done) {
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
            if(windowManager.isKeyPressed(SDLK_m)) {
                std::cout << "Basculement sur le système solaire." << std::endl;
                solarSystemProfileRender(applicationPath, windowManager, speed, vao, vbo, textures, mercury);
            }
            if(windowManager.isKeyPressed(SDLK_e)) {
                std::cout << "Basculement sur la Terre." << std::endl;
                earthViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mercury);
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

        glm::mat4 viewMatrix = camera.getViewMatrix();

        auto initial_projMatrix = projMatrix * viewMatrix;
        auto initial_MVMAtrix = MVMatrix * viewMatrix;

        // Rendu
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Pour mettre l'arrière-plan en gris

        mercuryProgram.m_Program.use();

        glm::mat4 mercuryMVMatrix = glm::rotate(initial_MVMAtrix, speed * windowManager.getTime(), glm::vec3(0, 1, 0));

        glUniformMatrix4fv(mercuryProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * mercuryMVMatrix));
        glUniformMatrix4fv(mercuryProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(mercuryMVMatrix));
        glUniformMatrix4fv(mercuryProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        // glActiveTexture(GL_TEXTURE);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[Mercury]);

        glDrawArrays(GL_TRIANGLES, 0, mercury.getVertexCount());
        
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();

    }

    // Clear everything after exiting
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, textures);
}