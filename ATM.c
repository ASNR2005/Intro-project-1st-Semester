#include "helpers.h"
#include <stdio.h>


float get_next_interface(float balance, char userName[], char password[]){

    int givenNumberByUser = 0;
    char mobileNumber[8];
    do{

        // reminder: move the 2nd option to 6th into its own ATM menu
        
        clearScreen();
        printf("1.Presentacion.\n"
                "2.Ver saldo.\n"
                "3.ATM menu."
                "3.Depositar.\n"
                "4.Retirar.\n"
                "5.Recargar.\n"
                "6.Configurar.\n"
                "7.Salir.\n"
                "Inserte opcion deseada: ");

        scanf("%d", &givenNumberByUser); 

        switch (givenNumberByUser)
        {
            case 1:
                introduce_team();
                return balance; 

            case 2:
                show_balance(balance);
                return balance;

            case 3:
                balance += make_a_deposit();
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
                exit(0);

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
    // registration variables
    char userName[30];  
    char userPassWord [30]; 
    char confirmationPassword[30];
    
    char givenUserName[30], givenPassword[30]; // log in variables

    float balance = 0.0;
    int userAttemptsToLog = 3;


    register_user(userName, userPassWord, confirmationPassword); 

    // reminder: refactor the log in functionality into its own separate function 
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