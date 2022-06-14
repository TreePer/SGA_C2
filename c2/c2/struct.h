#pragma once

struct Vector {
	float x = 0, y = 0, z = 0;

	Vector() {};

	Vector(float _x, float _y) : x(_x), y(_y) {};
	Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
};

struct TransForm {
	Vector Position;
	Vector Rotation;
	Vector Scale;
};

struct Info {
	char* Texture;
	int item;
	int life;
};

struct Object {
	Info Info;
	TransForm TransInfo;
};