#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 8
#define MAX_M 8
#define MAX_S 20
#define MAX_T 200000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int age;
    int level;
    int health;
    Point pos;
    int carryingCake;
} Ant;

typedef struct {
    Point pos;
    int damage;
    int range;
} Tower;

int n, m, s, d, r, t;
Tower towers[MAX_S];
Ant ants[6];
int antCount = 0;
int cakeCarrier = -1;
int gameOver = 0;

int isInRange(Point p1, Point p2, int range) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) <= range * range;
}

void spawnAnt() {
    if (antCount < 6) {
        ants[antCount].age = 0;
        ants[antCount].level = (antCount / 6) + 1;
        ants[antCount].health = (int)(4 * pow(1.1, ants[antCount].level));
        ants[antCount].pos.x = 0;
        ants[antCount].pos.y = 0;
        ants[antCount].carryingCake = 0;
        antCount++;
    }
}

void moveAnts() {
    for (int i = 0; i < antCount; i++) {
        if (ants[i].carryingCake && ants[i].pos.x == 0 && ants[i].pos.y == 0) {
            gameOver = 1;
            return;
        }
        // Implement movement logic here
    }
}

void attackAnts() {
    for (int i = 0; i < s; i++) {
        int target = -1;
        if (cakeCarrier != -1 && isInRange(towers[i].pos, ants[cakeCarrier].pos, towers[i].range)) {
            target = cakeCarrier;
        } else {
            for (int j = 0; j < antCount; j++) {
                if (isInRange(towers[i].pos, ants[j].pos, towers[i].range)) {
                    if (target == -1 || ants[j].age > ants[target].age) {
                        target = j;
                    }
                }
            }
        }
        if (target != -1) {
            ants[target].health -= towers[i].damage;
            if (ants[target].health <= 0) {
                if (ants[target].carryingCake) {
                    cakeCarrier = -1;
                }
                ants[target] = ants[antCount - 1];
                antCount--;
                i--;
            }
        }
    }
}

void updateGameState() {
    for (int i = 0; i < antCount; i++) {
        ants[i].age++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Implement pheromone logic here
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);
    for (int i = 0; i < s; i++) {
        scanf("%d %d", &towers[i].pos.x, &towers[i].pos.y);
        towers[i].damage = d;
        towers[i].range = r;
    }
    scanf("%d", &t);

    for (int time = 0; time < t && !gameOver; time++) {
        spawnAnt();
        moveAnts();
        attackAnts();
        updateGameState();
    }

    if (gameOver) {
        printf("Game over after %d seconds\n", t);
    } else {
        printf("The game is going on\n");
    }

    printf("%d\n", antCount);
    for (int i = 0; i < antCount; i++) {
        printf("%d %d %d %d %d\n", ants[i].age, ants[i].level, ants[i].health, ants[i].pos.x, ants[i].pos.y);
    }

    return 0;
}