// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>

#include "Vertice.h"
#include "Shader.h"
#include "Modelo.h"

using namespace std;

GLfloat red, green, blue;

GLuint posicionID;
GLuint colorID;

Modelo *figura;
Modelo *figuraCuadrado;

Shader *shader;

void actualizar() {

}

void dibujar() {
		figura->dibujar(GL_POLYGON);
		figuraCuadrado->dibujar(GL_POLYGON);
}

void inicializarFigura() {
	figura = new Modelo();
	Vertice v1 =
	{ vec3(-1.0f,0.5f,0.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	Vertice v2 =
	{ vec3(0.0f,-0.5f,0.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	Vertice v3 =
	{ vec3(1.0f,0.5f,0.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	figura->vertices.push_back(v1);
	figura->vertices.push_back(v2);
	figura->vertices.push_back(v3);
}

void inicializarFiguraCuadrado()
{
	figuraCuadrado = new Modelo();
	Vertice v1 =
	{ vec3(-0.5f,-0.5f,0.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	Vertice v2 =
	{ vec3(-0.5f,0.5f,0.0f), vec4(1.0f,0.0f,0.0f,1.0f) };
	Vertice v3 =
	{ vec3(0.5f,0.5f,0.0f), vec4(1.0f,0.0f,0.0f,1.0f) };
	Vertice v4 =
	{ vec3(0.5f,-0.5f,0.0f), vec4(1.0f,0.0f,1.0f,1.0f) };
	figuraCuadrado->vertices.push_back(v1);
	figuraCuadrado->vertices.push_back(v2);
	figuraCuadrado->vertices.push_back(v3);
	figuraCuadrado->vertices.push_back(v4);
}

int main()
{
	//Declaración de ventana
	GLFWwindow *window;
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW
	if (!glfwInit()) {
		//Si no se inició bien, terminar la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verficar si se creó bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializó bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;


	red = green = blue = 0.75f;

	inicializarFigura();
	inicializarFiguraCuadrado();

	//Crear instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";
	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID =
		glGetAttribLocation(shader->getID(), "posicion");
	colorID =
		glGetAttribLocation(shader->getID(), "color");

	//Desenlazar shader
	shader->desenlazarShader();

	figura->shader = shader;
	figura->inicializarVertexArray(posicionID, colorID);

	figuraCuadrado->shader = shader;
	figuraCuadrado->inicializarVertexArray(posicionID, colorID);

	//Habilitar el atributo solo en el vertex array en uso
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	//Especificar a OpenGL como usar la memoria con ese atributo
	glVertexAttribPointer(posicionID, 3, GL_FLOAT,
		GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertice), (void*) sizeof(vec3));

	//Soltarlos
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

