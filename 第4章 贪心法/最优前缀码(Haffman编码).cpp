#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct Node{
    char ch;
    int value; 
    Node *left;  
    Node *right;
};

Node* Haffman(list<Node> nodes);
bool cmp(Node a, Node b);
void PrintTree(Node *root, string s);

int main()
{
    list<Node> nodes = {{'0', 5}, {'1', 5}, {'2', 10}, {'3', 15}, {'4', 25}, {'5', 10}, {'6', 10}, {'7', 20}};
    Node* root = Haffman(nodes);
    PrintTree(root, "");
    return 0;
}
bool cmp(Node a, Node b){
    return a.value < b.value;
}

//4.4.1 最优前缀码
//由于存在大量队列前端的删除、插入操作，所以选用链表
//编码结果可能不唯一，但平均最小编码长度一致
Node* Haffman(list<Node> nodes){
    nodes.sort(cmp); //list自带sort函数
    while (nodes.size()>=2){
        //取出最小的两个节点
        Node *n1 = new Node(nodes.front()); //此处有大坑。必须新建对象，否则会造成重复使用同一块地址
        nodes.pop_front();
        Node *n2 = new Node(nodes.front());
        nodes.pop_front();
        //生成新节点
        Node *node = new Node();
        node->value = n1->value + n2->value;
        node->left = n1;
        node->right = n2;
        //插入链表中
        list<Node>::iterator it;
        for (it=nodes.begin(); it!=nodes.end(); ++it){
            if (node->value <= it->value){
                nodes.insert(it, *node);
                break;
            }
        }
        if (it==nodes.end()){
            nodes.insert(it, *node);
        }
    }
    Node *root = &nodes.front();
    return root;
}

void PrintTree(Node *root, string s){
    if (root->left==NULL){
        cout << root->ch << ": " << s << endl;
    }
    else{
        PrintTree(root->left, s + '0'); //注意是s+'0'不是'0'+s！往后面依次加字符
        PrintTree(root->right, s + '1');
    }
}
