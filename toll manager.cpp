#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Function declarations
void displayHeader();
void displayMainMenu();
void checkBalance(double balance);

int main() {
    double walletBalance = 0.0;
    int routeChoice = 0;
    int vehicleClass = 0;
    double tollFare = 0.0;
    char subChoice;
    bool continueProgram = true;

    displayHeader();

    // Student step: Set up initial wallet balance with validation
    cout << "Welcome! Please initialize your starting eWallet balance (RM): ";
    while (!(cin >> walletBalance) || walletBalance < 0) {
        cout << "Invalid input. Please enter a valid positive balance (RM): ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    do {
        displayMainMenu();
        cout << "\nEnter your option (1-4): ";
        cin >> routeChoice;

        // Process route selection
        switch (routeChoice) {
            case 1: // North-South Expressway (PLUS) - Long Distance
                cout << "\n--- Route: North-South Expressway (PLUS) ---" << endl;
                cout << "1. Class 1: Private Passenger Cars" << endl;
                cout << "2. Class 2: Small Commercial Vans/Lorries" << endl;
                cout << "3. Class 3: Heavy Duty Multi-Axle Trucks" << endl;
                cout << "Select vehicle class (1-3): ";
                cin >> vehicleClass;
                
                if (vehicleClass == 1) tollFare = 12.87;      // Simulating KL to Ayer Keroh rate
                else if (vehicleClass == 2) tollFare = 24.50;
                else if (vehicleClass == 3) tollFare = 38.00;
                else {
                    cout << "❌ Invalid vehicle class selection." << endl;
                    continue;
                }
                break;

            case 2: // Shah Alam Expressway (KESAS) - Open Toll Flat Rate
                cout << "\n--- Route: Shah Alam Expressway (KESAS) ---" << endl;
                cout << "1. Class 1: Private Passenger Cars" << endl;
                cout << "2. Class 2: Small Commercial Vans/Lorries" << endl;
                cout << "Select vehicle class (1-2): ";
                cin >> vehicleClass;

                if (vehicleClass == 1) tollFare = 2.00;
                else if (vehicleClass == 2) tollFare = 4.00;
                else {
                    cout << "❌ Invalid vehicle class selection." << endl;
                    continue;
                }
                break;

            case 3: // View current wallet status
                checkBalance(walletBalance);
                tollFare = 0.0; // Reset so transaction doesn't process
                break;

            case 4: // Exit System
                cout << "\nThank you for using the Highway Toll & eWallet Manager. Drive safely!" << endl;
                continueProgram = false;
                break;

            default:
                cout << "❌ Invalid choice! Please select a valid menu option." << endl;
                continue;
        }

        // Process transaction if a route was selected
        if (continueProgram && routeChoice != 3 && routeChoice != 4) {
            cout << fixed << setprecision(2);
            cout << "\n----------------------------------------" << endl;
            cout << "Processing Plaza Transaction..." << endl;
            cout << "Toll Fare Charges : RM " << tollFare << endl;
            cout << "Current Balance   : RM " << walletBalance << endl;

            if (walletBalance >= tollFare) {
                walletBalance -= tollFare;
                cout << "✅ Transaction Successful! Gate Opened." << endl;
                cout << "Updated eWallet Balance: RM " << walletBalance << endl;
            } else {
                cout << "❌ TRANSACTION DENIED: Insufficient eWallet Funds!" << endl;
                cout << "Missing Amount : RM " << (tollFare - walletBalance) << endl;
                cout << "Would you like to top up now? (Y/N): ";
                cin >> subChoice;

                if (subChoice == 'Y' || subChoice == 'y') {
                    double topUpAmount;
                    cout << "Enter top up amount (RM): ";
                    cin >> topUpAmount;
                    if (topUpAmount > 0) {
                        walletBalance += topUpAmount;
                        cout << "✅ Top Up Successful! Current Balance: RM " << walletBalance << endl;
                    } else {
                        cout << "Invalid amount. Transaction aborted." << endl;
                    }
                }
            }
            cout << "----------------------------------------" << endl;
        }

        if (routeChoice != 4) {
            cout << "\nReturn to Main Menu? (y/n): ";
            cin >> subChoice;
            if (subChoice == 'n' || subChoice == 'N') {
                cout << "\nThank you for using the system. Have a safe journey!" << endl;
                continueProgram = false;
            }
        }

    } while (continueProgram);

    return 0;
}

// Visual layout helper for high score on presentation/UX
void displayHeader() {
    cout << "=========================================================" << endl;
    cout << "       HIGHWAY TOLL FARE & EWALLET BALANCE MANAGER       " << endl;
    cout << "   Fundamentals of Digital Competence Course Assignment   " << endl;
    cout << "=========================================================" << endl;
}

void displayMainMenu() {
    cout << "\n**** SYSTEM MAIN MENU ****" << endl;
    cout << "1. Pass Through North-South Expressway (PLUS Plaza)" << endl;
    cout << "2. Pass Through Shah Alam Expressway (KESAS Plaza)" << endl;
    cout << "3. Check eWallet Balance Status" << endl;
    cout << "4. Exit System Application" << endl;
}

void checkBalance(double balance) {
    cout << fixed << setprecision(2);
    cout << "\n=== eWALLET ACCOUNT SUMMARY ===" << endl;
    cout << "Active Status: CONNECTED" << endl;
    cout << "Current Balance: RM " << balance << endl;
    if (balance < 10.00) {
        cout << "⚠️ Warning: Low Balance! Please top up your wallet soon." << endl;
    }
    cout << "===============================" << endl;
}
