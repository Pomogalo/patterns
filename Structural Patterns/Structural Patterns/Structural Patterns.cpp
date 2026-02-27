#include <iostream>
#include <string>
using namespace std;

// Базовый компонент: напиток
class Beverage {
public:
    virtual string getDescription() = 0;
    virtual double cost() = 0;
};

class Espresso : public Beverage {  // Базовый кофе
public:
    string getDescription() override { return "Эспрессо"; }
    double cost() override { return 1.99; }
};

// Абстрактный декоратор для добавок
class CondimentDecorator : public Beverage {
protected:
    Beverage* beverage;
public:
    CondimentDecorator(Beverage* b) : beverage(b) {}
    string getDescription() override { return beverage->getDescription(); }
    double cost() override { return beverage->cost(); }
};

// Конкретные добавки
class Milk : public CondimentDecorator {
public:
    Milk(Beverage* b) : CondimentDecorator(b) {}
    string getDescription() override { return beverage->getDescription() + ", Молоко"; }
    double cost() override { return beverage->cost() + 0.10; }
};

class Sugar : public CondimentDecorator {
public:
    Sugar(Beverage* b) : CondimentDecorator(b) {}
    string getDescription() override { return beverage->getDescription() + ", Сахар"; }
    double cost() override { return beverage->cost() + 0.05; }
};

class Syrup : public CondimentDecorator {
public:
    Syrup(Beverage* b) : CondimentDecorator(b) {}
    string getDescription() override { return beverage->getDescription() + ", Сироп"; }
    double cost() override { return beverage->cost() + 0.15; }
};

int main()
{
    setlocale(0, "");
    // Заказываем кофе с добавками
    Beverage* drink = new Espresso();
    drink = new Milk(drink);  // Добавляем молоко
    drink = new Sugar(drink);  // Добавляем сахар
    drink = new Syrup(drink);  // Добавляем сироп

    cout << drink->getDescription() << " стоит $" << drink->cost() << endl;
    // Вывод: Эспрессо, Молоко, Сахар, Сироп стоит $2.29

    // Простой кофе без добавок
    Beverage* simpleDrink = new Espresso();
    cout << simpleDrink->getDescription() << " стоит $" << simpleDrink->cost() << endl;
    // Вывод: Эспрессо стоит $1.99

    delete drink;
    delete simpleDrink;
}

