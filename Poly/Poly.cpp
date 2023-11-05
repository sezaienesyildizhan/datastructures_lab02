#include "Poly.h"
#include <cmath>            
#include <cstring>           
#include <iostream>   

/* 152120211042 Sezai Enes YILDIZHAN
   152120211053 Mehmet Ayberk GÜNEŞ
   
   We do not sure our codes work correctly but the task is very complicated and we did everything we could. */

// Define a structure named PolyNode for representing polynomial terms.
struct PolyNode *CreatePoly(char *expr) {
  struct PolyNode *head = nullptr;  // Initialize a pointer to the head of the polynomial as nullptr.

  // Tokenize the input expression using space as a delimiter.
  char *term = strtok(expr, " ");
  while (term != nullptr) {
    double coef;
    int exp;

    // Parse the term using sscanf, expecting the format "coefx^exp".
    std::sscanf(term, "%lfx^%d", &coef, &exp);

    // Add the parsed term to the polynomial.
    head = AddNode(head, coef, exp);
    term = strtok(nullptr, " ");
  }

  return head;  // Return a pointer to the head of the created polynomial.
}

// Function to delete a polynomial and free memory.
void DeletePoly(struct PolyNode *poly) {
  struct PolyNode *current = poly;
  while (current != nullptr) {
    struct PolyNode *next = current->next;
    delete current;  // Delete the current polynomial term.
    current = next;  // Move to the next term.
  }
}

// Add a new polynomial term to the existing polynomial.
struct PolyNode *AddNode(struct PolyNode *head, double coef, int exp) {
  struct PolyNode *newNode = new struct PolyNode;  // Create a new polynomial term.
  newNode->coef = coef;  // Set the coefficient of the term.
  newNode->exp = exp;    // Set the exponent of the term.
  newNode->next = nullptr;  // Initialize the next pointer as nullptr.

  if (head == nullptr) {
    return newNode;  // If the polynomial is empty, the new term becomes the head.
  }

  struct PolyNode *current = head;
  while (current->next != nullptr) {
    current = current->next;  // Traverse the existing polynomial to find the last term.
  }
  current->next = newNode;  // Add the new term to the end of the polynomial.

  return head;  // Return the updated polynomial.
}

// Add two polynomials and return the result.
struct PolyNode *Add(struct PolyNode *poly1, struct PolyNode *poly2) {
  struct PolyNode *result = nullptr;  // Initialize the result polynomial.
  struct PolyNode *current1 = poly1;  // Initialize current pointers for poly1 and poly2.
  struct PolyNode *current2 = poly2;
  struct PolyNode *currentResult = nullptr;  // Pointer to track the current result.

  while (current1 != nullptr || current2 != nullptr) {
    // Extract coefficients and exponents from the current terms (or use 0 and -1 if the term is nullptr).
    double coef1 = (current1 != nullptr) ? current1->coef : 0;
    int exp1 = (current1 != nullptr) ? current1->exp : -1;

    double coef2 = (current2 != nullptr) ? current2->coef : 0;
    int exp2 = (current2 != nullptr) ? current2->exp : -1;

    if (exp1 == exp2) {
      // If the exponents are equal, add the coefficients and create a new term.
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
      // If the exponent of the first term is greater, add it to the result.
      result = AddNode(result, coef1, exp1);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current1 = current1->next;
    } else {
      // If the exponent of the second term is greater, add it to the result.
      result = AddNode(result, coef2, exp2);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current2 = current2->next;
    }
  }

  return result;  // Return the sum of the two polynomials.
}

// Subtract one polynomial from another and return the result.
struct PolyNode *Subtract(struct PolyNode *poly1, struct PolyNode *poly2) {
  struct PolyNode *result = nullptr;  // Initialize the result polynomial.
  struct PolyNode *current1 = poly1;  // Initialize current pointers for poly1 and poly2.
  struct PolyNode *current2 = poly2;
  struct PolyNode *currentResult = nullptr;  // Pointer to track the current result.

  while (current1 != nullptr || current2 != nullptr) {
    // Extract coefficients and exponents from the current terms (or use 0 and -1 if the term is nullptr).
    double coef1 = (current1 != nullptr) ? current1->coef : 0;
    int exp1 = (current1 != nullptr) ? current1->exp : -1;

    double coef2 = (current2 != nullptr) ? current2->coef : 0;
    int exp2 = (current2 != nullptr) ? current2->exp : -1;

    if (exp1 == exp2) {
      // If the exponents are equal, subtract the coefficients and create a new term.
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
      // If the exponent of the first term is greater, add it to the result.
      result = AddNode(result, coef1, exp1);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current1 = current1->next;
    } else {
      // If the exponent of the second term is greater, subtract it from the result.
      result = AddNode(result, -coef2, exp2);
      if (currentResult == nullptr) {
        currentResult = result;
      }
      current2 = current2->next;
    }
  }

