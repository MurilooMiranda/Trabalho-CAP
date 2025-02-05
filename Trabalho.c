#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include<string.h>
#include<stdbool.h>
#include<locale.h> //Biblioteca para utilização de acentos e caracteres especiais

//Registro que define os dados do usuario
typedef struct
{
    char nome[40];
    char celular[13];
    char email[40];
    char username[40];
    char senha[10];

} cadastro;

void criptografia (char *x, int chave); //Protótipo da função de criptografia

//Criptografia dos dados do usuário usando Cifra de César

void criptografia (char *x, int chave)
{
    int aux;
    for(int i = 0; x[i] != '\0'; i++)
    {
        if(x[i] >= 33 && x[i] <= 126) //verifica se o caracter esta no alfabeto
        {
            aux = chave/26;

            if((chave > 94) || (chave < (-94)))
                chave = chave - (aux*94);

            if((x[i] + chave) < 33)
                x[i] =  x[i] + chave + 94;
            else if((x[i] + chave) > 126)
                x[i] =  x[i] + chave - 94;
            else
                x[i] = x[i] + chave;
        }
    }
}


bool verifica_p1(int a, char *c)
{
    char l[a];
    FILE *fp;

    do
    {
        fp = fopen("cadastro_novo_usuario.txt", "r");

        while (fgets(l,a, fp)!=NULL && strcmp(c,l)!=0) //Verifica se o que foi inserido pelo usuário é igual ao que está em alguma linha do arquivo
        {

        }

        if (strcmp(c,l)==0)
           return true;

        else
           return false;

    fclose(fp);

    } while (strcmp(c,l)!=0);
}

//Função que verifica o processo 2
void verifica_p2 ()
{
    char l[40]; //Armazena a linha do arquivo
    char loginUser[40];
    char loginSenha[40];

    FILE *fp;
    int cont = 0;
    int contSenha=0;

    fpos_t position; //armazena a posicao atual de leitura arquivo

    //Concaternar o que o usuario digitar para encontrar o USERNAME e a SENHA no arquivo

    char username[40];
    char senha[40] = "SENHA: ";

    fp = fopen("cadastro_novo_usuario.txt", "r"); //Abre o arquivo

    if(fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }

    do
    {
        strcpy(username, "USERNAME: ");

        printf("Insira o username: ");

        fgets(loginUser, 40, stdin);

        criptografia(loginUser,10);

        strcat(username, loginUser);

        /*
            Tenta encontrar o username percorrendo o arquivo todo em busca de
            USERNAME: com oque o usuario digitou e foi armazenado no arquivo
        */

        while (fgets(l,40, fp)!=NULL && strcmp(username,l)!=0)
        {

        }
        //Se nao encontrou o username -> cont++
        if (strcmp(username,l)!=0)
        {
            if(cont==2)
            {
                printf("Sistema travado por 1 hora.\n");
                exit(1);
            }

            printf("Por favor, verifique se username e senha estão corretos e tente novamente.\n");
            cont++;
            fclose(fp);
            fp = fopen("cadastro_novo_usuario.txt", "r"); ; //Volta pro comeco do arquivo para tentar uma nova busca
        }

        else
        {
            printf("Usuario encontrado!\n");
            fgetpos(fp,&position); //Se acha um usuário válido, guarda a posição que ele está
        }

    } while (strcmp(username,l)!=0);

    cont=0; //Zera o contador para que os erros cometidos no usuário não sejam acumulados para a senha

    //Faz o mesmo processo feito no username

    do
    {
        printf("Insira a senha: ");

        strcpy(senha, "SENHA: ");

        fgets(loginSenha, 40, stdin);

        criptografia(loginSenha,10);

        strcat(senha, loginSenha);

        while(fgets(l,40, fp)!=NULL && strcmp(senha,l)!=0 && contSenha<3)
        {
            contSenha++;
        }

        if (strcmp(senha,l)!=0)
        {
            if(cont==2)
            {
                printf("Sistema travado por 1 hora.\n");
                exit(1);
            }

            printf("Por favor, verifique se a senha esta correta e tente novamente.\n");
            cont++;
            contSenha=0;

            fsetpos(fp, &position);
        }

        else
        {
            printf("Senha correta! Logado com sucesso!\n");
            exit(1);
        }

    } while(strcmp(senha,l)!=0);
}

//Função que verifica o processo 3
void verifica_p3(int x)
{

    char l[40]; //Armazena a linha do arquivo
    char loginEmail[40];
    char loginCelular[40];

    FILE *fp;

    //Concaternar o que o usuario digitar para encontrar o USERNAME e a SENHA no arquivo

    char email[40];
    char celular[13] = "CELULAR: ";

    fp = fopen("cadastro_novo_usuario.txt", "r");

    if(fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }


    if(x==1)
    {
        do
        {
            printf("Insira o email: ");
            strcpy(email, "EMAIL: ");

            fgets(loginEmail, 40, stdin);

            criptografia(loginEmail,10);

            strcat(email, loginEmail);

            /*
                Tenta encontrar o email percorrendo o arquivo todo em busca de
                EMAIL: com o que o usuario digitou no cadastro e foi armazenado no arquivo
            */

            while (fgets(l,40, fp)!=NULL && strcmp(email,l)!=0)
            {
            }

            if (strcmp(email,l)!=0)
            {
                printf("Por favor, verifique se username e senha estão corretos e tente novamente.\n");
                fclose(fp);
                fp = fopen("cadastro_novo_usuario.txt", "r"); ; //Volta pro comeco do arquivo para tentar uma nova busca
            }
            else
            {
                printf("Email encontrado! Aqui está o link de recuperação de senha: www.linkderecuperacaodesenha.com\n");
                exit(1);
            }

        } while (strcmp(email,l)!=0);
    }

    else

        //Faz o mesmo processo feito no email

        if (x==2)
        {
            do
            {
                printf("Insira o celular: ");

                strcpy(celular, "CELULAR: ");

                fgets(loginCelular, 40, stdin);

                criptografia(loginCelular,10);

                strcat(celular, loginCelular);

                while(fgets(l,13, fp)!=NULL && strcmp(celular,l)!=0)
                {

                }

                if (strcmp(celular,l)!=0)
                {
                    printf("Por favor, verifique se a senha esta correta e tente novamente.\n");
                    fclose(fp);
                    fp = fopen("cadastro_novo_usuario.txt", "r"); ; //Volta pro comeco do arquivo para tentar uma nova busca

                }
                else
                {
                    printf("Celular encontrado! Aqui está o link de recuperação de senha: www.linkderecuperacaodesenha.com\n");
                    exit(1);
                }

            } while(strcmp(celular,l)!=0);
        }
}

