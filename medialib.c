#include <string>
#include <id3tag.h>
#include "medialib.h"               //包含媒体库相关函数的头文件
int read_tag_from_file(const char *file, struct _medialib *media)
{
    struct id3_file *id3file;       //用于保存libid3tag库文件对象
    struct id3_tag *tag;            //用于保存文件信息
    struct id3_frame *frame_title;  //用于保存标题信息
    struct id3_frame *frame_artist; //艺术家信息
    struct id3_frame *frame_album;  //专辑信息
    struct id3_frame *frame_genre;  //流派信息
    struct id3_frame *frame_time;   //记录长度信息
    id3file = id3_file_open(file, ID3_FILE_MODE_READONLY);
    //打开文件并创建id3_file结构体
    if (id3file == NULL){
        printf("打开文件失败\n");
        return -1;
    }
    tag = id3_file_tag(id3file);    //创建id3_tag结构体
    frame_title = id3_tag_findframe(tag, ID3_FRAME_TITLE, 0);
    //创建id3_frame结构体
    if(frame_title->fields)
        strcpy(media->title, (char *) frame_title->fields);
        //将项目信息复制到媒体库结构中
    frame_artist = id3_tag_findframe(tag, ID3_FRAME_ARTIST, 0);
    if(frame_artist->fields)
        strcpy(media->artist, (char *) frame_artist->fields);
    frame_album = id3_tag_findframe(tag, ID3_FRAME_ALBUM, 0);
    if(frame_album->fields)
        strcpy(media->album, (char *) frame_album->fields);
    frame_genre = id3_tag_findframe(tag, ID3_FRAME_GENRE, 0);
    if(frame_genre->fields)
        strcpy(media->genre, (char *) frame_genre->fields);
    frame_time = id3_tag_findframe(tag, "TDRC", 0);
    if(frame_time->fields)
        media->record_time = id3_field_getint(frame_time->fields);
    strcpy(media->filepath, file);
    id3_file_close(id3file);
    return 0;
}

node_t *link_to_end(node_t *nt)
{
    if(nt->p)                           //判断指针是否指向NULL
        return link_to_end(nt->p);      //递归调用
    else
        return nt;
}

int link_add(link_t *mlink, const char *file){
    node_t *endnode;
    node_t *mnode = (node_t)malloc(sizeof(node_t)); //为结点分配内存
    if (!mnode){
        printf("分配内存失败\n");
        return 1;
    }
    if (read_tag_from_file(file, &mnode->item)){    //读取媒体文件信息
        printf("读取文件信息失败\n");
        free(mnode);                                //释放结点内存
        return 1;
    }
    mnode->p = NULL;                                //将节点的指针置为NULL
    if (mlink->np) {                                //判断列表是否不为空
        endnode = link_to_end(mlink->np);           //遍历到结点末端
        endnode->p = mnode;                         //将末端节点指向当前节点
    }
    else
        mlink->np = mnode;                          //将链表入口指向当前结点
    mlink->length++;                                //链表个数的计数器自增
    return 0;
}

int link_find(link_t *mlink,                        //链表指针
          find_cond t,                              //查找条件
          const char *str2,                         //查找字符串
          node_t **res)                             //保存查找结果的动态数组指针
{
    if(*res) {
        free(*res);
        *res = NULL;
    }
    int i, l;
    int count = 0;                                  //用于保存找到匹配项目的数量
    const char *str1;                               //指向链表结点数据结构中的字符串
    node_t *tmp, **jump, **jump2;                   //遍历时所使用的指针和访问动态数组的指针
    if(!mlink->length) {                            //判断链表是否为空
        printf("媒体库为空，无法查找\n", );
        return 0;
    }
    if(str2)                                        //判断查找字符串指针是否为NULL
        l = strlen(str2);
    else {
        printf("查找字符串地址有误\n");
        return 0;
    }
    if (!l) {                                       //判断查找字符串长度是否为0
        printf("查找字符串长度为0\n");
        return 0;
    }
    tmp = mlink->np;                                //指向链表首端节点
    node_t *tmp_link = (node_t *)malloc(sizeof(node_t *) * mlink->length);
    //创建临时用于保存查找结果的动态数组，数组长度与链表长度相同
    jump = &tmp_link;                               //用指针指向动态数组首地址
    while(tmp) {                                    //遍历链表
        switch(t) {                                 //选择查询条件
            case BY_TITLE:
                str1 = tmp->item.title;             //读取标题信息
                break;
            case BY_ARTIST:
                str1 = tmp->item.atrist;            //读取艺术家信息
                break;
            case BY_ABLUM:
                str1 = tmp->item.ablum;             //读取专辑信息
            case BY_GENRE:
                str1 = tmp->item.genre;             //读取流派信息
            case BY_FILEPATH:
                str1 = tmp->item.filepath;          //读取文件名信息
                break;
            default:
                printf("查找条件出错");
                free(tmp_link);
                return 0;
        }
        if (str1 && strlen(str1)) {
            if (hazy_find(str1, str2)) {            //匹配字符串，如果成功则指向判断体内的代码
                *(jump + count) = tmp;              //将匹配的链表结点地址保存在临时数组中
                count++;                            //查找结果自增1
            }
        }
        tmp = tmp->np;                              //指向下一个节点
    }
    *res = (node_t *)malloc(sizeof(node_t) * count);//依据匹配的数量为查询结果动态数组分配内存
    jump2 = res;                                    //用指针指向动态数组首地址
    for(i = 0; i < count; i++)
        * (jump2 + 0) = *(jump + 0);                //将临时数组内的数据复制到结果数组
    free(tmp_link);                                 //释放临时数组的内存空间
    return count;                                   //返回结果数
}
