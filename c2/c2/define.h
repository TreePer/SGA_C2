#pragma once

static int g_nScreenIndex;
static HANDLE g_hScreen[2];
static unsigned int MapPosition = 0;
int score = 0;
bool jump = true;
bool drop = true;
bool gameover = false;
bool jump2 = true;


void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, char* string);
char* SplitMap(char* _map);

void Logo();
void Gameclear();
void Gameover(Object* _Player, LONGLONG* time);

void init(Object* _Obj, char* texture = nullptr, float px = 0, float py = 0, float pz = 0);
bool Collision(Object* _Player, Object* _block);
Object* Createbullet(const float x, const float y);
Object* CreateEnemy(const float x, const float y);
Object* CreateEnemybullet(const float x, const float y);
void UpdateInput(Object* _Obj, char map[]);


void ScreenInit() {
    CONSOLE_CURSOR_INFO cci;


    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping() {
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear() {
    COORD Coor = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 150 * 35, Coor, &dw);
}

void ScreenRelease() {
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string) {
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

char* SplitMap(char* _map) {
    char* map = strtok(_map, ",");

    string m = "";
    while (map != NULL) {
        m += map;
        map = strtok(NULL, ",");
    }

    map = new char[2048]();

    copy(m.begin(), m.end(), map);

    return map;
}

void Logo() {
    int i = 0;
    int x = 75 - (strlen(" #####  #     # ######  ####### ######     #     #    #    ######  ### ####### ") / 2);

        
    while (true) {
        ScreenClear();

        ScreenPrint(x, 3, (char*)" #####  #     # ######  ####### ######     #     #    #    ######  ### ####### ");
        ScreenPrint(x, 4, (char*)"#     # #     # #     # #       #     #    ##   ##   # #   #     #  #  #     # ");
        ScreenPrint(x, 5, (char*)"#       #     # #     # #       #     #    # # # #  #   #  #     #  #  #     # ");
        ScreenPrint(x, 6, (char*)" #####  #     # ######  #####   ######     #  #  # #     # ######   #  #     # ");
        ScreenPrint(x, 7, (char*)"      # #     # #       #       #   #      #     # ####### #   #    #  #     # ");
        ScreenPrint(x, 8, (char*)"#     # #     # #       #       #    #     #     # #     # #    #   #  #     # ");
        ScreenPrint(x, 9, (char*)" #####   #####  #       ####### #     #    #     # #     # #     # ### ####### ");


        if (GetAsyncKeyState(VK_UP) & 0x0001) {

            if (i == 1) {
                i = 0;
            }
            else {
                i = 1;
            }
        }
        
        
        if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
            if (i == 1) {
                i = 0;
            }
            else {
                i = 1;
            }
        }
        if (GetAsyncKeyState(VK_RETURN) && i == 0)
            break;
        if (GetAsyncKeyState(VK_RETURN) && i == 1)
            exit(0);

        switch (i) {
        case 0:
            ScreenPrint(75, 23, (char*)"Start ¡ç");
            ScreenPrint(75, 24, (char*)"Exit           ");
            break;
        case 1:
            ScreenPrint(75, 23, (char*)"Start           ");
            ScreenPrint(75, 24, (char*)"Exit ¡ç");
            break;
        }
        ScreenFlipping();
    }
}

void Gameclear() {
    int x = 75 - (strlen(" #####     #    #     # #######     #####  #       #######    #    ######  ") / 2);

    char finalscore[64];
    sprintf(finalscore, "Score : %d", score * 100);

    int a = 75 - (strlen(finalscore) / 2);

    while (true) {
        ScreenClear();

        ScreenPrint(x, 11, (char*)" #####     #    #     # #######     #####  #       #######    #    ######  ");
        ScreenPrint(x, 12, (char*)"#     #   # #   ##   ## #          #     # #       #         # #   #     # ");
        ScreenPrint(x, 13, (char*)"#        #   #  # # # # #          #       #       #        #   #  #     # ");
        ScreenPrint(x, 14, (char*)"#  #### #     # #  #  # #####      #       #       #####   #     # ######  ");
        ScreenPrint(x, 15, (char*)"#     # ####### #     # #          #       #       #       ####### #   #   ");
        ScreenPrint(x, 16, (char*)"#     # #     # #     # #          #     # #       #       #     # #    #  ");
        ScreenPrint(x, 17, (char*)" #####  #     # #     # #######     #####  ####### ####### #     # #     # ");
        ScreenPrint(a, 20, finalscore);

       
        if (GetAsyncKeyState(VK_RETURN))
            exit(0);

        ScreenFlipping();
    }

}

void Gameover(Object* _Player, LONGLONG* time) {

    int x = 75 - (strlen(" #####     #    #     # #######    ####### #     # ####### ######  ") / 2);

    

    while (true) {
        ScreenClear();

        ScreenPrint(x, 11, (char*)" #####     #    #     # #######    ####### #     # ####### ######  ");
        ScreenPrint(x, 12, (char*)"#     #   # #   ##   ## #          #     # #     # #       #     # ");
        ScreenPrint(x, 13, (char*)"#        #   #  # # # # #          #     # #     # #       #     # ");
        ScreenPrint(x, 14, (char*)"#  #### #     # #  #  # #####      #     # #     # #####   ######  ");
        ScreenPrint(x, 15, (char*)"#     # ####### #     # #          #     #  #   #  #       #   #   ");
        ScreenPrint(x, 16, (char*)"#     # #     # #     # #          #     #   # #   #       #    #  ");
        ScreenPrint(x, 17, (char*)" #####  #     # #     # #######    #######    #    ####### #     # ");


        if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
            _Player->Info.Texture = (char*)"¿ô";
            _Player->Info.life--;
            _Player->Info.item = 0;
            _Player->TransInfo.Position.x = 1;
            _Player->TransInfo.Position.y = 18;
            score = 0;
            MapPosition = 0;
            gameover = false;
            *time = GetTickCount64();
            break;
        }
            
        ScreenFlipping();
    }

}

