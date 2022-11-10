//
//  HUFFMAN.c
//  6-4
//
//  Created by Houtong Lei on 2021/5/19.
//

#include "huffman.h"

huffnodep huffnode(int key,int weight){
    huffnodep ret = (huffnodep)malloc(sizeof(HuffNode));
    ret->key = key;
    ret->weight = weight;
    ret->left = ret->right = NULL;
    return ret;
}

hufflistp hufflist(void){
    hufflistp ret = (hufflistp)malloc(sizeof(HuffList));
    ret->head = NULL;
    memset(ret->keys,0,sizeof(ret->keys[0])*256);
    ret->size = 0;
    return ret;
}

Boolean insertHuffNode(hufflistp list,huffnodep node){
    if(list == NULL || node == NULL || node->weight <= -256) return FALSE;
    hufflistnodep cur = list->head;
    hufflistnodep* rootp = &(list->head);
    hufflistnodep* last = NULL;
    hufflistnodep tmp = (hufflistnodep)malloc(sizeof(HuffListNode));
    tmp->node = node;
    tmp->next = NULL;
    if(node->key >= 0 && node->key < 256){
        list->keys[node->key] = node->weight;
    }
    list->size++;
    for(;cur != NULL  && cur->node->weight < node->weight; cur = cur->next){
        last = rootp;
        rootp = &(cur->next);
    }
    tmp->next = cur;
    if(last == NULL){
        list->head = tmp;
    }else{
        (*last)->next = tmp;
    }
    return TRUE;
}

huffnodep shiftHuffNode(hufflistp list){
    if(list == NULL || list->head == NULL) return NULL;
    huffnodep ret = list->head->node;
    hufflistnodep next = list->head->next;
    free(list->head);
    list->head = next;
    list->size--;
    return ret;
}

hufftreep hufftree(hufflistp list){
    hufftreep tree = (hufftreep)malloc(sizeof(HuffTree));
    tree->root = NULL;
    tree->size = 0;
    memset(tree->codes,0,sizeof(tree->codes));
    huffnodep a = NULL;
    huffnodep b = NULL;
    huffnodep c = NULL;
    tree->size = 2 * list->size - 1;
    while(list->size > 1){
        a = shiftHuffNode(list);
        b = shiftHuffNode(list);
        c = huffnode(-256,a->weight+b->weight);
        c->left = a;
        c->right = b;
        insertHuffNode(list,c);
    }
    tree->root = c;
    char codes[8092];
    return genhuffcodes(tree,tree->root,codes,0);
}

hufftreep genhuffcodes(hufftreep tree,huffnodep node,char codes[],int idx){
    if(tree == NULL || node == NULL) return NULL;

    if(node->left == NULL && node->right == NULL){
        int key = node->key;
        huffcodep code = (huffcodep)malloc(sizeof(HuffCode));
        code->code = (char*)malloc(idx+1);
        code->size = idx;
        memcpy(code->code,codes,code->size);
        code->code[code->size] = '\0';
        tree->codes[key] = code;
    }{
        codes[idx] = '1';
        genhuffcodes(tree,node->right,codes,idx+1);
        codes[idx] = '0';
        genhuffcodes(tree,node->left,codes,idx+1);
    }
    return tree;
}

hufflistp getHuffListByBuf(huffbufp buf){
    if(buf == NULL || buf->code == NULL) return NULL;
    char* code = buf->code;
    hufflistp list = hufflist();
    for(int i = 0; code[i] != '\0'; i++){
        unsigned char ch = code[i];
        list->keys[ch]++;
    }
    for(int i = 0; i < 256; i++){
        if(list->keys[i] > 0){
            insertHuffNode(list,huffnode(i,list->keys[i]));
        }
    }
    return list;
}

huffcodep getHuffCode(hufftreep tree,int key){
    if(key < 256 && key >= 0 && tree->codes[key] > 0){
        return tree->codes[key];
    }
    return NULL;
}

