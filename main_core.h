#ifndef MAIN_CORE_H_  //判断是否已包含该文件
#define MAIN_CORE_H_  //定义头文件
/*程序控制指令*/
#define GENERAL_MEDIALIB_INIT       1000  //初始化媒体库列表
#define GENERAL_PLAyLIST_INIT       1001  //初始化播放列表链表
#define GENERAL_PLAY_MODE           1002  //设置播放模式：顺序、随机、循环
#define GENERAL_VOLUME              1003  //调节音量
#define GENERAL_MUTE                1004  //静音
/*程序请求指令*/
#define REQUEST_STATE               2000  //返回系统当前状态
#define REQUEST_NOW_PLAY            2001  //返回当前播放的媒体文件名称
#define REQUEST_MEDIA_TYPE          2002  //返回当前播放的媒体文件状态
#define REQUEST_PLAYLIST_POSITION   2003  //返回指针指向当前播放列表的位置
#define REQUEST_WINDOW_SIZE         2004  //返回窗体的尺寸
#define REQUEST_VOLUME              2005  //返回当前音量信息
/*媒体库控制指令*/
#define MEDIALIB_SHOW               3000  //显示媒体库信息
#define MEDIALIB_BRUSH              3001  //刷新媒体库信息
#define MEDIALIB_ADD_FILE           3002  //添加文件到媒体库
#define MEDIALIB_ADD_DIR            3003  //添加目录到媒体库
#define MEDIALIB_FIND               3004  //在媒体库中查找文件
#define MEDIALIB_SEARCH             3005  //搜索本地媒体文件，并保存到媒体库
#define MEDIALIB_DEL                3006  //从媒体库中删除选定文件
#define MEDIALIB_DEL_ALL            3007  //从媒体库删除所有文件
#define MEDIALIB_SELECT_CLASS       3008  //在媒体库中选择一个分类
#define MEDIALIB_SELECT_FILE        3009  //在媒体库中选择文件
#define MEDIALIB_SEND_TO_PLAYLIST   3010  //将媒体库中选择的文件添加到播放列表中
/*播放列表控制指令*/
#define PLAYLIST_SHOW               3100  //显示播放列表
#define PLAYLIST_BRUSH              3101  //刷新播放列表
#define PLAYLIST_ADD_FILE           3102  //添加文件到播放列表
#define PLAYLIST_ADD_DIR            3103  //添加目录中所有文件到播放列表
#define PLAYLIST_DEL                3104  //删除播放列表中选定的文件
#define PLAYLIST_DEL_ALL            3105  //删除播放列表中所有文件
#define PLAYLIST_SELECT             3106  //在播放列表中选择文件
#define PLAYLIST_COMPOSITOR_BY_NAME 3107  //按名称排序
#define PLAYLIST_OPEN               3108  //打开播放列表文件
#define PLAYLIST_SAVE               3109  //保存播放列表文件
#define PLAYLIST_COMP               3110  //为播放列表排序
/*播放控制指令*/
#define PLAY_START                  4000  //开始播放文件
#define PLAY_STOP                   4001  //停止播放文件
#define PLAY_PAUSE                  4002  //暂停播放文件
#define PLAY_PRE                    4003  //播放前一个文件
#define PLAY_NEXT                   4004  //播放后一个文件
#define PLAY_PITCH                  4005  //播放指定文件
/*定义函数原型*/

int general_init(void);
int general_sleep(void);


#endif  /*MAIN_CORE_H_*/                  //结束头文件定义
