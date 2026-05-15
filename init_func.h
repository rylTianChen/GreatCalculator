#ifndef INIT_GR
#define INIT_GR

#include<cstdio>
#include"io_func.h"
#include"expr_func.h"

const char version[] = "1.6";

//初始化
void instructions(int lang){
    printf(COLOR_INS);
    if(lang == 1){
        printf("高精度计算器 版本%s\n", version);
        puts("具体使用说明见READ_ME.txt");
        puts("请输入一条简单算式:");
    }else if(lang == 2){
        printf("High-precision Calculator v%s\n", version);
        puts("See READ_ME.txt for detailed instructions");
        puts("Enter an expression:");
    }
    printf(COLOR_ORI);
}
void init(){
    #ifndef NOFILE
        freopen("input.log", "w", stdout);
        printf("GreatCalculator%s\n", version);
        freopen("output.log", "w", stdout);
        printf("GreatCalculator%s\n", version);
        out_con();
    #endif
    ori_lv['&'] = ori_lv['|'] = ori_lv['!'] = 1;
    ori_lv['+'] = ori_lv['-'] = 2;
    ori_lv['*'] = ori_lv['/'] = ori_lv['%'] = 3;
    ori_lv['^'] = 4;
}
int lan_ch(){
    #ifndef NOFILE
        printf(COLOR_INS);
        int lang = 0;
        freopen("lang.txt", "r", stdin);
        scanf("%d", &lang);
        if(lang<1 || lang>2) puts("1.简体中文\n2.English");
        input_con();

        while(lang<1 || lang>2){
            puts("请选择一门语言。(输入1或2)");
            puts("Please choose a language.(Type in 1 or 2)");
            scanf("%d", &lang);
            clear_line();
        }

        freopen("lang.txt", "w", stdout);
        printf("%d\n", lang);
        puts("1.简体中文\n2.English");
        out_con();
        printf(COLOR_ORI);
        return lang;
    #else
        return 2;
    #endif
}

#endif
