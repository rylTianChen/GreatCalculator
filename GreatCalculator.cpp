#include<cstdio>
#include<vector>
typedef std::vector<int> vi;
typedef long long ll;
const char version[] = "1.5";
#include"io_func.h"
#include"init_func.h"
#include"hpcalc.h"
using namespace grnum;

short math_check(vi &a, vi &b, char op){
    if(op=='+' || op=='-' || op=='*') return 0;//必定能算
    if(op == '^'){//幂运算判断
        if(b[0] < 0) return 2;//负次幂
        if(is_ZERO(a) && is_ZERO(b)) return 3;//0^0
        if(is_ZERO(b)) return -2;
        if(is_ZERO(a)) return -1;//结果为0
        if(a[0]==1 && a[1]==1) return -2;//结果为1
        if(a[0]==-1 && a[1]==1) return (b[1]&1) ? -3 : -2;
        if(abs(a[0])>1 || a[1]>1){//非0 +1 -1
            if(b[0] > 8) return 5;//结果太大
        }
    }
    //不能除以0、模0
    if(op=='/' && abs(b[0])==1 && b[1]==0) return 1;
    if(op=='%' && abs(b[0])==1 && b[1]==0) return 4;
    return 0;
}

int main(){
	enable_ansi_support();
    int ret, lang; char op;
    vi a(1, 0), b(1, 0), c(1, 0), d(1, 0);
    HP C;
    lang = lan_ch(); instructions(lang); init();
 
    while(1){
        endline();
        ret = read(a, b, c, d, op);
        if(ret){
        	printf(COLOR_RED);
            if(lang == 1){
                if(ret == 1) puts("输入不完整");
                else if(ret == 2) puts("输入多余内容");
                else if(ret == 3) puts("未知字符");
            }else if(lang == 2){
                if(ret == 1) puts("Incomplete input");
                else if(ret == 2) puts("Redundant content");
                else if(ret == 3) puts("Unknown character");
            }
            printf(COLOR_ORI);
            continue;
        }
        ret = math_check(a, b, op);
        if(ret > 0){
        	printf(COLOR_RED);
            if(lang == 1){
                if(ret == 1) puts("不能除以0");
                if(ret == 2) puts("暂不支持负次幂");
                if(ret == 3) puts("0^0无意义");
                if(ret == 4) puts("不能模0"); 
                if(ret == 5) puts("结果过大");
            }else if(lang == 2){
                if(ret == 1) puts("Cannot divide by zero");
                if(ret == 2) puts("Negative exponents not supported");
                if(ret == 3) puts("0^0 is undefined");
                if(ret == 4) puts("Cannot modulo by zero");
                if(ret == 5) puts("The answer is too big"); 
            }
            printf(COLOR_ORI);
            continue;
        }
        d = c;
        if(ret < 0){
            if(ret == -1) c = ZERO;
            if(ret == -2) c = ONE;
            if(ret == -3) c = M_ONE;
        }else{
            HP A(zip(a)), B(zip(b));
            if(op == '+') C = A + B;
            if(op == '-') C = A - B;
            if(op == '*') C = A * B;
            if(op == '/') C = A / B;
            if(op == '^') C = HP_pow(A, B);
            if(op == '%') C = A % B;
            if(op == '&') C = A & B;
            if(op == '|') C = A | B;
        }
        if(!C.isEMPTY()){
        	c = C.vec();
            out(c, 1), sci_out(c, lang, 1);//log
            out(c, 0), ans_out(c), sci_out(c, lang, 0);//给用户 
        }
    }
    return 0;//Maybe I don't have to write this...
}
