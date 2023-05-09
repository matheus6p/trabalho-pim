#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Endereco {
  char rua[100];
  char numero[10];
  char bairro[50];
  char cidade[50];
  char estado[3];
  char cep[9];
};

struct Comorbidade {
  int diabetes;
  int obesidade;
  int hipertensao;
  int tuberculose;
  char outros[50];
};

struct Paciente {
  char nome[50];
  char cpf[11];
  char telefone[11];
  char email[50];
  char data_nascimento[11];
  char data_diagnostico[11];
  struct Endereco endereco;
  struct Comorbidade comorbidade;
};

void listar_pacientes() {
  FILE *fp;
  char linha[100];

  fp = fopen("paciente.txt", "r");

  while (fgets(linha, 100, fp) != NULL) {
      printf("%s", linha);
  }

  fclose(fp);
}

void menu() {
  int opcao;
    while(1) {
      printf("Selecione uma opcao:\n");
      printf("1-Cadastrar Paciente\n");
      printf("2-Listar Pacientes\n");
      printf("3-Sair\n");
      scanf("%d", &opcao);
      fflush(stdin);

      switch(opcao) {
        case 1:
          system("cls");
          cadastrar_paciente();
          fflush(stdin);
          break;
        case 2:
          listar_pacientes();
          fflush(stdin);
          break;
        case 3:
          printf("Saindo do programa...");
          exit(0);
        default:
          printf("Opcao invalida, tente novamente!\n");
          break;
      }
    }
}

void login() {
  char usuario[20], senha[20];

  printf("Digite o usuario: ");
  fgets(usuario, 20, stdin);
  strtok(usuario, "\n");

  printf("Digite a senha: ");
  fgets(senha, 20, stdin);
  strtok(senha, "\n");

  if(strcmp(usuario, "medicina unip") == 0 && strcmp(senha, "unip") == 0) {
    printf("Login realizado com sucesso!\n");
    system("cls");
    menu();
  } else {
    printf("Usuario ou senha incorretos!\n");
  }
}

int calcular_idade(char data_nascimento[]) {
  int dia, mes, ano;
  sscanf(data_nascimento, "%d/%d/%d", &dia, &mes, &ano);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int anoAtual = tm.tm_year + 1900;
  int mesAtual = tm.tm_mon + 1;
  int diaAtual = tm.tm_mday;

  int idade = anoAtual - ano;
  if(mesAtual < mes || (mesAtual == mes && diaAtual < dia)) {
    idade--;
  }
  return idade;
}

int pertence_grupo_risco(int idade, int diabetes, int obesidade, int hipertensao, int tuberculose, char outros ) {
  if(idade >= 65 || diabetes || obesidade || hipertensao || tuberculose) {
    return 1;
  } else {
    return 0;
  }
}

void salvar_paciente(struct Paciente *paciente, char *arquivo) {
  FILE *fp = fopen(arquivo, "a");

  if(fp == NULL) {
    printf("Erro ao abrir o arquivo %s\n");
    return;
  }

  fprintf(fp, "Nome completo: %s", paciente->nome);
  fprintf(fp, "CPF: %s\n", paciente->cpf);
  fprintf(fp, "Telefone: %s\n", paciente->telefone);
  fprintf(fp, "Rua: %s\n", paciente->endereco.rua);
  fprintf(fp, "Numero: %s", paciente->endereco.numero);
  fprintf(fp, "Bairro: %s", paciente->endereco.bairro);
  fprintf(fp, "Cidade: %s", paciente->endereco.cidade);
  fprintf(fp, "Estado: %s\n", paciente->endereco.estado);
  fprintf(fp, "CEP: %s", paciente->endereco.cep);
  fprintf(fp, "Data de nascimento: %s\n", paciente->data_nascimento);
  fprintf(fp, "Data do diagnostico: %s\n", paciente->data_diagnostico);
  fprintf(fp, "Comorbidades:\n");
  fprintf(fp, "  Diabetes: %d\n", paciente->comorbidade.diabetes);
  fprintf(fp, "  Obesidade: %d\n", paciente->comorbidade.obesidade);
  fprintf(fp, "  Hipertensão: %d\n", paciente->comorbidade.hipertensao);
  fprintf(fp, "  Tuberculose: %d\n", paciente->comorbidade.tuberculose);
  fprintf(fp, "  Outros: %s", paciente->comorbidade.outros);
  fprintf(fp, "-----------------------------------------\n");

  fclose(fp);
  printf("Paciente cadastrado com sucesso!\n");
}

void cadastrar_paciente() {
  struct Paciente novoPaciente;
  printf("CADASTRO DE PACIENTE\n");

  printf("Nome completo: ");
  fgets(novoPaciente.nome, 100, stdin);
  getchar();
  fflush(stdin);

  printf("CPF: ");
  fgets(novoPaciente.cpf, 11, stdin);
  getchar();
  fflush(stdin);

  printf("Telefone: ");
  fgets(novoPaciente.telefone, 11, stdin);
  getchar();
  fflush(stdin);

  printf("Rua: ");
  fgets(novoPaciente.endereco.rua, 100, stdin);
  getchar();

  printf("Numero: ");
  fgets(novoPaciente.endereco.numero, 10, stdin);
  getchar();

  printf("Bairro: ");
  fgets(novoPaciente.endereco.bairro, 50, stdin);
  getchar();

  printf("Cidade: ");
  fgets(novoPaciente.endereco.cidade, 50, stdin);
  getchar();

  printf("Estado: ");
  fgets(novoPaciente.endereco.estado, 3, stdin);
  getchar();

  printf("CEP: ");
  fgets(novoPaciente.endereco.cep, 10, stdin);
  getchar();

  printf("Data de nascimento (DD/MM/AAAA): ");
  fgets(novoPaciente.data_nascimento, 11, stdin);
  getchar();
  fflush(stdin);

  printf("Data do diagnostico (DD/MM/AAAA): ");
  fgets(novoPaciente.data_diagnostico, 11, stdin);
  getchar();
  fflush(stdin);

  int idade = calcular_idade(novoPaciente.data_nascimento);

  printf("Comorbidade (0 - Nao / 1 - Sim):\n");
  printf("1. Diabetes\n");
  scanf("%i", &novoPaciente.comorbidade.diabetes);
  fflush(stdin);

  printf("2. Obesidade\n");
  scanf("%i", &novoPaciente.comorbidade.obesidade);
  fflush(stdin);

  printf("3. Hipertensao\n");
  scanf("%i", &novoPaciente.comorbidade.hipertensao);
  fflush(stdin);

  printf("4. Tuberculose\n");
  scanf("%i", &novoPaciente.comorbidade.tuberculose);
  fflush(stdin);

  printf("5. Outros\n");
  fgets(novoPaciente.comorbidade.outros, 50, stdin);
  getchar();

  salvar_paciente(&novoPaciente, "pacientes.txt");
}

int main() {
  int opcao;

  while(1) {
    printf("Selecione uma opcao:\n");
    printf("1-Login\n");
    printf("2-Sair\n");
    scanf("%d", &opcao);
    fflush(stdin);

    switch(opcao) {
      case 1:
        login();
        fflush(stdin);
        break;
      case 2:
        printf("Saindo do programa...\n");
        exit(0);
      default:
        printf("Opcao invalida, tente novamente. \n");
        break;
    }
  }

  return 0;
}
