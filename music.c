#define MAX_LENGTH 40     //定义数组长度，表示列表最大长度
#define MAX_FILE_LENGTH 255  //定义数组长度，表明文件名最大长度
#define GET_NAME "%255s"  //用于scanf函数输入文件名，说明输入字符串的长度
int main(int argc, char const *argv[]) {
    unsigned i, l;  //i表示操作时指向数组的游标，l表示已列表总长度
    char *p_list[MAX_LENGTH]; //定义指针列表
    char f_list[MAX_LENGTH][MAX_FILE_LENGTH + 1]; //定义文件名列表
                //文件名加一是用于存放字符串结束符
    for(i = 0; i < MAX_LENGTH; i++){ //用循环对指针列表和文件名列表初始化
        p_list[i] = NULL; //将指针列表指向NULL
        f_list[i][0] = 0; //将字符串列表首位置0
    }

    int select_value;    //用于接收键盘输入的菜单选择
    char exit_switch = 1;  //用于控制程序主操作循环的退出
    l = 0;  //初始化列表长度
    do{
        puts("请选择操作命令: ");
        puts("(1)添加新文件");
        puts("(2)删除列表中的文件");
        puts("(3)打印播放列表");
        puts("(4)退出程序");
        scanf("%1d", &select_value);   //输入的菜单选择
        getchar();  //吸收多余的输入字符
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
            case 2:{ //删除列表中的文件
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
            case 3:{ //打印播放列表
                for(i = 0; i < 1; i++)
                    printf("%d: %s\n", i + 1, p_list[i]);
                    //通过指针列表间接引用文件名列表，输出文件名
                break;
            }
            case 4:{                //退出程序
                exit_switch = 0;    //将程序主操作循环退出标记置0
            }
        }
    }while(exit_switch);            //如果主操作循环退出标记不为0，继续执行循环
    return EXIT_SUCCESS;




    return 0;
}
