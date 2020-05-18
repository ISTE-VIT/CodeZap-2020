#include<bits/stdc++.h>
    using namespace std;
    //typedef long long ll;

    int n;
    int arr[2005];
    int dp[2005][2005];

    int profit(int be, int en)
    {
        if(be > en)
            return 0;
        if(dp[be][en] != -1)
            return(dp[be][en]);
        int day = n - (en - be + 1) + 1;
        return(dp[be][en] = max(profit(be + 1, en) + day * arr[be], profit(be, en - 1) + day * arr[en]));
    }

    int main()
    {
        cin>>n;

        for(int i = 0; i < n; i++)
        {
            cin>>arr[i];
        }
        memset(dp, -1, sizeof(dp));
        cout<<profit(0, n - 1)<<"\n";

    }
