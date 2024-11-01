#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_STATES 16

int main(){
    int n, c;
    scanf("%d", &n);
    scanf("%d", &c);
    
    int on_lamps[MAX_N+1], on_cnt=0;
    int lamp;
    while(scanf("%d", &lamp)==1 && lamp != -1){
        on_lamps[on_cnt++] = lamp;
    }
    
    int off_lamps[MAX_N+1], off_cnt=0;
    while(scanf("%d", &lamp)==1 && lamp != -1){
        off_lamps[off_cnt++] = lamp;
    }
    
    char states[MAX_STATES][MAX_N+1];
    int state_count = 0;
    
    for(int combo=0; combo<16; combo++){
        // Count number of buttons pressed
        int buttons = 0;
        int tmp = combo;
        for(int b=0; b<4; b++) {
            if(tmp & 1) buttons++;
            tmp >>=1;
        }
        if(buttons > c) continue;
        if((c - buttons) %2 !=0) continue;
        
        // Determine lamp states
        char lamp_state[MAX_N+1];
        for(int i=1;i<=n;i++) lamp_state[i-1] = '1';
        lamp_state[n] = '\0';
        
        for(int i=1;i<=n;i++){
            int toggles = 0;
            // Button 1
            if(combo & 1) toggles++;
            // Button 2
            if((combo & 2) && (i%2==1)) toggles++;
            // Button 3
            if((combo & 4) && (i%2==0)) toggles++;
            // Button 4
            if((combo & 8) && ((i-1)%3==0)) toggles++;
            if(toggles %2){
                lamp_state[i-1] = (lamp_state[i-1] == '1') ? '0' : '1';
            }
        }
        
        // Check constraints
        int valid = 1;
        for(int j=0; j<on_cnt && valid; j++){
            if(lamp_state[on_lamps[j]-1] != '1') { valid = 0; }
        }
        for(int j=0; j<off_cnt && valid; j++){
            if(lamp_state[off_lamps[j]-1] != '0') { valid = 0; }
        }
        if(valid){
            // Check uniqueness
            int unique = 1;
            for(int s=0; s<state_count && unique; s++){
                if(strcmp(states[s], lamp_state)==0){
                    unique = 0;
                }
            }
            if(unique){
                strcpy(states[state_count++], lamp_state);
            }
        }
    }
    
    if(state_count ==0){
        printf("IMPOSSIBLE\n");
    }
    else{
        // Sort the states
        for(int i=0;i<state_count-1;i++){
            for(int j=i+1; j<state_count; j++){
                if(strcmp(states[i], states[j]) >0){
                    char temp[MAX_N+1];
                    strcpy(temp, states[i]);
                    strcpy(states[i], states[j]);
                    strcpy(states[j], temp);
                }
            }
        }
        // Print the states
        for(int i=0;i<state_count;i++) printf("%s\n", states[i]);
    }
}