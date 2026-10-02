#include "Skrap_Engine.h"


int main()
{
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

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	//shaders



	gladLoadGL();

	glViewport(0, 0, 1500, 800);


	Shader ShaderProgram(
		R"(C:\Users\Tudor_54ziysr\source\repos\Tinstruck\Skrap_Yard\Resources\Shaders\Default.vert)",
		R"(C:\Users\Tudor_54ziysr\source\repos\Tinstruck\Skrap_Yard\Resources\Shaders\Default.frag)"
	);

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// buffer objects and vertex array objects

	GLuint VAO, VBO, EBO;
	
	//create vertex array object 


	
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
