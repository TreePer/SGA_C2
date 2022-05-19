#pragma once

void init(Object* _Obj, char* name = nullptr, int px = 0, int py = 0, int pz = 0);
char* SetName();
void SetCursorPosition(int _x, int _y);
void SetTextColor(int color);
void OnDrawText(char* _str, int _x, int _y, int color = 15);
void OnDrawText(int value, int _x, int _y, int color = 15);
void HideCursor(bool _visible);
void Output(Object* _Obj);
void Collision(Object* _Player, Object* _block);
Object* Createbullet(const int x, const int y);

void init(Object* _Obj, char* name, int px, int py, int pz) {
	_Obj->Info.Texture = (name == nullptr ? SetName() : name);

	_Obj->Speed = 0;

	_Obj->TransInfo.Position = Vector(px, py, pz);
	_Obj->TransInfo.Rotation = Vector(0, 0, 0);
	_Obj->TransInfo.Scale = Vector(strlen(_Obj->Info.Texture), 1, 0);
}

char* SetName() {
	char name1[128] = "";

	cout << "이름을 입력하시오 : ";
	cin >> name1;

	char* name = new char[strlen(name1) + 1];

	strcpy(name, name1);

	return name;
}

void SetCursorPosition(int _x, int _y) {
	COORD Pos = { (short)_x, (short)_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(int color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

void OnDrawText(char* _str, int _x, int _y, int color) {
	SetCursorPosition(_x, _y);
	SetTextColor(color);
	cout << _str;
}

void OnDrawText(int value, int _x, int _y, int color) {
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

void Collision(Object* _Player, Object* _block) {
	if (_Player->TransInfo.Position.x + _Player->TransInfo.Scale.x > _block->TransInfo.Position.x &&
		_Player->TransInfo.Position.x < _block->TransInfo.Position.x + _block->TransInfo.Scale.x &&
		_Player->TransInfo.Position.y == _block->TransInfo.Position.y) {
		OnDrawText((char*)"충돌", 30, 2);
	}
}

Object* Createbullet(const int x, const int y) {
	Object* pBullet = new Object;

	init(pBullet, (char*)"==o", x + 2, y);

	return pBullet;
}