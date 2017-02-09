#include <iostream>
using namespace std;

struct Number;
struct Visitor;
struct BinaryOperation;
struct Expression;

struct Expression
{
    virtual double evaluate() const = 0; // абстрактный метод, должен быть виртуалным
    virtual ~Expression() {}; // должен быть виртуальный деструктор чтобы можно было удалять по ссылки базового типа
    virtual void visit(Visitor * visitor) const  = 0;
};

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
    virtual ~Visitor() { }
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
    void visit(Visitor * visitor) const;
    double get_value() const { return value; }

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

    Expression const * get_left()  const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

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
    void visit(Visitor * visitor) const;

private:
    Expression const * left; // поскольку этот класс отвечает за удаление этих полей и
    Expression const * right; // поскольку они должны быть базового класса (чтобы можно было 
    // вычислять как с числами так и с подвыражениями) то нужно чтобы базовым вычислением
    // был виртуальный метод. и деструктор.
    char op;
};

void BinaryOperation::visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }
void Number::visit(Visitor * visitor) const { visitor->visitNumber(this); }

bool check_equals(Expression const *left, Expression const *right)
{
    return *((int**)left) == *((int**)right);
}

struct PrintBinaryOperationsVisitor : Visitor {
    void visitNumber(Number const * number) { 
        cout << number->get_value() << ' ';
    }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        bop->get_left()->visit(this);
        std::cout << bop->get_op() << " ";
        bop->get_right()->visit(this);
    }
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
    Number n(5);
    Number k(6);
    cout << check_equals(&n, &k);
    PrintBinaryOperationsVisitor visitor;
    expr->visit(&visitor);
    delete expr;
    return 0;
}
// g++ -fdump-class-hierarchy classes.cpp
