// sudo apt-get install libncurses5-dev libncursesw5-dev
// gcc game.c -o game -lncurses

#include <ncurses.h> // 包含ncurses库，用于终端用户界面
#include <stdlib.h> // 包含标准库，用于通用函数

typedef enum { UP, DOWN, LEFT, RIGHT } Direction; // 定义四个可能的方向的枚举

// 定义蛇的结构体
typedef struct Snake {
    int x, y; // 蛇的x和y坐标
    int speed; // 蛇的速度
    Direction direction; // 蛇移动的方向
    struct Snake *next; // 指向蛇的下一段的指针
} Snake;

Snake *snake_head; // 指向蛇头的指针
int score; // 玩家的分数
struct { int x, y; } food; // 食物的x和y坐标

/**
 * 初始化游戏。
 * 设置屏幕，蛇，分数和食物。
 */
void initialize() {
    initscr(); // 初始化屏幕
    cbreak(); // 禁用行缓冲
    noecho(); // 不回显用户输入
    curs_set(0); // 隐藏光标
    keypad(stdscr, TRUE); // 启用特殊键
    timeout(300); // 设置用户输入的超时时间

    // 初始化蛇
    snake_head = malloc(sizeof(Snake)); // 为蛇分配内存
    snake_head->x = COLS / 2; // 设置蛇的初始x坐标
    snake_head->y = LINES / 2; // 设置蛇的初始y坐标
    snake_head->speed = 1; // 设置蛇的初始速度
    snake_head->direction = RIGHT; // 设置蛇的初始方向
    snake_head->next = NULL; // 蛇还没有其他段

    score = 0; // 初始化分数
    food.x = rand() % COLS; // 设置食物的初始x坐标
    food.y = rand() % LINES; // 设置食物的初始y坐标
}

/**
 * 绘制游戏屏幕。
 * 清屏，打印分数，蛇和食物。
 */
void draw() {
    clear(); // 清屏
    mvprintw(0, 0, "Score: %d", score); // 在屏幕的左上角打印分数

    // 打印蛇
    Snake *temp = snake_head; // 从蛇头开始
    while (temp) { // 当还有蛇的段时
        mvprintw(temp->y, temp->x, "O"); // 打印蛇的当前段
        temp = temp->next; // 移动到蛇的下一段
    }

    mvprintw(food.y, food.x, "X"); // 打印食物
    refresh(); // 刷新屏幕以显示新状态
}

/**
 * 更新游戏状态。
 * 处理用户输入，移动蛇，检查碰撞，更新分数。
 */
void update() {
    int ch = getch(); // 获取用户的输入
    Snake *new_head = malloc(sizeof(Snake)); // 为蛇的新头分配内存
    new_head->next = snake_head; // 新头的下一段是旧头
    new_head->speed = snake_head->speed; // 新头的速度与旧头相同
    new_head->direction = snake_head->direction; // 新头开始时的方向与旧头相同

    // 根据用户的输入改变新头的方向
    if (ch == KEY_LEFT) new_head->direction = LEFT;
    else if (ch == KEY_RIGHT) new_head->direction = RIGHT;
    else if (ch == KEY_UP) new_head->direction = UP;
    else if (ch == KEY_DOWN) new_head->direction = DOWN;

    // 让新头朝正确的方向移动
    if (new_head->direction == LEFT) new_head->x = snake_head->x - new_head->speed, new_head->y = snake_head->y;
    else if (new_head->direction == RIGHT) new_head->x = snake_head->x + new_head->speed, new_head->y = snake_head->y;
    else if (new_head->direction == UP) new_head->x = snake_head->x, new_head->y = snake_head->y - new_head->speed;
    else if (new_head->direction == DOWN) new_head->x = snake_head->x, new_head->y = snake_head->y + new_head->speed;

    // 检查新头是否与食物碰撞
    if (new_head->x == food.x && new_head->y == food.y) {
        score++; // 增加分数
        food.x = rand() % COLS; // 将食物移动到新的随机位置
        food.y = rand() % LINES; // 将食物移动到新的随机位置
        timeout(300 / snake_head->speed); // 根据蛇的速度减少超时时间

        // 在蛇的尾部添加新段
        Snake *temp = snake_head; // 从蛇头开始
        while (temp->next) temp = temp->next; // 找到蛇的尾部
        Snake *new_tail = malloc(sizeof(Snake)); // 为新尾部分配内存
        new_tail->x = temp->x; // 新尾部的x坐标与旧尾部相同
        new_tail->y = temp->y; // 新尾部的y坐标与旧尾部相同
        new_tail->next = NULL; // 新尾部没有下一段
        temp->next = new_tail; // 旧尾部的下一段是新尾部
    } else {
        // 移除蛇的尾部
        Snake *temp = snake_head; // 从蛇头开始
        while (temp->next && temp->next->next) temp = temp->next; // 找到蛇的倒数第二段
        if (temp->next) { // 如果有最后一段
            free(temp->next); // 释放最后一段的内存
            temp->next = NULL; // 倒数第二段现在是最后一段
        }
    }

    snake_head = new_head; // 新头现在是蛇的头
}

/**
 * 游戏的主函数。
 * 初始化游戏并运行游戏循环。
 */
int main() {
    initialize(); // 初始化游戏

    while (1) { // 游戏循环
        draw(); // 绘制游戏状态
        update(); // 更新游戏状态
    }

    endwin(); // 结束窗口
    return 0; // 退出程序
}