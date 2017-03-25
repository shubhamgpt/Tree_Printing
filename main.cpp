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

    template<typename T>
    int max_depth(node<T>* n)
    {
        if (!n) return 0;
        return 1 + std::max(max_depth(n->l), max_depth(n->r));
    }

    template<typename T>
    void printer(node<T>* n)
    {
        struct node_depth
        {
            node<T>* n;
            int lvl;
            node_depth(node<T>* n_, int lvl_) : n(n_), lvl(lvl_) {}
        };

        int depth = max_depth(n);

        char temp[1024];

        int last_lvl = 0;
        int offset = (1 << depth) - 1;

        std::list<node_depth> node_list;

        node_list.push_back(node_depth(n, last_lvl));

        while (node_list.size())
        {
            const node_depth& nd = *node_list.begin();

            if (last_lvl != nd.lvl)
            {
                std::cout << "\n";

                last_lvl = nd.lvl;
                offset = (1 << (depth - nd.lvl)) - 1;
            }

            if (nd.n)
            {
                sprintf(temp, " %*s%d%*s", offset, " ", nd.n->data, offset, " ");
            }

            std::cout << temp;

            if (nd.n)
            {
                node_list.push_back(node_depth(nd.n->l, last_lvl + 1));
                node_list.push_back(node_depth(nd.n->r, last_lvl + 1));
            }

        }
    }

}

int main()
{
    typedef tree::node<int> node;

    node* head = new node(1);

    head->l    = new node(1);
    head->r    = new node(1);

    head->l->l = new node(1);
    head->l->r = new node(2);
    head->r->l = new node(2);
    head->r->r = new node(1);

    tree::printer(head);

    return 0;
}