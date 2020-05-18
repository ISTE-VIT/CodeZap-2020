#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int infI=1e9+5;
const long long infL=1e16;
const int MOD=1e9+7;
const int MAX=2e5+5;

#define mp make_pair
#define in &
#define pb push_back
#define ii pair<int,int>
#define iii pair<ii,int>
#define ll long long
#define pll pair<ll,ll>
#define vvl vector<vector<ll> >
#define vi vector<int>
#define vvi vector<vector<int> >
#define vl vector<ll>
#define eb emplace_back
#define forn(i,a,b) for(ll i=a;i<b;i++)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#define popb pop_back()
#define se second
#define fi first
#define test(t) int t;cin>>t;while(t--)
#define debug(x) cerr<<"=>"<<#x<<" = "<<x<<endl

ll power(ll a,ll b){
    if(b==0){
        return 1;
    }
    if(b==1){
        return a;
    }
    ll temp=power(a,b/2);
    temp=(temp*temp)%MOD;
    if(b%2){
        temp=(temp*a)%MOD;
    }
    return temp;
}

//only use if mod is prime
ll mod_inv(ll a,ll mod){
    a%=mod;
    return power(a,mod-2);
}

void extended_gcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return;
    }
    ll x1,y1;
    extended_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-((a/b)*y1);
    return;
}

//TLE can also occur if vectors are not passed by reference
//priority_queue implements max heap by default

ll dp[1005][1005],a[1005];//dp[i][j] -> minimum number of hits to break j coconuts from first i,i+1,i+2.....n and last used coconut was the i'th one

ll get_cost(pll a,ll b){
    return (a.fi-a.se*b);
}

bool slope(pll a,pll b,pll c){
    ll val1 = (b.fi - a.fi)*(c.se - b.se);
    ll val2 = (c.fi - b.fi)*(b.se - a.se);
    return val1>=val2;
}

int main(){
    int zz;
    scanf("%d",&zz);
    while(zz--){
        int n,z;
        scanf("%d %d",&n,&z);
        forn(i,1,n+1){
            scanf("%lld",&a[i]);
            forn(j,1,z+1){
                dp[i][j] = infL;
            }
        }
        sort(a+1,a+n+1,greater<ll>());
        forn(i,1,n+1){
            dp[i][1] = a[i]*i;
        }
        forn(j,2,z+1){
            pll dq[n+1];
            int fptr = 1,bptr = 2;
            dq[1] = mp(dp[j-1][j-1],j-1);
            forn(i,j,n+1){
                pll part = mp(dp[i][j-1],i);
                while(bptr-fptr>=2 and get_cost(dq[bptr-1],a[i])>=get_cost(dq[bptr-2],a[i])){
                    --bptr;
                }
                dp[i][j] = get_cost(dq[bptr-1],a[i]) + i*a[i];
                // while(bptr-fptr>=1 and dp[dq[bptr-1].se][j-1] >= dp[i][j-1]){
                //     --bptr;
                // }
                while(bptr-fptr>=2 and slope(dq[bptr-2],dq[bptr-1],part)){
                    --bptr;
                }
                dq[bptr++] = part;
            }
        }
        ll ans = infL;
        forn(i,1,n+1){
            // cerr<<dp[i][z]<<" ";
            ans = min(ans,dp[i][z]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
