#include <iostream>
#include <locale>
#include <fstream>  // Para manipulação de arquivos
#include <string>

using namespace std;

/*QUESTÃO 1
Utilizar os algoritmos de ordenação aprendidos para:

1. Exibir um menu com 5 opções, para que o usuário digite de 1 a 4 para os algoritmos (Bubble, Selection, Insertion, Merge Sort), ou a opção 5 para sair.
2. Ler o arquivo “nomes2.txt” em anexo. Nenhum nome possui mais que 100 caracteres.
3. Imprimir os nomes do arquivo ordenados de acordo com o algoritmo selecionado

Dicas:
 Biblioteca “string.h”;
 Usar os ponteiros FILE *arquivo para ler o mesmo;
 Usar as funções fopen para abrir o arquivo em leitura (r+), feof para determinar o fim do arquivo, fgets para ler a linha e fclose para fechar o arquivo*/


void troca(string* linhas, int a, int b){
    string aux = linhas[a];
    linhas[a] = linhas[b];
    linhas[b] = aux;
}

// Complexidade de espaço: O(1)
void bubbleSort(string* linhas, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool houveTroca = false;
        for (int j = 0; j < (n - 1) - i; j++) {
            if (linhas[j] > linhas[j + 1]) {
                troca(linhas, j, j + 1);
                houveTroca = true;
            }
        }
        if (!houveTroca) return;
    }
}

// Espaço O(1) Tempo O(n^2)
void selectionSort(string* linhas, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = i +1; j < n; j++){
            if(linhas[i] > linhas[j]){
                troca(linhas, i, j);
            }
        }
    }
}

// Espaço O(1) tempo O(n^2)
void insertionSort(string* linhas, int n){
    for(int i = 1; i < n; i++){
        string aux = linhas[i];
        int j = i - 1;
        while(j >= 0 && aux < linhas[j]){
            linhas[j+1] = linhas[j];
            j--;
        }
        linhas[j+1] = aux;
    }
}

// Complexidade de tempo e espaço = O(n)
void merge(string* linhas, int s, int m, int e) {
    string tmp[(e - s) + 1];
    int i = s, j = m + 1, k = 0;
    while (i <= m && j <= e) {
        tmp[k++] = (linhas[i] < linhas[j]) ? linhas[i++] : linhas[j++];
    }
    while (i <= m) {
        tmp[k++] = linhas[i++];
    }
    while (j <= e) {
        tmp[k++] = linhas[j++];
    }
    for (i = s, k = 0; i <= e; i++, k++) {
        linhas[i] = tmp[k];
    }
}

// Complexidade de tempo O(n log n) e espaço O(n)
void mergeSort(string* linhas, int s, int e) {
    if (s < e) {
        int m = (s + e) / 2;
        //printf("%d %d %d\n", s, m, e);
        mergeSort(linhas, s, m);
        mergeSort(linhas, m + 1, e);
        merge(linhas, s, m, e);
    }
}


void imprimirVetor(string* linhas, int n) {
    for (int i = 0; i < n; i++) {
       cout << linhas[i] << endl;
    }
}

int main(){
    ifstream arquivo("C:/Users/natsa/OneDrive/Documentos/dados/nomes2.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    const int MAX_LINHAS = 1000;  // Definindo um tamanho máximo
    string* linhas = new string[MAX_LINHAS];  // Alocando um array dinâmico
    string linha;
    int contador = 0;

    // Lê cada linha do arquivo e armazena no array
    while (getline(arquivo, linha) && contador < MAX_LINHAS) {
        linhas[contador] = linha;
        contador++;
    }

    arquivo.close();  // Fecha o arquivo após a leitura

    setlocale(LC_ALL, "");
    int opcao;

    do {
        cout << "-------- Menu ---------\n";
        cout << "Escolha uma opção:\n";
        cout << "1. Algoritmo BubbleSort\n";
        cout << "2. Algoritmo SelectionSort\n";
        cout << "3. Algoritmo InsertionSort\n";
        cout << "4. Algoritmo MergeSort\n";
        cout << "5. Sair\n";
        cin >> opcao;

        switch (opcao) {
            case 1:
                bubbleSort(linhas, contador);
                imprimirVetor(linhas, contador);
                break;
            case 2:
                selectionSort(linhas, contador);
                imprimirVetor(linhas, contador);
                break;
            case 3:
                insertionSort(linhas, contador);
                imprimirVetor(linhas, contador);
                break;
            case 4:
                mergeSort(linhas, 0, contador - 1);
                imprimirVetor(linhas, contador);
                break;
            case 5:
                cout << "Você saiu do programa!\n";
                delete[] linhas;
                break;
            default:
                cout << "Opção invalida!\n";
                break;
        }
    } while (opcao != 5);

    return 0;
}
