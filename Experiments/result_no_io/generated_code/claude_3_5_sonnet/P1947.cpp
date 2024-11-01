extern int Seniorious(int);

int Chtholly(int n, int c) {
    int left = 1, right = n, mid;
    
    while (left <= right) {
        mid = left + (right - left) / 2;
        int result = Seniorious(mid);
        
        if (result == 0) {
            return mid;
        } else if (result == 1) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}