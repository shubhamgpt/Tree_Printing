#include <iostream>
#include <utility>
#include <algorithm>
#include <list>
#include <vector>
#include <math.h>

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
            else
            {
                sprintf(temp, " %*s", offset << 1, " ");
            }

            std::cout << temp;

            if (nd.n)
            {
                node_list.push_back(node_depth(nd.n->l, last_lvl + 1));
                node_list.push_back(node_depth(nd.n->r, last_lvl + 1));
            }

            node_list.pop_front();
        }
    }

}

int main()
{
    typedef tree::node<int> node;

    node* head = new node(1);
    //node* temp, temp_l, temp_r;


    int in_height;

    std::vector<int> nodeVecTemp1, nodeVecTemp2, nodeVector;

    std::cin >> in_height;

    if(in_height == 0)
    {
        std::cout << "Error: Input should be more than zero!!" << std::endl;
        return 0;
    }
    else if(in_height >= 1)
    {
        nodeVecTemp1.push_back(1);

        for(int j=1; j<=in_height; j++) {   //iterate over levels

            for (int i = 0; i < pow(2, double(j - 1)); i++) {   //iterate in level for each value

                if (i % 2 == 0) {   //check for i'th is position value is even/odd
                    if(i == 0)  //check for left boundary
                        nodeVecTemp2.push_back((nodeVecTemp1[i]));
                    else
                        nodeVecTemp2.push_back((nodeVecTemp1[i-1] + nodeVecTemp1[i-2]));
                }
                else {
                    if(i == (pow(2, double(j - 1))-1))  //check for right boundary
                        nodeVecTemp2.push_back((nodeVecTemp1[i-1]));
                    else
                        nodeVecTemp2.push_back((nodeVecTemp1[i-1] + nodeVecTemp1[i]));
                }

            }
            for(int k=0; k<nodeVecTemp2.size();k++) {
                nodeVector.push_back(nodeVecTemp2[k]);  //passing values to master array
            }
            nodeVecTemp1 = nodeVecTemp2;    //shifting temp1 to next level of temp2
            nodeVecTemp2.clear();   //cleaning temp2 to create next level
        }
    }

//    for(int i=0; i<nodeVecTemp2.size();i++) {
//        nodeVector.push_back(nodeVecTemp2[i]);
//    }

    std::cout<<"size= "<<nodeVector.size()<<std::endl;

    for(int i=0; i<nodeVector.size();i++){
        std::cout << nodeVector[i] << " ";
    }
    std::cout<<std::endl;


    head->l    = new node(1);
    head->r    = new node(1);

    head->l->l = new node(1);
    head->l->r = new node(2);
    head->r->l = new node(2);
    head->r->r = new node(1);

    head->l->l->l = new node(1);
    head->l->l->r = new node(3);
    head->l->r->l = new node(3);
    head->l->r->r = new node(4);
    head->r->l->l = new node(4);
    head->r->l->r = new node(3);
    head->r->r->l = new node(3);
    head->r->r->r = new node(1);

    tree::printer(head);

    return 0;
}