int main()
{
    setlocale(LC_ALL, "Portuguese"); //função da biblioteca locale.h, para imprimir os acentos e caracteres especiais corretamente

    int cad, es, s;
    cadastro c;
    cadastro confirma;
    FILE *fp;
    char cadUser[40];
    char cadEmail[40];
    char cadCelular[13];

    printf(" SEJA BEM-VINDO!\n\n");

    do
    {
        printf("1 - NOVO USUÁRIO\n");
        printf("2 - ENTRAR\n");
        printf("3 - ESQUECI A SENHA\n");
        printf("4 - SAIR\n");
        printf("Insira sua escolha: ");
        scanf("%d", &es);

        //Processo 1: Leitura e armazenamento dos dados cadastrados

        if(es==1)
        {
            fp = fopen("cadastro_novo_usuario.txt", "a+");

            if(fp == NULL)
                fp = fopen("cadastro_novo_usuario.txt", "w");


           if (fp == NULL)
            {
                printf("Erro ao abrir o arquivo.\n");
                return 1;
            }

            do
            {
                printf("Ok, preencha os campos a seguir: \n\n");

                printf("NOME COMPLETO: ");

                getchar();
                fgets (c.nome, 40, stdin);

                criptografia(c.nome,10);

                fprintf(fp,"NOME: %s", c.nome);


                printf("USERNAME: ");

                strcpy(cadUser, "USERNAME: ");

                fgets(c.username, 30, stdin);

                criptografia(c.username,10);

                strcat(cadUser, c.username);

                if(verifica_p1(30,cadUser)== true)
                {
                    printf("O username inserido já está cadastrado, realize um novo cadastro!\n");
                    exit(1);
                }
                else
                    fprintf(fp,"USERNAME: %s", c.username);


                printf("NUMERO DE CELULAR: ");

                strcpy(cadCelular, "CELULAR: ");

                fgets(c.celular, 13, stdin);

                criptografia(c.celular,10);

                strcat(cadCelular, c.celular);

                if(verifica_p1(13,cadCelular)== true)
                {
                    printf("O número de celular inserido já está cadastrado, realize um novo cadastro!");
                    exit(1);
                }
                else
                    fprintf(fp,"CELULAR: %s", c.celular);

                do
                {
                    printf("EMAIL: ");

                    fgets(c.email, 40, stdin);

                    printf("Insira novamente para confirmar: ");
                     fgets(confirma.email, 40, stdin);

                    if(strcmp(c.email,confirma.email)!=0)
                        printf("O email foi inserido errado, insira o email novamente.\n");

                } while(strcmp(c.email,confirma.email)!=0);

                strcpy(cadEmail, "EMAIL: ");

                criptografia(c.email,10);

                strcat(cadEmail, c.email);

                if(verifica_p1(40, cadEmail)== true)
                {
                    printf("O email inserido já está cadastrado, realize um novo cadastro!");
                    exit(1);
                }
                else
                    fprintf(fp,"EMAIL: %s", c.email);

                do
                {
                    printf("SENHA: ");
                    fgets(c.senha, 10, stdin);

                    printf("Insira novamente para confirmar: ");
                    fgets(confirma.senha, 10, stdin);

                    if(strcmp(c.senha,confirma.senha)!=0)
                        printf("A senha foi inserida errada, realize o cadastro novamente.\n");

                } while(strcmp(c.senha,confirma.senha)!=0);

                criptografia(c.senha,10);

                fprintf(fp,"SENHA: %s",c.senha);

                fprintf(fp,"\n");

                printf("Cadastro realizado com sucesso!\nDeseja inserir mais algum usuário? 1- SIM 2-NÃO\n");
                scanf("%d", &cad);

                fclose(fp);
                fp = fopen("cadastro_novo_usuario.txt", "a+");

            } while(cad!=2);

            fclose(fp);
        }
        else
             //Processo 2: Login de username e senha ja cadastrados
            if(es==2)
            {
                getchar();
                verifica_p2();
            }

            else

                //Processo 3: Procedimento caso seja esquecida a senha

                if(es==3)
                {
                    fp = fopen("cadastro_novo_usuario.txt", "r");
                    if (fp == NULL)
                    {
                        printf("Erro ao abrir o arquivo.\n");
                        return 1;
                    }

                    printf("Podemos redefinir a senha por dois meios: \n");
                    printf("1 - EMAIL\n");
                    printf("2 - CELULAR\n");
                    printf("3 - SAIR\n");

                    printf("Escolha por onde quer receber uma nova senha: ");
                    scanf("%d", &s);

                    getchar();
                    verifica_p3(s);
                }

        if(es!=1 && es!=2 && es!=3 && es!=4)
            printf("\nPor favor insira um comando válido.\n\n");

    } while(es!=4);

    printf("Agradecemos pelo acesso, tenha um bom dia!\n");

    return 0;
}