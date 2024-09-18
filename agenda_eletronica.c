#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Definindo tamanhos máximos para as variáveis
#define MAX_NOME 50
#define MAX_TEL 15
#define MAX_EMAIL 50
#define MAX_RUA 50
#define MAX_BAIRRO 50
#define MAX_CIDADE 50
#define MAX_ESTADO 3
#define MAX_ESTADOCIVIL 10
#define MAX_COMPLEMENTO 30

// Definindo a estrutura Contato 
typedef struct {
    char nome[MAX_NOME];
    char telefone_fixo[MAX_TEL];
    char telefone_celular1[MAX_TEL];
    char telefone_celular2[MAX_TEL];
    char email[MAX_EMAIL];
    char rua[MAX_RUA];
    int numero;
    char complemento[MAX_COMPLEMENTO];
    char bairro[MAX_BAIRRO];
    char cidade[MAX_CIDADE];
    char estado[MAX_ESTADO];
    char estado_civil[10];
} Contato;

void limBuffer() {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

// Função para cadastrar um novo contato
void cadastrarContato(FILE *arquivo, int *total_contatos) {
    Contato contato;

    // Coleta de dados do usuário
    printf("Digite o nome completo: ");
    fgets(contato.nome, MAX_NOME, stdin);
    contato.nome[strcspn(contato.nome, "\n")] = '\0'; // Remove o newline
    

    printf("Digite o telefone fixo: ");
    fgets(contato.telefone_fixo, MAX_TEL, stdin);
    contato.telefone_fixo[strcspn(contato.telefone_fixo, "\n")] = '\0';

    
    printf("Digite o telefone celular 1: ");
    fgets(contato.telefone_celular1, MAX_TEL, stdin);
    contato.telefone_celular1[strcspn(contato.telefone_celular1, "\n")] = '\0';
    
    
    printf("Digite o telefone celular 2: ");
    fgets(contato.telefone_celular2, MAX_TEL, stdin);
    contato.telefone_celular2[strcspn(contato.telefone_celular2, "\n")] = '\0';

    
    printf("Digite o e-mail: ");
    fgets(contato.email, MAX_EMAIL, stdin);
    contato.email[strcspn(contato.email, "\n")] = '\0';

    
    printf("Digite a rua: ");
    fgets(contato.rua, MAX_RUA, stdin);
    contato.rua[strcspn(contato.rua, "\n")] = '\0';
    
    
    printf("Digite o número da residência: ");
    scanf("%d", &contato.numero);
    getchar(); // Limpar o newline após a leitura do número
    

    printf("Digite o complemento (se houver): ");
    fgets(contato.complemento, MAX_COMPLEMENTO, stdin);
    contato.complemento[strcspn(contato.complemento, "\n")] = '\0';

    
    printf("Digite o bairro: ");
    fgets(contato.bairro, MAX_BAIRRO, stdin);
    contato.bairro[strcspn(contato.bairro, "\n")] = '\0';
    

    printf("Digite a cidade: ");
    fgets(contato.cidade, MAX_CIDADE, stdin);
    contato.cidade[strcspn(contato.cidade, "\n")] = '\0';
    

    printf("Digite o estado (sigla de 2 caracteres): ");
    fgets(contato.estado, MAX_ESTADO, stdin);
    contato.estado[strcspn(contato.estado, "\n")] = '\0';

    limBuffer();
     printf("\n");
    printf("Estado civil:\n");
    printf("1. solteiro\n");
    printf("2. casado\n");
    printf("3. separado\n");
    printf("4. viúvo\n");
    fgets(contato.estado_civil, 10, stdin);
    contato.estado_civil[strcspn(contato.estado_civil, "\n")] = '\0';
    
    // Grava o contato no arquivo binário
    fseek(arquivo, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    fwrite(&contato, sizeof(Contato), 1, arquivo);
    (*total_contatos)++;


    printf("\nDados cadrastrados com sucesso!!!\n");
}

// Função para exibir todos os contatos armazenados
void exibirContatos(FILE *arquivo, int total_contatos) {
    Contato contato;
    int i;

    fseek(arquivo, 0, SEEK_SET); // Move o ponteiro para o início do arquivo
    
    for (i = 0; i < total_contatos; i++) {
        fread(&contato, sizeof(Contato), 1, arquivo);
        printf("\n===== Contato %d=====\n", i + 1);
        printf("Nome: %s\n", contato.nome);
        printf("Telefone fixo: %s\n", contato.telefone_fixo);
        printf("Telefone celular 1: %s\n", contato.telefone_celular1);
        printf("Telefone celular 2: %s\n", contato.telefone_celular2);
        printf("E-mail: %s\n", contato.email);
        printf("Endereço: %s, %d, %s, %s, %s, %s\n",
            contato.rua, contato.numero, contato.complemento, contato.bairro, contato.cidade, contato.estado);
        printf("Estado Civil: %s\n", contato.estado_civil);
    }
}

// Função principal
int main() {
    FILE *arquivo;
    int opcao, total_contatos = 0;
    const char nome_arquivo[] = "dados.dat";
	
    // Abre o arquivo para leitura e escrita 
    arquivo = fopen(nome_arquivo, "ab+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    // Conta o número de contatos existentes no arquivo
    fseek(arquivo, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    long tamanho_arquivo = ftell(arquivo); // Obtém a posição atual do ponteiro
    if (tamanho_arquivo > 0) {
        total_contatos = tamanho_arquivo / sizeof(Contato);
    }
    
    // Menu de opções 
    	setlocale (LC_ALL, "Portuguese");
    printf("  ___                       _         _____ _      _                   _           \n");
    printf(" / _ \\                     | |       |  ___| |    | |                 (_)          \n");
    printf("/ /_\\ \\ __ _  ___ _ __   __| | __ _  | |__ | | ___| |_ _ __ ___  _ __  _  ___ __ _ \n");
    printf("|  _  |/ _` |/ _ \\ '_ \\ / _` |/ _` | |  __|| |/ _ \\ __| '__/ _ \\| '_ \\| |/ __/ _` |\n");
    printf("| | | | (_| |  __/ | | | (_| | (_| | | |___| |  __/ |_| | | (_) | | | | | (_| (_| |\n");
    printf("\\_| |_/\\__, |\\___|_| |_|\\__,_|\\__,_| \\____/|_|\\___|\\__|_|  \\___/|_| |_|_|\\___\\__,_|\n");
    printf("        __/ |                                                                      \n");
    printf("       |___/                                                                       \n");
    system("color 0B");
        printf("\n******************************************************************************\n");
    do {
    
        printf("\n1.Cadastrar novo contato\n");
        printf("2. Exibir contatos cadastrados\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o newline após a leitura da opção

        switch (opcao) {
            case 1:
                cadastrarContato(arquivo, &total_contatos);
                break;
            case 2:
                exibirContatos(arquivo, total_contatos);
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n"); 
        }
    } while (opcao != 3);

    // Fecha o arquivo ao final da execução do programa
    fclose(arquivo);

    return 0;
}
