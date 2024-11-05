#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/*QUESTÃO 2
Ler o arquivo disponibilizado com os resultados do campeonato mineiro de 2022 - módulo 1, até a 7a rodada.
Calcular e ordenar o placar do campeonato, usando as seguintes regras:
1) O maior número de pontos - vitória vale 3 pontos e empate vale 1 ponto
2) mais vitórias
3) melhor saldo de gols (diferença entre gols pró e gols contra)
4) mais gols pró

Imprimir a tabela do campeonato ordenada, contendo o nome do time, pontos, num. de vitórias, empates e derrotas, saldo de gols, gols pró, gols contra.

Perguntar ao usuário qual método de ordenação usar (Bubble, Selection, Insertion, Merge) e usar esse para ordenação dos valores.*/

// Definição da estrutura para armazenar os dados de cada time
struct Time {
    string nome;
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int saldoGols;
    int golsPro;
    int golsContra;
};

// Função para inicializar um time
void inicializaTime(Time &t, const string &nome) {
    t.nome = nome;
    t.pontos = 0;
    t.vitorias = 0;
    t.empates = 0;
    t.derrotas = 0;
    t.saldoGols = 0;
    t.golsPro = 0;
    t.golsContra = 0;
}

void calculaEstatisticas(Time times[], int indice1, int indice2, int g1, int g2) {
    // Atualiza estatísticas do time 1
    if (g1 > g2) { // Time 1 vence
        times[indice1].pontos += 3;
        times[indice1].vitorias++;
        times[indice2].derrotas++;
    } else if (g1 < g2) { // Time 2 vence
        times[indice2].pontos += 3;
        times[indice2].vitorias++;
        times[indice1].derrotas++;
    } else { // Empate
        times[indice1].pontos++;
        times[indice2].pontos++;
        times[indice1].empates++;
        times[indice2].empates++;
    }

    // Atualiza gols
    times[indice1].golsPro += g1;
    times[indice1].golsContra += g2;
    times[indice2].golsPro += g2;
    times[indice2].golsContra += g1;

    // Atualiza saldo de gols
    times[indice1].saldoGols = times[indice1].golsPro - times[indice1].golsContra;
    times[indice2].saldoGols = times[indice2].golsPro - times[indice2].golsContra;
}

// Função para encontrar o índice de um time
int encontraTime(Time times[], int n, const string &nome) {
    for (int i = 0; i < n; i++) {
        if (times[i].nome == nome) {
            return i;
        }
    }
    return -1; // Time não encontrado
}

void troca(Time times[], int a, int b) {
    if (a == b) return;
    Time aux = times[a];
    times[a] = times[b];
    times[b] = aux;
}

// Complexidade de espaço: O(1)
void bubbleSort(Time times[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool houveTroca = false;
        for (int j = 0; j < (n - 1) - i; j++) {
            if (times[j].pontos < times[j + 1].pontos ||
                (times[j].pontos == times[j + 1].pontos && times[j].vitorias < times[j + 1].vitorias) ||
                (times[j].pontos == times[j + 1].pontos && times[j].vitorias == times[j + 1].vitorias && times[j].saldoGols < times[j + 1].saldoGols) ||
                (times[j].pontos == times[j + 1].pontos && times[j].vitorias == times[j + 1].vitorias && times[j].saldoGols == times[j + 1].saldoGols && times[j].golsPro < times[j + 1].golsPro)) {
                troca(times, j, j + 1);
                houveTroca = true;
            }
        }
        // Se não houve troca, a lista já está ordenada
        if (!houveTroca) {
            break; // Use break em vez de return
        }
    }
}

void selectionSort(Time times[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (times[j].pontos > times[maxIdx].pontos ||
                (times[j].pontos == times[maxIdx].pontos && times[j].vitorias > times[maxIdx].vitorias) ||
                (times[j].pontos == times[maxIdx].pontos && times[j].vitorias == times[maxIdx].vitorias && times[j].saldoGols > times[maxIdx].saldoGols) ||
                (times[j].pontos == times[maxIdx].pontos && times[j].vitorias == times[maxIdx].vitorias && times[j].saldoGols == times[maxIdx].saldoGols && times[j].golsPro > times[maxIdx].golsPro)) {
                maxIdx = j;
            }
        }
        troca(times, i, maxIdx);
    }
}

void insertionSort(Time times[], int n) {
    for (int i = 1; i < n; i++) {
        Time key = times[i];
        int j = i - 1;
        while (j >= 0 && (key.pontos > times[j].pontos ||
            (key.pontos == times[j].pontos && key.vitorias > times[j].vitorias) ||
            (key.pontos == times[j].pontos && key.vitorias == times[j].vitorias && key.saldoGols > times[j].saldoGols) ||
            (key.pontos == times[j].pontos && key.vitorias == times[j].vitorias && key.saldoGols == times[j].saldoGols && key.golsPro > times[j].golsPro))) {
            times[j + 1] = times[j];
            j--;
        }
        times[j + 1] = key;
    }
}

