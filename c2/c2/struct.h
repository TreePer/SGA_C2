#pragma once

struct Vector {
	int x = 0, y = 0, z = 0;

	Vector() {};

	Vector(int _x, int _y) : x(_x), y(_y) {};
	Vector(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {};
};

struct TransForm {
	Vector Position;
	Vector Rotation;
	Vector Scale;
};

struct Info {
	char* Texture;
	int Color;
};

struct Object {
	char* Name;
	int Speed;
	Info Info;
	TransForm TransInfo;
};

struct TextInfo {
	int Option;
	Info Info;
	TransForm TransInfo;
};