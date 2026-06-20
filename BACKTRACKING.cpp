#include <iostream>
#include <vector>

using namespace std;

// Variabel global untuk menyimpan solusi keuntungan tertinggi dan kombinasi terbaik
int max_value = 0;
vector<int> best_combination;

// Fungsi rekursif Backtracking
void knapsackBacktracking(const vector<int>& weights, const vector<int>& values, int capacity, 
                          int n, int index, int current_weight, int current_value, vector<int>& current_choices) {
    
    // Base Case: Jika semua barang sudah dipertimbangkan (mencapai ujung percabangan)
    if (index == n) {
        // Jika keuntungan saat ini lebih besar dari yang pernah dicatat, perbarui nilai terbaik
        if (current_value > max_value) {
            max_value = current_value;
            best_combination = current_choices;
        }
        return;
    }

    // Opsi 1: AMBIL barang saat ini (jika kapasitas ransel masih muat)
    if (current_weight + weights[index] <= capacity) {
        current_choices[index] = 1; // Tandai barang diambil
        knapsackBacktracking(weights, values, capacity, n, index + 1, 
                             current_weight + weights[index], 
                             current_value + values[index], current_choices);
    }

    // Opsi 2: JANGAN AMBIL barang saat ini (Proses Backtrack)
    current_choices[index] = 0; // Tandai barang tidak diambil
    knapsackBacktracking(weights, values, capacity, n, index + 1, 
                         current_weight, current_value, current_choices);
}

int main() {
    // Input Data Sesuai Studi Kasus Toko Perhiasan
    vector<int> values = {10, 10, 12, 18}; // Keuntungan (dalam Juta Rp)
    vector<int> weights = {2, 4, 6, 9};    // Berat barang (dalam kg)
    int capacity = 15;                     // Kapasitas maksimal ransel (kg)
    int n = values.size();

    vector<int> current_choices(n, 0);
    best_combination.resize(n, 0);

    // Menjalankan Fungsi Backtracking dimulai dari indeks barang ke-0
    knapsackBacktracking(weights, values, capacity, n, 0, 0, 0, current_choices);

    // Menampilkan Hasil Output
    cout << "===========================================" << endl;
    cout << "       SOLUSI DENGAN BACKTRACKING          " << endl;
    cout << "===========================================" << endl;
    cout << "Keuntungan Maksimal : Rp " << max_value << " Juta" << endl;
    cout << "Kombinasi Barang     : " << endl;
    
    int total_berat = 0;
    for (int i = 0; i < n; i++) {
        if (best_combination[i] == 1) {
            cout << "- Barang " << (i + 1) << " (Berat: " << weights[i] << " kg, Profit: Rp " << values[i] << " Juta)" << endl;
            total_berat += weights[i];
        }
    }
    cout << "Total Berat Ransel  : " << total_berat << " kg" << endl;
    cout << "===========================================" << endl;

    return 0;
}