#include <ctype.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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


// pass the not helpers functions to the ATM.C

// principal menu fuctions

int register_user(char userName[], char password[]){
    do{
        clearScreen();
        printf("Igrese su nombre de usuario: ");
        scanf(" %50[^\n]s", userName);
        printf("Ingrese su contrasenia (alpha numerica): ");
        scanf(" %50[^\n]s", password);

        if (!is_valid_password(password)){
            printf("La contrasenia debe de tener letras y numeros, debe de ser alpha numerica.\n");
            getch();
            continue;
        }
        
    }while(!is_valid_password(password));
    getch();
}

int set_account_configuration(char givenUsername[], char givenPassword[]){
    clearScreen();
    printf("Inserte nuevo nombre de usuario: ");
    scanf(" %50[^\n]s", givenUsername);
    printf("Inserte la nueva contrasenia: ");
    scanf(" %50[^\n]s", givenPassword);
    getch();
    return 0;
}

float charge_prepaid_mobile(float balance, char mobileNumber[])
{
    int returnedValue = 0; 
    const char *mobileOperator;

    float amountToCharge = 0.0;
    // this if should be in a helper function
    if (balance < 1)
    {
        clearScreen();
        printf("No puede hacer una recarga, su cuenta no posee el saldo suficiente.\nSaldo actual: C$%.2f\n", balance);
        getch();
        return 0; // refactor this, to return an exit code failure without affecting the user balance.
    }

    do
    {
        clearScreen();
        fflush(stdin); // clean buffer
        printf("Inserte el numero telefonico: ");
        scanf(" %8[^\n]s", mobileNumber);

        if (is_phone_number_valid(mobileNumber))
        {
            mobileOperator = match_mobile_operator(mobileNumber);
            printf("%s\n", mobileOperator);
            getch();
        }

    } while (!is_phone_number_valid(mobileNumber));

    while (amountToCharge <= 0 || amountToCharge > balance)
    {
        fflush(stdin);
        clearScreen();
        printf("Inserte la cantidad a recargar: ");
        returnedValue = scanf(" %f", &amountToCharge);

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
        printf("No puede hacer un retiro, su cuenta no posee el saldo suficiente.\nSaldo actual: C$%.2f\n", balance);
        getch();
        return 0; // refactor this, to return an exit code failure without affecting the user balance.
    }

    while (amountToWithdraw <= 0 || amountToWithdraw > balance)
    {
        clearScreen();
        fflush(stdin);
        printf("Inserte la cantidad a retirar: ");
        returnedValue = scanf(" %f", &amountToWithdraw);

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

float make_a_deposit(float balance)
{
    int returnedValue = 0;
    float deposit = 0.0;

    while (deposit <= 0 || deposit > 10000)
    {
        clearScreen();
        fflush(stdin);
        printf("Inserte la cantidad a depositar: ");
        returnedValue = scanf(" %f", &deposit);

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
    clearScreen();
    printf("Proyecto Cajero UNI.\n");
    printf("Universidad Nacional De ingenieria.\n");
    printf("area de estudio: DATIC\n");

    printf("\t\tKenry Onell Lira Zavala \t\t2024-1898U\n"
           "\t\tCristhian Adonis Sevilla Diaz \t\t2024-1926U\n"
           "\t\tAryan Sidar Narvaez Rivera \t\t2024-1896U\n");


    printf("\n\t\tDocente: Ing.Nelson Barrios.\n");

    getch();

    return 0;
}
