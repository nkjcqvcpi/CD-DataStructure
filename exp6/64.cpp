#define LEN 512
struct huffman_node{
        char c;
        int weight;
        char huffman_code[LEN];
        huffman_node * left;
        huffman_node * right;
};

int huffman_tree_create(huffman_node *&root, map<char, int> &word){
        char line[MAX_LINE];
        vector<huffman_node *> huffman_tree_node;

        map<char, int>::iterator it_t;
        for (it_t = word.begin(); it_t != word.end(); it_t++){
                // 为每一个节点申请空间
                huffman_node *node = (huffman_node *)malloc(sizeof(huffman_node));
                node->c = it_t->first;
                node->weight = it_t->second;
                node->left = NULL;
                node->right = NULL;
                huffman_tree_node.push_back(node);
        }


        // 开始从叶节点开始构建Huffman树
        while (huffman_tree_node.size() > 0){
                // 按照weight升序排序
                sort(huffman_tree_node.begin(), huffman_tree_node.end(), sort_by_weight);
                // 取出前两个节点
                if (huffman_tree_node.size() == 1){// 只有一个根结点
                        root = huffman_tree_node[0];
                        huffman_tree_node.erase(huffman_tree_node.begin());
                }else{
                        // 取出前两个
                        huffman_node *node_1 = huffman_tree_node[0];
                        huffman_node *node_2 = huffman_tree_node[1];
                        // 删除
                        huffman_tree_node.erase(huffman_tree_node.begin());
                        huffman_tree_node.erase(huffman_tree_node.begin());
                        // 生成新的节点
                        huffman_node *node = (huffman_node *)malloc(sizeof(huffman_node));
                        node->weight = node_1->weight + node_2->weight;
                        (node_1->weight < node_2->weight)?(node->left=node_1,node->right=node_2):(node->left=node_2,node->right=node_1);
                        huffman_tree_node.push_back(node);
                }
        }

        return 0;
}

int read_file(FILE *fn, map<char, int> &word){
        if (fn == NULL) return 1;
        char line[MAX_LINE];
        while (fgets(line, 1024, fn)){
                fprintf(stderr, "%s\n", line);
                //解析，统计词频
                char *p = line;
                while (*p != '\0' && *p != '\n'){
                        map<char, int>::iterator it = word.find(*p);
                        if (it == word.end()){// 不存在，插入
                                word.insert(make_pair(*p, 1));
                        }else{
                                it->second ++;
                        }
                        p ++;
                }
        }
        return 0;
}

void print_huffman_pre(huffman_node *node){
        if (node != NULL){
                fprintf(stderr, "%c\t%d\n", node->c, node->weight);
                print_huffman_pre(node->left);
                print_huffman_pre(node->right);
        }
}

void print_huffman_in(huffman_node *node){
        if (node != NULL){
                print_huffman_in(node->left);
                fprintf(stderr, "%c\t%d\n", node->c, node->weight);
                print_huffman_in(node->right);
        }
}

int get_huffman_code(huffman_node *&node){
        if (node == NULL) return 1;
        // 利用层次遍历，构造每一个节点
        huffman_node *p = node;
        queue<huffman_node *> q;
        q.push(p);
        while(q.size() > 0){
                p = q.front();
                q.pop();
                if (p->left != NULL){
                        q.push(p->left);
                        strcpy((p->left)->huffman_code, p->huffman_code);
                        char *ptr = (p->left)->huffman_code;
                        while (*ptr != '\0'){
                                ptr ++;
                        }
                        *ptr = '0';
                }
                if (p->right != NULL){
                        q.push(p->right);
                        strcpy((p->right)->huffman_code, p->huffman_code);
                        char *ptr = (p->right)->huffman_code;
                        while (*ptr != '\0'){
                                ptr ++;
                        }
                        *ptr = '1';
                }
        }


        return 0;
}
