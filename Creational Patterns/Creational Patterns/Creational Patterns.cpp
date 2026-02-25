
#include <iostream>
#include <string>
using namespace std;
 
// Абстрактный персонаж (продукт)
class Character {
public:
    virtual string getType() = 0;
    virtual void attack() = 0;
};

// Конкретные персонажи
class Warrior : public Character {
public:
    string getType() override { return "Воин"; }
    void attack() override { cout << "Воин атакует мечом!" << endl; }
};

class Mage : public Character {
public:
    string getType() override { return "Маг"; }
    void attack() override { cout << "Маг кастует огненный шар!" << endl; }
};

class Archer : public Character {
public:
    string getType() override { return "Лучник"; }
    void attack() override { cout << "Лучник стреляет из лука!" << endl; }
};

// Абстрактная фабрика персонажей
class CharacterFactory {
public:
    virtual Character* createCharacter() = 0;
    void spawnAndAttack() {
        Character* chara = createCharacter();
        cout << "Создан " << chara->getType() << ". ";
        chara->attack();
        delete chara;
    }
};

// Конкретные фабрики
class WarriorFactory : public CharacterFactory {
public:
    Character* createCharacter() override { return new Warrior(); }
};

class MageFactory : public CharacterFactory {
public:
    Character* createCharacter() override { return new Mage(); }
};

class ArcherFactory : public CharacterFactory {
public:
    Character* createCharacter() override { return new Archer(); }
};

int main()
{
    setlocale(0, "");
    // Симуляция игры: создаем разных персонажей через фабрики
    CharacterFactory* factory = new WarriorFactory();
    factory->spawnAndAttack();  // Вывод: Создан Воин. Воин атакует мечом!

    factory = new MageFactory();
    factory->spawnAndAttack();  // Вывод: Создан Маг. Маг кастует огненный шар!

    factory = new ArcherFactory();
    factory->spawnAndAttack();  // Вывод: Создан Лучник. Лучник стреляет из лука!

    delete factory;
}
