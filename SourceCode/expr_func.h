#ifndef EXPR_GR
#define EXPR_GR

#include"hpcalc.h"
using HP = grnum::HP;
#include"numch_func.h"
#include"defs.h"
#include"errs.h"

constexpr int NUMTYPE = 1;
constexpr int OPTYPE = 2;
constexpr int HEADTYPE = -1;//头指针,不存值
constexpr int TAILTYPE = -2;//尾指针,不存值
int ori_lv[130], MAX_ORI_LV = 4;
struct Token{
    //Token类型
    int type;

    //如果这个Token是数
    HP num;

    //如果这个Token是运算符
    char op;
    int op_lv;

    //链表指针
    Token* prev;
    Token* next;

    Token(){
        type = 0;
        num.clear();
        op = 0;
        op_lv = 0;
        prev = nullptr;
        next = nullptr;
    }
};

void new_num_tk(Token*& prv, HP num){
    Token* item = new Token;
    Token* nxt = prv->next;
    item->type = NUMTYPE;
    item->num = num;

    item->next = nxt;
    nxt->prev = item;
    item->prev = prv;
    prv->next = item;

    prv = item;
}
void new_op_tk(Token*& prv, char op, int lv){
    Token* item = new Token;
    Token* nxt = prv->next;
    item->type= OPTYPE;
    item->op = op, item->op_lv = lv;

    item->next = nxt;
    nxt->prev = item;
    item->prev = prv;
    prv->next = item;

    prv = item;
}

void clear_tk(Token* head){
    Token* tmp = head->next;
    Token* del;
    while(tmp->type != TAILTYPE){
        del = tmp, tmp = tmp->next;
        delete del;
    }
    head->next = tmp;
    tmp->prev = head;
}

void print_tk(Token* head){
	Token* temp = head;
    while(temp->type != TAILTYPE){
        if(temp->type == NUMTYPE){
            printf(" ");
            grnum::putHP(temp->num);
            printf(" ");
        }
        if(temp->type == OPTYPE){
            printf(" %c(%d) ", temp->op, temp->op_lv);
        }
        temp = temp->next;
    }
    puts("");
}

int calculate(Token* head){
    Token* tail=head;
    Token* i;
    Token* lop, *rop, *nop;
    Token* lnum, *rnum, *nnum;
    int max_lv = 0, cur_lv;
    int num_cnt = 0, op_cnt = 0;
    int ret;
    char op;
    HP a, b, c;

    while(tail->type != TAILTYPE){
        max_lv = max(max_lv, tail->op_lv);
        num_cnt += tail->type == NUMTYPE;
        op_cnt += tail->type == OPTYPE;
        tail = tail->next;
    }
    if(num_cnt != op_cnt+1) return EXPR_ERR;

    for(cur_lv=max_lv; cur_lv; cur_lv--){
        for(i=head; i!=tail; ){
            if(i->type == OPTYPE && i->op_lv == cur_lv){
                op = i->op;
                lnum = i->prev, lop = lnum->prev;
                rnum = i->next, rop = rnum->next;
                a = lnum->num, b = rnum->num;
                if(a.isEMPTY() || b.isEMPTY()) return EXPR_ERR;
                ret = math_check(a, op, b);
                if(ret) return ret;

                if(op == '+') c = a+b;
                if(op == '-') c = a-b;
                if(op == '*') c = a*b;
                if(op == '/') c = a/b;
                if(op == '%') c = a%b;
                if(op == '^') c = HP_pow(a, b);
                if(op == '&') c = a&b;
                if(op == '|') c = a|b;
                if(op == '!') c = a^b;
                nnum = new Token;
                nnum->type = NUMTYPE;
                nnum->num = c;
                
                nop = i, i = rop;
                lop->next = nnum, nnum->prev = lop;
                rop->prev = nnum, nnum->next = rop;
                delete lnum;
                delete rnum;
                delete nop;
            }
            else{
            	i = i->next;
			}
        }
//        print_tk(head);
    }
    
    if(!(head->next->next == tail)){
    	return EXPR_ERR;
	}
    c = head->next->num;
    if(c.isEMPTY()) return CAL_ERR;
    
    return NO_ERR;
}

#endif
