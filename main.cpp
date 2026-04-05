#include <iostream>
#include <vector>
#include <algorithm> // next_permutation, sort
#include <chrono>    // medicion de tiempo
using namespace std;

int main() {

    cout << "=== Ejercicio 1: Permutaciones con Restriccion ===\n\n";

    int n;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    vector<int> A(n);
    cout << "Ingrese los " << n << " elementos: ";
    for (int i = 0; i < n; i++) cin >> A[i];

    // MUY IMPORTANTE: ordenar antes de next_permutation
    // para que recorra exactamente las n! permutaciones
    sort(A.begin(), A.end());

    int total_generadas = 0;
    int total_validas   = 0;

    cout << "\n--- Permutaciones validas ---\n";

    // ── inicio del cronometro ──
    auto inicio = chrono::high_resolution_clock::now();

    do {
        total_generadas++;

        bool valida = true;

        // verificar P[i] <= 2 * P[i+1] para cada posicion
        for (int i = 0; i < n - 1; i++) {
            if (A[i] > 2 * A[i + 1]) {
                valida = false;
                break; // ya sabemos que es invalida, no seguimos
            }
        }

        if (valida) {
            for (int x : A) cout << x << " ";
            cout << "\n";
            total_validas++;
        }

    } while (next_permutation(A.begin(), A.end()));

    // ── fin del cronometro ──
    auto fin = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(fin - inicio).count();

    cout << "\nTotal generadas : " << total_generadas << "\n";
    cout << "Total validas   : " << total_validas   << "\n";
    cout << "Tiempo          : " << ms << " ms\n";

    return 0;
}
