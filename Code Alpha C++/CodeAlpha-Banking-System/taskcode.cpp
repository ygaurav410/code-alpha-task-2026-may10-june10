#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct TransactionDetails
{
    int id;
    std::string transactionDate;
    std::string description;
    double amount;
    double balance;
};

struct CustomerDetails
{
    std::string name;
    int age;
    long long nin;
    long long accountNumber;
};

class Customer
{
private:
    std::string firstname;
    std::string surname;
    int age = 0;
    long long nin = 0;

public:
    void setFirstname(const std::string &value)
    {
        firstname = value;
    }

    void setSurname(const std::string &value)
    {
        surname = value;
    }

    void setAge(int value)
    {
        age = value;
    }

    void setNIN(long long value)
    {
        nin = value;
    }

    std::string getName() const
    {
        return surname + " " + firstname;
    }

    int getAge() const
    {
        return age;
    }

    long long getNIN() const
    {
        return nin;
    }
};

class Account
{
private:
    long long accountNumber = 0;
    double accountBalance = 10000.0;

public:
    void setAccountNumber(long long value)
    {
        accountNumber = value;
    }

    long long getAccountNumber() const
    {
        return accountNumber;
    }

    void setAccountBalance(double value)
    {
        accountBalance = value;
    }

    double getAccountBalance() const
    {
        return accountBalance;
    }
};

class Transaction
{
private:
    int id = 0;
    std::string transactionDate;
    std::string description;
    double amount = 0.0;
    double balance = 0.0;

public:
    void setTransaction(int transactionId,
                        const std::string &date,
                        const std::string &transactionDescription,
                        double transactionAmount,
                        double accountBalance)
    {
        id = transactionId;
        transactionDate = date;
        description = transactionDescription;
        amount = transactionAmount;
        balance = accountBalance;
    }

    TransactionDetails getTransactionDetails() const
    {
        return {id, transactionDate, description, amount, balance};
    }
};

struct BankAccount
{
    CustomerDetails customerDetails;
    Account account;
    std::vector<Transaction> transactions;
};

std::unordered_map<long long, BankAccount> bankDatabase;

bool accountExists(long long accountNumber)
{
    return bankDatabase.find(accountNumber) != bankDatabase.end();
}

int getInt(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        try
        {
            size_t processed = 0;
            int value = std::stoi(input, &processed);
            if (processed == input.size())
            {
                return value;
            }
        }
        catch (...)
        {
        }

        std::cout << "Invalid input. Try again.\n";
    }
}

long long getLongLong(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        try
        {
            size_t processed = 0;
            long long value = std::stoll(input, &processed);
            if (processed == input.size())
            {
                return value;
            }
        }
        catch (...)
        {
        }

        std::cout << "Invalid input. Try again.\n";
    }
}

double getMoney(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        try
        {
            size_t processed = 0;
            double value = std::stod(input, &processed);
            if (processed == input.size() && value > 0.0)
            {
                return value;
            }
        }
        catch (...)
        {
        }

        std::cout << "Enter an amount greater than 0.\n";
    }
}

std::string getString(const std::string &prompt)
{
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &nowTime);
#else
    localtime_r(&nowTime, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

bool performOperation()
{
    while (true)
    {
        std::string choice = getString("\nDo you wish to perform another operation? (y/n): ");

        if (choice == "y" || choice == "Y")
        {
            return true;
        }

        if (choice == "n" || choice == "N")
        {
            std::cout << "\nThank you for using this Banking System. Exiting...\n";
            return false;
        }

        std::cout << "Invalid choice! Please enter y or n.\n";
    }
}

bool isNINValid(long long nin)
{
    return nin >= 10000000000LL && nin <= 99999999999LL;
}

long long generateAccountNumber()
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<long long> distribution(1000000000LL, 1999999999LL);

    long long accountNumber = 0;
    do
    {
        accountNumber = distribution(generator);
    } while (accountExists(accountNumber));

    return accountNumber;
}

void addTransaction(BankAccount &bankAccount,
                    const std::string &description,
                    double amount,
                    double balance)
{
    Transaction transaction;
    int transactionId = static_cast<int>(bankAccount.transactions.size()) + 1;
    transaction.setTransaction(transactionId, getCurrentDateTime(), description, amount, balance);
    bankAccount.transactions.push_back(transaction);
}

