#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define MAX_CLIENTES 10
#define MAX_ATENDIMENTO 10

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
    int matricula; // Primary Key
    char cpf[15];
    char nome[50];
    Date dataNascimento;
    int idade;
    char email[50];
    char telefone[15];
    Address endereco;
} Cliente;

typedef struct Atendimento
{
    int numeroAtendimento;         // Primary Key
    Profissional *matProfissional; // Foreing Key
    Cliente *codCliente;           // Foreing Key
    Date dataAtendimento;
    char *descricao;
} Atendimento;

// metodos cliente inicio
int buscarPosicaoCliente(Cliente *clientes, int qtdClientes, char *cpf);
void cadastrarCliente(Cliente *clientes, int *qtdClientes);
void exibirCliente(Cliente cliente);
void exibirListaClientes(Cliente clientes, int qtdClientes);
void atualizarCliente(Cliente *clientes, int qtdClientes);
void excluirCliente(Cliente *clientes, int *qtdClientes);
void menuClientes(Cliente *clientes, int *qtdClientes);

int buscarPosicaoCliente(Cliente *clientes, int qtdClientes, char *matricula)
{
    for (int i = 0; i < qtdClientes; i++)
    {
        if (clientes[i].matricula == *matricula)
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

void menuClientes(Cliente *clientes, int *qtdClientes)
{
    int opcao = 0;
    int posicao = -1;
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

// Métodos da Lista de Profissões

void exibirProfissao(Profissao profissao)
{ // Exibe o conteúdo de uma única struct dentro do vetor das Profissões
    cout << "\n*******************************************************\n";
    cout << "Codigo: " << profissao.codigo << "\n";
    cout << "Profissao: " << profissao.nome << "\n";
    cout << "Sigla: " << profissao.sigla << "\n";
    cout << "*******************************************************\n\n";
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
    cout << "\nNova profissao cadastrada!\n\n";
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
        cout << "\nProfissao nao encontrada!";
    }
    else
    {
        cout << "Informe o titulo atualizado profissao: ";
        cin.ignore(); // Limpeza do buffer
        cin.getline(listaProfissoes[posicao].nome, LIMITVET);

        cout << "Informe a sigla do orgao regulador dessa profissao: ";
        cin.getline(listaProfissoes[posicao].sigla, 5);

        cout << "\nProfissao atualizada!\n\n";
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
        cout << "\nCodigo nao encontrado!\n";
    }
    else
    {
        // A partir da posição encontrada, o método irá sobescrever a posição atual pelo valor da posição seguinte
        for (int i = posicao; i < *qntProfissoes; i++)
        {
            listaProfissoes[i] = listaProfissoes[i + 1];
        }

        (*qntProfissoes)--; // A quantidade de registros existentes no vetor Profissoes é decrementada
        cout << "\n\nProfissao deletada dos registros!\n\n";
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
        {
            exibirListaProfissoes(listaProfissoes, *qntProfissoes);
            break;
        }
        case 2:
        {
            cadastrarNovaProfissao(listaProfissoes, qntProfissoes, incCodigo);
            break;
        }
        case 3:
        {
            atualizarProfissao(listaProfissoes, *qntProfissoes);
            break;
        }
        case 4:
        {
            deletarProfissao(listaProfissoes, qntProfissoes);
            break;
        }
        case 5:
        {
            cout << "\nAte a proxima!\n";
            break;
        }
        default:
            cout << "\nOpcao nao reconhecida, tente novamente!\n";
        }
    }
}

// Métodos da lista de Profissionais

// Exibe o conteúdo de um único registro da lista de Profissionais
void exibirProfissional(Profissional profissional)
{
    cout << "\n*******************************************************\n";
    cout << "Matricula: " << profissional.matricula << "\n";
    cout << "Nome: " << profissional.nome << "\n";

    cout << "Profissao: " << profissional.profissao->nome << "\n";
    cout << "Registro Profissional: " << profissional.regProfissional << " ";
    cout << profissional.profissao->sigla << "\n";

    cout << "CPF: " << profissional.cpf << "\n";
    cout << "E-mail: " << profissional.email << "\n";
    cout << "Telefone: " << profissional.telefone << "\n";

    cout << "Data de Nascimento: " << profissional.dataNascimento.dia << "/";
    cout << profissional.dataNascimento.mes << "/";
    cout << profissional.dataNascimento.ano << "\n";
    cout << "*******************************************************\n\n";
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
                listaProfissionais[*qntProfissionais].dataNascimento.mes <= 11)
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

        cout << "\n\nNovo colaborador cadastrado!\n\n";
    }
    else
    {
        cout << "\n\nOpcao nao reconhecida, tente novamente!\n\n";
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
        cout << "\nMatricula nao encontrada!\n";
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

        cout << "\nCadastro atualizado!\n\n";
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
    cout << "\n\nProfissional deletado dos registros!\n\n";
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
        {
            exibirListaProfissionais(listaProfissionais, *qntProfissionais);
            break;
        }
        case 2:
        {
            cadastrarNovoProfissional(listaProfissao,
                                      listaProfissionais,
                                      qntProfissoes,
                                      qntProfissionais,
                                      incCodigo,
                                      incMatricula);
            break;
        }
        case 3:
        {
            atualizarProfissional(listaProfissao, listaProfissionais, *qntProfissoes, *qntProfissionais);
            break;
        }
        case 4:
        {
            deletarProfissional(listaProfissionais, qntProfissionais);
            break;
        }
        case 5:
        {
            cout << "\nAta a proxima!\n\n";
            break;
        }
        default:
            cout << "\nOpcao nao reconhecida, tente novamente!\n\n";
        }
    }
}

