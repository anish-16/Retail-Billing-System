#include "admin.h"

void Admin::dashboard() {
    int choice;
    do {
        console.Clear();
        console.printHeader();
        console.SetColor(YELLOW);
        console.WriteLine("Admin Dashboard");
        console.SetColor(WHITE);

        std::cout << "1. Add Product\n2. Display Products\n3. Generate Bill\n4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                Product::addProduct();
                break;
            case 2:
                Product::displayProducts();
                break;
            case 3:
                Billing::generateBill();
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
    } while (choice != 4);
}