huffresultp getHuffCodesByBuf(huffbufp buf){
    huffresultp result = (huffresultp)malloc(sizeof(HuffResult));
    result->code = NULL;
    if(buf == NULL) return NULL;
    hufflistp list = getHuffListByBuf(buf);
    result->tree = hufftree(list);
    int buf_len = buf->size;
    int len = 0;
    for(int i = 0; buf->code[i] != '\0'; i++){
        int key = (unsigned char)buf->code[i];
        huffcodep code = getHuffCode(result->tree,key);
        if(code == NULL){
            printf("LLL:%c{%d}\n",key,key);
            return NULL;
        }
        len+=code->size;
    }
    result->code = (char*)malloc(len+1);
    result->code[0] = '\0';
    for(int i = 0; buf->code[i] != '\0'; i++){
        unsigned char key = buf->code[i];
        huffcodep code = getHuffCode(result->tree,key);
        strncat(result->code,code->code,code->size);
    }
    return result;
}

huffresultp getHuffCodesOfFile(huffbufp buf, const char *filename){
    huffresultp result = (huffresultp)malloc(sizeof(HuffResult));
    result->code = NULL;
    if(buf == NULL) return NULL;
    hufflistp list = getHuffListByBuf(readHuffFile(filename));
    result->tree = hufftree(list);
    int buf_len = buf->size;
    int len = 0;
    for(int i = 0; buf->code[i] != '\0'; i++){
        int key = (unsigned char)buf->code[i];
        huffcodep code = getHuffCode(result->tree,key);
        if(code == NULL){
            printf("LLL:%c{%d}\n",key,key);
            return NULL;
        }
        len+=code->size;
    }
    result->code = (char*)malloc(len+1);
    result->code[0] = '\0';
    for(int i = 0; buf->code[i] != '\0'; i++){
        unsigned char key = buf->code[i];
        huffcodep code = getHuffCode(result->tree,key);
        strncat(result->code,code->code,code->size);
    }
    return result;
}

int putOriginToFile(huffresultp result,const char* filename){
    if(result == NULL) return 0;
    huffbufp buf = str2bin(result->code);
    int i = 0;
    int len = 0;
    for(i = 0; i < 256; i++){
        if(result->tree->codes[i] > 0){
            len+= 5+result->tree->codes[i]->size;
        }
    }
    huffbufp keys = (huffbufp)malloc(sizeof(HuffBuf));
    keys->code = (char*)malloc(len);
    keys->size = 0;
    int idx = 0;
    for(i = 0; i < 256; i++){
        if(result->tree->codes[i] > 0){ //
            keys->code[idx++] = i;    //key
            int len = result->tree->codes[i]->size;
            memcpy(keys->code+idx,&len,4);    //key size
            // printf("%c[%d]:%d{%s}\n",i,i,len,result->tree->codes[i]->code);
            idx+=4;
            huffbufp tmp = str2bin(result->tree->codes[i]->code);
            // printf("%d,%d\n",tmp->code[0],tmp->size);
            int tsize = toByte(tmp->size);
            memcpy(keys->code+idx,tmp->code,tsize);
            idx+=tsize;
        }
    }

    keys->size = idx;
    FILE* fp = fopen(filename,"w");
    if(fp == NULL) return -1;
    fwrite("HUF\n",1,4,fp);
    fwrite(&idx,1,4,fp);    //size
    fwrite(keys->code,1,keys->size,fp); //写入code
    fwrite(&(buf->size),1,4,fp);    //size
    fwrite(buf->code,1,toByte(buf->size),fp);
    fclose(fp);
    return 4+4+keys->size+4+buf->size;
}


huffbufp str2bin(char* str){
    if(str == NULL) return NULL;
    huffbufp buf = (huffbufp)malloc(sizeof(HuffBuf));
    int l = (int)strlen(str);
    int size = (l / 8) + (l % 8 > 0);
    buf->code = (char*)malloc(l);
    memset(buf->code,0,l);
    for(int i = 0; i < l; i++){
        int idx = i/8;
        int bi = i%8;
        buf->code[idx] |= (str[i] == '0' ? 0:1) << bi;
    }
    buf->size = l;
    return buf;
}

