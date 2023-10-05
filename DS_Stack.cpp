/* ��������� ������ ��� �������� ���������, ������������ ��������:
    1) �������� �������
    2) �������� �� �������
    3) ��������� � ���� (push)
    4) ������� �� ����� (pop)
    5) ����������� ������� �������.

  LIFO = last in first out.
  ������ �������������� � ������ ����� ����������� �������� ����� (top).
  ������ ������ �� �����.
*/

/* ������ �� �����:
    1) ������� --- �������� ������ - ���� (,),[,],{,}
      ��������:
        ��� ������� �� ���������� �������� ����������.
        ���� ���������� ����������� ������ ������ ����, ��
          �������� � � ����.
        ���� ����������� ����������� ������, ��
          ���� ���� �� ���� ������ ����, �� return false;
          ���� �� ������� ����� ����������� ������ ������� ����, return false;
          ���� �� ������� ����� ������ ����������� ������, �� ��������� �� ��
   �����; ���� ������ �����������, � ���� �� ����, return false;

   2) ����������� �������� ����������� ���������

   3) ���������� ����������� ������ � ������� ���������
    a - (b+c*d) / e
    
    ch | ����(�� ��� � �������) | postfixexpr
    a  |                        | a
    -  | -                      | 
    (  | -(                     |
    b  | -(                     | ab
    +  | -(+                    | ab
    c  | -(+                    | abc
    *  | -(+*                   | abc
    d  | -(+*                   | abcd
    )  | -(+                    | abcd*
       | -(                     | abcd*+
       | -                      | abcd*+
    /  | -/                     | abcd*+
    e  |                        | abcd*+/-

*/

#include <fstream>
#include <iostream>
#include <string>
typedef int datatype;

class TStack {
 private:
  struct Node {
    datatype data;
    Node* next;
  };
  Node* top;

  void clear() {
    while (!isEmpty()) {
      pop();
    }
  }

 public:
  TStack() { top = nullptr; }
  ~TStack() { clear(); }

  bool isEmpty() { return top == nullptr; }

  void push(const datatype& elem) {
    Node* newNode = new Node;
    newNode->data = elem;
    newNode->next = top;
    top = newNode;
  }

  void pop() {
    Node* curNode = top;
    top = top->next;
    delete curNode;
    curNode = nullptr;
  }

  datatype peek() { return top->data; }
};

class ArrayStack {
 private:
  datatype* stack;
  int size_;
  int top;
  void clear() { top = -1; }

 public:
  ArrayStack(const int& size)
      : size_(size), stack(new datatype[size_]), top(-1) {}

  ~ArrayStack() { delete stack; }

  bool isEmpty() { return top == -1; }

  void push(const datatype& elem) {
    if ((top + 1) != size_) {
      top++;
      stack[top] = elem;
    } else {
      std::cout << "Stack overflow.";
    }
  }

  void pop() {
    if (!isEmpty()) {
      top--;
    }
  }

  datatype peek() { return stack[top]; }
};

int main() {
  TStack st;
  st.push(123);
  st.pop();
  st.push(321);
  st.pop();
  std::cout << st.peek();
}

// ������ � �������
bool isCorrect(TStack st, std::string filename) {
  bool result = true;
  std::ifstream fin(filename);
  char symbol;
  while (fin >> symbol && result) {
    if (symbol == '(' || symbol == '{' || symbol == '[')
      st.push(symbol);
    else {
      if (symbol == ')' || symbol == '}' || symbol == ']') {
        if (st.isEmpty() || ((symbol == ')') ^ (st.peek() == '(')) ||
            ((symbol == '}') ^ (st.peek() == '{')) ||
            ((symbol == ']') ^ (st.peek() == '['))) {
          result = false;
        } else {
          st.pop();
        }
      }
    }
  }
  return result && st.isEmpty();
}

// ������ � ����������� ����������
