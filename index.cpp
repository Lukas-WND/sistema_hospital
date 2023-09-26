#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <fstream>

#define MAX_CLIENTES 100
#define MAX_ATENDIMENTO 100

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
    char nome[LIMITVET];
    char sigla[7];
} Profissao;

typedef struct Profissional
{
    int matricula;        // Primary Key
    Profissao *profissao; // Foreing Key
    char cpf[12];
    char nome[LIMITVET];
    Date dataNascimento;
    char regProfissional[7];
    char telefone[12];
    char email[LIMITVET];
} Profissional;

typedef struct Cliente
{
    char matricula[5]; // Primary Key
    char cpf[15];
    char nome[50];
    Date dataNascimento;
    char email[50];
    char telefone[15];
    Address endereco;
} Cliente;

typedef struct Atendimento
{
    char numeroAtendimento[5];     // Primary Key
    Profissional *matProfissional; // Foreing Key
    Cliente *codCliente;           // Foreing Key
    Date dataAtendimento;
    char descricao[500];
} Atendimento;

// Arquivos para armazenamento de informações
const string CLIENTES_FILE = "clientes.txt";
const string PROFISSOES_FILE = "profissoes.txt";
const string PROFISSIONAIS_FILE = "profissionais.txt";
const string ATENDIMENTOS_FILE = "atendimentos.txt";

// Protótipos dos métodos de Cliente
int buscarPosicaoCliente(Cliente *clientes, int qtdClientes, char *matricula);
void salvarClientes(const Cliente *clientes, int qtdClientes);
void carregarClientes(Cliente *clientes, int *qtdClientes);
void cadastrarCliente(Cliente *clientes, int *qtdClientes);
void exibirCliente(Cliente cliente);
void exibirListaClientes(Cliente *clientes, int qtdClientes);
void atualizarCliente(Cliente *clientes, int qtdClientes, int posicao);
void excluirCliente(Cliente *clientes, int *qtdClientes);
void menuClientes(Cliente *clientes, int *qtdClientes);

int buscarPosicaoCliente(Cliente *clientes, int qtdClientes, char *matricula)
{
    for (int i = 0; i < qtdClientes; i++)
    {
        if (strcmp(clientes[i].matricula, matricula) == 0)
        {
            return i;
        }
    }
    return -1;
}

void salvarClientes(const Cliente *clientes, int qtdClientes)
{
    ofstream file(CLIENTES_FILE);

    if (file.is_open())
    {
        for (int i = 0; i < qtdClientes; i++)
        {
            file << clientes[i].matricula << ";"
                 << clientes[i].cpf << ";"
                 << clientes[i].nome << ";"
                 << clientes[i].dataNascimento.dia << ";"
                 << clientes[i].dataNascimento.mes << ";"
                 << clientes[i].dataNascimento.ano << ";"
                 << clientes[i].email << ";"
                 << clientes[i].telefone << ";"
                 << clientes[i].endereco.numero << ";"
                 << clientes[i].endereco.rua << ";"
                 << clientes[i].endereco.bairro << ";"
                 << clientes[i].endereco.cidade << ";"
                 << clientes[i].endereco.estado << ";"
                 << clientes[i].endereco.cep << endl;
        }
        file.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de clientes para salvar." << endl;
    }
}

void carregarClientes(Cliente *clientes, int *qtdClientes)
{
    ifstream file(CLIENTES_FILE);

    if (file.is_open())
    {
        *qtdClientes = 0; // Reset the client count

        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                Cliente novoCliente;
                istringstream ss(line);
                string field;

                getline(ss, field, ';');
                strcpy(novoCliente.matricula, field.c_str());

                getline(ss, field, ';');
                strcpy(novoCliente.cpf, field.c_str());

                getline(ss, field, ';');
                strcpy(novoCliente.nome, field.c_str());

                getline(ss, field, ';');
                novoCliente.dataNascimento.dia = stoi(field);

                getline(ss, field, ';');
                novoCliente.dataNascimento.mes = stoi(field);

                getline(ss, field, ';');
                novoCliente.dataNascimento.ano = stoi(field);

                getline(ss, field, ';');
                strcpy(novoCliente.email, field.c_str());

                getline(ss, field, ';');
                strcpy(novoCliente.telefone, field.c_str());

                getline(ss, field, ';');
                novoCliente.endereco.numero = stoi(field);

                getline(ss, field, ';');
                strcpy(novoCliente.endereco.rua, field.c_str());

                getline(ss, field, ';');
                strcpy(novoCliente.endereco.bairro, field.c_str());

                getline(ss, field, ';');
                strcpy(novoCliente.endereco.cidade, field.c_str());

                getline(ss, field, ';');
                strcpy(novoCliente.endereco.estado, field.c_str());

                getline(ss, field, ';');
                novoCliente.endereco.cep = stoi(field);

                clientes[*qtdClientes] = novoCliente;
                (*qtdClientes)++;
            }
        }
        file.close();
    }
    else
    {
        cout << "Arquivo de clientes nao encontrado. Os registros serao carregados vazios." << endl;
    }
}

char *getMatricula(int qtdCLientes, char *matricula)
{
    // pegar a quantidade matriculas e adicionar 3 zeros a esquerda se menor 10, 2 se menor que 100 e 1 se menor que 1000
    if (qtdCLientes < 10)
    {
        sprintf(matricula, "000%d", qtdCLientes + 1);
        return matricula;
    }
    else if (qtdCLientes < 100)
    {
        sprintf(matricula, "00%d", qtdCLientes + 1);
        return matricula;
    }
    else
    {
        sprintf(matricula, "0%d", qtdCLientes + 1);
        return matricula;
    }
}

void cadastrarCliente(Cliente *clientes, int *qtdClientes)
{
    if (*qtdClientes < MAX_CLIENTES)
    {
        int valid = 0;
        char matricula[5];
        strcpy(clientes[*qtdClientes].matricula, getMatricula(*qtdClientes, matricula));

        cin.ignore(); // Clear the input buffer
        cout << "Digite o nome do cliente: ";
        cin.getline(clientes[*qtdClientes].nome, sizeof(clientes[*qtdClientes].nome));
        cout << "Digite o CPF do cliente (11 digitos, sem simbolos): ";
        cin.getline(clientes[*qtdClientes].cpf, sizeof(clientes[*qtdClientes].cpf));
        cout << "Digite o email do cliente: ";
        cin.getline(clientes[*qtdClientes].email, sizeof(clientes[*qtdClientes].email));
        cout << "Digite o telefone do cliente(11 digitos, sem simbolos, ex: 92991203040): ";
        cin.getline(clientes[*qtdClientes].telefone, sizeof(clientes[*qtdClientes].telefone));
        cout << "Digite o dia de nascimento do cliente: ";
        while (valid == 0)
        {
            cin >> clientes[*qtdClientes].dataNascimento.dia;
            cin.ignore();
            if (clientes[*qtdClientes].dataNascimento.dia > 0 && clientes[*qtdClientes].dataNascimento.dia <= 31)
            {
                valid = 1;
            }
            else
            {
                cout << "\nDia informado invalido, tente novamente!\n";
            }
        }

        cout << "Digite o mes de nascimento do cliente: ";

        while (valid == 1)
        {
            cin >> clientes[*qtdClientes].dataNascimento.mes;
            cin.ignore();
            if (clientes[*qtdClientes].dataNascimento.mes > 0 && clientes[*qtdClientes].dataNascimento.mes <= 12)
            {
                valid = 2;
            }
            else
            {
                cout << "\nMes informado invalido, tente novamente!\n";
            }
        }
        cout << "Digite o ano de nascimento do cliente: ";

        while (valid == 2)
        {
            cin >> clientes[*qtdClientes].dataNascimento.ano;
            cin.ignore();
            if (clientes[*qtdClientes].dataNascimento.ano > (2023 - 120) && clientes[*qtdClientes].dataNascimento.ano <= (2023))
            {
                valid = 3;
            }
            else
            {
                cout << "\nAno informado invalido, tente novamente!\n\n";
            }
        }
        cout << "Digite o numero da casa do cliente: ";
        cin >> clientes[*qtdClientes].endereco.numero;
        cout << "Digite o nome da rua do cliente: ";
        cin.ignore(); // Clear the newline character from the previous input
        cin.getline(clientes[*qtdClientes].endereco.rua, sizeof(clientes[*qtdClientes].endereco.rua));
        cout << "Digite o nome do bairro do cliente: ";
        cin.getline(clientes[*qtdClientes].endereco.bairro, sizeof(clientes[*qtdClientes].endereco.bairro));
        cout << "Digite o nome da cidade do cliente: ";
        cin.getline(clientes[*qtdClientes].endereco.cidade, sizeof(clientes[*qtdClientes].endereco.cidade));
        cout << "Digite o nome do estado do cliente: ";
        cin.getline(clientes[*qtdClientes].endereco.estado, sizeof(clientes[*qtdClientes].endereco.estado));
        cout << "Digite o CEP do cliente (8 digitos, sem simbolos): ";
        cin >> clientes[*qtdClientes].endereco.cep;
        (*qtdClientes)++;
        salvarClientes(clientes, *qtdClientes);
    }
    else
    {
        cout << "Limite de clientes atingido!" << endl;
    }

    system("cls");
}

void exibirCliente(Cliente cliente)
{
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "Matricula: " << cliente.matricula << endl;
    cout << "Nome: " << cliente.nome << endl;
    cout << "CPF: " << cliente.cpf << endl;
    cout << "Email: " << cliente.email << endl;
    cout << "Telefone: " << cliente.telefone << endl;
    cout << "Data de nascimento: ";

    if (cliente.dataNascimento.dia < 10)
    {
        cout << "0" << cliente.dataNascimento.dia;
    }
    else
    {
        cout << cliente.dataNascimento.dia;
    }
    cout << "/";
    if (cliente.dataNascimento.mes < 10)
    {
        cout << "0" << cliente.dataNascimento.mes;
    }
    else
    {
        cout << cliente.dataNascimento.mes;
    }
    cout << "/";
    cout << cliente.dataNascimento.ano << endl;

    cout << "Rua: " << cliente.endereco.rua << endl;
    cout << "Numero: " << cliente.endereco.numero << endl;
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

void atualizarCliente(Cliente *clientes, int qtdClientes, int posicao)
{
    int valid = 0;

    system("cls");
    fflush(stdin);

    cout << "Atualizando cliente: " << clientes[posicao].nome << endl;
    cout << "Digite o novo nome do cliente: ";
    cin.getline(clientes[posicao].nome, sizeof(clientes[posicao].nome));
    cout << "Digite o novo CPF do cliente: ";
    cin.getline(clientes[posicao].cpf, sizeof(clientes[posicao].cpf));
    cout << "Digite o novo email do cliente: ";
    cin.getline(clientes[posicao].email, sizeof(clientes[posicao].email));
    cout << "Digite o novo telefone do cliente: ";
    cin.getline(clientes[posicao].telefone, sizeof(clientes[posicao].telefone));
    cout << "Digite o novo dia de nascimento do cliente: ";
    while (valid == 0)
    {
        cin >> clientes[posicao].dataNascimento.dia;
        cin.ignore();
        if (clientes[posicao].dataNascimento.dia > 0 && clientes[posicao].dataNascimento.dia <= 31)
        {
            valid = 1;
        }
        else
        {
            cout << "\nDia informado invalido, tente novamente!\n";
        }
    }
    cout << "Digite o novo mes de nascimento do cliente: ";
    while (valid == 1)
    {
        cin >> clientes[posicao].dataNascimento.mes;
        cin.ignore();
        if (clientes[posicao].dataNascimento.mes > 0 && clientes[posicao].dataNascimento.mes <= 12)
        {
            valid = 2;
        }
        else
        {
            cout << "\nMes informado invalido, tente novamente!\n";
        }
    }
    cout << "Digite o novo ano de nascimento do cliente: ";
    while (valid == 2)
    {
        cin >> clientes[posicao].dataNascimento.ano;
        cin.ignore();
        if (clientes[posicao].dataNascimento.ano > (2023 - 120) && clientes[posicao].dataNascimento.ano <= (2023))
        {
            valid = 3;
        }
        else
        {
            cout << "\nAno informado invalido, tente novamente!\n\n";
        }
    }
    cout << "Digite o novo numero da casa do cliente: ";
    cin >> clientes[posicao].endereco.numero;
    cout << "Digite o novo nome da rua do cliente: ";
    cin.ignore();
    cin.getline(clientes[posicao].endereco.rua, sizeof(clientes[posicao].endereco.rua));
    cout << "Digite o novo nome do bairro do cliente: ";
    cin.getline(clientes[posicao].endereco.bairro, sizeof(clientes[posicao].endereco.bairro));
    cout << "Digite o novo nome da cidade do cliente: ";
    cin.getline(clientes[posicao].endereco.cidade, sizeof(clientes[posicao].endereco.cidade));
    cout << "Digite o novo nome do estado do cliente: ";
    cin.getline(clientes[posicao].endereco.estado, sizeof(clientes[posicao].endereco.estado));
    cout << "Digite o novo CEP do cliente: ";
    cin >> clientes[posicao].endereco.cep;
    salvarClientes(clientes, qtdClientes);

    system("cls");
    cout << "Cliente atualizado com sucesso!\n\n";
}

void excluirCliente(Cliente *clientes, int *qtdClientes)
{
    char matricula[5];

    system("cls");
    fflush(stdin);

    cout << "Digite a matricula do cliente que deseja excluir: ";
    cin.getline(matricula, sizeof(matricula));

    int posicao = buscarPosicaoCliente(clientes, *qtdClientes, matricula);
    if (posicao != -1)
    {
        for (int i = posicao; i < *qtdClientes - 1; i++)
        {
            clientes[i] = clientes[i + 1];
        }
        (*qtdClientes)--;

        for (int i = posicao; i < *qtdClientes; i++)
        {
            char novaMatricula[5];
            getMatricula(i, novaMatricula);
            strcpy(clientes[i].matricula, novaMatricula);
        }

        salvarClientes(clientes, *qtdClientes);
        system("cls");
    }
    else
    {
        cout << "\nCliente nao encontrado!\n\n";
    }
}

void menuClientes(Cliente *clientes, int *qtdClientes)
{
    int opcao = 0;
    int posicao = -1;
    char matricula[5];

    system("cls");

    while (opcao != 6)
    {
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
            posicao = -1; // Reset the posicao variable
            cout << "Digite a matricula do cliente que deseja exibir: ";
            cin.ignore();
            cin.getline(matricula, sizeof(matricula));
            posicao = buscarPosicaoCliente(clientes, *qtdClientes, matricula);
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
            cout << "__________________________________________________________" << endl;
            cout << "Usuarios cadastrados: " << endl;
            exibirListaClientes(clientes, *qtdClientes);
            cout << "__________________________________________________________" << endl;
            cout << "Digite a matricula do cliente que deseja alterar: ";
            cin.ignore();
            cin.getline(matricula, sizeof(matricula));
            posicao = buscarPosicaoCliente(clientes, *qtdClientes, matricula);
            if (posicao != -1)
            {
                atualizarCliente(clientes, *qtdClientes, posicao);
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
            system("cls");
            break;
        default:
            system("cls");
            cout << "Opcao invalida!\n\n";
            break;
        }
    }
}
// metodos cliente fim

// metodos profissão inicio

// Método que percorre o vetor e retorna o índice que contém o valor passado pelo parâmetro codProfissao
int buscarPosicaoProfissao(Profissao *listaProfissao, int qntProfissoes, int codigoProfissao)
{

    for (int i = 0; i < qntProfissoes; i++)
    {
        // Verirfica se o valor passado por parâmetro corresponde ao valor da variável na posição i do vetor
        if (listaProfissao[i].codigo == codigoProfissao)
        {
            return i; // Retorna i caso seja verdadeiro
        }
    }

    /*Se o vetor inteiro for percorrido e a condição não for satisfeita,
     * então o valor passado pelo parâmetro não está contido no vetor*/
    return -1;
}

// Método que percorre o vetor e retorna o índice que contém o valor passado pelo parâmetro numMatricula
int buscarPosicaoProfissional(Profissional *listaProfissionais, int qntProfissionais, int numMatricula)
{
    // Verirfica se o valor passado por parâmetro corresponde ao valor da variável na posição i do vetor
    for (int i = 0; i < qntProfissionais; i++)
    {
        if (listaProfissionais[i].matricula == numMatricula)
        {
            return i;
        }
    }

    /* Se o vetor inteiro for percorrido e a condição não for satisfeita,
     * então o valor passado pelo parâmetro não está contido no vetor*/
    return -1;
}

void salvarProfissoes(const Profissao *listaProfissoes, int qtdProfissoes)
{
    ofstream file(PROFISSOES_FILE);

    if (file.is_open())
    {
        for (int i = 0; i < qtdProfissoes; i++)
        {
            file << listaProfissoes[i].codigo << ";"
                 << listaProfissoes[i].nome << ";"
                 << listaProfissoes[i].sigla << endl;
        }
        file.close();
    }
    else
    {
        cout << "\nErro ao abrir o arquivo de profissoes para salvar." << endl;
    }
}

void carregarProfissoes(Profissao *listaProfissoes, int *qtdProfissoes, int *incCodigo)
{
    ifstream file(PROFISSOES_FILE);

    if (file.is_open())
    {
        *qtdProfissoes = 0; // Reset the client count

        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                Profissao novaProfissao;
                istringstream ss(line);
                string field;

                getline(ss, field, ';');
                novaProfissao.codigo = stoi(field);

                getline(ss, field, ';');
                strcpy(novaProfissao.nome, field.c_str());

                getline(ss, field, ';');
                strcpy(novaProfissao.sigla, field.c_str());

                listaProfissoes[*qtdProfissoes] = novaProfissao;
                (*qtdProfissoes)++;
                (*incCodigo)++;
            }
        }
        file.close();
    }
    else
    {
        cout << "\nArquivo de profissoes não encontrado. Os registros serão carregados vazios." << endl;
    }
}

// Métodos da Lista de Profissões

void exibirProfissao(Profissao profissao)
{
    // Exibe o conteúdo de uma única struct dentro do vetor das Profissões
    cout << "------------------------------------------------------------------------------------------\n\n";
    cout << "Codigo: " << profissao.codigo << "\n";
    cout << "Profissao: " << profissao.nome << "\n";
    cout << "Orgao Regulador: " << profissao.sigla << "\n";
    cout << "------------------------------------------------------------------------------------------\n\n";
}

// Método Read do CRUD das Profissões, exibe o conteúdo de todas as posições do vetor
void exibirListaProfissoes(Profissao *listaProfissoes, int qntProfissoes)
{
    for (int i = 0; i < qntProfissoes; i++)
    {
        exibirProfissao(listaProfissoes[i]);
    }
}

