#include <stdio.h>
#include <stdlib.h>

#define HEIGHT      10
#define WIDTH       30

static int sx, sy, fx, fy;
static int gameover = 0;
static unsigned int score = 0;

static void gen_fruit(void)
{
    sx = WIDTH/2;
    sy = HEIGHT/2;

    fx = arc4random_uniform(WIDTH);
    fy = arc4random_uniform(HEIGHT);

    while (fx <= 1 || fx >= WIDTH-1) {
        fx = arc4random_uniform(WIDTH);
    }
    while (fy <= 1 || fy >= HEIGHT-1) {
        fy = arc4random_uniform(HEIGHT);
    }
}

static void draw(void)
{
    char c_to_print;

    // up
    for (int i = 0; i < WIDTH; ++i)
        printf("*");
    printf("\n");

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j <= WIDTH; ++j) {

            c_to_print = ' ';
            // corners
            if (j == 0 || j == WIDTH-1) {
                printf("+");
            }

            if (j == fx && i == fy) {
                printf("@");
                j++; i++;
            }

            if (j == sx && i == sy) {
                printf("0");
                j++; i++;
            }

            printf(" ");
        }
        printf("\n");
    }

    // down
    for (int i = 0; i < WIDTH; ++i)
        printf("*");
    printf("\n");

    printf(" --------------------------------\n");
    printf("|           (w -> up)            |\n");
    printf("|               ^                |\n");
    printf("|               |                |\n");
    printf("|(a -> left) <--0--> (d -> right)|\n");
    printf("|               |                |\n");
    printf("|               v                |\n");
    printf("|           (s -> down)          |\n");
    printf(" --------------------------------\n");
    printf("sy: %d\n", sy);
    printf("sx: %d\n", sx);
    printf("score: %d\n", score);
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
        gen_fruit();
    }

    if (sx <= 1 || sx >= WIDTH-1 || sy <= 1 || sy >= HEIGHT-1) gameover = 1;
}

int main(void)
{
    gen_fruit();

    while (!gameover) {
        draw();
        input();
        logic();
        // sleep(1); // I don't need this because of the read() function...
    }
    printf("END\n");
    return 0;
}
