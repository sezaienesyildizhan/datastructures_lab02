#ifndef POLY_H
#define POLY_H

#include "PolyNode.h"

struct PolyNode* CreatePoly(char* expr);
void DeletePoly(struct PolyNode* poly);
struct PolyNode* AddNode(struct PolyNode* head, double coef, int exp);
struct PolyNode* Add(struct PolyNode* poly1, struct PolyNode* poly2);
struct PolyNode* Subtract(struct PolyNode* poly1, struct PolyNode* poly2);
struct PolyNode* Multiply(struct PolyNode* poly1, struct PolyNode* poly2);
double Evaluate(struct PolyNode* poly, double x);
struct PolyNode* Derivative(struct PolyNode* poly);
void Plot(struct PolyNode* poly, int x1, int x2);
void Print(struct PolyNode* poly);

#endif
