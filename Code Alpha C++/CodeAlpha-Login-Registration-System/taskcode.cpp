#include <algorithm>
#include <cctype>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

const string DATA_DIR = "data";
const string USERS_FILE = "data/users.txt";

int getInt(const string &message)
{
    while (true)
    {
        cout << message;
        string input;
        getline(cin, input);

        try
        {
            size_t processed = 0;
            int value = stoi(input, &processed);
            if (processed == input.size())
            {
                return value;
            }
        }
        catch (...)
        {
        }

        cout << "\n[Input Error] Please enter a valid number.\n";
    }
}

string getString(const string &message)
{
    cout << message;
    string input;
    getline(cin, input);
    return input;
}

bool hasCharacterType(const string &value, int (*check)(int))
{
    return any_of(value.begin(), value.end(), [check](unsigned char ch) {
        return check(ch) != 0;
    });
}

bool isPasswordStrong(const string &password)
{
    return password.length() >= 8 &&
           hasCharacterType(password, ::isdigit) &&
           hasCharacterType(password, ::isupper) &&
           hasCharacterType(password, ::islower);
}

bool isUsernameValid(const string &username)
{
    if (username.empty())
    {
        return false;
    }

    return none_of(username.begin(), username.end(), [](unsigned char ch) {
        return isspace(ch) || ch == '|';
    });
}

string hashPassword(const string &password)
{
    // FNV-1a gives this educational app a deterministic hash across runs.
    uint64_t hash = 1469598103934665603ULL;
    for (unsigned char ch : password)
    {
        hash ^= ch;
        hash *= 1099511628211ULL;
    }

    ostringstream out;
    out << hex << setw(16) << setfill('0') << hash;
    return out.str();
}

void ensureDataDirectory()
{
    filesystem::create_directories(DATA_DIR);
}

unordered_map<string, string> loadUsers()
{
    unordered_map<string, string> users;
    ifstream file(USERS_FILE);

    string line;
    while (getline(file, line))
    {
        size_t separator = line.find('|');
        if (separator == string::npos)
        {
            continue;
        }

        string username = line.substr(0, separator);
        string passwordHash = line.substr(separator + 1);
        if (!username.empty() && !passwordHash.empty())
        {
            users[username] = passwordHash;
        }
    }

    return users;
}

bool usernameExists(const string &username)
{
    unordered_map<string, string> users = loadUsers();
    return users.find(username) != users.end();
}

string addUser(const string &username, const string &passwordHash)
{
    ensureDataDirectory();

    ofstream file(USERS_FILE, ios::app);
    if (!file)
    {
        return "Registration failed: unable to open user file.";
    }

    file << username << '|' << passwordHash << '\n';
    return "success";
}

string retrieveUserCredentials(const string &username)
{
    unordered_map<string, string> users = loadUsers();
    auto it = users.find(username);
    if (it == users.end())
    {
        return "";
    }

    return it->second;
}

string registerUser(const string &username, const string &password)
{
    if (!isUsernameValid(username))
    {
        return "[Validation Error] Username cannot be empty and must not contain spaces or '|'.";
    }

    if (usernameExists(username))
    {
        return "[Validation Error] Username already exists. Please choose another.";
    }

    string result = addUser(username, hashPassword(password));
    if (result != "success")
    {
        return result;
    }

    return "Registration successful! You can now log in.";
}

string loginUser(const string &username, const string &password)
{
    string storedHash = retrieveUserCredentials(username);

    if (storedHash.empty())
    {
        return "[Login Failed] Username not found.";
    }

    if (hashPassword(password) != storedHash)
    {
        return "[Login Failed] Incorrect password.";
    }

    return "Login successful! Welcome back.";
}

void Register()
{
    cout << "\n--- USER REGISTRATION ---\n";

    string username = getString("Enter username: ");
    string password;

    while (true)
    {
        password = getString("Enter password: ");

        if (isPasswordStrong(password))
        {
            break;
        }

        cout << "\n[Password Weak]\n"
             << "- Minimum 8 characters\n"
             << "- At least one uppercase letter\n"
             << "- At least one lowercase letter\n"
             << "- At least one number\n\n";
    }

    cout << "\n"
         << registerUser(username, password) << endl;
}

void Login()
{
    cout << "\n--- USER LOGIN ---\n";

    string username = getString("Username: ");
    string password = getString("Password: ");

    cout << "\n"
         << loginUser(username, password) << endl;
}

int main()
{
    cout << "Welcome to this Login & Registration System\n";

    while (true)
    {
        cout << "\nWhat would you like to do?\n"
             << "1. Register\n"
             << "2. Login\n"
             << "3. Exit\n";

        int choice = getInt("Your option (1-3): ");

        if (choice == 1)
        {
            Register();
        }
        else if (choice == 2)
        {
            Login();
        }
        else if (choice == 3)
        {
            cout << "\nThank you for using the system. Goodbye!\n";
            break;
        }
        else
        {
            cout << "\n[Input Error] Invalid menu option.\n";
        }

        string cont = getString("\nDo you want to perform another operation? (y/n): ");
        if (cont != "y" && cont != "Y")
        {
            cout << "\nSession ended. Stay safe!\n";
            break;
        }
    }

    return 0;
}
