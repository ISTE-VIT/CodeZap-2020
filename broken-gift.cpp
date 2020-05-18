#include<bits/stdc++.h>
using namespace std ;
typedef long long int ll ;

#define modulo 1000000007


ll bin_expo(ll a, ll b)
{
    ll ans = 1 ;
    while(b){
        if(b&1){
            ans = (ans * a)%modulo ;
        }
        a = (a* a)%modulo;
        b /=2 ;
    }
    return ans ;

}
ll l , d , t ;
ll ppm( ll a[2][2] ){

    ll ans[2][2] ={{1,0},{0,1}};


    while(t){

        if(t & 1){

            ll x = (a[0][0]*ans[0][0] + a[0][1]*ans[1][0])%modulo ;
            ll y = (a[0][0]*ans[0][1] + a[0][1]*ans[1][1])%modulo ;
            ll z = (a[1][0]*ans[0][0] + a[1][1]*ans[1][0] )%modulo;
            ll w = (a[1][0]*ans[0][1] + a[1][1]*ans[1][1] )%modulo;

            ans[0][0] = x ;
            ans[0][1] = y ;
            ans[1][0] = z ;
            ans[1][1] = w ;


        }


        t = t / 2 ;

        ll x1 = (a[0][0]*a[0][0] + a[0][1]*a[1][0])%modulo ;
        ll x2 = (a[0][0]*a[0][1] + a[0][1]*a[1][1])%modulo ;
        ll x3 = (a[1][0]*a[0][0] + a[1][1]*a[1][0] )%modulo;
        ll x4 = (a[1][0]*a[0][1] + a[1][1]*a[1][1] )%modulo;
         a[0][0] = x1 ;
        a[0][1] = x2 ;
        a[1][0] = x3 ;
        a[1][1] = x4 ;

    }

    return ((ans[0][0] * d)%modulo + ans[0][1] )%modulo ;
}

int main(){
    int T ;
    scanf("%d" , &T);
    while(T--){
        scanf("%lld%lld%lld" , &l , &d , &t);
        //cin >> l >> d >> t ;
        ll q = 2 * d ;
        ll r = (l * l )%modulo;
        r *= -1 ;
        ll a[2][2] = { {q  , r},{1,0}};

        //cout<<bin_expo(l,d)<<endl;
        if( t == 0 ){
            printf("%lld\n" , l);
            //cout<<l<<endl;
        }
        else if(t==1){
            printf("%lld\n" , d);
            //cout<<d<<endl;
        }
        else {
            ll t1 = t ;
            t -= 1 ;
            ll p = ppm(a);
            //cout<<p<<endl;
            ll q = bin_expo(l,t1-1);



            ll result = ((p * bin_expo(q,modulo-2) )%modulo + modulo )%modulo;
            printf("%lld\n" , result);
            //cout<<result<< endl ;


        }

    }
    return 0;
}
