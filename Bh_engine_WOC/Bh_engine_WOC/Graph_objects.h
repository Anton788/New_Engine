#pragma once
#include <iostream>
#include <cmath>
#include <time.h>
#include <vecters.h>
#include <shader.h> 
#include <string>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// GLEW
#define GLEW_STATIC
#include <glew.h>

// GLFW
#include <GLFW/glfw3.h>
// Window dimensions
using namespace std;




class object
{
public:
	//double mass, radius;
	vecter centr;
	GLuint pointnum, size_of_points, point_size, size_of_tries;
	GLfloat *points;
	GLfloat *zero_points;
	
	long int clock_bef, clock_now;
	GLfloat color[4];
	Shader* shader;
	GLuint texture1;
	object()
	{
		cout << "Center coord:" << endl;
		cin >> centr.x_proj >> centr.y_proj >> centr.z_proj;
		cout << "Number of points:" << endl;
		cin >> pointnum;
		cout << "Enter points:" << endl;
		points = new float[3 * pointnum];
		zero_points = new float[3 * pointnum];
		for (int i = 0; i < pointnum; i++)
		{
			cout << "point N" << (i + 1) << endl;
			cin >> zero_points[3 * i] >> zero_points[3 * i + 1] >> zero_points[3 * i + 2];
			cout << endl;
			points[3 * i] = zero_points[3 * i];
			points[3 * i + 1] = zero_points[3 * i + 1];
			points[3 * i + 2] = zero_points[3 * i + 2];
		}
		clock_now = clock_bef = clock();
		cout << "Enter color:" << endl;
		for (int i = 0; i < 4; i++)
		{
			cin >> color[i];
		}
	}
	object(GLfloat * pointdat,  vecter coordc,  int Num_of_points,int size_of_point)
	{
		zero_points = pointdat;
		point_size = size_of_point;
		
		centr = coordc;
		pointnum = Num_of_points;
		
		size_of_points = size_of_point * pointnum * sizeof(GLfloat);
		points = new float[size_of_point * pointnum];
		for (int i = 0; i < pointnum; i++)
		{
			for (int _k = 0; _k < size_of_point; _k++)
			{
				points[size_of_point * i + _k] = zero_points[size_of_point * i + _k];
			}
		}
		clock_now = clock_bef = clock();
	}
	void reloc() 
	{
		for (int i = 0; i < pointnum; i++)
		{
			for (int _k = 0; _k < point_size; _k++)
			{ 
				if (_k > 2)
					points[point_size * i +_k] = zero_points[point_size * i +_k];
				else if (_k == 0)
					points[point_size * i +_k] = zero_points[point_size * i +_k] + centr.x_proj;
				else if (_k==1)
					points[point_size * i +_k] = zero_points[point_size * i +_k] + centr.y_proj;
				else if (_k==2)
					points[point_size * i +_k] = zero_points[point_size * i +_k] + centr.z_proj;
			}
		}
	}
	void set(GLfloat * pointdat, vecter coordc, int size)
	{
		zero_points = pointdat;

		centr = coordc;
		
		pointnum = size;
		points = new float[3 * pointnum];
		for (int i = 0; i < pointnum; i++)
		{
			points[point_size  * i] = zero_points[point_size  * i];
			points[point_size  * i + 1] = zero_points[point_size  * i + 1];
			points[point_size  * i + 2] = zero_points[point_size  * i + 2];
		}
		clock_now = clock_bef = clock();
	}
	void set_shaders(GLchar* path_to_vertex, GLchar* path_to_fragment)
	{
		Shader tmp(path_to_vertex, path_to_fragment);
		shader = &tmp;
	}
	void set_texture(const char* path_to_texture)
	{
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
												// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Load, create texture and generate mipmaps
		int width, height;
		unsigned char* image = SOIL_load_image(path_to_texture, &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.


	}
	void draw(GLenum mode, GLuint VBO, GLuint VAO, Shader ourShader)
	{

		ourShader.Use();
		glBindTexture(GL_TEXTURE_2D, texture1);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size_of_points, points, GL_STATIC_DRAW);


		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, point_size * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, point_size * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(2);

		//glBindVertexArray(0);


		

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture1);
		//glUniform1i(glGetUniformLocation(ourShader.Program, name_of_Texture), 0);

		

		// Draw container
		
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);

		


		


		

	}
	void reset_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat black)
	{
		color[0] = red;
		color[1] = green;
		color[2] = blue;
		color[3] = black;
	}
};



class grafik {
public:
	
