#include "billing.h"
#include "console/console.h"

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
                cart.push_back(Product(p.getId(), p.getName(), p.getPrice(), qty, p.getExpiryDate(), p.getSubCategory()));
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

    displayBill(cart, total);
}

void Billing::displayBill(const std::vector<Product>& cart, float total) {
    console.SetColor(YELLOW);
    console.WriteLine("\n===== BILL RECEIPT =====");
    console.SetColor(WHITE);

    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(20) << "Name"
              << std::setw(10) << "Price"
              << std::setw(10) << "Qty"
              << std::setw(10) << "Total" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    for (const auto& item : cart) {
        std::cout << std::left << std::setw(10) << item.getId()
                  << std::setw(20) << item.getName()
                  << std::setw(10) << item.getPrice()
                  << std::setw(10) << item.getQuantity()
                  << std::setw(10) << item.getPrice() * item.getQuantity() << std::endl;
    }

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << std::setw(50) << "Grand Total: " << total << std::endl;

    console.SetColor(GREEN);
    console.WriteLine("\n✅ Bill displayed successfully!");
    console.SetColor(WHITE);
}
