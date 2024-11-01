#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 62500
#define MAX_SETS 7000

int main(){
    char sequence[MAX_POINTS];
    int len =0;
    int c;
    while((c = getchar()) != EOF){
        if(c == 'E') break;
        if(c == 'W' || c == 'L'){
            if(len < MAX_POINTS){
                sequence[len++] = c;
            }
        }
    }
    // Process 11-point system
    int set11a[MAX_SETS], set11b[MAX_SETS];
    int set11count =0;
    int score1a =0, score1b=0;
    for(int i=0;i<len;i++){
        if(sequence[i] == 'W') score1a++;
        else score1b++;
        if( ( (score1a >=11 || score1b >=11) && abs(score1a - score1b) >=2 )){
            set11a[set11count] = score1a;
            set11b[set11count] = score1b;
            set11count++;
            score1a =0;
            score1b =0;
        }
    }
    if(score1a >0 || score1b >0){
        set11a[set11count] = score1a;
        set11b[set11count] = score1b;
        set11count++;
    }
    // Process 21-point system
    int set21a[MAX_SETS], set21b[MAX_SETS];
    int set21count =0;
    int score2a =0, score2b=0;
    for(int i=0;i<len;i++){
        if(sequence[i] == 'W') score2a++;
        else score2b++;
        if( ( (score2a >=21 || score2b >=21) && abs(score2a - score2b) >=2 )){
            set21a[set21count] = score2a;
            set21b[set21count] = score2b;
            set21count++;
            score2a =0;
            score2b =0;
        }
    }
    if(score2a >0 || score2b >0){
        set21a[set21count] = score2a;
        set21b[set21count] = score2b;
        set21count++;
    }
    // Output 11-point sets
    for(int i=0;i<set11count;i++){
        printf("%d:%d\n", set11a[i], set11b[i]);
    }
    // Print blank line
    if(set11count >0 && set21count >0){
        printf("\n");
    }
    else if(set11count >0 && set21count ==0){
        printf("\n");
    }
    // Output 21-point sets
    for(int i=0;i<set21count;i++){
        printf("%d:%d\n", set21a[i], set21b[i]);
    }
    return 0;
}