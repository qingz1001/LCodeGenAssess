#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ANTS 2000000
#define MAX_TOWERS 20

typedef struct {
    int birth_time;
    int level;
    int hp;
    int x, y;
    int prev_x, prev_y;
    int carrying;
    int alive;
} Ant;

typedef struct {
    int x, y;
} Tower;

int n, m;
int s, d, r;
Tower towers[MAX_TOWERS];
int t;
int pheromone[10][10];
Ant ants[MAX_ANTS];
int ant_count = 0;
int live_ants = 0;
int cake_x, cake_y;
int game_over = 0;
int game_over_time = 0;

// Directions: East, South, West, North
int dir_x[4] = {1, 0, -1, 0};
int dir_y[4] = {0, 1, 0, -1};
const char dir_order[4] = {0, 1, 2, 3}; // E, S, W, N

// Function to calculate level based on birth order
int get_level(int birth_order){
    return (birth_order-1)/6 +1;
}

// Function to calculate initial hp based on level
int get_initial_hp(int level){
    double val = 4.0 * pow(1.1, level);
    return (int)floor(val);
}

// Function to compare ants by birth_time
int compare_ant(const void *a, const void *b){
    Ant *A = (Ant *)a;
    Ant *B = (Ant *)b;
    return A->birth_time - B->birth_time;
}

// Function to calculate distance squared
double distance_sq(int x1, int y1, int x2, int y2){
    double dx = (double)(x1 - x2);
    double dy = (double)(y1 - y2);
    return dx*dx + dy*dy;
}

// Function to check if position is within map
int in_map(int x, int y){
    return x >=0 && x <=n && y >=0 && y <=m;
}

// Function to check if position has tower
int has_tower(int x, int y){
    for(int i=0;i<s;i++) if(towers[i].x ==x && towers[i].y == y) return 1;
    return 0;
}

// Function to check if any ant is at position
int has_ant(int x, int y, int current_ant){
    for(int i=0;i<ant_count;i++) {
        if(i == current_ant) continue;
        if(ants[i].alive && ants[i].x ==x && ants[i].y ==y) return 1;
    }
    return 0;
}

// Function to select direction for an ant
int select_direction(int a_idx, int current_time){
    Ant *ant = &ants[a_idx];
    int possible_dirs[4];
    int cnt =0;
    for(int d_dir=0; d_dir<4; d_dir++){
        int nx = ant->x + dir_x[d_dir];
        int ny = ant->y + dir_y[d_dir];
        if(!in_map(nx, ny)) continue;
        if(has_tower(nx, ny)) continue;
        if(has_ant(nx, ny, a_idx)) continue;
        if(!(ant->prev_x == nx && ant->prev_y == ny)) {
            possible_dirs[cnt++] = d_dir;
        }
    }
    if(cnt ==0){
        // Can go back if stuck
        for(int d_dir=0; d_dir<4; d_dir++){
            int nx = ant->x + dir_x[d_dir];
            int ny = ant->y + dir_y[d_dir];
            if(!in_map(nx, ny)) continue;
            if(has_tower(nx, ny)) continue;
            if(has_ant(nx, ny, a_idx)) continue;
            possible_dirs[cnt++] = d_dir;
        }
    }
    if(cnt ==0) return -1;
    // Select direction with max pheromone
    int max_pher= -1;
    for(int i=0;i<cnt;i++) {
        int dir_sel = possible_dirs[i];
        int nx = ant->x + dir_x[dir_sel];
        int ny = ant->y + dir_y[dir_sel];
        if(pheromone[nx][ny] > max_pher){
            max_pher = pheromone[nx][ny];
        }
    }
    // Collect dirs with max pheromone
    int best_dirs[4];
    int best_cnt=0;
    for(int i=0;i<cnt;i++) {
        int dir_sel = possible_dirs[i];
        int nx = ant->x + dir_x[dir_sel];
        int ny = ant->y + dir_y[dir_sel];
        if(pheromone[nx][ny] == max_pher){
            best_dirs[best_cnt++] = dir_sel;
        }
    }
    if(best_cnt ==1) return best_dirs[0];
    // Tie-breaker: East, then clockwise
    int priority_dirs[4] = {0,1,2,3};
    for(int i=0;i<4;i++) {
        for(int j=0;j<best_cnt;j++) {
            if(best_dirs[j] == priority_dirs[i]) return best_dirs[j];
        }
    }
    return best_dirs[0];
}

// Function to rotate direction clockwise
int rotate_clockwise(int dir){
    return (dir +1)%4;
}

