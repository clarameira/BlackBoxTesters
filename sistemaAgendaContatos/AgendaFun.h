#include "AgendaFun.c"
#define size 32

//Função para criar um novo contato com os dados fornecidos
struct contato *criaContato(char *nome, char *tel, char *email);

//Função que calcula o índice na tabela hash usando divisão
int funHashDiv(int key);

//Função para inserir um contato na tabela hash
int inserir(agendaDeContatos Hash, struct contato *c);

//Função para buscar um contato na tabela hash pelo nome
struct contato *buscarContato(agendaDeContatos Hash, char *nome);

//Função para remover um contato da tabela hash pelo nome
void removerContato(agendaDeContatos Hash, char *nome);

//Função para listar todos os contatos na tabela hash
void listarContatos(agendaDeContatos Hash);

//Função para exportar os contatos para um arquivo
void exportarContatos(agendaDeContatos Hash, char *arquivo);
