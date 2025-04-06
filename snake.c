/**
 * @file snake_game.c
 * @brief 跨平台控制台贪吃蛇游戏（改进版）
 * 
 * 本程序实现了一个可在 Windows 和 Linux 平台运行的控制台贪吃蛇游戏。
 * 程序自动检测操作系统类型并使用对应的系统函数进行屏幕清理和按键检测。
 * 改进：降低初始速度，优化按键检测逻辑。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 检测操作系统类型
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define IS_WINDOWS 1
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #define CLEAR_SCREEN "clear"
    #define IS_WINDOWS 0
#endif

// 游戏配置常量
#define WIDTH 20          // 游戏区域宽度
#define HEIGHT 20         // 游戏区域高度
#define INITIAL_SNAKE_LENGTH 3  // 蛇的初始长度
#define INITIAL_SPEED 250  // 初始游戏速度 (毫秒)
#define SPEED_INCREMENT 5  // 每吃一个食物加快的速度

// 方向枚举
enum Direction {
    UP, 
    DOWN, 
    LEFT, 
    RIGHT
};

// 坐标结构体
typedef struct {
    int x;
    int y;
} Position;

// 游戏状态
typedef struct {
    Position snake[WIDTH * HEIGHT]; // 蛇身体各部分的位置
    int length;                     // 蛇的长度
    enum Direction direction;       // 蛇的移动方向
    Position food;                  // 食物位置
    int score;                      // 得分
    int gameOver;                   // 游戏结束标志
    int speed;                      // 游戏速度
} GameState;

/**
 * Linux系统下的按键检测函数
 * 
 * @return 按下的按键的ASCII值，如果没有按键则返回-1
 */
#ifndef _WIN32
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // 保存当前终端设置
    tcgetattr(STDIN_FILENO, &oldt);
    // 复制设置
    newt = oldt;
    // 禁用规范模式和回显
    newt.c_lflag &= ~(ICANON | ECHO);
    // 应用新设置
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // 保存当前文件描述符标志
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    // 设置非阻塞模式
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // 尝试读取字符
    ch = getchar();

    // 恢复终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    // 恢复文件描述符标志
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // 如果读取到字符，将其放回输入缓冲区并返回1
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

/**
 * Linux系统下的无回显读取按键函数
 * 
 * @return 按下的按键的ASCII值
 */
int getch(void) {
    struct termios oldt, newt;
    int ch;
    
    // 保存当前终端设置
    tcgetattr(STDIN_FILENO, &oldt);
    // 复制设置
    newt = oldt;
    // 禁用规范模式和回显
    newt.c_lflag &= ~(ICANON | ECHO);
    // 应用新设置
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    // 读取字符
    ch = getchar();
    
    // 恢复终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}
#endif

/**
 * 平台无关的睡眠函数
 * 
 * @param milliseconds 暂停的毫秒数
 */
void sleepMs(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}

/**
 * 清屏函数
 */
void clearScreen() {
    system(CLEAR_SCREEN);
}

/**
 * 初始化游戏状态
 * 
 * @param state 游戏状态指针
 */
void initGame(GameState *state) {
    // 初始化随机数生成器
    srand((unsigned int)time(NULL));
    
    // 初始化蛇的位置
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++) {
        state->snake[i].x = WIDTH / 2;
        state->snake[i].y = HEIGHT / 2 - i;
    }
    
    // 设置初始方向向下
    state->direction = DOWN;
    
    // 设置蛇的初始长度
    state->length = INITIAL_SNAKE_LENGTH;
    
    // 初始化分数
    state->score = 0;
    
    // 初始化游戏结束标志
    state->gameOver = 0;
    
    // 初始化游戏速度
    state->speed = INITIAL_SPEED;
    
    // 生成第一个食物
    state->food.x = rand() % WIDTH;
    state->food.y = rand() % HEIGHT;
}

/**
 * 处理用户输入
 * 
 * @param state 游戏状态指针
 */
void handleInput(GameState *state) {
    // 检查是否有按键输入
    int keyPressed = 0;
    
    #ifdef _WIN32
        keyPressed = kbhit();
    #else
        keyPressed = kbhit();
    #endif
    
    // 如果有按键输入
    if (keyPressed) {
        char key;
        
        #ifdef _WIN32
            key = getch();
            // 处理方向键的特殊情况（Windows方向键是两个字节）
            if (key == 0 || key == 224) {
                key = getch();
                switch (key) {
                    case 72: // 上箭头
                        if (state->direction != DOWN)
                            state->direction = UP;
                        break;
                    case 80: // 下箭头
                        if (state->direction != UP)
                            state->direction = DOWN;
                        break;
                    case 75: // 左箭头
                        if (state->direction != RIGHT)
                            state->direction = LEFT;
                        break;
                    case 77: // 右箭头
                        if (state->direction != LEFT)
                            state->direction = RIGHT;
                        break;
                }
            } else {
                // 处理WASD按键
                switch (key) {
                    case 'w': // 上
                    case 'W':
                        if (state->direction != DOWN)
                            state->direction = UP;
                        break;
                    case 's': // 下
                    case 'S':
                        if (state->direction != UP)
                            state->direction = DOWN;
                        break;
                    case 'a': // 左
                    case 'A':
                        if (state->direction != RIGHT)
                            state->direction = LEFT;
                        break;
                    case 'd': // 右
                    case 'D':
                        if (state->direction != LEFT)
                            state->direction = RIGHT;
                        break;
                    case 'q': // 退出
                    case 'Q':
                        state->gameOver = 1;
                        break;
                }
            }
        #else
            key = getch();
            // 处理WASD按键
            switch (key) {
                case 'w': // 上
                case 'W':
                    if (state->direction != DOWN)
                        state->direction = UP;
                    break;
                case 's': // 下
                case 'S':
                    if (state->direction != UP)
                        state->direction = DOWN;
                    break;
                case 'a': // 左
                case 'A':
                    if (state->direction != RIGHT)
                        state->direction = LEFT;
                    break;
                case 'd': // 右
                case 'D':
                    if (state->direction != LEFT)
                        state->direction = RIGHT;
                    break;
                case 'q': // 退出
                case 'Q':
                    state->gameOver = 1;
                    break;
            }
        #endif
    }
}

