#include <iostream>
#include <string>

#include "CreditCardPayment.h"
#include "PaymentProcessor.h"
#include "BitcoinPayment.h"

int main() {

    PaymentMethod* bit1 = new BitcoinPayment("ADFASF23RWEF2q3fgaSF3424GDF", 15.1);
    bit1->validate();
    bit1->pay(10.0);

    PaymentMethod* cr1 = new CreditCardPayment("5413101040409999", "311", "12/30");


    PaymentProcessor proc;
    proc.addMethod(bit1);
    proc.addMethod(cr1);

    proc.processAll(20.0);

    int total = proc.getTotalProcessed();
    std::cout << "Total: " << total;
    return 0;
}