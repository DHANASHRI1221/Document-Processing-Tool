// // Do NOT add any other includes
// #include <string>
// #include <vector>
// #include <iostream>
// #include <fstream>
// using namespace std;

// class Dict
// {
// private:
//     struct Node
//     {
//         string key;
//         int height;
//         int count = 1;

//         Node *par = NULL;
//         Node *left = NULL;
//         Node *right = NULL;
//         Node(string k)
//         {
//             key = k;
//             height = 1;
//             par = NULL;
//             right = NULL;
//             left = NULL;
//         }
//     };

//     Node *root;

//     int maximum_ele(int a, int bal_nce)
//     {
//         if (a > bal_nce)
//         {
//             return a;
//         }
//         else
//         {
//             return bal_nce;
//         }
//     }
//     int height11(Node *root)
//     {
//         if (root == nullptr)
//             return -1;
//         return root->height;
//     }
//     Node *lftrot(Node *x)
//     {
//         Node *y = x->right;
//         Node *t2 = y->left;
//         x->right = t2;
//         y->left = x;

//         x->height = maximum_ele(height11(x->left), height11(x->right)) + 1;
//         y->height = maximum_ele(height11(y->left), height11(y->right)) + 1;
//         return y;
//     }

//     Node *rgtrot(Node *y)
//     {
//         Node *x = y->left;
//         Node *t2 = x->right;
//         y->left = t2;
//         x->right = y;
//         y->height = maximum_ele(height11(y->left), height11(y->right)) + 1;
//         x->height = maximum_ele(height11(x->left), height11(x->right)) + 1;
//         return x;
//     }
//     int balance_get(Node *root)
//     {
//         if (root == nullptr)
//             return 0;
//         return height11(root->left) - height11(root->right);
//     }
//     Node *insert1(Node *root, string k)
//     {
//         //cout<<"hi"<<endl;
//         if (root == nullptr)
//             return new Node(k);
//         if (k < root->key)
//         {
//             Node *next = insert1(root->left, k);
//             root->left = next;
//             next->par = root;
//         }
//         else if (k > root->key)
//         {
//             Node *next = insert1(root->right, k);

//             root->right = next;
//             next->par = root;
//         }
//         else{
//              root->count++;
//         }

//         root->height = 1 + maximum_ele(height11(root->left), height11(root->right));
//         int bal_nce = balance_get(root);
//         if (bal_nce > 1 && k < root->left->key)
//         {
//             return rgtrot(root);
//         }
//         else if (bal_nce < -1 && k > root->right->key)
//         {
//             return lftrot(root);
//         }
//         else if (bal_nce > 1 && k > root->left->key)
//         {
//             root->left = lftrot(root->left);
//             return rgtrot(root);
//         }
//         else if (bal_nce < -1 && k < root->right->key)
//         {
//             root->right = rgtrot(root->right);
//             return lftrot(root);
//         }
//         else
//             return root;

//     }
//     Node *search(string k)
//     {
//          if (root==nullptr) return nullptr;
//         Node *next = root;
//         while (next != nullptr && next->key != k)
//         {
//             if (k < next->key)
//             {
//                 next = next->left;
//             }
//             else
//             {
//                 next = next->right;
//             }
//         }
       
//         return next; 
//     }
//     // bool does_exist(string k){
//     //     //cout<<k<<endl;
//     //     if (root==nullptr) return false;
//     //      Node *next = root;
//     //     while (next != nullptr && next->key != k)
//     //     {
//     //         //cout<<k<<endl;
//     //       //  cout<<next->key<<endl;
         
//     //         if (k < next->key)
//     //         {
//     //             next = next->left;
//     //         }
//     //         else
//     //         {
//     //             next = next->right;
//     //         }
//     //     }
       
//     //     return next!=nullptr; 
//     // }
// public:
//     void insert(string k);

//     Dict();

//     ~Dict();
//     bool is_punct(char d);

//     void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

//     int get_word_count(string word);


//     void dump_dictionary1(Node* node, ofstream& mask);
//     void dump_dictionary(string filename);
// };


/* --------------------------------------------------------------------------------------- */
// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include<fstream>
using namespace std;

class Dict {
private:
    // You can add attributes/helper functions here
    struct WordCount {
    string word;
    int count;

};
 vector<WordCount> v;
  //char arr[21]={'.', ',', '-', ':', '!', '"', '\'', '(', ')', '?', '—', '[', ']', '“', '”', '‘', '’', '˙', ';', '@'};

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    int bank_code;
    int page;
    int paragraph;
    int sentence_no;
    string sentence;
    int hash1(string d);
    int hash2(string d);
    int hash_final(string d);
    void insert1(string d);
    bool does_exist(string d);
    int search(string d);
    bool is_punct(char d);
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);
    
    /*-----------------------------------------*/
};