#ifndef IO_GR
#define IO_GR 3

#include<vector>
#include<cstdio>
#include"numch_func.h"
#include"vec_func.h"
#include"defs.h"

// 启用 ANSI 转义序列支持
#ifdef _WIN32
#include<windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
bool enable_ansi_support() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return false;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return false;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    return SetConsoleMode(hOut, dwMode);
}
#endif

vi EMPTY(1, 0);
//文件流
void out_con(){
    #ifdef _WIN32
        freopen("CON", "w", stdout);
    #else
        freopen("/dev/tty", "w", stdout);
    #endif
}
void input_con(){
    #ifdef _WIN32
        freopen("CON", "r", stdin);
    #else
        freopen("/dev/tty", "r", stdout);
    #endif
}//不能频繁使用此函数 
//输入输出函数
inline void in_log(char x){
	#ifndef ANDR15
    freopen("input.log", "a", stdout);
    putchar(x); out_con();
    #endif
}
inline void clear_line(){
    char t = getchar();
    while(t != '\n'){
        in_log(t);
        t = getchar();
    }
    in_log('\n');
}
int cli_ret(int x){
    clear_line();
    return x;
}
inline void endline(){
	puts("");
}
char input_check(vi a, vi b, char op){//检查输入正确性
    int na=abs(a[0]), nb = abs(b[0]);
    if(!na || !nb || !op) return INCOMPLETE_INPUT;//输入不完整
    return NO_ERROR;//无错误
}
char read(vi &a, vi &b, vi c, vi d, char &op){
    to_EMPTY(a), to_EMPTY(b); op = 0;
    int na=0, nb=0, nc=abs(c[0]), nd=abs(d[0]);
    char za=0, zb=0, zc=int_zf(c[0]), zd=int_zf(d[0]);
 
    char t, a_r = 1, b_r = 1;
    int fh_cnt = 0;
    while((t = getchar())){
        in_log(t);
        if(t < 20) break;//换行符 
        if(t<33 || t==',' || t=='_') continue;//忽略空格,_ 
        if(t>='0' && t<='9'){
            if(!op) a.push_back(t-48), na++;
            else b.push_back(t-48), nb++;
        }else if(is_zf(t)){
            fh_cnt++;
            if(!na && !za) za = t;
            else if(!op) op = t;
            else if(!nb && !zb) zb = t;
            else return cli_ret(REDUNDANT_CONTENT);
        }else if(is_fh(t)){
            fh_cnt++;
            if(!op) op = t;
            else return cli_ret(REDUNDANT_CONTENT);
        }else return cli_ret(UNKNOWN_CHAR);
    }
 
    //输入补全 
    if(!na && !nb){//只输入一个运算符
        if(fh_cnt > 1) return REDUNDANT_CONTENT;
        a_r = b_r = 0;//都不必反转 
        if(op){//运算符非加减 
            na=nd, za=zd, a=d;
            nb=nc, zb=zc, b=c;
        }else if(za){
            op = za;
            na=nd, za=zd, a=d;
            nb=nc, zb=zc, b=c;
        }
    }else if(!op){
        if(fh_cnt > 2) return REDUNDANT_CONTENT;
        a_r = 0, op = za;
        b = a, nb = na, zb = '+';
        a = c, na = nc, za = zc;
    }else if(!na && is_zf(op)){
        if(fh_cnt > 2) return REDUNDANT_CONTENT;
        a_r = 0, zb = op, op = za;
        a = c, na = nc, za = zc;
    }else if(!na && is_fh(op)){
        if(fh_cnt > 2) return REDUNDANT_CONTENT;
        a_r = 0, zb = za;
        na = nc, za = zc, a = c;
    }
    if(!za) za = '+';
    if(!zb) zb = '+';
    a[0] = na*zf_int(za);
    b[0] = nb*zf_int(zb);
 
    char r = input_check(a, b, op);
    if(r) return INCOMPLETE_INPUT;//输入不全
    if(a_r) reverse(a);
    if(b_r) reverse(b);
    pop_front_zero(a);
    pop_front_zero(b);
    return 0;//正常返回
}
void out(vi c, char fi){
    int nc = abs(c[0]);
    #ifndef ANDR15
    if(nc > 1e4) return;
    #endif
    if(fi) freopen("output.log", "a", stdout);
    if(!fi) printf(COLOR_RES);
    putchar(int_zf(c[0]));
    for(; nc; nc--) putchar(c[nc]+48);
    endline();
	if(!fi) printf(COLOR_ORI);
    if(fi) out_con();
}
void sci_out(vi c, int lang, char fi){
    int nc = abs(c[0]), i;
    if(nc < 5) return;//不必用科学计数法
    if(fi) freopen("output.log", "a", stdout);
    if(!fi) printf(COLOR_RES);
    if(c[0] < 0) putchar('-');
    putchar(c[nc]+48);
    putchar('.');
    for(i=nc-1; nc-i<11 && i; i--) putchar(c[i]+48);
    printf("e%d\n", nc-1);
    #ifndef ANDR15
    if(nc > 1e4){
        if(lang == 1) puts("前往ans.txt查看精确结果");
        else if(lang == 2) puts("see ans.txt for precise result");
    }
    #endif
    if(!fi) printf(COLOR_ORI);
    if(fi) out_con(); 
}
void ans_out(vi c){
    freopen("ans.txt", "w", stdout);
    int nc = abs(c[0]);
    putchar(int_zf(c[0]));
    for(; nc; nc--) putchar(c[nc]+48);
    endline();
    out_con();
}

 
#endif