void CreateAccount()
{
    Customer customer;
    Account account;

    std::cout << "\nYou are welcome to this banking system.\n";
    std::cout << "Kindly provide your details.\n";

    std::string surname;
    do
    {
        surname = getString("\nEnter your last name (surname): ");
        if (surname.empty())
        {
            std::cout << "Surname cannot be empty.\n";
        }
    } while (surname.empty());

    std::string firstname;
    do
    {
        firstname = getString("Enter your first name: ");
        if (firstname.empty())
        {
            std::cout << "First name cannot be empty.\n";
        }
    } while (firstname.empty());

    int age = 0;
    while (age < 18)
    {
        age = getInt("Enter your age: ");
        if (age < 18)
        {
            std::cout << "You must be at least 18 years old to create an account.\n";
        }
    }

    long long nin = 0;
    do
    {
        nin = getLongLong("Enter your NIN number: ");
        if (!isNINValid(nin))
        {
            std::cout << "Invalid NIN. NIN must be exactly 11 digits.\n";
        }
    } while (!isNINValid(nin));

    customer.setSurname(surname);
    customer.setFirstname(firstname);
    customer.setAge(age);
    customer.setNIN(nin);

    long long accountNumber = generateAccountNumber();
    account.setAccountNumber(accountNumber);

    CustomerDetails details;
    details.name = customer.getName();
    details.age = customer.getAge();
    details.nin = customer.getNIN();
    details.accountNumber = accountNumber;

    bankDatabase[accountNumber] = {details, account, {}};

    std::cout << "\nAccount created successfully!\n";
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Opening Balance: " << std::fixed << std::setprecision(2)
              << account.getAccountBalance() << "\n";
}

void BalanceEnquiry()
{
    long long accountNumber = getLongLong("\nEnter account number: ");

    if (!accountExists(accountNumber))
    {
        std::cout << "Invalid account number!\n";
        return;
    }

    BankAccount &bankAccount = bankDatabase[accountNumber];
    std::cout << "\nAccount Balance: " << std::fixed << std::setprecision(2)
              << bankAccount.account.getAccountBalance() << "\n";
}

void DepositFund()
{
    long long accountNumber = getLongLong("\nEnter account number: ");

    if (!accountExists(accountNumber))
    {
        std::cout << "Invalid account number!\n";
        return;
    }

    double depositAmount = getMoney("Enter amount to deposit: ");

    BankAccount &bankAccount = bankDatabase[accountNumber];
    double newBalance = bankAccount.account.getAccountBalance() + depositAmount;
    bankAccount.account.setAccountBalance(newBalance);
    addTransaction(bankAccount, "Deposit", depositAmount, newBalance);

    std::cout << "Amount " << std::fixed << std::setprecision(2)
              << depositAmount << " successfully deposited.\n";
}

void Withdrawal()
{
    long long accountNumber = getLongLong("\nPlease enter your account number: ");

    if (!accountExists(accountNumber))
    {
        std::cout << "Invalid account number!\n";
        return;
    }

    BankAccount &bankAccount = bankDatabase[accountNumber];
    double currentBalance = bankAccount.account.getAccountBalance();
    std::cout << "Your account balance: " << std::fixed << std::setprecision(2)
              << currentBalance << "\n";

    double withdrawalAmount = getMoney("Please enter how much you would like to withdraw: ");
    if (withdrawalAmount > currentBalance)
    {
        std::cout << "Insufficient funds!\n";
        return;
    }

    double newBalance = currentBalance - withdrawalAmount;
    bankAccount.account.setAccountBalance(newBalance);
    addTransaction(bankAccount, "Withdrawal", withdrawalAmount, newBalance);

    std::cout << "You have successfully withdrawn " << std::fixed << std::setprecision(2)
              << withdrawalAmount << ".\nYour account balance is: " << newBalance << "\n";
}

