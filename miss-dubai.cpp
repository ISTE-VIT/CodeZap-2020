#include<bits/stdc++.h>
using namespace std;

const int N = 105;
const int mod = 1000000007;
char str[N];
int cnt[1030];
int pre[10][10];
int n;
int dp[N][2][2][1030][2];


int rec(int p,int f1,int f2,int mask,int f)
{
    if(p==n) return f*cnt[mask];
    int &ret=dp[p][f1][f2][mask][f];
    if(ret!=-1) return ret;
    ret=0;
    int nw=str[p]-'0';
    for(int i=0; i<=9; i++)
    {
        for(int j=0; j<=9; j++)
        {
            if(f1==0 && i>nw) continue;
            if(f2==0 && j>i) continue;
            int tmask=mask;
            if(mask==1023)
            {
                ret+=rec(p+1,f1|(i<nw),f2|(j<i),mask,f|(j>0));
                ret%=mod;
                continue;
            }
            if(f2==0)
            {
                if(p==n-1) ret+=rec(p+1,f1|(1<nw),f2|(i<nw),mask|pre[j][i],f|(j>0));
                else if(i==j)
                {
                    if(f || i!=0) ret+=rec(p+1,f1|(i<nw),f2|(j<i),mask|(1<<i),f|(j>0));
                    else ret+=rec(p+1,f1|(i<nw),f2|(j<i),mask,f|(j>0));
                }
                else if(i-j>1) ret+=rec(p+1,f1|(i<nw),f2|(j<i),1023,f|(j>0));
                else if(i-j==1)
                {
                    if(f || j!=0) ret+=rec(p+1,f1|(i<nw),f2|(j<i),mask|pre[j][i],f|(j>0));
                    else ret+=rec(p+1,f1|(i<nw),f2|(j<i),mask|(1<<i),f|(j>0));
                }
                ret%=mod;
            }
            else
            {
                if(i>=j) ret+=rec(p+1,f1|(i<nw),f2|(j<i),1023,f|(j>0));
                else if(p==n-1) ret+=rec(p+1,f1|(i<nw),f2|(j<i),mask|pre[j][9]|pre[0][i],f|(j>0));
                else if(i==0 && j==9) ret+=rec(p+1,f1|(i<nw),f2|(j<i),mask|pre[j][9]|pre[0][i],f|(j>0));
                else ret+=rec(p+1,f1|(i<nw),f2|(j<i),1023,f|(j>0));
                ret%=mod;
            }
        }
    }
    return ret;
}


int main()
{
    int t;
    scanf("%d",&t);
    while(t>0){
        t=t-1;
    scanf("%s",str);
    n=strlen(str);
    for(int i=0; i<1024; i++) cnt[i]=__builtin_popcount(i);
    for(int i=0; i<10; i++)
    {
        for(int j=i; j<10; j++)
        {
            pre[i][j]=0;
            for(int k=i; k<=j; k++) pre[i][j]|=(1<<k);
        }
    }
    memset(dp,-1,sizeof dp);
    printf("%d\n",rec(0,0,0,0,0));
    }
}
