#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>

bool is_not_equal(char userInputtedStr[], char declaredStr[]){

    if( strlen(userInputtedStr) != strlen(declaredStr))
        return true;

    for(int i = 0; i < strlen(userInputtedStr); i++){
        if(userInputtedStr[i] != declaredStr[i])
            return true; 
    }

    return false;
}

int main(){

    char givenUserName[50], givenPassword[50];
    char userName[] = "aryan";
    char userPassWord [] = "user@34"; //alphanumeric password
    int userAttemptsToLog = 3;

    do
    {
        printf("Ingrese su usruario: ");
        scanf( " %50[^\n]s", givenUserName);
        printf("Insert su contraseña: ");
        scanf( " %50[^\n]s", givenPassword);

        
        // validate username and password
        if ( is_not_equal(givenPassword, userPassWord) || is_not_equal(givenUserName, userName) )
            printf("Ha puesto el nombre de usuario o la contrasenia erronea.\nIntendos restantes %d\n", userAttemptsToLog - 1);
        
        else 
            break;

        userAttemptsToLog--;

    } while (userAttemptsToLog != 0);
    

    return 0;
}