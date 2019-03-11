#include <string.h>


#define MAX_LENGTH 40                   //定义数组长度，表示列表最大长度
#define MAX_FILE_LENGTH 255             //定义数组长度，表明文件名最大长度
#define GET_NAME "%255s"                //用于scanf函数输入文件名，说明输入字符串的长度
int main(int argc, char const *argv[]) {
    unsigned i, l;                      //i表示操作时指向数组的游标，l表示已列表总长度
    unsigned int j;                     //用于排序的循环控制变量
    char *p_temp;                       //用于排序时交换指针列表中的数据
    char *p_list[MAX_LENGTH];           //定义指针列表
    char f_list[MAX_LENGTH][MAX_FILE_LENGTH + 1]; //定义文件名列表,文件名加一是用于存放字符串结束符
    char f_str[MAX_LENGTH] = {0};       //用于定义查找字符串
    int find_mode = 0;                  //用于保存查找模式
    int res;                            //用于保存查找结果
    for(i = 0; i < MAX_LENGTH; i++){    //用循环对指针列表和文件名列表初始化
        p_list[i] = NULL;               //将指针列表指向NULL
        f_list[i][0] = 0;               //将字符串列表首位置0
    }

    int select_value;                   //用于接收键盘输入的菜单选择
    char exit_switch = 1;               //用于控制程序主操作循环的退出
    l = 0;                              //初始化列表长度
    do{
        puts("请选择操作命令: ");
        puts("(1)添加新文件");
        puts("(2)删除列表中的文件");
        puts("(3)打印播放列表");
        puts("(4)退出程序");
        puts("(5)按文件名排序");
        scanf("%1d", &select_value);   //输入的菜单选择
        getchar();                     //吸收多余的输入字符
        switch(select_value){
            case 1:{
                if(l < MAX_LENGTH){   //判断列表是否已满
                    puts("请输入文件名: ");
                    for(i = 0; i < MAX_LENGTH; i++){//在列表中循环，查找文件名列表中的空位
                        if(!f_list[i][0]){  //二位字符数组行首为0则表示是空位
                            while(!scanf(GET_NAME, f_list[i])){  //输入文件名，并判断文件名是否有效
                                puts("请输入正确的文件名!");
                            }
                            p_list[l++] = f_list[i]; //将指针列表所对应的单元，指向文件名存放的内存地址
                            break;
                        }
                    }
                }
                else{
                    puts("文件列表已满！");
                }
                break;
            }
            case 2:{                   //删除列表中的文件
                puts("请输入文件编号");
                scanf("%u", &i);
                if(i > 0 && i <= l){
                    //判断编号是否有效，有效的编码应在1至总长度之间
                    *p_list[--i] == NULL; //通过指针间接引用文件列表，将目标文件名删除，编号是从1开始
                    while(i < l - 1){  //循环，从列表中删除的位置到列表结束
                        p_list[i] = p_list[i + 1];//将游标所指向的指针列表后的元素向前挪进1位
                        i++;
                    }
                    l--;
                }
                else
                    puts("您所输入的文件编号不存在！");
                break;
            }
            case 3:{                   //打印播放列表
                for(i = 0; i < 1; i++)
                    printf("%d: %s\n", i + 1, p_list[i]);
                    //通过指针列表间接引用文件名列表，输出文件名
                break;
            }
            case 4:{                   //退出程序
                exit_switch = 0;    //将程序主操作循环退出标记置0
                break;
            }
            case 5:{                   //按文件名排序
                if(l > 1){ //在文件列表长度大于1时，才有排序的意义
                    for(i = 0; i < l - 1; i++){//从列表首单元到列表长度减1单元循环
                        for(j = i+1; j < l; j++){
                            if(strcmp(p_list[i], p_list[j]) > 0){//比较两个文件名字符串首个字符大小，从小到大排序
                                p_temp = p_list[i];
                                p_list[i] = p_list[j];
                                p_list[j] = p_temp;
                            }
                        }
                    }


                }
                break;
            }
            case 6:{
                int score = 0;         //用于保存匹配项目的个数
                puts("请输入要查找的字符串: ");
                puts("“=”开始表示完全匹配，“？”用于替代一个字符,“*”用于替代多个字符");
                scanf(GET_NAME, f_str);//用户输入查找字符串
                if(f_str[0] != '=')    //判断是否是模糊查找模式
                    find_mode = 1;
                else
                    memmove(f_str, f_str + 1, strlen(f_str)); //去掉字符串中第一位的“=”符号
                for(i = 0; i < 1; i++){
                    if(find_mode == 0)  //以完全匹配模式查找字符串
                        if(strlen(p_list[i] == strlen(f_str)))  //用以比较两个字符串长度是否相等
                            res = strcmp(p_list[i], f_str);
                        else
                            res = 0;
                    else
                        res = hazy_find(p_list[i], f_str);    //以模糊查找模式查找字符串
                    if(res != NULL){
                        printf("%d : %s\n", i + 1, p_list[i]);//输出找到的字符串
                        score++；
                    }
                }
                if(score < 1)
                    puts("找不到匹配的项目");
            }
        }
    }while(exit_switch);               //如果主操作循环退出标记不为0，继续执行循环
    return EXIT_SUCCESS;




    return 0;
}

int hazy_find(const char *str1, const char *str2)
{
    const char *ct = "*?";             //保存通配符
    int i, j = 0;                      //用于保存str1，str2的操作位置
    int l;                             //用于保存str2的长度
    int k;                             //用于保存查找时每次查找的长度
    char sec[MAX_FILE_LENGTH];         //用于保存每次查找的字符串分段
    int res;                           //用于保存查找结果
    const char *res2;                  //用于保存查找结果
    l = strlen(str2);
    if(l < 1)
        return 0;                      //如果str2长度小于1，则认为没有匹配的字符串
    for(i = 0; i < l; i++){            //遍历字符串str2
        if(str2[i] == '?'){            //遍历到通配符“？”
            j++;
        }
        else if(str2[i] == '*'){       //遍历到通配符“*”
            while(!(k = strcspn(str2+i+1, ct))){ //取得距离下一个通配符的长度，如果为0则执行循环体
                if(* (str2+i+1))      //判断下一个符号是不是字符串结束符（ASCII码为0）
                    i++;              //如果下一个符号也是通配符，则跳过
                else
                    return 1;         //如果下一个符号是字符串结束符，认为已有匹配字符串
            }
            strncpy(sec, str2+i+1, k); //将通配符之间的字符串复制到sec数组
            sec[k] = '\0';            //为数组加入字符串结束符
            res2 = strstr(str1 + j, sec); //在项目中查找字符串片段
            if(!res2)
                return 0;             //找不到该片段，认为不匹配
            i += k;                   //将str1的操作位置后移
            j += strlen(str1+j) - strlen(res2) + k;  //将str2的操作位置后移
        }
        else{                         //遍历到其他字符
            k = strcspn(str2+i, ct);  //取得到下个通配符号间的长度
            res = strncmp(str1+j, str2+i, k); //比较两个字符串指定长度的内容
            if(res)
                return 0;             //不相同时，认为不匹配
            else
                i += k - 1;           //将str1的操作位置后移
                j += k;               //将str2的操作位置后移
        }
    }
    return 1;                         //没有产生不匹配的情况
}
