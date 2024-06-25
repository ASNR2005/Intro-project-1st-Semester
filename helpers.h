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

const char *match_mobile_operator(char phoneNumber[])
{
    char *mobilePhone;
    for (int i = 0; i < strlen(phoneNumber); i++)
    {
        if (phoneNumber[i] == '7' && phoneNumber[i + 1] == '6')
        {
            mobilePhone = "tigo";
            return mobilePhone;
        }
    }
    mobilePhone = "claro";

    return mobilePhone;
}

bool is_tigo(){
    return true;
}

bool is_claro(){
    return true;
}

bool is_valid_password(char passwordInRegistration[]){
    bool hasLetter = false;
    bool hasNumber = false;

    for(int i = 0; i < strlen(passwordInRegistration); i++){
        if(isalpha(passwordInRegistration[i])){
            hasLetter = true;
        }

        if (isdigit(passwordInRegistration[i])){
            hasNumber = true;
        }
        
    }

    return hasLetter && hasNumber;
}

bool is_a_valid_floating_point_value(int valueReturnedByScanf){
    if (valueReturnedByScanf == 1)
        return true;
    else
       return false;
}

bool is_phone_number_valid(char phoneNumber[])
{

    if (strlen(phoneNumber) < 8 || strlen(phoneNumber) > 8)
        return false;

    for (int i = 0; i < strlen(phoneNumber); i++)
    {
        if (isdigit(phoneNumber[i]))
            continue;
        else
            return false;
    }

    return true;
}

bool is_not_equal(char userInputtedStr[], char declaredStr[])
{
    if (strlen(userInputtedStr) != strlen(declaredStr))
        return true;

    for (int i = 0; i < strlen(userInputtedStr); i++)
    {
        if (userInputtedStr[i] != declaredStr[i])
            return true;
    }
    return false;
}

int get_masked_password(char userPassword[]){

    int index = 0;
    char userChar;

    while ((userChar = getch()) != '\r' && index < 30)
    {
        if (index > 0)
        {
            if (userChar == '\b' || userChar == -32)
            {
                putchar('\b'); // Move cursor back
                putchar(' ');  // Overwrite the character with a space
                putchar('\b'); // Move cursor back again
                index--;
                continue;
            }
            else if (isalnum(userChar))
            {
                putchar('*');
                userPassword[index] = userChar;
                index++;
            }
        }

        else
        {
            if (userChar == '\b' || userChar == -32) // -32 is the spr key
                continue;
            else if (isalnum(userChar)){
                putchar('*');
                userPassword[index] = userChar;
                index++;
            }

        }
    }
    userPassword[index] = '\0';

    return EXIT_SUCCESS;
}

// pass the not helpers functions to the ATM.C

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
    printf("Inserte nuevo nombre de usuario: ");
    scanf(" %30[^\n]s", username);
    clearInputBuffer();

    printf("Inserte la nueva contrasenia: ");
    get_masked_password(password);
    return EXIT_SUCCESS;
}

float charge_prepaid_mobile(float balance)
{
    char mobileNumber[8];
    const char *mobileOperator;
    int returnedValue = 0; 

    float amountToCharge = 0.0;
    // this if should be in a helper function
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
            mobileOperator = match_mobile_operator(mobileNumber);
            printf("%s\n", mobileOperator);
            getch();
        }

    } while (!is_phone_number_valid(mobileNumber));

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

    // ask if this needs to be inside a loop.
    if (balance < 1)
    {
        clearScreen();
        printf( "No puede hacer un retiro, su cuenta no posee el saldo suficiente."
                "\nSaldo actual: C$%.2f\n", balance);
        getch();
        return 0; // refactor this, to return an exit code failure without affecting the user balance.
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
    printf("Cristhian Adonis Sevilla Diaz \t2024-1926U");

    axis.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Aryan Sidar Narvaez Rivera \t\t2024-1896U");

    axis.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), axis);
    printf("Docente: Ing.Nelson Barrios.\n");

    getch();

    return 0;
}
