#ifndef LAB4_MYMAP_H
#define LAB4_MYMAP_H
#include <iostream>
namespace Map {
    template<class Key, class T>
    class MyMapIt;

    template<class Key, class Info>
    struct Node {
        Key key;
        Node *right, *left, *parent;
        Info info;

        Node() : key(Key()), right(nullptr), left(nullptr), info(Info()), parent(nullptr) {}

        Node(const Key k, const Info inf) : key(k), right(nullptr), left(nullptr), parent(nullptr) {
            info = inf;
        }

        bool operator != (Node<Key, Info> &it) const{
            return key!=it.key;
        }
        bool operator == (Node<Key, Info> &it) const{
            return key==it.key;
        }
    };

    template<class Key, class Info>
    class MyMap {
        friend class MyMapIt<Key, Info>;
    private:
        Node<Key, Info> *Root;
        void copy(Map::Node<Key, Info> *from);
        void DeleteNode(Map::Node<Key, Info> *node);
        Map::Node<Key, Info> * Minimum(Map::Node<Key, Info> *);
        void DeleteNodes(Map::Node<Key, Info> *node);
        Map::Node<Key, Info> * Maximum(Map::Node<Key, Info> *);

    public:
        MyMap(): Root(nullptr){}
        MyMap(MyMap<Key, Info> &a);
        MyMap(MyMap<Key, Info> &&a);

        int count(Map::Node<Key, Info> *x, Key num) const {
            if (x!= nullptr){
                if (x->key==num)
                    return 1;
                else if (x->key>num){
                    return count(x->left, num);
                }else if (x->key<num){
                    return count(x->right, num);
                }
            }
            return 0;
        }
        Map::Node<Key, Info> * TakeRoot() const{ return Root;}

        ~MyMap();

        const Info operator [](const Key num) const;
        void insert(Key num, Info inf);
        void RemoveElem(Key num);
        typedef MyMapIt<Key, Info> Iterator;

        Iterator begin() const{
            Map::Node<Key, Info> *x = Root;
            if (x == nullptr)
                return Iterator(x);
            while(x->left!= nullptr)
                x = x->left;
            return Iterator(x);
        }

        Iterator end() const{
            Map::Node<Key, Info> *x = Root;
            if(x == nullptr){
                return Iterator (x);
            }
            while(x->right!= nullptr)
                x = x->right;
            return Iterator(x->right);
        }
    };

    template<class Key, class Info>
    class MyMapIt{
    private:
        Node<Key, Info> *node;
    public:
        MyMapIt(Node<Key, Info> *n): node(n){}

        Node<Key, Info> * minimum(Node<Key, Info> *);

        bool operator !=(const MyMapIt<Key, Info>&) const;
        bool operator ==(const MyMapIt<Key, Info>&) const;
        Node<Key, Info>& operator *() { return *node; }
        Node<Key, Info>* operator ->(){ return node; }
        MyMapIt<Key, Info>& operator ++();
        MyMapIt<Key, Info>  operator ++(int);
    };

    template<class Key, class Info>
    Node<Key, Info> *MyMapIt<Key, Info>::minimum(Node<Key, Info> *x) {
        if (x->left== nullptr)
            return x;
        return minimum(x->left);
    }

    template<class Key, class Info>
    MyMapIt<Key, Info> &MyMapIt<Key, Info>::operator++() {
        if (node->right != nullptr) {
            node = minimum(node->right);
            return *this;
        }
        Node<Key, Info> *y = node->parent;
        while(y!= nullptr && node == y->right){
            node = y;
            y = y->parent;
        }
        node = y;
        return *this;
    }

    template<class Key, class Info>
    MyMapIt<Key, Info> MyMapIt<Key, Info>::operator++(int) {
        MyMapIt<Key, Info> res(*this);
        if (node->right != nullptr) {
            node = minimum(node->right);
            return *this;
        }
        Node<Key, Info> *y = node->parent;
        while(y!= nullptr && node == y->right){
            node = y;
            y = y->parent;
        }
        node = y;
        return res;
    }

    template<class Key, class Info>
    bool MyMapIt<Key, Info>::operator!=(const MyMapIt<Key, Info> &it) const {
        if(node == nullptr){
            if (it.node== nullptr)
                return false;
            else
                return true;
        }
        else{
            return node!=it.node;
        }
    }

    template<class Key, class Info>
    bool MyMapIt<Key, Info>::operator==(const MyMapIt<Key, Info> &it) const {
        if (node == nullptr){
            if (it.node== nullptr)
                return true;
            else
                return false;
        }else {
            return node == it.node;
        }
    }

    template<class Key, class Info>
    void MyMap<Key, Info>::insert(Key num, Info inf) {
        Map::Node<Key, Info> *x = Root;
        auto *z = new Map::Node<Key, Info>(num, inf);
        if (Root == nullptr)
            Root = z;
        while(x != nullptr){
            if (num>x->key){
                if (x->right!= nullptr)
                    x = x->right;
                else{
                    z->parent = x;
                    x->right = z;
                    break;
                }
            }else{
                if (x->left!= nullptr)
                    x = x->left;
                else{
                    z->parent = x;
                    x->left = z;
                    break;
                }
            }
        }
    }

    template<class Key, class Info>
    MyMap<Key, Info>::MyMap(MyMap<Key, Info> &a) {
        copy(a.Root);
    }

