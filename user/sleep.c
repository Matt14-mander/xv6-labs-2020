#include "kernel/types.h" 
#include "user/user.h"

// argc 是命令行总的参数个数  
// argv[] 是 argc 个参数，其中第 0 个参数是程序的全名，以后的参数是命令行后面跟的用户输入的参数
int main(int argc, char* argv[]){
    // 如果命令行参数不等于2个，则打印错误信息
    if(argc != 2){
        // 系统调用 write(int fd, char *buf, int n) 函数输出错误信息
        // 参数 fd 是文件描述符，0 表示标准输入，1 表示标准输出，2 表示标准错误
        // 参数 buf 是程序中存放写的数据的字符数组
        // 参数 n 是要传输的字节数
        // 所以这里调用 user/ulib.c 的 strlen() 函数获取字符串长度字节数
        write(2, "Usage: sleep time\n", strlen("Usage: sleep time\n"));
        exit(1);
    }
    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}