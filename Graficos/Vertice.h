#pragma once

struct vec3 {
	vec3(float _x = 0, float _y = 0, float _z = 0) :
		x(_x), y(_y), z(_z) {}
	float x, y, z;
};

struct vec4 {
	vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) :
		x(_x), y(_y), z(_z), w(_w) {}
	float x, y, z, w;
};

struct Vertice {
	vec3 posicion;
	vec4 color;
};
