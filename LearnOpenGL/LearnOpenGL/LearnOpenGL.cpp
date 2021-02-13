#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 400;
float lastY = 300;
bool firstMouse = true;



float vertices[] =
{
	// positions               //colors       
	-0.5f,-0.5f,0.0f,          1.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f,           0.0f,1.0f,0.0f,
	0.0f,0.5f,0.0f,            0.0f,0.0f,1.0f
};


float rectVertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	-1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	-1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.0f,  0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f,  -1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	0.0f,  -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  -1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f,  -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f,  -1.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f,  1.0f, 0.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

float texCoords[] = {
	0.0f,0.0f,
	1.0f,0.0f,
	0.5f,1.0f,
};


unsigned int indices[] =
{
	0,1,2
};

unsigned int rectIndices[] = 
{  
	//// note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};



//const char *vertexShaderSource = "#version 330 core\n"
//									"layout (location = 0) in vec3 aPos;\n"
//									"layout (location = 1) in vec3 aColor;\n"
//									"out vec3 ourColor;\n"
//									"void main()\n"
//									"{\n"
//									" gl_Position = vec4(aPos, 1.0);\n"
//									" ourColor = aColor;"
//									"}\0";
//
//const char *fragmentShaderSource = "#version 330 core\n"
//									"out vec4 FragColor;\n"
//									"in vec3 ourColor;"
//									"void main()\n"
//									"{\n"
//									" FragColor = vec4(ourColor,1.0);\n"
//									"}\0";



void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	return;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = (float)xPos;
		lastY = (float)yPos;
		firstMouse = false;
	}
	float xOffset = (float)xPos - lastX;
	float yOffset = (float)yPos - lastY;
	lastX = (float)xPos;
	lastY = (float)yPos;
	
	camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll((float)yOffset);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int wWidth = 800;
	int wHeight = 600;
	GLFWwindow * window = glfwCreateWindow(wWidth, wHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed To Create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed To Initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, wWidth, wHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	

	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

	// Shader
	/*unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[521];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error::Shader::Vertext::Compilation_Failed\n" << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error:;Shader::Fragment:;Comilation_Failed\n" << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error::Shader::ShaderProgram::Link_Failed" << std::endl;
	}*/

	Shader ourShader("../LearnOpenGL/Shader/shader.vs", "../LearnOpenGL/Shader/shader.fs");
	Shader lightShader("../LearnOpenGL/Shader/lightShader.vs", "../LearnOpenGL/Shader/lightShader.fs");
	
	/*int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maxinum nr of vertex attributes supported:" << nrAttributes << std::endl;*/

	
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char * data = stbi_load("../LearnOpenGL/Image/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed To Load Image" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("../LearnOpenGL/Image/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed To Load Image" << std::endl;
	}
	stbi_image_free(data);

	glEnable(GL_DEPTH_TEST);
	
	
	unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
	unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Light
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);



	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*glUseProgram(shaderProgram);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
		

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


		lightShader.use();
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightShader.setMat4("model", lightModel);
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		float timeValue = (float)glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		glBindVertexArray(VAO);

		ourShader.use();
		glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
		ourShader.setInt("texture2", 1);
		ourShader.setVec3("lightPos", lightPos);

		ourShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		ourShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		ourShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
		ourShader.setFloat("material.shininess", 32.0f);

		// light properties
		glm::vec3 lightColor;
		lightColor.x = sin((float)glfwGetTime() * 2.0f);
		lightColor.y = sin((float)glfwGetTime() * 0.7f);
		lightColor.z = sin((float)glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		ourShader.setVec3("light.ambient", ambientColor);
		ourShader.setVec3("light.diffuse", diffuseColor);
		ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() , glm::vec3(0.5f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	glfwTerminate();
	return 0;
}