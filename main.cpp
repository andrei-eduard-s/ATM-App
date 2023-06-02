#include <iostream>
#include <string>
#include <map>

using namespace std;

class ATM {
private:
    int card_balance; // stores the balance of the card
    string card_type; // stores the type of the card
    map<int, int> bills; // stores the number of bills for each category using key-value pairs container
    bool card_validated; // stores true/false depending on the card validation,
    //  whether it was done successfully or not.
public:
    ATM() {
        // initialize with 10 for each category of bill
        bills[500] = 10;
        bills[200] = 10;
        bills[100] = 10;
        bills[50] = 10;
        bills[20] = 10;
        bills[10] = 10;
        bills[5] = 10;

        card_balance = 0;
        card_type = "";
        card_validated = false;
    }

    bool validate_card(int card_num, int pin) {
        // validate the card number and PIN
        if (pin == 1234) {
            if (card_num % 2 == 0) {
                // even card numbers are Gold cards
                card_type = "Gold";
                card_balance = 1000;
            } else if (card_num % 2 == 1) {
                // odd card numbers are Basic cards
                card_type = "Basic";
                card_balance = 500;
            }
            card_validated = true;
            return card_validated;
        } else {
            return false;
        }
    }

    void display_balance() const {
        // display the current balance of the card
        cout << "Your current balance is " << card_balance << " RON" << endl;
    }

    bool withdraw(int amount) {
        // withdraw the specified amount from the card (if possible)
        if (amount > card_balance) {
            cout << "Insufficient Funds." << endl;
            return false;
        } else if (amount % 10 != 0) {
            cout << "Invalid amount. Please enter a multiple of 10." << endl;
            return false;
        } else {
            // check if ATM has enough bills to cover the withdrawal
            int remaining_amount = amount;
            for (auto i = bills.rbegin(); i != bills.rend(); ++i) {
                int bill_category = i->first;
                int num_bills = i->second;
                int num_needed = remaining_amount / bill_category;
                if (num_needed > num_bills) {
                    // not enough bills of this category
                    remaining_amount -= num_bills * bill_category;
                    bills[bill_category] = 0;
                } else {
                    // enough bills of this category
                    remaining_amount -= num_needed * bill_category;
                    bills[bill_category] -= num_needed;
                }
            }
            if (remaining_amount == 0) {
                // withdrawal successful
                card_balance -= amount;
                cout << "Withdrawal successful. Your new balance is " << card_balance << " RON" << endl;
                return true;
            } else {
                // not enough bills in ATM to cover withdrawal
                cout << "The machine does not have enough funds, please enter a smaller amount." << endl;
                return false;
            }
        }
    }

    void eject_card() {
        // eject the card and reset ATM
        card_balance = 0;
        card_type = "";
        card_validated = false;
        cout << "Card ejected.\n"
                "Thank you for visiting us!" << endl;
    }

    bool is_card_validated() const {
        // check if the card has been validated
        return card_validated;
    }
};

int main() {
    ATM atm;
    cout << "-------- Welcome to Solomon's Bank --------\n"
            "------------- Card numbers: ---------------\n"
            "- Even card numbers are Gold cards  -\n"
            "- Odd card numbers are Basic cards  -\n"
            "-------------------------------------\n";
    int card_num;
    cout << "Enter your credit card number: ";
    cin >> card_num;
    cin.ignore();

    int pin;
    cout << "Enter your PIN: ";
    cin >> pin;
    cin.ignore();

    if (!atm.validate_card(card_num, pin))
        cout << "Invalid card number or PIN. Please try again." << endl;

    while (atm.is_card_validated()) {
        if (atm.validate_card(card_num, pin)) {
            // card validated, display options to the user
            int choice;
            do {
                cout << "Press 1 to display balance." << endl;
                cout << "Press 2 to withdraw money." << endl;
                cout << "Press 3 to eject card." << endl;
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1:
                        system("CLS");
                        atm.display_balance();
                        break;
                    case 2:
                        system("CLS");
                        cout << "Enter amount to withdraw: ";
                        int amount;
                        cin >> amount;
                        cin.ignore();
                        atm.withdraw(amount);
                        break;
                    case 3:
                        system("CLS");
                        atm.eject_card();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            } while (choice != 3);
        } else {
            cout << "Invalid card number or PIN. Please try again." << endl;
        }
    }
    return 0;
}