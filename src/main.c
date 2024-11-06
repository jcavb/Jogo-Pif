#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define WIDTH 20
#define HEIGHT 20

typedef struct {
    int x, y;
} Car;

Car player;
Car obstacles[5];
int score = 0;
int game_over = 0;

void init_game() {
    player.x = WIDTH / 2;
    player.y = HEIGHT - 2;
    for (int i = 0; i < 5; i++) {
        obstacles[i].x = rand() % WIDTH;
        obstacles[i].y = rand() % (HEIGHT / 2);
    }
}

void update_game() {
    if (kbhit()) {
        char key = getch();
        if (key == 'w') player.y--;
        if (key == 's') player.y++;
        if (key == 'a') player.x--;
        if (key == 'd') player.x++;
    }

    for (int i = 0; i < 5; i++) {
        obstacles[i].y++;
        if (obstacles[i].y >= HEIGHT) {
            obstacles[i].y = 0;
            obstacles[i].x = rand() % WIDTH;
            score++;
        }
        if (obstacles[i].x == player.x && obstacles[i].y == player.y) {
            game_over = 1;
        }
    }
}

void draw_game() {
    clear_screen();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == player.y && j == player.x) {
                printf("A");
            } else {
                int is_obstacle = 0;
                for (int k = 0; k < 5; k++) {
                    if (i == obstacles[k].y && j == obstacles[k].x) {
                        printf("X");
                        is_obstacle = 1;
                        break;
                    }
                }
                if (!is_obstacle) {
                    printf(".");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

int main() {
    init_screen();
    init_game();
    while (!game_over) {
        update_game();
        draw_game();
        delay(100);
    }
    printf("Game Over! Final Score: %d\n", score);
return 0;
}