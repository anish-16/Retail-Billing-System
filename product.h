#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

class Product {
private:
    int id;
    std::string name;
    float price;
    int quantity;
    std::string expiryDate;
    std::string subCategory;

public:
    Product();
    Product(int, std::string, float, int, std::string, std::string);

    int getId() const;
    std::string getName() const;
    float getPrice() const;
    int getQuantity() const;
    std::string getExpiryDate() const;
    std::string getSubCategory() const;

    void setQuantity(int);
    void display() const;

    static void addProduct();
    static void displayProducts();
    static void deleteProduct();
    static void updateProductQuantity();
    static std::vector<Product> loadProducts();
    static void saveProducts(const std::vector<Product>&);
};

#endif
