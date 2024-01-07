#pragma once

#include <render/ProfileViewRender.hpp>

using namespace glimac;

float mimasOrbitalPeriod = 2.9677113 * pow(10, -6);
float mimasSize = 0.00340374377;
float mimasDistance = 0.1855402;

float enceladusOrbitalPeriod = 2.9677113 * pow(10, -6);
float enceladusSize = 0.00432938347;
float enceladusDistance = 0.2380245;

float tethysOrbitalPeriod = 2.9677113 * pow(10, -6);
float tethysSize = 0.00457667868;
float tethysDistance = 0.29466;

float dioneOrbitalPeriod = 2.9677113 * pow(10, -6);
float dioneSize = 0.00964107848;
float dioneDistance = 0.3774022;

float rheaOrbitalPeriod = 2.9677113 * pow(10, -6);
float rheaSize = 0.01313755795;
float rheaDistance = 0.527041;

float titanOrbitalPeriod = 2.9677113 * pow(10, -6);
float titanSize = 0.0442168985;
float titanDistance = 1.2218992;

float hyperionOrbitalPeriod = 2.9677113 * pow(10, -6);
float hyperionSize = 0.00231839258;
float hyperionDistance = 1.5010342;

float iapetusOrbitalPeriod = 2.9677113 * pow(10, -6);
float iapetusSize = 0.01261377296;
float iapetusDistance = 3.5608783;


void saturnViewRender(FilePath applicationPath, 
            SDLWindowManager windowManager, 
            float &speed,
            GLuint vao,
            GLuint vbo,
            GLuint* textures,
            Sphere saturn) {

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
            if(e.type == SDL_QUIT) {
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
                solarSystemProfileRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP1)) {
                std::cout << "Basculement sur Mercure." << std::endl;
                mercuryViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP2)) {
                std::cout << "Basculement sur Venus." << std::endl;
                venusViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP3)) {
                std::cout << "Basculement sur la Terre." << std::endl;
                earthViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP4)) {
                std::cout << "Basculement sur Mars." << std::endl;
                marsViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP5)) {
                std::cout << "Basculement sur Jupiter." << std::endl;
                jupiterViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP7)) {
                std::cout << "Basculement sur Uranus." << std::endl;
                uranusViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP8)) {
                std::cout << "Basculement sur Neptune." << std::endl;
                neptuneViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_KP9)) {
                std::cout << "Basculement sur Pluto." << std::endl;
                plutoViewRender(applicationPath, windowManager, speed, vao, vbo, textures, saturn);
            }
            if(windowManager.isKeyPressed(SDLK_x)) {
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
        glm::mat4 saturnMVMatrix = glm::rotate(initial_MVMAtrix, rotationValue * saturnLengthDay, glm::vec3(0, 1, 0));
        saturnMVMatrix = glm::scale(saturnMVMatrix, glm::vec3(homothetiePlanete, homothetiePlanete, homothetiePlanete));


        glUniformMatrix4fv(uniTextureProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * saturnMVMatrix));
        glUniformMatrix4fv(uniTextureProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(saturnMVMatrix));
        glUniformMatrix4fv(uniTextureProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);

        // Draw Saturn

        glBindTexture(GL_TEXTURE_2D, textures[Saturn]);

        glDrawArrays(GL_TRIANGLES, 0, saturn.getVertexCount());

        // Homothétie mulitiplié par 10 en général pour voir Hyperion.

        // Draw Mimas

        drawSatellite(textures, Mimas, uniTextureProgram, saturn, saturnMVMatrix, mimasOrbitalPeriod, mimasSize, 10 * homothetiePlanete, mimasDistance, 50 * homothetieDistanceSatellite);
    
        // Draw Enceladus

        drawSatellite(textures, Enceladus, uniTextureProgram, saturn, saturnMVMatrix, enceladusOrbitalPeriod, enceladusSize, 10 * homothetiePlanete, enceladusSize, 50 * homothetieDistanceSatellite);

        // Draw Tethys

        drawSatellite(textures, Tethys, uniTextureProgram, saturn, saturnMVMatrix, tethysOrbitalPeriod, tethysSize, homothetiePlanete, tethysDistance, 50 * homothetieDistanceSatellite);
    
        // Draw Dione

        drawSatellite(textures, Dione, uniTextureProgram, saturn, saturnMVMatrix, dioneOrbitalPeriod, dioneSize, homothetiePlanete, dioneDistance, 50 * homothetieDistanceSatellite);

        // Draw Rhea

        drawSatellite(textures, Rhea, uniTextureProgram, saturn, saturnMVMatrix, rheaOrbitalPeriod, rheaSize, homothetiePlanete, rheaDistance, 50 * homothetieDistanceSatellite);
    
        // Draw Titan

        drawSatellite(textures, Titan, uniTextureProgram, saturn, saturnMVMatrix, titanOrbitalPeriod, titanSize, homothetiePlanete, titanDistance, 50 * homothetieDistanceSatellite);
    
        // Draw Hyperion
        
        drawSatellite(textures, Hyperion, uniTextureProgram, saturn, saturnMVMatrix, hyperionOrbitalPeriod, hyperionSize, homothetiePlanete, hyperionDistance, 50 * homothetieDistanceSatellite);

        // Draw Iapetus

        drawSatellite(textures, Iapetus, uniTextureProgram, saturn, saturnMVMatrix, iapetusOrbitalPeriod, iapetusSize, homothetiePlanete, iapetusSize, 50 * homothetieDistanceSatellite);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    // Clear everything after exiting
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, textures);
}