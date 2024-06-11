#include "helpers.h"
#include <stdio.h>


float get_next_interface(float balance, char userName[], char password[]){

    int givenNumberByUser = 0;
    char mobileNumber[8];
    do{
        clearScreen();
        printf("1.Presentacion.\n"
                "2.Ver saldo.\n"
                "3.Depositar.\n"
                "4.Retirar.\n"
                "5.Recargar.\n"
                "6.Configurar.\n"
                "7.Salir.\n"
                "Inserte opcion deseada: ");

        scanf(" %d", &givenNumberByUser); 

        switch (givenNumberByUser)
        {
            case 1:
                introduce_team();
                return balance;

            case 2:
                show_balance(balance);
                return balance;

            case 3:
                balance += make_a_deposit(balance);
                return balance; 

            case 4:
                balance -= withdraw_money(balance);
                return balance;

            case 5:
                balance -= charge_prepaid_mobile(balance, mobileNumber);
                return balance;

            case 6:
                set_account_configuration(userName, password);
                return balance;

            case 7:
                clearScreen();
                printf("HA SALIDO EXITOSAMENTE DEL CAJERO.\n");
                getch();
                return balance;

            default:
                clearScreen();
                printf("Opcion seleccionada, no valida.\n");
                getch();
                clearScreen();
                break;
        }

    }while(givenNumberByUser != 7);
}

int main(){

    // remainder: make this in order for the user to register, or log in without hard coding the username not the password
    char givenUserName[50], givenPassword[50];

    char userName[50];
    char userPassWord [50]; //alphanumeric password
    
    float balance = 0.0;
    int userAttemptsToLog = 3;


    register_user(userName, userPassWord);

    do
    {
        fflush(stdin); // clean buffer for input 
        clearScreen();
        printf("Ingrese su usruario: ");
        scanf( " %50[^\n]s", givenUserName);
        printf("Insert su contraseña: ");
        scanf( " %50[^\n]s", givenPassword);

        
        // validate username and password
        if ( is_not_equal(givenPassword, userPassWord) || is_not_equal(givenUserName, userName) ){
            clearScreen();
            printf("Ha puesto el nombre de usuario o la contrasenia erronea.\nIntendos restantes %d\n", userAttemptsToLog - 1);
            getch();
            userAttemptsToLog--; 
        }
        
        else 
            balance = get_next_interface(balance, userName, userPassWord);


    } while (userAttemptsToLog != 0);
    
    getch();

    return 0;
}