
#include "pch.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <vecters.h>
#include <Gas.h> 
#include <Mags_and_coils.h>
// GLEW

#define GLEW_STATIC
#include <glew.h>


// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <time.h>
#include <vecters.h>
#include <SOIL.h>

// Other includes
#include <shader.h>
#include "Graph_objects.h"






// Window dimensions

#pragma warning(disable : 4430)
#pragma warning(disable : 2065)

const GLuint WIDTH = 1800, HEIGHT = 900;

using namespace std;


void reset_for_screen(float*arr, int size, int pointsize)
{
	for (int i = 0; i < size; i++)
	{

		arr[pointsize * i + 1] = arr[pointsize * i + 1] / HEIGHT * WIDTH;
		
	}
}




// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


// Shaders


 
// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Engine", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);


	// Build and compile our shader program
	Shader ourShader("C:/textures.vs", "C:/textures.frag");

	// XPENЬ C ШEЙDAPAMИ





				// Objects setup

	// vecters:
	vecter zero(0, 0, 0), sp(-60, 0, 0), coic(-0.4, 0, 0), vec1(-0.3, 0, 0);


	//Magnets:
	Magnet mag_left(200, 1700000, 0.2, 5, 0.1, vec1, sp, -1);
	Magnet mag_right(200, 1700000, 0.2, 5, 0.1, zero - vec1, zero - sp, 1);
	Magnet mag_left_static(200, 1700000, 0.2, 2, 0.1, 2.9 * vec1, zero, 1);
	Magnet mag_right_static(200, 1700000, 0.2, 20, 0.1, zero - 2.9 * vec1, zero, -1);

	//Coils:
	Coil S1(200, 0, 0.24, 0.2, coic, 100);
	Coil S2(200, 0, 0.24, 0.2, (zero - coic), 100);


	//Gases:
	double * _μ, *_aVV, *_bVV, *_cstech, *_Cv, *_ν, *_InjQnu;
	//parametrs 
	_μ = new double[4]; _μ[0] = 2; _μ[1] = 32; _μ[2] = 18; _μ[3] = 28;
	_aVV = new double[4]; _aVV[0] = 0.0248; _aVV[1] = 0.1378; _aVV[2] = 0.5536; _aVV[3] = 0.1;
	_bVV = new double[4]; _bVV[0] = (26.61 / 1000000); _bVV[1] = (31.83 / 1000000); _bVV[2] = (30.49 / 1000000); _bVV[3] = (31.83 / 1000000);
	_cstech = new double[4]; _cstech[0] = 1; _cstech[1] = 0.5; _cstech[2] = 1; _cstech[3] = 0;
	_ν = new double[4]; _ν[0] = 0.01; _ν[1] = 0.01; _ν[2] = 0.125; _ν[3] = 0.1;
	_InjQnu = new double[4]; _InjQnu[0] = 0.12; _InjQnu[1] = 0.07; _InjQnu[2] = 0; _InjQnu[3] = 0.55;
	_Cv = new double[4]; _Cv[0] = 5 / 2 * R; _Cv[1] = 5 / 2 * R; _Cv[2] = 3 * R; _Cv[3] = 5 / 2 * R;
	double S_porsh = mag_left.diametr_SI * mag_left.diametr_SI * π / 4;


	Gas gas_left(_μ, _aVV, _bVV, _cstech, _Cv, S_porsh * abs(-0.8 - mag_left.position_SI.x_proj + mag_left.height_SI / 2),
		300, 200000, _ν, 80000, S_porsh, _InjQnu, 0.01, 400, 7.5E-010, 0.0003, 550, 0.001, 4);
	gas_left.P = Patm;

	double* _InjQnu1 = new double[4]; _InjQnu1[0] = 0.22; _InjQnu1[1] = 0.11; _InjQnu1[2] = 0; _InjQnu1[3] = 0.6;
	double* _ν1 = new double[4]; _ν1[0] = 0.01; _ν1[1] = 0.01; _ν1[2] = 0; _ν1[3] = 0.1;
	Gas gas_centr(_μ, _aVV, _bVV, _cstech, _Cv, 2 * S_porsh * abs(-mag_left.position_SI.x_proj + mag_left.height_SI / 2),
		300, 200000, _ν1, 80000, S_porsh, _InjQnu1, 0.01, 400, 7.5E-010, 0.0004, 550, 0.0015, 0);
	gas_centr.P = Patm;
	//Field configurations:
	mag_left.Set_Field2D_Conf(80, 80, 320, 80);
	mag_right.Mag_field = mag_left.Mag_field;
	mag_left.show_field(4);


	//Textures:
	GLfloat porsh[20] = {

		mag_left.height_SI / 2 ,  mag_left.diametr_SI / 2, 0,		1.0f,1.0f,
		mag_left.height_SI / 2 , -mag_left.diametr_SI / 2, 0,		1.0f,0.0f,
		-mag_left.height_SI / 2 , -mag_left.diametr_SI / 2, 0,		0.0f,0.0f,
		-mag_left.height_SI / 2 ,  mag_left.diametr_SI / 2, 0,		0.0f,1.0f
	};

	GLfloat cylindr[20] = {

		 0.8f , S1.diametr_SI / 2 - 0.01f, 0,		1.0f,1.0f,
		-0.8f , S1.diametr_SI / 2 - 0.01f, 0,		1.0f,0.0f,
		-0.8f ,-S1.diametr_SI / 2 + 0.01f, 0,		0.0f,0.0f,
		 0.8f ,-S1.diametr_SI / 2 + 0.01f, 0,		0.0f,1.0f
	};

	GLfloat coil[20] = {
		S1.height_SI / 2, S1.diametr_SI / 2 , 0,		1.0f,1.0f,
		S1.height_SI / 2, -S1.diametr_SI / 2, 0,		1.0f,0.0f,
		-S1.height_SI / 2, -S1.diametr_SI / 2, 0,		0.0f,0.0f,
		-S1.height_SI / 2 , S1.diametr_SI / 2, 0,		0.0f,1.0f
	};


	
	// Graph objects:
	object mag1(porsh, vec1, 4, 5);
	object mag2(porsh, zero - vec1, 4, 5);
	object magleft_static(porsh, 2.9 * vec1, 4, 5);
	object magright_static(porsh, zero - 2.9 * vec1, 4, 5);
	object coil1(coil, coic, 4, 5);
	object coil2(coil, zero - coic, 4, 5);


	// Graph objects setup:
