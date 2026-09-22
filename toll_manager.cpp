#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Structure to track user account and eWallet details
struct WalletAccount {
    string ownerName;
    string vehiclePlate;
    double eWalletBalance;
};

// Function prototypes
void displayHeader();
void processTollJourney(WalletAccount &acc);
void reloadWallet(WalletAccount &acc);

int main() {
    WalletAccount driver;
    int choice;

    cout << "=== HIGHWAY TOLL & eWALLET INITIALIZATION ===" << endl;
    cout << "Enter Driver Name: ";
    getline(cin, driver.ownerName);
    cout << "Enter Vehicle Plate Number (e.g., ABC1234): ";
    cin >> driver.vehiclePlate;
    cout << "Initial eWallet Balance (RM): ";
    cin >> driver.eWalletBalance;

    do {
        displayHeader();
        cout << "\n[MAIN DASHBOARD - Welcome, " << driver.ownerName << "]" << endl;
        cout << "Vehicle Plate : " << driver.vehiclePlate << endl;
        cout << "Current eWallet Balance : RM " << fixed << setprecision(2) << driver.eWalletBalance << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Simulate RFID Toll Journey & Fare Deduction" << endl;
        cout << "2. Reload eWallet Balance" << endl;
        cout << "3. Exit System" << endl;
        cout << "Select an option (1-3): ";
        cin >> choice;

        // Input error handling for non-integer choices
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[Error] Invalid input type. Please enter a numerical option (1-3).\n";
            continue;
        }

        switch (choice) {
            case 1:
                processTollJourney(driver);
                break;
            case 2:
                reloadWallet(driver);
                break;
            case 3:
                cout << "\nThank you for using the Smart Highway Toll & eWallet Manager. Drive safely!\n";
                break;
            default:
                cout << "\n[Error] Invalid option. Please select between 1 and 3.\n";
        }

    } while (choice != 3);

    return 0;
}

void displayHeader() {
    cout << "\n==================================================" << endl;
    cout << "      SMART RFID TOLL & eWALLET GATEWAY SYSTEM    " << endl;
    cout << "==================================================" << endl;
}

void processTollJourney(WalletAccount &acc) {
    int entryZone, exitZone;
    double fareRate = 0.0;

    cout << "\n--- SELECT HIGHWAY TOLL PLAZAS ---" << endl;
    cout << "1. Plaza North (Jitra)" << endl;
    cout << "2. Plaza Central (Sungai Buloh)" << endl;
    cout << "3. Plaza South (Skudai)" << endl;
    cout << "Enter Entry Plaza (1-3): ";
    cin >> entryZone;
    cout << "Enter Exit Plaza (1-3): ";
    cin >> exitZone;

    // Validate plaza inputs
    if (entryZone < 1 || entryZone > 3 || exitZone < 1 || exitZone > 3) {
        cout << "\n[Error] Invalid toll plaza selected. Journey aborted.\n";
        return;
    }

    if (entryZone == exitZone) {
        cout << "\n[Notice] Entry and Exit plazas are identical. Flat minimum fee applied: RM 2.00\n";
        fareRate = 2.00;
    } else {
        int distanceUnit = abs(exitZone - entryZone);
        fareRate = 5.80 * distanceUnit; // Distance-based calculation mock
    }

    cout << "Calculated Toll Fare: RM " << fixed << setprecision(2) << fareRate << endl;

    // Check balance adequacy
    if (acc.eWalletBalance < fareRate) {
        cout << "[TRANSACTION DECLINED] Insufficient eWallet balance!" << endl;
        cout << "RFID barrier will not open. Please reload your account or back up to cash/SmartTAG lane.\n";
    } else {
        acc.eWalletBalance -= fareRate;
        cout << "[SUCCESS] RFID scanner verified. Toll fee deducted successfully." << endl;
        cout << "Updated eWallet Balance: RM " << fixed << setprecision(2) << acc.eWalletBalance << endl;
        
        // Low balance notification threshold
        if (acc.eWalletBalance < 15.00) {
            cout << "[WARNING] Your eWallet balance is below RM 15.00. Auto-reload recommended!\n";
        }
    }
    cout << "==================================================" << endl;
}

void reloadWallet(WalletAccount &acc) {
    double reloadAmount;
    cout << "\n--- eWALLET INSTANT RELOAD KIOSK ---" << endl;
    cout << "Enter amount to reload (RM): ";
    cin >> reloadAmount;

    if (reloadAmount <= 0) {
        cout << "[Error] Reload amount must be greater than zero.\n";
    } else {
        acc.eWalletBalance += reloadAmount;
        cout << "[SUCCESS] eWallet successfully reloaded. New Balance: RM " << fixed << setprecision(2) << acc.eWalletBalance << endl;
    }
    cout << "==================================================\n";
}