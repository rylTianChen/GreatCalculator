#ifndef INIT_GR
#define INIT_GR 4
 
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
	#ifndef ANDR15
    freopen("input.log", "w", stdout);
    printf("GreatCalculator%s\n", version);
    freopen("output.log", "w", stdout);
    printf("GreatCalculator%s\n", version);
    out_con();
    #endif
}
int lan_ch(){
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
    return lang;
}
 
#endif