// Método Create do CRUD das Profissões, insere novos dados da primeira posição vazia do vetor
void cadastrarNovaProfissao(Profissao *listaProfissoes, int *qntProfissoes, int *incCodigo)
{
    int codigo;

    system("cls");

    codigo = (2023 * 100) + *incCodigo; // O código vai ser gerado a partir do ano + a variável de incremento

    listaProfissoes[*qntProfissoes].codigo = codigo;

    cout << "Informe o titulo da nova profissao: "; // Nome da profissão
    cin.ignore();
    cin.getline(listaProfissoes[*qntProfissoes].nome, LIMITVET);

    cout << "Informe a sigla do orgao regulador dessa profissao: ";
    cin.getline(listaProfissoes[*qntProfissoes].sigla, 7);

    (*incCodigo)++;
    (*qntProfissoes)++; // A quantidade de profissões cadastradas é incrementada
    salvarProfissoes(listaProfissoes, *qntProfissoes);

    system("cls");
    cout << "Nova profissao cadastrada!\n\n";
}

/* Método Update do CRUD das Profissões,
 * busca a posição correspondente a um código especificado e altera os dados daquela posição*/
void atualizarProfissao(Profissao *listaProfissoes, int qntProfissoes)
{
    int codigo, posicao;
    system("cls");

    cout << "Informe o codigo da profissao que deseja atualizar: ";
    cin >> codigo;

    posicao = buscarPosicaoProfissao(listaProfissoes, qntProfissoes, codigo);

    // Verifica se a função não retornou um valor válido de posição
    if (posicao == -1)
    {
        system("cls");
        cout << "\nProfissao nao encontrada!";
    }
    else
    {
        cout << "Informe o titulo atualizado profissao: ";
        cin.ignore(); // Limpeza do buffer
        cin.getline(listaProfissoes[posicao].nome, LIMITVET);

        cout << "Informe a sigla do orgao regulador dessa profissao: ";
        cin.getline(listaProfissoes[posicao].sigla, 6);
        salvarProfissoes(listaProfissoes, qntProfissoes);

        system("cls");
        cout << "Profissao atualizada!\n\n";
    }
}

// Método Delete do CRUD das Profissões, encontra uma posição especificada e subscreve os dados pelos da posição seguinte
void deletarProfissao(Profissao *listaProfissoes, int *qntProfissoes)
{
    int codigo, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe o codigo da profissao que deseja deletar: ";
    cin >> codigo;

    posicao = buscarPosicaoProfissao(listaProfissoes, *qntProfissoes, codigo);

    // Verifica se o método encontrou uma posição válida
    if (posicao == -1)
    {
        system("cls");
        cout << "Codigo nao encontrado!\n";
    }
    else
    {
        // A partir da posição encontrada, o método irá sobescrever a posição atual pelo valor da posição seguinte
        for (int i = posicao; i < *qntProfissoes; i++)
        {
            listaProfissoes[i] = listaProfissoes[i + 1];
        }

        (*qntProfissoes)--; // A quantidade de registros existentes no vetor Profissoes é decrementada
        salvarProfissoes(listaProfissoes, *qntProfissoes);

        system("cls");
        cout << "Profissao deletada dos registros!\n\n";
    }
}

// Menu secundário, correspondente ao CRUD das Profissões
void menuProfissoes(Profissao *listaProfissoes, int *qntProfissoes, int *incCodigo)
{
    int menu = 0;

    system("cls");

    while (menu != 5)
    {
        fflush(stdin);

        cout << "Bem-vindo ao menu das profissoes!\n";
        cout << "Por favor, selecione uma opcao a seguir:\n";
        cout << "1 - Exibir a lista de profissoes cadastradas\n";
        cout << "2 - Cadastrar uma nova profissao\n";
        cout << "3 - Atualizar o registro de alguma profissao\n";
        cout << "4 - Deletar o registro de alguma profissao\n";
        cout << "5 - Voltar ao menu principal\n\n";
        cin >> menu;

        switch (menu)
        {
        case 1:
            exibirListaProfissoes(listaProfissoes, *qntProfissoes);
            break;
        case 2:
            cadastrarNovaProfissao(listaProfissoes, qntProfissoes, incCodigo);
            break;
        case 3:
            atualizarProfissao(listaProfissoes, *qntProfissoes);
            break;
        case 4:
            deletarProfissao(listaProfissoes, qntProfissoes);
            break;
        case 5:
            system("cls");
            cout << "Ate a proxima!\n";
            break;
        default:
            system("cls");
            cout << "Opcao nao reconhecida, tente novamente!\n";
        }
    }
}

// Métodos da lista de Profissionais

void salvarProfissionais(const Profissional *listaProfissionais, int qtdProfissionais)
{
    ofstream file(PROFISSIONAIS_FILE);

    if (file.is_open())
    {
        for (int i = 0; i < qtdProfissionais; i++)
        {
            file << listaProfissionais[i].matricula << ";"
                 << listaProfissionais[i].profissao->codigo << ";"
                 << listaProfissionais[i].cpf << ";"
                 << listaProfissionais[i].nome << ";"
                 << listaProfissionais[i].dataNascimento.dia << ";"
                 << listaProfissionais[i].dataNascimento.mes << ";"
                 << listaProfissionais[i].dataNascimento.ano << ";"
                 << listaProfissionais[i].regProfissional << ";"
                 << listaProfissionais[i].telefone << ";"
                 << listaProfissionais[i].email << endl;
        }
        file.close();
    }
    else
    {
        cout << "\nErro ao abrir o arquivo de profissionais para salvar." << endl;
    }
}

void carregarProfissionais(Profissional *listaProfissionais,
                           Profissao *listaProfissoes,
                           int *qtdProfissionais,
                           int *incMatricula,
                           int qtdProfissoes)
{
    ifstream file(PROFISSIONAIS_FILE);

    if (file.is_open())
    {
        *qtdProfissionais = 0;

        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                Profissional novoProfissional;
                istringstream ss(line);
                string field;
                int posicao = 0;

                getline(ss, field, ';');
                novoProfissional.matricula = stoi(field);

                getline(ss, field, ';');
                posicao = buscarPosicaoProfissao(listaProfissoes, qtdProfissoes, stoi(field));
                if (posicao == -1)
                {
                    novoProfissional.profissao = NULL;
                }
                else
                {
                    novoProfissional.profissao = &listaProfissoes[posicao];
                }

                getline(ss, field, ';');
                strcpy(novoProfissional.cpf, field.c_str());

                getline(ss, field, ';');
                strcpy(novoProfissional.nome, field.c_str());

                getline(ss, field, ';');
                novoProfissional.dataNascimento.dia = stoi(field);

                getline(ss, field, ';');
                novoProfissional.dataNascimento.mes = stoi(field);

                getline(ss, field, ';');
                novoProfissional.dataNascimento.ano = stoi(field);

                getline(ss, field, ';');
                strcpy(novoProfissional.regProfissional, field.c_str());

                getline(ss, field, ';');
                strcpy(novoProfissional.telefone, field.c_str());

                getline(ss, field, ';');
                strcpy(novoProfissional.email, field.c_str());

                listaProfissionais[*qtdProfissionais] = novoProfissional;
                (*qtdProfissionais)++;
                (*incMatricula)++;
            }
        }
        file.close();
    }
    else
    {
        cout << "\nArquivo de profissionais nao encontrado. Os registros serao carregados vazios." << endl;
    }
}

// Exibe o conteúdo de um único registro da lista de Profissionais
void exibirProfissional(Profissional profissional)
{
    cout << "------------------------------------------------------------------------------------------\n\n";
    cout << "Matricula: " << profissional.matricula << "\n";
    cout << "Nome: " << profissional.nome << "\n";

    cout << "Profissao: " << profissional.profissao->nome << "\n";
    cout << "Registro Profissional: " << profissional.regProfissional << " ";
    cout << profissional.profissao->sigla << "\n";

    cout << "CPF: " << profissional.cpf << "\n";
    cout << "E-mail: " << profissional.email << "\n";
    cout << "Telefone: " << profissional.telefone << "\n";

    cout << "Data de Nascimento: ";

    if (profissional.dataNascimento.dia < 10)
    {
        cout << "0" << profissional.dataNascimento.dia;
    }
    else
    {
        cout << profissional.dataNascimento.dia;
    }
    cout << "/";
    if (profissional.dataNascimento.mes < 10)
    {
        cout << "0" << profissional.dataNascimento.mes;
    }
    else
    {
        cout << profissional.dataNascimento.mes;
    }
    cout << "/";
    cout << profissional.dataNascimento.ano << "\n";
    cout << "------------------------------------------------------------------------------------------\n\n";
}

// Método Read do CRUD dos Profissionais
void exibirListaProfissionais(Profissional *listaProfissionais, int qntProfissionais)
{
    for (int i = 0; i < qntProfissionais; i++)
    {
        exibirProfissional(listaProfissionais[i]);
    }
}