// resetting for screen:
	reset_for_screen(mag1.zero_points, 4, 5);
	reset_for_screen(coil1.zero_points, 4, 5);
	reset_for_screen(cylindr, 4, 5);

	// texture loading:
	mag1.set_texture("C:/BH.jpg");
	mag2.set_texture("C:/BH.jpg");
	magleft_static.set_texture("C:/BH.jpg");
	magright_static.set_texture("C:/BH.jpg");
	coil1.set_texture("C:/container.jpg");
	coil2.set_texture("C:/container.jpg");

	// first reloc:
	coil1.reloc();
	coil2.reloc();
	mag1.reloc();
	mag2.reloc();
	magleft_static.reloc();
	magright_static.reloc();

	// Backgrounds:
// positions:
	vecter gr(0.6, 0.6, 0);


	// objects:
	object background(cylindr, zero, 4, 5);
	// textures:
	background.set_texture("C:/background.jpg");
	// first reloc:
	background.reloc();


	// Plots:
//positions:
	vecter graph(0.6, 0.6, 0);


	//plot's init:
	grafik EDS(100, 0.5f, graph);


	//Plot's colors:
	EDS.reset_color(1.0f, 0.0f, 0.0f, 1.0f, EDS.shaderProgram);


	// first reloc:
	EDS.reloc();

	//buffers
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	// consol cout parametrs:
	cout.width(6);
	cout.scientific;
	cout.precision(6);

	// counters: 
	long int clock1 = 0;

	double f1 = 0, E = 0, c1 = 0, c2 = 0;

	//Time precision:
	double dtime = 0.01, time = 0;
	int dddddd = 0;;

	// Game loop:
	while (!glfwWindowShouldClose(window))
	{
		time += dtime;
		clock1++;

		glfwPollEvents();

		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Resetting currents in coils
		c2 = S1.flow_X_from_mag(mag_left) - S1.flow_X_from_mag(mag_right);
		S1.current = (c2 - c1) * 100000 / 1.5;
		S2.current = S1.current;
		c1 = c2;
		E += 2 * S1.current * S1.current / 100000 * 1.5;
		if (clock1 < 5)
			E = 0;


		if ((gas_left.phase == 4) && (dddddd == 0))
		{
			gas_left.P = 1.1 * Patm;

		}
		if ((gas_left.phase != 4) && (dddddd == 0))
		{
			dddddd = 1;

		}
		/*if ((gas_centr.phase == 4) && (abs(mag_left.speed_SI.x_proj) > 10))
		{
			gas_centr.P =  gas_left.P;

		}*/
		// resetting forces  
		mag_left.force_on.set(0, 0, 0);
		mag_right.force_on.set(0, 0, 0);
		mag_left.force_on.x_proj = S1.F_from_coil(mag_left).x_proj + S2.F_from_coil(mag_left).x_proj +
			mag_right.Mag_Mag_F(mag_left, 100).x_proj - mag_right_static.Mag_Mag_F(mag_left, 100).x_proj +
			mag_left_static.Mag_Mag_F(mag_left, 100).x_proj -
			0 * mag_left.speed_SI.x_proj + gas_left.Force() - gas_centr.Force();

		mag_right.force_on.x_proj = -mag_left.force_on.x_proj;
		cout << "Phase L:" << gas_left.phase << " Phase C:" << gas_centr.phase
			<< " L Temp:" << gas_left.T - 273 << "  C Temp: " << gas_centr.T - 273
			<< " L sp" << mag_left.speed_SI.x_proj << endl;


		// relocating pistons:  
		mag_right.relocate(dtime / 1000);
		mag_left.relocate(dtime / 1000);

		// resetting gases
		if ((abs(mag_left.position_SI.x_proj) < 0.12) && (gas_left.phase == 3))
		{
			gas_left.phase = 4;
			gas_left.counter = 3;
		}

		gas_left.GasFullUpdate(dtime / 1000,
			S_porsh * abs(-0.8 - mag_left.position_SI.x_proj + mag_left.height_SI / 2), abs(mag_left.speed_SI.x_proj));
		gas_centr.GasFullUpdate(dtime / 1000,
			2 * S_porsh * abs(-mag_left.position_SI.x_proj + mag_left.height_SI / 2), abs(mag_left.speed_SI.x_proj));




		// resetting positions:
		mag1.centr.x_proj = mag_left.position_SI.x_proj;
		mag2.centr.x_proj = mag_right.position_SI.x_proj;




		// graph object's relocating:
		mag1.reloc();
		mag2.reloc();



		if (clock1 % 100 == 0)
		{
			EDS.reloc(S1.current / 10000 / 2);
		}






		// Drawing:

		coil1.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
		coil2.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
		background.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
		mag1.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
		mag2.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
		magleft_static.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
		magright_static.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
		EDS.draw(VBO, VAO);
		glfwSwapBuffers(window);

	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}