#include "Skrap_Engine.h"






int main()
{
	// initialize glfw
	bool  isInitialized = glfwInit();
	


	// window icon
	GLFWwindow* window = glfwCreateWindow(1500, 800, "Skrap Engine", NULL, NULL);
	GLFWimage image;
	image.width = ICON_WIDTH;
	image.height = ICON_HEIGHT;
	image.pixels = (unsigned char*)icon;


	;


	//glfw create context
	glfwMakeContextCurrent(window);
	bool isGLADInitialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//icon
	glfwSetWindowIcon(window, 1, &image);
	

	//imgui create context
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	// for each polygon in the shape created create template for a triangle holding a 
	// part of that shape and disect it in little triangles 
	
	// 1- you get a 3d polygon lets say a cube 
	// 2- each face on the cube and turn it into a triangle (metaphoricaly you have a cube)
	// 3- each vertecie has its own coordinate so its as modifiable 


	// 1st triangle 

	float movex = 0.0f;
	
	float movey = 0.0f;
	


	float a1 = -0.5f;
	float a2 = -0.5f;

	float b1 = 0.5f;
	float b2 = -0.5f;

	float c1 = 0.0f;
	float c2 = 0.5f;

	a1 + movey;
	b1 + movey;
	c1 + movey;

	a2 + movex;
	b2 + movex;
	c2 + movex;

	
	GLfloat vertices[] = {
		a1, a2, 0.0f,
		b1, b2, 0.0f,
		c1, c2, 0.0f
	};


	//shaders
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos; \n"
		"uniform vec2 uOffset;\n"
		"void main()\n"
		"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
	"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
		"}\n\0";


	gladLoadGL();

	glViewport(0, 0, 1500, 800);

	//vertex shader create
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//fragment shader create
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//shadere program create
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// buffer objects and vertex array objects

	GLuint VAO, VBO;
	
	//create vertex array object 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//link vertex array object
	glBindVertexArray(VAO);

	// AFTER linking vertext array object link   
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
	bool isWireframe = false;

	bool isdemowindowopen = false;


	//-------------------------------------------#
	//mainloop, while window should NOT close, run 
	//-------------------------------------------#

	while (!glfwWindowShouldClose(window))
	{

	//-------------------------------------------#
	//background sp init vao init and drawing 
	//-------------------------------------------#

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
	//===========================================#
	//IMPORTANT
	//===========================================#
		glDrawArrays(GL_TRIANGLES, 0, 3);



		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//DEBUG SHOW DEMO FOR NEW FRAMES
		//COMENT OUT WHEN NOT NEEDED
		if (isdemowindowopen) {

			ImGui::ShowDemoWindow();

		}
		

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("debug"))
			{
				
				ImGui::MenuItem("Demo Window", NULL, &isdemowindowopen);

				ImGui::EndMenu(); 
			}

			// work on later

			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New")) {
					// new file
				}
				if (ImGui::MenuItem("Open")) {
					// open file
				}
				if (ImGui::MenuItem("Save")) {
					// save file
				}
				if (ImGui::MenuItem("Save As")) {
					// save as file
				}
				ImGui::EndMenu();
			

		}

		ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Explorer");
		ImGui::Text("Hello World");
		ImGui::End();

		ImGui::Begin("Properties");
		ImGui::Checkbox("Wireframe Mode", &isWireframe);
		ImGui::SliderFloat("Move X", &movex, -1.0f, 1.0f);
		ImGui::SliderFloat("Move Y", &movey, -1.0f, 1.0f);
		ImGui::End();

		ImGui::Begin("Text Editor");
		// noah make a text editor here
		// make it so you can imput text and it auto saves into a file or if thats hard make it so you can input text and it saves into a file when you click a button
		ImGui::End();


		// wireframe view i tought this'd be cool
		if (isWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}












		// Draw 
		

		ImGui::Render();

		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// render background open gl context
		// all i need is a cube    

		glfwPollEvents();
		glfwSwapBuffers(window);

	};

	





	//cleanup
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