// Método Create do CRUD dos Profissionais
void cadastrarNovoProfissional(Profissao *listaProfissoes,
                               Profissional *listaProfissionais,
                               int *qntProfissoes,
                               int *qntProfissionais,
                               int *incCodigo,
                               int *incMatricula)
{

    int codigo, profissao = -1, valid = 0;
    char cadastrar;

    system("cls");

    // Exibe a lista de Profissões disponíveis
    cout << "Lista de profissoes disponiveis: \n";
    exibirListaProfissoes(listaProfissoes, *qntProfissoes);
    cout << "\nDeseja cadastrar uma nova profissao? (s/n)\n";
    cin >> cadastrar;
    cin.ignore();

    // Caso a Profissão do novo profissional não esteja na lista, é possível cadastrar uma nova profissão

    if (cadastrar == 's')
    {                                                                      // Verifica se o usuário deseja cadastrar uma nova profissão
        cadastrarNovaProfissao(listaProfissoes, qntProfissoes, incCodigo); // Chama o método de cadastro
        cout << "\nRetornando ao menu\n\n";
    }
    else if (cadastrar == 'n')
    {
        // A matrícula do Profissional é gerada a partir do ano atual somado a uma variável de incremento
        listaProfissionais[*qntProfissionais].matricula = (2023 * 1000) + *incMatricula;

        cout << "Informe o nome do novo colaborador: ";
        cin.getline(listaProfissionais[*qntProfissionais].nome, LIMITVET);

        // Loop não encerra até o usuário informar um código de profissão válido
        while (profissao < 0)
        {
            cout << "Informe o codigo da profissao do novo colaborador: ";
            cin >> codigo;
            cin.ignore();
            profissao = buscarPosicaoProfissao(listaProfissoes, *qntProfissoes, codigo);
            if (profissao == -1)
            {
                cout << "\nCodigo nao encontrado, tente novamente\n\n";
            }
            else
            {
                // O endereço de memória da profissão correspondente ao código é atribuído ao ponteiro profissao
                listaProfissionais[*qntProfissionais].profissao = &listaProfissoes[profissao];
            }
        }

        cout << "Informe o cpf do novo colaborador: ";
        cin.getline(listaProfissionais[*qntProfissionais].cpf, 12);

        cout << "Informe a data de nascimento do novo colaborador \n";

        // Sequencia de loops que validam a entrada dos dados de tipo Data
        while (valid == 0)
        {
            cout << "Dia: ";
            cin >> listaProfissionais[*qntProfissionais].dataNascimento.dia;
            cin.ignore();

            if (listaProfissionais[*qntProfissionais].dataNascimento.dia > 0 &&
                listaProfissionais[*qntProfissionais].dataNascimento.dia <= 31)
            {
                valid = 1;
            }
            else
            {
                cout << "\nDia informado invalido, tente novamente!\n";
            }
        }

        while (valid == 1)
        {
            cout << "Mes: ";
            cin >> listaProfissionais[*qntProfissionais].dataNascimento.mes;
            cin.ignore();

            if (listaProfissionais[*qntProfissionais].dataNascimento.mes > 0 &&
                listaProfissionais[*qntProfissionais].dataNascimento.mes <= 12)
            {
                valid = 2;
            }
            else
            {
                cout << "\nMes informado invalido, tente novamente!\n";
            }
        }

        while (valid == 2)
        {
            cout << "Ano: ";
            cin >> listaProfissionais[*qntProfissionais].dataNascimento.ano;
            cin.ignore();

            if (listaProfissionais[*qntProfissionais].dataNascimento.ano > (2023 - 120) &&
                listaProfissionais[*qntProfissionais].dataNascimento.ano <= (2023 - 18))
            {
                valid = 3;
            }
            else
            {
                cout << "\nAno informado invalido, ou profissional eh menor de idade, tente novamente!\n\n";
            }
        }

        cout << "\n";

        cout << "Informe o registro profissional do novo colaborador: ";
        cin.getline(listaProfissionais[*qntProfissionais].regProfissional, 7);
        cout << "Informe o telefone do novo colaborador: ";
        cin.getline(listaProfissionais[*qntProfissionais].telefone, 12);
        cout << "Informe o e-mail do novo colaborador: ";
        cin.getline(listaProfissionais[*qntProfissionais].email, LIMITVET);

        (*incMatricula)++;     // Incrementa a variável de gerar novas matrículas
        (*qntProfissionais)++; // Incrementa a quantidade de registros armazenados dentro do vetor
        salvarProfissionais(listaProfissionais, *qntProfissionais);

        system("cls");
        cout << "Novo colaborador cadastrado!\n\n";
    }
    else
    {
        system("cls");
        cout << "Opcao nao reconhecida, tente novamente!\n\n";
    }
}

// Método Update do CRUD dos Profissionais
void atualizarProfissional(Profissao *listaProfissoes,
                           Profissional *listaProfissionais,
                           int qntProfissoes,
                           int qntProfissionais)
{

    int matricula, posicao, valid = 0;

    system("cls");

    cout << "Informe a matricula do profissional que deseja atualizar os dados: ";
    cin >> matricula;
    cin.ignore();
    posicao = buscarPosicaoProfissional(listaProfissionais, qntProfissionais, matricula);

    // Verifica se o método encontrou uma posição válida correspondente à matrícula digitada
    if (posicao == -1)
    {
        system("cls");
        cout << "Matricula nao encontrada!\n\n";
    }
    else
    {
        int codigo, profissao;

        // Exibe a lista de Profissões disponíveis
        cout << "\nLista de profissoes disponiveis: \n";
        exibirListaProfissoes(listaProfissoes, qntProfissoes);

        cout << "Informe o nome do novo colaborador: \n";
        cin.getline(listaProfissionais[posicao].nome, LIMITVET);

        cout << "Informe o codigo da profissao do novo colaborador: ";
        cin >> codigo;
        cin.ignore();
        profissao = buscarPosicaoProfissao(listaProfissoes, qntProfissoes, codigo);
        listaProfissionais[posicao].profissao = &listaProfissoes[profissao];

        cout << "Informe o cpf do novo colaborador: ";
        cin.getline(listaProfissionais[posicao].cpf, 12);

        while (valid == 0)
        {
            cout << "Dia: ";
            cin >> listaProfissionais[posicao].dataNascimento.dia;
            cin.ignore();

            if (listaProfissionais[posicao].dataNascimento.dia > 0 &&
                listaProfissionais[posicao].dataNascimento.dia <= 31)
            {
                valid = 1;
            }
            else
            {
                cout << "\nDia informado invalido, tente novamente!\n";
            }
        }

        while (valid == 1)
        {
            cout << "Mes: ";
            cin >> listaProfissionais[posicao].dataNascimento.mes;
            cin.ignore();

            if (listaProfissionais[posicao].dataNascimento.mes > 0 &&
                listaProfissionais[posicao].dataNascimento.mes <= 11)
            {
                valid = 2;
            }
            else
            {
                cout << "\nMes informado invalido, tente novamente!\n";
            }
        }

        while (valid == 2)
        {
            cout << "Ano: ";
            cin >> listaProfissionais[posicao].dataNascimento.ano;
            cin.ignore();

            if (listaProfissionais[posicao].dataNascimento.ano > (2023 - 120) &&
                listaProfissionais[posicao].dataNascimento.ano <= (2023 - 18))
            {
                valid = 3;
            }
            else
            {
                cout << "\nAno informado invalido, ou profissional eh menor de idade, tente novamente!\n\n";
            }
        }

        cout << "\n";

        cout << "Informe o registro profissional do novo colaborador: ";
        cin.getline(listaProfissionais[posicao].regProfissional, 7);
        cout << "Informe o telefone do novo colaborador: ";
        cin.getline(listaProfissionais[posicao].telefone, 12);
        cout << "Informe o e-mail do novo colaborador: ";
        cin.getline(listaProfissionais[posicao].email, LIMITVET);

        salvarProfissionais(listaProfissionais, qntProfissionais);

        system("cls");
        cout << "Cadastro atualizado!\n\n";
    }
}

// Método Delete do CRUD dos Profissionais
void deletarProfissional(Profissional *listaProfissionais, int *qntProfissionais)
{

    int matricula, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe a matricula do profissional que deseja deletar: ";
    cin >> matricula;

    posicao = buscarPosicaoProfissional(listaProfissionais, *qntProfissionais, matricula);

    // Verifica se o método de busca encontrou uma posição válida
    if (posicao == -1)
    {
        cout << "\n\nMatricula nao encontrada!\n\n";
    }
    else
    {
        // A partir da posição encontrada, o método sobrescreve o valor da posição atual pelo da próxima posição do vetor
        for (int i = posicao; i < *qntProfissionais; i++)
        {
            listaProfissionais[i] = listaProfissionais[i + 1];
        }
    }

    (*qntProfissionais)--; // A quantidade de registros armazenados é decrementada
    salvarProfissionais(listaProfissionais, *qntProfissionais);

    system("cls");
    cout << "Profissional deletado dos registros!\n\n";
}

// Menu secundário, correspondente ao CRUD dos registros dos Profissionais
void menuProfissional(Profissao *listaProfissao,
                      Profissional *listaProfissionais,
                      int *qntProfissoes,
                      int *qntProfissionais,
                      int *incCodigo,
                      int *incMatricula)
{

    int menu = 0;

    system("cls");

    while (menu != 5)
    {
        fflush(stdin);
        cout << "Bem-vindo ao menu dos profissionais!\n";
        cout << "Por favor, selecione uma opcao a seguir:\n";
        cout << "1 - Exibir a lista de profissionais cadastrados\n";
        cout << "2 - Cadastrar um novo profissional\n";
        cout << "3 - Atualizar o registro de algum profissional\n";
        cout << "4 - Deletar o registro de algum profissional\n";
        cout << "5 - Voltar ao menu principal\n\n";
        cin >> menu;

        switch (menu)
        {
        case 1:
            exibirListaProfissionais(listaProfissionais, *qntProfissionais);
            break;
        case 2:
            cadastrarNovoProfissional(listaProfissao,
                                      listaProfissionais,
                                      qntProfissoes,
                                      qntProfissionais,
                                      incCodigo,
                                      incMatricula);
            break;
        case 3:
            atualizarProfissional(listaProfissao, listaProfissionais, *qntProfissoes, *qntProfissionais);
            break;
        case 4:
            deletarProfissional(listaProfissionais, qntProfissionais);
            break;
        case 5:
            system("cls");
            cout << "Ate a proxima!\n\n";
            break;
        default:
            system("cls");
            cout << "Opcao nao reconhecida, tente novamente!\n\n";
        }
    }
}

