#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Struktur data untuk menampung spesifikasi barang
struct Item {
    int id;
    int value;
    int weight;
    double ratio; // Rasio Keuntungan / Berat
};

// Struktur data untuk Node pada Pohon Ruang Status (State Space Tree)
struct Node {
    int level;    // Indeks level barang yang sedang diproses
    int profit;   // Akumulasi keuntungan saat ini
    int weight;   // Akumulasi berat saat ini
    double bound; // Prediksi batas atas keuntungan maksimal dari cabang ini
};

// Fungsi pembanding untuk mengurutkan barang berdasarkan rasio terbesar ke terkecil
bool compareItems(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Fungsi pembanding untuk Antrean Prioritas (Mendahulukan Node dengan Bound terbesar)
struct CompareNode {
    bool operator()(Node const& n1, Node const& n2) {
        return n1.bound < n2.bound;
    }
};

// Fungsi menghitung Upper Bound (Estimasi keuntungan menggunakan Fractional Knapsack)
double calculateBound(Node u, int n, int capacity, const vector<Item>& items) {
    if (u.weight >= capacity) return 0;

    double profit_bound = u.profit;
    int j = u.level + 1;
    int total_weight = u.weight;

    // Masukkan barang secara utuh selama kapasitas ransel masih muat
    while (j < n && total_weight + items[j].weight <= capacity) {
        total_weight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    // Jika masih ada sisa kapasitas, ambil pecahan nilai dari barang berikutnya
    if (j < n) {
        profit_bound += (capacity - total_weight) * items[j].ratio;
    }

    return profit_bound;
}

int knapsackBranchAndBound(int capacity, vector<Item>& items) {
    int n = items.size();
    
    // Syarat wajib Branch & Bound: Urutkan barang berdasarkan rasio profit/weight secara menurun
    sort(items.begin(), items.end(), compareItems);

    priority_queue<Node, vector<Node>, CompareNode> pq;
    Node u, v;

    // Inisialisasi Node Akar (Root) awal
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = calculateBound(u, n, capacity, items);
    pq.push(u);

    int max_profit = 0;

    while (!pq.empty()) {
        // Ambil Node yang memiliki nilai prediksi keuntungan (bound) tertinggi
        u = pq.top();
        pq.pop();

        // Pangkas cabang (Pruning) jika prediksi nilainya sudah tidak lebih baik dari max_profit saat ini
        if (u.bound <= max_profit) continue;

        // Bergeser ke level barang berikutnya
        v.level = u.level + 1;

        // JALUR KIRI: Keputusan memuat/mengambil barang ke dalam ransel
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        // Jika berat aman dan profitnya memecahkan rekor baru, perbarui max_profit
        if (v.weight <= capacity && v.profit > max_profit) {
            max_profit = v.profit;
        }

        v.bound = calculateBound(v, n, capacity, items);
        // Jika cabangnya masih potensial menghasilkan nilai lebih tinggi, masukkan ke antrean
        if (v.bound > max_profit) {
            pq.push(v);
        }

        // JALUR KANAN: Keputusan TIDAK mengambil barang ke dalam ransel
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v, n, capacity, items);

        if (v.bound > max_profit) {
            pq.push(v);
        }
    }

    return max_profit;
}

int main() {
    // Input Data Sesuai Studi Kasus Toko Perhiasan
    vector<int> values = {10, 10, 12, 18};
    vector<int> weights = {2, 4, 6, 9};
    int capacity = 15;
    int n = values.size();

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;
        items[i].value = values[i];
        items[i].weight = weights[i];
        items[i].ratio = (double)values[i] / weights[i];
    }

    // Menjalankan Fungsi Branch and Bound
    int max_value = knapsackBranchAndBound(capacity, items);

    // Menampilkan Hasil Output
    cout << "===========================================" << endl;
    cout << "       SOLUSI DENGAN BRANCH AND BOUND      " << endl;
    cout << "===========================================" << endl;
    cout << "Keuntungan Maksimal : Rp " << max_value << " Juta" << endl;
    cout << "Catatan: Hasil optimasi ini telah melewati" << endl;
    cout << "proses pemangkasan (pruning) cabang pohon" << endl;
    cout << "keputusan yang tidak efisien." << endl;
    cout << "===========================================" << endl;

    return 0;
}