#include <stdio.h>
#include <conio.h>
#include <windows.h>


#define ROW 10
#define COL 12

char maze[ROW][COL] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','P','.','.','#','.','.','.','.','.','.','#'},
    {'#','#','#','.','#','#','#','#','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','#','.','#'},
    {'#','.','#','#','#','#','#','#','.','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','#','#','#','#','#','#','#','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','#','#','#','#','#','E','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#'}
};

int px = 1, py = 1;

void printMaze()
{
    system("cls");
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n==== game ====\n");
    printf("directions up:w down:s left:a right:d player:P destination:E \n");
}

void movePlayer(int dx, int dy)
{
    int nx = px + dx;
    int ny = py + dy;


    if(maze[nx][ny] == '#')
    {
        return;
    }


    if(maze[nx][ny] == 'E')
    {
        printMaze();
        printf("\n OK! \n");
        exit(0);
    }


    maze[px][py] = '.';
    px = nx;
    py = ny;
    maze[px][py] = 'P';
}


void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void clearScreen() {
    gotoxy(0, 0);

}


void hideCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

int main() {
    hideCursor();

    bool st=true;

    printMaze();

    while (true) {

        if (st) {
            clearScreen();
            printMaze();
            st=false;
        }


        if (_kbhit()) {
            char key = _getch();
            st=true;
            switch (key) {
                case 'w': movePlayer(-1, 0); break; // 上
                case 's': movePlayer(1, 0);  break; // 下
                case 'a': movePlayer(0, -1); break; // 左
                case 'd': movePlayer(0, 1);  break; // 右
            }
            Sleep(30);
        }

    }
    system("pause");
    return 0;
}
