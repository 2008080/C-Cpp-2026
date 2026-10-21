#include <iostream>
#include <vector>
#include <string>

using namespace std;
=
class Animal {
public:
    virtual ~Animal() {}
    virtual void speak() const = 0;
};


class Dog : public Animal {
public:
    void speak() const override {
        cout << "狗：汪汪汪！" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        cout << "猫：喵喵喵！" << endl;
    }
};

class Zoo {
private:
    vector<Animal*> animals; 

public:
    ~Zoo() {
        for (Animal* animal : animals) {
            delete animal;
        }
        animals.clear();
    }

    void addAnimal(Animal* animal) {
        animals.push_back(animal);
    }

    void makeAllSounds() const {
        for (Animal* animal : animals) {
            animal->speak(); 
        }
    }
};

class Bird : public Animal {
public:
    void speak() const override {
        cout << "鸟：叽叽喳喳！" << endl;
    }
};

class WolfDog : public Dog {
public:
    void speak() const override {
        cout << "狼狗：嗷呜~~~（狼嚎）" << endl;
    }
};

int main() {
    cout << "=== 测试功能要求 (一) ===" << endl;
    Zoo myZoo;

    myZoo.addAnimal(new Dog());
    myZoo.addAnimal(new Cat());
    
    myZoo.makeAllSounds();


    cout << "\n=== 测试功能要求 (二) ===" << endl;
    
    myZoo.addAnimal(new Bird());
    myZoo.addAnimal(new WolfDog());
    
    myZoo.makeAllSounds();

    return 0;
}
