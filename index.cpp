#include <iostream>

#define LIMITVET 50

using namespace std;

typedef struct Date {
    int dia;
    int mes;
    int ano;
} Date;

typedef struct Address {
    char rua[LIMITVET];
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
    float cpf;
    char nome[LIMITVET];
    Date dataNascimento;
    int regProfissional;
    char telefone[11];
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

int buscarPosicaoProfissao(Profissao *listaProfissao, int qntProfissoes, int codigoProfissao){

    for(int i = 0; i < qntProfissoes; i++){
        if(listaProfissao[i].codigo == codigoProfissao){
            return i;
        }
    }

    return -1;
}

int buscarPosicaoProfissional(Profissional *listaProfissionais, int qntProfissionais, int numMatricula){
    for(int i = 0; i < qntProfissionais; i++){
        if(listaProfissionais[i].matricula == numMatricula){
            return i;
        }
    }

    return -1;
}

// Métodos da Lista de Profissões

void exibirProfissao(Profissao profissao){
    cout << "\n*******************************************************\n";
    cout << "Codigo: " << profissao.codigo << "\n";
    cout << "Profissao: " << profissao.nome << "\n";
    cout << "Sigla: " << profissao.sigla << "\n";
    cout << "*******************************************************\n\n";
}

void exibirListaProfissoes(Profissao *listaProfissoes, int qntProfissoes){
    for(int i = 0; i < qntProfissoes; i++){
        exibirProfissao(listaProfissoes[i]);
    }
}

void cadastrarNovaProfissao(Profissao *listaProfissoes, int *qntProfissoes){
    int codigo, achou;

    system("cls");
    fflush(stdin);

    cout << "Informe um codigo para a nova profissao que deseja criar: ";
    cin >> codigo;

    achou = buscarPosicaoProfissao(listaProfissoes, *qntProfissoes, codigo);

    if(achou == -1) {
        listaProfissoes[*qntProfissoes].codigo = codigo;

        cin.ignore();
        cout << "Informe o titulo da nova profissao: ";
        gets(listaProfissoes[*qntProfissoes].nome);

        cout << "Informe a sigla do orgao regulador dessa profissao: ";
        gets(listaProfissoes[*qntProfissoes].sigla);

        (*qntProfissoes)++;
        cout << "\nNova profissao cadastrada!\n";
    } else {
        cout << "\nCodigo ja existe nos registros, tente outro!\n";
    }
}

void atualizarProfissao(Profissao *listaProfissoes, int qntProfissoes){
    int codigo, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe o codigo da profissao que deseja atualizar: ";
    cin >> codigo;

    posicao = buscarPosicaoProfissao(listaProfissoes, qntProfissoes, codigo);

    if(posicao == -1){
        cout << "\nProfissao nao encontrada!";
    } else {
        cout << "Informe o codigo atualizado da profissao: ";
        cin >> listaProfissoes[posicao].codigo;

        cin.ignore();

        cout << "Informe o titulo atualizado profissao: ";
        gets(listaProfissoes[posicao].nome);

        cout << "Informe a sigla do orgao regulador dessa profissao: ";
        gets(listaProfissoes[posicao].sigla);

        cout << "\nProfissao atualizada!\n";
    }
}

void deletarProfissao(Profissao *listaProfissoes, int *qntProfissoes){
    int codigo, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe o codigo da profissao que deseja deletar: ";
    cin >> codigo;

    posicao = buscarPosicaoProfissao(listaProfissoes, *qntProfissoes, codigo);

    for(int i = posicao; i < *qntProfissoes; i++) {
        listaProfissoes[i] = listaProfissoes[i+1];
    }

    (*qntProfissoes)--;
    cout << "\n\nProfissao deletada dos registros!\n\n";
}

void menuProfissoes(Profissao *listaProfissoes, int *qntProfissoes){
    int menu = 0;

    system("cls");

    while(menu != 5){
        fflush(stdin);

        cout << "Bem-vindo ao menu das profissoes!\n";
        cout << "Por favor, selecione uma opcao a seguir:\n";
        cout << "1 - Exibir a lista de profissoes cadastradas\n";
        cout << "2 - Cadastrar uma nova profissao\n";
        cout << "3 - Atualizar o registro de alguma profissao\n";
        cout << "4 - Deletar o registro de alguma profissao\n";
        cout << "5 - Voltar ao menu principal\n\n";
        cin >> menu;

        switch (menu) {
            case 1: {
                exibirListaProfissoes(listaProfissoes, *qntProfissoes);
                break;
            }
            case 2: {
                cadastrarNovaProfissao(listaProfissoes, qntProfissoes);
                break;
            }
            case 3: {
                atualizarProfissao(listaProfissoes, *qntProfissoes);
                break;
            }
            case 4: {
                deletarProfissao(listaProfissoes, qntProfissoes);
                break;
            }
            case 5: {
                cout << "\nAte a proxima!\n";
                break;
            }
            default: cout << "\nOpcao nao reconhecida, tente novamente!\n";
        }
    }
}

// Métodos da lista de Profissionais

void exibirProfissional(Profissional profissional){
    cout << "\n*******************************************************\n";
    cout << "Nome: " << profissional.nome << "\n";
    cout << "Matricula: " << profissional.matricula << "\n";
    cout << "CPF: " << profissional.cpf << "\n";

    cout << "Data de Nascimento: " << profissional.dataNascimento.dia << "/";
    cout << profissional.dataNascimento.mes << "/";
    cout << profissional.dataNascimento.ano << "\n";

    cout << "E-mail: " << profissional.email << "\n";
    cout << "Profissao: " << profissional.profissao->nome << "\n";

    cout << "Registro Profissional: " << profissional.regProfissional << " ";
    cout << profissional.profissao->sigla << "\n";

    cout << "Telefone: " << profissional.telefone << "\n";
    cout << "*******************************************************\n\n";
}

void exibirListaProfissionais(Profissional *listaProfissionais, int qntProfissionais) {
    for(int i = 0; i < qntProfissionais; i++){
        exibirProfissional(listaProfissionais[i]);
    }
}

void cadastrarNovoProfissional(Profissao *listaProfissoes,
                               Profissional *listaProfissionais,
                               int *qntProfissoes,
                               int *qntProfissionais) {

    int codigo, profissao;
    char cadastrar;

    system("cls");
    fflush(stdin);

    cout << "Lista de profissoes disponiveis: \n";
    exibirListaProfissoes(listaProfissoes, *qntProfissoes);
    cout << "\nDeseja cadastrar uma nova profissao? (s/n)\n";
    fflush(stdin);
    cin >> cadastrar;

    if(cadastrar == 's'){
        cadastrarNovaProfissao(listaProfissoes, qntProfissoes);
        cout << "\nRetornando ao menu\n\n";
    }
    else if(cadastrar == 'n'){
        cout << "\nPor favor informe a matricula do novo colaborador: \n";
        cin >> listaProfissionais[*qntProfissionais].matricula;
        cin.ignore();
        cout << "Informe o nome do novo colaborador: \n";
        gets(listaProfissionais[*qntProfissionais].nome);

        cout << "Informe o codigo da profissao do novo colaborador: ";
        cin >> codigo;
        profissao = buscarPosicaoProfissao(listaProfissoes, *qntProfissoes, codigo);
        listaProfissionais[*qntProfissionais].profissao = &listaProfissoes[profissao];

        cout << "Informe o cpf do novo colaborador: ";
        cin >> listaProfissionais[*qntProfissionais].cpf;

        cout << "Informe a data de nascimento do novo colaborador: \n";
        cout << "Dia: ";
        cin >> listaProfissionais[*qntProfissionais].dataNascimento.dia;
        cout << "Mes: ";
        cin >> listaProfissionais[*qntProfissionais].dataNascimento.mes;
        cout << "Ano: ";
        cin >> listaProfissionais[*qntProfissionais].dataNascimento.ano;
        cout << "\n";

        cout << "Informe o registro profissional do novo colaborador: ";
        cin >> listaProfissionais[*qntProfissionais].regProfissional;

        cin.ignore();
        cout << "Informe o telefone do novo colaborador: ";
        gets(listaProfissionais[*qntProfissionais].telefone);
        cout << "Informe o e-mail do novo colaborador: ";
        gets(listaProfissionais[*qntProfissionais].email);

        (*qntProfissionais)++;

        cout << "\n\nNovo colaborador cadastrado!\n\n";
    }
    else {
        cout << "\n\nOpcao nao reconhecida, tente novamente!\n\n";
    }
}

void atualizarProfissional(Profissao *listaProfissoes,
                           Profissional *listaProfissionais,
                           int qntProfissoes,
                           int qntProfissionais){

    int matricula, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe a matricula do profissional que deseja atualizar os dados: ";
    cin >> matricula;
    posicao = buscarPosicaoProfissional(listaProfissionais, qntProfissionais, matricula);

    if(posicao == -1){
        cout << "\nMatricula nao encontrada!\n";
    } else {
        int codigo, profissao;

        cout << "\nLista de profissoes disponiveis: \n";
        exibirListaProfissoes(listaProfissoes, qntProfissoes);

        cout << "\nPor favor informe a matricula do novo colaborador: \n";
        cin >> listaProfissionais[posicao].matricula;
        cout << "Informe o nome do novo colaborador: \n";
        gets(listaProfissionais[posicao].nome);

        cout << "Informe o codigo da profissao do novo colaborador: ";
        cin >> codigo;
        profissao = buscarPosicaoProfissao(listaProfissoes, qntProfissoes, codigo);
        listaProfissionais[posicao].profissao = &listaProfissoes[profissao];

        cout << "Informe o cpf do novo colaborador: ";
        cin >> listaProfissionais[posicao].cpf;

        cout << "Informe a data de nascimento do novo colaborador: \n";
        cout << "Dia: ";
        cin >> listaProfissionais[posicao].dataNascimento.dia;
        cout << "Mes: ";
        cin >> listaProfissionais[posicao].dataNascimento.mes;
        cout << "Ano: ";
        cin >> listaProfissionais[posicao].dataNascimento.ano;
        cout << "\n";

        cout << "Informe o telefone do novo colaborador: ";
        cin >> listaProfissionais[posicao].telefone;
        cout << "Informe o e-mail do novo colaborador: ";
        gets(listaProfissionais[posicao].email);

        cout << "\nCadastro atualizado!\n";
    }
}

void deletarProfissional(Profissional *listaProfissionais, int *qntProfissionais){

    int matricula, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe a matricula do profissional que deseja deletar: ";
    cin >> matricula;

    posicao = buscarPosicaoProfissional(listaProfissionais, *qntProfissionais, matricula);

    if(posicao == -1){
        cout << "\n\nMatricula nao encontrada!\n\n";
    } else {
        for(int i = posicao; i < *qntProfissionais; i++) {
            listaProfissionais[i] = listaProfissionais[i+1];
        }
    }

    (*qntProfissionais)--;
    cout << "\n\nProfissional deletado dos registros!\n\n";
}

void menuProfissional(Profissao *listaProfissao,
                      Profissional *listaProfissionais,
                      int *qntProfissoes,
                      int *qntProfissionais){

    int menu = 0;

    system("cls");

    while (menu != 5) {
        fflush(stdin);
        cout << "Bem-vindo ao menu dos profissionais!\n";
        cout << "Por favor, selecione uma opcao a seguir:\n";
        cout << "1 - Exibir a lista de profissionais cadastrados\n";
        cout << "2 - Cadastrar um novo profissional\n";
        cout << "3 - Atualizar o registro de algum profissional\n";
        cout << "4 - Deletar o registro de algum profissional\n";
        cout << "5 - Voltar ao menu principal\n\n";
        cin >> menu;

        switch (menu) {
            case 1: {
                exibirListaProfissionais(listaProfissionais, *qntProfissionais);
                break;
            }
            case 2: {
                cadastrarNovoProfissional(listaProfissao, listaProfissionais, qntProfissoes, qntProfissionais);
                break;
            }
            case 3: {
                atualizarProfissional(listaProfissao, listaProfissionais, *qntProfissoes, *qntProfissionais);
                break;
            }
            case 4: {
                deletarProfissional(listaProfissionais, qntProfissionais);
                break;
            }
            case 5: {
                cout << "\nAta a proxima!\n";
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
    int menu = 0;

    while(menu != 10){
        fflush(stdin);
        cout << "Bem-vindo ao sistema do hospital **********\n";
        cout << "Selecione uma das opcoes no menu abaixo:\n";
        cout << "1 - Acessar os registros de profissoes\n";
        cout << "2 - Acessar os registros de profissionais\n\n";
        cin >> menu;

        switch (menu) {
            case 1: {
                menuProfissoes(listaProfissao, &qntProfissioes);
                break;
            }
            case 2: {
                menuProfissional(listaProfissao,
                                 listaProfissionais,
                                 &qntProfissioes,
                                 &qntProfissionais);
                break;
            }
            case 10: {
                cout << "\nAte a proxima!\n";
                break;
            }
            default: cout << "\nOpcao nao identificada, tente novamente!\n";
        }
    }

    cin.get();
    return 0;
}