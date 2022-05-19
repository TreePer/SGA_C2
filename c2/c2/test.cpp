#include "Headers.h"

int main(void) {

	HideCursor(false);

	TextInfo BackGround[30];

	system("mode con:cols=150 lines=30");

	for (int i = 0; i < 30; ++i) {
			srand((GetTickCount64() + i) * (GetTickCount64() + i) + i + i);

			switch ((rand() % 5)) {
			case 0 :
				BackGround[i].Info.Texture = (char*)"*";
				break;
			case 1 :
				BackGround[i].Info.Texture = (char*)"&";
				break;
			case 2 :
				BackGround[i].Info.Texture = (char*)"\\";
				break;
			case 3 :
				BackGround[i].Info.Texture = (char*)"|";
				break;
			case 4:
				BackGround[i].Info.Texture = (char*)"$";
				
				break;
			}

			BackGround[i].Info.Color = rand() % 16;
			BackGround[i].Option = 0;

			BackGround[i].TransInfo.Position.x = rand() % 149 + 1;
			BackGround[i].TransInfo.Position.y = rand() % 29 + 1;
		
	}


	Object* Player = new Object;
	Object* Enemy = new Object;
	Object* Bullet[128];

	init(Player, (char*)"¿ô", 10, 20);
	init(Enemy, (char*)"ÈÊ", 30, 15);

	for (int i = 0; i < 128; ++i) {
		Bullet[i] = new Object;
		Bullet[i] = nullptr;
	}

	int BulletCount = 0;

	LONGLONG Time = GetTickCount64();

	while (true) {
		if (Time + 80 < GetTickCount64()) {
			Time = GetTickCount64();

			system("cls");

			

			for (int i = 0; i < 30; ++i) {
				OnDrawText(BackGround[i].Info.Texture, BackGround[i].TransInfo.Position.x, BackGround[i].TransInfo.Position.y, BackGround[i].Info.Color);
			}


			if (GetAsyncKeyState(VK_SPACE)) {
				for (int i = 0; i < 128; ++i) {
					if (Bullet[i] == nullptr) {
						Bullet[i] = Createbullet(Player->TransInfo.Position.x, Player->TransInfo.Position.y);
						BulletCount++;
						break;
					}
				}
				
			}

			UpdateInput(Player);

			Collision(Player, Enemy);
			Output(Player);
			Output(Enemy);
			OnDrawText(BulletCount, 5, 2);

			for (int i = 0; i < 128; ++i) {
				if (Bullet[i] != nullptr && Bullet[i]->TransInfo.Position.x < 148)
					OnDrawText(Bullet[i]->Info.Texture, Bullet[i]->TransInfo.Position.x++, Bullet[i]->TransInfo.Position.y);

				if (Bullet[i] != nullptr && BulletHit(Enemy, Bullet[i])) {
					delete Bullet[i];
					Bullet[i] = nullptr;
					BulletCount--;
					OnDrawText((char*)"HIT!!", 5, 3);
				}

				if (Bullet[i] != nullptr && Bullet[i]->TransInfo.Position.x >= 148) {
					delete Bullet[i];
					Bullet[i] = nullptr;
					BulletCount--;
				}
			}
		}
	}


	return 0;
}