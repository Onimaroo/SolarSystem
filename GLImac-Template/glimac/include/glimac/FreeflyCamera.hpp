#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <math.h>

class FreeflyCamera {
    public:
        FreeflyCamera() {
            m_Position.x = 0;
            m_Position.y = 0;
            m_Position.z = 5;
            m_fPhi = M_PI;
            m_fTheta = 0; 

            computeDirectionVectors();   
        }

        void moveLeft(float t) {
            m_Position += t * m_LeftVector;
        }

        void moveFront(float t) {
            m_Position += t * m_FrontVector;
        }

        void rotateLeft(float degrees) {
            m_fPhi += glm::radians(degrees);
        }

        void rotateUp(float degrees) {
            m_fTheta += glm::radians(degrees);
        }

        glm::mat4 getViewMatrix() const {
            glm::mat4 viewMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
            viewMatrix = glm::rotate(viewMatrix, m_fPhi, glm::vec3(1, 0, 0));
            viewMatrix = glm::rotate(viewMatrix, m_fTheta, glm::vec3(0, 1, 0));
            return viewMatrix;
        }
    
    private:
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        void computeDirectionVectors() {
            m_FrontVector.x = glm::cos(m_fTheta) * glm::sin(m_fPhi);
            m_FrontVector.y = glm::sin(m_fTheta);
            m_FrontVector.z = glm::cos(m_fTheta) * glm::cos(m_fPhi); 

            m_LeftVector.x = glm::sin(m_fPhi + (M_PI / 2)); 
            m_LeftVector.y = 0;
            m_LeftVector.y = glm::cos(m_fPhi + (M_PI / 2)); 

            m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
        }

};