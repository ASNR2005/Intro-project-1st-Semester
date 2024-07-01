#include <ctype.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen()
{
    system("cls");
}

bool is_tigo(char const phoneNumber[static 8])
{
    int const startOfPrefixes[] = {7600,7710, 7750, 7820, 7870, 8150, 8260, 8320, 8370, 8450, 8550, 8590, 8670, 8750, 8800, 8860, 8950, 8990};
    int const endOfPrefixes[] = {7709,7719, 7769, 7829,7879, 8159, 8269, 8329, 8399, 8489, 8559, 8599, 8689, 8779, 8819, 8899, 8979, 8999};

    // Extract the first four digits as a substring and convert to integer
    char const str[] = {phoneNumber[0], phoneNumber[1], phoneNumber[2], phoneNumber[3]};
    int const firstFourDigits = atoi(str);

    // Check if the first four digits are within any of the ranges
    for (int i = 0; i < 18; i++)
    {
        if (firstFourDigits >= startOfPrefixes[i] && firstFourDigits <= endOfPrefixes[i])
        {
            return true;
        }
    }
    return false;
}

bool is_claro(char const phoneNumber[static 8])
{
    int const startOfPrefixes[] = {5510, 5740, 5780, 5800, 8330, 8350, 8400, 8490, 8500, 8600, 8690, 8700, 8820, 8900};
    int const endOfPrefixes[] = {5599, 5749, 5789, 5809, 8339, 8369, 8449, 8499, 8549, 8669, 8699, 8749, 8959, 8949};

    // Extract the first four digits as a substring and convert to integer
    char const str[] = {phoneNumber[0], phoneNumber[1], phoneNumber[2], phoneNumber[3]};
    int const firstFourDigits = atoi(str);

    // Check if the first four digits are within any of the ranges
    for (int i = 0; i < 14; i++)
    {
        if (firstFourDigits >= startOfPrefixes[i] && firstFourDigits <= endOfPrefixes[i])
        {
            return true;
        }
    }
    return false;
}

bool is_valid_password(char const password[]){
    // Initialize flags for checking presence of letter and number
    bool hasLetter = false;
    bool hasNumber = false;

    // Iterate through each character in the password
    for(int i = 0; i < strlen(password); i++){
        // Check if the character is a letter
        if(isalpha(password[i])){
            hasLetter = true;
        }
        // Check if the character is a digit
        if (isdigit(password[i])){
            hasNumber = true;
        }
        
    }
    // Return true if password has both letter and number, otherwise false
    return hasLetter && hasNumber;
}

// Function to check if the returned value by scanf indicates a valid floating-point input
bool is_a_valid_floating_point_value(int valueReturnedByScanf){
    // If scanf returns 1, the input is a valid floating-point number
    if (valueReturnedByScanf == 1)
        return true;
    else
       return false;
}

