// You are given a shopping cart with items represented as a list of characters, for example ['A', 'A', 'A', 'B', 'B', 'C']. Each item has a unit price and may have an optional bulk pricing rule. The pricing is as follows:

// A costs ₹50, or ₹130 for 3 units

// B costs ₹30, or ₹45 for 2 units

// C costs ₹20

// D costs ₹15

// You need to calculate the total cart value by applying the most cost-effective pricing — that is, apply the bulk price as many times as possible, and charge the remaining items at unit price.

// Input:
// cart = ['A', 'A', 'A', 'B', 'B', 'C']

// Output:
// Total = ₹195

// Explanation:

// A ×3 → apply bulk offer → ₹130

// B ×2 → apply bulk offer → ₹45

// C ×1 → unit price → ₹20
// Total = 130 + 45 + 20 = ₹195

 //self done 
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Product {
public:
    char code;
    int unit_price;
    int bulk_qty;
    int bulk_price;
    Product() {
    code = '\0';
    unit_price = 0;
    bulk_qty = 0;
    bulk_price = 0;
}
// above consturct is just because in chekout we have used map<char,product> so for default value like map[z] there should construct wiht zero argument

    Product(char c, int u, int bq = 0, int bp = 0) {
        code = c;
        unit_price = u;
        bulk_qty = bq;
        bulk_price = bp;
    }
};

class Checkout {
private:
    map<char, Product> pricing_rules;

public:
    Checkout() {
        // Initialize pricing rules
        pricing_rules['A'] = Product('A', 50, 3, 130);
        pricing_rules['B'] = Product('B', 30, 2, 45);
        pricing_rules['C'] = Product('C', 20);
        pricing_rules['D'] = Product('D', 15);
    }

    int calculateTotal(  string s) {
        map<char, int> item_count;
        for (char item : s) {
            item_count[item]++;
        }

        int total = 0;
        for (auto it : item_count) {
            char item = it.first;
            int count = it.second;
            Product prod = pricing_rules[item];

            if (prod.bulk_qty > 0) {
                int bulk_sets = count / prod.bulk_qty;
                int remainder = count % prod.bulk_qty;
                total += bulk_sets * prod.bulk_price + remainder * prod.unit_price;
            } else {
                // No bulk pricing
                total += count * prod.unit_price;
            }
        }
        return total;
    }
};

int main() {
    string cart="AAABBC";
    Checkout checkout;
    int total = checkout.calculateTotal(cart);
    cout << "Total =" << total << endl;

    return 0;
}
