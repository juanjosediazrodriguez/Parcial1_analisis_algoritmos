/*
 * Ejercicio 1 - Permutaciones con Restricciones (Fuerza Bruta)
 *
 * Dado un conjunto de n elementos distintos, genero todas las permutaciones
 * posibles usando next_permutation y filtro las que cumplen la condicion:
 *   P[i] <= 2 * P[i+1]  para todo i en {0, 1, ..., n-2}
 *
 * Clasifico este enfoque como Fuerza Bruta porque genero y evaluo
 * absolutamente todas las n! permutaciones sin descartar ninguna
 * a mitad de construccion (no hay poda).
 *
 * Complejidad temporal: O(n! * n)
 * Complejidad espacial: O(n)
 */

#include <iostream>
#include <vector>
#include <algorithm> // next_permutation, sort
#include <chrono>    // medicion de tiempo de ejecucion
using namespace std;

int main() {

    cout << "=== Ejercicio 1: Permutaciones con Restriccion ===\n\n";

    // ── leer entrada ──────────────────────────────────────
    int n;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    vector<int> A(n);
    cout << "Ingrese los " << n << " elementos (distintos): ";
    for (int i = 0; i < n; i++) cin >> A[i];

    // ── ordenar el arreglo ────────────────────────────────
    // Esto es obligatorio antes de usar next_permutation.
    // La funcion recorre permutaciones en orden lexicografico
    // ascendente, entonces necesita partir del arreglo en su
    // estado minimo (de menor a mayor). Si no ordeno, no se
    // generarian todas las n! permutaciones.
    sort(A.begin(), A.end());

    int total_generadas = 0; // debe llegar exactamente a n!
    int total_validas   = 0; // solo las que cumplen la restriccion

    cout << "\n--- Permutaciones validas ---\n";

    // ── inicio del cronometro ─────────────────────────────
    // Uso high_resolution_clock porque es el reloj mas preciso
    // que ofrece C++. Lo inicio justo antes del algoritmo para
    // medir solo el tiempo de procesamiento, no el de entrada.
    auto inicio = chrono::high_resolution_clock::now();

    // ── bucle principal: recorre todas las permutaciones ──
    // Uso do-while para que la primera permutacion (el arreglo
    // ordenado) tambien sea evaluada antes de llamar a
    // next_permutation por primera vez.
    do {
        total_generadas++;

        // ── verificar la restriccion P[i] <= 2 * P[i+1] ──
        // Recorro cada par consecutivo. Si alguno la viola,
        // marco la permutacion como invalida y salgo del for
        // con break para no hacer comparaciones innecesarias.
        bool valida = true;
        for (int i = 0; i < n - 1; i++) {
            if (A[i] > 2 * A[i + 1]) {
                valida = false;
                break;
            }
        }

        // si paso todas las comparaciones, la imprimo
        if (valida) {
            for (int x : A) cout << x << " ";
            cout << "\n";
            total_validas++;
        }

    // next_permutation reorganiza A en la siguiente permutacion
    // en orden lexicografico y devuelve true. Cuando ya no hay
    // mas permutaciones (llegamos a la mayor), devuelve false
    // y el bucle termina. En total itera exactamente n! veces.
    } while (next_permutation(A.begin(), A.end()));

    // ── fin del cronometro ────────────────────────────────
    auto fin = chrono::high_resolution_clock::now();
    // convierto la diferencia de tiempo a milisegundos
    double ms = chrono::duration<double, milli>(fin - inicio).count();

    // ── resultados finales ────────────────────────────────
    cout << "\nTotal generadas : " << total_generadas << "\n";
    cout << "Total validas   : " << total_validas   << "\n";
    cout << "Tiempo          : " << ms << " ms\n";

    return 0;
}
