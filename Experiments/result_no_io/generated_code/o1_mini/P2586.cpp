#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ANTS 1000000
#define MAX_TOWERS 20
#define MAX_N 9
#define MAX_M 9

typedef struct {
    int age;
    int level;
    int blood;
    int x, y;
    int has_cake;
    int prev_x, prev_y;
    int active;
    int birth_time;
} Ant;

typedef struct {
    int x, y;
} Tower;

int n, m, s, d, r, t;
Tower towers[MAX_TOWERS];
Ant ants[MAX_ANTS];
int ant_count = 0;
int pheromone[MAX_N+1][MAX_M+1];
int occupied[MAX_N+1][MAX_M+1];
int has_cake = 0;
int cake_x, cake_y;
int game_over_time = -1;
int game_over = 0;

int cmp_ant(const void* a, const void* b){
    Ant* aa = (Ant*)a;
    Ant* bb = (Ant*)b;
    if (aa->age != bb->age) return bb->age - aa->age;
    return 0;
}

int distance_squared(int x1, int y1, int x2, int y2){
    int dx = x1 - x2, dy = y1 - y2;
    return dx*dx + dy*dy;
}

int main(){
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);
    for(int i=0;i<s;i++) scanf("%d %d", &towers[i].x, &towers[i].y);
    scanf("%d", &t);
    cake_x = n;
    cake_y = m;
    for(int time=1; time<=t && !game_over; time++){
        // 1. Spawn ant
        if(ant_count < MAX_ANTS){
            int current_ants = 0;
            for(int i=0;i<ant_count;i++) if(ants[i].active && (ants[i].x !=0 || ants[i].y !=0)) current_ants++;
            if(current_ants <6){
                int occupied_flag = 0;
                for(int i=0;i<ant_count;i++) if(ants[i].active && ants[i].x ==0 && ants[i].y ==0){
                    occupied_flag =1; break;
                }
                if(!occupied_flag){
                    Ant new_ant;
                    new_ant.age =0;
                    new_ant.level = (ant_count /6)+1;
                    double tmp = 4 * pow(1.1, new_ant.level);
                    new_ant.blood = floor(tmp);
                    new_ant.x =0;
                    new_ant.y =0;
                    new_ant.has_cake =0;
                    new_ant.prev_x = -1;
                    new_ant.prev_y = -1;
                    new_ant.active =1;
                    new_ant.birth_time = time;
                    ants[ant_count++] = new_ant;
                }
            }
        }
        // 2. Leave pheromones
        memset(occupied, 0, sizeof(occupied));
        for(int i=0;i<ant_count;i++) if(ants[i].active){
            occupied[ants[i].x][ants[i].y] =1;
        }
        for(int i=0;i<ant_count;i++) if(ants[i].active){
            if(ants[i].has_cake) pheromone[ants[i].x][ants[i].y] +=5;
            else pheromone[ants[i].x][ants[i].y] +=2;
        }
        // 3. Move ants
        for(int i=0;i<ant_count;i++) {
            if(!ants[i].active) continue;
            // Determine movement
            int directions[4][2] = {{1,0},{0,1},{-1,0},{0,-1}}; // E, S, W, N
            int possible_dir[4][2];
            int possible_count =0;
            for(int d_dir=0;d_dir<4;d_dir++){
                int nx = ants[i].x + directions[d_dir][0];
                int ny = ants[i].y + directions[d_dir][1];
                if(nx <0 || ny <0 || nx >n || ny >m) continue;
                int blocked =0;
                // Check towers
                for(int ti=0;ti<s;ti++) if(towers[ti].x ==nx && towers[ti].y ==ny){
                    blocked =1; break;
                }
                if(blocked) continue;
                // Check other ants
                for(int ai=0;ai<ant_count;ai++) if(ai !=i && ants[ai].active && ants[ai].x ==nx && ants[ai].y ==ny){
                    blocked =1; break;
                }
                if(blocked) continue;
                // Check previous position
                if(!(ants[i].prev_x == nx && ants[i].prev_y == ny)){
                    possible_dir[possible_count][0] = directions[d_dir][0];
                    possible_dir[possible_count][1] = directions[d_dir][1];
                    possible_count++;
                }
            }
            if(possible_count ==0){
                ants[i].prev_x = ants[i].x;
                ants[i].prev_y = ants[i].y;
                continue;
            }
            // Select direction with max pheromone
            int max_pher = -1;
            for(int d_dir=0;d_dir<possible_count;d_dir++) {
                int px = ants[i].x + possible_dir[d_dir][0];
                int py = ants[i].y + possible_dir[d_dir][1];
                if(pheromone[px][py] > max_pher) max_pher = pheromone[px][py];
            }
            // Collect directions with max pheromone
            int candidates[4][2];
            int cand_count =0;
            for(int d_dir=0;d_dir<possible_count;d_dir++) {
                int px = ants[i].x + possible_dir[d_dir][0];
                int py = ants[i].y + possible_dir[d_dir][1];
                if(pheromone[px][py] == max_pher){
                    candidates[cand_count][0] = possible_dir[d_dir][0];
                    candidates[cand_count][1] = possible_dir[d_dir][1];
                    cand_count++;
                }
            }
            // If multiple, apply rule 3
            int chosen_dir_x =0, chosen_dir_y =0;
            if(cand_count >1){
                // Priority: East, then clockwise
                int priority_dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
                for(int pd=0;pd<4;pd++) {
                    for(int cd=0;cd<cand_count;cd++) {
                        if(candidates[cd][0] == priority_dirs[pd][0] && candidates[cd][1] == priority_dirs[pd][1]){
                            chosen_dir_x = candidates[cd][0];
                            chosen_dir_y = candidates[cd][1];
                            break;
                        }
                    }
                    if(chosen_dir_x !=0 || chosen_dir_y !=0) break;
                }
            }
            else{
                chosen_dir_x = candidates[0][0];
                chosen_dir_y = candidates[0][1];
            }
            // Apply rule 4
            if(time %5 ==0){
                // Determine direction
                int dir_idx = -1;
                for(int d_dir=0;d_dir<4;d_dir++) if(directions[d_dir][0]==chosen_dir_x && directions[d_dir][1]==chosen_dir_y){
                    dir_idx = d_dir;
                    break;
                }
                if(dir_idx != -1){
                    dir_idx = (dir_idx +3)%4; // counter clockwise
                    int rotated =0;
                    while(rotated <4){
                        int rx = directions[dir_idx][0];
                        int ry = directions[dir_idx][1];
                        int nx = ants[i].x + rx;
                        int ny = ants[i].y + ry;
                        if(nx >=0 && ny >=0 && nx <=n && ny <=m){
                            // Check towers
                            int blocked =0;
                            for(int ti=0;ti<s;ti++) if(towers[ti].x ==nx && towers[ti].y ==ny){
                                blocked =1; break;
                            }
                            if(!blocked){
                                // Check other ants
                                blocked =0;
                                for(int ai=0;ai<ant_count;ai++) if(ai !=i && ants[ai].active && ants[ai].x ==nx && ants[ai].y ==ny){
                                    blocked =1; break;
                                }
                                if(!blocked){
                                    chosen_dir_x = rx;
                                    chosen_dir_y = ry;
                                    break;
                                }
                            }
                        }
                        dir_idx = (dir_idx +3)%4;
                        rotated++;
                    }
                }
            }
            // Move
            ants[i].prev_x = ants[i].x;
            ants[i].prev_y = ants[i].y;
            ants[i].x += chosen_dir_x;
            ants[i].y += chosen_dir_y;
        }
        // 4. Check for cake pickup
        if(!has_cake){
            for(int i=0;i<ant_count;i++) if(ants[i].active && ants[i].x ==cake_x && ants[i].y ==cake_y){
                has_cake =1;
                ants[i].has_cake =1;
                double tmp = ants[i].blood + floor(ants[i].blood/2.0);
                // Calculate max blood
                int lvl = ants[i].level;
                double max_blood_f = 4 * pow(1.1, lvl);
                int max_blood = floor(max_blood_f);
                if(tmp > max_blood) tmp = max_blood;
                ants[i].blood = (int)tmp;
                break;
            }
        }
        // 5. Towers attack
        // Determine targets
        Ant* targets[s];
        for(int ti=0;ti<s;ti++) targets[ti] = NULL;
        for(int ti=0;ti<s;ti++){
            int tx = towers[ti].x;
            int ty = towers[ti].y;
            Ant* target = NULL;
            // Check if any ant has cake and in range
            for(int ai=0;ai<ant_count;ai++) if(ants[ai].active && ants[ai].has_cake){
                double dist = sqrt((ants[ai].x - tx)*(ants[ai].x - tx) + (ants[ai].y - ty)*(ants[ai].y - ty));
                if(dist <= r){
                    if(target == NULL || ants[ai].birth_time < target->birth_time){
                        target = &ants[ai];
                    }
                }
            }
            if(target == NULL){
                // Find closest ant
                int min_dist_sq = (n)*(n)+(m)*(m)+1;
                for(int ai=0;ai<ant_count;ai++) if(ants[ai].active){
                    double dist = sqrt((ants[ai].x - tx)*(ants[ai].x - tx) + (ants[ai].y - ty)*(ants[ai].y - ty));
                    if(dist <= r){
                        if(distance_squared(ants[ai].x, ants[ai].y, tx, ty) < min_dist_sq){
                            min_dist_sq = distance_squared(ants[ai].x, ants[ai].y, tx, ty);
                            target = &ants[ai];
                        }
                        else if(distance_squared(ants[ai].x, ants[ai].y, tx, ty) == min_dist_sq){
                            if(target && ants[ai].birth_time < target->birth_time){
                                target = &ants[ai];
                            }
                        }
                    }
                }
            }
            targets[ti] = target;
        }
        // Apply attacks
        for(int ti=0;ti<s;ti++) if(targets[ti]){
            int tx = towers[ti].x;
            int ty = towers[ti].y;
            Ant* tgt = targets[ti];
            // Calculate angle
            double angle = atan2(tgt->y - ty, tgt->x - tx);
            // Traverse grid in line
            int dx = (tgt->x > tx) ? 1 : (tgt->x < tx) ? -1 :0;
            int dy = (tgt->y > ty) ? 1 : (tgt->y < ty) ? -1 :0;
            int cx = tx;
            int cy = ty;
            while(!(cx == tgt->x && cy == tgt->y)){
                cx += dx;
                cy += dy;
                // Check if ant is here
                for(int ai=0;ai<ant_count;ai++) if(ants[ai].active){
                    double dist = sqrt((ants[ai].x - cx)*(ants[ai].x - cx) + (ants[ai].y - cy)*(ants[ai].y - cy));
                    if(dist <=0.5){
                        ants[ai].blood -=d;
                        if(ants[ai].blood <0){
                            ants[ai].active =0;
                            if(ants[ai].has_cake){
                                has_cake =0;
                            }
                        }
                        break;
                    }
                }
                // Stop if target is hit
                if(cx == tgt->x && cy == tgt->y) break;
            }
        }
        // 6. Check if cake holding ant reached (0,0)
        for(int i=0;i<ant_count;i++) if(ants[i].active && ants[i].has_cake && ants[i].x ==0 && ants[i].y ==0){
            game_over =1;
            game_over_time = time;
            break;
        }
        // 7. Update pheromones
        for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) if(pheromone[i][j] >0) pheromone[i][j]--;
        // 8. Update ages
        for(int i=0;i<ant_count;i++) if(ants[i].active) ants[i].age++;
    }
    if(game_over_time !=-1 && game_over_time <=t){
        printf("Game over after %d seconds\n", game_over_time);
    }
    else{
        printf("The game is going on\n");
    }
    // Collect active ants
    int alive =0;
    for(int i=0;i<ant_count;i++) if(ants[i].active) alive++;
    printf("%d\n", alive);
    // Sort ants by age descending
    qsort(ants, ant_count, sizeof(Ant), cmp_ant);
    for(int i=0;i<ant_count;i++) if(ants[i].active){
        printf("%d %d %d %d %d\n", ants[i].age, ants[i].level, ants[i].blood, ants[i].x, ants[i].y);
    }
    return 0;
}