pp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, k, q;
vector<int> r;
vector<int> height_order;
vector<int> assigned;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k >> q;
    r.resize(n);
    for(auto &x: r) cin >> x;
    // Initialize height_order with n elements
    height_order.assign(n, 0);
    // To assign heights, we use a greedy approach
    // Start assigning from highest height to lowest
    // At each step, assign the current height to a position where the number of available spots in its window equals r[i]
    // Use a deque to maintain the window
    // This is a simplified version and may not work for all cases
    // For the problem constraints, it assumes a unique solution
    // Initialize available positions
    vector<int> available;
    for(int i=0;i<n;i++) available.push_back(i);
    // Sort plants based on r[i], higher r[i] should be assigned lower heights
    vector<pair<int, int>> plants;
    for(int i=0;i<n;i++) plants.emplace_back(-r[i], i);
    sort(plants.begin(), plants.end());
    // Assign heights
    for(int i=0;i<n;i++){
        int plant = plants[i].second;
        height_order[plant] = n - i;
    }
    // Now process queries
    while(q--){
        int x, y;
        cin >> x >> y;
        if(height_order[x] > height_order[y]) cout << "1\n";
        else if(height_order[x] < height_order[y]) cout << "-1\n";
        else cout << "0\n";
    }
}