void init(Object* _Obj, char* texture, float px, float py, float pz) {
    _Obj->Info.Texture = texture;
    _Obj->Info.item = 0;
    _Obj->Info.life = 2;

    _Obj->TransInfo.Position = Vector(px, py, pz);
    _Obj->TransInfo.Rotation = Vector(1, 0, 0);
    _Obj->TransInfo.Scale = Vector(strlen(_Obj->Info.Texture), 1.0f, 0);
}


bool Collision(Object* _Player, Object* _block) {
    if (_Player->TransInfo.Position.x + _Player->TransInfo.Scale.x > _block->TransInfo.Position.x &&
        _Player->TransInfo.Position.x < _block->TransInfo.Position.x + _block->TransInfo.Scale.x &&
        _Player->TransInfo.Position.y == _block->TransInfo.Position.y) {
        return true;
    }
    return false;
}

Object* Createbullet(const float x, const float y) {
    Object* pBullet = new Object;

    init(pBullet, (char*)"==o", x + 2, y);

    return pBullet;
}

Object* CreateEnemy(const float x, const float y) {
    Object* pEnemy = new Object;

    init(pEnemy, (char*)"¤¡ÈÊ", x, y);
    pEnemy->TransInfo.Rotation.x = -1;

    return pEnemy;
}

Object* CreateEnemybullet(const float x, const float y) {
    Object* pBullet = new Object;

    init(pBullet, (char*)"o==", x - 2, y);

    return pBullet;
}

void UpdateInput(Object* _Obj, char map[]) {

    LONGLONG Time = GetTickCount64();

    if (GetAsyncKeyState(VK_UP))
        _Obj->TransInfo.Position.y--;

    if (GetAsyncKeyState(VK_DOWN))
        _Obj->TransInfo.Position.y++;

    if (jump && jump2 && drop && GetAsyncKeyState(VK_LSHIFT) & 0x0001) {
        jump2 = false;
    }

    if (_Obj->Info.item == 0) {
        if (GetAsyncKeyState(VK_LEFT) && _Obj->TransInfo.Position.x > 2 && drop && jump && jump2) {
            if (map[(int)_Obj->TransInfo.Position.x + MapPosition - 1] != '1') {
                if (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x > 26 || (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x > 2 + _Obj->TransInfo.Scale.x && MapPosition == 0)) {
                    _Obj->TransInfo.Position.x -= 1;
                    _Obj->TransInfo.Rotation.x = -1;
                }

                if (_Obj->TransInfo.Position.x == 23 && MapPosition > 0) {
                    MapPosition -= 1;
                    _Obj->TransInfo.Rotation.x = -1;
                }
            }
        }


        if (GetAsyncKeyState(VK_RIGHT) && _Obj->TransInfo.Position.x < 142 && drop && jump && jump2) {
            if (map[(int)_Obj->TransInfo.Position.x + MapPosition + 3] != '1') {
                if (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x < 130 || (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x < 146 && MapPosition >= 600)) {
                    _Obj->TransInfo.Position.x += 1;
                    _Obj->TransInfo.Rotation.x = 1;
                }

                if (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x >= 130 && MapPosition < 599) {
                    MapPosition += 1;
                    _Obj->TransInfo.Rotation.x = 1;
                }
            }

        }
    }


    if (_Obj->Info.item == 1) {
        if (GetAsyncKeyState(VK_LEFT) && _Obj->TransInfo.Position.x > 2 && drop && jump && jump2) {
            if (map[(int)_Obj->TransInfo.Position.x + MapPosition - 1] != '1') {
                if (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x > 26 || (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x > 2 + _Obj->TransInfo.Scale.x && MapPosition == 0)) {
                    _Obj->TransInfo.Position.x -= 1;
                    _Obj->TransInfo.Rotation.x = -1;
                    _Obj->Info.Texture = (char*)"¤¡¿ô";
                }

                if (_Obj->TransInfo.Position.x == 23 && MapPosition > 0) {
                    MapPosition -= 1;
                    _Obj->TransInfo.Rotation.x = -1;
                    _Obj->Info.Texture = (char*)"¤¡¿ô";


                }
            }
        }


        if (GetAsyncKeyState(VK_RIGHT) && _Obj->TransInfo.Position.x < 142 && drop && jump && jump2) {
            if (map[(int)_Obj->TransInfo.Position.x + MapPosition + 3] != '1') {
                if (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x < 130 || (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x < 146 && MapPosition >= 600)) {
                    _Obj->TransInfo.Position.x += 1;
                    _Obj->TransInfo.Rotation.x = 1;
                    _Obj->Info.Texture = (char*)"¿ôr";

                }

                if (_Obj->TransInfo.Position.x + _Obj->TransInfo.Scale.x >= 130 && MapPosition < 599) {
                    MapPosition += 1;
                    _Obj->TransInfo.Rotation.x = 1;
                    _Obj->Info.Texture = (char*)"¿ôr";


                }
            }

        }
    }
    

    if (jump && jump2 && drop && GetAsyncKeyState(VK_LMENU) & 0x0001) {
        jump = false;

    }
    
    
}
