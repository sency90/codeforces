#include <cstdio>
#include <iostream>
using namespace std;
int get_bit(int a) {
	a++;
	int ret = 0;
	while(a) {
		a>>=1;
		ret++;
	}
	return ret-1;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int tc; cin >> tc;
	while(tc--) {
		int a,b,c; cin>>a>>b>>c;
		int bit = get_bit(a);
		int t = (1<<bit)-1;
		int p2= a-t;
		int p1=(1<<bit)-p2;
		//printf("bit:%d, t:%d, p1:%d, p2:%d\n", bit, t, p1, p2);
		if(c != p1+2*p2) puts("-1");
		else {
			if(a+b+c==1) puts("0");
			else if(b==0) printf("%d\n", bit+1);
			else {
				b -= p1;
				if(b<=0) printf("%d\n", bit+1);
				else {
					while(true) {
						b -= p1+2*p2;
						bit++;
						if(b<=0) break;
					}
					printf("%d\n", bit+1);
				}
			}
		}
	}
	return 0;
}
