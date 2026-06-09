# Login and Registration System (C++)

This project is a console-based Login and Registration System built in C++ for CodeAlpha Task 2.

## Features

- Register users with a username and password.
- Validate password strength.
- Prevent duplicate usernames.
- Store password hashes in a local file.
- Verify login credentials.
- Show clear success and error messages.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

Linux or macOS:

```bash
./build/AuthenticationSystem
```

Windows:

```bash
build\AuthenticationSystem.exe
```

## Menu Options

| Option | Action |
| --- | --- |
| 1 | Register a new user |
| 2 | Login with existing credentials |
| 3 | Exit |

## Data Storage

The application stores users in:

```text
data/users.txt
```

Each line uses this format:

```text
username|password_hash
```

Passwords are never stored as plain text.

## Password Rules

Passwords must have:

- At least 8 characters.
- At least one uppercase letter.
- At least one lowercase letter.
- At least one digit.

## Notes

The password hash is deterministic for this educational project, but it is not a replacement for a production password hashing algorithm such as Argon2, bcrypt, or scrypt.
