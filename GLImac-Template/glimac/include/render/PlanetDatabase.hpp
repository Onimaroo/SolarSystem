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
                     Phobos = 11,
                     Demios = 12,
                     Callisto = 13,
                     Ganymede = 14,
                     Europa = 15,
                     Io = 16,
                     Mimas = 17,
                     Enceladus = 18,
                     Tethys = 19,
                     Dione = 20,
                     Rhea = 21,
                     Titan = 22,
                     Hyperion = 23,
                     Iapetus = 24,
                     Ariel = 25,
                     Umbriel = 26,
                     Titania = 27,
                     Oberon = 28,
                     Miranda = 29,
                     Triton = 30,
                     Nereid = 31,
                     Charon = 32,
                     Cloud = 33
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

// OrbitalPeriod et LengthDay = Nombre de secondes pour faire un tour complet dans l'application divisé par le nombre total de secondes pour un tour complet en réalité.

float mercuryOrbitalPeriod = 9.20664983 * pow(10, -7);
float venusOrbitalPeriod = 3.617571 * pow(10, -7);
float earthOrbitalPeriod = 2.21940393 * pow(10, -7);
float marsOrbitalPeriod = 1.17924528 * pow(10, -7);
float jupiterOrbitalPeriod = 1.8706574 * pow(10, -8);
float saturnOrbitalPeriod = 7.53870858 * pow(10, -9);
float uranusOrbitalPeriod = 2.64861572 * pow(10, -9);
float neptuneOrbitalPeriod = 1.35482472 * pow(10, -9);
float plutoOrbitalPeriod = 8.94639575 * pow(10, -10);

float mercuryLengthDay = 4.60485114 * pow(10, -7);
float venusLengthDay = 6.93962526 * pow(10, -7);
float earthLengthDay = 8.10185185 * pow(10, -5);
float marsLengthDay = 7.87224471 * pow(10, -5);
float jupiterLengthDay = 1.9640853 * pow(10, -4);
float saturnLengthDay = 1.8172378 * pow(10, -4);
float uranusLengthDay = 1.14379085 * pow(10, -4);
float neptuneLengthDay = 1.21527778 * pow(10, -4);
float plutoLengthDay = 1.27087872 * pow(10, -5);

float mercurySize = 0.00350654017;
float venusSize = 0.00869915193;
float earthSize = 0.00916774471;
float marsSize = 0.0048814144;
float jupiterSize = 0.1004901538;
float saturnSize = 0.08662929423;
float uranusSize = 0.03673853672;
float neptuneSize = 0.03559580278;
float plutoSize = 0.0017076326;

float mercuryDistance = 57.9;
float venusDistance = 108;
float earthDistance = 149;
float marsDistance = 228;
float jupiterDistance = 778;
float saturnDistance = 1432.0;
float uranusDistance = 2867.0;
float neptuneDistance = 4515.0;
float plutoDistance = 5906.4;

float homothetiePlanete = 5; // On augmente de cinq fois les tailles des planètes pour éviter qu'elles soient trop petites.
float homothetieDistance = 0.02; // On divise par 50 la distance des planètes pour éviter qu'elles soient trop loin.
float homothetieDistanceSatellite = 5; // On multiplie par 5 la distance des satellites pour éviter qu'elles soient trop proche.

float sunLengthDay = 3.24074074 * pow(10, -6);