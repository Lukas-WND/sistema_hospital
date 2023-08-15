#include <iostream>

#define LIMITVET 50

using namespace std;

typedef struct Date {
    int dia;
    int mes;
    int ano;
} Date;

typedef struct Address {
    char *rua;
    int numero;
    char bairro[LIMITVET];
    char cidade[LIMITVET];
    char estado[LIMITVET];
    int cep;
} Address;

typedef struct Profissao {
    int codigo; // Primary Key
    char nome[LIMITVET];
    char sigla[5];
} Profissao;

typedef struct Profissional {
    int matricula; // Primary Key
    Profissao *profissao; // Foreing Key
    int cpf;
    char nome[LIMITVET];
    Date dataNascimento;
    int regProfissional;
    int telefone;
    char email[50];
} Profissional;

typedef struct Cliente {
    int matricula; // Primary Key
    int cpf;
    char nome[LIMITVET];
    Date dataNascimento;
    int idade;
    char email[LIMITVET];
    int telefone;
    Address endereco;
} Cliente;

typedef struct Atendimento {
    int numeroAtendimento; // Primary Key
    Profissional *matProfissional; // Foreing Key
    Cliente *codCliente; // Foreing Key
    Date dataAtendimento;
    char descricao[100];
} Atendimento;

Profissao* buscarProfissao(Profissao *listaProfissao, int codigoProfissao){
    Profissao *atual = listaProfissao;

    for(int i = 0; i < LIMITVET; i++){
        if(atual->codigo == codigoProfissao){
            return atual;
        }
        else {
            atual++;
        }
    }

    return NULL;
}

Profissional* buscarProfissional(Profissional *listaProfissionais, int numMatricula){
    Profissional *atual = listaProfissionais;

    for(int i = 0; i < LIMITVET; i++){
        if(atual->matricula == numMatricula){
            return atual;
        }
        else {
            atual++;
        }
    }

    return NULL;
}

// Métodos da Lista de Profissões

void exibirListaProfissoes(Profissao *listaProfissoes, int *qntProfissoes);
void cadastrarNovaProfissao();
void atualizarProfissao();
void deletarProfissao();

// Métodos da lista de Profissionais

void exibirListaProfissionais(Profissional *listaProfissionais, int *qntProfissionais) {
    Profissional *atual = listaProfissionais;

    system("cls");

    for(int i = 0; i < *qntProfissionais; i++){
        cout << "\n*******************************************************\n";
        cout << "Nome: " << atual->nome << "\n";
        cout << "Matricula: " << atual->matricula << "\n";
        cout << "CPF: " << atual->cpf << "\n";

        cout << "Data de Nascimento: " << atual->dataNascimento.dia << "/";
        cout << atual->dataNascimento.mes << "/";
        cout << atual->dataNascimento.ano << "\n";

        cout << "E-mail: " << atual->email << "\n";
        cout << "Profissao: " << atual->profissao->nome << "\n";

        cout << "Registro Profissional: " << atual->regProfissional << " ";
        cout << atual->profissao->sigla << "\n";

        cout << "Telefone: " << atual->telefone << "\n";
        cout << "*******************************************************\n";

        atual++;
    }
}

void cadastrarNovoProfissional(Profissao *listaProfissao,
                               Profissional *listaProfissional,
                               int *qntProfissoes,
                               int *qntProfissionais) {

    Profissional *novoProfissional = listaProfissional;
    Profissao *profissao;
    int codigo;

    system("cls");
    fflush(stdin);

    for(int i = 0; i < *qntProfissionais; i++){
        novoProfissional++;
    }

    cout << "Lista de profissoes disponiveis: \n";
    exibirListaProfissoes(listaProfissao, qntProfissoes);

    cout << "\nPor favor informe a matricula do novo colaborador: \n";
    cin >> novoProfissional->matricula;
    cout << "Informe o nome do novo colaborador: \n";
    gets(novoProfissional->nome);

    cout << "Informe o codigo da profissao do novo colaborador: ";
    cin >> codigo;
    profissao = buscarProfissao(listaProfissao, codigo);
    novoProfissional->profissao = profissao;

    cout << "Informe o cpf do novo colaborador: ";
    cin >> novoProfissional->cpf;

    cout << "Informe a data de nascimento do novo colaborador: \n";
    cout << "Dia: ";
    cin >> novoProfissional->dataNascimento.dia;
    cout << "Mes: ";
    cin >> novoProfissional->dataNascimento.mes;
    cout << "Ano: ";
    cin >> novoProfissional->dataNascimento.ano;
    cout << "\n";

    cout << "Informe o telefone do novo colaborador: ";
    cin >> novoProfissional->telefone;
    cout << "Informe o e-mail do novo colaborador: ";
    gets(novoProfissional->email);

    *qntProfissionais++;
    cout << "\nNovo colaborador cadastrado!\n";
}

