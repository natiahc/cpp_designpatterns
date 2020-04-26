#include <iostream>
#include <string>
#include <vector>

template<typename T> struct BinaryTree;


template<typename T> struct Node
{
    T value = T();
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    Node<T>* parent = nullptr;
    BinaryTree<T>* tree = nullptr;

    explicit Node(const T& value)
        : value(value)
    {}

    ~Node()
    {
        if(left) delete left;
        if(right) delete right;
    }

    Node(const T& value, Node<T>* const left, Node<T>* const right)
        : value{value},
          left{left},
          right{right}
    {
        this->left->parent = this->right->parent = this;
    }

    void setTree(BinaryTree<T>* t)
    {
        tree = t;
        if(left) left->setTree(t);
        if(right) right->setTree(t);
    }
};

template<typename T> struct BinaryTree
{
    Node<T>* root = nullptr;

    template<typename U>
    struct BinaryTreeIterator
    {
        Node<U>* current;

        explicit BinaryTreeIterator(Node<U>* const current)
            : current{current}
        {}

        bool operator!=(const BinaryTreeIterator<U>& other)
        {
            return current != other.current;
        }

        Node<U>& operator*() 
        {
            return *current;
        }

        BinaryTreeIterator<U>& operator++()
        {
            if(current->right)
            {
                current = current->right;
                while(current->left)
                    current = current->left;
            }
            else
            {
                Node<T>* p = current->parent;
                while(p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }

                current = p;
            }

            return *this;            
        }
    };

    using Iterator = BinaryTreeIterator<T>;

    explicit BinaryTree(Node<T>* const root)
        : root{root}
    {
        root->setTree(this);
    }

    ~BinaryTree()
    {
        if(root) delete root;
    }

    Iterator end()
    {
        return Iterator{nullptr};
    }

    Iterator begin()
    {
        Node<T>* n = root;
        
        if(n)
            while(n->left)
                n = n->left;
            
        return Iterator{n};
    }
};

int main()
{
    BinaryTree<std::string> family {
        new Node<std::string>{"me", new Node<std::string>{"mother",
            new Node<std::string>{"mothers mother"},
            new Node<std::string>{"mothers father"}
        },
        new Node<std::string>{"father"}
    }  
    };

    for (auto it = family.begin(); it != family.end(); ++it)
    {
        std::cout << (*it).value << std::endl;
    }

    return 0;
}