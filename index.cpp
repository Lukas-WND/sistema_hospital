#include <iostream>

using namespace std;

#define MAX_CLIENTES 10

typedef struct Date {
    int dia;
    int mes;
    int ano;
} Date;

typedef struct Address {
    char rua[50];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[50];
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
    char nome[50];
    Date dataNascimento;
    int idade;
    char email[50];
    int telefone;
    Address endereco;
} Cliente;

// Função para adicionar um cliente
// Função para adicionar um cliente
void addCliente(Cliente *cliente) {
    cout << "Digite o nome do cliente: ";
    cin.ignore();
    cin.getline(cliente->nome, 50);

    cout << "Digite o CPF do cliente: ";
    cin >> cliente->cpf;

    cout << "Digite a data de nascimento do cliente: ";
    cin >> cliente->dataNascimento.dia >> cliente->dataNascimento.mes >> cliente->dataNascimento.ano;

    cout << "Digite a idade do cliente: ";
    cin >> cliente->idade;

    cout << "Digite o email do cliente: ";
    cin.ignore();
    cin.getline(cliente->email, 50);

    cout << "Digite o telefone do cliente: ";
    cin >> cliente->telefone;

    cin.ignore(); // Limpa o buffer do caractere de nova linha

    cout << "Digite o endereço do cliente: ";
    cin.getline(cliente->endereco.rua, 50);

    cout << "Digite o número do endereço do cliente: ";
    cin >> cliente->endereco.numero;
    cin.ignore(); // Limpa o buffer do caractere de nova linha

    cout << "Digite o bairro do cliente: ";
    cin.getline(cliente->endereco.bairro, 50);

    cout << "Digite a cidade do cliente: ";
    cin.getline(cliente->endereco.cidade, 50);

    cout << "Digite o estado do cliente: ";
    cin.getline(cliente->endereco.estado, 50);

    cout << "Digite o CEP do cliente: ";
    cin >> cliente->endereco.cep;
}

//função para mostrar um cliente cadastrado
void showCliente(Cliente cliente) {
    cout << "----------------------------------------" << endl;
    cout << endl;
    cout << endl;
    cout << "Nome: " << cliente.nome << endl;
    cout << "CPF: " << cliente.cpf << endl;
    cout << "Data de nascimento: " << cliente.dataNascimento.dia << "/" << cliente.dataNascimento.mes << "/" << cliente.dataNascimento.ano << endl;
    cout << "Idade: " << cliente.idade << endl;
    cout << "Email: " << cliente.email << endl;
    cout << "Telefone: " << cliente.telefone << endl;
    cout << "Endereço: " << cliente.endereco.rua << ", " << cliente.endereco.numero << ", " << cliente.endereco.bairro << ", " << cliente.endereco.cidade << ", " << cliente.endereco.estado << ", " << cliente.endereco.cep << endl;
    cout << endl;
    cout << endl;
    cout << "----------------------------------------" << endl;
}

//função para mostrar todos os clientes cadastrados
void showAllClientes(Cliente *clientes, int qtdClientes) {
    for (int i = 0; i < qtdClientes; i++) {
        showCliente(clientes[i]);
    }
}

typedef struct Atendimento {
    int numeroAtendimento; // Primary Key
    Profissional *matProfissional; // Foreing Key
    Cliente *codCliente; // Foreing Key
    Date dataAtendimento;
    char *descricao;
} Atendimento;

int main(){
    Cliente clientes[MAX_CLIENTES];
    int qtdClientes = 0;
    int opcao = 0;
    do {
        cout << "1 - Cadastrar cliente" << endl;
        cout << "2 - Mostrar todos os clientes" << endl;
        cout << "3 - Mostrar um cliente" << endl;
        cout << "4 - Cadastrar profissional" << endl;
        cout << "5 - Mostrar todos os profissionais" << endl;
        cout << "6 - Mostrar um profissional" << endl;
        cout << "7 - Cadastrar atendimento" << endl;
        cout << "8 - Mostrar todos os atendimentos" << endl;
        cout << "9 - Mostrar um atendimento" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite uma opção: ";
        cin >> opcao;
        switch (opcao) {
            case 1:
                addCliente(&clientes[qtdClientes]);
                qtdClientes++;
                break;
            case 2:
                showAllClientes(clientes, qtdClientes);
                break;
            case 3:
                int codCliente;
                cout << "Digite o código do cliente: ";
                cin >> codCliente;
                showCliente(clientes[codCliente]);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
        }
    } while (opcao != 0);
    system("pause");
    return 0;
}