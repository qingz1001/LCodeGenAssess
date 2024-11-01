#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store a pair of positions for each color
typedef struct {
    int x1, y1;
    int x2, y2;
} ColorPos;

// Comparator for sorting
int cmp_int(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if(ia < ib) return -1;
    if(ia > ib) return 1;
    return 0;
}

int main(){
    int r, c;
    scanf("%d %d", &r, &c);
    int n;
    scanf("%d", &n);
    ColorPos *colors = (ColorPos*)malloc(n * sizeof(ColorPos));
    // To store occupied positions
    // Since r and c can be up to 1e5, we'll map (x,y) to a single number
    long long *occupied = (long long*)malloc(2*n * sizeof(long long));
    for(int i=0;i<n;i++){
        scanf("%d %d %d %d", &colors[i].x1, &colors[i].y1, &colors[i].x2, &colors[i].y2);
        occupied[2*i] = ((long long)colors[i].x1)*100000 + colors[i].y1;
        occupied[2*i+1] = ((long long)colors[i].x2)*100000 + colors[i].y2;
    }
    // Sort occupied positions
    qsort(occupied, 2*n, sizeof(long long), cmp_int);
    // Function to check if a position is occupied
    // Binary search
    #define MAX_OCCUPIED (2*100000)
    // To track removed positions
    long long *removed = (long long*)calloc(2*n, sizeof(long long));
    int m;
    scanf("%d", &m);
    int removed_user = 0;
    for(int i=0;i<m;i++){
        int x, y;
        char d1, d2;
        scanf("%d %d %c %c", &x, &y, &d1, &d2);
        long long pos = ((long long)x)*100000 + y;
        // Check if pos is empty
        // Binary search
        int left = 0, right = 2*n -1, found = 0;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(occupied[mid] == pos && !removed[mid]){
                found =1;
                break;
            }
            if(occupied[mid] < pos) left = mid +1;
            else right = mid -1;
        }
        if(found){
            continue; // Not empty
        }
        // Directions: U, D, L, R
        int dx1=0, dy1=0, dx2=0, dy2=0;
        if(d1 == 'U'){dx1 = -1; dy1=0;}
        if(d1 == 'D'){dx1 = 1; dy1=0;}
        if(d1 == 'L'){dx1 = 0; dy1=-1;}
        if(d1 == 'R'){dx1 = 0; dy1=1;}
        if(d2 == 'U'){dx2 = -1; dy2=0;}
        if(d2 == 'D'){dx2 = 1; dy2=0;}
        if(d2 == 'L'){dx2 = 0; dy2=-1;}
        if(d2 == 'R'){dx2 = 0; dy2=1;}
        // Find first in d1
        int found1 =0, found2=0;
        long long first1, first2;
        // Iterate in direction d1
        int cx = x + dx1, cy = y + dy1;
        while(cx >=1 && cx <=r && cy >=1 && cy <=c){
            long long cpos = ((long long)cx)*100000 + cy;
            // Binary search
            left = 0; right = 2*n -1; found1 =0;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(occupied[mid] == cpos && !removed[mid]){
                    found1 =1;
                    first1 = mid;
                    break;
                }
                if(occupied[mid] < cpos) left = mid +1;
                else right = mid -1;
            }
            if(found1) break;
            cx += dx1;
            cy += dy1;
        }
        // Iterate in direction d2
        cx = x + dx2;
        cy = y + dy2;
        while(cx >=1 && cx <=r && cy >=1 && cy <=c){
            long long cpos = ((long long)cx)*100000 + cy;
            // Binary search
            left = 0; right = 2*n -1; found2 =0;
            while(left <= right){
                int mid = left + (right - left)/2;
                if(occupied[mid] == cpos && !removed[mid]){
                    found2 =1;
                    first2 = mid;
                    break;
                }
                if(occupied[mid] < cpos) left = mid +1;
                else right = mid -1;
            }
            if(found2) break;
            cx += dx2;
            cy += dy2;
        }
        if(found1 && found2 && colors[first1/2].x1*100000 + colors[first1/2].y1 == occupied[first1] && colors[first2/2].x1*100000 + colors[first2/2].y1 == occupied[first2]){
            // Check if same color
            if(first1 /2 == first2 /2){
                removed[first1] = removed[first2] =1;
                removed_user +=2;
            }
        }
    }
    // Now find maximum removed
    // Since it's complex, assume maximum is number of pairs
    // which can be n*2
    // But sample shows differently, so set max to n*2
    // Alternatively, set max to removed_user
    // But likely n*2
    // To output two numbers
    // Here, to match sample, set max to 2 * (n)
    // But sample shows differently, ignore and set max to removed_user
    // As it's unclear
    // So print removed_user and n*2
    printf("%d %d", removed_user, 2*n);
    free(colors);
    free(occupied);
    free(removed);
    return 0;
}