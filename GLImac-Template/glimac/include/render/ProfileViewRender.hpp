#pragma once

#include <render/PlanetDatabase.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <cmath>

using namespace glimac;

// Event loop:
float currentSecond = 0;
float prevSecond = 0;
float secondSpeed = 0;

float rotationValue = 0;

int currentX = 0;
int currentY = 0;
int lastX = 0;
int lastY = 0;
int click = 0;

FreeflyCamera camera = FreeflyCamera();

glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 800.f / 600.f , 0.1f, 100.f);
glm::mat4 MVMatrix = glm::translate(glm:: mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
glm::mat4 normalMatrix = glm::transpose(glm::inverse(MVMatrix));

void mercuryViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere mercury);
void venusViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere venus);
void earthViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere earth);
void marsViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere mars);
void jupiterViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere jupiter);
void saturnViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere saturn);
void uranusViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere uranus);
void neptuneViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere neptune);
void plutoViewRender(FilePath applicationPath, SDLWindowManager windowManager, float &speed, GLuint vao, GLuint vbo, GLuint* textures, Sphere pluto);

void drawUniTexturePlanet(GLuint* textures,
            PlanetTexture name, 
            const UniTexturePlanetProgram& uniTextureProgram, 
            Sphere sun,
            glm::mat4 sunMVMatrix, 
            float orbitalPeriod,
            float lengthDay,
            float size,
            float homothetieSize, 
            float distance,
            float homothetieDistance) {

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, textures[name]);

    glm::mat4 planetMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));

    planetMVMatrix = glm::rotate(sunMVMatrix, rotationValue * orbitalPeriod, glm::vec3(0, 1, 0)); // Rotation autour du soleil
    planetMVMatrix = glm::translate(planetMVMatrix, glm::vec3(distance * homothetieDistance, 0, 0)); // La distance réelle * l'homothétie
    planetMVMatrix = glm::scale(planetMVMatrix, glm::vec3(size * homothetieSize, size * homothetieSize, size * homothetieSize)); // Prise de rapport taille Planète/Soleil * l'homothétie
    planetMVMatrix = glm::rotate(planetMVMatrix, rotationValue * lengthDay, glm::vec3(0, 1, 0)); // Rotation sur elle-même  

    glUniformMatrix4fv(uniTextureProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * planetMVMatrix));
    glUniformMatrix4fv(uniTextureProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(planetMVMatrix));

    glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

    glBindTexture(GL_TEXTURE_2D, 0);


};

void drawMultiTexturePlanet(GLuint* textures,
            PlanetTexture firstName,
            PlanetTexture secondName,
            const UniTexturePlanetProgram& uniTextureProgram,
            const MultiTextureProgram& multiTextureProgram, 
            Sphere sun, 
            glm::mat4 sunMVMatrix, 
            float orbitalPeriod,
            float lengthDay,
            float size,
            float homothetieSize,
            float distance,
            float homothetieDistance) {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[firstName]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[secondName]);

    multiTextureProgram.m_Program.use();

    glUniform1i(multiTextureProgram.uFirstTexture, 0);
    glUniform1i(multiTextureProgram.uSecondTexture, 1);

    glm::mat4 planetMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));

    planetMVMatrix = glm::rotate(sunMVMatrix, rotationValue * orbitalPeriod, glm::vec3(0, 1, 0)); // 7 secondes pour un tour complet
    planetMVMatrix = glm::translate(planetMVMatrix, glm::vec3(distance * homothetieDistance, 0, 0)); // Homothétie de 1/5
    planetMVMatrix = glm::scale(planetMVMatrix, glm::vec3(size * homothetieSize, size * homothetieSize, size * homothetieSize)); // Prise de rapport taille Planète/Soleil * Homothétie de 10
    planetMVMatrix = glm::rotate(planetMVMatrix, rotationValue * lengthDay, glm::vec3(0, 1, 0)); // Rotation sur elle-même 

    glUniformMatrix4fv(multiTextureProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * planetMVMatrix));
    glUniformMatrix4fv(uniTextureProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(planetMVMatrix));

    glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

};

void drawSatellite(GLuint* textures,
            PlanetTexture name, 
            const UniTexturePlanetProgram& uniTextureProgram, 
            Sphere sun,
            glm::mat4 sunMVMatrix, 
            float orbitalPeriod,
            float lengthDay,
            float size,
            float homothetieSize, 
            float distance,
            float homothetieDistance) {

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, textures[name]);

    glm::mat4 planetMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));

    planetMVMatrix = glm::rotate(sunMVMatrix, rotationValue * orbitalPeriod, glm::vec3(0, 1, 0)); // Rotation autour du soleil
    planetMVMatrix = glm::translate(planetMVMatrix, glm::vec3(distance * homothetieDistance, 0, 0)); // La distance réelle * l'homothétie
    planetMVMatrix = glm::scale(planetMVMatrix, glm::vec3(size, size, size)); // Prise de rapport taille Planète/Soleil * l'homothétie
    planetMVMatrix = glm::rotate(planetMVMatrix, rotationValue * lengthDay, glm::vec3(0, 1, 0)); // Rotation sur elle-même  

    glUniformMatrix4fv(uniTextureProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * planetMVMatrix));
    glUniformMatrix4fv(uniTextureProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(planetMVMatrix));

    glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

    glBindTexture(GL_TEXTURE_2D, 0);


};


