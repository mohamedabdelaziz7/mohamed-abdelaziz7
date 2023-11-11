#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

// User structure
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    union {
        unsigned int flags;
    };
} User;

// Array to store registered users
User users[MAX_USERS];

// Number of registered users
int numUsers = 0;

// Function to register a new user
void registerUser() {
    if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached. Cannot register new user.\n");
        return;
    }

    User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);

    printf("Enter password: ");
    scanf("%s", newUser.password);

    printf("Set active flag (0 for False, 1 for True): ");
    scanf("%u", &newUser.flags);

    users[numUsers] = newUser;
    numUsers++;

    printf("User registered successfully.\n");
}

// Function to authenticate a user
int authenticateUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (users[i].flags) {
                return i;
            } else {
                printf("This user is currently inactive. Please contact the administrator.\n");
                return -1;
            }
        }
    }

    return -1;
}

int main() {
    int option;
    int loggedInUserIndex = -1;

    do {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedInUserIndex = authenticateUser();
                if (loggedInUserIndex != -1) {
                    printf("Login successful. Welcome, %s!\n", users[loggedInUserIndex].username);
                } else {
                    printf("Invalid username or password.\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    } while (option != 3);

    return 0;
}