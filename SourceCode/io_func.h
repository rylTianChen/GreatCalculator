#ifndef IO_GR
#define IO_GR

#include<vector>
#include<cstdio>
#include<string>
using str = std::string;
#include"numch_func.h"
#include"defs.h"
#include"expr_func.h"
#include"hpcalc.h"
#include"file_func.h"

// 启用 ANSI 转义序列支持
#ifdef _WIN32
    #include<windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif
bool enable_ansi_support() {
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return false;
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return false;
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        return SetConsoleMode(hOut, dwMode);
    #else
        return true;
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

char input_check(vi &a, vi &b, char op){//检查输入正确性
    int na=abs(a[0]), nb = abs(b[0]);
    if(!na || !nb || !op) return INCOMPLETE_INPUT;//输入不完整
    return NO_ERR;//无错误
}
using HP = grnum::HP;
char read(Token* head, HP lst_res){
    char is_first_ch = 1, t, lst_ch = 0;
    int par_lv = 0;//括号等级
    str temp_num = "";
    Token* lst_tk = head;

    while((t = getchar())){
        in_log(t);
//        putchar(t);
        if(t < 20) break;//换行符
        if(t<33 || t==',' || t=='_') continue;//忽略空格,_
        if(is_digit(t)){
            if(lst_ch == ')') return cli_ret(INCOMPLETE_INPUT);
            temp_num += t;
        }else{
            if(is_first_ch){
                if(is_zf(t)){
                    if(!lst_res.isEMPTY()){
                        //沿用上次结果
                        new_num_tk(lst_tk, lst_res);
                        lst_ch = lst_res.GetDigit(1)+'0';
                    }else{
                        temp_num += t;//作为正负号
                    }
                }
                if(is_fh(t)){
                    if(!lst_res.isEMPTY()){
                        new_num_tk(lst_tk, lst_res);
                        lst_ch = lst_res.GetDigit(1)+'0';
                    }else{
                        return cli_ret(INCOMPLETE_INPUT);
                    }
                }
            }
            if(!is_first_ch && (temp_num=="+" || temp_num=="-")){
                return cli_ret(INCOMPLETE_INPUT);
            }
            if(temp_num != ""){
                //把数存起来
//                cout << temp_num << endl;
                new_num_tk(lst_tk, HP(temp_num));
                temp_num = "";
            }
            if(is_zf(t)){
                if(is_digit(lst_ch) || lst_ch==')'){
                    //这个字符当运算符存起来
                    new_op_tk(lst_tk, t, ori_lv[int(t)]+par_lv);
                }else{
                    //这个字符当正负号
                    if(temp_num == "") temp_num += t;
                    else return cli_ret(REDUNDANT_CONTENT);
                }
            }
            else if(is_fh(t)){
                if(is_digit(lst_ch) || lst_ch==')'){
                    new_op_tk(lst_tk, t, ori_lv[int(t)]+par_lv);
                }
                else return cli_ret(REDUNDANT_CONTENT);
            }
            else if(t == '('){
                if(is_zf(lst_ch) || is_fh(lst_ch) || lst_ch=='('){
                    //括号内运算符等级提高
                    par_lv += MAX_ORI_LV;
                }
                else return cli_ret(INCOMPLETE_INPUT);
            }
            else if(t == ')'){
                if(is_digit(lst_ch) || lst_ch==')'){
                    par_lv -= MAX_ORI_LV;
                    if(par_lv < 0) return cli_ret(MUCH_RPAR);
                }
                else return cli_ret(INCOMPLETE_INPUT);
            }
            else return cli_ret(UNKNOWN_CHAR);
        }
        is_first_ch = 0;
        lst_ch = t;
    }
    if(par_lv > 0) return MUCH_LPAR;
    if(is_digit(lst_ch)) new_num_tk(lst_tk, HP(temp_num));
    if(is_zf(lst_ch) || is_fh(lst_ch) || lst_ch=='(') return INCOMPLETE_INPUT;

    return NO_ERR;
}
void out(vi c, char fi){
    int nc = abs(c[0]);
    #ifndef NOFILE
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
    #ifndef NOFILE
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
