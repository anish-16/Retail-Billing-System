#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "console/console.h"

class Product {
private:
    int id;
    std::string name;
    float price;
    int quantity;

public:
    Product();
    Product(int, std::string, float, int);

    int getId() const;
    std::string getName() const;
    float getPrice() const;
    int getQuantity() const;

    void setQuantity(int);
    void display() const;

    static void addProduct();
    static void displayProducts();
    static std::vector<Product> loadProducts();
    static void saveProducts(const std::vector<Product>&);
};

#endif
