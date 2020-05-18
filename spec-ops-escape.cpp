#include<bits/stdc++.h>
using namespace std;
/************************************************************************************************/
static struct IO {char tmp[1 << 10];char cur;inline char nextChar()
{ return cur = getc_unlocked(stdin); }inline char peekChar() { return cur; }
inline operator bool() { return peekChar(); }inline static bool isBlank(char c)
{ return (c < '-' && c); }inline bool skipBlanks()
{ while (isBlank(nextChar())); return peekChar() != 0; }
inline IO& operator >> (char & c) { c = nextChar(); return *this; }
inline IO& operator >> (char * buf) {if (skipBlanks()) {if (peekChar()) {*(buf++) = peekChar();
while (!isBlank(nextChar())) *(buf++) = peekChar();} *(buf++) = 0; } return *this; }
inline IO& operator >> (string & s) {if (skipBlanks()) {    s.clear(); s += peekChar();
while (!isBlank(nextChar())) s += peekChar(); }return *this; }
inline IO& operator >> (double & d) { if ((*this) >> tmp) sscanf(tmp, "%lf", &d); return *this;    }
#define defineInFor(intType) inline IO& operator >>(intType & n) { if (skipBlanks()) { \
int sign = +1; if (peekChar() == '-') { sign = -1; n = nextChar() - '0'; } else \
n = peekChar() - '0'; while (!isBlank(nextChar())) { n += n + (n << 3) + peekChar() - 48; } \
n *= sign; } return *this; }
defineInFor(int)defineInFor(unsigned int)defineInFor(long long)
inline void putChar(char c) { putc_unlocked(c, stdout); }inline IO& operator << (char c) { putChar(c); return *this; }
inline IO& operator << (const char * s) { while (*s) putChar(*s++); return *this; }
inline IO& operator << (const string & s) { for (int i = 0; i < (int)s.size(); ++i) putChar(s[i]); return *this; }
char * toString(double d) { sprintf(tmp, "%lf%c", d, '\0'); return tmp; }
inline IO& operator << (double d) { return (*this) << toString(d); }
#define defineOutFor(intType) inline char * toString(intType n) { char * p = (tmp + 30); \
if (n) { bool isNeg = 0; if (n < 0) isNeg = 1, n = -n; while (n) *--p = (n % 10) + '0', n /= 10; \
if (isNeg) *--p = '-'; } else *--p = '0'; return p; } inline IO& operator << (intType n) { return (*this) << toString(n); }
defineOutFor(int)defineOutFor(long long)
#define endl ('\n')
#define cout __io__
#define cin __io__
} __io__;
/**************************************************************************************************/

class Node
{
public:
    int rem1,rem2,rem0;
    int added;
    Node()
    {
        rem1=0;rem2=0;rem0=0,added=0;
    }
};
vector<Node>st;
int left(int P){return (P<<1);}
int right(int P){return (P<<1)+1;}
void build(int P,int L,int R)
{
    if(L==R)
    {
        st[P].rem0 = 1;
        st[P].rem1 = 0;
        st[P].rem2 = 0;
        st[P].added = 0;
        return ;
    }
    else
    {
        int mid = (L+R)/2;
        build(left(P),L,mid);
        build(right(P),mid+1,R);
        st[P].rem0 = st[left(P)].rem0+st[right(P)].rem0;
        st[P].rem1 = st[left(P)].rem1+st[right(P)].rem1;
        st[P].rem2 = st[left(P)].rem2+st[right(P)].rem2;
    }
}

void change(Node&P)
{
    int temp = P.rem0;
    P.rem0 = P.rem2;
    P.rem2 = P.rem1;
    P.rem1 = temp;
}

void update(int P,int L,int R,int i,int j)
{
    if(L==i&&R==j)
    {
        st[P].added++;
        change(st[P]);
        return;
    }
    int mid = (L+R)/2;
    if(j<=mid)
        update(left(P),L,mid,i,j);
    else if(i>mid)
        update(right(P),mid+1,R,i,j);
    else
    {
        update(left(P),L,mid,i,mid);
        update(right(P),mid+1,R,mid+1,j);
    }
    st[P].rem0 = st[left(P)].rem0+st[right(P)].rem0;
    st[P].rem1 = st[left(P)].rem1+st[right(P)].rem1;
    st[P].rem2 = st[left(P)].rem2+st[right(P)].rem2;
    for(int i =0;i<st[P].added%3;i++)
        change(st[P]);
}

int query(int P,int L,int R,int i,int j,int added)
{
    if(L==i&&R==j)
    {
        if(added%3==0)
            return st[P].rem0;
        if(added%3==1)
            return st[P].rem2;
        if(added%3==2)
            return st[P].rem1;
    }
    added+=st[P].added;
    int mid = (L+R)/2;
    if(j<=mid)
        return query(left(P),L,mid,i,j,added);
    else if(i>mid)
        return query(right(P),mid+1,R,i,j,added);
    else
    {
        return query(left(P),L,mid,i,mid,added)+query(right(P),mid+1,R,mid+1,j,added);
    }

}

int main()
{

    int nsize,nquery;
    cin>>nsize>>nquery;
    st.assign(4*nsize,Node());
    build(1,0,nsize-1);
    while(nquery--)
    {
        int type,l,r;
        cin>>type>>l>>r;
        if(type==0)
            update(1,0,nsize-1,l,r);
        else
            cout<<query(1,0,nsize-1,l,r,0)<<endl;
    }

    return 0;
}
