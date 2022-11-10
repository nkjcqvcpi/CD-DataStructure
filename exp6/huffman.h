//
//  HUFFMAN.h
//  6-4
//
//  Created by Houtong Lei on 2021/5/19.
//

#ifndef HUFFMAN_h
#define HUFFMAN_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MacTypes.h>

#define toByte(n) ((n) / 8 + ((n) % 8 > 0))

typedef struct HuffListNode HuffListNode,*hufflistnodep;
typedef struct HuffNode HuffNode,*huffnodep;
typedef struct HuffTree HuffTree,*hufftreep;
typedef struct HuffCode HuffCode,*huffcodep;
typedef struct HuffList HuffList,*hufflistp;
typedef struct HuffResult HuffResult,*huffresultp;
typedef struct HuffCode HuffBuf,*huffbufp;  //缓存类型

struct HuffListNode{
    huffnodep node;
    hufflistnodep next;
};

struct HuffList{
    hufflistnodep head;
    int keys[256];
    int size;
};

struct HuffNode{
    int key;
    int weight;
    huffnodep left;
    huffnodep right;
};

struct HuffCode{
    char* code;
    int size;
};

struct HuffTree{
    huffnodep root;
    huffcodep codes[256];
    int size;
};

struct HuffResult{
    char* code;
    hufftreep tree;
};

hufflistp getHuffListByBuf(huffbufp buf);
huffbufp str2bin(char* str);
char* bin2str(huffbufp buf);
huffbufp readHuffFile(const char* filename);
int putOriginToFile(huffresultp result,const char* filename);
huffresultp getHuffCodesByBuf(huffbufp buf);
huffresultp getHuffCodesOfFile(huffbufp buf, const char *filename);
huffcodep getHuffCode(hufftreep tree,int key);
hufftreep hufftree(hufflistp list);
huffnodep huffnode(int key,int weight);
hufflistp hufflist(void);
Boolean insertHuffNode(hufflistp list,huffnodep node);
huffnodep shiftHuffNode(hufflistp list);
hufftreep genhuffcodes(hufftreep tree,huffnodep node,char codes[],int idx);

#endif /* HUFFMAN_h */
