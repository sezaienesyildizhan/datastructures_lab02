#ifndef POLYNODE_H
#define POLYNODE_H

struct PolyNode {
    double coef;
    int exp;
    struct PolyNode* next;
};

#endif