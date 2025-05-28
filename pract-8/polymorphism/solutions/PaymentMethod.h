#include <string>

#ifndef PAYMENT_METHOD_H
#define PAYMENT_METHOD_H

class PaymentMethod {
public:
    virtual bool pay(double amount) = 0;
    virtual bool validate() const = 0;
    virtual std::string getType() const = 0;
    virtual ~PaymentMethod() = default;
    PaymentMethod() = default;

    bool operator==(const PaymentMethod& other) const;
    bool operator<(const PaymentMethod& other) const;
};

bool PaymentMethod::operator==(const PaymentMethod& other) const {
    return this->getType() == other.getType();
}

bool PaymentMethod::operator<(const PaymentMethod& other) const {
    //return strcmp(this->getType().c_str(), other.getType().c_str()) < 0;
    return this->getType() < other.getType();
}

#endif // PAYMENT_METHOD_H