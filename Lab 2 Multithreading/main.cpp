#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>

std::mutex g_lock;

void ZeroTheMatrix(int**& matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }
}

void FillMatrices(int**& a, int**& b, int**& result, int n){
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        a[i] = new int[n];
        b[i] = new int[n];
        result[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            a[i][j] = rand() % 15;
            b[i][j] = rand() % 15;
            result[i][j] = 0;
        }
    }
}

void PrintMatrix(int**& matrix, int& n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MultiplyTheRest(int** a, int** b, int**& result, int start, int n){
    for (int i = 0; i < n; i++) {
        for (int j = start; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int j = 0; j < n; j++){
        for(int i = start; i < n; i++){
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int l = start; l < n; l++){
                result[i][j] += a[i][l] * b[l][j];
            }
        }
    }
}
void MultiplyMatrices(int**& a, int**& b, int**& result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void MultiplyBlocks(int** a, int** b, int**& result, int i_, int k_, int j_, int size) {
    for (int i = i_; i < i_ + size; i++) {
        for (int j = j_; j < j_ + size; j++) {
            int current = 0;
            for (int k = 0; k < size; k++) {
                current += a[i][k_ + k] * b[k_ + k][j];
            }
            g_lock.lock();
            result[i][j] += current;
            g_lock.unlock();
        }
    }
}
void MultiplyByBlocks(int**& a, int**& b, int**& result, int& n, int& block_size){
    int rest = n - (n % block_size);
    if (n % block_size != 0){
        std::thread thr(MultiplyTheRest,a,b, std::ref(result), rest, n);
        thr.join();
    }
    std::vector<std::thread> threads;
    for (int i = 0; i < rest; i += block_size){
        for (int j = 0; j < rest; j += block_size) {
            for (int k = 0; k < rest; k += block_size) {
                std::thread thr(MultiplyBlocks, a,b, std::ref(result), i, k, j, block_size);
                threads.push_back(std::move(thr));
            }
        }
    }
    for (auto & thread : threads) {
        thread.join();
    }
}

int main() {
    int n;
    std::cout << "Enter the size of matrices:";
    std::cin >> n;
    int** a = new int*[n];
    int** b = new int*[n];
    int** result = new int*[n];
    FillMatrices(a, b, result, n);
   auto begin = std::chrono::steady_clock::now();
    MultiplyMatrices(a, b,  result, n);
    auto end = std::chrono::steady_clock::now();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

//    PrintMatrix(a,n);
//    std::cout << std::endl;
//    PrintMatrix(b,n);
//    std::cout << std::endl;
//    MultiplyMatrices(a, b, result, n);
//    PrintMatrix(result, n);
    std::cout << "simple multiplication takes: "<< nanoseconds.count() << " nanoseconds" << std::endl;
    std::cout << std::endl;

    for(int i = 1; i <= n; i++){
        ZeroTheMatrix(result, n);
        begin = std::chrono::steady_clock::now();
        MultiplyByBlocks(a,b,result,n,i);
        end = std::chrono::steady_clock::now();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        if (n % i != 0){
//            PrintMatrix(result, n);
            std::cout << i << ": num of threads is " << (n/i)*(n/i) << " (+ 1), it takes " << nanoseconds.count() << " nanoseconds\n";
            std::cout << std::endl;
        }else {
//            PrintMatrix(result, n);
            std::cout << i << ": num of threads is " << (n/i) * (n/i) << ", it takes " << nanoseconds.count() << " nanoseconds\n";
            std::cout << std::endl;
        }
    }
    return 0;
}