#pragma once
#include <iostream>
#include <cmath>
#include <time.h>
#include <vecters.h>
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
	double mass, radius;
	vecter centr, speed, accel;
	int pointnum;
	GLfloat *points;
	GLfloat *zero_points;
	long int clock_bef, clock_now;
	GLfloat color[4];
	GLchar* vertexShaderSource;
	GLchar* fragmentShaderSource;
	object()
	{
		cout << "Center coord:" << endl;
		cin >> centr.x_proj >> centr.y_proj >> centr.z_proj;
		cout << "speed:" << endl;
		cin >> speed.x_proj >> speed.y_proj >> speed.z_proj;
		cout << "accel:" << endl;
		cin >> accel.x_proj >> accel.y_proj >> accel.y_proj;
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
	object(GLfloat * pointdat, vecter coordc, vecter coordv, vecter acc, int size)
	{
		zero_points = pointdat;

		centr = coordc;
		speed = coordv;
		accel = acc;
		pointnum = size;
		points = new float[3 * pointnum];
		for (int i = 0; i < pointnum; i++)
		{
			points[3 * i] = zero_points[3 * i];
			points[3 * i + 1] = zero_points[3 * i + 1];
			points[3 * i + 2] = zero_points[3 * i + 2];
		}
		clock_now = clock_bef = clock();
	}
	void set(GLfloat * pointdat, vecter coordc, vecter coordv, vecter acc, int size)
	{
		zero_points = pointdat;

		centr = coordc;
		speed = coordv;
		accel = acc;
		pointnum = size;
		points = new float[3 * pointnum];
		for (int i = 0; i < pointnum; i++)
		{
			points[3 * i] = zero_points[3 * i];
			points[3 * i + 1] = zero_points[3 * i + 1];
			points[3 * i + 2] = zero_points[3 * i + 2];
		}
		clock_now = clock_bef = clock();
	}
	GLuint shaderProgram;
	void set_shaders(GLchar* vertex, GLchar* fragment)
	{
		vertexShaderSource = vertex;
		fragmentShaderSource = fragment;
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
	void reloc(double dt)
	{
		centr += ((speed*dt) + (accel*((dt*dt) / 2)));
		speed += (accel*dt);
		for (int i = 0; i < pointnum; i++)
		{
			points[3 * i] = zero_points[3 * i] + centr.x_proj;
			points[3 * i + 1] = zero_points[3 * i + 1] + centr.y_proj;
			points[3 * i + 2] = zero_points[3 * i + 2] + centr.z_proj;
		}

	}
	void reloc()
	{
		
		for (int i = 0; i < pointnum; i++)
		{
			points[3 * i] = zero_points[3 * i] + centr.x_proj;
			points[3 * i + 1] = zero_points[3 * i + 1] + centr.y_proj;
			points[3 * i + 2] = zero_points[3 * i + 2] + centr.z_proj;
		}
		
	}
	void draw(GLenum mode, GLuint VBO, GLuint VAO, GLuint shaderProg)
	{


		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 3 * pointnum * sizeof(GLfloat), points, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		GLint vertexColorLocation = glGetUniformLocation(shaderProg, "ourColor");
		glUniform4f(vertexColorLocation, color[0], color[1], color[2], color[3]);
		glBindVertexArray(VAO);


		glDrawArrays(mode, 0, pointnum);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

	}
	void draw(GLenum mode, GLuint VBO, GLuint VAO, void func(float*arr, int size, ...), ...)
	{

		func(points, pointnum);
		for (int i = 0; i < pointnum; i++)
		{
			points[3 * i] = zero_points[3 * i] + centr.x_proj;
			points[3 * i + 1] = zero_points[3 * i + 1] + centr.y_proj;
			points[3 * i + 2] = zero_points[3 * i + 2] + centr.z_proj;
		}
		//glUseProgram(shaderProgram);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 3 * pointnum * sizeof(GLfloat), points, GL_STATIC_DRAW);
		glBindVertexArray(VAO);
		glDrawArrays(mode, 0, pointnum);
		glBindVertexArray(0);
	}
	void Set_acc(vecter acc)
	{
		accel += acc;
	}
	void reset_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat black)
	{
		color[0] = red;
		color[1] = green;
		color[2] = blue;
		color[3] = black;
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