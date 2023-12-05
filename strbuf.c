#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct strbuf
{
    int len;
    int alloc;
    char *buf;
};

//Part 2A
void strbuf_init(struct strbuf *sb, size_t alloc){
    sb->len = 0;
    sb->alloc = alloc;
    sb->buf = (char*)malloc(sizeof(char)*alloc);
}

void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    sb->alloc = alloc;
    sb->len = len;
    sb->buf = (char*)str;
}

void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);
}

void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    char *temp;
    int cnt;

    //先交换容量与长度
    cnt = a->len;
    a->len = b->len;
    b->len = cnt;
    cnt = a->alloc;
    a->alloc = b->alloc;
    b->alloc = cnt;

    temp = a->buf;
    a->buf =b->buf;
    b->buf = temp;

}

char *strbuf_detach(struct strbuf *sb, size_t *sz){
    char *source;
    source = sb->buf;
    *sz = sb->alloc;
    return source; 
}

int strbuf_cmp(const struct strbuf *first, const struct strbuf *second){
    if(first->len == second->len)
        return memcmp(first->buf,second->buf,first->len);
    else 
        return 1;
}

void strbuf_reset(struct strbuf *sb)
{
    memset(sb->buf,0,sb->len);
    sb->len = 0;
}

//Part 2B
void strbuf_grow(struct strbuf *sb, size_t extra){
    if(sb->len + extra > sb->alloc){
        sb->buf = (char*)realloc(sb->buf,(sb->alloc)*2);
        sb->alloc = sb->len + extra;
    }
    else 
        return;
}

void strbuf_add(struct strbuf *sb, const void *data, size_t len){
    if(data == NULL)
        return;
    while(sb->len + len >= sb->alloc){
        sb->alloc *= 2;
        sb->buf = (char*)realloc(sb->buf,sb->alloc);
        
    }
    //strncat(sb->buf,(char*)data,len);
    memcpy(sb->buf + sb->len,data,len);//将缓冲指针向后移动sb->len个字节，确保不覆盖原来的数据
    sb->len += len;
    sb->buf[sb->len] = '\0';
    
}

void strbuf_addch(struct strbuf *sb, int c){
    if(sb->len + 2 >= sb->alloc){
        sb->buf = (char*)realloc(sb->buf,(sb->alloc)*2);
        sb->alloc *= 2;
    }
    sb->buf[sb->len] = c;
    sb->len++;
    sb->buf[sb->len] = '\0';

}

void strbuf_addstr(struct strbuf *sb, const char *s){
    int len = strlen(s);
    strbuf_add(sb,s,len);

}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2){
    while(sb->len + sb2->len >= sb->alloc){
        sb->buf = (char*)realloc(sb->buf,(sb->alloc)*2);
        sb->alloc *= 2;
    } 
    strcpy(sb->buf + sb->len,sb2->buf);
    sb->len += sb2->len;
    
}

void strbuf_setlen(struct strbuf *sb, size_t len){
    sb->len = len;
    sb->buf[sb->len] = '\0';

}

size_t strbuf_avail(const struct strbuf *sb){
    int remain = sb->alloc - sb->len - 1;
    return remain;

}


void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len){
    while(sb->len + len >= sb->alloc){
        sb->buf = (char*)realloc(sb->buf,(sb->alloc)*2);
        sb->alloc *= 2;
    }
    memmove(sb->buf + (pos + len),sb->buf + pos,sb->len - pos);
    memcpy(sb->buf + pos,data,len);
    sb->len += len;
    sb->buf[sb->len] = '\0';

}