bool is_phone_number_valid(char phoneNumber[])
{
    // Check if the length of the phone number is exactly 8
    if (strlen(phoneNumber) < 8 || strlen(phoneNumber) > 8)
    {
        return false;
    }

    // Iterate through each character in the phone number
    for (int i = 0; i < strlen(phoneNumber); i++)
    {
        // Check if the character is a digit
        if (isdigit(phoneNumber[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    // Return true if all characters are digits and length is 8
    return true;
}

bool is_not_equal(char userInputtedStr[], char declaredStr[])
{
    // Check if the lengths of the strings are different
    if (strlen(userInputtedStr) != strlen(declaredStr))
        return true;

    // Iterate through each character in the strings
    for (int i = 0; i < strlen(userInputtedStr); i++)
    {
        // Check if characters at the same position are different
        if (userInputtedStr[i] != declaredStr[i])
            return true;
    }

    // Return false if all characters match and lengths are equal
    return false;
}

int get_masked_password(char userPassword[]){

    int index = 0;
    char userChar;

    // Loop to read characters until Enter key is pressed or max length is reached
    while ((userChar = getch()) != '\r' && index < 30)
    {
        if (index > 0)
        {
            // Handle backspace or special keys
            if (userChar == '\b' || userChar == -32)
            {
                putchar('\b'); // Move cursor back
                putchar(' ');  // Overwrite the character with a space
                putchar('\b'); // Move cursor back again
                index--;
                continue;
            }
            // Handle alphanumeric characters
            else if (isalnum(userChar))
            {
                putchar('*'); // Print asterisk to mask the character
                userPassword[index] = userChar;
                index++;
            }
        }

        else
        {
            // Handle backspace or special keys at the start
            if (userChar == '\b' || userChar == -32) // -32 is the spr key
                continue;

            // Handle alphanumeric characters at the start
            else if (isalnum(userChar)){
                putchar('*');
                userPassword[index] = userChar;
                index++;
            }

        }
    }
    // Null-terminate the password string
    userPassword[index] = '\0';

    return EXIT_SUCCESS;
}

int authenticate_user(char * username, char *password){
    char usernameToVerify[30];
    char passwordToVerify[30];

    int attemptsToVerifyUser = 3; // Number of allowed attempts
    do
    {

        clearScreen();
        // Prompt user to enter their old username
        printf("Ingrese su antiguo usuario: ");
        scanf(" %30[^\n]s", usernameToVerify);
        clearInputBuffer();

        // Prompt user to enter their old password
        printf("Insert su antigua contrasenia: ");
        get_masked_password(passwordToVerify);

        // validate username and password
        if (is_not_equal(passwordToVerify, password) || is_not_equal(usernameToVerify, username))
        {
            clearScreen();
            printf("El usuario o la contrasenia no coinciden.\n"
                   "Intentos restantes %d\n",
                   attemptsToVerifyUser - 1);
            getch();
            attemptsToVerifyUser--;
        }

        else
            return EXIT_SUCCESS; // Authentication successful

    } while (attemptsToVerifyUser != 0);
    return EXIT_FAILURE; // Authentication failed after all attempts
}

// principal menu fuctions
    
int login_user(char userName[], char password[]){

    char givenUsername[30];
    char givenPassword[30];

    int userAttemptsToLog = 3;
    do
    {
        
        clearScreen();
        printf("Ingrese su usuario: ");
        scanf(" %30[^\n]s", givenUsername);
        clearInputBuffer();
        
        printf("Insert su contrasenia: ");
        get_masked_password(givenPassword);
        

        // validate username and password
        if (is_not_equal(givenPassword, password) || is_not_equal(givenUsername, userName))
        {
            clearScreen();
            printf( "Ha puesto el nombre de usuario o la contrasenia erronea.\n"
                    "Intentos restantes %d\n", userAttemptsToLog - 1);
            getch();
            userAttemptsToLog--;
        }

        else
            return EXIT_SUCCESS;

    } while (userAttemptsToLog != 0);
    return EXIT_FAILURE;
}

int register_user(char userName[], char password[]){
    char confirmationPassword[30];
    bool isNotMatch;

    clearScreen();
    printf("Pantalla de Registro.\n");
    printf("Igrese su nombre de usuario: ");
    scanf(" %30[^\n]s", userName);
    clearInputBuffer();

    do{
        isNotMatch = false;
        clearScreen();
        printf("Ingrese su contrasenia (alpha numerica): ");
        get_masked_password(password);
        

        if (!is_valid_password(password)){
            printf("\nLa contrasenia debe de ser alpha numerica.\n");
            getch();
            continue;
        }

        printf("\nIngrese confirmacion de contrasenia: ");
        get_masked_password(confirmationPassword);
        

        if (is_not_equal(password,confirmationPassword))
        {
            printf("\nLas contrasenias no coinciden.\n");
            getch();
            isNotMatch = true;
            continue;
        }

    
    }while(!is_valid_password(password) || isNotMatch);
    return EXIT_SUCCESS; 
}

int set_account_configuration(char username[], char password[]){
    clearScreen();

    printf("Verificacion de usuario\n");
    getch();

    if(authenticate_user(username, password)){
        return EXIT_FAILURE;
    }
    
    clearScreen();
    printf("Inserte nuevo nombre de usuario: ");
    scanf(" %30[^\n]s", username);
    clearInputBuffer();

    do
    {
        clearScreen();
        printf("Inserte la nueva contrasenia: ");
        get_masked_password(password);

        if (is_valid_password(password))
        {
            clearScreen();
            printf("El usuario y la contrasenia han sido cambiados con exito.\n");
            getch();
            return EXIT_SUCCESS;
        }
        else
        {
            clearScreen();
            printf("La contrasenia debe de ser alpha numerica.");
            getch();
            continue;
        }
    } while (!is_valid_password(password));
}

float charge_prepaid_mobile(float balance)
{
    bool isInvalidOperator = false;
    char mobileNumber[8];
    const char *mobileOperator;
    int returnedValue = 0; 

    float amountToCharge = 0.0;
    
    if (balance < 1)
    {
        clearScreen();
        printf( "No puede hacer una recarga, su cuenta no posee el saldo suficiente."
                "\nSaldo actual: C$%.2f\n", balance);
        getch();
        return 0;
    }

    do
    {
        clearScreen();
        printf("Inserte el numero telefonico: ");
        scanf(" %8[^\n]s", mobileNumber);
        clearInputBuffer();

        if (is_phone_number_valid(mobileNumber))
        {
            if (is_tigo(mobileNumber))
            {
                mobileOperator = "Tigo";
            }

            else if (is_claro(mobileNumber))
            {
                mobileOperator = "Claro";
            }

            else
            {
                printf("El numero %s no es un operador movil valido.\n", mobileNumber);
                isInvalidOperator = true;
                getch();
                continue;
            }
            
            printf("Su operador telefonico es: %s\n", mobileOperator);
            getch();
        }

    } while (!is_phone_number_valid(mobileNumber) || isInvalidOperator); 

    while (amountToCharge <= 0 || amountToCharge > balance)
    {
        
        clearScreen();
        printf("Inserte la cantidad a recargar: ");
        returnedValue = scanf(" %f", &amountToCharge);
        clearInputBuffer();

        if(!is_a_valid_floating_point_value(returnedValue)){
            clearScreen();
            printf("Por favor insertar un numero decimal o entero.\n");
            getch();
            continue;
        }

        if (amountToCharge < 1)
        {
            clearScreen();
            printf("La cantidad de recarga debe de ser mayor a 0.\n");
            getch();
            continue;
        }

        if (amountToCharge > balance)
        {
            clearScreen();
            printf("La cantidad de recarga no puede ser mayor a su saldo.\n");
            getch();
            continue;
        }
    }

    clearScreen();
    printf("Su recarga de C$%.2f ha sido realizada con exito.\n", amountToCharge);
    getch();

    return amountToCharge;
}

float withdraw_money(float balance)
{
    int returnedValue = 0; 
    float amountToWithdraw = 0.0;

   
    if (balance < 1)
    {
        clearScreen();
        printf( "No puede hacer un retiro, su cuenta no posee el saldo suficiente."
                "\nSaldo actual: C$%.2f\n", balance);
        getch();
        return 0;
    }

    while (amountToWithdraw <= 0 || amountToWithdraw > balance)
    {
        clearScreen();
        
        printf("Inserte la cantidad a retirar: ");
        returnedValue = scanf(" %f", &amountToWithdraw);
        clearInputBuffer();

        if(!is_a_valid_floating_point_value(returnedValue)){
            clearScreen();
            printf("Por favor insertar un numero decimal o entero.\n");
            getch();
            continue;
        }


        if (amountToWithdraw < 1)
        {
            clearScreen();
            printf("La cantidad del retiro debe de ser mayor a 0.\n");
            getch();
            continue;
        }

        if (amountToWithdraw > balance)
        {
            clearScreen();
            printf("La cantidad del retiro no puede ser mayor a su saldo.\n");
            getch();
            continue;
        }
    }
    
    clearScreen();
    printf("Su retriro de C$%.2f se ha realizado de manera exitosa.\n", amountToWithdraw);
    getch();

    return amountToWithdraw;
}

float make_a_deposit()
{
    int returnedValue = 0;
    float deposit = 0.0;

    while (deposit <= 0 || deposit > 10000)
    {
        clearScreen();
        
        printf("Inserte la cantidad a depositar: ");
        returnedValue = scanf(" %f", &deposit);
        clearInputBuffer();

        if (!is_a_valid_floating_point_value(returnedValue))
        {
            clearScreen();
            printf("Por favor insertar un numero decimal o entero.\n");
            getch();
            continue;
        }

        if (deposit < 1)
        {
            clearScreen();
            printf("El deposito debe de ser mayor a 0.\n");
            getch();
            clearScreen();
            continue;
        }

        if (deposit > 10000)
        {
            clearScreen();
            printf("El deposito debe de ser menor a C$10,000\n");
            getch();
            clearScreen();
            continue;
        }
    }

    clearScreen();
    printf("Su deposito  de C$%.2f a sido realizado correctamente.\n", deposit);
    getch();

    return deposit;
}

int show_balance(float balance)
{
    clearScreen();
    printf("El saldo actual de su cuenta es de: C$%.2f\n", balance);
    getch();
    return 0; // exit code, success
}

int introduce_team()
{
    COORD axis;
    axis.X = 60;
    axis.Y = 15;
    clearScreen();

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Proyecto Cajero UNI.");

    axis.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Universidad Nacional De Ingenieria.");

    axis.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Area de estudio: DATIC.");

    axis.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Kenry Onell Lira Zavala \t\t2024-1898U");

    axis.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Aryan Sidar Narvaez Rivera \t\t2024-1896U");

    axis.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Docente: Ing.Nelson Barrios.\n");

    getch();

    return 0;
}
