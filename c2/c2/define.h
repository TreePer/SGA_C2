#pragma once

void init(Object* _Obj, char* name = nullptr, float px = 0, float py = 0, float pz = 0);
char* SetName();
void SetCursorPosition(float _x, float _y);
void SetTextColor(int color);
void OnDrawText(char* _str, float _x, float _y, int color = 15);
void OnDrawText(int value, float _x, float _y, int color = 15);
void HideCursor(bool _visible);
void Output(Object* _Obj);
bool Collision(Object* _Player, Object* _block);
Object* Createbullet(const float x, const float y);
void UpdateInput(Object* _Obj);
float GetDistance(Object* _Player, Object* _Temp);
Vector GetDistanceV(Object* _Player, Object* _Temp);

void init(Object* _Obj, char* name, float px, float py, float pz) {
	_Obj->Info.Texture = (name == nullptr ? SetName() : name);

	_Obj->Speed = 0;

	_Obj->TransInfo.Position = Vector(px, py, pz);
	_Obj->TransInfo.Rotation = Vector(0, 0, 0);
	_Obj->TransInfo.Scale = Vector(strlen(_Obj->Info.Texture), 1.0f, 0);
}

char* SetName() {
	char name1[128] = "";

	cout << "이름을 입력하시오 : ";
	cin >> name1;

	char* name = new char[strlen(name1) + 1];

	strcpy(name, name1);

	return name;
}

void SetCursorPosition(float _x, float _y) {
	COORD Pos = { (short)_x, (short)_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(int color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

void OnDrawText(char* _str, float _x, float _y, int color) {
	SetCursorPosition(_x, _y);
	SetTextColor(color);
	cout << _str;
}

void OnDrawText(int value, float _x, float _y, int color) {
	SetCursorPosition(_x, _y);
	SetTextColor(color);

	char* text = new char[4];
	_itoa(value, text, 10);

	cout << text;
}

void HideCursor(bool _visible) {
	CONSOLE_CURSOR_INFO Info;

	Info.bVisible = _visible;
	Info.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Output(Object* _Obj) {
	if (_Obj->Info.Texture == nullptr) {
		OnDrawText((char*)"NULL", _Obj->TransInfo.Position.x, _Obj->TransInfo.Position.y);
	}
	else {
		OnDrawText(_Obj->Info.Texture, _Obj->TransInfo.Position.x, _Obj->TransInfo.Position.y);
	}
}

bool Collision(Object* _Player, Object* _block) {
	if (_Player->TransInfo.Position.x + _Player->TransInfo.Scale.x >= _block->TransInfo.Position.x &&
		_Player->TransInfo.Position.x <= _block->TransInfo.Position.x + _block->TransInfo.Scale.x &&
		_Player->TransInfo.Position.y == _block->TransInfo.Position.y) {
		return true;
	}
	return false;
}

Object* Createbullet(const float x, const float y, const int speed) {
	Object* pBullet = new Object;

	init(pBullet, (char*)"==o", x + 2, y);
	pBullet->Speed = speed;

	return pBullet;
}

Object* CreateEnemy(const float x, const float y) {
	Object* pEnemy = new Object;

	init(pEnemy, (char*)"훗", x, y);

	return pEnemy;
}

Object* CreateEnemybullet(const float x, const float y) {
	Object* pBullet = new Object;

	init(pBullet, (char*)"o==", x - 2, y);

	return pBullet;
}

void UpdateInput(Object* _Obj) {

	if (GetAsyncKeyState(VK_UP))
		_Obj->TransInfo.Position.y -= 1;

	if (GetAsyncKeyState(VK_DOWN))
		_Obj->TransInfo.Position.y += 1;

	if (GetAsyncKeyState(VK_LEFT))
		_Obj->TransInfo.Position.x -= 2;

	if (GetAsyncKeyState(VK_RIGHT))
		_Obj->TransInfo.Position.x += 2;
}

float GetDistance(Object* _Player, Object* _Temp) {
	float x = _Player->TransInfo.Position.x - _Temp->TransInfo.Position.x;
	float y = _Player->TransInfo.Position.y - _Temp->TransInfo.Position.y;

	return sqrt((x * x) + (y * y));
}

Vector GetDistanceV(Object* _Player, Object* _Temp) {
	float x = _Player->TransInfo.Position.x - _Temp->TransInfo.Position.x;
	float y = _Player->TransInfo.Position.y - _Temp->TransInfo.Position.y;
	float z = sqrt((x * x) + (y * y));

	return Vector(x / z, y / z);
}