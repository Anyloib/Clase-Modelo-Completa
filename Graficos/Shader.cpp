#include "stdafx.h"
#include "Shader.h"

GLuint Shader::getID() {
	return shaderID;
}

Shader::Shader(const char * rutaVertex, const char * rutaFragment) {

	//Aqui se va a guardar el texto del vertex shader
	string codigoVertexShader;
	//Declara input stream para leer archivo del vertex shader
	ifstream vertexShaderStream(rutaVertex, ios::in);
	//Verificamos si se pudo abrir el archivo
	if (vertexShaderStream.is_open()) {
		//Declaramos un string que irá tomando el valor
		//de cada linea de texto del archivo
		string linea = "";
		//Recorremos linea por linea el archivo
		while (getline(vertexShaderStream,linea)) {
			//Concatenamos cada linea para obtener el texto completo
			codigoVertexShader += linea + "\n";
		}
		//Cerramos el stream
		vertexShaderStream.close();
	}
	else {
		//Mensaje de error que no se pudo abrir el archivo
		cout << "No se pudo abrir el archivo: " << rutaVertex;
		exit(EXIT_FAILURE);
	}

	//Ahora lo mismo pero para el fragment
	string codigoFragmentShader;
	ifstream fragmentShaderStream(rutaFragment, ios::in);
	if (fragmentShaderStream.is_open()) {
		string linea = "";
		while (getline(fragmentShaderStream, linea)) {
			codigoFragmentShader += linea + "\n";
		}
		fragmentShaderStream.close();
	}
	else {
		cout << "No se pudo abrir el archivo: " << rutaFragment;
		exit(EXIT_FAILURE);
	}

	//Conversion de formato string a cadena de chars
	const char * cadenaCodigoVertex = 
		codigoVertexShader.c_str();
	const char * cadenaCodigoFragment =
		codigoFragmentShader.c_str();

	//1.- Crear programa
	shaderID = glCreateProgram();
	GLuint vertexShaderID = 
		glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID =
		glCreateShader(GL_FRAGMENT_SHADER);

	//2.- Cargar los shaders
	glShaderSource(vertexShaderID, 1, &cadenaCodigoVertex, NULL);
	glShaderSource(fragmentShaderID, 1, &cadenaCodigoFragment, NULL);

	//3.- compilar los shaders
	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	//4.- Verificar la compilacion
	verificarCompilacion(vertexShaderID);
	verificarCompilacion(fragmentShaderID);

	//5.- Adjuntar shader al programa
	glAttachShader(shaderID, vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);

	//6.- Vincular el programa a OpenGL
	glLinkProgram(shaderID);

	//7.- Verificar la vinculación
	verificarVinculacion(shaderID);

	//8.- Usar el programa
	glUseProgram(shaderID);

}

void Shader::enlazarShader() {
	glUseProgram(shaderID);
}

void Shader::desenlazarShader() {
	glUseProgram(0);
}

void Shader::verificarCompilacion(GLuint id) {
	GLint resultado = GL_FALSE;
	int longitudLog = 0;

	glGetShaderiv(id, GL_COMPILE_STATUS, &resultado);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &longitudLog);

	if (longitudLog > 0) {
		vector<char> mensajeError(longitudLog + 1);
		glGetShaderInfoLog(id, longitudLog, NULL, &mensajeError[0]);
		for (vector<char>::const_iterator i = mensajeError.begin();
			i != mensajeError.end(); i++) {
			cout << *i;
		}

	}
}

void Shader::verificarVinculacion(GLuint id) {
	GLint estadoVinculacion, estadoValidacion;
	glGetProgramiv(id, GL_LINK_STATUS, &estadoVinculacion);
	if (estadoVinculacion == GL_FALSE) {
		cout << "Falló la vinculación";
	}

	glGetProgramiv(id, GL_VALIDATE_STATUS, &estadoValidacion);
	if (estadoValidacion == GL_FALSE) {
		cout << "Falló la validación";
	}
}

