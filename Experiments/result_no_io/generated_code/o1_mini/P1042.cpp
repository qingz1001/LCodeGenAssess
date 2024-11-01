#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAMES 70000
#define MAX_LINE 30

typedef struct {
    int w;
    int l;
} Game;

int main(){
    Game games11[MAX_GAMES];
    Game games21[MAX_GAMES];
    int count11 = 0, count21 = 0;
    int cw11 = 0, cl11 = 0;
    int cw21 = 0, cl21 = 0;
    char line[MAX_LINE];
    int ended = 0;

    while(fgets(line, sizeof(line), stdin)){
        for(int i=0; line[i] != '\0' && !ended; i++){
            char c = line[i];
            if(c == 'E'){
                ended = 1;
                break;
            }
            if(c != 'W' && c != 'L') continue;
            
            // Update for 11
            if(c == 'W') cw11++;
            else cl11++;
            // Check if game ended for 11
            if( (cw11 >=11 || cl11 >=11) && abs(cw11 - cl11) >=2 ){
                games11[count11].w = cw11;
                games11[count11].l = cl11;
                count11++;
                cw11 = 0;
                cl11 = 0;
            }
            
            // Update for 21
            if(c == 'W') cw21++;
            else cl21++;
            // Check if game ended for 21
            if( (cw21 >=21 || cl21 >=21) && abs(cw21 - cl21) >=2 ){
                games21[count21].w = cw21;
                games21[count21].l = cl21;
                count21++;
                cw21 = 0;
                cl21 = 0;
            }
        }
    }

    // Add the ongoing game for 11
    games11[count11].w = cw11;
    games11[count11].l = cl11;
    count11++;

    // Add the ongoing game for 21
    games21[count21].w = cw21;
    games21[count21].l = cl21;
    count21++;

    // Print 11 scoring
    for(int i=0; i < count11; i++){
        printf("%d-%d\n", games11[i].w, games11[i].l);
    }

    printf("\n");

    // Print 21 scoring
    for(int i=0; i < count21; i++){
        printf("%d-%d\n", games21[i].w, games21[i].l);
    }

    return 0;
}