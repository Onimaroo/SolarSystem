#pragma once

#include <render/ProfileViewRender.hpp>

using namespace glimac;

void earthViewRender(FilePath applicationPath, 
            SDLWindowManager windowManager, 
            float &speed,
            GLuint vao,
            GLuint vbo,
            GLuint* textures,
            Sphere earth) {

    bool done = false;

    MultiTextureProgram earthProgram(applicationPath);  
    UniTexturePlanetProgram moonProgram(applicationPath);

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
            if(windowManager.isKeyPressed(SDLK_e)) {
                std::cout << "Basculement sur le système solaire." << std::endl;
                solarSystemProfileRender(applicationPath, windowManager, speed, vao, vbo, textures, earth);
            }
            if(windowManager.isKeyPressed(SDLK_m)) {
                std::cout << "Basculement sur Mercure." << std::endl;
                mercuryViewRender(applicationPath, windowManager, speed, vao, vbo, textures, earth);
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

        earthProgram.m_Program.use();

        glUniform1i(earthProgram.uFirstTexture, 0);
        glUniform1i(earthProgram.uSecondTexture, 1);

        glm::mat4 earthMVMatrix = glm::rotate(initial_MVMAtrix, speed * windowManager.getTime(), glm::vec3(0, 1, 0));

        glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * earthMVMatrix));
        glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(earthMVMatrix));
        glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        // glActiveTexture(GL_TEXTURE);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[Earth]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[Cloud]);

        glDrawArrays(GL_TRIANGLES, 0, earth.getVertexCount());

        glActiveTexture(GL_TEXTURE0);
        
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindTexture(GL_TEXTURE_2D, textures[Moon]);
	
        moonProgram.m_Program.use();

        glm::mat4 MVMatrixMoon;

        for(int j = 0; j < 32; j++) {
            MVMatrixMoon = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
            MVMatrixMoon = glm::rotate(initial_MVMAtrix, 23.f, rotationAxes[j]); // Rotation
            MVMatrixMoon = glm::rotate(MVMatrixMoon, speed * windowManager.getTime(), glm::vec3(0, 1, 0)); // Rotation
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

    // Clear everything after exiting
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, textures);
}