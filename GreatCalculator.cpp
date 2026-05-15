#include<cstdio>
#include<vector>
#include"io_func.h"
#include"errs.h"
#include"init_func.h"
#include"hpcalc.h"
#include"expr_func.h"

using HP = grnum::HP;
using vi = std::vector<int>;

int main(){
    enable_ansi_support();
    int lang = lan_ch();
    instructions(lang);
    init();

    int ret = 0;
    //head、tail均不存值
    Token* head = new Token;
    Token* tail = new Token;
    head->type = HEADTYPE;
    tail->type = TAILTYPE;
    head->prev = head, head->next = tail;
    tail->prev = head, tail->next = tail;
    HP ans, lst_res;
    lst_res.clear();
    vi ans_vi;

    while(1){
        endline();
        clear_tk(head);
        ret = read(head, lst_res);
        if(ret){
            error_output(lang, ret);
            continue;
        }
        
//        print_tk(head);
        ret = calculate(head);
        if(ret > 0){
            error_output(lang, ret);
            continue;
        }
        
        ans = head->next->num;
        if(!ans.isEMPTY()){
            ans_vi = ans.getvec();
            ans_vi = unzip(ans_vi);
            #ifndef NOFILE
                out(ans_vi, 1), sci_out(ans_vi, lang, 1);//log
                out(ans_vi, 0), ans_out(ans_vi), sci_out(ans_vi, lang, 0);//给用户
            #else
                out(ans_vi, 0), sci_out(ans_vi, lang, 0);
            #endif
            lst_res = ans;
        }else{
        	error_output(lang, CAL_ERR);
		}
    }
    return 0;//Maybe I don't have to write this...
}