void merge(Time times[], int s, int m, int e) {
    int leftSize = m - s + 1;
    int rightSize = e - m;
    Time* left = new Time[leftSize];
    Time* right = new Time[rightSize];

    for (int i = 0; i < leftSize; i++)
        left[i] = times[s + i];
    for (int j = 0; j < rightSize; j++)
        right[j] = times[m + 1 + j];

    int i = 0, j = 0, k = s;
    while (i < leftSize && j < rightSize) {
        if (left[i].pontos > right[j].pontos ||
            (left[i].pontos == right[j].pontos && left[i].vitorias > right[j].vitorias) ||
            (left[i].pontos == right[j].pontos && left[i].vitorias == right[j].vitorias && left[i].saldoGols > right[j].saldoGols) ||
            (left[i].pontos == right[j].pontos && left[i].vitorias == right[j].vitorias && left[i].saldoGols == right[j].saldoGols && left[i].golsPro > right[j].golsPro)) {
            times[k++] = left[i++];
        } else {
            times[k++] = right[j++];
        }
    }
    while (i < leftSize) {
        times[k++] = left[i++];
    }
    while (j < rightSize) {
        times[k++] = right[j++];
    }
    delete[] left;
    delete[] right;
}

void mergeSort(Time times[], int s, int e) {
    if (s < e) {
        int m = s + (e - s) / 2;
        mergeSort(times, s, m);
        mergeSort(times, m + 1, e);
        merge(times, s, m, e);
    }
}

bool comparaTimes(const Time &a, const Time &b) {
    if (a.pontos != b.pontos) return a.pontos > b.pontos;
    if (a.vitorias != b.vitorias) return a.vitorias > b.vitorias;
    if (a.saldoGols != b.saldoGols) return a.saldoGols > b.saldoGols;
    return a.golsPro > b.golsPro;
}

int partition(Time times[], int s, int e) {
    Time pivot = times[e];
    int i = s - 1;
    for (int j = s; j < e; j++) {
        if (comparaTimes(times[j], pivot)) {
            troca(times, ++i, j);
        }
    }
    troca(times, i + 1, e);
    return i + 1;
}


// O(n log n) caso médio, O(n^2) pior caso
// complexidade de espaço O(1)
void quickSort(Time times[], int s, int e) {
    if (s < e) {
        int p = partition(times, s, e);
        //imprimir(v, 8);
        //printf("%d %d %d\n", s, p, e);
        quickSort(times, s, p - 1);
        quickSort(times, p + 1, e);
    }

}

// Função para imprimir a tabela
void imprimeTabela(Time times[], int n) {
    cout << left << setw(10) << "Time"
         << setw(7) << "Pontos"
         << setw(9) << "Vitórias"
         << setw(8) << "Empates"
         << setw(9) << "Derrotas"
         << setw(12) << "Saldo Gols"
         << setw(9) << "Gols Pró"
         << setw(12) << "Gols Contra" << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << times[i].nome
             << setw(7) << times[i].pontos
             << setw(9) << times[i].vitorias
             << setw(9) << times[i].empates
             << setw(8) << times[i].derrotas
             << setw(12) << times[i].saldoGols
             << setw(9) << times[i].golsPro
             << setw(12) << times[i].golsContra << endl;
    }
}

int main(){
    const int MAX_TIMES = 12; // Defina o número máximo de times
    Time times[MAX_TIMES];
    int n = 0; // Número de times

    // Inicializa os times
    inicializaTime(times[n++], "CAM");
    inicializaTime(times[n++], "CAL");
    inicializaTime(times[n++], "ATH");
    inicializaTime(times[n++], "DGV");
    inicializaTime(times[n++], "AME");
    inicializaTime(times[n++], "CRU");
    inicializaTime(times[n++], "TOM");
    inicializaTime(times[n++], "VNO");
    inicializaTime(times[n++], "URT");
    inicializaTime(times[n++], "POU");
    inicializaTime(times[n++], "CAP");
    inicializaTime(times[n++], "UBE");

    // Ler dados do arquivo
    ifstream arquivo("C:/Users/natsa/OneDrive/Documentos/dados/dados.txt");
    string linha;

    while (getline(arquivo, linha)) {
        string time1 = linha.substr(0, 3);
        string time2 = linha.substr(linha.length() - 3, 3);
        int g1 = stoi(linha.substr(4, 1)); // Ajuste para pegar o número correto de gols
        int g2 = stoi(linha.substr(6, 1)); // Ajuste para pegar o número correto de gols
        int indice1 = encontraTime(times, n, time1);
        int indice2 = encontraTime(times, n, time2);
        if (indice1 != -1 && indice2 != -1) {
            calculaEstatisticas(times, indice1, indice2, g1, g2); // Passa os índices corretos
        }
    }

    setlocale(LC_ALL, "");
    int opcao;

    do {
        cout << "-------- Menu ---------\n";
        cout << "Escolha o método de ordenação:\n";
        cout << "1. Algoritmo BubbleSort\n";
        cout << "2. Algoritmo SelectionSort\n";
        cout << "3. Algoritmo InsertionSort\n";
        cout << "4. Algoritmo MergeSort\n";
        cout << "5. Algoritmo QuickSort\n";
        cout << "6. Sair\n";
        cin >> opcao;

        switch (opcao) {
            case 1:
                bubbleSort(times, n);
                imprimeTabela(times, n);
                break;
            case 2:
                selectionSort(times, n);
                imprimeTabela(times, n);
                break;
            case 3:
                insertionSort(times, n);
                imprimeTabela(times, n);
                break;
            case 4:
                mergeSort(times, 0, n - 1);
                imprimeTabela(times, n);
                break;
            case 5:
                quickSort(times, 0, n - 1);
                imprimeTabela(times, n);
                break;
            case 6:
                cout << "Você saiu do programa!\n";
                break;
            default:
                cout << "Opção invalida!\n";
                break;
        }
    } while (opcao != 6);

    return 0;
}
