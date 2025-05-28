#pragma once
#include "PaymentMethod.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

class PaymentProcessor {
private:
    std::vector<PaymentMethod*> payments;
    std::vector<std::pair<PaymentMethod*, double>> transactions;

public:
    bool addMethod(PaymentMethod* method);
    bool removeMethod(PaymentMethod* method);
    unsigned processAll(double amount);
    unsigned getTotalProcessed() const;
    void sortMethods();
};

bool PaymentProcessor::addMethod(PaymentMethod* method) {

    if(!method->validate()) {
        throw std::invalid_argument("Invalid method!");
    }
    this->payments.push_back(method);
    return true;
}

bool PaymentProcessor::removeMethod(PaymentMethod* method) {

    for(int i = 0; i < payments.size(); ++i) {
        PaymentMethod* current = payments[i];
        if(current == method) {
            payments.erase(payments.begin() + i);
            return true;
        }
    }

    return false;
}

unsigned PaymentProcessor::processAll(double amount) {

    if(amount < 0) throw std::invalid_argument("ne stava");
    unsigned successCount = 0;

    for(PaymentMethod* p : payments) {
        bool s = p->pay(amount);
        if(s) {
            successCount++;
            this->transactions.push_back(std::pair(p, amount));
        }

    }

    return successCount;
}

unsigned PaymentProcessor::getTotalProcessed() const {
    double sum;

    for(auto p : transactions) {
        sum += p.second;
    }
    return sum;
}

void PaymentProcessor::sortMethods() {

    // Bubble sort

    int size = payments.size();

    for(int i = 0; i < size; i ++) {
        PaymentMethod* currentI = payments[i];
        for (int j = i + 1; j < size - 1; j++) {
            PaymentMethod* currentJ = payments[j];
            if(*currentJ < *currentI) {
                //swap
                std::swap(currentI, currentJ);
            }
        }
    }
}