void Transfer()
{
    long long senderAccountNumber = getLongLong("\nEnter sender account number: ");

    if (!accountExists(senderAccountNumber))
    {
        std::cout << "Invalid sender account number!\n";
        return;
    }

    long long recipientAccountNumber = getLongLong("Enter recipient account number: ");

    if (!accountExists(recipientAccountNumber))
    {
        std::cout << "Invalid recipient account number!\n";
        return;
    }

    if (senderAccountNumber == recipientAccountNumber)
    {
        std::cout << "Sender and recipient accounts must be different.\n";
        return;
    }

    BankAccount &sender = bankDatabase[senderAccountNumber];
    BankAccount &recipient = bankDatabase[recipientAccountNumber];

    double senderBalance = sender.account.getAccountBalance();
    std::cout << "Your available balance: " << std::fixed << std::setprecision(2)
              << senderBalance << "\n";
    std::cout << "Recipient: " << recipient.customerDetails.name << "\n";

    double amount = getMoney("Enter amount to transfer: ");
    if (amount > senderBalance)
    {
        std::cout << "Insufficient funds!\n";
        return;
    }

    double recipientBalance = recipient.account.getAccountBalance() + amount;
    recipient.account.setAccountBalance(recipientBalance);
    addTransaction(recipient, "Transfer Received", amount, recipientBalance);

    double newSenderBalance = senderBalance - amount;
    sender.account.setAccountBalance(newSenderBalance);
    addTransaction(sender, "Fund Transfer", amount, newSenderBalance);

    std::cout << "Fund successfully sent to "
              << recipient.customerDetails.name << ".\n";
}

void CustomerInfo()
{
    long long accountNumber = getLongLong("\nEnter account number: ");

    if (!accountExists(accountNumber))
    {
        std::cout << "Account not found!\n";
        return;
    }

    BankAccount &bankAccount = bankDatabase[accountNumber];
    CustomerDetails &info = bankAccount.customerDetails;

    std::cout << "\nAccount Number: " << info.accountNumber;
    std::cout << "\nOwner's Name: " << info.name;
    std::cout << "\nOwner's Age: " << info.age;
    std::cout << "\nOwner's NIN: " << info.nin;
    std::cout << "\nAccount Balance: " << std::fixed << std::setprecision(2)
              << bankAccount.account.getAccountBalance() << "\n";
}

void TransactionHistory()
{
    long long accountNumber = getLongLong("\nEnter account number: ");

    if (!accountExists(accountNumber))
    {
        std::cout << "Account not found!\n";
        return;
    }

    BankAccount &bankAccount = bankDatabase[accountNumber];
    if (bankAccount.transactions.empty())
    {
        std::cout << "No transactions found for this account.\n";
        return;
    }

    for (const Transaction &transaction : bankAccount.transactions)
    {
        TransactionDetails history = transaction.getTransactionDetails();
        std::cout << "\nTransaction ID: " << history.id;
        std::cout << "\nTransaction Date: " << history.transactionDate;
        std::cout << "\nTransaction Description: " << history.description;
        std::cout << "\nTransaction Amount: " << std::fixed << std::setprecision(2)
                  << history.amount;
        std::cout << "\nBalance: " << history.balance << "\n";
    }
}

int main()
{
    while (true)
    {
        std::cout << "\n=====================================\n";
        std::cout << "      WELCOME TO THE BANKING SYSTEM\n";
        std::cout << "=====================================\n";
        std::cout << "Please select an operation below:\n\n";

        std::cout << "  1. Create Account\n";
        std::cout << "  2. View Balance\n";
        std::cout << "  3. Deposit Money\n";
        std::cout << "  4. Withdraw Money\n";
        std::cout << "  5. Funds Transfer\n";
        std::cout << "  6. View Customer Info\n";
        std::cout << "  7. Print Transaction History\n";
        std::cout << "  8. Exit\n";

        int choice = getInt("\nEnter your option (1-8): ");

        if (choice == 1)
        {
            CreateAccount();
        }
        else if (choice == 2)
        {
            BalanceEnquiry();
        }
        else if (choice == 3)
        {
            DepositFund();
        }
        else if (choice == 4)
        {
            Withdrawal();
        }
        else if (choice == 5)
        {
            Transfer();
        }
        else if (choice == 6)
        {
            CustomerInfo();
        }
        else if (choice == 7)
        {
            TransactionHistory();
        }
        else if (choice == 8)
        {
            std::cout << "\nThank you for using this Banking System. Exiting...\n";
            break;
        }
        else
        {
            std::cout << "\nInvalid option! Please try again.\n";
            continue;
        }

        if (!performOperation())
        {
            break;
        }
    }

    return 0;
}
