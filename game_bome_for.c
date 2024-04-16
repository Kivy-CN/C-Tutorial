#include <stdio.h> // 包含标准输入输出库
#include <stdlib.h> // 包含标准库，用于调用rand()和srand()
#include <time.h> // 包含时间库，用于获取当前时间

int main() { // 主函数
    int disarm_code; // 存储解除炸弹的代码
    int player_guess; // 存储玩家的猜测
    int guess_limit = 3; // 猜测的限制次数
    int bomb_defused = 0; // 标记炸弹是否被拆除

    srand(time(0)); // 设置随机数种子

    disarm_code = rand() % 10 + 1; // 生成1到10的随机数作为解除炸弹的代码

    printf("欢迎来到炸弹拆除游戏！\n"); // 打印欢迎信息
    printf("你有3次机会来猜测解除炸弹的代码（1-10）。\n"); // 打印游戏规则

    // 循环让玩家猜测解除炸弹的代码
    for(int guess_count = 0; guess_count < guess_limit && !bomb_defused; guess_count++) {
        printf("请输入你的猜测："); // 提示玩家输入猜测
        scanf("%d", &player_guess); // 读取玩家的猜测

        // 检查玩家的猜测是否正确
        if(player_guess == disarm_code) {
            bomb_defused = 1; // 如果猜测正确，标记炸弹已被拆除
        } else if(player_guess < disarm_code) {
            printf("太低了！再试一次。\n"); // 如果猜测太低，提示玩家
        } else {
            printf("太高了！再试一次。\n"); // 如果猜测太高，提示玩家
        }
    }

    if(bomb_defused) {
        printf("恭喜，你成功拆除了炸弹！\n");        
        printf("\n");
        printf("\033[0;34m");
        printf("       \n");
        printf(" _   _  ___  _   _  __      _(_)_ __  \n");
        printf("| | | |/ _ \\| | | | \\ \\ /\\ / / | '_ \\ \n");
        printf("| |_| | (_) | |_| |  \\ V  V /| | | | |\n");
        printf(" \\__, |\\___/ \\__,_|   \\_/\\_/ |_|_| |_|\n");
        printf(" |___/                             \n");
        printf("\033[0m");
        printf("\n");
    } else {
        printf("砰！炸弹爆炸了。正确的解除代码是%d。\n", disarm_code);
        printf("\n");
        printf("\033[0;31m");
        printf(" __ _  __ _ _ __ ___   ___    _____   _____ _ __ \n");
        printf("/ _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|\n");
        printf("| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |   \n");
        printf("\\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   \n");
        printf(" |___/                                             \n");
        printf("\033[0m");
        printf("\n");
    }

    return 0;
}