// Function to rotate direction counter-clockwise
int rotate_counter(int dir){
    return (dir +3)%4;
}

// Function to handle movement with rule 4
int adjust_direction(int a_idx, int selected_dir){
    Ant *ant = &ants[a_idx];
    int current_time = ant->birth_time + ant->hp; // Not sure, better use age
    int age = current_time;
    if((age) %5 !=0) return selected_dir;
    // Rotate selected_dir counter-clockwise until valid
    int dir = rotate_counter(selected_dir);
    for(int i=0;i<4;i++){
        int nx = ant->x + dir_x[dir];
        int ny = ant->y + dir_y[dir];
        if(!in_map(nx, ny)) { dir = rotate_counter(dir); continue;}
        if(has_tower(nx, ny)) { dir = rotate_counter(dir); continue;}
        int conflict = has_ant(nx, ny, a_idx);
        if(conflict) { dir = rotate_counter(dir); continue;}
        if(!(ant->prev_x == nx && ant->prev_y == ny)) {
            return dir;
        }
        dir = rotate_counter(dir);
    }
    return selected_dir;
}

int main(){
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);
    for(int i=0;i<s;i++) scanf("%d %d", &towers[i].x, &towers[i].y);
    scanf("%d", &t);
    cake_x = n;
    cake_y = m;
    // Initialize pheromone
    memset(pheromone, 0, sizeof(pheromone));
    // Simulation
    int current_time =1;
    int carrying_ant = -1;
    int cake_present =1;
    for(; current_time<=t; current_time++){
        // 1. Spawn ants
        if(live_ants <6){
            int occupied = has_ant(0,0,-1) || has_tower(0,0);
            if(!occupied){
                // Spawn ant
                ant_count++;
                live_ants++;
                Ant *ant = &ants[ant_count-1];
                ant->birth_time = current_time;
                ant->level = get_level(ant_count);
                ant->hp = get_initial_hp(ant->level);
                ant->x =0;
                ant->y =0;
                ant->prev_x = -1;
                ant->prev_y = -1;
                ant->carrying =0;
                ant->alive =1;
            }
        }
        // 2. Leave pheromones
        for(int i=0;i<ant_count;i++) {
            if(!ants[i].alive) continue;
            if(ants[i].carrying){
                pheromone[ants[i].x][ants[i].y] +=5;
            }
            else{
                pheromone[ants[i].x][ants[i].y] +=2;
            }
        }
        // 3. Move ants
        // Sort ants by birth_time
        qsort(ants, ant_count, sizeof(Ant), compare_ant);
        for(int i=0;i<ant_count;i++){
            if(!ants[i].alive) continue;
            if(carrying_ant != -1 && carrying_ant ==i) continue;
            // Select direction
            int dir = select_direction(i, current_time);
            if(dir == -1){
                // Stay
                ants[i].prev_x = ants[i].x;
                ants[i].prev_y = ants[i].y;
                continue;
            }
            // Handle rule 4
            int age = current_time - ants[i].birth_time +1;
            if(age %5 ==0){
                // Rotate direction counter-clockwise
                int original_dir = dir;
                int rotated_dir = rotate_counter(dir);
                int tried =0;
                while(tried <4){
                    int nx = ants[i].x + dir_x[rotated_dir];
                    int ny = ants[i].y + dir_y[rotated_dir];
                    if(in_map(nx, ny) && !has_tower(nx, ny) && !has_ant(nx, ny, i)){
                        if(!(ants[i].prev_x == nx && ants[i].prev_y == ny)){
                            dir = rotated_dir;
                            break;
                        }
                    }
                    rotated_dir = rotate_counter(rotated_dir);
                    tried++;
                }
            }
            // Move
            int nx = ants[i].x + dir_x[dir];
            int ny = ants[i].y + dir_y[dir];
            if(in_map(nx, ny) && !has_tower(nx, ny) && !has_ant(nx, ny, i)){
                ants[i].prev_x = ants[i].x;
                ants[i].prev_y = ants[i].y;
                ants[i].x = nx;
                ants[i].y = ny;
            }
            else{
                ants[i].prev_x = ants[i].x;
                ants[i].prev_y = ants[i].y;
            }
        }
        // 4. Check for cake pickup
        if(cake_present){
            for(int i=0;i<ant_count;i++) {
                if(!ants[i].alive) continue;
                if(ants[i].x == cake_x && ants[i].y == cake_y){
                    // Pick up cake
                    ants[i].carrying =1;
                    carrying_ant =i;
                    // Increase hp
                    int increase = ants[i].hp /2;
                    int max_hp = get_initial_hp(ants[i].level);
                    ants[i].hp += increase;
                    if(ants[i].hp > max_hp) ants[i].hp = max_hp;
                    cake_present =0;
                    break;
                }
            }
        }
        // 5. Towers attack
        // Determine targets for each tower
        int targets[MAX_TOWERS];
        for(int i=0;i<s;i++) targets[i] = -1;
        for(int i=0;i<s;i++) {
            // Check if there is a carrying ant in range
            int tx = towers[i].x;
            int ty = towers[i].y;
            int min_dist = r*r +1;
            int target = -1;
            // First prioritize carrying ant
            if(carrying_ant != -1){
                double dist = distance_sq(tx, ty, ants[carrying_ant].x, ants[carrying_ant].y);
                if(dist <= r*r){
                    targets[i] = carrying_ant;
                    continue;
                }
            }
            // Else, find closest ant
            for(int j=0;j<ant_count;j++) {
                if(!ants[j].alive) continue;
                double dist = distance_sq(tx, ty, ants[j].x, ants[j].y);
                if(dist > r*r) continue;
                if(dist < min_dist || (dist == min_dist && j < target)){
                    min_dist = dist;
                    target =j;
                }
            }
            if(target != -1) targets[i] = target;
        }
        // Apply attacks
        for(int i=0;i<s;i++) {
            if(targets[i]==-1) continue;
            int tx = towers[i].x;
            int ty = towers[i].y;
            int target = targets[i];
            // Determine the line
            // Bresenham's line algorithm simplified
            double dx = ants[target].x - tx;
            double dy = ants[target].y - ty;
            double step = fmax(fabs(dx), fabs(dy));
            double x_inc = dx / step;
            double y_inc = dy / step;
            double x = tx + 0.5;
            double y_pos = ty + 0.5;
            int hit =0;
            for(int s_step=0;s_step<=step;s_step++){
                int cx = round(x);
                int cy = round(y_pos);
                // Check if ant is at (cx, cy)
                for(int j=0;j<ant_count;j++) {
                    if(!ants[j].alive) continue;
                    double dist = sqrt((ants[j].x -x)*(ants[j].x -x) + (ants[j].y - y_pos)*(ants[j].y - y_pos));
                    if(dist <=0.5){
                        ants[j].hp -=d;
                        if(ants[j].hp <0){
                            ants[j].alive =0;
                            live_ants--;
                            if(carrying_ant ==j){
                                carrying_ant = -1;
                                cake_present =1;
                            }
                        }
                        hit =1;
                        break;
                    }
                }
                if(hit) break;
                x +=x_inc;
                y_pos +=y_inc;
            }
        }
        // 6. Check if carrying ant reached (0,0)
        if(carrying_ant != -1){
            if(ants[carrying_ant].x ==0 && ants[carrying_ant].y ==0){
                game_over =1;
                game_over_time = current_time;
                break;
            }
        }
        // 7. Pheromone decay
        for(int i_p=0;i_p<=n;i_p++) for(int j_p=0;j_p<=m;j_p++) {
            if(pheromone[i_p][j_p] >0) pheromone[i_p][j_p]--;
        }
        // 8. Age increment is implicit by current_time
    }
    if(game_over){
        printf("Game over after %d seconds\n", game_over_time);
    }
    else{
        printf("The game is going on\n");
    }
    // Prepare list of live ants
    Ant live_list[MAX_ANTS];
    int live_num =0;
    for(int i=0;i<ant_count;i++) {
        if(ants[i].alive){
            live_list[live_num++] = ants[i];
        }
    }
    // Sort live_list by age descending (current_time - birth_time)
    for(int i=0;i<live_num-1;i++) {
        for(int j=i+1;j<live_num;j++) {
            int age_i = (game_over? game_over_time : current_time-1) - live_list[i].birth_time;
            int age_j = (game_over? game_over_time : current_time-1) - live_list[j].birth_time;
            if(age_i < age_j){
                Ant temp = live_list[i];
                live_list[i] = live_list[j];
                live_list[j] = temp;
            }
        }
    }
    printf("%d\n", live_num);
    for(int i=0;i<live_num;i++) {
        int age = (game_over? game_over_time : current_time-1) - live_list[i].birth_time;
        printf("%d %d %d %d %d\n", age, live_list[i].level, live_list[i].hp, live_list[i].x, live_list[i].y);
    }
    return 0;
}