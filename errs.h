#ifndef ERRS_GR
#define ERRS_GR 6

#include<vector>
#include"defs.h"
#include"numch_func.h"
#include"vec_func.h"

int math_check(vi &a, vi &b, char op){
    if(op=='+' || op=='-' || op=='*') return NO_ERROR;//必定能算
    if(op == '^'){//幂运算判断
        if(b[0] < 0) return NEGATIVE_POWER;//负次幂
        if(is_ZERO(a) && is_ZERO(b)) return ZERO_POW_ZERO;//0^0
        if(abs(a[0])>1 || a[1]>1){//非0 +1 -1
            if(b[0] > 8) return LARGE_RES;//结果太大
        }
    }
    //不能除以0、模0
    if(op=='/' && abs(b[0])==1 && b[1]==0) return DIVISION_BY_ZERO;
    if(op=='%' && abs(b[0])==1 && b[1]==0) return MODULE_BY_ZERO;
    return 0;
}

//错误提示函数
void error_output(int lang, int ret){
	printf(COLOR_ERR);
	if(lang == 1){
        if(ret == INCOMPLETE_INPUT) puts("输入不完整");
        if(ret == REDUNDANT_CONTENT) puts("输入多余内容");
        if(ret == UNKNOWN_CHAR) puts("未知字符");
        
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
        
        if(ret == DIVISION_BY_ZERO) puts("Cannot divide by zero");
        if(ret == NEGATIVE_POWER) puts("Negative exponents not supported");
        if(ret == ZERO_POW_ZERO) puts("0^0 is undefined");
        if(ret == MODULE_BY_ZERO) puts("Cannot modulo by zero");
        if(ret == LARGE_RES) puts("The answer is too big");
	}
	printf(COLOR_ORI);
}
#endif
