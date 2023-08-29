#include <iostream>
#include <string.h>

#define MAX_CLIENTES 10

#define LIMITVET 50

using namespace std;

typedef struct Date
{
    int dia;
    int mes;
    int ano;
} Date;

typedef struct Address
{
    char rua[50];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[50];
    int cep;
} Address;

typedef struct Profissao
{
    int codigo; // Primary Key
    char *nome;
    char *sigla;
} Profissao;

typedef struct Profissional
{
    int matricula;        // Primary Key
    Profissao *profissao; // Foreing Key
    int cpf;
    char *nome;
    Date dataNascimento;
    int regProfissional;
    int telefone;
    char *email;
} Profissional;

typedef struct Cliente
{
    char matricula[10];
    char cpf[15];
    char nome[50];
    Date dataNascimento;
    int idade;
    char email[50];
    char telefone[15];
    Address endereco;
} Cliente;

int buscarPosicaoCliente(Cliente *clientes, int qtdClientes, const char *cpf)
{
    for (int i = 0; i < qtdClientes; i++)
    {
        if (strcmp(clientes[i].cpf, cpf) == 0)
        {
            return i;
        }
    }
    return -1;
}

void cadastrarCliente(Cliente *clientes, int *qtdClientes)
{
    if (*qtdClientes < MAX_CLIENTES)
    {
        cin.ignore(); // Clear the input buffer
        cout << "Digite o nome do cliente: ";
        cin.getline(clientes[*qtdClientes].nome, sizeof(clientes[*qtdClientes].nome));
        cout << "Digite o CPF do cliente: ";
        cin.getline(clientes[*qtdClientes].cpf, sizeof(clientes[*qtdClientes].cpf));
        cout << "Digite o email do cliente: ";
        cin.getline(clientes[*qtdClientes].email, sizeof(clientes[*qtdClientes].email));
        cout << "Digite o telefone do cliente: ";
        cin.getline(clientes[*qtdClientes].telefone, sizeof(clientes[*qtdClientes].telefone));
        cout << "Digite o dia de nascimento do cliente: ";
        cin >> clientes[*qtdClientes].dataNascimento.dia;
        cout << "Digite o mes de nascimento do cliente: ";
        cin >> clientes[*qtdClientes].dataNascimento.mes;
        cout << "Digite o ano de nascimento do cliente: ";
        cin >> clientes[*qtdClientes].dataNascimento.ano;
        cout << "Digite o numero da casa do cliente: ";
        cin >> clientes[*qtdClientes].endereco.numero;
        cin.ignore(); // Clear the newline character from the previous input
        cout << "Digite o nome da rua do cliente: ";
        cin.getline(clientes[*qtdClientes].endereco.rua, sizeof(clientes[*qtdClientes].endereco.rua));
        cout << "Digite o nome do bairro do cliente: ";
        cin.getline(clientes[*qtdClientes].endereco.bairro, sizeof(clientes[*qtdClientes].endereco.bairro));
        cout << "Digite o nome da cidade do cliente: ";
        cin.getline(clientes[*qtdClientes].endereco.cidade, sizeof(clientes[*qtdClientes].endereco.cidade));
        cout << "Digite o nome do estado do cliente: ";
        cin.getline(clientes[*qtdClientes].endereco.estado, sizeof(clientes[*qtdClientes].endereco.estado));
        cout << "Digite o CEP do cliente: ";
        cin >> clientes[*qtdClientes].endereco.cep;
        (*qtdClientes)++;
    }
    else
    {
        cout << "Limite de clientes atingido!" << endl;
    }
}

void exibirCliente(Cliente cliente)
{
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "Nome: " << cliente.nome << endl;
    cout << "CPF: " << cliente.cpf << endl;
    cout << "Email: " << cliente.email << endl;
    cout << "Telefone: " << cliente.telefone << endl;
    cout << "Data de nascimento: " << cliente.dataNascimento.dia << "/" << cliente.dataNascimento.mes << "/" << cliente.dataNascimento.ano << endl;
    cout << "Numero: " << cliente.endereco.numero << endl;
    cout << "Rua: " << cliente.endereco.rua << endl;
    cout << "Bairro: " << cliente.endereco.bairro << endl;
    cout << "Cidade: " << cliente.endereco.cidade << endl;
    cout << "Estado: " << cliente.endereco.estado << endl;
    cout << "CEP: " << cliente.endereco.cep << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
}

void exibirListaClientes(Cliente *clientes, int qtdClientes)
{
    for (int i = 0; i < qtdClientes; i++)
    {
        exibirCliente(clientes[i]);
    }
}