char* bin2str(huffbufp buf){
    char* ret = (char*)malloc(buf->size+1);
    for(int i = 0; i < buf->size; i++){
        int idx = i / 8;
        int offset = i % 8;
        ret[i] = (buf->code[idx] & (0x01 << offset)) ? '1' : '0';
    }
    ret[buf->size] = '\0';
    return ret;
}

huffbufp readHuffFile(const char* filename){
    FILE* fp = fopen(filename,"r");
    if(fp == NULL) return NULL;
    fseek(fp,0L,SEEK_END);
    int len = (int)ftell(fp);
    rewind(fp);
    huffbufp ret = (huffbufp)malloc(sizeof(HuffBuf));
    ret->code = (char*)malloc(len+1);
    ret->size = len;
    fread(ret->code,1,len,fp);
    fclose(fp);
    huffbufp buf =  ret;
    if(buf == NULL) return NULL;
    if(memcmp(buf->code,"HUF\n",4) != 0) return NULL;
    huffresultp result = (huffresultp)malloc(sizeof(HuffResult));
    int key_size = *(int*)(buf->code+4);
    int base = 8;
    hufftreep tree = (hufftreep)malloc(sizeof(HuffTree));
    tree->root = NULL;
    tree->size = 0;
    huffcodep* codes = tree->codes;
    memset(codes,0,sizeof(huffcodep)*256);
    int oft = 0;
    for(;oft < key_size;){
        int offset = base+oft;
        unsigned char key = buf->code[offset];
        int size = *(int*)(buf->code+offset+1); //长度
        int byte = toByte(size);
        huffbufp htmp = (huffbufp)malloc(sizeof(HuffBuf));
        htmp->code = buf->code+offset+5;
        htmp->size = size;
        huffcodep tmp = (huffcodep)malloc(sizeof(HuffCode));
        tmp->size = size;
        tmp->code = bin2str(htmp);
        tree->codes[key] = tmp;
        tree->size++;
        huffnodep root = tree->root;
        if(root == NULL){
            tree->root = huffnode(-256,0);
            root = tree->root;
        }
        for(int i = 0; i < tmp->size; i++){
            char ch = tmp->code[i];
            huffnodep node = NULL;
            if(ch == '0'){
                node = root->left;
                if(node == NULL) node = huffnode(-256,0);
                root->left = node;
            }else{
                node = root->right;
                if(node == NULL) node = huffnode(-256,0);
                root->right = node;
            }
            if(i == tmp->size - 1) node->key = key;
            root = node;
        }
        oft+=5+byte;
    }
    huffbufp tmp = (huffbufp)malloc(sizeof(HuffBuf));
    tmp->code = buf->code+base+oft+4;
    tmp->size = *(int*)(buf->code+base+oft);
    result->tree = tree;
    result->code = bin2str(tmp);
    if(result == NULL || result->code == NULL || result->tree == NULL) return NULL;
    hufftreep rtree = result->tree;
    char* code = result->code;
    int rlen = 0;
    for(int i = 0; code[i] != '\0';){
        huffnodep root = rtree->root;
        while(root->left != NULL && root->right != NULL && code[i] != '\0'){
            root = (code[i] == '0' ? root->left : root->right);
            i++;
        }
        if((root->left != NULL || root->right != NULL) && code[i] == '\0')
            return NULL;
        rlen++;
    }
    huffbufp rret = (huffbufp)malloc(sizeof(HuffBuf));
    rret->code = (char*)malloc(rlen+1);
    rret->code[0] = '\0';
    rret->size = rlen;
    int idx = 0;
    for(int i = 0; code[i] != '\0';){
        huffnodep root = rtree->root;
        while(root->left != NULL && root->right != NULL && code[i] != '\0'){
            root = (code[i] == '0' ? root->left : root->right);
            i++;
        }
        rret->code[idx++] = root->key;
    }
    rret->code[idx] = '\0';
    return rret;
}