// Começo dos métodos "Atendimento"

void menuAtendimento(Atendimento *listaAtendimentos, int *qtdAtendimentos, Cliente *clientes, int *qtdClientes,
                     Profissional *listaProfissionais, int qntProfissionais);
void cadastrarAtendimento(Atendimento *listaAtendimento, int *qtdAtendimentos, Cliente *clientes, int *qtdClientes,
                          Profissional *listaProfissionais, int qntProfissionais);

void cadastrarAtendimento(Atendimento *listaAtendimento, int *qtdAtendimentos, Cliente *clientes, int *qtdClientes,
                          Profissional *listaProfissionais, int qntProfissionais)
{
    char cpf[15];
    int opcao1 = 0, w1 = 0, w2 = 0, matriculaP, numeroD;
    system("cls");
    if (*qtdAtendimentos < MAX_ATENDIMENTO)
    {
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
                cout << "    lISTA DE CLINTES   \n";
                cout << "-----------------------\n\n";
                exibirListaClientes(clientes, *qtdClientes);
                cout << "\n";
                cout << "Informe o CPF do cliente: ";
                cin.getline(cpf, sizeof(cpf));
                int posicaoC = buscarPosicaoCliente(clientes, *qtdClientes, cpf);
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
            listaAtendimento[*qtdAtendimentos].codCliente = &clientes[*qtdClientes];
            break;
        }
        system("cls");
        while (w2 != 1)
        {
            cout << "Escolha um profissional para o atendimento: \n\n";
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

        cout << "Gerando registro de Atendimento";
        listaAtendimento.numeroAtendimento = *qtdAtendimentos;
        cout << "Cadastro do Atendimento finalizado";
    }
    else
    {
        cout << "Maximo de Atendimentos cadastrados\n";
    }
}

void menuAtendimento(Atendimento *listaAtendimentos, int *qtdAtendimentos, Cliente *clientes, int *qtdClientes,
                     Profissional *listaProfissionais, int qntProfissionais)
{
    int opcaomenu = 0;
    system("cls");

    while (opcaomenu != 6)
    {
        fflush(stdin);
        cout << "Bem vindo ao Menu Atendimento \n";
        cout << "Selecione alguma das opcoes a seguir: \n";
        cout << "1 - Cadastro de Atendimento \n";
        cout << "2 - Atualizar Atendimento \n";
        cout << "3 - Exibir Atendimentos \n";
        cout << "4 - Busca de Atendimento \n";
        cout << "5 - Excluir Atendimento \n";
        cout << "6 - Voltar ao Menu principal \n";
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
            // Método atualizarAtendimento
            break;
        case 3:
            // Método exibirAtendimento
            break;
        case 4:
            // Método buscaAtendimento
            break;
        case 5:
            // Metodo excluirAtendimento
            break;
        case 6:
            break;
        default:
            cout << "Opcao Invalida\n";
        }
    }
}

// Fim dos metodos de Atendimento

int main()
{
    Cliente clientes[MAX_CLIENTES];
    Profissao listaProfissoes[LIMITVET];
    Profissional listaProfissionais[LIMITVET];
    Atendimento listaAtendimentos[MAX_ATENDIMENTO];
    int incCodigo = 1;
    int incMatricula = 1;
    int qntProfissoes = 0;
    int qntProfissionais = 0;

    int qtdClientes = 0;
    int qtdAtendimentos = 0;

    int opcao = 0;

    while (opcao != 5)
    {
        system("cls");
        fflush(stdin);

        cout << "1 - Menu de clientes" << endl;
        cout << "2 - Menu de profissões" << endl;
        cout << "3 - Menu de profissionais" << endl;
        cout << "4 - Menu de atendimento" << endl;
        cout << "5 - Sair" << endl;

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
        }
        system("pause");
    }
}