void atualizarCliente(Cliente *clientes, int qtdClientes)
{
    char cpf[11];

    system("cls");
    fflush(stdin);

    cout << "Digite o CPF do cliente que deseja atualizar: ";
    cin.getline(cpf, sizeof(cpf));

    int posicao = buscarPosicaoCliente(clientes, qtdClientes, cpf);
    if (posicao != -1)
    {
        cout << "Digite o nome do cliente: ";
        cin >> clientes[posicao].nome;
        cout << "Digite o CPF do cliente: ";
        cin >> clientes[posicao].cpf;
        cout << "Digite o email do cliente: ";
        cin >> clientes[posicao].email;
        cout << "Digite o telefone do cliente: ";
        cin >> clientes[posicao].telefone;
        cout << "Digite o dia de nascimento do cliente: ";
        cin >> clientes[posicao].dataNascimento.dia;
        cout << "Digite o mes de nascimento do cliente: ";
        cin >> clientes[posicao].dataNascimento.mes;
        cout << "Digite o ano de nascimento do cliente: ";
        cin >> clientes[posicao].dataNascimento.ano;
        cout << "Digite o numero da casa do cliente: ";
        cin >> clientes[posicao].endereco.numero;
        cout << "Digite o nome da rua do cliente: ";
        cin >> clientes[posicao].endereco.rua;
        cout << "Digite o nome do bairro do cliente: ";
        cin >> clientes[posicao].endereco.bairro;
        cout << "Digite o nome da cidade do cliente: ";
        cin >> clientes[posicao].endereco.cidade;
        cout << "Digite o nome do estado do cliente: ";
        cin >> clientes[posicao].endereco.estado;
        cout << "Digite o CEP do cliente: ";
        cin >> clientes[posicao].endereco.cep;
    }
    else
    {
        cout << "Cliente nao encontrado!" << endl;
    }
}

void excluirCliente(Cliente *clientes, int *qtdClientes)
{
    char cpf[11];

    system("cls");
    fflush(stdin);

    cout << "Digite o CPF do cliente que deseja excluir: ";
    cin.getline(cpf, sizeof(cpf));

    int posicao = buscarPosicaoCliente(clientes, *qtdClientes, cpf);
    if (posicao != -1)
    {
        for (int i = posicao; i < *qtdClientes; i++)
        {
            clientes[i] = clientes[i + 1];
        }
        (*qtdClientes)--;
    }
    else
    {
        cout << "Cliente nao encontrado!" << endl;
    }
}

// void validação([$nome = '', $cpf = '', $email = "" , $telefone = '', $dataNascimento, $numero, $rua, $bairro, $cidade, $estado, $cep],){
//     //validar uma a uma com regras, e caso uma seja encontrada erro, ela retorna para o usuário e pede para ele corrigir.
//     //validar nome
//     if (strlen($nome) < 3){
//         echo "Nome inválido, digite novamente";
//     }
//     //validar cpf
//         while()
//         if (strlen($cpf) < 11){
//         cin.gets
//         }
//     //validar email
//     if (strlen($email) < 10){
//         echo "Email inválido, digite novamente";
//     }
//     //validar telefone
//     if (strlen($telefone) < 8){
//         echo "Telefone inválido, digite novamente";
//     }
//     //validar data de nascimento
//     if (strlen($dataNascimento) < 8){
//         echo "Data de nascimento inválida, digite novamente";
//     }
// }


// validacao([$nome, $cpf], true);


void menuClientes(Cliente *clientes, int *qtdClientes)
{
    int opcao = 0;
    int posicao = -1; // Define the variable outside the switch
    char cpf[12];

    while (opcao != 6)
    {
        system("cls");
        fflush(stdin);

        cout << "1 - Cadastrar cliente" << endl;
        cout << "2 - Exibir cliente" << endl;
        cout << "3 - Exibir lista de clientes" << endl;
        cout << "4 - Atualizar cliente" << endl;
        cout << "5 - Excluir cliente" << endl;
        cout << "6 - Voltar" << endl;

        cout << "Digite a opcao desejada: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            cadastrarCliente(clientes, qtdClientes);
            break;
        case 2:
            cout << "Digite o CPF do cliente que deseja exibir: ";
            cin.ignore();
            cin.getline(cpf, sizeof(cpf));
            posicao = buscarPosicaoCliente(clientes, *qtdClientes, cpf);
            if (posicao != -1)
            {
                exibirCliente(clientes[posicao]);
            }
            else
            {
                cout << "Cliente nao encontrado!" << endl;
            }
            break;
        case 3:
            exibirListaClientes(clientes, *qtdClientes);
            break;
        case 4:
            posicao = -1; // Reset the posicao variable
            cout << "Digite o CPF do cliente que deseja atualizar: ";
            cin.ignore();
            cin.getline(cpf, sizeof(cpf));
            posicao = buscarPosicaoCliente(clientes, *qtdClientes, cpf);
            if (posicao != -1)
            {
                atualizarCliente(clientes, *qtdClientes);
            }
            else
            {
                cout << "Cliente nao encontrado!" << endl;
            }
            break;
        case 5:
            posicao = -1; // Reset the posicao variable
            excluirCliente(clientes, qtdClientes);
            break;
        case 6:
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
        system("pause");
    }
}

int main()
{
    Cliente clientes[MAX_CLIENTES];
    int qtdClientes = 0;

    int opcao = 0;

    while (opcao != 5)
    {
        system("cls");
        fflush(stdin);

        cout << "1 - Menu de clientes" << endl;
        cout << "2 - Menu de profissionais" << endl;
        cout << "3 - Menu de servicos" << endl;
        cout << "4 - Menu de agendamentos" << endl;
        cout << "5 - Sair" << endl;

        cout << "Digite a opcao desejada: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            menuClientes(clientes, &qtdClientes);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
        system("pause");
    }
}