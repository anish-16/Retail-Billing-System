#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct Product {
    int id;
    string name;
    float price;
    int quantity;
};

void addProduct() {
    ofstream file("products.txt", ios::app);
    Product p;
    cout << "Enter Product ID: ";
    cin >> p.id;
    cout << "Enter Product Name: ";
    cin >> p.name;
    cout << "Enter Price: ";
    cin >> p.price;
    cout << "Enter Quantity: ";
    cin >> p.quantity;
    
    file << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
    file.close();
    cout << "Product added successfully!!\n";
}

void displayProducts() {
    ifstream file("products.txt");
    if (!file) {  // Check if file exists
        cout << "❌ Error: Could not open 'products.txt'!\n";
        return;
    }
    Product p;
    cout << "\n📦 Available Products:\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    cout << "-----------------------------------------------------\n";

    bool isEmpty = true;  // Track if file is empty
    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        cout << left << setw(10) << p.id << setw(20) << p.name << setw(10) << p.price << setw(10) << p.quantity << endl;
        isEmpty = false;
    }

    if (isEmpty) {
        cout << "⚠️ No products available!\n";
    }

    file.close();
}
void generateBill() {
    vector<Product> cart;
    ifstream file("products.txt");
    vector<Product> products;
    Product p;
    
    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        products.push_back(p);
    }
    file.close();
    
    int id, qty;
    char choice;
    float total = 0;
    ofstream billFile("bill.txt");
    
    cout << "\nBilling System:\n";
    do {
        cout << "Enter Product ID to purchase: ";
        cin >> id;
        cout << "Enter Quantity: ";
        cin >> qty;
        
        bool found = false;
        for (auto &prod : products) {
            if (prod.id == id && prod.quantity >= qty) {
                prod.quantity -= qty;
                total += prod.price * qty;
                cart.push_back({prod.id, prod.name, prod.price, qty});
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Invalid ID or insufficient quantity!\n";
        }
        cout << "Do you want to add more items? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    
    billFile << "Retail Store Bill\n";
    billFile << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Qty" << setw(10) << "Total" << endl;
    
    for (const auto &item : cart) {
        billFile << left << setw(10) << item.id << setw(20) << item.name << setw(10) << item.price << setw(10) << item.quantity << setw(10) << item.price * item.quantity << endl;
    }
    billFile << "\nGrand Total: " << total << endl;
    billFile.close();
    
    ofstream outFile("products.txt");
    for (const auto &prod : products) {
        outFile << prod.id << " " << prod.name << " " << prod.price << " " << prod.quantity << endl;
    }
    outFile.close();
    
    cout << "Bill generated successfully! Check 'bill.txt'.\n";
}

int main() {
    int choice;
    do {
        cout << "\nRetail Billing System";
        cout << "\n1. Add Product";
        cout << "\n2. Display Products";
        cout << "\n3. Generate Bill";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: generateBill(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    return 0;
}