void atualizarProfissional(Profissao *listaProfissao,
                           Profissional *listaProfissionais,
                           int *qntProfissoes,
                           int *qntProfissionais){

    Profissional *profissionalEncontrado;
    Profissao *profissao;
    int matricula, codigo;

    system("cls");
    fflush(stdin);

    cout << "Informe a matricula do profissional que deseja atualizar os dados: ";
    cin >> matricula;
    profissionalEncontrado = buscarProfissional(listaProfissionais, matricula);

    if(profissionalEncontrado == NULL){
        cout << "\nMatricula nao encontrada!\n";
    } else {
        cout << "\nLista de profissoes disponiveis: \n";
        exibirListaProfissoes(listaProfissao, qntProfissoes);

        cout << "\nPor favor informe a matricula do novo colaborador: \n";
        cin >> profissionalEncontrado->matricula;
        cout << "Informe o nome do novo colaborador: \n";
        gets(profissionalEncontrado->nome);

        cout << "Informe o codigo da profissao do novo colaborador: ";
        cin >> codigo;
        profissao = buscarProfissao(listaProfissao, codigo);
        profissionalEncontrado->profissao = profissao;

        cout << "Informe o cpf do novo colaborador: ";
        cin >> profissionalEncontrado->cpf;

        cout << "Informe a data de nascimento do novo colaborador: \n";
        cout << "Dia: ";
        cin >> profissionalEncontrado->dataNascimento.dia;
        cout << "Mes: ";
        cin >> profissionalEncontrado->dataNascimento.mes;
        cout << "Ano: ";
        cin >> profissionalEncontrado->dataNascimento.ano;
        cout << "\n";

        cout << "Informe o telefone do novo colaborador: ";
        cin >> profissionalEncontrado->telefone;
        cout << "Informe o e-mail do novo colaborador: ";
        gets(profissionalEncontrado->email);

        cout << "\nNovo colaborador cadastrado!\n";
    }
}

void deletarProfissional(Profissional *listaProfissionais, int *qntProfissionais){

    Profissional *profissionalEncontrado, *proxProfissional, *ultProfissional;
    int matricula;

    system("cls");
    fflush(stdin);

    cout << "Informe a matricula do profissional que deseja deletar do registro: ";
    cin >> matricula;

    profissionalEncontrado = buscarProfissional(listaProfissionais, matricula);
    proxProfissional = profissionalEncontrado++;
    ultProfissional = listaProfissionais;
    for(int i = 0; i < *qntProfissionais; i++){
        ultProfissional++;
    }

    while(profissionalEncontrado != ultProfissional){
        profissionalEncontrado = proxProfissional;
        proxProfissional++;
    }

    *qntProfissionais--;
    cout << "\nProfissional deletado!\n";
}

void menuProfissional(Profissao *listaProfissao,
                      Profissional *listaProfissionais,
                      int *qntProfissoes,
                      int *qntProfissionais){

    int menu = 0, matricula;

    system("cls");

    while (menu != 5) {
        fflush(stdin);
        cout << "Bem-vindo ao menu dos profissionais!\n";
        cout << "Por favor, selecione uma opcao a seguir:\n";
        cout << "1 - Exibir a lista de profissionais cadastrados\n";
        cout << "2 - Cadastrar um novo profissional\n";
        cout << "3 - Atualizar o registro de algum profissional\n";
        cout << "4 - Deletar o registro de algum profissional\n";
        cout << "5 - Voltar ao menu principal\n;";
        cin >> menu;

        switch (menu) {
            case 1: {
                exibirListaProfissionais(listaProfissionais, qntProfissionais);
                break;
            }
            case 2: {
                cadastrarNovoProfissional(listaProfissao, listaProfissionais, qntProfissoes, qntProfissionais);
                break;
            }
            case 3: {
                atualizarProfissional(listaProfissao, listaProfissionais, qntProfissoes, qntProfissionais);
                break;
            }
            case 4: {
                deletarProfissional(listaProfissionais, qntProfissionais);
                break;
            }
            case 5: {
                cout << "\nAté a próxima!\n";
                break;
            }
            default: cout << "\nOpcao nao reconhecida, tente novamente!\n";
        }
    }
}

int main(){
    Profissao listaProfissao[LIMITVET];
    Profissional listaProfissionais[LIMITVET];
    int qntProfissioes = 0, qntProfissionais = 0;
    
    menuProfissional(&listaProfissao[0],
                     &listaProfissionais[0],
                     &qntProfissioes,
                     &qntProfissionais);

    system("pause");
    return 0;
}