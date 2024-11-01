#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 8
#define MAX_M 8
#define MAX_ANTS 1000
#define MAX_TOWERS 20

typedef struct {
    int age;
    int level;
    int health;
    int x, y;
    int hasCake;
} Ant;

typedef struct {
    int x, y;
} Tower;

int n, m, s, d, r, t;
int map[MAX_N+1][MAX_M+1];
int pheromone[MAX_N+1][MAX_M+1];
Tower towers[MAX_TOWERS];
Ant ants[MAX_ANTS];
int antCount = 0;
int gameOver = 0;
int gameOverTime = 0;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void initGame() {
    memset(map, 0, sizeof(map));
    memset(pheromone, 0, sizeof(pheromone));
    for (int i = 0; i < s; i++) {
        map[towers[i].x][towers[i].y] = 1;
    }
}

int isValidMove(int x, int y) {
    return x >= 0 && x <= n && y >= 0 && y <= m && map[x][y] == 0;
}

void moveAnt(int i) {
    Ant *ant = &ants[i];
    int bestDir = -1;
    int maxPheromone = -1;

    for (int dir = 0; dir < 4; dir++) {
        int nx = ant->x + dx[dir];
        int ny = ant->y + dy[dir];
        if (isValidMove(nx, ny) && (nx != ant->x || ny != ant->y) && pheromone[nx][ny] > maxPheromone) {
            maxPheromone = pheromone[nx][ny];
            bestDir = dir;
        }
    }

    if (bestDir == -1) return;

    if (ant->age % 5 == 0) {
        bestDir = (bestDir + 3) % 4;
        for (int i = 0; i < 4; i++) {
            int nx = ant->x + dx[bestDir];
            int ny = ant->y + dy[bestDir];
            if (isValidMove(nx, ny)) break;
            bestDir = (bestDir + 3) % 4;
        }
    }

    ant->x += dx[bestDir];
    ant->y += dy[bestDir];
}

void spawnAnt() {
    if (antCount < 6 && map[0][0] == 0) {
        Ant newAnt = {0, (antCount / 6) + 1, 0, 0, 0, 0};
        newAnt.health = floor(4 * pow(1.1, newAnt.level));
        ants[antCount++] = newAnt;
    }
}

void updatePheromone() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (pheromone[i][j] > 0) pheromone[i][j]--;
        }
    }
    for (int i = 0; i < antCount; i++) {
        pheromone[ants[i].x][ants[i].y] += ants[i].hasCake ? 5 : 2;
    }
}

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void towerAttack() {
    for (int i = 0; i < s; i++) {
        int targetAnt = -1;
        double minDist = 1e9;
        for (int j = 0; j < antCount; j++) {
            if (ants[j].hasCake && distance(towers[i].x, towers[i].y, ants[j].x, ants[j].y) <= r) {
                targetAnt = j;
                break;
            }
            double dist = distance(towers[i].x, towers[i].y, ants[j].x, ants[j].y);
            if (dist <= r && dist < minDist) {
                minDist = dist;
                targetAnt = j;
            }
        }
        if (targetAnt != -1) {
            for (int j = 0; j < antCount; j++) {
                if (distance(towers[i].x, towers[i].y, ants[j].x, ants[j].y) <= 
                    distance(towers[i].x, towers[i].y, ants[targetAnt].x, ants[targetAnt].y)) {
                    ants[j].health -= d;
                }
            }
        }
    }
}

void removeDeadAnts() {
    int newCount = 0;
    for (int i = 0; i < antCount; i++) {
        if (ants[i].health > 0) {
            ants[newCount++] = ants[i];
        } else if (ants[i].hasCake) {
            map[n][m] = 0;
        }
    }
    antCount = newCount;
}

void checkCake() {
    for (int i = 0; i < antCount; i++) {
        if (ants[i].x == n && ants[i].y == m && map[n][m] == 0) {
            ants[i].hasCake = 1;
            map[n][m] = 1;
            int healthIncrease = floor(4 * pow(1.1, ants[i].level) / 2);
            ants[i].health = fmin(ants[i].health + healthIncrease, floor(4 * pow(1.1, ants[i].level)));
        }
        if (ants[i].hasCake && ants[i].x == 0 && ants[i].y == 0) {
            gameOver = 1;
            return;
        }
    }
}

void simulateGame() {
    for (int second = 1; second <= t; second++) {
        spawnAnt();
        for (int i = 0; i < antCount; i++) {
            moveAnt(i);
            ants[i].age++;
        }
        checkCake();
        if (gameOver) {
            gameOverTime = second;
            return;
        }
        towerAttack();
        removeDeadAnts();
        updatePheromone();
    }
}

void printResult() {
    if (gameOver) {
        printf("Game over after %d seconds\n", gameOverTime);
    } else {
        printf("The game is going on\n");
    }
    printf("%d\n", antCount);
    for (int i = 0; i < antCount; i++) {
        for (int j = i + 1; j < antCount; j++) {
            if (ants[i].age < ants[j].age) {
                Ant temp = ants[i];
                ants[i] = ants[j];
                ants[j] = temp;
            }
        }
    }
    for (int i = 0; i < antCount; i++) {
        printf("%d %d %d %d %d\n", ants[i].age, ants[i].level, ants[i].health, ants[i].x, ants[i].y);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);
    for (int i = 0; i < s; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
    }
    scanf("%d", &t);

    initGame();
    simulateGame();
    printResult();

    return 0;
}