// Começo dos métodos "Atendimento"

char *getNumeroAtendimento(int qtdAtendimentos, char *numeroAtendimento);
void exibirAtendimento(Atendimento listaAtendimento);
void exibirListaAtendimento(Atendimento *listaAtendimento, int qtdAtendimentos);
int buscarAtendimento(Atendimento *listaAtendimento, int qtdAtendimentos, char *numeroAtendimento);
void deletarAtendimento(Atendimento *listaAtendimento, int *qtdAtendimentos);
void salvarAtendimentos(const Atendimento *listaAtendimentos, int qtdAtendimentos);
void carregarAtendimentos(Atendimento *listaAtendimentos,
                          Profissional *listaProfissionais,
                          Cliente *clientes,
                          int *qtdAtendimentos,
                          int qtdProfissionais,
                          int qtdClientes);
void cadastrarAtendimento(Atendimento *listaAtendimento,
                          int *qtdAtendimentos,
                          Cliente *clientes,
                          int *qtdClientes,
                          Profissional *listaProfissionais,
                          int qntProfissionais);
void atualizarAtendimento(Atendimento *listaAtendimento,
                          int *qtdAtendimentos, Cliente *clientes,
                          int *qtdClientes,
                          Profissional *listaProfissionais,
                          int qntProfissionais);
void menuAtendimento(Atendimento *listaAtendimentos,
                     int *qtdAtendimentos,
                     Cliente *clientes,
                     int *qtdClientes,
                     Profissional *listaProfissionais,
                     int qntProfissionais);

char *getNumeroAtendimento(int qtdAtendimentos, char *numeroAtendimento)
{
    if (qtdAtendimentos < 10)
    {
        sprintf(numeroAtendimento, "000%d", qtdAtendimentos + 1);
        return numeroAtendimento;
    }
    else if (qtdAtendimentos < 100)
    {
        sprintf(numeroAtendimento, "00%d", qtdAtendimentos + 1);
        return numeroAtendimento;
    }
    else
    {
        sprintf(numeroAtendimento, "0%d", qtdAtendimentos + 1);
        return numeroAtendimento;
    }
}

int buscarAtendimento(Atendimento *listaAtendimento, int qtdAtendimentos, char *numeroAtendimento)
{
    for (int i = 0; i < qtdAtendimentos; i++)
    {
        if (strcmp(listaAtendimento[i].numeroAtendimento, numeroAtendimento) == 0)
        {
            return i;
        }
    }
    return -1;
}

void salvarAtendimentos(const Atendimento *listaAtendimentos, int qtdAtendimentos)
{
    ofstream file(ATENDIMENTOS_FILE);

    if (file.is_open())
    {
        for (int i = 0; i < qtdAtendimentos; i++)
        {
            file << listaAtendimentos[i].numeroAtendimento << ";"
                 << listaAtendimentos[i].matProfissional->matricula << ";"
                 << listaAtendimentos[i].codCliente->matricula << ";"
                 << listaAtendimentos[i].dataAtendimento.dia << ";"
                 << listaAtendimentos[i].dataAtendimento.mes << ";"
                 << listaAtendimentos[i].dataAtendimento.ano << ";"
                 << listaAtendimentos[i].descricao << endl;
        }
        file.close();
    }
    else
    {
        cout << "\nErro ao abrir o arquivo de atendimentos para salvar." << endl;
    }
}

void carregarAtendimentos(Atendimento *listaAtendimentos,
                          Profissional *listaProfissionais,
                          Cliente *clientes,
                          int *qtdAtendimentos,
                          int qtdProfissionais,
                          int qtdClientes)
{
    ifstream file(ATENDIMENTOS_FILE);

    if (file.is_open())
    {
        *qtdAtendimentos = 0;

        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                Atendimento novoAtendimento;
                istringstream ss(line);
                string field;
                int posicao = 0;
                char codCliente[5];

                getline(ss, field, ';');
                strcpy(novoAtendimento.numeroAtendimento, field.c_str());

                getline(ss, field, ';');
                posicao = buscarPosicaoProfissional(listaProfissionais, qtdProfissionais, stoi(field));
                if (posicao == -1)
                {
                    novoAtendimento.matProfissional = NULL;
                }
                else
                {
                    novoAtendimento.matProfissional = &listaProfissionais[posicao];
                }

                getline(ss, field, ';');
                strcpy(codCliente, field.c_str());
                posicao = buscarPosicaoCliente(clientes, qtdClientes, codCliente);
                if (posicao == -1)
                {
                    novoAtendimento.codCliente = NULL;
                }
                else
                {
                    novoAtendimento.codCliente = &clientes[posicao];
                }

                getline(ss, field, ';');
                novoAtendimento.dataAtendimento.dia = stoi(field);

                getline(ss, field, ';');
                novoAtendimento.dataAtendimento.mes = stoi(field);

                getline(ss, field, ';');
                novoAtendimento.dataAtendimento.ano = stoi(field);

                getline(ss, field, ';');
                strcpy(novoAtendimento.descricao, field.c_str());

                listaAtendimentos[*qtdAtendimentos] = novoAtendimento;
                (*qtdAtendimentos)++;
            }
        }
        file.close();
    }
    else
    {
        cout << "\nArquivo de atendimentos nao encontrado. Os registros serao carregados vazios." << endl;
    }
}

void cadastrarAtendimento(Atendimento *listaAtendimento,
                          int *qtdAtendimentos,
                          Cliente *clientes,
                          int *qtdClientes,
                          Profissional *listaProfissionais,
                          int qntProfissionais)
{
    char matricula[5];
    int opcao1 = 0, w1 = 0, w2 = 0, matriculaP;
    system("cls");
    if (*qtdAtendimentos < MAX_ATENDIMENTO)
    {
        char numeroAtendimento[5];
        strcpy(listaAtendimento[*qtdAtendimentos].numeroAtendimento, getNumeroAtendimento(*qtdAtendimentos, numeroAtendimento));

        cout << "-----------------------\n";
        cout << "Cadastro de Atendimento\n";
        cout << "-----------------------\n\n";
        cout << "O Cliente ja foi cadastrado no Sistema?\n";
        cout << "1-Sim\n";
        cout << "2-Nao\n";
        cin >> opcao1;

        switch (opcao1)
        {
        case 1:
            while (w1 != 1)
            {
                system("cls");
                cout << "-----------------------\n";
                cout << "    lISTA DE CLIENTES   \n";
                cout << "-----------------------\n\n";
                exibirListaClientes(clientes, *qtdClientes);
                cout << "\n";
                cout << "Informe a matricula do cliente: ";
                cin.getline(matricula, sizeof(matricula));
                int posicaoC = buscarPosicaoCliente(clientes, *qtdClientes, matricula);
                if (posicaoC != -1)
                {
                    w1 = 1;
                    listaAtendimento[*qtdAtendimentos].codCliente = &clientes[posicaoC];
                    cout << "Cliente registrado no Atendimento\n";
                }
                else
                {
                    cout << "Cliente nao encontrado!" << endl;
                }
            }
            break;
        case 2:
            cadastrarCliente(clientes, qtdClientes);
            listaAtendimento[*qtdAtendimentos].codCliente = &clientes[*qtdClientes - 1];
            break;
        }
        system("cls");
        while (w2 != 1)
        {
            cout << "Escolha um profissional para o atendimento: \n\n";
            cout << "---------------------------\n";
            cout << "    Lista de Profissionais   \n";
            cout << "---------------------------\n\n";
            exibirListaProfissionais(listaProfissionais, qntProfissionais);
            cout << "Informe a matricula do profissional: ";
            cin >> matriculaP;
            int posicaoP = buscarPosicaoProfissional(listaProfissionais, qntProfissionais, matriculaP);
            if (posicaoP != -1)
            {
                w2 = 1;
                listaAtendimento[*qtdAtendimentos].matProfissional = &listaProfissionais[posicaoP];
                cout << "Profissional registrado no Atendimento\n";
            }
            else
            {
                cout << "Profissional nao encontrado!" << endl;
            }
        }
        system("cls");
        cout << "Digite o dia do Atendimento: ";
        cin >> listaAtendimento[*qtdAtendimentos].dataAtendimento.dia;
        cout << "\nDigite o mes do Atendimento: ";
        cin >> listaAtendimento[*qtdAtendimentos].dataAtendimento.mes;
        cout << "\nDigite o ano do Atendimento: ";
        cin >> listaAtendimento[*qtdAtendimentos].dataAtendimento.ano;
        cout << "Data cadastrada\n";
        cout << "Descricao do Atendimento 'max = 500 caracteres'\n";
        cin.ignore();
        cin.getline(listaAtendimento[*qtdAtendimentos].descricao, 500);

        (*qtdAtendimentos)++;
        salvarAtendimentos(listaAtendimento, *qtdAtendimentos);

        system("cls");
        cout << "Cadastro do Atendimento finalizado!\n\n";
    }
    else
    {
        system("cls");
        cout << "Maximo de Atendimentos cadastrados\n";
    }
}

