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
	//---------------------------------------------------#
	//				   WORLD SUBSECTION
	// -- this defines the world and the objects in it --
	//---------------------------------------------------#


		float movex = 0.0f;
		float movey = 0.0f;
		float movez = 0.0f;

		GLfloat x1 = -0.5f;
		GLfloat y1 = -0.5f;
		GLfloat z1 = 0.0f;
		GLfloat x2 = 0.5f; 
		GLfloat y2 = -0.5f;
		GLfloat z2 = 0.0f;
		GLfloat x3 = -0.5f;
		GLfloat y3 = 0.5f;
		GLfloat z3 = 0.0f;


		x1 + movex;
		x2 + movex;
		x3 + movex;

		y1 + movey;
		y2 + movey;
		y3 + movey;

		z1 + movez;
		z2 + movez;
		z3 + movez;

	GLfloat vertices[] = {
			x1, y1, z1, // bottom left
			 x2, y2, z2, // bottom right
			 x3,  y3, z3, // top right
		};




	


	//shaders
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos; \n"
		"uniform vec3 uOffset;\n"
		"void main()\n"
		"{\n"
	"gl_Position = vec4(aPos.x + uOffset.x, aPos.y + uOffset.y, aPos.z, 1.0);\n"
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

	int uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");

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
	bool isGLDebugWindowOpen = false;

	//le triangle
	bool isSelected = false;





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
		// offset
		glUniform3f(uOffsetLoc, movex, movey, movez);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();






			
		//input handling







		//DEBUG SHOW DEMO FOR NEW FRAMES
		//COMENT OUT WHEN NOT NEEDED
		if (isdemowindowopen) {

			ImGui::ShowDemoWindow();

		}

		if (isGLDebugWindowOpen) {
			ImGui::Begin("GL Debug Window");
			ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
			ImGui::Text("OpenGL Renderer: %s", glGetString(GL_RENDERER));
			ImGui::Text("OpenGL Vendor: %s", glGetString(GL_VENDOR));
			ImGui::Text("OpenGL Shading Language Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
			ImGui::End();
			ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));

		}
		
		// good for now
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("debug"))
			{
				
				ImGui::MenuItem("Demo Window", NULL, &isdemowindowopen);

				ImGui::MenuItem("GL debug window ", NULL, &isGLDebugWindowOpen);
				
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
		ImGui::Selectable("Triangle 1", &isSelected);
		ImGui::End();

		ImGui::Begin("Properties");
		if (isSelected) {
			ImGui::Checkbox("Wireframe Mode", &isWireframe);
			ImGui::Text("Triangle 1 Properties");
			ImGui::Text("Position: (0.0, 0.0)");
			ImGui::Text("Rotation: 0.0 degrees");
			ImGui::Text("Scale: (1.0, 1.0)");

			ImGui::SliderFloat("Move X", &movex, -1.0f, 1.0f);
			ImGui::SliderFloat("Move Y", &movey, -1.0f, 1.0f);
			ImGui::SliderFloat("Move Z", &movez, -1.0f, 1.0f);
		}
		else {
			ImGui::Text("No object selected");
		}

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
