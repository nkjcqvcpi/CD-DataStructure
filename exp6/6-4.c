#include"huffman.h"

int main(){
    huffbufp buf = (huffbufp)malloc(sizeof(HuffBuf));
    int n;
    printf("n = ");scanf("%d", &n);fflush(stdin);
    char c[n], tc;
    int w[n], tw, total = 0, cnt = 0, i;
    for (i = 0;i < n;++i){
        scanf("%c %d", &tc, &tw);fflush(stdin);
        c[i] = tc;w[i] = tw;
        total += w[i];
    }
    char code[total];
    for (int i = 0;i < n;i++)
        for (int j = 0;j < w[i];j++){
            code[cnt] = c[i];cnt++;
        }

    buf->code = code;
    buf->size = total;
    huffresultp result = getHuffCodesByBuf(buf);
    puts("");
    for (int i = 0;i<n;i++)
        printf("%c : %s\n", c[i],
               result->tree->codes[(int)c[i]]->code);
    putOriginToFile(result, "hfmtree");
    
    char message[8092];
    puts("\nmessage:");gets(message);
    buf->code = message;
    buf->size = (int)strlen(message);
    huffresultp origin = getHuffCodesOfFile(buf, "hfmtree");
    printf("origin: %s\n", origin->code);

    return 0;
}
