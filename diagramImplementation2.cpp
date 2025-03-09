#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

class Product {
private:
    string productId;
    string name;
    float price;
    string productDescription;

public:
    Product(string id, string n, float p, string desc)
        : productId(id), name(n), price(p), productDescription(desc) {}

    string getProductId() const { return productId; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    string getProductDescription() const { return productDescription; }
};

class Order {
private:
    int orderId;
    float totalAmount;
    vector<pair<Product, int>> orderItems;

public:
    Order(int id, const vector<pair<Product, int>>& items, float total)
        : orderId(id), orderItems(items), totalAmount(total) {}

    void displayOrder() const {
        cout << "\nOrder ID: " << orderId << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "Order Details:\n";
        cout << left << setw(15) << "Product ID" << setw(20) << "Name"
             << setw(10) << "Price" << setw(15) << "Quantity" << "Description\n";
        cout << "------------------------------------------------------------------\n";
        for (const auto& item : orderItems) {
            cout << left << setw(15) << item.first.getProductId()
                 << setw(20) << item.first.getName()
                 << setw(10) << fixed << setprecision(2) << item.first.getPrice()
                 << setw(15) << item.second
                 << item.first.getProductDescription() << endl;
        }
    }
};

class ShoppingCart {
private:
    vector<pair<Product, int>> productLists;
    vector<Order>& orderHistory;
    int& orderCount;

public:
    ShoppingCart(vector<Order>& orders, int& count) : orderHistory(orders), orderCount(count) {}

    void addItem(const Product& product, int quantity) {
        for (auto& item : productLists) {
            if (item.first.getProductId() == product.getProductId()) {
                item.second += quantity;
                cout << "Product added successfully!\n";
                return;
            }
        }
        productLists.emplace_back(product, quantity);
        cout << "Product added successfully!\n";
    }

    void checkout() {
        if (productLists.empty()) {
            cout << "Shopping cart is empty. Cannot checkout.\n";
            return;
        }
        float total = calculateTotal();
        orderHistory.emplace_back(++orderCount, productLists, total);
        productLists.clear();
        cout << "Checkout successful! Order placed.\n";
    }

    void displayCart() {
        if (productLists.empty()) {
            cout << "Shopping cart is empty.\n";
            return;
        }
        cout << "\nShopping Cart:\n";
        cout << left << setw(15) << "Product ID" << setw(20) << "Name"
             << setw(10) << "Price" << setw(15) << "Quantity" << "Description\n";
        cout << "------------------------------------------------------------------\n";
        for (const auto& item : productLists) {
            cout << left << setw(15) << item.first.getProductId()
                 << setw(20) << item.first.getName()
                 << setw(10) << fixed << setprecision(2) << item.first.getPrice()
                 << setw(15) << item.second
                 << item.first.getProductDescription() << endl;
        }
        cout << "Total: $" << fixed << setprecision(2) << calculateTotal() << endl;
        
        cout << "\nDo you want to checkout? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            checkout();
        }
    }

    float calculateTotal() const {
        float total = 0;
        for (const auto& item : productLists) {
            total += item.first.getPrice() * item.second;
        }
        return total;
    }
};

int getValidChoice() {
    string input;
    while (true) {
        cout << "Enter your choice (1-4): ";
        cin >> input;
        if (input.length() == 1 && isdigit(input[0]) && input[0] >= '1' && input[0] <= '4') {
            return input[0] - '0';
        }
        cout << "Invalid input! Please enter a number between 1 and 4.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    vector<Product> products = {
        Product("ABC123", "50 dias", 50.0, "50 + 5 dias"),
        Product("DEF456", "100 dias", 98.0, "100 + 10 dias"),
        Product("GHI789", "250", 230.0, "250 + 30 dias"),
        Product("JKL012", "Starlight", 300.0, "1 Starlight Card"),
        Product("MNO345", "500 dias", 500.0, "500 + 50 dias")
    };

    vector<Order> orderHistory;
    int orderCount = 0;
    ShoppingCart cart(orderHistory, orderCount);

    cout << fixed << setprecision(2);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";

        int choice = getValidChoice();

        if (choice == 1) {
            cout << "\nAvailable Products:\n";
            cout << left << setw(15) << "Product ID" << setw(20) << "Name"
                 << setw(10) << "Price" << "Description\n";
            cout << "------------------------------------------------------\n";
            for (const auto& product : products) {
                cout << left << setw(15) << product.getProductId()
                     << setw(20) << product.getName()
                     << setw(10) << fixed << setprecision(2) << product.getPrice()
                     << product.getProductDescription() << endl;
            }
            
            cout << "\nEnter Product ID to add to cart (or type '0' to cancel): ";
            string productId;
            cin >> productId;
            if (productId != "0") {
                for (const auto& product : products) {
                    if (product.getProductId() == productId) {
                        cout << "Enter quantity: ";
                        int quantity;
                        cin >> quantity;
                        cart.addItem(product, quantity);
                        break;
                    }
                }
            }
        } else if (choice == 2) {
            cart.displayCart();
        } else if (choice == 3) {
            for (const Order& order : orderHistory) order.displayOrder();
        } else if (choice == 4) {
            cout << "Exiting program...\n";
            break;
        }
    }
    return 0;
    
}
