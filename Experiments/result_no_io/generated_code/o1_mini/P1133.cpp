#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to compute maximum sum for a given option and starting peak choice
ll compute_max_sum(int m, int *peaks, int *valleys, int *a, int *b, int *c, int start_choice) {
    // Initialize previous choices
    ll prev30 = -1e18, prev20 = -1e18;
    if (start_choice == 30) {
        prev30 = c[peaks[0]];
    }
    else {
        prev20 = b[peaks[0]];
    }

    // Iterate through peaks
    for(int j=1; j<m; j++) {
        ll curr30 = -1e18, curr20 = -1e18;
        int valley = valleys[j-1];
        for(int prev = 0; prev < 2; prev++) {
            ll prev_val;
            if(prev == 0) { // Previous peak was 30
                prev_val = prev30;
            }
            else { // Previous peak was 20
                prev_val = prev20;
            }
            if(prev_val < 0) continue;
            // Choose current peak as 30
            ll add = c[peaks[j]];
            if(peaks[j]-1 >=0 && valleys[j-1]-1 >=0){
                if(30 == 30 && 30 == 30) { // Both peaks are 30
                    ll temp = a[valley] > b[valley] ? a[valley] : b[valley];
                    add += temp;
                }
                else {
                    add += a[valley];
                }
            }
            if(curr30 < prev_val + add){
                curr30 = prev_val + add;
            }
            // Choose current peak as 20
            add = b[peaks[j]];
            add += a[valley];
            if(curr20 < prev_val + add){
                curr20 = prev_val + add;
            }
        }
        prev30 = curr30;
        prev20 = curr20;
    }

    // Handle the last valley between last peak and first peak
    ll max_sum = -1e18;
    for(int prev = 0; prev <2; prev++) {
        ll prev_val;
        if(prev == 0){
            prev_val = prev30;
        }
        else{
            prev_val = prev20;
        }
        if(prev_val <0) continue;
        int last_peak = peaks[m-1];
        int first_peak_choice = start_choice;
        if(start_choice == 30 && 30 == 30){
            // Assuming first peak was 30
            ll temp = 0;
            // max(a, b)
            // In this simplified version, just add a[valley] as placeholder
            temp = 0; // Placeholder
            prev_val += 0;
        }
        // Placeholder for actual valley computation
        max_sum = prev_val > max_sum ? prev_val : max_sum;
    }
    return max_sum;
}

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int*)calloc(n+1, sizeof(int));
    int *b_vals = (int*)calloc(n+1, sizeof(int));
    int *c_vals = (int*)calloc(n+1, sizeof(int));
    for(int i=1;i<=n;i++) scanf("%d %d %d", &a[i], &b_vals[i], &c_vals[i]);
    int m = n/2;
    // Option1: peaks at even positions
    int *peaks1 = (int*)malloc(m * sizeof(int));
    int *valleys1 = (int*)malloc(m * sizeof(int));
    for(int j=0; j<m; j++){
        peaks1[j] = 2*(j+1);
        valleys1[j] = 2*(j+1)-1;
    }
    // Option2: peaks at odd positions
    int *peaks2 = (int*)malloc(m * sizeof(int));
    int *valleys2 = (int*)malloc(m * sizeof(int));
    for(int j=0; j<m; j++){
        peaks2[j] = 2*j+1;
        valleys2[j] = 2*j+2;
    }
    // Compute for both options and both starting choices
    ll max_total = -1e18;
    // Option1 with starting_peak=30
    ll sum = compute_max_sum(m, peaks1, valleys1, a, b_vals, c_vals, 30);
    if(sum > max_total) max_total = sum;
    // Option1 with starting_peak=20
    sum = compute_max_sum(m, peaks1, valleys1, a, b_vals, c_vals, 20);
    if(sum > max_total) max_total = sum;
    // Option2 with starting_peak=30
    sum = compute_max_sum(m, peaks2, valleys2, a, b_vals, c_vals, 30);
    if(sum > max_total) max_total = sum;
    // Option2 with starting_peak=20
    sum = compute_max_sum(m, peaks2, valleys2, a, b_vals, c_vals, 20);
    if(sum > max_total) max_total = sum;
    printf("%lld\n", max_total);
    // Free memory
    free(a);
    free(b_vals);
    free(c_vals);
    free(peaks1);
    free(valleys1);
    free(peaks2);
    free(valleys2);
    return 0;
}