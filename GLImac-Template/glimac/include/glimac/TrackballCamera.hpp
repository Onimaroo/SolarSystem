#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>

class TrackballCamera {
    public:
        TrackballCamera() {
            m_fDistance = 5;
            m_fAngleX = 0;
            m_fAngleY = 0;    
        }

        void moveFront(float delta) {
            m_fDistance -= delta;
        }

        void rotateLeft(float degrees) {
            m_fAngleY += degrees;
        }

        void rotateUp(float degrees) {
            m_fAngleX += degrees;
        }

        glm::mat4 getViewMatrix() const {
            glm::mat4 viewMatrix = glm::translate(glm:: mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance));
            viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1, 0, 0));
            viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0, 1, 0));
            return viewMatrix;
        }
    
    private:
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;

};