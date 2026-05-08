#include<cstdio>
#include<vector>
#include"defs.h"
#include"io_func.h"
#include"errs.h"
#include"init_func.h"
#include"hpcalc.h"

int main(){
    enable_ansi_support();
    int ret;
    char op;
    vi a(1, 0), b(1, 0);
    vi c(1, 0), d(1, 0);
    int lang = lan_ch();

    instructions(lang);
    init();

    while(1){
        endline();
        ret = read(a, b, c, d, op);
        if(ret){
            error_output(lang, ret);
            continue;
        }
        ret = math_check(a, b, op);
        if(ret > 0){
            error_output(lang, ret);
            continue;
        }
        d = c;
        grnum::HP A(zip(a)), B(zip(b)), C;
        //在了解存储逻辑之前, 不要使用这个构造函数
        if(op == '+') C = A + B;
        if(op == '-') C = A - B;
        if(op == '*') C = A * B;
        if(op == '/') C = A / B;
        if(op == '^') C = HP_pow(A, B);
        if(op == '%') C = A % B;
        if(op == '&') C = A & B;
        if(op == '|') C = A | B;
        if(op == '!') C = A ^ B;
        if(!C.isEMPTY()){
            c = C.getvec();
            c = unzip(c);
	        #ifndef NOFILE
	            out(c, 1), sci_out(c, lang, 1);//log
	            out(c, 0), ans_out(c), sci_out(c, lang, 0);//给用户
	        #else
	            out(c, 0), sci_out(c, lang, 0);
	        #endif
        }
    }
    return 0;//Maybe I don't have to write this...
}