	vecter centr;
	int pointnum;
	GLfloat *points, *zero_points;	
	GLfloat color[4], size_x;
	GLchar* vertexShaderSource;
	GLchar* fragmentShaderSource;
	GLuint shaderProgram, VTCLLC;
	grafik()
	{
		
		cout << "Enter color:" << endl;
		for (int i = 0; i < 4; i++)
		{
			cin >> color[i];
		}

	}
	grafik(int _pointnum, float sizex, vecter coordc)
	{
		centr = coordc;
		size_x = sizex;
		pointnum = _pointnum;
		points = new float[3 * pointnum];
		zero_points = new float[3 * pointnum];
		for (int i = 0; i < pointnum; i++)
		{
			points[3 * i] = zero_points[3 * i] = sizex / pointnum * (float)(i - pointnum / 2) + coordc.x_proj;
			points[3 * i + 1] = zero_points[3 * i + 1] = coordc.y_proj;
			points[3 * i + 2] = zero_points[3 * i + 2] = 0;
		}
		for (int i = 0; i < 4; i++)
		{
			color[i] = 0.5;
		}
		set_shaders();
	}
	void set_shaders()
	{
		vertexShaderSource = (GLchar*)"#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"layout (location = 1) in vec3 color;\n"
			"out vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(position, 1.0);\n"
			"ourColor = color;\n"
			"}\0";
		fragmentShaderSource = (GLchar*)"#version 330 core\n"
			"out vec4 color;\n"
			"uniform vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"color = ourColor;\n"
			"}\n\0";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// Check for compile time errors
		GLint success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// Check for compile time errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// Link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// Check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void reloc()
	{
		for (int i = 0; i < 3 * pointnum; i++)
		{

			points[i] = zero_points[i];
		}
	}
	void reloc(float _y_last)
	{
			for (int i = 0; i < pointnum; i++)
			{

				points[3 * i + 1] = points[3 * (i + 1) + 1];
			}
		
			points[3 * pointnum - 2 ] = zero_points[3 * pointnum - 2] + _y_last;
	}

	void draw(GLuint VBO, GLuint VAO)
	{
		glUseProgram(shaderProgram);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferData(GL_ARRAY_BUFFER, 3 * pointnum * sizeof(GLfloat), points, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		VTCLLC = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(VTCLLC, color[0], color[1], color[2], color[3]);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, pointnum);
		glBindVertexArray(0);

	}
	
	void reset_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat black, GLuint shaderProg)
	{
		color[0] = red;
		color[1] = green;
		color[2] = blue;
		color[3] = black;
		VTCLLC = glGetUniformLocation(shaderProg, "ourColor");
	}
};


GLfloat* Circle_arr(GLfloat radius, int prec)
{
	GLfloat *tmp = new GLfloat[3 * prec];
	for (int i = 0; i < prec; i++)
	{
		tmp[3 * i] = radius*cos(2 * 3.14159265358979323 / prec*i);
		tmp[3 * i + 1] = radius*sin(2 * 3.14159265358979323 / prec*i);
		tmp[3 * i + 2] = 0;
	}
	return tmp;
}
float* Ellips_arr(float big_r, int prec, double _e, double angle)
{
	float *tmp = new float[3 * prec];
	float x, y;
	for (int i = 0; i < prec; i++)
	{
		tmp[3 * i] = big_r*cos(2 * 3.14159265358979323 / prec*i);
		tmp[3 * i + 1] = big_r*sin(2 * 3.14159265358979323 / prec*i)  * sqrt(1 - _e *_e);
		tmp[3 * i + 2] = 0;
		x = tmp[3 * i];
		y = tmp[3 * i + 1];
		tmp[3 * i] = x * cos(angle) + y * sin(angle);
		tmp[3 * i + 1] = (-x *sin(angle) + y* cos(angle));
	}
	return tmp;
}
void reloc(float*arr, float dx, float dy, int size)
{

	for (int i = 0; i < size; i++)
	{
		arr[3 * i] = arr[3 * i] + dx;
		arr[3 * i + 1] = arr[3 * i + 1] + dy;
		arr[3 * i + 2] = 0;
	}

}
void rotate(float*arr, float angle, int size)
{
	float x, y;
	for (int i = 0; i < size; i++)
	{

		x = arr[3 * i];
		y = arr[3 * i + 1];
		arr[3 * i] = x * cos(angle) + y * sin(angle);
		arr[3 * i + 1] = (-x *sin(angle) + y* cos(angle));
	}
}