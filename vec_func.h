#ifndef VEC_GR
#define VEC_GR 2

#include"numch_func.h" 
//vector相关函数 
void all_resize(int n, vi &a, vi &b, vi &c) {a.resize(n), b.resize(n), c.resize(n);}
void to_EMPTY(vi &a) {a.clear(), a.push_back(0);}
void vec_swap(vi &a, vi &b) {a.swap(b);}
bool c_legal(vi &c) {return c.size();}
char is_ZERO(vi &a) {return a[0]==1 && !a[1];}
void reverse(vi &a){
    int n = my::abs(a[0]);
    for(int i=1; i+i<=n; i++)
        swap(a[i], a[n-i+1]);
}
void pop_front_zero(vi &a){
    int na = my::abs(a[0]);
    int f = a[0]>0 ? 1 : -1; 
    while(na>1 && a[na]==0) na--, a.pop_back();
    a[0] = na*f;
}
short vec_cmp(vi &a, vi &b){
    int na=my::abs(a[0]), nb=my::abs(b[0]);
    if(na != nb) return na>nb ? 1 : -1;
    for(int i=na; i>0; i--)
        if(a[i] != b[i]) return a[i]>b[i] ? 1 : -1;
    return 0;
}//1:a>b 0:a=b -1:a<b
ll vec_ll(vi b){
    ll ans = 0; int nb = my::abs(b[0]);
    while(nb) ans = ans*10+b[nb--];
    return ans;
}
vi zip(vi a){
    int f = a[0]>0 ? 1 : -1;
    int na = my::abs(a[0]), i;
    a.resize(na+5, 0);
    int nb = (na+2)/3;
    vi b(nb+5, 0);
    for(i=1; i<=na; i+=3){
        b[i/3+1] = a[i+2]*100+a[i+1]*10+a[i]; 
    }
    b[0] = f*nb;
    return b;
}//压位 
vi unzip(vi a){
    int f = a[0]>0 ? 1 : -1;
    int na = my::abs(a[0]), i;
    a.resize(na+5, 0);
    int nb = (na<<1)+na;
    vi b(nb+5, 0);
    for(i=1; i<=na; i++){
        b[i*3-3+1] = a[i]%10;
        b[i*3-3+2] = a[i]/10%10;
        b[i*3-3+3] = a[i]/100;
    }
    b[0] = f*nb;
    pop_front_zero(b);
    return b;
}//解压
 
#endif
