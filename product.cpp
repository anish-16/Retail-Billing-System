#include<bits/stdc++.h>
using namespace std;

#include "Product.h"
#include "console/console.h"

Product::Product() : id(0), name(""), price(0.0), quantity(0), expiryDate(""), subCategory("") {}

Product::Product(int id, string name, float price, int quantity, string expiryDate, string subCategory)
    : id(id), name(name), price(price), quantity(quantity), expiryDate(expiryDate), subCategory(subCategory) {}

int Product::getId() const {
    return id;
}

string Product::getName() const {
    return name;
}

float Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

string Product::getExpiryDate() const {
    return expiryDate;
}

string Product::getSubCategory() const {
    return subCategory;
}

void Product::setQuantity(int qty) {
    quantity = qty;
}

void Product::display() const {
    cout << left << setw(10) << id
         << setw(20) << name
         << setw(10) << fixed << setprecision(2) << price
         << setw(10) << quantity
         << setw(15) << expiryDate
         << setw(20) << subCategory << endl;
}

void Product::addProduct() {
    int id, quantity;
    string name, expiryDate, subCategory;
    float price;

    cout << "Enter Product ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Product Name: ";
    getline(cin, name);
    cout << "Enter Product Price: ";
    cin >> price;
    cout << "Enter Product Quantity: ";
    cin >> quantity;
    cin.ignore();
    cout << "Enter Expiry Date (YYYY-MM-DD): ";
    getline(cin, expiryDate);
    cout << "Enter Product Sub-Category: ";
    getline(cin, subCategory);

    vector<Product> products = loadProducts();
    products.push_back(Product(id, name, price, quantity, expiryDate, subCategory));
    saveProducts(products);

    cout << "Product added successfully!\nPress any key to continue...";
    cin.ignore();
    cin.get();
}

void Product::displayProducts() {
    vector<Product> products = loadProducts();
    if (products.empty()) {
        cout << "No products available.\nPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << setw(15) << "Expiry Date"
         << setw(20) << "Sub-Category" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (const auto& product : products) {
        product.display();
    }

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}

vector<Product> Product::loadProducts() {
    vector<Product> products;
    ifstream file("products.txt");
    if (!file) return products;

    int id, quantity;
    string name, expiryDate, subCategory;
    float price;

    while (file >> id >> price >> quantity >> ws) {
        getline(file, expiryDate, '|');
        getline(file, subCategory, '|');
        getline(file, name);
        products.push_back(Product(id, name, price, quantity, expiryDate, subCategory));
    }

    file.close();
    return products;
}

void Product::saveProducts(const vector<Product>& products) {
    ofstream file("products.txt");
    for (const auto& product : products) {
        file << product.getId() << " "
             << product.getPrice() << " "
             << product.getQuantity() << " "
             << product.getExpiryDate() << "|"
             << product.getSubCategory() << "|"
             << product.getName() << "\n";
    }
    file.close();
}

void Product::deleteProduct() {
    int id;
    cout << "Enter Product ID to delete based on expiry date: ";
    cin >> id;
    
    vector<Product> products = loadProducts();
    bool found = false;
    auto it = remove_if(products.begin(), products.end(), [id, &found](const Product& product) {
        if (product.getId() == id) {
            found = true;
            cout << "Product with ID " << id << " and expiry date " << product.getExpiryDate() << " has been deleted." << endl;
            return true;
        }
        return false;
    });
    
    if (!found) {
        cout << "No expired product found with ID " << id << "." << endl;
    }
    
    products.erase(it, products.end());
    saveProducts(products);
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}

void Product::updateProductQuantity() {
    int id, newQuantity;
    cout << "Enter Product ID to update quantity: ";
    cin >> id;
    cout << "Enter new quantity: ";
    cin >> newQuantity;

    vector<Product> products = loadProducts();
    bool found = false;
    for (auto& product : products) {
        if (product.getId() == id) {
            product.setQuantity(newQuantity);
            found = true;
            cout << "Quantity updated successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Product with ID " << id << " not found." << endl;
    }

    saveProducts(products);
    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();
}
