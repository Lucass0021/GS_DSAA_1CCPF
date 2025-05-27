#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#define RAIO_MAXIMO_KM 10.0

struct relato {
  char nome[100]; // Nome do Registrante do Relato
  char cpf[12]; // CPF do Registrante
  char Data[11]; // Ex: 26/05/2025
  char Hora[6]; // Ex: 18:39
  char tipo[30]; // Ex: "Terremoto", "Enchente", etc..
  char descricao[200]; // Relato textual do ocorrido
  float x; // coordenada X para verificação de raio de 10km
  float y; // coordenada Y para verificação de raio de 10km
};

int validarCPF(const char *cpf) { // Validando se o usuário inseriu corretamente os 11 dígitos do CPF
  if (strlen(cpf) != 11) return 0;
  for (int i = 0; i < 11; i++) {
    if (cpf[i] < '0' || cpf[i] > '9') return 0;
  }
  return 1;
}

float calcularDistancia(float x1, float y1, float x2, float y2) {
  return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
} // Fórmula de distância Euclidiana, pegamos os valores X e Y inseridos pelo usuário, para calcular a distância do relato com a base central, para garantir que esteja dentro dos 10km.

int validarDataAtual(const char *data) {
  // data no formato dd/mm/aaaa
  int dia, mes, ano;
  if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) {
    return 0; // formato inválido
  }

  time_t t = time(NULL);
  struct tm *tm_atual = localtime(&t); // garantindo que a data inserida condiza com a data atual

  int dia_atual = tm_atual->tm_mday;
  int mes_atual = tm_atual->tm_mon + 1;  // tm_mon começa em 0
  int ano_atual = tm_atual->tm_year + 1900;

  if (dia == dia_atual && mes == mes_atual && ano == ano_atual) {
    return 1;
  } else {
    return 0;
  }
}

int compararDatas(const char *data1, const char *data2) {
  int d1, m1, a1, d2, m2, a2;
  sscanf(data1, "%d/%d/%d", &d1, &m1, &a1);
  sscanf(data2, "%d/%d/%d", &d2, &m2, &a2);

  if (a1 != a2) return a2 - a1; // Ano mais recente primeiro
  if (m1 != m2) return m2 - m1; // Mês mais recente
  return d2 - d1; // Dia mais recente
}

// Função para ordenar os relatos pela data (mais recentes primeiro)
void ordenarRelatosPorData(struct relato *relatos, int quantidade) {
  for (int i = 0; i < quantidade - 1; i++) {
    for (int j = 0; j < quantidade - i - 1; j++) {
      if (compararDatas(relatos[j].Data, relatos[j + 1].Data) > 0) {
        struct relato temp = relatos[j];
        relatos[j] = relatos[j + 1];
        relatos[j + 1] = temp;
      }
    }
  }
}

int cadastrarRelato(struct relato *d) {
  printf("Nome: ");
  scanf(" %[^\n]", d->nome);

  do {
    printf("CPF (somente numeros): ");
    scanf(" %[^\n]", d->cpf);
    if (!validarCPF(d->cpf)) {
      printf("CPF invalido! Tente novamente.\n");
    }
  } while (!validarCPF(d->cpf));

  // Validação da data com data atual
  do {
    printf("Data (dd/mm/aaaa) - deve ser a data atual: ");
    scanf(" %[^\n]", d->Data);
    if (!validarDataAtual(d->Data)) {
      printf("Data invalida ou diferente da data atual! Tente novamente.\n");
    }
  } while (!validarDataAtual(d->Data));

  printf("Hora (ex: 19:04): ");
  scanf(" %[^\n]", d->Hora);

  printf("Tipo (ex: Terremoto, enchente, etc.): ");
  scanf(" %[^\n]", d->tipo);

  printf("Descricao do Ocorrido: ");
  scanf(" %[^\n]", d->descricao);

  printf("Informe a coordenada X do local do ocorrido: ");
  scanf("%f", &d->x);

  printf("Informe a coordenada Y do local do ocorrido: ");
  scanf("%f", &d->y);

  float distancia = calcularDistancia(0, 0, d->x, d->y);

  if (distancia <= RAIO_MAXIMO_KM) { // Programa compara a distancia calculada em relação à coordenada (0,0) e exibe uma mensagem de acordo com o valor.
    printf("\nA localizacao do seu relato esta a %.2f km da nossa Base Central.\n", distancia);
    printf("Seu relato foi registrado com sucesso! Logo nossas equipes estarao tomando as devidas providencias.\n");
    return 1;
  } else {
    printf("\nA localizacao do seu relato esta a %.2f km da nossa Base Central.\n", distancia);
    printf("Infelizmente sua localizacao ultrapassa nosso raio de operacoes de %.1f km.\n", RAIO_MAXIMO_KM);
    printf("Seu relato nao foi registrado. Por favor, busque outra central.\n");
    return 0;
  }
}

