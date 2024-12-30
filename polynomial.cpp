#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

struct Monom {
    double coeff;
    int pow;
    Monom* next;
    Monom(double c, int p) : coeff(c), pow(p), next(nullptr) {}
    
};

class Polynomial {
public:
    Monom* head;

    Polynomial() : head(nullptr) {};
    void addMonom(double coeff, int pow) {
        if (coeff == 0) return;
        Monom* newMonom = new Monom(coeff, pow);
        if (!head || head->pow < pow) {
            newMonom->next = head;
            head = newMonom;
        }
        else {
            Monom* tmp = head;
            while (tmp->next && tmp->next->pow >= pow) {
                tmp = tmp->next;
            }
            newMonom->next = tmp->next;
            tmp->next = newMonom;
        }
    }
    Monom* getHead() const { return head; }
    void print() {
        Monom* current = head;
        while (current) {
            cout << current->coeff << "x^" << current->pow / 100 << "y^" << (current->pow % 100) / 10 << "z^" << current->pow % 10 << " ";
            current = current->next;
        }
        cout << endl;
    }
    Polynomial operator+(const Polynomial& other) {
        Polynomial result;
        Monom* p1 = getHead(); //head;
        Monom* p2 = other.getHead(); //other.head;

        while (p1 || p2) {
            if (!p1) {
                result.addMonom(p2->coeff, p2->pow);
                p2 = p2->next;
            }
            else if (!p2) {
                result.addMonom(p1->coeff, p1->pow);
                p1 = p1->next;
            }
            else if (p1->pow > p2->pow) {
                result.addMonom(p1->coeff, p1->pow);
                p1 = p1->next;
            }
            else if (p1->pow < p2->pow) {
                result.addMonom(p2->coeff, p2->pow);
                p2 = p2->next;
            }
            else {

                cout << abs(p1->coeff + p2->coeff) << "\n";
                if (abs(p1->coeff + p2->coeff) > 1e-12)
                {
                    result.addMonom(p1->coeff + p2->coeff, p1->pow);
                }
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        
        //result.print();
        return result;
    }

    ~Polynomial() {
        Monom* current = head;
        while (current) {
            Monom* to_delete = current;
            current = current->next;
            delete to_delete;
        }
    }
   
   Polynomial& operator=(const Polynomial& other) {
        if (this == &other) {
            return *this;
        }
        Monom* tmp = getHead();
        while (tmp) {
            Monom* to_delete = tmp;
            tmp = tmp->next;
            delete to_delete;
        }
        head = nullptr; 
        const Monom* otherCurrent = other.getHead();
        while (othertmp) {
            addMonom(othertmp->coeff, othertmp->pow);
            othertmp = othertmp->next;
        }
        
        return *this;  
    }
};

int main() {
    Polynomial poly1, poly2, tmp;

    poly1.addMonom(3.5, 123);
    poly1.addMonom(3, 125);
    poly1.print();


    poly2.addMonom(-3.5, 123);
    poly2.addMonom(2, 125);
    poly2.addMonom(2, 130);

    poly2.print();
    tmp = poly1 + poly2;
    tmp.print();

    return 0;
}
