#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <ctime>
#include <cstring>
#include <cstdio>
using namespace std;
#define r4 (r<<2)
//#define mx2 ((sx+ex)>>1)
//#define my2 ((sy+ey)>>1)
typedef pair<int,int> pii;
typedef pair<pii,pii> piipii;
typedef long long ll;
typedef unsigned long long ull;
map<piipii,int> mp;
int n,m,q;
int sx=1,sy=1,ex,ey,sz=1;
vector<ll> lazy,tree;

struct ano{
    operator ull(){
        ull x=0,y=0,c=getchar();
        while(c<48) y=c==45,c=getchar();
        while(c>47) x=(x<<1)+(x<<3)+c-48,c=getchar();
        return y?-x:x;
    }
}buf;


inline void pushdown(int r, int sx, int sy, int ex, int ey) {
    //if(lazy[r]) {
    if(!(sx==ex && sy==ey)) {
        int a,b,c,d;

        if(r==0) a=1,b=2,c=3,d=4;
        else if(r&1) a=r4+1,b=r4+2,c=r4+5,d=r4+6;
        else a=r4-1,b=r4,c=r4+3,d=r4+4;
        lazy[a] += lazy[r];
        lazy[b] += lazy[r];
        lazy[c] += lazy[r];
        lazy[d] += lazy[r];
    } else tree[r] += lazy[r]; //단말노드에만 tree[r]값 갱신해준다.
    //tree[r]+=lazy[r]*(ex-sx+1)*(ey-sy+1); //근데 단말 노드가 아니면 이 정보가 필요가 없음.
    lazy[r]=0;
    //}
}
void update(int r, int sx, int sy, int ex, int ey, int qsx, int qsy, int qex, int qey, int by) {
    if(lazy[r]) pushdown(r,sx,sy,ex,ey);
    if(ex<qsx || qex<sx || ey<qsy || qey<sy) return; //tree[r];
    else if(qsx<=sx && ex<=qex && qsy<=sy && ey<=qey) {
        lazy[r]+=(ll)by;
        if(lazy[r]) pushdown(r,sx,sy,ex,ey);
        //return tree[r];
    } else {
        int mx2=(sx+ex)>>1, my2=(sy+ey)>>1, t=r4;
        int a,b,c,d;
        if(r==0) a=1,b=2,c=3,d=4;
        else if(r&1) a=r4+1,b=r4+2,c=r4+5,d=r4+6;
        else a=r4-1,b=r4,c=r4+3,d=r4+4;

        update(a, sx,sy, mx2,my2, qsx,qsy,qex,qey,by);
        update(b, sx,my2+1, mx2,ey, qsx,qsy,qex,qey,by);
        update(c, mx2+1,sy, ex,my2, qsx,qsy,qex,qey,by);
        update(d, mx2+1,my2+1, ex,ey, qsx,qsy,qex,qey,by);
    }
}
ll query(int r, int sx, int sy, int ex, int ey, int qx, int qy) {
    if(lazy[r]) pushdown(r,sx,sy,ex,ey);
    if(ex<qx || qx<sx || ey<qy || qy<sy) return 0; //tree[r];
    else if(sx==ex && sy==ey) return tree[r];
    else {
        int mx2=(sx+ex)>>1, my2=(sy+ey)>>1;
        int a,b,c,d;
        if(r==0) a=1,b=2,c=3,d=4;
        else if(r&1) a=r4+1,b=r4+2,c=r4+5,d=r4+6;
        else a=r4-1,b=r4,c=r4+3,d=r4+4;

        ll u=query(a,sx,sy,mx2,my2,qx,qy);
        ll v=query(b,sx,my2+1,mx2,ey,qx,qy);
        ll w=query(c,mx2+1,sy,ex,my2,qx,qy);
        ll z=query(d,mx2+1,my2+1,ex,ey,qx,qy);
        return u+v+w+z;
    }
}
int main() {
    n=buf;m=buf;q=buf;
    int i;
    sx=sy=ex=ey=sz=i=1;
    for(;i<max(n,m);i<<=1) sz+=i*i;
    sz+=i*i, ex=ey=i;

    //tree.clear(); tree.resize(sz);
    //lazy.clear(); lazy.resize(sz);
    tree.resize(sz); lazy.resize(sz);
    for(int i=0; i<q; i++) {
        int t=buf,x1=buf,y1=buf,x2=buf,y2=buf;
        if((x1==x2 && y1>y2) || x1>x2) swap(x1,x2),swap(y1,y2);
        if(t==1) {
            int val = (rand()<<15)|rand();
            mp[piipii(pii(x1,y1),pii(x2,y2))]=val;
            update(0,sx,sy,ex,ey,x1,y1,x2,y2,val);
        } else if(t==2) {
            int val = mp[piipii(pii(x1,y1),pii(x2,y2))];
            update(0,sx,sy,ex,ey,x1,y1,x2,y2,-val);
        } else {
            if(query(0,sx,sy,ex,ey,x1,y1) == query(0,sx,sy,ex,ey,x2,y2)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
