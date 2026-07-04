
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Function Prototypes
void registerUser();
bool loginUser();
bool userExists(const string& username);
void clearBuffer();

int main() {
    int choice;

    while (true) {
        cout << "\n=========================================" << endl;
        cout << "      LOGIN & REGISTRATION SYSTEM        " << endl;
        cout << "=========================================" << endl;
        cout << "1. Register an Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Enter your choice (1-3): ";
        
        if (!(cin >> choice)) {
            cout << "[ERROR] Invalid input! Please enter a number." << endl;
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    cout << "\n[SUCCESS] Access Granted! Welcome to the secure dashboard." << endl;
                } else {
                    cout << "\n[ERROR] Access Denied! Incorrect username or password." << endl;
                }
                break;
            case 3:
                cout << "\nThank you for using the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "[ERROR] Invalid choice! Please select 1, 2, or 3." << endl;
        }
    }
    return 0;
}

// Utility function to safely clean out input stream errors
void clearBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Check if the username file already exists to prevent duplicates
bool userExists(const string& username) {
    ifstream file(username + ".txt");
    return file.good(); 
}

// Handle Account Registration
void registerUser() {
    string username, password;

    cout << "\n--- CREATE NEW ACCOUNT ---" << endl;
    cout << "Enter a unique username (no spaces): ";
    cin >> username;

    if (userExists(username)) {
        cout << "\n[ERROR] Registration failed! Username '" << username << "' is already taken." << endl;
        clearBuffer(); // Clean up lingering inputs
        return;
    }

    cout << "Enter a secure password (no spaces): ";
    cin >> password;

    ofstream file(username + ".txt");
    
    if (file.is_open()) {
        file << username << endl;
        file << password << endl;
        file.close();
        cout << "\n[SUCCESS] Registration complete! You can now log in." << endl;
    } else {
        cout << "\n[ERROR] System error. Could not save user credentials." << endl;
    }
    clearBuffer();
}

// Handle Account Login
bool loginUser() {
    string username, password;
    string storedUser, storedPass;

    cout << "\n--- USER LOGIN ---" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file(username + ".txt");
    
    if (!file.is_open()) {
        clearBuffer();
        return false;
    }

    if (getline(file, storedUser) && getline(file, storedPass)) {
        file.close();
        clearBuffer();
        if (username == storedUser && password == storedPass) {
            return true;
        }
    }

    file.close();
    clearBuffer();
    return false;
}