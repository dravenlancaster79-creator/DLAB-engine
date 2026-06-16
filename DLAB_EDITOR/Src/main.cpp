#define SDL_MAIN_HANDLED 1;
#include <Windowing/Window/Window.h>
#include<SDL.h>
#include <glad/glad.h>
#include <iostream>
int main() 
{ 
	bool running = (true);

	// initializing SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::string error = SDL_GetError();
		std::cout << "Failed to initialize SDL: " << error << "\n";
		running = false;
		return -1
			
			 ;
	
	}
	// setup OpenGL
	if (SDL_GL_LoadLibrary(NULL) != 0)
	{
		std::string error = SDL_GetError();
		std::cout << "Failed to load OpenGL library: " << error << "\n";
		running = false;
		return -99;
	}

	// set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// set num of bits for each color channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// create window
	DLAB_WINDowing::Window window("DLAB Editor", 1280, 720, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true, SDL_WINDOW_OPENGL);

	if (!window.GetWindow())
	{
		std::cout << "Failed to create window\n";
		running = false;
	}

	//Create OpenGL context
	window.SetGLContext(SDL_GL_CreateContext(window.GetWindow().get()));

	if (!window.GetGLContext())
	{
		std::string error = SDL_GetError();
		std::cout << "Failed to create OpenGL context: " << error << "\n";
		running = false;

		return -1;

	}

	SDL_GL_MakeCurrent(window.GetWindow().get(), window.GetGLContext());
	SDL_GL_SetSwapInterval(1);

	//init glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		running = false;
		return -1;
	}

	// Create temp Vertex Data
	float vertices[] =
	{
		.00f, .0f ,.0f, // one vert
		-.5f,-.5f, .0f,
		.5f, -.5f, .0f

	};
    //create temp vert Src
	const char* vertexSource =
		"#version 450 core \n"
		"layout (location = 0) in vec3 aPosition;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPosition, 1.0);\n"
		"}\0";

	// create Shaders
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//add Vert Shader Src
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	//Compile Vert Shader
	glCompileShader(vertexShader);

	//Gert the comilation status
	int status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Failed to compile vertex shader!!\n" << infoLog << std::endl;
		return -1;



	}

	// Create temp Fragment Shader
	const char* fragmentSource =
		"#version 450 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0f, .54f, .69f, 1.0f);\n"
		"}\0";

	//create fragshade
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Add Frag shd src
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	//Compile Frag Shader
	glCompileShader(fragmentShader);

	// get cumil status
	 status; 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Failed to copile fragment shader!!\n" << infoLog << std::endl;
		return -1;



	}

	// Create Shd Program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	//attach above shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//link shd

	glLinkProgram(shaderProgram);

	//check link status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

	if (!status)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Failed to Link Shader Program!!\n" << infoLog << std::endl;
		return -1;



	}


	//enable Shader
	glUseProgram(shaderProgram);

	//created and linked=delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//creete vertex array obj and buffer obj
	GLuint VAO, VBO;

	// gen VAO

	glGenVertexArrays(1, &VAO);

	// GEN VBO

	glGenBuffers(1, &VBO);

	//BIND VAO VBO

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(
	GL_ARRAY_BUFFER, // buf type
	sizeof(vertices) * 3 * sizeof(float), // size in byte of the buff
	vertices,
	GL_STATIC_DRAW				//the use of data stored

	
	);

	glVertexAttribPointer(
	0,  // att 0 --layout pos in shder
	3, // num of components p/vertex
	GL_FLOAT, //type 
	GL_FALSE, // normalized-- specifies if Fixed data vals should be normalizedddddddd :)
	3 * sizeof(float), // stride
	(void*)0 // pointer  --offset of 1 component

	
	
	);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);









	SDL_Event event{};

	//window loop
	while (running)
	{
		// process events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						running = false;
					break;
				default:
					break;
			}
		}

		glViewport(
			0,
			0,
			window.GetWidth(),
			window.GetHeight());
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		SDL_GL_SwapWindow(window.GetWindow().get());
	}


	std::cout << "Exiting...\n";
	return	0;
}