void exibirAtendimento(Atendimento listaAtendimento)
{
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "Numero do Atendimento: " << listaAtendimento.numeroAtendimento << endl;
    cout << "Nome do Cliente: " << listaAtendimento.codCliente->nome << endl;
    cout << "Nome do Profissional: " << listaAtendimento.matProfissional->nome << endl;
    cout << "Data do Atendimento: ";
    if (listaAtendimento.dataAtendimento.dia < 10)
    {
        cout << "0" << listaAtendimento.dataAtendimento.dia;
    }
    else
    {
        cout << listaAtendimento.dataAtendimento.dia;
    }
    cout << "/";
    if (listaAtendimento.dataAtendimento.mes < 10)
    {
        cout << "0" << listaAtendimento.dataAtendimento.mes;
    }
    else
    {
        cout << listaAtendimento.dataAtendimento.mes;
    }
    cout << "/";
    cout << listaAtendimento.dataAtendimento.ano << "\n";
    cout << "Descricao: " << listaAtendimento.descricao << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
}

void exibirListaAtendimento(Atendimento *listaAtendimento, int qtdAtendimentos)
{
    for (int i = 0; i < qtdAtendimentos; i++)
    {
        exibirAtendimento(listaAtendimento[i]);
    }
}

void atualizarAtendimento(Atendimento *listaAtendimento,
                          int *qtdAtendimentos,
                          Cliente *clientes,
                          int *qtdClientes,
                          Profissional *listaProfissionais,
                          int qntProfissionais)
{
    char matricula[5];
    int opcao1 = 0, w1 = 0, w2 = 0, matriculaP, repeticao = 0, encontrar = 0;
    char numeroAtendimento[5];
    while (encontrar != 1)
    {
        system("cls");
        cout << "-----------------------\n";
        cout << "Atualizar Atendimento\n";
        cout << "-----------------------\n\n";
        cout << "Informe o numero do Atendimento: ";
        cin.ignore();
        cin.getline(numeroAtendimento, sizeof(numeroAtendimento));
        int atualizar = buscarAtendimento(listaAtendimento, *qtdAtendimentos, numeroAtendimento);
        if (atualizar != -1)
        {
            while (repeticao != 1)
            {
                cout << "Qual opcao a baixo gostaria de atualizar?\n";
                cout << "1 - Cliente\n";
                cout << "2 - Profissional\n";
                cout << "3 - Data\n";
                cout << "4 - Descrição\n";
                cout << "5 - Sair\n";
                cin >> opcao1;

                switch (opcao1)
                {

                case 1:
                    while (w1 != 1)
                    {
                        system("cls");
                        cout << "-----------------------\n";
                        cout << "    lISTA DE CLIENTES   \n";
                        cout << "-----------------------\n\n";
                        exibirListaClientes(clientes, *qtdClientes);
                        cout << "\n";
                        cout << "Informe a matricula do novo cliente: ";
                        cin.getline(matricula, sizeof(matricula));
                        int posicaoC = buscarPosicaoCliente(clientes, *qtdClientes, matricula);
                        if (posicaoC != -1)
                        {
                            w1 = 1;
                            listaAtendimento[atualizar].codCliente = &clientes[posicaoC];
                            cout << "Cliente registrado no Atendimento\n";
                        }
                        else
                        {
                            cout << "Cliente nao encontrado!" << endl;
                        }
                    }
                    break;
                case 2:
                    system("cls");
                    while (w2 != 1)
                    {
                        cout << "Escolha um profissional para o atendimento: \n\n";
                        cout << "---------------------------\n";
                        cout << "    Lista de Profissionais   \n";
                        cout << "---------------------------\n\n";
                        exibirListaProfissionais(listaProfissionais, qntProfissionais);
                        cout << "Informe a matricula do profissional: ";
                        cin >> matriculaP;
                        int posicaoP = buscarPosicaoProfissional(listaProfissionais, qntProfissionais, matriculaP);
                        if (posicaoP != -1)
                        {
                            w2 = 1;
                            listaAtendimento[atualizar].matProfissional = &listaProfissionais[posicaoP];
                            cout << "Profissional registrado no Atendimento\n";
                        }
                        else
                        {
                            cout << "Profissional nao encontrado!" << endl;
                        }
                    }
                    break;
                case 3:
                    system("cls");
                    cout << "Digite o novo dia do Atendimento: ";
                    cin >> listaAtendimento[atualizar].dataAtendimento.dia;
                    cout << "\nDigite o novo mes do Atendimento: ";
                    cin >> listaAtendimento[atualizar].dataAtendimento.mes;
                    cout << "\nDigite o novo ano do Atendimento: ";
                    cin >> listaAtendimento[atualizar].dataAtendimento.ano;
                    cout << "Data atualizada\n";
                    break;
                case 4:
                    cout << "Descricao do Atendimento 'max = 500 caracteres'\n";
                    cin.ignore();
                    cin.getline(listaAtendimento[atualizar].descricao, sizeof(listaAtendimento[atualizar].descricao));
                    break;
                case 5:
                    repeticao = 1;
                    encontrar = 1;
                    break;
                default:
                    cout << "Digito nao valido\n";
                    break;
                }
            }
            salvarAtendimentos(listaAtendimento, *qtdAtendimentos);
            system("cls");
        }
        else
        {
            cout << "\nAtendimento nao encontrado\n\n";
        }
    }
}

void deletarAtendimento(Atendimento *listaAtendimento, int *qtdAtendimentos)
{
    cout << "----------------------\n";
    cout << "  Excluir atendimento\n";
    cout << "----------------------\n";
    cout << "Informe o numero do Atendimento: ";
    char numeroAtendimento[5];
    cin.ignore();
    cin.getline(numeroAtendimento, sizeof(numeroAtendimento));

    int excluir = buscarAtendimento(listaAtendimento, *qtdAtendimentos, numeroAtendimento);
    if (excluir != -1)
    {
        for (int i = excluir; i < *qtdAtendimentos; i++)
        {
            listaAtendimento[i] = listaAtendimento[i + 1];
        }
        (*qtdAtendimentos)--;
        salvarAtendimentos(listaAtendimento, *qtdAtendimentos);
        system("cls");
    }
    else
    {
        cout << "\nAtendimento nao encontrado!\n\n";
    }
}

void menuAtendimento(Atendimento *listaAtendimentos,
                     int *qtdAtendimentos,
                     Cliente *clientes,
                     int *qtdClientes,
                     Profissional *listaProfissionais,
                     int qntProfissionais)
{
    int opcaomenu = 0;
    system("cls");

    while (opcaomenu != 5)
    {
        fflush(stdin);
        cout << "Bem vindo ao Menu Atendimento \n";
        cout << "Selecione alguma das opcoes a seguir: \n";
        cout << "1 - Cadastro de Atendimento \n";
        cout << "2 - Atualizar Atendimento \n";
        cout << "3 - Exibir Atendimentos \n";
        cout << "4 - Excluir Atendimento \n";
        cout << "5 - Voltar ao Menu principal \n";
        cin >> opcaomenu;

        switch (opcaomenu)
        {
        case 1:
            cadastrarAtendimento(listaAtendimentos,
                                 qtdAtendimentos,
                                 clientes,
                                 qtdClientes,
                                 listaProfissionais,
                                 qntProfissionais);
            break;
        case 2:
            atualizarAtendimento(listaAtendimentos,
                                 qtdAtendimentos,
                                 clientes,
                                 qtdClientes,
                                 listaProfissionais,
                                 qntProfissionais);
            break;
        case 3:
            exibirListaAtendimento(listaAtendimentos, *qtdAtendimentos);
            break;
        case 4:
            deletarAtendimento(listaAtendimentos, qtdAtendimentos);
            break;
        case 5:
            system("cls");
            break;
        default:
            system("cls");
            cout << "Opcao Invalida\n\n";
        }
    }
}

// Fim dos metodos de Atendimento

// Início dos métodos de Consultas

