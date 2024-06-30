#include "helpers.h"
#include <stdio.h>

int get_first_menu(float *, char *, char *);

void get_ATM_menu(float *, char *, char *);

int main(){

    bool hasSucceedToLogIn = true;
    char userName[30];
    char userPassWord [30];

    float balance = 0.0;
    int const rePromptLoginCode = 10;



    if(!register_user(userName, userPassWord)){
        int valueReturned;
        do
        {
            if (!login_user(userName,userPassWord))
            {
                valueReturned = get_first_menu(&balance, userName, userPassWord);
            }
            else
            {
                clearScreen();
                hasSucceedToLogIn = false;
                printf("No ha sido capaz de iniciar sesion.\n");
                getch();
                exit(0); // program succeeded, but user was not capable of logging in.
            }
        } while (valueReturned == rePromptLoginCode || valueReturned == EXIT_FAILURE);
        
    }
    getch();
    return 0;
}


int get_first_menu(float *balance, char * username, char * userPassword){
    int givenNumberByUser = 0;
    int const backToLoginCode = 10;

    do
    {
        clearScreen();
        printf("1.Presentacion.\n"
               "2.ATM menu.\n"
               "3.Salir.\n"
               "Inserte opcion deseada: ");

        scanf("%d", &givenNumberByUser);
        clearInputBuffer();

        switch (givenNumberByUser)
        {
            case 1:
                introduce_team();
                break;

            case 2:
                get_ATM_menu(balance, username, userPassword);
                return backToLoginCode;

            case 3:
                clearScreen();
                printf("HA SALIDO EXITOSAMENTE DEL CAJERO.\n");
                return EXIT_SUCCESS;

            default:
                clearScreen();
                printf("Opcion seleccionada, no valida.\n");
                getch();
                clearScreen();
                return EXIT_FAILURE;
        }

    } while (givenNumberByUser != 3);

    return EXIT_SUCCESS;
}

void get_ATM_menu(float *balance, char *username, char *userPassword)
{
    char moveOpc = ' ';
    bool has_other_movement = false;
    float availableMoney = *balance;
    int result = 0;

    do
    {
        fflush(stdin);
        clearScreen();
        printf("1.Ver saldo.\n"
               "2.Depositar.\n"
               "3.Retirar.\n"
               "4.Recargar.\n"
               "5.Configurar.\n"
               "Inserte su opcion: ");

        scanf(" %d", &result);
        clearInputBuffer();

        switch (result)
        {
        case 1:
            show_balance(availableMoney);
            break;

        case 2:
            availableMoney += make_a_deposit();
            break;

        case 3:
            availableMoney -= withdraw_money(availableMoney);
            break;

        case 4:
            availableMoney -= charge_prepaid_mobile(availableMoney);
            break;

        case 5:
            if(set_account_configuration(username, userPassword) == EXIT_FAILURE){
                clearScreen();
                printf("Error al intentar verificar el usuario.\n");
                getch();
                exit(0);
            }
            break;

        default:
            clearScreen();
            printf("Opcion seleccionada, no valida.\n");
            has_other_movement = true;
            getch();
            clearScreen();
            continue;
        }

        do
        {
            clearScreen();
            printf( "Desea hacer otro movimiento?\n"
                    "S(si) / N(no): ");
            scanf(" %c", &moveOpc);
            clearInputBuffer();

            if (tolower(moveOpc) == 's')
            {
                has_other_movement = true;
            }
            else if (tolower(moveOpc) == 'n')
            {
                has_other_movement = false;
            }
            else
            {
                printf("Entrada no valida.\n");
                getch();
            }
        } while (tolower(moveOpc) != 'n' && tolower(moveOpc) != 's');
        
    } while (has_other_movement == true);

    *balance = availableMoney;
}
