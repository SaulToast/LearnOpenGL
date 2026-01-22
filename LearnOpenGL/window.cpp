#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource;
const char* fragmentShaderSource;

int main() 
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	// callback for window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// vertext input
	float vertices[] = {
		// verts			//colors
		-0.5f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,// left  
		 0.5f, 0.1f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
		 0.0f,  0.6f, 0.0f, 0.0f, 0.0f, 1.0f,// top  

		 //tri 2
		 -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// left  
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
		 -0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f, // top

		 -0.5f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, // left  
		 0.5f, 0.1f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
	};

	Shader ourShader("shaders/TestShader.vert", "shaders/TestShader.frag");

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	glEnable(GL_DEPTH_TEST);


	//render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);


		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		glBindVertexArray(VAO);
		
		ourShader.use();
		glm::mat4 id = glm::mat4(1.0f);
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(id));

		auto colorMask = glm::vec3(1.0f, 1.0f, 0.0f);
		unsigned int maskLoc = glGetUniformLocation(ourShader.ID, "colorMask");
		glUniform3fv(maskLoc, 1, glm::value_ptr(colorMask));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawArrays(GL_TRIANGLES, 6, 3);


		ourShader.use();
		glm::mat4 trans = glm::mat4(1.0);
		trans = glm::translate(trans, glm::vec3(-0.4f, -0.3f, -0.1f));
		trans = glm::scale(trans, glm::vec3(1.3f, 1.3f, 1.3f));
		transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		colorMask = glm::vec3(1.0f, 0.0f, 1.0f);
		maskLoc = glGetUniformLocation(ourShader.ID, "colorMask");
		glUniform3fv(maskLoc, 1, glm::value_ptr(colorMask));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawArrays(GL_TRIANGLES, 6, 3);

		ourShader.use();
		glm::mat4 trans1 = glm::mat4(1.0f);
		trans1 = glm::translate(trans1, glm::vec3(0.4f, 0.3f, 0.1f));
		trans1 = glm::scale(trans1, glm::vec3(0.7f, 0.7f, 0.7f));
		transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans1));

		colorMask = glm::vec3(0.0f, 1.0f, 1.0f);
		maskLoc = glGetUniformLocation(ourShader.ID, "colorMask");
		glUniform3fv(maskLoc, 1, glm::value_ptr(colorMask));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawArrays(GL_TRIANGLES, 6, 3);
		
		/// events and buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

