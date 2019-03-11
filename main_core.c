#include "main_core.h"
void *main_core(int cmd, void *data)
{
    static int state = 0;                        //用于保存当前程序状态
    static char *now_play;                       //正在播放的媒体文件路径
    static char *media_type;                     //正在播放的媒体类型
    static int playlist_position;                //播放列表当前位置
    static int window_size[2];                   //主窗体尺寸

    mlink
    plink
    link_t

    .
    .
    int ctype;                                   //用户保存指令的分类
    ctype = cmd/1000;                            //获得指令类型
    switch(ctype){                               //第一层选择语句处理分类
        case 1:                                  //处理程序控制指令
            switch(cmd){                         //第二层选择语句处理具体指令
                case GENERAL_MEDIALIB_INIT:      //初始化媒体库链表
                    mlink = (link_t *)data;
                    break;
                case GENERAL_PLAYLIST_INIT:      //初始化播放列表链表
                    plink = (link_t *)data;
                    break;
                case GENERAL_PLAY_MODE:          //设置播放状态
                    state = *((int *)data);
                    break;
                case GENERAL_VOLUME:             //设置播放音量
                    general_volume(*((int *)data));
                case GENERAL_MUTE:               //设置静音
                    general_mute(*((int *)data));
                default:
                    return NULL;
                        break;
            }
            break;
        case 2: {                                 //处理程序请求指令
            switch(cmd) {
                case REQUEST_STATE:              //请求返回播放状态
                    return &state;
                    break;
                case REQUEST_NOW_PLAY:

                    break;
                case REQUEST_MEDIA_TYPE:

                    break;
                case REQUEST_PLAYLIST_POSITION:

                    break;
                case REQUEST_WINDOW_SIZE:

                    break;


                case REQUEST_VOLUME:

                    break;
            }
            break;
        }
        case 3: {                                 //处理媒体库操作指令
            medialib(cmd, data);
            break;
        }
        case 4: {                                 //处理播放控制操作指令
            play(cmd, data);
            break;
        }                                //处理播放控制操作指令
        default:                                  //处理错误命令
            return NULL;
        }

    }
}
