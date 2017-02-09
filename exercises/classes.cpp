#include <iostream>
using namespace std;

struct Expression
{
    virtual double evaluate() const = 0; // абстрактный метод, должен быть виртуалным
    virtual ~Expression() {}; // должен быть виртуальный деструктор чтобы можно было удалять по ссылки базового типа
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}

    // надо перегрузить метод вычисления
    double evaluate() const { // при этом он тоже должен быть константным (совпадать)
        return value;
    }

private:
    double value;
};

struct BinaryOperation : Expression
{
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые вам нужно реализовать.
     */
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }

    // поскольку будут созданы объекты в куче нужно определить деструктор
    ~BinaryOperation() {
        // и удалить их
        delete left;
        delete right;
    }
    
    // надо перегрузить метод вычисления
    double evaluate() const {
        double l = left->evaluate();
        double r = right->evaluate();
        switch (op) {
            case '+':
                return l + r; break; //? not need
            case '-':
                return l - r;
            case '*':
                return l * r;
            case '/':
                return l / r;
        }
    }

private:
    Expression const * left; // поскольку этот класс отвечает за удаление этих полей и
    Expression const * right; // поскольку они должны быть базового класса (чтобы можно было 
    // вычислять как с числами так и с подвыражениями) то нужно чтобы базовым вычислением
    // был виртуальный метод. и деструктор.
    char op;
};

int main() {
    // сначала создаём объекты для подвыражения 4.5 * 5
    Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    // потом используем его в выражении для +
    Expression * expr = new BinaryOperation(new Number(3), '+', sube);
    // вычисляем и выводим результат: 25.5
    std::cout << expr->evaluate() << std::endl;
    // тут освобождаются *все* выделенные объекты
    // (например, sube будет правым операндом expr, поэтому его удалять не нужно)
    delete expr;
    return 0;
}
