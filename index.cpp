#include <iostream>

using namespace std;

typedef struct Date {
    int dia;
    int mes;
    int ano;
} Date;

typedef struct Address {
    char *rua;
    int numero;
    char *bairro;
    char *cidade;
    char *estado;
    int cep;
} Address;

typedef struct Profissao {
    int codigo; // Primary Key
    char *nome;
    char *sigla;
} Profissao;

typedef struct Profissional {
    int matricula; // Primary Key
    Profissao *profissao; // Foreing Key
    int cpf;
    char *nome;
    Date dataNascimento;
    int regProfissional;
    int telefone;
    char *email;
} Profissional;

typedef struct Cliente {
    int matricula; // Primary Key
    int cpf;
    char *nome;
    Date dataNascimento;
    int idade;
    char *email;
    int telefone;
    Address endereco;
} Cliente;

typedef struct Atendimento {
    int numeroAtendimento; // Primary Key
    Profissional *matProfissional; // Foreing Key
    Cliente *codCliente; // Foreing Key
    Date dataAtendimento;
    char *descricao;
} Atendimento;

int main(){

    system("pause");
    return 0;
}