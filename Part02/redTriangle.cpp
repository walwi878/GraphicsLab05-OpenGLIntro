
/*
 * redTriangle.cpp
 *
 * Adapted from http://opengl-tutorial.org
 * by Stefanie Zollmann
 *
 * Solution for OpenGL Lab Part02
 *
 */


/* ------------------------------------------------------------------------- */
/* ---- INCLUDES ----------------------------------------------------------- */
/*
 * Include standard headers
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// Include GLEW
#include <GL/glew.h>

/*
 * Include GLFW
 * Multi-platform library for creating windows, contexts and surfaces, receiving input and events.
 */
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;

#include <common/Shader.hpp>
#include <common/ColorShader.hpp>
#include <common/Camera.hpp>
#include <common/Scene.hpp>
#include <common/Object.hpp>
#include <common/Triangle.hpp>
#include <common/Quad.hpp>

/* ---- Helper Functions  ------------------------------------------------------- */

/*
 *  initWindow
 *
 *  This is used to set up a simple window using GLFW.
 *  Returns true if sucessful otherwise false.
 */
bool initWindow(std::string windowName){
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return false;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, windowName.c_str(), NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n" );
        getchar();
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    
    return true;
    
}

/*
 *  main
 *
 *  This is the main function that does all the work.
 *  Creates the window and than calls renderLoop.
 */
int main( void )
{
    
    initWindow("Part02");
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.3f, 0.9f, 0.7f, 0.0f);

    
    //create a Vertex Array Object and set it as the current one
    //we will not go into detail here. but this can be used to optimise the performance by storing all of the state needed to supply vertex data
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

    // create a triangle and set a shader
    Triangle* myTriangle1 = new Triangle();
    //the basic vertex shader transforms the vertices using the Model-View Projection matrix and the basic fragment shader outputs a predefined color
	
    myTriangle1->setTranslate(vec3(0.3,1.1,0.5));
   
    ColorShader* shader1 = new ColorShader( "simpleColor");
    myTriangle1->setShader(shader1);
    Triangle* myTriangle2 = new Triangle();
    myTriangle2->setTranslate(vec3(-0.3,1.7,0.2));
    ColorShader* shader2 = new ColorShader( "simpleColor");
    shader2->setColor(glm::vec4(0.3,0.9,0.2,0.6));
    myTriangle2->setShader(shader2);

    //excercise create a quad
    Quad* myQuad = new Quad();
    
    ColorShader* shader3 = new ColorShader( "simpleColor");
    shader3->setColor(glm::vec4(0.3,0.6,0.9,1.0));
    myQuad->setShader(shader3);
	
    
    Scene* myScene = new Scene();
    myScene->addObject(myTriangle1);
    myScene->addObject(myTriangle2);
    myScene->addObject(myQuad);
    myQuad->setTranslate(vec3(0.0,-1.0,0.0));
    
    Camera* myCamera = new Camera();
	myCamera->setPosition(glm::vec3(0,0,5));
    
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ){// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

        myScene->render(myCamera);
        
        glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

    }
    

    glDeleteVertexArrays(1, &VertexArrayID);
	
    delete myScene;
    delete myCamera;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

