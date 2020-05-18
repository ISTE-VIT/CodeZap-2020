#include <bits/stdc++.h>
using namespace std;
int to[20000007][2];
int cnt[20000007];
int SZ=0,LIM=11;
void insert(int r,int x)
{
    for(int i=LIM-1;i>=0;--i)
    {
        bool c=x&(1<<i);
        ++cnt[r];
        if(!to[r][c])
            to[r][c]=++SZ;
        r=to[r][c];
    }
    ++cnt[r];
}
void erase(int r,int x)
{
    for(int i=LIM-1;i>=0;--i)
    {
        bool c=x&(1<<i);
        --cnt[r];
        r=to[r][c];
    }
    --cnt[r];
}
int maxXor(int r,int x)
{
    int ret=0;
    for(int i=LIM-1;i>=0;--i)
    {
        bool c=x&(1<<i);
        if(to[r][1-c] && cnt[to[r][1-c]])
            ret+=(1<<i),
            r=to[r][1-c];
        else if(to[r][c] && cnt[to[r][c]])
            r=to[r][c];
        else
            assert(false);
    }
    return ret;
}
const int MAXN=5e4+6,LN=ceil(log2(MAXN)),mod=1e3+9;
vector<int> g[MAXN];
int dep[MAXN],pa[LN][MAXN],st[MAXN],en[MAXN],a[MAXN],pool=-1;
char op[11];
void dfs(int u,int p)
{
    st[u]=++pool;
    dep[u]=dep[p]+1;
    pa[0][u]=p;
    for(auto v:g[u])
        if(v!=p)
            dfs(v,u);
    en[u]=pool;
}
int lca(int u,int v)
{
    if(dep[u]<dep[v])
        swap(u,v);
    int d=dep[u]-dep[v];
    for(int i=LN-1;i>=0;--i)
        if(d&(1<<i))
            u=pa[i][u];
    if(u==v)
        return u;
    for(int i=LN-1;i>=0;--i)
        if(pa[i][u]!=pa[i][v])
            u=pa[i][u],
            v=pa[i][v];
    return pa[0][u];
}
set<int,bool(*)(int,int)> *active[4*MAXN];
int query(int u,int l,int r,int x,int y,int v)
{
    if(x>r || y<l)
        return 0;
    if(x<=l && r<=y)
        return maxXor(u,v);
    return max(query(2*u+1,l,(l+r)/2,x,y,v),query(2*u+2,(l+r)/2+1,r,x,y,v));
}
void update(int u,int l,int r,int x,int add,int rem)
{
    if(rem!=-1)
        erase(u,rem);
    insert(u,add);
    if(l==r)
        return;
    if(x<=(l+r)/2)
        update(2*u+1,l,(l+r)/2,x,add,rem);
    else
        update(2*u+2,(l+r)/2+1,r,x,add,rem);
}
void updateNode(int u,int l,int r,int x,int y,bool insert,int d)
{
    if(x>r || y<l)
        return;
    if(x<=l && r<=y)
    {
        if(insert)
            active[u]->insert(d);
        else
            active[u]->erase(d);
        return;
    }
    updateNode(2*u+1,l,(l+r)/2,x,y,insert,d);
    updateNode(2*u+2,(l+r)/2+1,r,x,y,insert,d);
}
int getNext(int u,int l,int r,int x)
{
    int ans=0;
    if(!active[u]->empty())
        ans=*active[u]->begin();
    if(l==r)
        return ans;
    if(x<=(l+r)/2)
        ans=min(ans,getNext(2*u+1,l,(l+r)/2,x),[](int u,int v){return dep[u]>dep[v];});
    else
        ans=min(ans,getNext(2*u+2,(l+r)/2+1,r,x),[](int u,int v){return dep[u]>dep[v];});
    return ans;
}
void init(int n)
{
    dfs(1,0);
    for(int j=1;j<LN;++j)
        for(int i=1;i<=n;++i)
            pa[j][i]=pa[j-1][pa[j-1][i]];
    for(int i=0;i<4*MAXN;++i)
        active[i]=new set<int,bool (*)(int,int)>([](int u,int v){return dep[u]>dep[v];});
    SZ=4*MAXN;
    for(int i=1;i<=n;++i)
    {
        update(0,0,n-1,st[i],a[i],-1);
        if(a[i]>1)
            updateNode(0,0,n-1,st[i]+1,en[i],1,i);
    }
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=1;i<n;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    init(n);
    while(q--)
    {
        int u,v,w,k;
        scanf("%s",op);
        if(!strcmp(op,"Divide"))
        {
            scanf("%d%d%d",&u,&v,&w);
            //corner case
            if(w==1)
                continue;
            int l=lca(u,v);
            if(a[u]==1)
                u=getNext(0,0,n-1,st[u]);
            if(a[v]==1)
                v=getNext(0,0,n-1,st[v]);
            while(dep[u]>=dep[l])
            {
                update(0,0,n-1,st[u],(a[u]+w-1)/w,a[u]);
                a[u]=(a[u]+w-1)/w;
                if(a[u]==1)
                    updateNode(0,0,n-1,st[u]+1,en[u],0,u);
                u=getNext(0,0,n-1,st[u]);
            }
            while(dep[v]>dep[l])
            {
                update(0,0,n-1,st[v],(a[v]+w-1)/w,a[v]);
                a[v]=(a[v]+w-1)/w;
                if(a[v]==1)
                    updateNode(0,0,n-1,st[v]+1,en[v],0,v);
                v=getNext(0,0,n-1,st[v]);
            }
        }
        else if(!strcmp(op,"Multiply"))
        {
            scanf("%d%d",&k,&w);
            if(w==1)
                continue;
            if(a[k]==1 && w>1)
                updateNode(0,0,n-1,st[k]+1,en[k],1,k);
            else if(a[k]>1 && ((long long)a[k]*w%mod)==1) //make case for this
                updateNode(0,0,n-1,st[k]+1,en[k],-1,k);
            update(0,0,n-1,st[k],((long long)a[k]*w)%mod,a[k]);

            a[k]=((long long)a[k]*w)%mod;
        }
        else if(!strcmp(op,"Query"))
        {
            scanf("%d%d",&k,&w);
            printf("%d\n",query(0,0,n-1,st[k],en[k],w));
        }
    }
}