bool dataCompare(Date data1, Date data2)
{
    if (data1.dia == data2.dia && data1.mes == data2.mes && data1.ano == data2.ano)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void profissionaisAniversariantes(Date dataAtual, Profissional *listaProfissionais, int qtdProfissionais)
{
    int opcao, countAniv = 0, mesAniversario = 0;
    system("cls");

    while (opcao != 3)
    {
        cout << "Deseja saber os aniversariantes do mes atual ou de outro?" << endl;
        cout << "1 - Do mes atual" << endl;
        cout << "2 - De outro mes" << endl;
        cout << "3 - Voltar ao menu das consultas" << endl;
        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            for (int i = 0; i < qtdProfissionais; i++)
            {
                if (listaProfissionais[i].dataNascimento.mes == dataAtual.mes)
                {
                    countAniv++;
                }
            }

            if (countAniv == 0)
            {
                cout << "\nNao ha aniversariantes neste mes!" << endl;
            }
            else
            {
                Profissional aniversariantes[countAniv];

                countAniv = 0;
                for (int i = 0; i < qtdProfissionais; i++)
                {
                    if (listaProfissionais[i].dataNascimento.mes == dataAtual.mes)
                    {
                        aniversariantes[countAniv] = listaProfissionais[i];
                        countAniv++;
                    }
                }

                cout << "\nLista de profissionais aniversariantes desse mes:" << endl;
                exibirListaProfissionais(aniversariantes, countAniv);
            }
            break;
        case 2:
            while (mesAniversario > 12 || mesAniversario < 1)
            {
                cout << "\nInforme o mes que deseja buscar aniversariantes da instituicao: ";
                cin >> mesAniversario;

                if (mesAniversario < 1 || mesAniversario > 12)
                {
                    cout << "\nMes invalido, tente novamente" << endl;
                }
            }

            for (int i = 0; i < qtdProfissionais; i++)
            {
                if (listaProfissionais[i].dataNascimento.mes == mesAniversario)
                {
                    countAniv++;
                }
            }

            if (countAniv == 0)
            {
                cout << "\nNao ha aniversariantes no mes selecionado!" << endl;
            }
            else
            {
                Profissional aniversariantes[countAniv];

                countAniv = 0;
                for (int i = 0; i < qtdProfissionais; i++)
                {
                    if (listaProfissionais[i].dataNascimento.mes == mesAniversario)
                    {
                        aniversariantes[countAniv] = listaProfissionais[i];
                        countAniv++;
                    }
                }

                cout << "\nLista de profissionais aniversariantes desse mes:" << endl;
                exibirListaProfissionais(aniversariantes, countAniv);
            }
            break;
        case 3:
            system("cls");
            cout << "Ate a proxima" << endl;
            break;
        default:
            system("cls");
            cout << "Opcao nao identificada, tente novamente" << endl;
            break;
        }
        countAniv = 0;
        mesAniversario = 0;
    }
}

void clientesAniversariantes(Date dataAtual, Cliente *listaClientes, int qtdClientes)
{
    int opcao = 0, countAniv = 0, mesAniversario = 0;
    system("cls");

    while (opcao != 3)
    {
        cout << "Deseja saber os aniversariantes do mes atual ou de outro?" << endl;
        cout << "1 - Do mes atual" << endl;
        cout << "2 - De outro mes" << endl;
        cout << "3 - Voltar ao menu das consultas" << endl;
        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            for (int i = 0; i < qtdClientes; i++)
            {
                if (listaClientes[i].dataNascimento.mes == dataAtual.mes)
                {
                    countAniv++;
                }
            }

            if (countAniv == 0)
            {
                cout << "\nNao ha clientes aniversariantes neste mes!" << endl;
            }
            else
            {
                Cliente aniversariantes[countAniv];

                countAniv = 0;
                for (int i = 0; i < qtdClientes; i++)
                {
                    if (listaClientes[i].dataNascimento.mes == dataAtual.mes)
                    {
                        aniversariantes[countAniv] = listaClientes[i];
                        countAniv++;
                    }
                }

                cout << "\nLista de clientes aniversariantes desse mes:" << endl;
                exibirListaClientes(aniversariantes, countAniv);
            }
            break;
        case 2:
            while (mesAniversario > 12 || mesAniversario < 1)
            {
                cout << "\nInforme o mes que deseja buscar clientes aniversariantes: ";
                cin >> mesAniversario;

                if (mesAniversario < 1 || mesAniversario > 12)
                {
                    cout << "\nMes invalido, tente novamente" << endl;
                }
            }

            for (int i = 0; i < qtdClientes; i++)
            {
                if (listaClientes[i].dataNascimento.mes == mesAniversario)
                {
                    countAniv++;
                }
            }

            if (countAniv == 0)
            {
                cout << "\nNao ha aniversariantes no mes selecionado!" << endl;
            }
            else
            {
                Cliente aniversariantes[countAniv];

                countAniv = 0;
                for (int i = 0; i < qtdClientes; i++)
                {
                    if (listaClientes[i].dataNascimento.mes == mesAniversario)
                    {
                        aniversariantes[countAniv] = listaClientes[i];
                        countAniv++;
                    }
                }

                cout << "\nLista de clientes aniversariantes desse mes:" << endl;
                exibirListaClientes(aniversariantes, countAniv);
            }
            break;
        case 3:
            system("cls");
            cout << "Ate a proxima" << endl;
            break;
        default:
            system("cls");
            cout << "Opcao nao identificada, tente novamente" << endl;
        }
        countAniv = 0;
        mesAniversario = 0;
    }
}

void atendimentosPorData(Date dataAtual, Atendimento *listaAtendimentos, int qtdAtendimentos)
{
    int opcao = 0, countAtendimento = 0, dataValid = 0;
    Date dataAtendimento;

    system("cls");

    while (opcao != 3)
    {
        cout << "Deseja verificar os atendimentos da data atual ou de uma diferente?" << endl;
        cout << "1 - Data atual" << endl;
        cout << "2 - Data diferente" << endl;
        cout << "3 - Voltar ao menu das consultas" << endl;
        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            for (int i = 0; i < qtdAtendimentos; i++)
            {
                if (dataCompare(listaAtendimentos[i].dataAtendimento, dataAtual))
                {
                    countAtendimento++;
                }
            }

            if (countAtendimento == 0)
            {
                cout << "\nNao ha atendimentos para a data atual" << endl;
            }
            else
            {
                Atendimento atendimentosAtuais[countAtendimento];
                countAtendimento = 0;

                for (int i = 0; i < qtdAtendimentos; i++)
                {
                    if (dataCompare(listaAtendimentos[i].dataAtendimento, dataAtual))
                    {
                        atendimentosAtuais[countAtendimento] = listaAtendimentos[i];
                        countAtendimento++;
                    }
                }

                cout << "Lista de atendimentos realizados na data atual: " << endl;
                exibirListaAtendimento(atendimentosAtuais, countAtendimento);
            }
            break;
        case 2:
            cout << "Informe da Data que deseja buscar os atendimentos " << endl;

            while (dataValid == 0)
            {
                cout << "Dia: ";
                cin >> dataAtendimento.dia;
                cin.ignore();

                if (dataAtendimento.dia > 0 && dataAtendimento.dia <= 31)
                {
                    dataValid = 1;
                }
                else
                {
                    cout << "\nDia informado invalido, tente novamente!\n";
                }
            }

            while (dataValid == 1)
            {
                cout << "Mes: ";
                cin >> dataAtendimento.mes;
                cin.ignore();

                if (dataAtendimento.mes > 0 && dataAtendimento.mes <= 12)
                {
                    dataValid = 2;
                }
                else
                {
                    cout << "\nMes informado invalido, tente novamente!\n";
                }
            }

            while (dataValid == 2)
            {
                cout << "Ano: ";
                cin >> dataAtendimento.ano;
                cin.ignore();

                if (dataAtendimento.ano > (2023 - 50))
                {
                    dataValid = 3;
                }
                else
                {
                    cout << "\nAno informado invalido!\n\n";
                }
            }

            for (int i = 0; i < qtdAtendimentos; i++)
            {
                if (dataCompare(listaAtendimentos[i].dataAtendimento, dataAtendimento))
                {
                    countAtendimento++;
                }
            }

            if (countAtendimento == 0)
            {
                cout << "\nNao ha atendimentos para a data especificada" << endl;
            }
            else
            {
                Atendimento atendimentosAtuais[countAtendimento];
                countAtendimento = 0;

                for (int i = 0; i < qtdAtendimentos; i++)
                {
                    if (dataCompare(listaAtendimentos[i].dataAtendimento, dataAtendimento))
                    {
                        atendimentosAtuais[countAtendimento] = listaAtendimentos[i];
                        countAtendimento++;
                    }
                }

                cout << "Lista de atendimentos realizados na data atual: " << endl;
                exibirListaAtendimento(atendimentosAtuais, countAtendimento);
            }
            break;
        case 3:
            system("cls");
            cout << "Ate a proxima!\n\n";
            break;
        default:
            system("cls");
            cout << "Opcao invalida, tente novamente!\n\n";
        }
        countAtendimento = 0;
        dataValid = 0;
    }
}

void atendimentosPorMes(Date dataAtual, Atendimento *listaAtendimentos, int qtdAtendimentos)
{
    int opcao = 0, mes = 0, countAtendimento = 0;

    system("cls");

    while (opcao != 3)
    {
        cout << "Deseja verificar os registros de atendimento: " << endl;
        cout << "1 - Do mes atual" << endl;
        cout << "2 - De outro mes" << endl;
        cout << "3 - Voltar ao menu de consultas" << endl;
        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            for (int i = 0; i < qtdAtendimentos; i++)
            {
                if (listaAtendimentos[i].dataAtendimento.mes == dataAtual.mes)
                {
                    countAtendimento++;
                }
            }

            if (countAtendimento == 0)
            {
                cout << "\nNao ha atendimentos registrados no mes atual!\n"
                     << endl;
            }
            else
            {
                Atendimento atendimentosAtuais[countAtendimento];
                countAtendimento = 0;

                for (int i = 0; i < qtdAtendimentos; i++)
                {
                    if (listaAtendimentos[i].dataAtendimento.mes == dataAtual.mes)
                    {
                        atendimentosAtuais[countAtendimento] = listaAtendimentos[i];
                        countAtendimento++;
                    }
                }

                cout << "\nLista de atendimentos do mes atual:\n\n";
                exibirListaAtendimento(atendimentosAtuais, countAtendimento);
            }
            break;
        case 2:
            cout << "\nInforme o mes o qual deseja verificar: ";
            cin >> mes;

            if (mes < 1 || mes > 12)
            {
                cout << "\nMes informado invalido, tente novamente!\n"
                     << endl;
            }
            else
            {
                for (int i = 0; i < qtdAtendimentos; i++)
                {
                    if (listaAtendimentos[i].dataAtendimento.mes == mes)
                    {
                        countAtendimento++;
                    }
                }

                if (countAtendimento == 0)
                {
                    cout << "\nNao ha atendimentos registrados no mes atual!\n"
                         << endl;
                }
                else
                {
                    Atendimento atendimentosAtuais[countAtendimento];
                    countAtendimento = 0;

                    for (int i = 0; i < qtdAtendimentos; i++)
                    {
                        if (listaAtendimentos[i].dataAtendimento.mes == mes)
                        {
                            atendimentosAtuais[countAtendimento] = listaAtendimentos[i];
                            countAtendimento++;
                        }
                    }

                    cout << "\nLista de atendimentos do mes" << mes << "\n\n";
                    exibirListaAtendimento(atendimentosAtuais, countAtendimento);
                }
            }
            break;
        case 3:
            system("cls");
            cout << "Ate a proxima\n\n";
            break;
        default:
            system("cls");
            cout << "Opcao invalida, tente novamente\n\n";
        }
        countAtendimento = 0;
        mes = 0;
    }
}

