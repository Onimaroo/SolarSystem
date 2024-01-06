#include "../glimac/include/render/ProfileViewRender.hpp"
#include "../glimac/include/render/EarthViewRender.hpp"
#include "../glimac/include/render/MercuryViewRender.hpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace glimac;

int main(int argc, char** argv) {

    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    /***************************************
           INITIAISATION DES TEXTURES
     ***************************************/

    // Chargement des images

    std::vector<std::unique_ptr<Image>> image_array;

    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/SunMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/MercuryMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/VenusMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/EarthMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/MarsMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/JupiterMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/SaturnMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/UranusMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/NeptuneMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/PlutoMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/MoonMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/CloudMap.jpg"));
    image_array.push_back(loadImage("/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_SolarSystem/textures/SkyboxMap.png"));

    for(int i = 0; i < image_array.size(); i++) {
        if(image_array[i] == NULL) {
            std::cout << "Couldn't find image." << std::endl;
        }
    }


    // Ajout des textures au tableau de texture

    GLuint textures[image_array.size()];
    
    glGenTextures(image_array.size(), textures);

    for(int i = 0; i < image_array.size(); i++) {

        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_array[i]->getWidth(), image_array[i]->getHeight(), 0, GL_RGBA, GL_FLOAT, image_array[i]->getPixels());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

    }

    /*********************************
            CODE D'APPLICATION
     *********************************/

    // Initialisation des programmes

    FilePath applicationPath(argv[0]);

    glEnable(GL_DEPTH_TEST);
    
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    Sphere sun(1, 32, 16);

    std::cout << "Number of vertexes: " << sun.getVertexCount() << std::endl;

    // Création du VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Remplissage du VBO
    const ShapeVertex* vertices = sun.getDataPointer();

    glBufferData(GL_ARRAY_BUFFER, sun.getVertexCount() * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);

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

    /****************************************************************
          CODE DE RENDU (se référer aux fichiers .hpp de render)
     ****************************************************************/
    
    float speed = 1;

    // L'application commence directement par la vue de profil
    solarSystemProfileRender(applicationPath, windowManager, speed, vao, vbo, textures, sun);

    return EXIT_SUCCESS;
}