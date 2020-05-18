
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

// typedef  long long int ll;
// typedef long double   ld;
#define    int                      long long int
#define    f(i,j,n)                 for(int i = j; i <= n; i++)
#define    r(i,n,j)                 for(int i = n; i >= j; i--)
#define    mod                      1000000007
#define    speed                    ios_base::sync_with_stdio(false);
#define    upp                      cin.tie(NULL);
#define    pb                       push_back
#define    mp                       make_pair
#define    T                        int tt; cin >> tt; while(tt--)
#define    ff                       first
#define    ss                       second
#define    all(container)           container.begin() , container.end()
#define    sz(container)            (int)container.size()
#define    pii                      pair <int , int>
#define    pll                      pair <long long int , long long int>
#define    ppl                      pair <long long int , pll>              //pair of ll and pair ll
#define    sp(x)                    setprecision(x)



int32_t main()
{
    speed upp
    while(1)
    {
        int n;
        cin>>n;
        if(n==0)
            break;
        int a[n+1],j=1;
        f(i,1,n)
            cin>>a[i];
        vector<int>v;
        stack<int>q;
        f(i,1,n)
        {
            if(a[i]==j)
            {
                v.pb(j);
                j++;
                continue;
            }
            if(!q.empty() && q.top()==j)
            {
                q.pop();
                v.pb(j);
                j++;
                i--;
                continue;
            }
            q.push(a[i]);
        }
        while(!q.empty())
        {

            v.pb(q.top());
            q.pop();
        }
        int f=0;
        f(i,1,sz(v))
            if(v[i-1]!=i)
                f=1;
        if(f)
            cout<<"no\n";
        else
            cout<<"yes\n";
    }
}
