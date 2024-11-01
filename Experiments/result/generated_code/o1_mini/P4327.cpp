#include <stdio.h>
#include <string.h>

int main(){
    char s[16];
    scanf("%s", s);
    int N = strlen(s);
    int total_cols = 4 * N +1;
    char grid[5][61];
    int priority_grid[5][61];
    // Initialize grid with '.' and priority with -1
    for(int i=0;i<5;i++){
        for(int j=0;j<61;j++){
            grid[i][j] = '.';
            priority_grid[i][j] = -1;
        }
    }
    // Define frame patterns
    char P_pat[5][5+1] = {
        "..#..",
        ".#.#.",
        "#.X.#",
        ".#.#.",
        "..#.."
    };
    char W_pat[5][5+1] = {
        "..*..",
        ".*.*.",
        "*.X.*",
        ".*.*.",
        "..*.."
    };
    for(int idx=0; idx<N; idx++){
        int isW = ((idx+1) %3 ==0) ? 1 : 0;
        int frame_priority = isW ? 1 : 0;
        char (*current_pat)[6];
        if(isW){
            current_pat = W_pat;
        }
        else{
            current_pat = P_pat;
        }
        // Replace 'X' with the actual character
        char frame[5][5+1];
        for(int l=0;l<5;l++){
            for(int c=0;c<5;c++){
                if(current_pat[l][c] == 'X'){
                    frame[l][c] = s[idx];
                }
                else{
                    frame[l][c] = current_pat[l][c];
                }
            }
            frame[l][5] = '\0';
        }
        int start_col = 4 * idx;
        for(int l=0;l<5;l++){
            for(int c=0;c<5;c++){
                char ch = frame[l][c];
                if(ch != '.'){
                    int pos = start_col + c;
                    if(frame_priority >= priority_grid[l][pos]){
                        grid[l][pos] = ch;
                        priority_grid[l][pos] = frame_priority;
                    }
                }
            }
        }
    }
    // Print the grid
    for(int l=0;l<5;l++){
        for(int c=0;c<4*N +1;c++){
            printf("%c", grid[l][c]);
        }
        printf("\n");
    }
    return 0;
}