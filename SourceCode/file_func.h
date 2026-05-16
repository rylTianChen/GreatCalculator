#ifndef FILE_GR
#define FILE_GR

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
        freopen("/dev/tty", "r", stdin);
    #endif
}//不能频繁使用此函数
//输入输出函数
inline void in_log(char x){
    #ifndef NOFILE
        freopen("input.log", "a", stdout);
        putchar(x); out_con();
    #endif
}

#endif
