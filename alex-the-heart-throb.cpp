#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,cnt[10],cnt2[10],t[100];
int mo,m,pd[10],A[100],a[10],d[30][30][30][30][2],pre[30][30][30][30][2],u[10],tot,go[100];
int lim=5;
struct atom{
    int B[5],size;
}x[500];
int compare(int k1,int k2){
    return cnt[k1]>cnt[k2];
}
int check(){
    int x[11]; memset(x,0x00,sizeof x);
    int len=0,k1=0;
    for (int i=0;i<lim;i++)
        for (int j=1;j<=cnt2[i];j++)
            x[len]=a[i],len++,k1=(k1+a[i])%mo;
    if (k1) return 0;
    for (int i=1;i<(1<<len)-1;i++){
        int num=0;
        for (int j=0;j<len;j++) if (i&(1<<j)) num=(num+x[j])%mo;
        if (num==0) return 0;
    }
    return 1;
}
void get(int k1,int k2,int k3){
    if (k2&&k3&&check()){
        tot++; x[tot].size=k2;
        for (int i=0;i<lim;i++) x[tot].B[i]=cnt2[i];
    }
    if (k1==lim) return;
    for (int i=0;i<=cnt[k1]&&k2+i<=mo;i++){
        cnt2[k1]+=i; get(k1+1,k2+i,i); cnt2[k1]-=i;
    }
}
int compare1(atom k1,atom k2){
    return k1.size<k2.size;
}
int getpath(int k1,int k2){
    int aa=cnt2[0],b=cnt2[1],c=cnt2[2],dd=cnt2[3],e=cnt2[4];
    if (d[aa][b][c][dd][e]<k2) return 1;
    if (k1>tot) return 0;
    for (int now=0;now<=t[k1];now++){
        int flag=0; go[k1]=now;
        for (int i=0;i<lim;i++) if (u[i]<=cnt2[i]) flag=1;
        if (flag) break;
        if (getpath(k1+1,k2)) return 1;
        k2+=x[k1].size-1;
        for (int i=0;i<lim;i++) cnt2[i]+=x[k1].B[i];
    }
    cnt2[0]=aa; cnt2[1]=b; cnt2[2]=c; cnt2[3]=dd; cnt2[4]=e;
    return 0;
}
void solve(){
    memset(cnt,0x00,sizeof cnt);
    scanf("%lld%d%d",&n,&mo,&m); int Pre=0;
    for (;m;m--){
        int k1,k2,k3; long long k4; scanf("%d%d%d%lld",&k1,&k2,&k3,&k4);
        for (int i=1;i<=mo&&k4;i++){
            cnt[(k1-Pre+mo)%mo]++; Pre=k1; k1=(k1*k2+k3)%mo; k4--;
        }
        memset(pd,0x00,sizeof pd); int len=0; A[0]=k1; pd[k1]=1;
        while (1){
            A[len+1]=(A[len]*k2+k3)%mo;
            if (pd[A[len+1]]) break; len++;
            pd[A[len]]=1;
        }
        len++;
        long long num=k4/len;
        if (num==0){
            for (int i=0;i<k4;i++){
                cnt[(A[i]-Pre+mo)%mo]++; Pre=A[i];
            }
            continue;
        }
        for (int i=0;i<len;i++){
            cnt[(A[i]-Pre+mo)%mo]++; Pre=A[i];
        }
        for (int i=0;i<len;i++){
            cnt[(A[i]-Pre+mo)%mo]+=num-1; Pre=A[i];
        }
        for (int i=0;i<k4%len;i++){
            cnt[(A[i]-Pre+mo)%mo]++; Pre=A[i];
        }
    }
    cnt[(-Pre+mo)%mo]++;
    //for (int i=0;i<mo;i++) cout<<cnt[i]<<" "; cout<<endl;
    cnt[0]=0;
    long long ans=0;
    for (int i=0;i<mo;i++){
        int j=mo-i;
        if (j==i){
            ans+=cnt[i]/2; cnt[i]%=2;
        } else {
            long long k1=min(cnt[i],cnt[j]);
            ans+=k1; cnt[i]-=k1; cnt[j]-=k1;
        }
    }
    memset(a,0x00,sizeof a);
    for (int i=0;i<mo;i++) a[i]=i;
    sort(a,a+mo,compare);
    memcpy(cnt2,cnt,sizeof cnt);
    for (int i=0;i<mo;i++) cnt[i]=cnt2[a[i]];
    memset(cnt2,0x00,sizeof cnt2);
    tot=0; get(0,0,0);
    sort(x+1,x+tot+1,compare1);
    memset(t,0x00,sizeof t);
    for (int i=0;i<lim;i++) u[i]=min(cnt[i]+1,1ll*mo+3);
    for (int i=1;i<=tot;i++){
        long long k1=1e18;
        for (int j=0;j<lim;j++) if (x[i].B[j]) k1=min(k1,cnt[j]/x[i].B[j]);
        t[i]=k1; ans+=k1*(x[i].size-1);
        for (int j=0;j<lim;j++) cnt[j]-=x[i].B[j]*k1;
    }
    memset(d,0x3f,sizeof d); d[0][0][0][0][0]=0;
    memset(pre,0x00,sizeof pre);
    //cout<<u[0]<<" "<<u[1]<<" "<<u[2]<<" "<<u[3]<<" "<<u[4]<<endl;
    for (int aa=0;aa<u[0];aa++)
        for (int b=0;b<u[1];b++)
            for (int c=0;c<u[2];c++)
                for (int ddd=0;ddd<u[3];ddd++)
                    for (int e=0;e<u[4];e++){
                        if ((aa*a[0]+b*a[1]+c*a[2]+ddd*a[3]+e*a[4])%mo) continue;
                   //   cout<<aa<<" "<<b<<" "<<c<<" "<<ddd<<" "<<e<<endl;
                        for (int i=1;i<=tot;i++)
                            if (x[i].B[0]<=aa&&x[i].B[1]<=b&&x[i].B[2]<=c&&x[i].B[3]<=ddd&&x[i].B[4]<=e){
                                int aaa=aa-x[i].B[0],bb=b-x[i].B[1],cc=c-x[i].B[2],dd=ddd-x[i].B[3],ee=e-x[i].B[4];
                                if (d[aaa][bb][cc][dd][ee]+x[i].size-1<d[aa][b][c][ddd][e]){
                                    d[aa][b][c][ddd][e]=d[aaa][bb][cc][dd][ee]+x[i].size-1;
                                    pre[aa][b][c][ddd][e]=i;
                                }
                            }
                //      if (d[aa][b][c][ddd][e]<=1e9) cout<<aa<<" "<<b<<" "<<c<<" "<<ddd<<" "<<e<<" "<<d[aa][b][c][ddd][e]<<" "<<pre[aa][b][c][ddd][e]<<endl;
                    }
  /*  cout<<tot<<endl;
    cout<<"fa"<<endl;
    for (int j=0;j<lim;j++) cout<<a[j]<<" "; cout<<endl;
    for (int i=1;i<=tot;i++){
        cout<<"fa "<<t[i]<<" "<<x[i].size<<endl;
        for (int j=0;j<lim;j++) cout<<x[i].B[j]<<" "; cout<<endl;
    }*/
    while (1){
        memset(go,0x00,sizeof go);
        memset(cnt2,0x00,sizeof cnt2);
        if (getpath(1,0)==0) break;
        long long k1=1e18;
        int a=cnt2[0],b=cnt2[1],c=cnt2[2],d=cnt2[3],e=cnt2[4];
    //  cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
        for (int i=1;i<=tot;i++) if (go[i]) k1=min(k1,t[i]/go[i]);
        for (int i=1;i<=tot;i++){
            ans-=1ll*go[i]*k1*(x[i].size-1); t[i]-=go[i]*k1;
        }
        while (a+b+c+d+e){
            int k2=pre[a][b][c][d][e]; t[k2]+=k1; ans+=k1*(x[k2].size-1);
            a-=x[k2].B[0]; b-=x[k2].B[1]; c-=x[k2].B[2]; d-=x[k2].B[3]; e-=x[k2].B[4];
        }
    }
    printf("%lld\n",ans);
}
int main(){
    int t; scanf("%d",&t);
    for (;t;t--) solve();
    return 0;
}