void estatisticasProfissionais(Date dataAtual,
                               Profissional *listaProfissionais,
                               Atendimento *listaAtendimentos,
                               int qtdProfissionais,
                               int qtdAtendimentos)
{
    int opcao = 0, mes = 0, matricula = 0, countAtendimentos = 0, valid = 0;

    system("cls");

    while (opcao != 4)
    {
        cout << "Selecione uma opcao:" << endl;
        cout << "1 - Verificar a lista de profissionais cadastrados na insituicao" << endl;
        cout << "2 - Verificar as estatisticas de um profissional no mes atual" << endl;
        cout << "3 - Verificar as estatisticas de um profissional em outro mes" << endl;
        cout << "4 - Voltar ao menu das consultas" << endl;
        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            exibirListaProfissionais(listaProfissionais, qtdProfissionais);
            break;
        case 2:
            cout << "\nInforme a matricula do profissional: ";
            cin >> matricula;

            valid = buscarPosicaoProfissional(listaProfissionais, qtdProfissionais, matricula);

            if (valid == -1)
            {
                cout << "\nProfissional nao encontrado nos registros!\n\n";
            }
            else
            {
                for (int i = 0; i < qtdAtendimentos; i++)
                {
                    if (listaAtendimentos[i].matProfissional->matricula == matricula &&
                        listaAtendimentos[i].dataAtendimento.mes == dataAtual.mes)
                    {
                        countAtendimentos++;
                    }
                }

                if (countAtendimentos == 0)
                {
                    cout << "O profissional " << listaProfissionais[valid].nome;
                    cout << " nao possui atendimentos neste mes" << endl;
                }
                else
                {
                    cout << "O profissional " << listaProfissionais[valid].nome;
                    cout << " possui um total de " << countAtendimentos;
                    cout << " atendimentos realizados neste mes" << endl;
                }
            }
            break;
        case 3:
            cout << "\nInforme o mes que deseja verificar: ";
            cin >> mes;

            if (mes < 1 || mes > 12)
            {
                cout << "\nMes informado invalido\n"
                     << endl;
            }
            else
            {
                cout << "\nInforme a matricula do profissional: ";
                cin >> matricula;

                valid = buscarPosicaoProfissional(listaProfissionais, qtdProfissionais, matricula);

                if (valid == -1)
                {
                    cout << "\nProfissional nao encontrado nos registros!\n\n";
                }
                else
                {
                    for (int i = 0; i < qtdAtendimentos; i++)
                    {
                        if (listaAtendimentos[i].matProfissional->matricula == matricula &&
                            listaAtendimentos[i].dataAtendimento.mes == mes)
                        {
                            countAtendimentos++;
                        }
                    }

                    if (countAtendimentos == 0)
                    {
                        cout << "O profissional " << listaProfissionais[valid].nome;
                        cout << " nao possui atendimentos no mes " << mes << "\n\n";
                    }
                    else
                    {
                        cout << "O profissional " << listaProfissionais[valid].nome;
                        cout << " possui um total de " << countAtendimentos;
                        cout << " atendimentos realizados no mes " << mes << "\n\n";
                    }
                }
            }
            break;
        case 4:
            system("cls");
            cout << "Ate a proxima!\n\n";
            break;
        default:
            system("cls");
            cout << "Opcao nao identificada, tente novamente\n\n";
        }
        countAtendimentos = 0;
    }
}

void menuConsultas(Cliente *listaClientes,
                   Profissional *listaProfissionais,
                   Atendimento *listaAtendimentos,
                   Date dataAtual,
                   int qtdClientes,
                   int qtdProfissionais,
                   int qtdAtendimentos)
{
    int menu = 0;
    system("cls");

    while (menu != 6)
    {
        cout << "Bem-vindo ao menu das consultas!" << endl;
        cout << "Por favor, selecione a opcao que deseja consultar:" << endl;
        cout << "1 - Profissionais aniversariantes do mes" << endl;
        cout << "2 - Clientes aniversariantes do mes" << endl;
        cout << "3 - Atendimentos realizados em determinada data" << endl;
        cout << "4 - Atendimentos realizados em determinado mes e ano" << endl;
        cout << "5 - Estatisticas de um Profissional em determinado periodo" << endl;
        cout << "6 - Voltar ao menu principal" << endl;
        cin >> menu;
        cin.ignore();

        switch (menu)
        {
        case 1:
            profissionaisAniversariantes(dataAtual, listaProfissionais, qtdProfissionais);
            break;
        case 2:
            clientesAniversariantes(dataAtual, listaClientes, qtdClientes);
            break;
        case 3:
            atendimentosPorData(dataAtual, listaAtendimentos, qtdAtendimentos);
            break;
        case 4:
            atendimentosPorMes(dataAtual, listaAtendimentos, qtdAtendimentos);
            break;
        case 5:
            estatisticasProfissionais(dataAtual,
                                      listaProfissionais,
                                      listaAtendimentos,
                                      qtdProfissionais,
                                      qtdAtendimentos);
            break;
        case 6:
            system("cls");
            cout << "Ate a proxima!\n\n";
            break;
        default:
            system("cls");
            cout << "Opcao invalida, tente novamente\n\n";
        }
    }
}

int main()
{
    Cliente clientes[MAX_CLIENTES];
    Profissao listaProfissoes[LIMITVET];
    Profissional listaProfissionais[LIMITVET];
    Atendimento listaAtendimentos[MAX_ATENDIMENTO];
    Date dataAtual;

    int incCodigo = 1;
    int incMatricula = 1;
    int qntProfissoes = 0;
    int qntProfissionais = 0;
    int qtdClientes = 0;
    int qtdAtendimentos = 0;

    int opcao = 0;

    // Obtém o tempo atual
    time_t now = time(nullptr);
    // Converte o tempo atual em uma estrutura tm (para manipulação da data)
    tm *data_hora = localtime(&now);

    // Extrai os componentes da data (dia, mês e ano)
    dataAtual.dia = data_hora->tm_mday;
    dataAtual.mes = data_hora->tm_mon + 1;     // Os meses começam em 0, então adicionamos 1
    dataAtual.ano = data_hora->tm_year + 1900; // Ano é o ano atual - 1900

    cout << "Carregando arquivos\n";

    carregarClientes(clientes, &qtdClientes);
    carregarProfissoes(listaProfissoes, &qntProfissoes, &incCodigo);
    carregarProfissionais(listaProfissionais,
                          listaProfissoes,
                          &qntProfissionais,
                          &incMatricula,
                          qntProfissoes);
    carregarAtendimentos(listaAtendimentos,
                         listaProfissionais,
                         clientes,
                         &qtdAtendimentos,
                         qntProfissionais,
                         qtdClientes);

    while (opcao != 6)
    {
        fflush(stdin);

        // cout << dataAtual.dia << "/" << dataAtual.mes << "/" << dataAtual.ano << endl;
        cout << "1 - Menu de clientes" << endl;
        cout << "2 - Menu de profissoes" << endl;
        cout << "3 - Menu de profissionais" << endl;
        cout << "4 - Menu de atendimento" << endl;
        cout << "5 - Menu de consultas" << endl;
        cout << "6 - Sair" << endl;

        cout << "Digite a opcao desejada: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            menuClientes(clientes, &qtdClientes);
            break;
        case 2:
            menuProfissoes(listaProfissoes, &qntProfissoes, &incCodigo);
            break;
        case 3:
            menuProfissional(listaProfissoes,
                             listaProfissionais,
                             &qntProfissoes,
                             &qntProfissionais,
                             &incCodigo,
                             &incMatricula);
            break;
        case 4:
            menuAtendimento(listaAtendimentos,
                            &qtdAtendimentos,
                            clientes,
                            &qtdClientes,
                            listaProfissionais,
                            qntProfissionais);
            break;
        case 5:
            menuConsultas(clientes,
                          listaProfissionais,
                          listaAtendimentos,
                          dataAtual,
                          qtdClientes,
                          qntProfissionais,
                          qtdAtendimentos);
            break;
        case 6:
            cout << "\n\nAte a proxima!\n\n";
            break;
        default:
            system("cls");
            cout << "Opcao invalida, tente novamente!\n\n";
        }
    }
}
