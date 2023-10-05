/* Структура данных для хранения элементов, поддерживает операции:
    1) Создание пустого
    2) Проверка на пустоту
    3) Поместить в стек (push)
    4) Удалить из стека (pop)
    5) Просмотреть верхний элемент.

  LIFO = last in first out.
  Доступ осуществляется с одного конца называемого вершиной стека (top).
  Нельзя бегать по стеку.
*/

/* Задачи на стеки:
    1) Условие --- Закрытие скобок - есть (,),[,],{,}
      Алгоритм:
        Все символы не являющиеся скобками пропускаем.
        Если встетилась открывающая скобка любого вида, то
          помещаем её в стек.
        Если встретилась закрывающая скобка, то
          если стек на этот момент пуст, то return false;
          если на вершине стека открывающая скобка другого вида, return false;
          если на вершине стека парная открывающая скобка, то извлекаем ее из
   стека; если строка закончилась, а стек не пуст, return false;

   2) Выячисление значений постфиксных выражений

   3) Построение постфиксной записи с помощью инфиксной
    a - (b+c*d) / e
    
    ch | стек(от дна к вершине) | postfixexpr
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

// Задача о скобках
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

// Задача о постфиксных выражениях
