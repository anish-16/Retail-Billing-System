#include "billing.h"

void Billing::generateBill() {
    std::vector<Product> products = Product::loadProducts();
    std::vector<Product> cart;
    float total = 0;
    char choice;

    console.Clear();
    console.printHeader();
    console.SetColor(CYAN);
    console.WriteLine("Billing System");
    console.SetColor(WHITE);

    do {
        int id, qty;
        std::cout << "Enter Product ID: ";
        std::cin >> id;
        std::cout << "Enter Quantity: ";
        std::cin >> qty;

        for (auto& p : products) {
            if (p.getId() == id && p.getQuantity() >= qty) {
                p.setQuantity(p.getQuantity() - qty);
                cart.push_back(Product(p.getId(), p.getName(), p.getPrice(), qty));
                total += p.getPrice() * qty;
                break;
            }
        }

        std::cout << "Add more? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y');

    Product::saveProducts(products);

    std::ofstream billFile("bill.txt");
    billFile << "ID\tName\tPrice\tQty\tTotal\n";
    for (const auto& item : cart) {
        billFile << item.getId() << "\t" << item.getName() << "\t" << item.getPrice() << "\t"
                 << item.getQuantity() << "\t" << item.getPrice() * item.getQuantity() << "\n";
    }
    billFile << "\nGrand Total: " << total << "\n";

    console.SetColor(GREEN);
    console.WriteLine("✅ Bill generated successfully! Check 'bill.txt'.");
    console.SetColor(WHITE);
}
