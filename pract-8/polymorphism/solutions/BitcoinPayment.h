#include "PaymentMethod.h"

#include <string>
#include <iostream>

#ifndef BITCOIN_PAYMENT_H
#define BITCOIN_PAYMENT_H

class BitcoinPayment : public PaymentMethod {
private:
    std::string walletAddress;
    double transactionFee;
public:
    BitcoinPayment(const std::string& walletAddress, double transactionFee) : PaymentMethod() {
        this->walletAddress = walletAddress;
        this->transactionFee = transactionFee;
    }

    bool pay(double amount) override;
    bool validate() const override;
    std::string getType() const override;
};

bool BitcoinPayment::pay(double amount) {
        if(!validate()) {
        std::cerr << "Invalid credentials!";
        return false;
    }

    if(amount < 0) {
        std::cerr << "Amount must be non-negative!";
        return false;
    }

    std::cout << "Success! Amount paid: " << amount;
    return true;
}

bool BitcoinPayment::validate() const {
    return this->walletAddress.length() >= 26 && transactionFee >= 0.0;
}

std::string BitcoinPayment::getType() const {
    return "Bitcoin paynment";
}

#endif

