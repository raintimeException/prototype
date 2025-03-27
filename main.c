#include <stdio.h>
#include <stdlib.h>

#define HEIGHT      10
#define WIDTH       30

static int sx = WIDTH/2;
static int sy = HEIGHT/2;
static int fx, fy;
static int zx, zy;
static int gameover;

static unsigned int score;
static int level = 1;

static void gen_pos_x_pos_y(int *x, int *y)
{
    *x = arc4random_uniform(WIDTH);
    *y = arc4random_uniform(HEIGHT);

    while (*x <= 1 || *x >= WIDTH-1) {
        *x = arc4random_uniform(WIDTH);
    }
    while (*y <= 1 || *y >= HEIGHT-1) {
        *y = arc4random_uniform(HEIGHT);
    }
}

static void draw(void)
{
    printf(" --------------------------------\n");
    printf("|           (w -> up)            |\n");
    printf("|               ^                |\n");
    printf("|               |                |\n");
    printf("|(a -> left) <--0--> (d -> right)|\n");
    printf("|               |                |\n");
    printf("|               v                |\n");
    printf("|           (s -> down)          |\n");
    printf(" --------------------------------\n");
    printf("[sy: %d]\n", sy);
    printf("[sx: %d]\n", sx);

    printf("~~~~~~~~~\n");
    printf("SCORE: %d\n", score);
    printf("LEVEL: %d\n", level);
    printf("~~~~~~~~~\n");

    // up
    for (int i = 0; i <= WIDTH; ++i)
        printf("*");
    printf("\n");

    for (int i = 0; i < HEIGHT+level; ++i) {
        for (int j = 0; j <= WIDTH+level; ++j) {

            // corners
            if (j == 0 || j == WIDTH-1) {
                printf("+");
            }

            if ((j == fx && i == fy) && (j == sx && i == sy)) {
                printf("0");
            } else if ((j == zx && i == zy) && (j == sx && i == sy)) {
                printf("x");
            } else if (j == fx && i == fy) {
                printf("@");
            } else if (j == sx && i == sy) {
                printf("0");
            } else if (j == zx && i == zy) {
                printf("x");
            } else {
                printf(" ");
            }

        }
        printf("\n");
    }

    // down
    for (int i = 0; i <= WIDTH; ++i)
        printf("*");
    printf("\n");

}

static void input(void)
{
    char direction = getchar();


    if (direction == 'w') {
        sy--; printf("w\n");
    } else if (direction == 's') {
        sy++; printf("s\n");
    } else if (direction == 'd') {
        sx++; printf("d\n");
    } else if (direction == 'a') {
        sx--; printf("a\n");
    }
}


static void logic(void)
{
    if (sx == fx && sy == fy) {
        ++score;
        gen_pos_x_pos_y(&fx, &fy);
        if (score % 2 == 0) {
            level++;
        }
    }
    gen_pos_x_pos_y(&zx, &zy);

    if (sx == zx && sy == zy) {
        gameover = 1;
        printf("           GAME OVER            \n");
        printf("YOU HAVE BEEN KILLED BY A ZOMBIE\n");
    }
    if (sx < 1 || sx >= WIDTH-1 || sy < 0 || sy >= HEIGHT) gameover = 1;
}

int main(void)
{
    gen_pos_x_pos_y(&fx, &fy);

    while (!gameover) {
        draw();
        input();
        logic();
        // sleep(1); // I don't need this because of the read() function...
    }
    printf("END\n");
    return 0;
}
