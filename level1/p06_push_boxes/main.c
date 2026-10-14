#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Windows环境下用于接收无需回车的键盘输入

// 定义地图的最大尺寸
#define MAX_ROWS 10
#define MAX_COLS 10

// 地图元素含义:
// '#' : 墙壁
// ' ' : 空地
// '@' : 玩家
// '$' : 箱子
// '.' : 箱子目标位置
// '*' : 箱子已在目标位置
// '+' : 玩家站在目标位置上

// 直接在代码中生成的一关地图
char map[MAX_ROWS][MAX_COLS] = {
    "########",
    "#      #",
    "# .$@  #",
    "#      #",
    "########",
    "        ",
    "        ",
    "        ",
    "        ",
    "        "
};

int playerX, playerY; // 玩家当前坐标
int steps = 0;        // 玩家步数
int boxCount = 0;     // 剩余未归位的箱子数量

// 函数声明
void initGame();
void drawMap();
int checkWin();
void movePlayer(char direction);

int main() {
    // 初始化游戏数据（寻找玩家位置、统计箱子数量）
    initGame();

    system("cls"); // 清屏 (Windows)
    printf("--- 推箱子小游戏 --- (使用 w/a/s/d 控制移动, q 退出)\n");
    drawMap();

    // 游戏主循环
    while (1) {
        if (_kbhit()) { // 检查是否有键盘按下
            char ch = _getch(); // 获取按下的字符

            switch (ch) {
                case 'w': case 'W': movePlayer('w'); break;
                case 's': case 'S': movePlayer('s'); break;
                case 'a': case 'A': movePlayer('a'); break;
                case 'd': case 'D': movePlayer('d'); break;
                case 'q': case 'Q':
                    printf("\n游戏已退出。\n");
                    return 0;
            }

            system("cls"); // 每次移动后清屏重绘
            printf("--- 推箱子小游戏 --- (使用 w/a/s/d 控制移动, q 退出)\n");
            drawMap();

            // 检查是否胜利
            if (checkWin()) {
                printf("\n>>> 恭喜你！你赢得了游戏！<<<\n");
                printf(">>> 总共使用步数: %d <<<\n", steps);
                printf("按任意键退出...\n");
                _getch();
                break;
            }
        }
    }

    return 0;
}

// 初始化游戏
void initGame() {
    boxCount = 0;
    steps = 0;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (map[i][j] == '@' || map[i][j] == '+') {
                playerX = i;
                playerY = j;
            }
            // 统计有多少个箱子没有归位（包含 '$' 和 '*'，但在判断胜利时 '*' 不算未归位）
            // 这里我们只统计 '$' 的数量，作为未归位的箱子
            if (map[i][j] == '$') {
                boxCount++;
            }
        }
    }
}

// 绘制地图
void drawMap() {
    for (int i = 0; i < MAX_ROWS; i++) {
        // 如果这一行全是空格，就不打印了（为了美观）
        int hasContent = 0;
        for (int j = 0; j < MAX_COLS; j++) {
            if (map[i][j] != ' ' && map[i][j] != '\0') {
                hasContent = 1;
                break;
            }
        }
        if (!hasContent) continue;

        for (int j = 0; j < MAX_COLS; j++) {
            if (map[i][j] == '\0') break; // 遇到字符串结尾结束当前行打印

            switch (map[i][j]) {
                case '#': printf("█"); break; // 墙
                case '$': printf("□"); break; // 箱子
                case '.': printf("○"); break; // 目标点
                case '@': printf("♀"); break; // 玩家
                case '*': printf("■"); break; // 箱子在目标点上
                case '+': printf("♂"); break; // 玩家在目标点上
                default:  printf(" "); break; // 空地
            }
        }
        printf("\n");
    }
    printf("当前步数: %d\n", steps);
    printf("还需归位箱子数: %d\n", boxCount);
}

// 检查胜利条件
int checkWin() {
    // 如果未归位的箱子数量为0，说明游戏胜利
    return (boxCount == 0);
}

// 处理玩家移动逻辑
void movePlayer(char direction) {
    int dx = 0, dy = 0;

    switch (direction) {
        case 'w': dx = -1; break; // 上
        case 's': dx = 1; break;  // 下
        case 'a': dy = -1; break; // 左
        case 'd': dy = 1; break;  // 右
    }

    int newX = playerX + dx;
    int newY = playerY + dy;

    // 1. 检查是否越界
    if (newX < 0 || newX >= MAX_ROWS || newY < 0 || newY >= MAX_COLS) return;

    char nextCell = map[newX][newY];

    // 2. 如果前面是墙，不能走
    if (nextCell == '#') return;

    // 3. 如果前面是空地或目标点，直接移动
    if (nextCell == ' ' || nextCell == '.') {
        // 恢复玩家原位置
        if (map[playerX][playerY] == '@') map[playerX][playerY] = ' ';
        else if (map[playerX][playerY] == '+') map[playerX][playerY] = '.';

        // 更新玩家新位置
        if (nextCell == ' ') map[newX][newY] = '@';
        else if (nextCell == '.') map[newX][newY] = '+';

        playerX = newX;
        playerY = newY;
        steps++;
    }
    // 4. 如果前面是箱子，判断能否推动
    else if (nextCell == '$' || nextCell == '*') {
        int boxNewX = newX + dx;
        int boxNewY = newY + dy;

        // 检查箱子后面是否越界
        if (boxNewX < 0 || boxNewX >= MAX_ROWS || boxNewY < 0 || boxNewY >= MAX_COLS) return;

        char boxNextCell = map[boxNewX][boxNewY];

        // 箱子后面是墙或者另一个箱子，推不动
        if (boxNextCell == '#' || boxNextCell == '$' || boxNextCell == '*') return;

        // 可以推动箱子
        // a. 处理箱子的新位置
        if (boxNextCell == ' ') {
            map[boxNewX][boxNewY] = '$';
        } else if (boxNextCell == '.') {
            map[boxNewX][boxNewY] = '*';
            boxCount--; // 箱子归位，未归位数量减1
        }

        // b. 处理玩家移动后，原来箱子所在位置的状态
        if (nextCell == '$') {
            map[newX][newY] = '@';
        } else if (nextCell == '*') {
            map[newX][newY] = '+';
            boxCount++; // 原本归位的箱子被推走了，未归位数量加1
        }

        // c. 恢复玩家原来的位置
        if (map[playerX][playerY] == '@') map[playerX][playerY] = ' ';
        else if (map[playerX][playerY] == '+') map[playerX][playerY] = '.';

        // 更新玩家最终坐标
        playerX = newX;
        playerY = newY;
        steps++;
    }
}
