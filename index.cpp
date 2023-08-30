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
    char sigla[7];
} Profissao;

typedef struct Profissional {
    int matricula; // Primary Key
    Profissao *profissao; // Foreing Key
    char cpf[12];
    char nome[LIMITVET];
    Date dataNascimento;
    char regProfissional[7];
    char telefone[12];
    char email[LIMITVET];
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

// Método que percorre o vetor e retorna o índice que contém o valor passado pelo parâmetro codProfissao
int buscarPosicaoProfissao(Profissao *listaProfissao, int qntProfissoes, int codigoProfissao){

    for(int i = 0; i < qntProfissoes; i++){
        // Verirfica se o valor passado por parâmetro corresponde ao valor da variável na posição i do vetor
        if(listaProfissao[i].codigo == codigoProfissao){
            return i; // Retorna i caso seja verdadeiro
        }
    }

    /*Se o vetor inteiro for percorrido e a condição não for satisfeita,
     * então o valor passado pelo parâmetro não está contido no vetor*/
    return -1;
}

// Método que percorre o vetor e retorna o índice que contém o valor passado pelo parâmetro numMatricula
int buscarPosicaoProfissional(Profissional *listaProfissionais, int qntProfissionais, int numMatricula){
    // Verirfica se o valor passado por parâmetro corresponde ao valor da variável na posição i do vetor
    for(int i = 0; i < qntProfissionais; i++){
        if(listaProfissionais[i].matricula == numMatricula){
            return i;
        }
    }

    /* Se o vetor inteiro for percorrido e a condição não for satisfeita,
     * então o valor passado pelo parâmetro não está contido no vetor*/
    return -1;
}

// Métodos da Lista de Profissões

void exibirProfissao(Profissao profissao){ // Exibe o conteúdo de uma única struct dentro do vetor das Profissões
    cout << "\n*******************************************************\n";
    cout << "Codigo: " << profissao.codigo << "\n";
    cout << "Profissao: " << profissao.nome << "\n";
    cout << "Sigla: " << profissao.sigla << "\n";
    cout << "*******************************************************\n\n";
}

// Método Read do CRUD das Profissões, exibe o conteúdo de todas as posições do vetor
void exibirListaProfissoes(Profissao *listaProfissoes, int qntProfissoes){
    for(int i = 0; i < qntProfissoes; i++){
        exibirProfissao(listaProfissoes[i]);
    }
}

// Método Create do CRUD das Profissões, insere novos dados da primeira posição vazia do vetor
void cadastrarNovaProfissao(Profissao *listaProfissoes, int *qntProfissoes, int *incCodigo){
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
void atualizarProfissao(Profissao *listaProfissoes, int qntProfissoes){
    int codigo, posicao;
    system("cls");

    cout << "Informe o codigo da profissao que deseja atualizar: ";
    cin >> codigo;

    posicao = buscarPosicaoProfissao(listaProfissoes, qntProfissoes, codigo);

    // Verifica se a função não retornou um valor válido de posição
    if(posicao == -1){ 
        cout << "\nProfissao nao encontrada!";
    } else {
        cout << "Informe o titulo atualizado profissao: ";
        cin.ignore(); // Limpeza do buffer
        cin.getline(listaProfissoes[posicao].nome, LIMITVET);

        cout << "Informe a sigla do orgao regulador dessa profissao: ";
        cin.getline(listaProfissoes[posicao].sigla, 5);

        cout << "\nProfissao atualizada!\n\n";
    }
}

// Método Delete do CRUD das Profissões, encontra uma posição especificada e subscreve os dados pelos da posição seguinte
void deletarProfissao(Profissao *listaProfissoes, int *qntProfissoes){
    int codigo, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe o codigo da profissao que deseja deletar: ";
    cin >> codigo;

    posicao = buscarPosicaoProfissao(listaProfissoes, *qntProfissoes, codigo);

    // Verifica se o método encontrou uma posição válida
    if(posicao == -1){
        cout << "\nCodigo nao encontrado!\n";
    } else {
        // A partir da posição encontrada, o método irá sobescrever a posição atual pelo valor da posição seguinte
        for(int i = posicao; i < *qntProfissoes; i++) {
            listaProfissoes[i] = listaProfissoes[i+1];
        }

        (*qntProfissoes)--; // A quantidade de registros existentes no vetor Profissoes é decrementada
        cout << "\n\nProfissao deletada dos registros!\n\n";
    }
}

// Menu secundário, correspondente ao CRUD das Profissões
void menuProfissoes(Profissao *listaProfissoes, int *qntProfissoes, int *incCodigo){
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
                cadastrarNovaProfissao(listaProfissoes, qntProfissoes, incCodigo);
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

// Exibe o conteúdo de um único registro da lista de Profissionais
void exibirProfissional(Profissional profissional){
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
void exibirListaProfissionais(Profissional *listaProfissionais, int qntProfissionais) {
    for(int i = 0; i < qntProfissionais; i++){
        exibirProfissional(listaProfissionais[i]);
    }
}

// Método Create do CRUD dos Profissionais
void cadastrarNovoProfissional(Profissao *listaProfissoes,
                               Profissional *listaProfissionais,
                               int *qntProfissoes,
                               int *qntProfissionais,
                               int *incCodigo,
                               int *incMatricula) {

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

    if(cadastrar == 's'){ // Verifica se o usuário deseja cadastrar uma nova profissão
        cadastrarNovaProfissao(listaProfissoes, qntProfissoes, incCodigo); // Chama o método de cadastro
        cout << "\nRetornando ao menu\n\n";
    }
    else if(cadastrar == 'n') {
        // A matrícula do Profissional é gerada a partir do ano atual somado a uma variável de incremento
        listaProfissionais[*qntProfissionais].matricula = (2023 * 1000) + *incMatricula;

        cout << "Informe o nome do novo colaborador: ";
        cin.getline(listaProfissionais[*qntProfissionais].nome, LIMITVET);

        // Loop não encerra até o usuário informar um código de profissão válido
        while(profissao < 0){
            cout << "Informe o codigo da profissao do novo colaborador: ";
            cin >> codigo;
            cin.ignore();
            profissao = buscarPosicaoProfissao(listaProfissoes, *qntProfissoes, codigo);
            if(profissao == -1){
                cout << "\nCodigo nao encontrado, tente novamente\n\n";
            } else {
                // O endereço de memória da profissão correspondente ao código é atribuído ao ponteiro profissao
                listaProfissionais[*qntProfissionais].profissao = &listaProfissoes[profissao];
            }
        }

        cout << "Informe o cpf do novo colaborador: ";
        cin.getline(listaProfissionais[*qntProfissionais].cpf, 12);

        cout << "Informe a data de nascimento do novo colaborador \n";

        // Sequencia de loops que validam a entrada dos dados de tipo Data
        while(valid == 0){
            cout << "Dia: ";
            cin >> listaProfissionais[*qntProfissionais].dataNascimento.dia;
            cin.ignore();

            if(listaProfissionais[*qntProfissionais].dataNascimento.dia > 0 &&
            listaProfissionais[*qntProfissionais].dataNascimento.dia <= 31){
                valid = 1;
            } else {
                cout << "\nDia informado invalido, tente novamente!\n";
            }
        }

        while(valid == 1){
            cout << "Mes: ";
            cin >> listaProfissionais[*qntProfissionais].dataNascimento.mes;
            cin.ignore();

            if(listaProfissionais[*qntProfissionais].dataNascimento.mes > 0 &&
            listaProfissionais[*qntProfissionais].dataNascimento.mes <= 11){
                valid = 2;
            }
            else {
                cout << "\nMes informado invalido, tente novamente!\n";
            }
        }

        while(valid == 2){
            cout << "Ano: ";
            cin >> listaProfissionais[*qntProfissionais].dataNascimento.ano;
            cin.ignore();

            if(listaProfissionais[*qntProfissionais].dataNascimento.ano > (2023-120) &&
            listaProfissionais[*qntProfissionais].dataNascimento.ano <= (2023-18)){
                valid = 3;
            }
            else {
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

        (*incMatricula)++; // Incrementa a variável de gerar novas matrículas
        (*qntProfissionais)++; // Incrementa a quantidade de registros armazenados dentro do vetor

        cout << "\n\nNovo colaborador cadastrado!\n\n";
    }
    else {
        cout << "\n\nOpcao nao reconhecida, tente novamente!\n\n";
    }
}

// Método Update do CRUD dos Profissionais
void atualizarProfissional(Profissao *listaProfissoes,
                           Profissional *listaProfissionais,
                           int qntProfissoes,
                           int qntProfissionais){

    int matricula, posicao, valid = 0;

    system("cls");

    cout << "Informe a matricula do profissional que deseja atualizar os dados: ";
    cin >> matricula;
    cin.ignore();
    posicao = buscarPosicaoProfissional(listaProfissionais, qntProfissionais, matricula);

    // Verifica se o método encontrou uma posição válida correspondente à matrícula digitada
    if(posicao == -1){
        cout << "\nMatricula nao encontrada!\n";
    } else {
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

        while(valid == 0){
            cout << "Dia: ";
            cin >> listaProfissionais[posicao].dataNascimento.dia;
            cin.ignore();

            if(listaProfissionais[posicao].dataNascimento.dia > 0 &&
               listaProfissionais[posicao].dataNascimento.dia <= 31){
                valid = 1;
            } else {
                cout << "\nDia informado invalido, tente novamente!\n";
            }
        }

        while(valid == 1){
            cout << "Mes: ";
            cin >> listaProfissionais[posicao].dataNascimento.mes;
            cin.ignore();

            if(listaProfissionais[posicao].dataNascimento.mes > 0 &&
               listaProfissionais[posicao].dataNascimento.mes <= 11){
                valid = 2;
            }
            else {
                cout << "\nMes informado invalido, tente novamente!\n";
            }
        }

        while(valid == 2){
            cout << "Ano: ";
            cin >> listaProfissionais[posicao].dataNascimento.ano;
            cin.ignore();

            if(listaProfissionais[posicao].dataNascimento.ano > (2023-120) &&
               listaProfissionais[posicao].dataNascimento.ano <= (2023-18)){
                valid = 3;
            }
            else {
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
void deletarProfissional(Profissional *listaProfissionais, int *qntProfissionais){

    int matricula, posicao;

    system("cls");
    fflush(stdin);

    cout << "Informe a matricula do profissional que deseja deletar: ";
    cin >> matricula;

    posicao = buscarPosicaoProfissional(listaProfissionais, *qntProfissionais, matricula);

    // Verifica se o método de busca encontrou uma posição válida
    if(posicao == -1){
        cout << "\n\nMatricula nao encontrada!\n\n";
    } else {
        // A partir da posição encontrada, o método sobrescreve o valor da posição atual pelo da próxima posição do vetor
        for(int i = posicao; i < *qntProfissionais; i++) {
            listaProfissionais[i] = listaProfissionais[i+1];
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
                      int *incMatricula){

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
                cadastrarNovoProfissional(listaProfissao,
                                          listaProfissionais,
                                          qntProfissoes,
                                          qntProfissionais,
                                          incCodigo,
                                          incMatricula);
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
                cout << "\nAta a proxima!\n\n";
                break;
            }
            default: cout << "\nOpcao nao reconhecida, tente novamente!\n\n";
        }
    }
}

int main(){
    Profissao listaProfissao[LIMITVET];
    Profissional listaProfissionais[LIMITVET];
    int qntProfissioes = 0, qntProfissionais = 0;
    int  incCodigo = 1, incMatricula = 1;
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
                menuProfissoes(listaProfissao, &qntProfissioes, &incCodigo);
                break;
            }
            case 2: {
                menuProfissional(listaProfissao,
                                 listaProfissionais,
                                 &qntProfissioes,
                                 &qntProfissionais,
                                 &incCodigo,
                                 &incMatricula);
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
