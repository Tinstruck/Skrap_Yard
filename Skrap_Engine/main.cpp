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

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		};



	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos; \n"
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

	//-------------------------------------------#
	//mainloop, while window should NOT close, run 
	//-------------------------------------------#

	while (!glfwWindowShouldClose(window))
	{

	//-------------------------------------------#
	//background sp init vao init and drawing 
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
		ImGui::ShowDemoWindow();

		if (ImGui::BeginMainMenuBar())
		{
			// top menu add anything important here 
			
			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Explorer");
		ImGui::Text("Hello World");
		ImGui::End();

		ImGui::Begin("Properties");
		ImGui::Checkbox("Wireframe Mode", &isWireframe);
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


		ImGui::Begin("Viewport");
		ImGui::GetMainViewport();
		ImGui::Image((void*)(intptr_t)0, ImVec2(800, 600));
		ImGui::End();












		// Draw 
		

		ImGui::Render();

		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// render background open gl context
		// all i need is a cube    

		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	





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
