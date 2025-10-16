#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 32

struct contato{
    char nome[50];    
    char tel[20];     
    char email[50];  
};

//Função para criar um novo contato com os dados fornecidos
struct contato *criaContato(char *nome, char *tel, char *email){
    struct contato *novo = (struct contato *)malloc(sizeof(struct contato));
    strncpy(novo->nome, nome, sizeof(novo->nome)); //Faz uma cópia de uma string contida na variável nome para a estrutura novo, no campo nome, usando a função strncpy. 
    strncpy(novo->tel, tel, sizeof(novo->tel)); //A função strncpy é usada para copiar a string nome para o campo nome da estrutura novo. O terceiro argumento, sizeof(novo->tel), especifica o tamanho máximo a ser copiado para evitar estouro de buffer.
    strncpy(novo->email, email, sizeof(novo->email));
    return novo; //A função retorna o ponteiro novo, que aponta para a nova estrutura de contato criada. Isso permite que o novo contato seja acessado e gerenciado em outras partes do programa.
}

//Função que calcula o índice na tabela hash usando divisão
int funHashDiv(int key){
    return key % size; //Dentro da função, o operador % é usado para calcular o resto da divisão de key por size. Isso significa que a função retorna o valor resultante da operação de módulo.
}

//Definição do tipo 'agendaDeContatos' que é uma tabela hash de contatos
typedef struct contato *agendaDeContatos[size];

//Função para inserir um contato na tabela hash
int inserir(agendaDeContatos Hash, struct contato *c){
    int key = funHashDiv(key); //Calcula o índice na tabela hash com base na chave calculada anteriormente usando a função funHashDiv. Essa função aplica a operação de módulo (%) para garantir que o índice esteja dentro dos limites da tabela hash.

    int key_inicio = key; //Verifica se a função está entrando em um loop infinito ao procurar um espaço vazio na tabela.

    while(1){ //Inicia um loop infinito, que será interrompido quando o contato for inserido com sucesso na tabela hash.
        if(Hash[key] == NULL){
            Hash[key] = c;  //Insere o contato no índice se estiver vazio
            break;
        }
        key++; //Se o índice key não estiver vazio, incrementa key para verificar a próxima posição da tabela hash.

        if(key_inicio == key){ //Verificação para evitar loops infinitos
            printf("Tabela cheia. Não foi possível inserir o contato.\n");
            return (0);
        }

        if(key >= size){ //Verificação para evitar que a tabela ultrapasse o tamanho máximo
            key = key % size;
        }
    }
    return (1);
}

//Função para buscar um contato na tabela hash pelo nome
struct contato *buscarContato(agendaDeContatos Hash, char *nome){
    int key = funHashDiv(key);  //Calcula o índice usando a função de hash
    int key_inicio = key; // verificar se a função está entrando em um loop infinito ao procurar o contato na tabela.

    while(1){
        if(Hash[key] != NULL && strcmp(Hash[key]->nome, nome) == 0){ // Verifica se a posição key da tabela hash não está vazia (Hash[key] != NULL) e se o nome do contato naquela posição é igual ao nome procurado (strcmp(Hash[key]->nome, nome) == 0).
            printf("-------------------\n");
            return Hash[key]; //Se um contato com o nome procurado for encontrado na posição key, a função retorna um ponteiro para esse contato.
            printf("-------------------\n");
        }
        key++;

        if(key_inicio == key){ //Feito para evitar loops infinitos quando o contato não está na tabela.
            break;
        }

        if(key >= size){
            key = key % size;
        }
    }

    return NULL; //Retorna NULL se o contato não for encontrado
}

//Função para remover um contato da tabela hash pelo nome
void removerContato(agendaDeContatos Hash, char *nome){
   int key = funHashDiv(key); //Calcula o índice usando a função de hash

    int key_inicio = key;

    while(1){
        if(Hash[key] != NULL && strcmp(Hash[key]->nome, nome) == 0){ //Verifica se a posição key da tabela hash não está vazia (Hash[key] != NULL) e se o nome do contato naquela posição é igual ao nome procurado (strcmp(Hash[key]->nome, nome) == 0).
            free(Hash[key]);  //Se um contato com o nome procurado for encontrado na posição key, libera a memória alocada para esse contato usando a função free. Isso remove o contato da memória.
            Hash[key] = NULL; //Indica que essa posição está disponível para ser usada novamente.
            printf("Contato '%s' removido com sucesso.\n", nome);
            return;  //Sai da função quando o contato é removido
        }
        key++;

        if(key_inicio == key){ //Feito para evitar loops infinitos quando o contato não está na tabela.
            break;
        }

        if(key >= size){ //Verificação para evitar que a tabela ultrapasse o tamanho máximo
            key = key % size; 
        }
    }
    printf("Contato '%s' não encontrado.\n", nome);
}

//Função para listar todos os contatos na tabela hash
void listarContatos(agendaDeContatos Hash){
    int i;
    printf("\nLista de Contatos:\n");
    for (i = 0; i < size; i++){
        if (Hash[i] != NULL) {
            printf("-------------------\n");
            printf("Nome: %s\n", Hash[i]->nome);
            printf("Telefone: %s\n", Hash[i]->tel);
            printf("Email: %s\n", Hash[i]->email);
            printf("-------------------\n");
        }
    }
}

//Função para exportar os contatos para um arquivo
void exportarContatos(agendaDeContatos Hash, char *arquivo){
    FILE *fp;
    fp = fopen(arquivo, "w"); //A função começa abrindo um arquivo de texto chamado arquivo no modo de escrita ("w"). Ela tenta criar o arquivo ou substituir o conteúdo de um arquivo existente com o mesmo nome. O ponteiro fp é usado para manipular o arquivo.
    if (fp == NULL){ //Verifica se a abertura do arquivo foi bem-sucedida. Se não for possível abrir o arquivo, a função exibe uma mensagem de erro informando que ocorreu um erro na criação do arquivo de exportação e, em seguida, retorna, encerrando a função.
        printf("Erro ao criar o arquivo de exportação.\n"); //Escreve no arquivo de destino a linha inicial indicando que a seguir serão listados os contatos.
        return;
    }

    fprintf(fp, "Lista de Contatos:\n");
    int i;
    for (i = 0; i < size; i++){ //Inicia um loop que percorre todas as posições da tabela hash, de 0 até size - 1.
        if (Hash[i] != NULL){ //Verifica se há um contato na posição atual da tabela hash (Hash[i] não é nulo). Se houver um contato na posição, o código dentro deste bloco será executado.
            fprintf(fp, "-------------------\n"); 
            fprintf(fp, "Nome: %s\n", Hash[i]->nome); 
            fprintf(fp, "Telefone: %s\n", Hash[i]->tel); 
            fprintf(fp, "Email: %s\n", Hash[i]->email);
            fprintf(fp, "-------------------\n"); 
        }
    }
    //O loop continua, percorrendo todas as posições da tabela hash e exportando os contatos.
    fclose(fp); //Fecha o arquivo de destino após concluir a escrita dos contatos.
    printf("Contatos exportados para '%s' com sucesso.\n", arquivo); //Imprime uma mensagem informando que a exportação foi concluída com sucesso, incluindo o nome do arquivo para o qual os contatos foram exportados.
}
