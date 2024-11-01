#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int x1, y1, x2, y2;
    int xmin, xmax, ymin, ymax;
} Line;

int overlap(int a_min, int a_max, int b_min, int b_max){
    if(a_max <= b_min || b_max <= a_min) return 0;
    return 1;
}

int can_move(Line *lines, int n, int move_idx, int dir, int removed[]) {
    Line l = lines[move_idx];
    for(int i=0;i<n;i++) {
        if(i == move_idx || removed[i]) continue;
        Line o = lines[i];
        int overlap_flag = 0;
        if(dir == 0 || dir == 2){
            overlap_flag = overlap(l.ymin, l.ymax, o.ymin, o.ymax);
        }
        else{
            overlap_flag = overlap(l.xmin, l.xmax, o.xmin, o.xmax);
        }
        if(!overlap_flag) continue;
        if(dir == 0){
            if(o.xmax < l.xmin)
                return 0;
        }
        else if(dir ==1){
            if(o.ymin > l.ymax)
                return 0;
        }
        else if(dir ==2){
            if(o.xmin > l.xmax)
                return 0;
        }
        else if(dir ==3){
            if(o.ymax < l.ymin)
                return 0;
        }
    }
    return 1;
}

int main(){
    int n;
    scanf("%d", &n);
    Line lines[n];
    for(int i=0;i<n;i++){
        scanf("%d %d %d %d", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2);
        lines[i].id = i+1;
        lines[i].xmin = lines[i].x1 < lines[i].x2 ? lines[i].x1 : lines[i].x2;
        lines[i].xmax = lines[i].x1 > lines[i].x2 ? lines[i].x1 : lines[i].x2;
        lines[i].ymin = lines[i].y1 < lines[i].y2 ? lines[i].y1 : lines[i].y2;
        lines[i].ymax = lines[i].y1 > lines[i].y2 ? lines[i].y1 : lines[i].y2;
    }
    int given_moves[n][2];
    for(int i=0;i<n;i++) {
        scanf("%d %d", &given_moves[i][0], &given_moves[i][1]);
    }
    // Step 1: Find first illegal move
    int removed1[n];
    for(int i=0;i<n;i++) removed1[i]=0;
    int illegal = -1;
    for(int i=0;i<n;i++){
        int p = given_moves[i][0]-1;
        int q = given_moves[i][1];
        if(can_move(lines, n, p, q, removed1)==0){
            illegal = i+1;
            break;
        }
        removed1[p]=1;
    }
    printf("%d\n", illegal);
    // Step 2: Find a valid move sequence
    int removed2[n];
    for(int i=0;i<n;i++) removed2[i]=0;
    int move_seq[n][2];
    int cnt=0;
    while(cnt<n){
        int found = 0;
        for(int i=0;i<n;i++){
            if(!removed2[i] && can_move(lines, n, i, 0, removed2)){
                move_seq[cnt][0] = lines[i].id;
                move_seq[cnt][1] =0;
                removed2[i]=1;
                cnt++;
                found =1;
                break;
            }
            if(!removed2[i] && can_move(lines, n, i,1, removed2)){
                move_seq[cnt][0] = lines[i].id;
                move_seq[cnt][1] =1;
                removed2[i]=1;
                cnt++;
                found =1;
                break;
            }
            if(!removed2[i] && can_move(lines, n, i,2, removed2)){
                move_seq[cnt][0] = lines[i].id;
                move_seq[cnt][1] =2;
                removed2[i]=1;
                cnt++;
                found =1;
                break;
            }
            if(!removed2[i] && can_move(lines, n, i,3, removed2)){
                move_seq[cnt][0] = lines[i].id;
                move_seq[cnt][1] =3;
                removed2[i]=1;
                cnt++;
                found =1;
                break;
            }
        }
        if(!found){
            // Assign any remaining moves with direction 0
            for(int i=0;i<n;i++){
                if(!removed2[i]){
                    move_seq[cnt][0] = lines[i].id;
                    move_seq[cnt][1] =0;
                    removed2[i]=1;
                    cnt++;
                    break;
                }
            }
        }
    }
    for(int i=0;i<n;i++) printf("%d %d\n", move_seq[i][0], move_seq[i][1]);
    return 0;
}