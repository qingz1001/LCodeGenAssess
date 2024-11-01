#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long x;
    long long y;
    char type;
} Mirror;

int cmp_x(const void *a, const void *b) {
    Mirror *m1 = (Mirror *)a;
    Mirror *m2 = (Mirror *)b;
    if (m1->x != m2->x)
        return (m1->x < m2->x) ? -1 : 1;
    if (m1->y != m2->y)
        return (m1->y < m2->y) ? -1 : 1;
    return 0;
}

int cmp_y(const void *a, const void *b) {
    Mirror *m1 = (Mirror *)a;
    Mirror *m2 = (Mirror *)b;
    if (m1->y != m2->y)
        return (m1->y < m2->y) ? -1 : 1;
    if (m1->x != m2->x)
        return (m1->x < m2->x) ? -1 : 1;
    return 0;
}

int main(){
    int N;
    long long Bx, By;
    scanf("%d %lld %lld", &N, &Bx, &By);
    Mirror *mirrors = (Mirror *)malloc(N * sizeof(Mirror));
    for(int i=0;i<N;i++) {
        scanf("%lld %lld %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].type);
    }
    // Sort mirrors by x and y
    Mirror *mirrors_x = (Mirror *)malloc(N * sizeof(Mirror));
    Mirror *mirrors_y = (Mirror *)malloc(N * sizeof(Mirror));
    memcpy(mirrors_x, mirrors, N * sizeof(Mirror));
    memcpy(mirrors_y, mirrors, N * sizeof(Mirror));
    qsort(mirrors_x, N, sizeof(Mirror), cmp_x);
    qsort(mirrors_y, N, sizeof(Mirror), cmp_y);
    // Function to find next mirror in a direction
    auto find_next = [&](long long x, long long y, char dir) -> int {
        if(dir == 'N'){
            // Find the smallest y' > y with same x
            int left = 0, right = N-1, res = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(mirrors_x[mid].x == x && mirrors_x[mid].y > y){
                    res = mid;
                    right = mid -1;
                }
                else{
                    if(mirrors_x[mid].x < x || (mirrors_x[mid].x == x && mirrors_x[mid].y <= y))
                        left = mid +1;
                    else
                        right = mid -1;
                }
            }
            return res;
        }
        if(dir == 'S'){
            // Find the largest y' < y with same x
            int left = 0, right = N-1, res = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(mirrors_x[mid].x == x && mirrors_x[mid].y < y){
                    res = mid;
                    left = mid +1;
                }
                else{
                    if(mirrors_x[mid].x < x || (mirrors_x[mid].x == x && mirrors_x[mid].y >= y))
                        right = mid -1;
                    else
                        left = mid +1;
                }
            }
            return res;
        }
        if(dir == 'E'){
            // Find the smallest x' > x with same y
            int left = 0, right = N-1, res = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(mirrors_y[mid].y == y && mirrors_y[mid].x > x){
                    res = mid;
                    right = mid -1;
                }
                else{
                    if(mirrors_y[mid].y < y || (mirrors_y[mid].y == y && mirrors_y[mid].x <= x))
                        left = mid +1;
                    else
                        right = mid -1;
                }
            }
            return res;
        }
        if(dir == 'W'){
            // Find the largest x' < x with same y
            int left = 0, right = N-1, res = -1;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(mirrors_y[mid].y == y && mirrors_y[mid].x < x){
                    res = mid;
                    left = mid +1;
                }
                else{
                    if(mirrors_y[mid].y < y || (mirrors_y[mid].y == y && mirrors_y[mid].x >= x))
                        right = mid -1;
                    else
                        left = mid +1;
                }
            }
            return res;
        }
        return -1;
    };
    // Simulate the laser path
    long long cx = 0, cy = 0;
    char dir = 'N';
    // To store the path
    typedef struct {
        long long x;
        long long y;
        char direction;
    } PathPoint;
    PathPoint *path = (PathPoint *)malloc((N+2) * sizeof(PathPoint));
    int path_len = 0;
    while(1){
        path[path_len].x = cx;
        path[path_len].y = cy;
        path[path_len].direction = dir;
        path_len++;
        int next = find_next(cx, cy, dir);
        if(next == -1){
            break;
        }
        Mirror m = mirrors[next];
        if(dir == 'N'){
            cy = m.y;
            cx = m.x;
        }
        else if(dir == 'S'){
            cy = m.y;
            cx = m.x;
        }
        else if(dir == 'E'){
            cx = m.x;
            cy = m.y;
        }
        else if(dir == 'W'){
            cx = m.x;
            cy = m.y;
        }
        // Change direction based on mirror type
        if(m.type == '/'){
            if(dir == 'N') dir = 'E';
            else if(dir == 'E') dir = 'N';
            else if(dir == 'S') dir = 'W';
            else if(dir == 'W') dir = 'S';
        }
        else if(m.type == '\\'){
            if(dir == 'N') dir = 'W';
            else if(dir == 'W') dir = 'N';
            else if(dir == 'S') dir = 'E';
            else if(dir == 'E') dir = 'S';
        }
    }
    // Now, for each point in path, try placing a mirror and check if it can reach barn
    // To check path from mirror to barn, simulate from mirror to barn direction
    // For simplicity, we assume only placing mirror to redirect directly to barn
    // Count unique positions
    typedef struct {
        long long x;
        long long y;
    } Position;
    Position *possible = (Position *)malloc((path_len)*2 * sizeof(Position));
    int possible_cnt = 0;
    for(int i=0;i<path_len;i++){
        long long mx = path[i].x;
        long long my = path[i].y;
        // Check if Bessie is not on existing mirror
        int exists = 0;
        int left = 0, right = N-1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(mirrors[mid].x == mx && mirrors[mid].y == my){
                exists = 1;
                break;
            }
            if(mirrors[mid].y > my || (mirrors[mid].y == my && mirrors[mid].x > mx))
                right = mid -1;
            else
                left = mid +1;
        }
        if(exists) continue;
        // Try '/' mirror
        // Determine new direction
        char new_dir;
        if(path[i].direction == 'N') new_dir = 'E';
        else if(path[i].direction == 'S') new_dir = 'W';
        else if(path[i].direction == 'E') new_dir = 'N';
        else { // 'W'
            new_dir = 'S';
        }
        // Check if from (mx, my) in new_dir can reach barn
        // Simulate path
        long long bx = mx, by = my;
        char d = new_dir;
        int blocked = 0;
        while(1){
            if(d == 'N'){
                if(Bx != bx) {blocked=1; break;}
                if(by > By){
                    blocked=1; break;
                }
                // Check if any mirror between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_x[mid].x == bx && mirrors_x[mid].y > by && mirrors_x[mid].y < By){
                        found = 1;
                        break;
                    }
                    if(mirrors_x[mid].x < bx || (mirrors_x[mid].x == bx && mirrors_x[mid].y <= by))
                        l = mid +1;
                    else
                        r = mid -1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(Bx == bx && By >= by){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
            else if(d == 'S'){
                if(Bx != bx) {blocked=1; break;}
                if(by < By){
                    blocked=1; break;
                }
                // Check mirrors between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_x[mid].x == bx && mirrors_x[mid].y < by && mirrors_x[mid].y > By){
                        found = 1;
                        break;
                    }
                    if(mirrors_x[mid].x < bx || (mirrors_x[mid].x == bx && mirrors_x[mid].y >= by))
                        r = mid -1;
                    else
                        l = mid +1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(Bx == bx && By <= by){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
            else if(d == 'E'){
                if(By != by) {blocked=1; break;}
                if(bx > Bx){
                    blocked=1; break;
                }
                // Check mirrors between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_y[mid].y == by && mirrors_y[mid].x > bx && mirrors_y[mid].x < Bx){
                        found = 1;
                        break;
                    }
                    if(mirrors_y[mid].y < by || (mirrors_y[mid].y == by && mirrors_y[mid].x <= bx))
                        l = mid +1;
                    else
                        r = mid -1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(By == by && Bx >= bx){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
            else { // 'W'
                if(By != by) {blocked=1; break;}
                if(bx < Bx){
                    blocked=1; break;
                }
                // Check mirrors between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_y[mid].y == by && mirrors_y[mid].x < bx && mirrors_y[mid].x > Bx){
                        found = 1;
                        break;
                    }
                    if(mirrors_y[mid].y < by || (mirrors_y[mid].y == by && mirrors_y[mid].x >= bx))
                        r = mid -1;
                    else
                        l = mid +1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(By == by && Bx <= bx){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
        }
        // Try '\' mirror
        // Determine new direction
        if(path[i].direction == 'N') new_dir = 'W';
        else if(path[i].direction == 'S') new_dir = 'E';
        else if(path[i].direction == 'E') new_dir = 'S';
        else { // 'W'
            new_dir = 'N';
        }
        // Check if from (mx, my) in new_dir can reach barn
        bx = mx;
        by = my;
        d = new_dir;
        blocked = 0;
        while(1){
            if(d == 'N'){
                if(Bx != bx) {blocked=1; break;}
                if(by > By){
                    blocked=1; break;
                }
                // Check if any mirror between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_x[mid].x == bx && mirrors_x[mid].y > by && mirrors_x[mid].y < By){
                        found = 1;
                        break;
                    }
                    if(mirrors_x[mid].x < bx || (mirrors_x[mid].x == bx && mirrors_x[mid].y <= by))
                        l = mid +1;
                    else
                        r = mid -1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(Bx == bx && By >= by){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
            else if(d == 'S'){
                if(Bx != bx) {blocked=1; break;}
                if(by < By){
                    blocked=1; break;
                }
                // Check mirrors between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_x[mid].x == bx && mirrors_x[mid].y < by && mirrors_x[mid].y > By){
                        found = 1;
                        break;
                    }
                    if(mirrors_x[mid].x < bx || (mirrors_x[mid].x == bx && mirrors_x[mid].y >= by))
                        r = mid -1;
                    else
                        l = mid +1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(Bx == bx && By <= by){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
            else if(d == 'E'){
                if(By != by) {blocked=1; break;}
                if(bx > Bx){
                    blocked=1; break;
                }
                // Check mirrors between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_y[mid].y == by && mirrors_y[mid].x > bx && mirrors_y[mid].x < Bx){
                        found = 1;
                        break;
                    }
                    if(mirrors_y[mid].y < by || (mirrors_y[mid].y == by && mirrors_y[mid].x <= bx))
                        l = mid +1;
                    else
                        r = mid -1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(By == by && Bx >= bx){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
            else { // 'W'
                if(By != by) {blocked=1; break;}
                if(bx < Bx){
                    blocked=1; break;
                }
                // Check mirrors between (bx, by) and (Bx, By)
                int l = 0, r = N-1, found = 0;
                while(l <= r){
                    int mid = l + (r - l)/2;
                    if(mirrors_y[mid].y == by && mirrors_y[mid].x < bx && mirrors_y[mid].x > Bx){
                        found = 1;
                        break;
                    }
                    if(mirrors_y[mid].y < by || (mirrors_y[mid].y == by && mirrors_y[mid].x >= bx))
                        r = mid -1;
                    else
                        l = mid +1;
                }
                if(found) {blocked=1; break;}
                else {
                    if(By == by && Bx <= bx){
                        possible[possible_cnt].x = mx;
                        possible[possible_cnt].y = my;
                        possible_cnt++;
                    }
                    break;
                }
            }
        }
    }
    // Now, count unique positions
    // Sort possible positions
    qsort(possible, possible_cnt, sizeof(Position), cmp_x);
    // Remove duplicates
    int unique = 0;
    for(int i=0;i<possible_cnt;i++){
        if(i ==0 || possible[i].x != possible[i-1].x || possible[i].y != possible[i-1].y){
            unique++;
        }
    }
    printf("%d\n", unique);
    // Free memory
    free(mirrors);
    free(mirrors_x);
    free(mirrors_y);
    free(path);
    free(possible);
    return 0;
}