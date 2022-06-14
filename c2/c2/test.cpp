#include "Headers.h"

int main(void) {

	system("mode con:cols=150 lines=30");
	ScreenInit();	
	
	Logo();


	Object* Player = new Object;
	Object* Enemy[64];
	Object* Bullet[128];
	Object* Bullet2[128];
	Object* EnemyBullet[128];
	Object* EnemyBullet2[128];

	LONGLONG Time = GetTickCount64();
	LONGLONG Time2 = GetTickCount64();
	LONGLONG Time3 = GetTickCount64();
	LONGLONG Time4 = GetTickCount64();
	LONGLONG Time5 = GetTickCount64();

	FILE* map_file = fopen("map.csv", "r");

	char* map[30];

	char test[64];

	int jumpcount = 0;

	init(Player, (char*)"¿ô", 0.0f, 18.0f);

	for (int i = 0; i < 128; ++i) {
		Bullet[i] = nullptr;
		Bullet2[i] = nullptr;
		EnemyBullet[i] = nullptr;
		EnemyBullet2[i] = nullptr;
	}

	for (int i = 0; i < 64; ++i) {
		Enemy[i] = nullptr;
	}

	for (int i = 0; i < 30; ++i) {
		map[i] = new char[2048]();
		fgets(map[i], 2048, map_file);
		map[i] = SplitMap(map[i]);
	}

	fclose(map_file);

	while (Player->Info.life > -1) {
		
		if (Time + 50 < GetTickCount64()) {

			Time = GetTickCount64();

			ScreenClear();

			if (Player->TransInfo.Position.y < 30)
				UpdateInput(Player, map[(int)Player->TransInfo.Position.y]);	
			

			if (Time3 + 3000 < GetTickCount64()) {
				Time3 = GetTickCount64();

				for (int i = 0; i < 64; ++i) {
					if (Enemy[i] == nullptr) {
						if (Player->TransInfo.Position.y < 30) {
							if (MapPosition > 150) {
								for (int x = 0; x < 150; ++x) {
									if (map[(int)Player->TransInfo.Position.y][x + MapPosition] == '3') {
										Enemy[i] = CreateEnemy(x, Player->TransInfo.Position.y);
										if (Collision(Player, Enemy[i])) {
											delete Enemy[i];
											Enemy[i] = nullptr;
										}
										else if (map[(int)Enemy[i]->TransInfo.Position.y + 1][(int)Enemy[i]->TransInfo.Position.x] == '0') {
											delete Enemy[i];
											Enemy[i] = nullptr;
										}
										break;
									}
								
								}
							}
							else {
								for (int x = 0; x < 150; ++x) {
									if (map[(int)Player->TransInfo.Position.y][x] == '3') {
										Enemy[i] = CreateEnemy(x, Player->TransInfo.Position.y);
										if (Collision(Player, Enemy[i])) {
											delete Enemy[i];
											Enemy[i] = nullptr;
										}
										else if (map[(int)Enemy[i]->TransInfo.Position.y + 1][(int)Enemy[i]->TransInfo.Position.x] == '0') {
											delete Enemy[i];
											Enemy[i] = nullptr;
										}
										break;
									}
								}
							}

						}
					}
					break;
				}
			}

			if (Time4 + 6000 < GetTickCount64()) {
				Time4 = GetTickCount64();
				for (int i = 0; i < 64; ++i) {
					if (Enemy[i] != nullptr) {
						for (int j = 0; j < 128; ++j) {
							if (Enemy[i]->TransInfo.Rotation.x == 1) {
								if (EnemyBullet[i] == nullptr) {
									EnemyBullet[j] = Createbullet(Enemy[i]->TransInfo.Position.x + 3, Enemy[i]->TransInfo.Position.y);
									break;
								}
							}
							else {
								if (EnemyBullet2[j] == nullptr) {
									EnemyBullet2[j] = CreateEnemybullet(Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
									break;
								}
							}
						}
					}
				}
			}



			if (drop && GetAsyncKeyState(VK_LCONTROL) & 0x0001 && Player->Info.item == 1) {
				if (Player->TransInfo.Rotation.x == 1) {
					for (int i = 0; i < 128; ++i) {
						if (Bullet[i] == nullptr) {

							Bullet[i] = Createbullet(Player->TransInfo.Position.x, Player->TransInfo.Position.y);
							break;
						}
					}
				}
				else {
					for (int i = 0; i < 128; ++i) {
						if (Bullet2[i] == nullptr) {

							Bullet2[i] = CreateEnemybullet(Player->TransInfo.Position.x, Player->TransInfo.Position.y);
							break;
						}
					}
				}
			}



			if (!jump) {
				if (Time2 + 100 < GetTickCount64()) {
					Time2 = GetTickCount64();
					if (jumpcount < 3) {
						if (Player->TransInfo.Rotation.x == 1) {
							if (map[(int)Player->TransInfo.Position.y - 1][(int)Player->TransInfo.Position.x + MapPosition + 2] == '1') {
								jump = true;
								jumpcount = 6;
							}
							else if (Player->TransInfo.Position.x + Player->TransInfo.Scale.x >= 130 && MapPosition < 599) {
								MapPosition += 2;
								Player->TransInfo.Position.y -= 1;
								jumpcount++;
							}
							else {
								Player->TransInfo.Position.x += 2;
								Player->TransInfo.Position.y -= 1;
								jumpcount++;
							}

						}
						else {
							if (map[(int)Player->TransInfo.Position.y - 1][(int)Player->TransInfo.Position.x + MapPosition - 2] == '1') {
								jump = true;
								jumpcount = 6;
							}
							else if (Player->TransInfo.Position.x == 23 && MapPosition > 0) {
								MapPosition -= 2;
								Player->TransInfo.Position.y -= 1;
								jumpcount++;
							}
							else if (Player->TransInfo.Position.x > 1) {
								Player->TransInfo.Position.x -= 2;
								Player->TransInfo.Position.y -= 1;
								jumpcount++;
							}
							else {
								jump = true;
								jumpcount = 6;
							}

						}
						ScreenPrint((int)Player->TransInfo.Position.x, (int)Player->TransInfo.Position.y, Player->Info.Texture);
					}
					else if (jumpcount < 6) {
						if (Player->TransInfo.Rotation.x == 1) {
							if (map[(int)Player->TransInfo.Position.y + 1][(int)Player->TransInfo.Position.x + MapPosition + 2] == '1') {
								jump = true;
								jumpcount = 6;
							}
							else if (Player->TransInfo.Position.x + Player->TransInfo.Scale.x >= 130 && MapPosition < 599) {
								MapPosition += 2;
								Player->TransInfo.Position.y += 1;
								jumpcount++;
							}
							else {
								Player->TransInfo.Position.x += 2;
								Player->TransInfo.Position.y += 1;
								jumpcount++;
							}
						}
						else {
							if (map[(int)Player->TransInfo.Position.y + 1][(int)Player->TransInfo.Position.x + MapPosition - 2] == '1') {
								jump = true;
								jumpcount = 6;
							}
							else if (Player->TransInfo.Position.x == 23 && MapPosition > 0) {
								MapPosition -= 2;
								Player->TransInfo.Position.y += 1;
								jumpcount++;
							}
							else if (Player->TransInfo.Position.x > 1) {
								Player->TransInfo.Position.x -= 2;
								Player->TransInfo.Position.y += 1;
								jumpcount++;
							}
							else {
								jump = true;
								jumpcount = 6;
							}
						}
						ScreenPrint((int)Player->TransInfo.Position.x, (int)Player->TransInfo.Position.y, Player->Info.Texture);
					}

					if (jumpcount >= 6) {
						jump = true;
						jumpcount = 0;
					}
				}
			}

			if (!jump2) {
				if (Time5 + 100 < GetTickCount64()) {
					Time5 = GetTickCount64();
					if (Player->TransInfo.Position.y < 30) {
						if (jumpcount < 3) {
							if (map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x] == '1') {
								jump2 = true;
								jumpcount = 0;
							}
							else {
								Player->TransInfo.Position.y -= 1;
								jumpcount++;
							}
						}
						else if (jumpcount < 6) {
							Player->TransInfo.Position.y += 1;
							jumpcount++;

						}

						if (jumpcount >= 6) {
							jump2 = true;
							jumpcount = 0;
						}
						ScreenPrint((int)Player->TransInfo.Position.x, (int)Player->TransInfo.Position.y, Player->Info.Texture);
					}					
				}
			}

			if (jump && jump2 && Player->TransInfo.Position.y < 29) {
				if (Player->TransInfo.Rotation.x == 1 && map[(int)Player->TransInfo.Position.y + 1][(int)Player->TransInfo.Position.x + MapPosition] != '1') {
					drop = false;
					Player->TransInfo.Position.y++;
				}
				else if (Player->TransInfo.Rotation.x == -1 && map[(int)Player->TransInfo.Position.y + 1][(int)Player->TransInfo.Position.x + 3 + MapPosition] != '1') {
					drop = false;
					Player->TransInfo.Position.y++;
				}
				else {
					drop = true;
				}
			}
			else if (Player->TransInfo.Position.y == 29) {
				drop = true;
				gameover = true;
			}


			for (int i = 0; i < 64; ++i) {
				if (Enemy[i] != nullptr) {
					if (Enemy[i]->TransInfo.Position.y < 30) {
						if (Enemy[i]->TransInfo.Rotation.x == 1) {
							if (map[(int)Enemy[i]->TransInfo.Position.y][(int)Enemy[i]->TransInfo.Position.x + MapPosition + 1] == '3') {
								if (Enemy[i]->TransInfo.Position.x > 143) {
									Enemy[i]->Info.Texture = (char*)"¤¡ÈÊ";
									Enemy[i]->TransInfo.Rotation.x = -1;
									ScreenPrint(Enemy[i]->TransInfo.Position.x--, Enemy[i]->TransInfo.Position.y, Enemy[i]->Info.Texture);
								}
								else {
									ScreenPrint(Enemy[i]->TransInfo.Position.x++, Enemy[i]->TransInfo.Position.y, Enemy[i]->Info.Texture);
								}
							}
							else {
								Enemy[i]->Info.Texture = (char*)"¤¡ÈÊ";
								Enemy[i]->TransInfo.Rotation.x = -1;
								ScreenPrint(Enemy[i]->TransInfo.Position.x--, Enemy[i]->TransInfo.Position.y, Enemy[i]->Info.Texture);
							}
						}
						else {
							if(map[(int)Enemy[i]->TransInfo.Position.y][(int)Enemy[i]->TransInfo.Position.x + MapPosition - 1] == '3') {
								if (Enemy[i]->TransInfo.Position.x < 3) {
									Enemy[i]->Info.Texture = (char*)"ÈÊr";
									Enemy[i]->TransInfo.Rotation.x = 1;
									ScreenPrint(Enemy[i]->TransInfo.Position.x++, Enemy[i]->TransInfo.Position.y, Enemy[i]->Info.Texture);
								}
								else {
									ScreenPrint(Enemy[i]->TransInfo.Position.x--, Enemy[i]->TransInfo.Position.y, Enemy[i]->Info.Texture);
								}
							}
							else {
								Enemy[i]->Info.Texture = (char*)"ÈÊr";
								Enemy[i]->TransInfo.Rotation.x = 1;
								ScreenPrint(Enemy[i]->TransInfo.Position.x++, Enemy[i]->TransInfo.Position.y, Enemy[i]->Info.Texture);
							}
						}
					}
					if (Enemy[i]->TransInfo.Position.x <= 3 || Enemy[i]->TransInfo.Position.x > 145) {
						delete Enemy[i];
						Enemy[i] = nullptr;
					}
				}
				if (Enemy[i] != nullptr && Collision(Player, Enemy[i])) {
					gameover = true;
				}
			}




			for (int i = 0; i < 128; ++i) {
				if (Bullet[i] != nullptr && Bullet[i]->TransInfo.Position.x <= 144) {
					ScreenPrint(Bullet[i]->TransInfo.Position.x += 3, Bullet[i]->TransInfo.Position.y, Bullet[i]->Info.Texture);
				}

				if (Bullet[i] != nullptr && Bullet[i]->TransInfo.Position.x > 143) {
					delete Bullet[i];
					Bullet[i] = nullptr;
				}

				for (int j = 0; j < 64; ++j) {
					if (Bullet[i] != nullptr && Enemy[j] != nullptr && Collision(Enemy[j], Bullet[i])) {
						delete Bullet[i];
						Bullet[i] = nullptr;
						delete Enemy[j];
						Enemy[j] = nullptr;
						score++;
					}
				}
			}



			for (int i = 0; i < 128; ++i) {
				if (Bullet2[i] != nullptr && Bullet2[i]->TransInfo.Position.x >= 3) {
					ScreenPrint(Bullet2[i]->TransInfo.Position.x -= 3, Bullet2[i]->TransInfo.Position.y, Bullet2[i]->Info.Texture);
				}
				if (Bullet2[i] != nullptr && Bullet2[i]->TransInfo.Position.x < 3) {
					delete Bullet2[i];
					Bullet2[i] = nullptr;
				}
				for (int j = 0; j < 64; ++j) {
					if (Bullet2[i] != nullptr && Enemy[j] != nullptr && Collision(Enemy[j], Bullet2[i])) {
						delete Bullet2[i];
						Bullet2[i] = nullptr;
						delete Enemy[j];
						Enemy[j] = nullptr;
						score++;
					}
				}
			}



			for (int i = 0; i < 128; ++i) {
				if (EnemyBullet[i] != nullptr && EnemyBullet[i]->TransInfo.Position.x <= 144) {
					ScreenPrint(EnemyBullet[i]->TransInfo.Position.x += 3, EnemyBullet[i]->TransInfo.Position.y, EnemyBullet[i]->Info.Texture);
				}
				if (EnemyBullet[i] != nullptr && EnemyBullet[i]->TransInfo.Position.x > 143) {
					delete EnemyBullet[i];
					EnemyBullet[i] = nullptr;
				}
				if (EnemyBullet[i] != nullptr && Collision(Player, EnemyBullet[i])) {
					delete EnemyBullet[i];
					EnemyBullet[i] = nullptr;
					gameover = true;
				}
			}



			for (int i = 0; i < 128; ++i) {
				if (EnemyBullet2[i] != nullptr && EnemyBullet2[i]->TransInfo.Position.x >= 3) {
					ScreenPrint(EnemyBullet2[i]->TransInfo.Position.x -= 3, EnemyBullet2[i]->TransInfo.Position.y, EnemyBullet2[i]->Info.Texture);
				}
				if (EnemyBullet2[i] != nullptr && EnemyBullet2[i]->TransInfo.Position.x < 3) {
					delete EnemyBullet2[i];
					EnemyBullet2[i] = nullptr;
				}

				if (EnemyBullet2[i] != nullptr && Collision(Player, EnemyBullet2[i])) {
					delete EnemyBullet2[i];
					EnemyBullet2[i] = nullptr;
					gameover = true;
				}
			}
			


			for (int y = 0; y < 30; ++y) {
				int a = 0;
				for (int x = MapPosition; x < MapPosition + 148; ++x) {
					if (map[y][x] == '1' || map[y][x] == '4') {
						ScreenPrint(a, y, (char*)"¡á");
					}
					if (map[y][x] == '5') {
						ScreenPrint(a, y, (char*)"¡Ú");
					}
					if (map[y][x] == '6') {
						ScreenPrint(a, y, (char*)"¢¾");
					}
					if (map[y][x] == '7') {
						ScreenPrint(a, y, (char*)"¢ç");
					}
					if (map[y][x] == 'a') {
						ScreenPrint(a, y, (char*)"_");
					}
					if (map[y][x] == 'b') {
						ScreenPrint(a, y, (char*)"/");
					}
					if (map[y][x] == 'c') {
						ScreenPrint(a, y, (char*)"|");
					}
					if (map[y][x] == 'd') {
						ScreenPrint(a, y, (char*)"\\");
					}
					if (map[y][x] == 'e') {
						ScreenPrint(a, y, (char*)"*");
					}
					a++;
				}
			}

			if (MapPosition + 8 < 148) {
				ScreenPrint(MapPosition + 8, 2, (char*)".");
				ScreenPrint(MapPosition + 6, 3, (char*)"\\ | /");
				ScreenPrint(MapPosition + 4, 4, (char*)"'-.;;;.-'");
				ScreenPrint(MapPosition + 3, 5, (char*)"-==;;;;;==-");
				ScreenPrint(MapPosition + 4, 6, (char*)".-';;;'-.");
				ScreenPrint(MapPosition + 6, 7, (char*)"/ | \\");
				ScreenPrint(MapPosition + 8, 8, (char*)"'");

			}
			else if ((MapPosition - 150) / 2 + 4 < 148) {
				ScreenPrint((MapPosition - 150) / 2 + 3, 2, (char*)"_.._");
				ScreenPrint((MapPosition - 150) / 2 + 1, 3, (char*)".' .-'`");
				ScreenPrint((MapPosition - 150) / 2, 4, (char*)"/  /");
				ScreenPrint((MapPosition - 150) / 2, 5, (char*)"|  |");
				ScreenPrint((MapPosition - 150) / 2, 6, (char*)"\\  '.___.;");
				ScreenPrint((MapPosition - 150) / 2 + 1, 7, (char*)"'._  _.'");
				ScreenPrint((MapPosition - 150) / 2 + 4, 8, (char*)"``");
			}

			if (Player->Info.life == 1) {
				ScreenPrint(5, 2, (char*)"LIFE ¡Ü ¡Û");
			}
			else if (Player->Info.life == 2) {
				ScreenPrint(5, 2, (char*)"LIFE ¡Ü ¡Ü");
			}
			else if (Player->Info.life == 3) {
				ScreenPrint(5, 2, (char*)"LIFE ¡Ü ¡Ü ¡Ü");
			}
			else if (Player->Info.life == 4) {
				ScreenPrint(5, 2, (char*)"LIFE ¡Ü ¡Ü ¡Ü ¡Ü");
			}
			else {
				ScreenPrint(5, 2, (char*)"LIFE ¡Û ¡Û");
			}

			sprintf(test, "Score : %d", score * 100);
			ScreenPrint(5, 3, (char*)test);


			

			ScreenPrint((int)Player->TransInfo.Position.x, (int)Player->TransInfo.Position.y, Player->Info.Texture);

			



			if (Player->TransInfo.Position.y < 30) {
				if (map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition] == '4') {
					Gameclear();
				}
			}
			if (Player->TransInfo.Position.y < 30) {
				if (map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition] == '5' || 
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 1] == '5' || 
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 1] == '5' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 2] == '5' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 2] == '5' 
					) {
					Player->Info.item = 1;
					if (Player->TransInfo.Rotation.x == 1) {
						Player->Info.Texture = (char*)"¿ôr";
						Player->TransInfo.Scale.x = 3;
					}
					else {
						Player->Info.Texture = (char*)"¤¡¿ô";
					}
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 1] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 1] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 2] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 2] = 0;
				}
				else if (map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition] == '6' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 1] == '6' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 1] == '6' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 2] == '6' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 2] == '6') {
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 1] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 1] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 2] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 2] = 0;
					Player->Info.life++;
					ScreenPrint((int)Player->TransInfo.Position.x, (int)Player->TransInfo.Position.y--, (char*)"LIFE UP");
				}
				else if (map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition] == '7' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 1] == '7' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 1] == '7' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 2] == '7' ||
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 2] == '7') {
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 1] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 1] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition + 2] = 0;
					map[(int)Player->TransInfo.Position.y][(int)Player->TransInfo.Position.x + MapPosition - 2] = 0;
					score++;
				}
			}

			if (gameover) {
				for (int i = 0; i < 128; ++i) {
					if (Bullet[i] != nullptr) {
						delete Bullet[i];
						Bullet[i] = nullptr;
					}
					if (Bullet2[i] != nullptr) {
						delete Bullet2[i];
						Bullet2[i] = nullptr;
					}
					if (EnemyBullet[i] != nullptr) {
						delete EnemyBullet[i];
						EnemyBullet[i] = nullptr;
					}
					if (EnemyBullet2[i] != nullptr) {
						delete EnemyBullet2[i];
						EnemyBullet2[i] = nullptr;
					}
				}
				for (int i = 0; i < 64; ++i) {
					if (Enemy[i] != nullptr) {
						delete Enemy[i];
						Enemy[i] = nullptr;
					}
				}

				map_file = fopen("map.csv", "r");

				for (int i = 0; i < 30; ++i) {
					map[i] = new char[2048]();
					fgets(map[i], 2048, map_file);
					map[i] = SplitMap(map[i]);
				}

				fclose(map_file);

				Gameover(Player, &Time3);
			}

			ScreenFlipping();

		}
	}

	ScreenRelease();


	return 0;
}