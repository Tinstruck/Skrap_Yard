#include "Skrap_Engine.h"


int main()
{

	std::cout << "Working Directory: " << std::filesystem::current_path() << std::endl;

	//variables 
	int WINwidth = 1500;
	int WINheight = 800;







	// initialize glfw
	bool  isInitialized = glfwInit();
	




	// window icon
	GLFWwindow* window = glfwCreateWindow(WINwidth, WINheight, "Skrap Engine", NULL, NULL);
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

	glm::vec3 camera = glm::vec3(0, 0, 3);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 Lookinghere = glm::vec3(0, 0, 0);
	glm::mat4 matrix = glm::lookAt(camera, Lookinghere, up);

	glm::vec3 veccol1 = glm::vec3(1.0f, 0.0f, 0.0f); // Red
	glm::vec3 veccol2 = glm::vec3(0.0f, 1.0f, 0.0f); // Green
	glm::vec3 veccol3 = glm::vec3(0.0f, 0.0f, 1.0f); // Blue


	GLfloat vertices[] =
	{
		-0.5f,	-0.5f * float(sqrt(3)) / 3, 0.0f,		 veccol1.r ,veccol1.g, veccol1.b, // Lower left corner

		0.5f,	-0.5f * float(sqrt(3)) / 3, 0.0f,		 veccol2.r, veccol2.g, veccol2.b,// Lower right corner

		0.0f,	0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	 veccol3.r, veccol3.g, veccol3.b, // Upper corner

		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		 veccol1.r, veccol1.g, veccol1.b, // Inner left

		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		 veccol2.r, veccol2.g, veccol2.b, // Inner right

		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,			 veccol3.r, veccol3.g, veccol3.b // Inner down
	};


	GLuint indices[] =
	{
		0, 5, 3, 
		3, 2, 4,
		4, 1, 5
	};

	//shaders



	gladLoadGL();

	glViewport(0, 0, 1500, 800);



	Shader ShaderProgram("../../../Resources/Shaders/Default.vert", "../../../Resources/Shaders/Default.frag");


	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// buffer objects and vertex buffer objects and element buffer objects

	GLuint VAO, VBO, EBO;
	
	


	
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
		
		ShaderProgram.Activate();
		
		VAO1.Bind();
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
		
			ImGui::ColorEdit3("Color", (float*)&veccol1);
			ImGui::ColorEdit3("Color2", (float*)&veccol2);
			ImGui::ColorEdit3("Color3", (float*)&veccol3);
			
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



		GLfloat vertices[] =
		{
			-0.5f,	-0.5f * float(sqrt(3)) / 3, 0.0f,		 veccol1.r, veccol1.g, veccol1.b,
			0.5f,	-0.5f * float(sqrt(3)) / 3, 0.0f,		 veccol2.r, veccol2.g, veccol2.b,
			0.0f,	0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	 veccol3.r, veccol3.g, veccol3.b,
			-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		 veccol1.r, veccol1.g, veccol1.b,
			0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		 veccol2.r, veccol2.g, veccol2.b,
			0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,			 veccol3.r, veccol3.g, veccol3.b
		};








		// Draw 
		ImGui::Begin("Viewport");
		ImGui::Image((void*)(intptr_t)0, ImVec2(800, 600), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		VBO1.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		ImGui::Render();

		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// render background open gl context
		  

		glfwPollEvents();
		glfwSwapBuffers(window);

	};

	



	
	ShaderProgram.Activate();
	VAO1.Bind();

	//cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ShaderProgram.Delete();
	


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
