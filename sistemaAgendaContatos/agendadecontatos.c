#include "AgendaFun.h"

int main(){

    agendaDeContatos agenda;

    for (int i = 0; i < size; i++){
        agenda[i] = NULL;
    }

    while(1){

        printf("\nOpções:\n");
        printf("1. Adicionar contato.\n");
        printf("2. Buscar contato.\n");
        printf("3. Remover contato.\n");
        printf("4. Listar contatos.\n");
        printf("5. Exportar contatos.\n");
        printf("6. Sair.\n");
        printf("Escolha uma opção: ");

        int op;
        scanf("%d", &op);

        switch(op){
            case 1:
                {
                    char nome[50];
                    char tel[20];
                    char email[50];

                    printf("Digite o nome: ");
                    scanf("%s", nome);
                    fflush(stdin); //Descarregando o buffer.

                    printf("Digite o telefone: ");
                    scanf("%s", tel);
                    fflush(stdin); 

                    printf("Digite o email: ");
                    scanf("%s", email);
                    fflush(stdin);

                    struct contato *novo = criaContato(nome, tel, email);
                    inserir(agenda, novo);
                    printf("Contato adicionado com sucesso.\n");
                }
                break;
            case 2:
                {
                    char nome[50];
                    printf("Digite o nome do contato a ser buscado: ");
                    scanf("%s", nome);
                    struct contato *encontrado = buscarContato(agenda, nome);
                    if (encontrado != NULL){
                        printf("Contato encontrado:\n");
                        printf("Nome: %s\n", encontrado->nome);
                        printf("Telefone: %s\n", encontrado->tel);
                        printf("Email: %s\n", encontrado->email);
                    }else{
                        printf("Contato não encontrado.\n");
                    }
                }
                break;
            case 3:
                {
                    char nome[20];
                    printf("Digite o nome do contato a ser removido: ");
                    scanf("%s", nome);
                    removerContato(agenda, nome);
                }
                break;
            case 4:
                listarContatos(agenda);
                break;
            case 5:
                {
                    char arquivo[50];
                    printf("Digite o nome do arquivo para exportar os contatos: ");
                    scanf("%s", arquivo);
                    exportarContatos(agenda, arquivo);
                }
                break;
            case 6: //Liberar a memória alocada para os contatos na agenda
                for (int i = 0; i < size; i++){
                    if (agenda[i] != NULL){
                        free(agenda[i]);
                    }
                }
                printf("Programa encerrado.\n");
                return (0);
            default:
                printf("Opção inválida.\n");
        }
    }
    return (0);
}