#ifndef ERRS_GR
#define ERRS_GR

#include"numch_func.h"
#include"vec_func.h"
#include"defs.h"
#include"hpcalc.h"

//错误提示函数
void error_output(int lang, int ret){
    printf(COLOR_ERR);
    if(lang == 1){
        if(ret == INCOMPLETE_INPUT) puts("输入不完整");
        if(ret == REDUNDANT_CONTENT) puts("输入多余内容");
        if(ret == UNKNOWN_CHAR) puts("未知字符");
        if(ret == MUCH_LPAR) puts("过多左括号");
        if(ret == MUCH_RPAR) puts("过多右括号");
        if(ret == EMPTY_INPUT) puts("输入为空");
        
        if(ret == EXPR_ERR) puts("表达式错误");
        if(ret == CAL_ERR) puts("计算错误");

        if(ret == DIVISION_BY_ZERO) puts("不能除以0");
        if(ret == NEGATIVE_POWER) puts("暂不支持负次幂");
        if(ret == ZERO_POW_ZERO) puts("0^0无意义");
        if(ret == MODULE_BY_ZERO) puts("不能模0");
        if(ret == LARGE_RES) puts("结果过大");
    }
    if(lang == 2){
        if(ret == INCOMPLETE_INPUT) puts("Incomplete input");
        if(ret == REDUNDANT_CONTENT) puts("Redundant content");
        if(ret == UNKNOWN_CHAR) puts("Unknown character");
        if(ret == MUCH_LPAR) puts("Too much left parentheses");
        if(ret == MUCH_RPAR) puts("Too much right parentheses");
        if(ret == EMPTY_INPUT) puts("Empty input");
        
        if(ret == EXPR_ERR) puts("Expression error");
        if(ret == CAL_ERR) puts("Calculation error");

        if(ret == DIVISION_BY_ZERO) puts("Cannot divide by zero");
        if(ret == NEGATIVE_POWER) puts("Negative exponents not supported");
        if(ret == ZERO_POW_ZERO) puts("0^0 is undefined");
        if(ret == MODULE_BY_ZERO) puts("Cannot modulo by zero");
        if(ret == LARGE_RES) puts("The answer is too big");
    }
    printf(COLOR_ORI);
}

int math_check(HP &a, char op, HP &b){
	if(op=='+' || op=='-') return NO_ERR;
	if(op == '*'){
		if(a.size()+b.size() > LEN_LIMIT) return LARGE_RES;
	}
	if(op == '/'){
		if(b.sign() == 0) return DIVISION_BY_ZERO;
	}
	if(op == '%'){
		if(b.sign() == 0) return MODULE_BY_ZERO;
	}
	if(op == '^'){
		if(b.sign() < 0) return NEGATIVE_POWER;
		if(a.sign()==0 && b.sign()==0) return ZERO_POW_ZERO;
		if(a!=0 && a!=1 && a!=-1){
			if(b.size() > POW_LIMIT) return LARGE_RES;
		}
	}
    return NO_ERR;
}
#endif
