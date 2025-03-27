#ifndef BILLING_H
#define BILLING_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Product.h"
#include "console/console.h"

class Billing {
public:
    static void generateBill();
    static void displayBill(const std::vector<Product>& cart, float total);
};

#endif
