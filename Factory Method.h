#ifndef OOP_COMISSION_FACTORY_METHOD_H
#define OOP_COMISSION_FACTORY_METHOD_H

#include "vector.h"
#include "algorithm"

enum class Gender { Male, Female, Unisex };

class Product {
public:
    virtual void display() = 0;

protected:
    std::string size;
    Gender gender;
    bool inStock;

public:
    Product(const std::string& size, Gender gender, bool inStock)
            : size(size), gender(gender), inStock(inStock) {}
};


class Shirt : public Product {
public:
    Shirt(const std::string& size, Gender gender, bool inStock) : Product(size, gender, inStock) {}

    void display() override {
        std::cout << "Шорты: Размер - " << size << ", Пол - ";
        if (gender == Gender::Male) {
            std::cout << "Мужской";
        } else if (gender == Gender::Female) {
            std::cout << "Женский";
        } else {
            std::cout << "Унисекс";
        }
        std::cout << ", В наличии - " << (inStock ? "Да" : "Нет") << std::endl;
    }
};

class Jeans : public Product {
public:
    Jeans(const std::string& size, Gender gender, bool inStock) : Product(size, gender, inStock) {}
    void display() override {
        std::cout << "Джинсы: Размер - " << size << ", Пол - ";
        if (gender == Gender::Male) {
            std::cout << "Мужской";
        } else if (gender == Gender::Female) {
            std::cout << "Женский";
        } else {
            std::cout << "Унисекс";
        }
        std::cout << ", В наличии - " << (inStock ? "Да" : "Нет") << std::endl;
    }
};

class Sneakers : public Product {
public:
    Sneakers(const std::string& size, Gender gender, bool inStock) : Product(size, gender, inStock) {}
    void display() override {
        std::cout << "Кроссовки: Размер - " << size << ", Пол - ";
        if (gender == Gender::Male) {
            std::cout << "Мужской";
        } else if (gender == Gender::Female) {
            std::cout << "Женский";
        } else {
            std::cout << "Унисекс";
        }
        std::cout << ", В наличии - " << (inStock ? "Да" : "Нет") << std::endl;
    }
};

class ProductFactory {
public:
    virtual Product* createProduct(const std::string& size, Gender gender, bool inStock) = 0;
};

class ShirtFactory : public ProductFactory {
public:
    Product* createProduct(const std::string& size, Gender gender, bool inStock){
        return new Shirt(size, gender, inStock);
    }
};

class JeansFactory : public ProductFactory {
public:
    Product* createProduct(const std::string& size, Gender gender, bool inStock) {
        return new Jeans(size, gender, inStock);
    }
};

class SneakersFactory : public ProductFactory {
public:
    Product* createProduct(const std::string& size, Gender gender, bool inStock)  {
        return new Sneakers(size, gender, inStock);
    }
};

void print(Vector<Product*> object){
    std::for_each(object.begin(), object.end(), [](Product* object) {object->display();});
}

#endif //OOP_COMISSION_FACTORY_METHOD_H