/**
 * 更新游戏状态
 * 
 * @param state 游戏状态指针
 */
void updateGame(GameState *state) {
    // 计算蛇头的新位置
    Position newHead = state->snake[0];
    
    // 根据方向移动蛇头
    switch (state->direction) {
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case RIGHT:
            newHead.x++;
            break;
    }
    
    // 检查是否撞墙
    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
        state->gameOver = 1;
        return;
    }
    
    // 检查是否撞到自己（除了尾巴，因为尾巴会移动）
    for (int i = 0; i < state->length - 1; i++) {
        if (newHead.x == state->snake[i].x && newHead.y == state->snake[i].y) {
            state->gameOver = 1;
            return;
        }
    }
    
    // 检查是否吃到食物
    if (newHead.x == state->food.x && newHead.y == state->food.y) {
        // 增加分数
        state->score += 10;
        
        // 增加蛇的长度
        state->length++;
        
        // 加快游戏速度
        if (state->speed > SPEED_INCREMENT) {
            state->speed -= SPEED_INCREMENT;
        }
        
        // 生成新的食物（确保不在蛇身上）
        int validPosition;
        do {
            validPosition = 1;
            state->food.x = rand() % WIDTH;
            state->food.y = rand() % HEIGHT;
            
            for (int i = 0; i < state->length; i++) {
                if (state->food.x == state->snake[i].x && state->food.y == state->snake[i].y) {
                    validPosition = 0;
                    break;
                }
            }
        } while (!validPosition);
    } else {
        // 如果没有吃到食物，移动蛇（通过移动身体部分）
        for (int i = state->length - 1; i > 0; i--) {
            state->snake[i] = state->snake[i - 1];
        }
    }
    
    // 更新蛇头位置
    state->snake[0] = newHead;
}

/**
 * 绘制游戏界面
 * 
 * @param state 游戏状态指针
 */
void renderGame(const GameState *state) {
    // 清屏
    clearScreen();
    
    // 创建临时游戏区域
    char board[HEIGHT][WIDTH];
    
    // 初始化游戏区域
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            board[y][x] = ' ';
        }
    }
    
    // 绘制蛇
    for (int i = 0; i < state->length; i++) {
        int x = state->snake[i].x;
        int y = state->snake[i].y;
        
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            if (i == 0) {
                // 蛇头
                board[y][x] = '@';
            } else {
                // 蛇身
                board[y][x] = 'o';
            }
        }
    }
    
    // 绘制食物
    if (state->food.x >= 0 && state->food.x < WIDTH && state->food.y >= 0 && state->food.y < HEIGHT) {
        board[state->food.y][state->food.x] = '*';
    }
    
    // 打印游戏区域
    printf("贪吃蛇游戏 - 得分: %d    速度: %d ms\n", state->score, state->speed);
    printf("使用WASD键或方向键移动，Q键退出\n\n");
    
    // 打印上边框
    printf("+");
    for (int x = 0; x < WIDTH; x++) {
        printf("-");
    }
    printf("+\n");
    
    // 打印游戏区域
    for (int y = 0; y < HEIGHT; y++) {
        printf("|");
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", board[y][x]);
        }
        printf("|\n");
    }
    
    // 打印下边框
    printf("+");
    for (int x = 0; x < WIDTH; x++) {
        printf("-");
    }
    printf("+\n");
    
    // 打印操作说明和操作系统信息
    printf("\n@ - 蛇头  o - 蛇身  * - 食物\n");
    printf("运行环境: %s\n", IS_WINDOWS ? "Windows" : "Linux/Unix");
}

/**
 * 主函数
 */
int main() {
    // 创建游戏状态
    GameState state;
    
    // 初始化游戏
    initGame(&state);
    
    // 清屏并显示开始提示
    clearScreen();
    printf("贪吃蛇游戏即将开始!\n");
    printf("使用WASD键或方向键控制蛇的移动\n");
    printf("吃到食物(*)可以增加得分并加长蛇身\n");
    printf("撞到墙壁或自己的身体游戏结束\n");
    printf("按任意键开始游戏...\n");
    
    // 等待用户按键开始
    #ifdef _WIN32
        getch();
    #else
        getchar();
    #endif
    
    // 游戏主循环
    while (!state.gameOver) {
        // 处理用户输入
        handleInput(&state);
        
        // 更新游戏状态
        updateGame(&state);
        
        // 绘制游戏界面
        renderGame(&state);
        
        // 控制游戏速度
        sleepMs(state.speed);
    }
    
    // 游戏结束
    clearScreen();
    printf("\n游戏结束！\n");
    printf("最终得分: %d\n", state.score);
    printf("蛇的长度: %d\n\n", state.length);
    printf("按任意键退出...\n");
    
    // 等待用户按键退出
    #ifdef _WIN32
        getch();
    #else
        getchar();
    #endif
    
    return 0;
}