#version 330 core
//version

in vec4 fragmentColor;

//atributos
out vec4 salidaColor;

//funcion main
void main() {
	salidaColor = fragmentColor;
}