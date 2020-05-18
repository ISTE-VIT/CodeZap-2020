#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

ll solve(vector<vector<ll>>& marketing, vector<vector<ll>>& generosity, int k) {
    int m = marketing.size();
    int n = marketing[0].size();
    int t = generosity.size();

    // max visits per group
    int maxVisits = n * k;
    for(int i = 0; i < t; i++) {
        if(maxVisits < (int) generosity[i].size()) {
            // if this condition is true, no group of students can visit all rooms from the floor
            return -1;
        }
    }

    for(int i = 0; i < m; i++) {
        // sort by non-increasing marketing factor
        sort(marketing[i].begin(), marketing[i].end(), greater<ll>());
    }

    // sort all subsets for all masks
    vector<vector<ll>> genCombos(1 << t);
    for(int mask = 0; mask < 1 << t; mask++) {
        for(int i = 0; i < t; i++) {
            if(mask & (1 << i)) {
                genCombos[mask].insert(genCombos[mask].end(), generosity[i].begin(), generosity[i].end());
            }
        }
        if(genCombos[mask].size() > maxVisits) {
            // don't bother sorting, won't use anyway
            continue;
        }
        // sort in non increasing order
        sort(genCombos[mask].begin(), genCombos[mask].end(), greater<ll>());
    }

    // best[i][mask] stores the maximum registration group i can get from floors represented by mask
    vector<vector<ll>> best(m, vector<ll>(1 << t, -1));
    // compute best for all combinations
    for(int i = 0; i < m; i++) {
        for(int mask = 0; mask < 1 << t; mask++) {
            if(genCombos[mask].size() > maxVisits) {
                // this combination is not possible
                continue;
            }
            // assign k most marketing students and then the next k in non increasing order
            int p = 0, kk = k;
            best[i][mask] = 0;
            for(int j = 0; j < (int) genCombos[mask].size(); j++) {
                best[i][mask] += genCombos[mask][j] * marketing[i][p];
                if(--kk == 0) {
                    ++p;
                    kk = k;
                }
            }
        }
    }

    // compute the max registrations by bitmask dp
    vector<vector<ll>> dp(m, vector<ll>(1 << t, -1));
    dp[0] = best[0];
    for(int i = 1; i < m; i++) {
        for(int mask = 0;  mask < 1 << t; mask++) {
            // consider all state transitions from submask to mask
            for(int submask = mask;; submask = (submask - 1) & mask) {
                // illegal state transition check
                if(best[i][submask] == -1 || dp[i-1][submask ^ mask] == -1) {
                    if(submask == 0) {
                        break;
                    } else {
                        continue;
                    }
                }
                dp[i][mask] = max(dp[i][mask], dp[i-1][submask ^ mask] + best[i][submask]);
                if(submask == 0) {
                    break;
                }
            }
        }
    }

    return dp[m-1][(1 << t) - 1];
}

int main() {
    int tc;
    cin >> tc;
    while(tc--) {
        int m, n, t;
        cin >> m >> n >> t;
        vector<vector<ll>> marketing(m, vector<ll>(n)), generosity(t);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                cin >> marketing[i][j];
            }
        }
        for(int i = 0; i < t; i++) {
            int x;
            cin >> x;
            generosity[i].resize(x);
            for(int j = 0; j < x; j++) {
                cin >> generosity[i][j];
            }
        }
        int k;
        cin >> k;
        cout << solve(marketing, generosity, k) << '\n';
    }
    return 0;
}