  return result;  // Return the difference of the two polynomials.
}

// Multiply two polynomials and return the result.
struct PolyNode *Multiply(struct PolyNode *poly1, struct PolyNode *poly2) {
  struct PolyNode *result = nullptr;  // Initialize the result polynomial.

  struct PolyNode *current1 = poly1;
  while (current1 != nullptr) {
    struct PolyNode *current2 = poly2;
    while (current2 != nullptr) {
      double coef = current1->coef * current2->coef;  // Multiply coefficients.
      int exp = current1->exp + current2->exp;        // Add exponents.
      result = AddNode(result, coef, exp);           // Add the term to the result.
      current2 = current2->next;  // Move to the next term in poly2.
    }
    current1 = current1->next;  // Move to the next term in poly1.
  }

  return result;  // Return the product of the two polynomials.
}

// Evaluate the polynomial at a given value of x and return the result.
double Evaluate(struct PolyNode *poly, double x) {
  double result = 0.0;  // Initialize the result.

  struct PolyNode *current = poly;
  while (current != nullptr) {
    // Add the result of the current term to the overall result.
    result += current->coef * pow(x, current->exp);
    current = current->next;  // Move to the next term.
  }

  return result;  // Return the result of the evaluation.
}

// Calculate the derivative of a polynomial and return the result.
struct PolyNode *Derivative(struct PolyNode *poly) {
  struct PolyNode *result = nullptr;  // Initialize the result polynomial.

  struct PolyNode *current = poly;
  while (current != nullptr) {
    if (current->exp > 0) {
      double coef = current->coef * current->exp;  // Multiply coefficient by exponent.
      int exp = current->exp - 1;                 // Subtract 1 from the exponent.
      result = AddNode(result, coef, exp);         // Add the derivative term to the result.
    }
    current = current->next;  // Move to the next term.
  }

  return result;  // Return the derivative of the polynomial.
}

// Plot the polynomial within a specified range of x values.
void Plot(struct PolyNode *poly, int x1, int x2) {
  std::cout << "Plot of the function ";

  Print(poly);  // Print the polynomial.

  // Loop through y values from 12 to -12 (inclusive).
  for (int y = 12; y >= -12; y--) {
    for (int x = x1; x <= x2; x++) {
      double result = Evaluate(poly, x);  // Evaluate the polynomial at current x value.
      if (round(result) == y) {
        // Print a specific character if the result matches the current y value.
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

// Print the polynomial in a readable format.
void Print(PolyNode *poly) {
  if (poly == nullptr) {
    std::cout << "<NULL>\n";  // If the polynomial is empty, print "<NULL>".
    return;
  }

  PolyNode *p = poly;
  while (p != nullptr) {
    if (p->exp == 0) {
      std::cout << p->coef;  // If the term has exponent 0, print just the coefficient.
    } else if (p->exp == 1) {
      // If the exponent is 1, print "x" with appropriate sign and coefficient.
      if (p->coef == 1.0)
        std::cout << "+x ";
      else if (p->coef == -1.0)
        std::cout << "-x ";
      else
        std::cout << p->coef << "x ";
    } else {
      // Print the term with exponent greater than 1.
      if (p->coef == 1.0)
        std::cout << "+x^" << p->exp << " ";
      else if (p->coef == -1.0)
        std::cout << "-x^" << p->exp << " ";
      else
        std::cout << p->coef << "x^" << p->exp << " ";
    }

    p = p->next;  // Move to the next term.
  }

  std::cout << ">\n";  // Print ">" to indicate the end of the polynomial.
}

// Test function 1.
void Test1() {
  std::cout << "******TEST1******\n";

  struct PolyNode *poly = nullptr;  // Initialize an empty polynomial.
  std::cout << "Initial poly: ";
  Print(poly);

  poly = AddNode(poly, -2, 5);  // Add terms to the polynomial.
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

  DeletePoly(poly);  // Delete the polynomial to free memory.
}

// Main function to run the tests.
int main() {
  Test1();  // Run Test1.

  return 0;
}