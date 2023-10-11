#include "iostream"
#include "Factory Method.h"

int main() {
    ShirtFactory shirtFactory;
    JeansFactory jeansFactory;
    SneakersFactory sneakersFactory;

    Product* shirt1 = shirtFactory.createProduct("38", Gender::Male, true);
    Product* shirt2 = shirtFactory.createProduct("39", Gender::Female, true);

    Product* jeans1 = jeansFactory.createProduct("33", Gender::Female, false);
    Product* jeans2 = jeansFactory.createProduct("38", Gender::Male, false);


    Product* sneakers1 = sneakersFactory.createProduct("43", Gender::Unisex, true);
    Product* sneakers2 = sneakersFactory.createProduct("42", Gender::Unisex, true);

    // Создание массива одежды
    Vector<Product*> shirts;
    Vector<Product*> jeans;
    Vector<Product*> sneakers;

    shirts.push_back(shirt1);
    shirts.push_back(shirt2);

    jeans.push_back(jeans1);
    jeans.push_back(jeans2);

    sneakers.push_back(sneakers1);
    sneakers.push_back(sneakers2);


    print(jeans);
    print(sneakers);
    print(shirts);

    shirts.clear();
    jeans.clear();
    sneakers.clear();


    return 0;
}