    template<class Key, class Info>
    MyMap<Key, Info>::MyMap(MyMap<Key, Info> &&a) {
        Root = a.Root;
        a.Node = nullptr;
    }

    template<class Key, class Info>
    MyMap<Key, Info>::~MyMap() {
        DeleteNodes(Root);
    }

    template<class Key, class Info>
    void MyMap<Key, Info>::copy(Map::Node <Key, Info> *from) {
        if (from!= nullptr){
            insert(from->key, from->info);
            copy(from->left);
            copy(from->right);
        }
    }

    template<class Key, class Info>
    void MyMap<Key, Info>::RemoveElem(Key num) {
        Map::Node<Key, Info> *x = Root;
        while(x!= nullptr){
            if (x->key == num){
                DeleteNode(x);
                return;
            }else if(x->key < num){
                x = x->right;
            }else if (x->key > num){
                x = x->left;
            }
        }
        throw std::runtime_error("No element with this number!");
    }

    template<class Key, class Info>
    void MyMap<Key, Info>::DeleteNode(Map::Node<Key, Info> *node) {
        Map::Node<Key, Info> *par = node->parent;
        if (node == Root){
            if (Root->right==nullptr && Root->left == nullptr) {
                Root = nullptr;
                node->right = nullptr;
                node->left = nullptr;
                node->parent = nullptr;
                delete node->info;
                delete node;
                node = nullptr;
            }
            else if (Root->right == nullptr) {
                Root = Root->left;
                Root->parent = nullptr;
                node->right = nullptr;
                node->left = nullptr;
                node->parent = nullptr;
                delete node->info;
                delete node;
                node = nullptr;
            }
            else if (Root->left == nullptr) {
                Root = Root->right;
                Root->parent = nullptr;
                node->right = nullptr;
                node->left = nullptr;
                node->parent = nullptr;
//                delete node->key;
                delete node->info;
                delete node;
                node = nullptr;
            }
            else{
                Map::Node<Key, Info> *x = Minimum(Root->right);
                Map::Node<Key, Info> *xpar = x->parent;
                if (xpar->left == x)
                    xpar->left = x->right;
                x->parent = nullptr;
                x->left = Root->left;
                if (x->left!=nullptr)
                    x->left->parent = x;
                if (Root->right != x){
                    x->right = Root->right;
                    if (x->right!=nullptr)
                        x->right->parent = x;
                }
                Root = x;
                node->right = nullptr;
                node->left = nullptr;
                node->parent = nullptr;
//                delete node->key;
                delete node->info;
                delete node;
                node = nullptr;
            }
        }else {
            if (node->right != nullptr) {
                Map::Node<Key, Info> *x = Minimum(node->right);
                Map::Node<Key, Info> *xpar = x->parent;
                if (xpar->left == x)
                    xpar->left = x->right;
                x->parent = par;
                x->left = node->left;
                if (x->left!=nullptr)
                    x->left->parent = x;
                if (node->right != x) {
                    x->right = node->right;
                    x->right->parent = x;
                }
                if (par->left == node) {
                    par->left = x;
                } else if (par->right == node) {
                    par->right = x;
                }
                node->right = nullptr;
                node->left = nullptr;
                node->parent = nullptr;
//                delete node->key;
                delete node->info;
                delete node;
                node = nullptr;
            }
            else if (node->left != nullptr){//node.right == nullptr
                Map::Node<Key, Info> *x = Maximum(node->left);
                Map::Node<Key, Info> *xpar = x->parent;
                if (xpar->right == x)
                    xpar->right = x->left;
                x->parent = par;
                x->left = node->left;
                x->left->parent = x;
                if (par->left == node) {
                    par->left = x;
                } else if (par->right == node) {
                    par->right = x;
                }
                node->left = nullptr;
                node->parent = nullptr;
//                delete node->key;
                delete node->info;
                delete node;
            } else { // node.right && node.left == nullptr
                if (par->left == node) {
                    par->left = nullptr;
                } else if (par->right == node) {
                    par->right = nullptr;
                }
                node->parent = nullptr;
//                delete node->key;
                delete node->info;
                delete node;
            }
        }
    }

    template<class Key, class Info>
    Map::Node<Key, Info> *MyMap<Key, Info>::Minimum(Map::Node<Key, Info> *x) {
        if (x->left== nullptr)
            return x;
        return Minimum(x->left);
    }

    template<class Key, class Info>
    void MyMap<Key, Info>::DeleteNodes(Map::Node<Key, Info> *node) {
        if (node!=nullptr) {
            DeleteNodes(node->left);
            DeleteNodes(node->right);
            node->right = nullptr;
            node->left = nullptr;
            node->parent = nullptr;
//            delete node->key;
            delete node->info;
            delete node;
        }
    }

    template<class Key, class Info>
    const Info MyMap<Key, Info>::operator[](const Key num) const {
        Map::Node<Key, Info> *x = Root;
        while(x!= nullptr){
            if (x->key == num){
                return x->info;
            }else if (x->key>num){
                x = x->left;
            }else if (x->key<num){
                x = x->right;
            }
        }
        return nullptr;
    }

    template<class Key, class Info>
    Node<Key, Info> *MyMap<Key, Info>::Maximum(Node<Key, Info> *x) {
        if (x->right== nullptr)
            return x;
        return Maximum(x->right);
    }

}

#endif //LAB4_MYMAP_H
