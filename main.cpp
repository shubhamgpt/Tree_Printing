#include <iostream>
#include <utility>
#include <algorithm>
#include <list>

namespace tree {

    template<typename T>
    struct node
    {
        T data;
        node* l;
        node* r;
        node(T&& data_ = T()) : data(std::move(data_)), l(0), r(0) {}
    };

}

int main()
{
    typedef tree::node<int> node;

    node* head = new node(1);

    head->l    = new node(1);
    head->r    = new node(1);

    return 0;
}