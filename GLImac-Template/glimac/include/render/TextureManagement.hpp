#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

enum PlanetTexture { Sun = 0,
                     Mercury = 1, 
                     Venus = 2, 
                     Earth = 3, 
                     Mars = 4, 
                     Jupiter = 5, 
                     Saturn = 6, 
                     Uranus = 7, 
                     Neptune = 8, 
                     Pluto = 9, 
                     Moon = 10, 
                     Cloud = 11,
                     Skybox = 12
                   };

struct BackgroundProgram {
    Program m_Program;

    GLint uTexture;

    BackgroundProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex2D.fs.glsl")) {
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};


struct UniTexturePlanetProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    UniTexturePlanetProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

struct MultiTextureProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uFirstTexture;
    GLint uSecondTexture;

    MultiTextureProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uFirstTexture = glGetUniformLocation(m_Program.getGLId(), "uFirstTexture");
        uSecondTexture = glGetUniformLocation(m_Program.getGLId(), "uSecondTexture");
    }
};