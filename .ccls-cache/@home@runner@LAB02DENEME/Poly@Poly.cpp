#include "Poly.h"
#include <cmath>
#include <cstring>
#include <iostream>

struct PolyNode *CreatePoly(char *expr) {
  struct PolyNode *head = nullptr;

  char *term = strtok(expr, " ");
  while (term != nullptr) {
    double coef;
    int exp;
    std::sscanf(term, "%lfx^%d", &coef, &exp);

    head = AddNode(head, coef, exp);
    term = strtok(nullptr, " ");
  }

  return head;
}

void DeletePoly(struct PolyNode *poly) {
  struct PolyNode *current = poly;
  while (current != nullptr) {
    struct PolyNode *next = current->next;
    delete current;
    current = next;
  }
}

struct PolyNode *AddNode(struct PolyNode *head, double coef, int exp) {
  struct PolyNode *newNode = new struct PolyNode;
  newNode->coef = coef;
  newNode->exp = exp;
  newNode->next = nullptr;

  if (head == nullptr) {
    return newNode;
  }

  struct PolyNode *current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  current->next = newNode;

  return head;
}

struct PolyNode *Add(struct PolyNode *poly1, struct PolyNode *poly2) {
  struct PolyNode *result = nullptr;
  struct PolyNode *current1 = poly1;
  struct PolyNode *current2 = poly2;
  struct PolyNode *currentResult = nullptr;

  while (current1 != nullptr || current2 != nullptr) {
    double coef1 = (current1 != nullptr) ? current1->coef : 0;
    int exp1 = (current1 != nullptr) ? current1->exp : -1;

    double coef2 = (current2 != nullptr) ? current2->coef : 0;
    int exp2 = (current2 != nullptr) ? current2->exp : -1;

    if (exp1 == exp2) {
      double sum = coef1 + coef2;
      if (sum != 0) {
        result = AddNode(result, sum, exp1);
        if (currentResult == nullptr) {
          currentResult = result;
        }
      }
      current1 = current1->next;
      current2 = current2->next;
    } else if (exp1 > exp2) {
      result = AddNode(result, coef1, exp1);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current1 = current1->next;
    } else {
      result = AddNode(result, coef2, exp2);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current2 = current2->next;
    }
  }

  return result;
}

struct PolyNode *Subtract(struct PolyNode *poly1, struct PolyNode *poly2) {
  struct PolyNode *result = nullptr;
  struct PolyNode *current1 = poly1;
  struct PolyNode *current2 = poly2;
  struct PolyNode *currentResult = nullptr;

  while (current1 != nullptr || current2 != nullptr) {
    double coef1 = (current1 != nullptr) ? current1->coef : 0;
    int exp1 = (current1 != nullptr) ? current1->exp : -1;

    double coef2 = (current2 != nullptr) ? current2->coef : 0;
    int exp2 = (current2 != nullptr) ? current2->exp : -1;

    if (exp1 == exp2) {
      double diff = coef1 - coef2;
      if (diff != 0) {
        result = AddNode(result, diff, exp1);
        if (currentResult == nullptr) {
          currentResult = result;
        }
      }
      current1 = current1->next;
      current2 = current2->next;
    } else if (exp1 > exp2) {
      result = AddNode(result, coef1, exp1);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current1 = current1->next;
    } else {
      result = AddNode(result, -coef2, exp2);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current2 = current2->next;
    }
  }

  return result;
}

struct PolyNode *Multiply(struct PolyNode *poly1, struct PolyNode *poly2) {
  struct PolyNode *result = nullptr;

  struct PolyNode *current1 = poly1;
  while (current1 != nullptr) {
    struct PolyNode *current2 = poly2;
    while (current2 != nullptr) {
      double coef = current1->coef * current2->coef;
      int exp = current1->exp + current2->exp;
      result = AddNode(result, coef, exp);
      current2 = current2->next;
    }
    current1 = current1->next;
  }

  return result;
}

double Evaluate(struct PolyNode *poly, double x) {
  double result = 0.0;

  struct PolyNode *current = poly;
  while (current != nullptr) {
    result += current->coef * pow(x, current->exp);
    current = current->next;
  }

  return result;
}

struct PolyNode *Derivative(struct PolyNode *poly) {
  struct PolyNode *result = nullptr;

  struct PolyNode *current = poly;
  while (current != nullptr) {
    if (current->exp > 0) {
      double coef = current->coef * current->exp;
      int exp = current->exp - 1;
      result = AddNode(result, coef, exp);
    }
    current = current->next;
  }

  return result;
}

void Plot(struct PolyNode *poly, int x1, int x2) {
  std::cout << "Plot of the function ";

  Print(poly);

  for (int y = 12; y >= -12; y--) {
    for (int x = x1; x <= x2; x++) {
      double result = Evaluate(poly, x);
      if (round(result) == y) {
        if (x == 0 && y == 0) {
          std::cout << "O ";
        } else if (x == 0) {
          std::cout << "| ";
        } else if (y == 0) {
          std::cout << "- ";
        } else {
          std::cout << "* ";
        }
      } else if (x == 0 && y == 0) {
        std::cout << "+ ";
      } else if (x == 0) {
        std::cout << "| ";
      } else if (y == 0) {
        std::cout << "- ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

void Print(PolyNode *poly) {
  if (poly == nullptr) {
    std::cout << "<NULL>\n";
    return;
  }

  PolyNode *p = poly;
  while (p != nullptr) {
    if (p->exp == 0) {
      std::cout << p->coef;
    } else if (p->exp == 1) {
      if (p->coef == 1.0)
        std::cout << "+x ";
      else if (p->coef == -1.0)
        std::cout << "-x ";
      else
        std::cout << p->coef << "x ";
    } else {
      if (p->coef == 1.0)
        std::cout << "+x^" << p->exp << " ";
      else if (p->coef == -1.0)
        std::cout << "-x^" << p->exp << " ";
      else
        std::cout << p->coef << "x^" << p->exp << " ";
    }

    p = p->next;
  }

  std::cout << ">\n";
}

void Test1() {
  std::cout << "******TEST1******\n";

  struct PolyNode *poly = nullptr;
  std::cout << "Initial poly: ";
  Print(poly);

  poly = AddNode(poly, -2, 5);
  std::cout << "Adding -2x^5: ";
  Print(poly);

  poly = AddNode(poly, 4.4, 7);
  std::cout << "Adding 4.4x^7: ";
  Print(poly);

  poly = AddNode(poly, 2, 3);
  std::cout << "Adding 2x^3: ";
  Print(poly);

  poly = AddNode(poly, 1, 4);
  std::cout << "Adding x^4: ";
  Print(poly);

  poly = AddNode(poly, 4, 4);
  std::cout << "Adding 4x^4: ";
  Print(poly);

  poly = AddNode(poly, 2, 5);
  std::cout << "Adding 2x^5: ";
  Print(poly);

  poly = AddNode(poly, -4.4, 7);
  std::cout << "Adding 4.4x^7: ";
  Print(poly);

  poly = AddNode(poly, -2, 3);
  std::cout << "Adding -2x^3: ";
  Print(poly);

  poly = AddNode(poly, -5, 4);
  std::cout << "Adding -5x^4: ";
  Print(poly);

  DeletePoly(poly);
}

// Add more test functions if needed

int main() {
  Test1();
  // Add calls to other test functions if needed

  return 0;
}
