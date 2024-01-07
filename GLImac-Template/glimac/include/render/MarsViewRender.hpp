#pragma once

#include <render/SolarSystemViewRender.hpp>

using namespace glimac;

float phobosOrbitalPeriod = 2.9677113 * pow(10, -6);
float phobosSize = 0.2724;
float phobosDistance = 0.009378;

float demiosOrbitalPeriod = 2.9677113 * pow(10, -6);
float demiosSize = 0.2724;
float demiosDistance = 0.023459;

void marsViewRender(FilePath applicationPath, 
            SDLWindowManager windowManager, 
            float &speed,
            GLuint vao,
            GLuint vbo,
            GLuint* textures,
            Sphere mars) {

    bool done = false;

    UniTexturePlanetProgram uniTextureProgram(applicationPath);
    MultiTextureProgram multiTextureProgram(applicationPath);  

    while(!done) {
        currentSecond = windowManager.getTime();
        secondSpeed = speed * (currentSecond - prevSecond);
        prevSecond = currentSecond;

        rotationValue += secondSpeed;

        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT || windowManager.isKeyPressed(SDLK_x)) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_RIGHT)) {
                speed *= 2;     
                std::cout << "Vitesse accélérée. Vitesse désormais à " << speed << "x." << std::endl;
            }
            if(windowManager.isKeyPressed(SDLK_LEFT)) {
                speed /= 2;
                std::cout << "Vitesse ralentie. Vitesse désormais à " << speed << "x." << std::endl;
            }
            if(windowManager.isKeyPressed(SDLK_UP)) {
                std::cout << "Basculement sur la vue écliptique." << std::endl;
                camera = FreeflyCamera();
                camera.rotateLeft(90);
            }
            if(windowManager.isKeyPressed(SDLK_DOWN)) {
                std::cout << "Basculement sur la vue de profil." << std::endl;
                camera = FreeflyCamera();
            }
            if(windowManager.isKeyPressed(SDLK_KP0)) {
                std::cout << "Basculement sur le système solaire." << std::endl;
                solarSystemProfileRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP1)) {
                std::cout << "Basculement sur Mercure." << std::endl;
                mercuryViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP2)) {
                std::cout << "Basculement sur Venus." << std::endl;
                venusViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP3)) {
                std::cout << "Basculement sur la Terre." << std::endl;
                earthViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP5)) {
                std::cout << "Basculement sur Jupiter." << std::endl;
                jupiterViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP6)) {
                std::cout << "Basculement sur Saturne." << std::endl;
                saturnViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP7)) {
                std::cout << "Basculement sur Uranus." << std::endl;
                uranusViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP8)) {
                std::cout << "Basculement sur Neptune." << std::endl;
                neptuneViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_KP9)) {
                std::cout << "Basculement sur Pluto." << std::endl;
                plutoViewRender(applicationPath, windowManager, speed, vao, vbo, textures, mars);
            }
            if(windowManager.isKeyPressed(SDLK_w)) {
                std::cout << "Nombre de secondes écoulés:" << rotationValue << std::endl;
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

        uniTextureProgram.m_Program.use();
        glm::mat4 marsMVMatrix = glm::rotate(initial_MVMAtrix, rotationValue * marsLengthDay, glm::vec3(0, 1, 0));
        marsMVMatrix = glm::scale(marsMVMatrix, glm::vec3(homothetiePlanete, homothetiePlanete, homothetiePlanete));


        glUniformMatrix4fv(uniTextureProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * marsMVMatrix));
        glUniformMatrix4fv(uniTextureProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(marsMVMatrix));
        glUniformMatrix4fv(uniTextureProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);

        // Draw Mars

        glBindTexture(GL_TEXTURE_2D, textures[Mars]);

        glDrawArrays(GL_TRIANGLES, 0, mars.getVertexCount());

        // Draw Phobos

        drawSatellite(textures, Phobos, uniTextureProgram, mars, marsMVMatrix, phobosOrbitalPeriod, phobosSize, 1, phobosDistance, 40 * homothetieDistanceSatellite);
    
        // Draw Demios

        drawSatellite(textures, Demios, uniTextureProgram, mars, marsMVMatrix, demiosOrbitalPeriod, demiosSize, 1, demiosDistance, 40 * homothetieDistanceSatellite);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    // Clear everything after exiting
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, textures);
}