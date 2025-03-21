#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "console/console.h"

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
    
    console.Clear();
    console.printHeader();
    console.SetColor(GREEN);
    console.WriteLine("Add Product");
    console.SetColor(WHITE);
    
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
    
    console.SetColor(GREEN);
    console.WriteLine("Product added successfully!");
    console.SetColor(WHITE);
}

void displayProducts() {
    ifstream file("products.txt");
    if (!file) {
        console.SetColor(RED);
        console.WriteLine(" Error: Could not open 'products.txt'!");
        console.SetColor(WHITE);
        return;
    }

    Product p;
    console.Clear();
    console.printHeader();
    console.SetColor(YELLOW);
    console.WriteLine("Available Products");
    console.SetColor(WHITE);
    
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    cout << "-----------------------------------------------------\n";

    bool isEmpty = true;
    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        cout << left << setw(10) << p.id << setw(20) << p.name << setw(10) << p.price << setw(10) << p.quantity << endl;
        isEmpty = false;
    }

    if (isEmpty) {
        console.SetColor(YELLOW);
        console.WriteLine(" No products available!");
        console.SetColor(WHITE);
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
    
    console.Clear();
    console.printHeader();
    console.SetColor(CYAN);
    console.WriteLine("Billing System");
    console.SetColor(WHITE);

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
            console.SetColor(RED);
            console.WriteLine("Invalid ID or insufficient quantity!");
            console.SetColor(WHITE);
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
    
    console.SetColor(GREEN);
    console.WriteLine("✅ Bill generated successfully! Check 'bill.txt'.");
    console.SetColor(WHITE);
}

int main() {
    int choice;
    console.CreateConsole(L"Retail Billing System");
    do {
        console.Clear();
        console.printHeader();
        console.SetColor(YELLOW);
        console.WriteLine("Retail Billing System");
        console.SetColor(WHITE);
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Generate Bill\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                generateBill();
                break;
            case 4:
                console.SetColor(GREEN);
                console.WriteLine("Thank you for using the system!");
                console.SetColor(WHITE);
                break;
            default:
                console.SetColor(RED);
                console.WriteLine("Invalid choice! Try again.");
                console.SetColor(WHITE);
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 4);
    
    return 0;
}
