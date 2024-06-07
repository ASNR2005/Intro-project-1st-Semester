#include <ctype.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// make a helper .h file with all the helpers functions to make this code cleaner.

void clearScreen(){
    system("cls");
}

bool is_phone_number_valid(char phoneNumber[]){

    if(strlen(phoneNumber) < 8 || strlen(phoneNumber) > 8)
        return false;

    for (int i = 0; i < strlen(phoneNumber); i++)
    {
        if(isdigit(phoneNumber[i]))
            continue;
        else
            return false;
    }
    

    return true;
}

bool is_not_equal(char userInputtedStr[], char declaredStr[]){

    if( strlen(userInputtedStr) != strlen(declaredStr))
        return true;

    for(int i = 0; i < strlen(userInputtedStr); i++){
        if(userInputtedStr[i] != declaredStr[i])
            return true; 
    }

    return false;
}

// principal menu fuctions 

int show_balance(float balance){
    clearScreen();
    printf("El saldo actual de su cuenta es de: C$%.2f\n", balance);
    getch();
    return 0; // exit code, success
} 

float charge_prepaid_mobile(float balance, char mobileNumber[]){

    float amountToCharge = 0.0;
    // this if should be in a helper function
    if (balance < 1){
        clearScreen();
        printf("No puede hacer una recarga, su cuenta no posee el saldo suficiente.\nSaldo actual: C$%.2f\n", balance);
        getch();
        clearScreen();
        return 0; // refactor this, to return an exit code failure without affecting the user balance.
    }

    do
    {
        fflush(stdin); // clean buffer
        printf("Inserte el numero telefonico: ");
        scanf(" %8[^\n]s", mobileNumber);

    } while (!is_phone_number_valid(mobileNumber));
    
    while (amountToCharge <= 0 || amountToCharge > balance)
    {    

        printf("Inserte la cantidad a recargar: ");
        scanf(" %f", &amountToCharge);

        if (amountToCharge < 1)
        {
            clearScreen();
            printf("La cantidad de recarga debe de ser mayor a 0.\n");
            getch();
            clearScreen();
            continue;
        }

        if (amountToCharge > balance)
        {
            clearScreen();
            printf("La cantidad de recarga no puede ser mayor a su saldo.\n");
            getch();
            clearScreen();
            continue;
        }
        
    }

    return amountToCharge;
}

float withdraw_money(float balance){

    float amountToWithdraw = 0.0;

    // ask if this needs to be inside a loop.
    if(balance < 1){
        clearScreen();
        printf("No puede hacer un retiro, su cuenta no posee el saldo suficiente.\nSaldo actual: C$%.2f\n", balance);
        getch();
        clearScreen();
        return 0; // refactor this, to return an exit code failure without affecting the user balance.
    }

    while (amountToWithdraw <= 0 || amountToWithdraw > balance)
    {
        printf("Inserte la cantidad a retirar: ");
        scanf(" %f", &amountToWithdraw); 

        if(amountToWithdraw < 1){
            clearScreen();
            printf("La cantidad del retiro debe de ser mayor a 0.\n");
            getch();
            clearScreen();
            continue;
        }

        if (amountToWithdraw > balance){
            clearScreen();
            printf("La cantidad del retiro no puede ser mayor a su saldo.\n");
            getch();
            clearScreen();
            continue;
        }

    }
    
    return amountToWithdraw;
}

float make_a_deposit(float balance){
    float deposit = 0.0;

    while (deposit <= 0 || deposit > 10000)
    {
        clearScreen();
        printf("Inserte la cantidad a depositar: ");
        scanf(" %f", &deposit);

        if( deposit < 1){
            clearScreen();
            printf("El deposito debe de ser mayor a 0.\n");
            getch();
            clearScreen();
            continue;
        }
        
        if (deposit > 10000){
            clearScreen();
            printf("El deposito debe de ser menor a C$10,000\n");
            getch();
            clearScreen();
            continue;
        }
    }
    

    return deposit;
}

int introduce_team(){
    clearScreen();
    printf("Proyecto de introduccion a ing. en computacion.\n");
    printf("area de estudio: DATIC\n");

    printf("\t\tKenry onell waslala\n"
           "\t\tchristopher ....\n"
           "\t\tAryan Sidar Narvaez Rivera\n");

    getch();

    return 0; 
}

int get_next_interface(){

    int givenNumberByUser;
    char mobileNumber[8];
    float balance = 0.0; // think in a way to make this variable "remember" its value, when logged in again
                        /* the last means that when I deposit money, then I get to log in again I need to keep the balance with the last deposit made.*/
    do{
        printf("1.Presentacion.\n"
                "2.Ver saldo.\n"
                "3.Depositar.\n"
                "4.Retirar.\n"
                "5.Recargar.\n"
                "6.Configurar.\n"
                "7.Salir.\n"
                "Inserte opcion deseada: ");

        scanf(" %d", &givenNumberByUser); // add a validation in case the user inputs a string 

        switch (givenNumberByUser)
        {
            case 1:
                introduce_team();
                clearScreen();
                return 0;

            case 2:
                show_balance(balance);
                break;

            case 3:
                balance += make_a_deposit(balance);
                break;

            case 4:
                balance -= withdraw_money(balance);
                break;

            case 5:
                balance -= charge_prepaid_mobile(balance, mobileNumber);
                break;

            case 6:
                //set_account_configuration();
                break;

            case 7:
                printf("HA SALIDO EXITOSAMENTE DEL CAJERO.\n");
                clearScreen();
                break;

            default:
                clearScreen();
                printf("Opcion seleccionada, no valida.\n");
                getch();
                clearScreen();
                return 1;
        }

    }while(givenNumberByUser != 7);

    return 0; // success returning value
}

int main(){

    // remainder: make this in order for the user to register, or log in without hard coding the username not the password
    char givenUserName[50], givenPassword[50];
    char userName[] = "aryan";
    char userPassWord [] = "user@34"; //alphanumeric password
    int userAttemptsToLog = 3;

    do
    {
        fflush(stdin); // clean buffer for input 
        printf("Ingrese su usruario: ");
        scanf( " %50[^\n]s", givenUserName);
        printf("Insert su contraseña: ");
        scanf( " %50[^\n]s", givenPassword);

        
        // validate username and password
        if ( is_not_equal(givenPassword, userPassWord) || is_not_equal(givenUserName, userName) )
            printf("Ha puesto el nombre de usuario o la contrasenia erronea.\nIntendos restantes %d\n", userAttemptsToLog - 1);
        
        else 
            get_next_interface();

        userAttemptsToLog--;

    } while (userAttemptsToLog != 0);
    
    getch();

    return 0;
}