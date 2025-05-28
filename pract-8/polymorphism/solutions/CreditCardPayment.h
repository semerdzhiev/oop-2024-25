
#include <chrono> 
#include <iostream>
#include "PaymentMethod.h"

#ifndef CREDIT_CARD_PAYMENT_H
#define CREDIT_CARD_PAYMENT_H

class CreditCardPayment : public PaymentMethod {
private:
    std::string cardNumber;
    std::string cvv;
    std::string expiryDate;
public:
    CreditCardPayment(const std::string& cardNumber, const std::string& cvv, const std::string& expiryDate) : PaymentMethod() {
        this->cardNumber = cardNumber;
        this->cvv = cvv;
        this->expiryDate = expiryDate;
    };
    bool pay(double amount) override;
    bool validate() const override;
    std::string getType() const override;
};

bool CreditCardPayment::pay(double amount) {
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

bool CreditCardPayment::validate() const {

    if(this->cardNumber.length() != 16) return false;
    if(this->cvv.length() != 3) return false;

    for(char s : this->cardNumber) {
        if(!isdigit(s)) return false;
    }

    for(char s : this->cvv) {
        if(!isdigit(s)) return false;
    }

    if(!isdigit(expiryDate[0]) 
        || !isdigit(expiryDate[1])
        || !isdigit(expiryDate[3])
        || !isdigit(expiryDate[4])
        || expiryDate[2] != '/') return false;
        
    int month = (expiryDate[0] - '0') * 10 + expiryDate[1] - '0';
    int year = (expiryDate[2] - '0') * 10 + expiryDate[3] - '0';

    if(year < 25 || month > 12 || month == 0) return false;
    if(year == 25 && month < 5) return false;

    return true;
}

 std::string CreditCardPayment::getType() const {
    return "Credit Card";
 }

#endif