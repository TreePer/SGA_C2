#include "Headers.h"

int main(void) {

	HideCursor(false);

	TextInfo BackGround[30];

	system("mode con:cols=150 lines=30");

	for (int i = 0; i < 30; ++i) {
		srand((GetTickCount64() + i) * (GetTickCount64() + i) + i + i);

		switch ((rand() % 5)) {
		case 0:
			BackGround[i].Info.Texture = (char*)"*";
			break;
		case 1:
			BackGround[i].Info.Texture = (char*)"&";
			break;
		case 2:
			BackGround[i].Info.Texture = (char*)"\\";
			break;
		case 3:
			BackGround[i].Info.Texture = (char*)"|";
			break;
		case 4:
			BackGround[i].Info.Texture = (char*)"$";

			break;
		}

		BackGround[i].Info.Color = rand() % 16;
		BackGround[i].Option = 0;

		BackGround[i].TransInfo.Position.x = rand() % 149;
		BackGround[i].TransInfo.Position.y = rand() % 29;

	}


	Object* Player = new Object;
	Object* Enemy[32];
	Object* Bullet[128];
	Object* EnemyBullet[128];

	Object* Temp = nullptr;

	Vector Test;

	

	init(Player, (char*)"웃", 10, 20);

	Enemy[0] = new Object;
	init(Enemy[0], (char*)"훗", 30, 15);

	for (int i = 1; i < 32; ++i) {
		Enemy[i] = nullptr;
	}
	
	

	for (int i = 0; i < 128; ++i) {
		Bullet[i] = nullptr;
		EnemyBullet[i] = nullptr;
	}

	int BulletCount = 0;

	LONGLONG Time = GetTickCount64();
	LONGLONG EnemyTime = GetTickCount64();
	LONGLONG EnemyBulletTime = GetTickCount64();

	bool check = false;
	int speed = 1;

	while (true) {
		if (Time + 50 < GetTickCount64()) {
			Time = GetTickCount64();

			system("cls");



			for (int i = 0; i < 30; ++i) {
				OnDrawText(BackGround[i].Info.Texture, BackGround[i].TransInfo.Position.x, BackGround[i].TransInfo.Position.y, BackGround[i].Info.Color);
			}

			if (EnemyTime + 1500 < GetTickCount64()) {
				EnemyTime = GetTickCount64();

				for (int i = 0; i < 32; ++i) {
					if (Enemy[i] == nullptr) {
						srand((GetTickCount64() + i) * (GetTickCount64() + i) + i + i);

						float x = (rand() % 131) + 18;
						float y = (rand() % 29);

						if (x != Player->TransInfo.Position.x && y != Player->TransInfo.Position.y) {
							Enemy[i] = CreateEnemy(x, y);
							break;
						}
						
					}
				}
			}
			if (EnemyBulletTime + 300 < GetTickCount64()) {
				EnemyBulletTime = GetTickCount64();

				srand((GetTickCount64()) * (GetTickCount64()));

				int j = rand() % 32;

				for (int i = 0; i < 128; ++i) {
					if (EnemyBullet[i] == nullptr && Enemy[j] != nullptr) {
						EnemyBullet[i] = CreateEnemybullet(Enemy[j]->TransInfo.Position.x, Enemy[j]->TransInfo.Position.y);
						break;
					}

				}
			}

			for (int i = 0; i < 128; ++i) {
				if (EnemyBullet[i] != nullptr && EnemyBullet[i]->TransInfo.Position.x > 0)
					OnDrawText(EnemyBullet[i]->Info.Texture, EnemyBullet[i]->TransInfo.Position.x--, EnemyBullet[i]->TransInfo.Position.y);

				if (EnemyBullet[i] != nullptr && Collision(Player, EnemyBullet[i])) {
					delete EnemyBullet[i];
					EnemyBullet[i] = nullptr;

					OnDrawText((char*)"HIT!!", 5, 5);
				}

				if (EnemyBullet[i] != nullptr && EnemyBullet[i]->TransInfo.Position.x <= 0) {
					delete EnemyBullet[i];
					EnemyBullet[i] = nullptr;
				}
			}


			if (!check && GetAsyncKeyState(VK_SPACE) & 0x8000) {
				check = true;
			}

			
			if (GetAsyncKeyState(VK_SPACE) & 0x8001) {
				if (speed < 10)
					speed++;
				
			}

			if (check && !(GetAsyncKeyState(VK_SPACE) & 0x8000)) {

				for (int i = 0; i < 128; ++i) {
					if (Bullet[i] == nullptr) {

						Bullet[i] = Createbullet(Player->TransInfo.Position.x, Player->TransInfo.Position.y, speed);
						BulletCount++;
						speed = 1;
						break;
					}
				}
				
				check = false;
			}
			
				

			UpdateInput(Player);

			for (int i = 0; i < 32; ++i) {
				if (Enemy[i] != nullptr && Collision(Player, Enemy[i])) {
					OnDrawText((char*)"충돌", 30, 2);
				}
				if (Enemy[i] != nullptr)
					Output(Enemy[i]);
			}
			
			
			Output(Player);
			

			OnDrawText(BulletCount, 5, 2);



			for (int i = 0; i < 128; ++i) {
				if (Bullet[i] != nullptr && Bullet[i]->TransInfo.Position.x < 148)
					OnDrawText(Bullet[i]->Info.Texture, Bullet[i]->TransInfo.Position.x += Bullet[i]->Speed, Bullet[i]->TransInfo.Position.y);

				for (int j = 0; j < 32; ++j) {
					if (Bullet[i] != nullptr && Enemy[j] != nullptr && Collision(Enemy[j], Bullet[i])) {
						delete Bullet[i];
						Bullet[i] = nullptr;
						delete Enemy[j];
						Enemy[j] = nullptr;
						BulletCount--;
						OnDrawText((char*)"HIT!!", 5, 3);
					}
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

/*
				Temp = new Object;

				Temp->TransInfo.Position.x = 80;
				Temp->TransInfo.Position.y = 10;

				Temp->Info.Texture = (char*)"☆";

				Test = GetDistanceV(Player, Temp);

			if (Temp != nullptr) {
				Output(Temp);



				Temp->TransInfo.Position.x += Test.x * speed;
				Temp->TransInfo.Position.y += Test.y * speed;

				OnDrawText((int)GetDistance(Player, Temp), 5, 8);
			}

			*/