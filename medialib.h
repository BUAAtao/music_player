#ifndef MEDIALIB_H_
#define MEDIALIB_H_
#define MAX_TITLE_LENGTH      512              //标题最长长度
#define MAX_ATRIST_LENGTH     512              //艺术家名称最长长度
#define MAX_ALBUM_LENGTH      256              //专辑名称最长长度
#define MAX_GENRE_LENGTH      256              //流派最长长度
#define MAX_PATH_LENGTH       4096             //路径最长长度
typedef struct _medialib Medialib;             //将结构体定义新数据类型
struct _medialib {                             //媒体库项目结构体
    char title[MAX_TITLE_LENGTH];              //标题
    char atrist[MAX_ATRIST_LENGTH];            //艺术家
    char album[MAX_ALBUM_LENGTH];              //专辑名称
    char genre[MAX_GENRE_LENGTH];              //流派
    double record_time;                        //记录时间
    char filepath[MAX_PATH_LENGTH];            //文件路径
};

typedef struct _node_t node_t;                 //将结构体定义为新类型
struct _node_t {                               //结点的结构体
    Medialib item;                             //存放媒体信息的结构体成员
    node_t *p;                                 //指向另一个结点的指针
};
typedef struct _link_t link_t;
struct _link_t {                               //链表的结构体
    node_t *np;                                //指向链表中第一个结点首地址的指针
    int length;                                //用于记录链表的长度
};
int read_tag_from_file(const char *file, struct _medialib *media);
#endif  /*MEDIALIB_H_*/
