#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char cpf[12];
    char senha[7];
    float reais;
    float btc;
    float eth;
    float xrp;
} Usuario;

void cadastrar();
int login(Usuario *user);

int main() {
    Usuario user;
    int opcao;

    while (1) {
        printf("\n1. Cadastrar\n2. Login\n3. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrar();
        } else if (opcao == 2) {
            if (login(&user)) {
                int respuser;
                while (1) {
                    printf(" /$$$$$$$  /$$$$$$ /$$$$$$$$ /$$$$$$$  /$$   /$$ /$$     /$$ \n");
                    printf("| $$__  $$|_  $$_/|__  $$__/| $$__  $$| $$  | $$|  $$   /$$/\n");
                    printf("| $$  \\ $$  | $$     | $$   | $$  \\ $$| $$  | $$ \\  $$ /$$/ \n");
                    printf("| $$$$$$$   | $$     | $$   | $$$$$$$ | $$  | $$  \\  $$$$/  \n");
                    printf("| $$__  $$  | $$     | $$   | $$__  $$| $$  | $$   \\  $$/   \n");
                    printf("| $$  \\ $$  | $$     | $$   | $$  \\ $$| $$  | $$    | $$    \n");
                    printf("| $$$$$$$/ /$$$$$$   | $$   | $$$$$$$/|  $$$$$$/    | $$    \n");
                    printf("|_______/ |______/   |__/   |_______/  \\______/     |__/    \n");
                    printf("\n");
                    printf("\n1. Depósito\n2. Comprar Criptomoeda\n3. Vender Criptomoeda\n4. Ver Extrato\n5. Sacar\n6. Consultar Saldo\n7. Atualizar cotação\n8. Sair\nEscolha uma opção: ");
                    scanf("%d", &respuser);

                    if (respuser == 1) {
                        // deposito(&user);
                    } else if (respuser == 2) {
                        // comprar(&user);
                    } else if (respuser == 3) {
                        // vender(&user);
                    } else if (respuser == 4) {
                        // extrato(&user);
                    } else if (respuser == 5) {
                        // saque(&user);
                    } else if (respuser == 6){
                        // consultasaldo(&user);
                    } else if (respuser == 7){
                        // cotacao(&user);
                    } else if (respuser == 8) {
                        FILE *file = fopen("usuarios.bin", "r+b");
                        if (file != NULL) {
                            Usuario temp;
                            while (fread(&temp, sizeof(Usuario), 1, file)) {
                                if (strcmp(temp.cpf, user.cpf) == 0) {
                                    fseek(file, -(long)sizeof(Usuario), SEEK_CUR);
                                    fwrite(&user, sizeof(Usuario), 1, file);
                                    break;
                                }
                            }
                            fclose(file);
                        }
                        break;
                    }
                }
            } else {
                printf("CPF ou senha incorretos.\n");
            }
        } else if (opcao == 3) {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}

void cadastrar() {
    FILE *file = fopen("usuarios.bin", "ab");

    Usuario novoUsuario;

    printf("Digite o nome: ");
    scanf(" %[^\n]", novoUsuario.nome);

    printf("Digite o CPF: ");
    scanf("%s", novoUsuario.cpf);

    printf("Digite a senha (6 dígitos): ");
    scanf("%s", novoUsuario.senha);

    novoUsuario.reais = 0;
    novoUsuario.btc = 0;
    novoUsuario.eth = 0;
    novoUsuario.xrp = 0;

    fwrite(&novoUsuario, sizeof(Usuario), 1, file);
    fclose(file);

    printf("Usuário cadastrado com sucesso! Bem vindo %s\n", novoUsuario.nome);
}

int login(Usuario *user) {
    FILE *file = fopen("usuarios.bin", "rb");

    char cpf[12], senha[7];
    printf("Digite o CPF: ");
    scanf("%s", cpf);

    printf("Digite a senha: ");
    scanf("%s", senha);

    Usuario temp;
    while (fread(&temp, sizeof(Usuario), 1, file)) {
        if (strcmp(temp.cpf, cpf) == 0 && strcmp(temp.senha, senha) == 0) {
            *user = temp;
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
