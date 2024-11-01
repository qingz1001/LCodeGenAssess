#include <stdio.h>
#include <string.h>

int main(){
    char s[16];
    scanf("%s", s);
    int n = strlen(s);
    int width = 4*(n-1)+5;
    char output[5][65];
    for(int i=0;i<5;i++) {
        for(int j=0;j<width;j++) output[i][j]='.';
        output[i][width] = '\0';
    }
    for(int i=0;i<n;i++){
        int start = i*4;
        char frame[5][5];
        // Decide frame type
        int isWendy = ((i+1)%3)==0;
        // Initialize frame
        for(int r=0;r<5;r++) {
            for(int c=0;c<5;c++) {
                frame[r][c]='.';
            }
        }
        if(isWendy){
            frame[0][2]='*';
            frame[1][1]='*'; frame[1][3]='*';
            frame[2][0]='*'; frame[2][2]=s[i]; frame[2][4]='*';
            frame[3][1]='*'; frame[3][3]='*';
            frame[4][2]='*';
        }
        else{
            frame[0][2]='#';
            frame[1][1]='#'; frame[1][3]='#';
            frame[2][0]='#'; frame[2][2]=s[i]; frame[2][4]='#';
            frame[3][1]='#'; frame[3][3]='#';
            frame[4][2]='#';
        }
        // Overlay frame onto output
        for(int r=0;r<5;r++) {
            for(int c=0;c<5;c++) {
                if(frame[r][c] != '.'){
                    // If Wendy, it overwrites
                    if(isWendy){
                        output[r][start+c] = frame[r][c];
                    }
                    else{
                        if(output[r][start+c] != '*') output[r][start+c] = frame[r][c];
                    }
                }
            }
        }
    }
    for(int i=0;i<5;i++) printf("%s\n", output[i]);
    return 0;
}