void exibirRelato(struct relato d) {
  printf("\n--- Relato ---\n");
  printf("Nome: %s\n", d.nome);
  printf("CPF: %s\n", d.cpf);
  printf("Data: %s\n", d.Data);
  printf("Hora: %s\n", d.Hora);
  printf("Tipo: %s\n", d.tipo);
  printf("Descricao: %s\n", d.descricao);
  printf("Localizacao (X: %.2f, Y: %.2f)\n", d.x, d.y);
}

void salvarRelatoIndividual(struct relato d, const char *arquivo) {
  FILE *fp = fopen(arquivo, "a"); // Abre em modo append
  if (!fp) {
    printf("Erro ao salvar o relato.\n");
    return;
  }
  fprintf(fp, "%s;%s;%s;%s;%s;%s;%.2f;%.2f\n",
    d.nome, d.cpf, d.Data, d.Hora,
    d.tipo, d.descricao, d.x, d.y);
  fclose(fp);
}

int carregarRelatos(struct relato **lista, const char *arquivo) {
  FILE *fp = fopen(arquivo, "r");
  if (!fp) return 0;

  struct relato temp;
  int qtd = 0;
  struct relato *buffer = NULL;

  while (fscanf(fp, " %99[^;];%11[^;];%10[^;];%5[^;];%29[^;];%199[^;];%f;%f\n",
                temp.nome, temp.cpf, temp.Data, temp.Hora, temp.tipo,
                temp.descricao, &temp.x, &temp.y) == 8) {
    buffer = realloc(buffer, (qtd + 1) * sizeof(struct relato));
    buffer[qtd++] = temp;
  }

  fclose(fp);
  *lista = buffer;
  return qtd;
}

int main() {
  setlocale(LC_ALL, "");

  struct relato *relatos = NULL;
  int quantidade = carregarRelatos(&relatos, "relato.txt");
  int opcao;

  do {
    printf("\n=== SISTEMA DE CADASTRO DE CATASTROFES NATURAIS ===\n");
    printf("1 - Listar relatos\n");
    printf("2 - Cadastrar novo relato\n");
    printf("3 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      if (quantidade == 0) {
        printf("Nenhum relato cadastrado.\n");
      } else {
        ordenarRelatosPorData(relatos, quantidade); // Ordena antes de exibir
        for (int i = 0; i < quantidade; i++) {
          exibirRelato(relatos[i]);
        }
      }
    } else if (opcao == 2) {
      struct relato novo;
      int aceito = cadastrarRelato(&novo);
      if (aceito) {
        struct relato *temp = realloc(relatos, (quantidade + 1) * sizeof(struct relato));
        if (!temp) {
          printf("Erro ao alocar memoria.\n");
          free(relatos);
          return 1;
        }
        relatos = temp;
        relatos[quantidade] = novo;
        salvarRelatoIndividual(novo, "relato.txt");
        quantidade++;
      }
    } else if (opcao == 3) {
      printf("Saindo do sistema...\n");
    } else {
      printf("Opcao invalida.\n");
    }

  } while (opcao != 3);

  free(relatos);
  return 0;
}