void solarSystemProfileRender(FilePath applicationPath, 
            SDLWindowManager windowManager, 
            float &speed,
            GLuint vao,
            GLuint vbo,
            GLuint* textures,
            Sphere sun) {

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
            if(windowManager.isKeyPressed(SDLK_KP1)) {
                std::cout << "Basculement sur Mercure." << std::endl;
                mercuryViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP2)) {
                std::cout << "Basculement sur Venus." << std::endl;
                venusViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP3)) {
                std::cout << "Basculement sur la Terre." << std::endl;
                earthViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP4)) {
                std::cout << "Basculement sur Mars." << std::endl;
                marsViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP5)) {
                std::cout << "Basculement sur Jupiter." << std::endl;
                jupiterViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP6)) {
                std::cout << "Basculement sur Saturne." << std::endl;
                saturnViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP7)) {
                std::cout << "Basculement sur Uranus." << std::endl;
                uranusViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP8)) {
                std::cout << "Basculement sur Neptune." << std::endl;
                neptuneViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
            }
            if(windowManager.isKeyPressed(SDLK_KP9)) {
                std::cout << "Basculement sur Pluto." << std::endl;
                plutoViewRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);
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
        glm::mat4 sunMVMatrix = glm::rotate(initial_MVMAtrix, rotationValue * sunLengthDay, glm::vec3(0, 1, 0));
        sunMVMatrix = glm::scale(sunMVMatrix, glm::vec3(homothetiePlanete, homothetiePlanete, homothetiePlanete));


        glUniformMatrix4fv(uniTextureProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * sunMVMatrix));
        glUniformMatrix4fv(uniTextureProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(sunMVMatrix));
        glUniformMatrix4fv(uniTextureProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);

        // Draw the Sun

        glBindTexture(GL_TEXTURE_2D, textures[Sun]);

        glDrawArrays(GL_TRIANGLES, 0, sun.getVertexCount());

        // Draw Mercury

        drawUniTexturePlanet(textures, Mercury, uniTextureProgram, sun, sunMVMatrix, mercuryOrbitalPeriod, mercuryLengthDay, mercurySize, homothetiePlanete, mercuryDistance, homothetieDistance);

        // Draw Venus

        drawUniTexturePlanet(textures, Venus, uniTextureProgram, sun, sunMVMatrix, venusOrbitalPeriod, venusLengthDay, venusSize, homothetiePlanete, venusDistance, homothetieDistance);
        
        // Draw the Earth

        drawMultiTexturePlanet(textures, Earth, Cloud, uniTextureProgram, multiTextureProgram, sun, sunMVMatrix, earthOrbitalPeriod, earthLengthDay, earthSize, homothetiePlanete, earthDistance, homothetieDistance);

        // Draw Mars

        drawUniTexturePlanet(textures, Mars, uniTextureProgram, sun, sunMVMatrix, marsOrbitalPeriod, marsLengthDay, marsSize, homothetiePlanete, marsDistance, homothetieDistance);

        // Draw Jupiter

        drawUniTexturePlanet(textures, Jupiter, uniTextureProgram, sun, sunMVMatrix, jupiterOrbitalPeriod, jupiterLengthDay, jupiterSize, homothetiePlanete, jupiterDistance, homothetieDistance);

        // Draw Saturn

        drawUniTexturePlanet(textures, Saturn, uniTextureProgram, sun, sunMVMatrix, saturnOrbitalPeriod, saturnLengthDay, saturnSize, homothetiePlanete, saturnDistance, homothetieDistance);

        // Draw Uranus

        drawUniTexturePlanet(textures, Uranus, uniTextureProgram, sun, sunMVMatrix, uranusOrbitalPeriod, uranusLengthDay, uranusSize, homothetiePlanete, uranusDistance, homothetieDistance);

        // Draw Neptune

        drawUniTexturePlanet(textures, Neptune, uniTextureProgram, sun, sunMVMatrix, neptuneOrbitalPeriod, neptuneLengthDay, neptuneSize, homothetiePlanete, neptuneDistance, homothetieDistance);

        // Draw Pluto

        drawUniTexturePlanet(textures, Pluto, uniTextureProgram, sun, sunMVMatrix, plutoOrbitalPeriod, plutoLengthDay, plutoSize, homothetiePlanete, plutoDistance, homothetieDistance);
    
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    // Clear everything after exiting
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, textures);
}