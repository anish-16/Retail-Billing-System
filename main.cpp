#include "admin.h"
#include "console/console.h"
int main() {
    console.CreateConsole(L"Retail Billing System");
    Admin::dashboard();
    return 0;
}
