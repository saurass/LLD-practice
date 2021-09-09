#include<bits/stdc++.h>
using namespace std;

class Product {
    string name;
    int price;
public:
    Product(string name, int price) {
        this->name = name;
        this->price = price;
    }

    string getName() {
        return this->name;
    }

    int getPrice() {
        return this->price;
    }

    string productDetail() {
        return this->name + " " + to_string(this->price);
    }
};

class Store {

    unordered_map<Product*, int> store;

    int countLeftProduct(Product *productRef) {
        return this->store[productRef];
    }

public:
    bool addProduct(Product *productRef, int quantity) {
        this->store[productRef] += quantity;
        return true;
    }

    string getMenu() {
        string retval = "";
        for(auto x: this->store) {
            if(x.second > 0)
                retval += x.first->productDetail() + "\n";
        }
        return retval;
    }

    bool canDispense(Product *productRef) {
        return this->countLeftProduct(productRef) > 0;
    }

    string dispenseProduct(Product *productRef) {
        if(canDispense(productRef)) {
            return "Enjoy your " + productRef->getName();
        } else {
            return "Dispense not possible";
        }
    }

};

class Vault {

    int totalMoney;

public:
    Vault() {
        this->totalMoney = 1000;
    }

    string takeMoney(int moneyGiven, int moneyToTake) {
        if(!isTransactionPossible(moneyGiven, moneyToTake)) {
            return "Transaction Error";
        } else {
            this->totalMoney += moneyToTake;
            return "Thanks for using machine. Please take change - " + to_string(moneyGiven - moneyToTake);
        }
    }

    bool isTransactionPossible(int moneyGiven, int moneyToTake) {
        if(moneyGiven < moneyToTake)
            return false;
        return this->totalMoney >= (moneyGiven - moneyToTake);
    }
    
    int moneyLeft() {
        return this->totalMoney;
    }

};

class VendingMachine {
    int currentState;
    Store store;
    Vault vault;
    Product *selectedProduct;
    string ERROR_MESSAGE = "Operation Failed, Machine Is busy";
    bool setState(int newState) {
        bool retval = false;
        if((this->currentState + 1) % 4 == newState || this->currentState == 4)
            retval = true;
        if((this->currentState == 3 || this->currentState == 0 || this->currentState == 4) && newState == 4)
            retval = true;
        
        if(retval)
            this->currentState = newState;
        
        return retval;
    }

    string dispenseProduct() {
        cout << "=>Dispensing your product\n";
        if(!setState(3))
            return ERROR_MESSAGE;
        return this->store.dispenseProduct(this->selectedProduct);
    }

public:
    VendingMachine() {
        this->store = Store();
        this->vault = Vault();
        this->currentState = 0;
    }

    string addProduct(Product *productRef, int quantity) {
        cout << "=> Adding product " + productRef->getName() +" in store\n";
        if(!setState(4))
            return ERROR_MESSAGE;
        bool isSuccess = this->store.addProduct(productRef, quantity);
        if(isSuccess)
            return "Product addition success";
        else
            return "Product Addition failed";
    }

    string showMenu() {
        if(!setState(0))
            return ERROR_MESSAGE;
        return this->store.getMenu();
    }

    string selectProduct(Product *productRef) {
        cout << "=>Selecting Product\n";
        if(!setState(1))
            return ERROR_MESSAGE;
        if(this->store.canDispense(productRef)) {
            this->selectedProduct = productRef;
            return "Product Selection Success";
        } else {
            return "Product selection failed";
        }
    }

    string makeTransaction(int moneyGiven) {
        if(!setState(2))
            return ERROR_MESSAGE;
        string retval = "";
        retval += this->dispenseProduct() + "\n";
        retval += this->vault.takeMoney(moneyGiven, this->selectedProduct->getPrice());
        return retval;
    }

};

int main() {
    VendingMachine machine = VendingMachine();

    Product chanaProduct = Product("chana", 30);
    Product riceProduct = Product("rice", 23);
    
    cout << machine.addProduct(&chanaProduct, 100) << endl;
    cout << machine.addProduct(&riceProduct, 20) << endl;

    cout << machine.showMenu() << endl;

    cout << machine.selectProduct(&chanaProduct) << endl;
    cout << machine.makeTransaction(400) << endl;
    

    
    return 0;
}