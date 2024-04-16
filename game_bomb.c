#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // disarm_code: 炸弹的解除代码
    int disarm_code;
    // player_guess: 玩家的猜测
    int player_guess;
    // guess_limit: 玩家的最大猜测次数
    int guess_limit = 3;
    // guess_count: 玩家已经猜测的次数
    int guess_count = 0;
    // bomb_defused: 炸弹是否已经被拆除，0表示未拆除，1表示已拆除
    int bomb_defused = 0;

    // 初始化随机数生成器
    srand(time(0));

    // 生成一个1到10之间的解除代码
    disarm_code = rand() % 10 + 1;

    // 打印欢迎信息和游戏规则
    printf("欢迎来到炸弹拆除游戏！\n");
    printf("你有3次机会来猜测解除炸弹的代码（1-10）。\n");

    // 当炸弹未被拆除且玩家还有剩余尝试次数时，继续游戏
    while(!bomb_defused && guess_count < guess_limit) {
        // 提示玩家输入猜测
        printf("请输入你的猜测：");
        scanf("%d", &player_guess);
        guess_count++;

        // 如果玩家猜对了，炸弹被拆除
        if(player_guess == disarm_code) {
            bomb_defused = 1;
        } else if(player_guess < disarm_code) { // 如果玩家猜低了，提示玩家
            printf("太低了！再试一次。\n");
        } else { // 如果玩家猜高了，提示玩家
            printf("太高了！再试一次。\n");
        }
    }

    // 如果炸弹被拆除，恭喜玩家
    if(bomb_defused) {
        printf("恭喜，你成功拆除了炸弹！\n");        
        printf("\n");
        printf("\033[0;34m"); // 设置颜色为蓝色
        printf("       \n");
        printf(" _   _  ___  _   _  __      _(_)_ __  \n");
        printf("| | | |/ _ \\| | | | \\ \\ /\\ / / | '_ \\ \n");
        printf("| |_| | (_) | |_| |  \\ V  V /| | | | |\n");
        printf(" \\__, |\\___/ \\__,_|   \\_/\\_/ |_|_| |_|\n");
        printf(" |___/                             \n");
        printf("\033[0m"); // 重置颜色
        printf("\n");
    } else { // 如果炸弹未被拆除，告诉玩家正确的解除代码，并结束游戏
       
        printf("砰！炸弹爆炸了。正确的解除代码是%d。\n", disarm_code);
        printf("\n");
        printf("\033[0;31m"); // 设置颜色为红色
        printf(" __ _  __ _ _ __ ___   ___    _____   _____ _ __ \n");
        printf("/ _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|\n");
        printf("| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |   \n");
        printf("\\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   \n");
        printf(" |___/                                             \n");
        printf("\033[0m"); // 重置颜色
        printf("\n");
    }

    return 0;
}