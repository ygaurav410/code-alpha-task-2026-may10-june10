# Console Banking System (C++)

This project is a console-based Banking System built in C++ for CodeAlpha Task 4.

## Features

- Create customer accounts.
- Generate account numbers.
- Deposit money into an account.
- Withdraw money from an account.
- Transfer funds between accounts.
- View balances and customer details.
- View timestamped transaction history.
- Validate account numbers and transaction amounts.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

Linux or macOS:

```bash
./build/BankingSystem
```

Windows:

```bash
build\BankingSystem.exe
```

## Menu Options

| Option | Action |
| --- | --- |
| 1 | Create Account |
| 2 | View Balance |
| 3 | Deposit Money |
| 4 | Withdraw Money |
| 5 | Funds Transfer |
| 6 | View Customer Information |
| 7 | View Transaction History |
| 8 | Exit |

## Design Overview

- `Customer` stores customer details and generates account numbers.
- `Account` stores account number and balance.
- `Transaction` stores transaction amount, description, timestamp, and balance.
- `BankAccount` groups customer data, account data, and transaction history.

## Limitations

- Data is stored in memory and resets when the program exits.
- There is no PIN or password authentication.
- Floating-point values are used for balances because this is an educational console project.
