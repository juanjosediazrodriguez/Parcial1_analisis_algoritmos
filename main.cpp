#include <iostream>
#include <vector>
#include <algorithm> // para usar next_permutation
using namespace std;

int main() {

    int n;
    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    // vector donde guardamos los numeros
    vector<int> A(n);

    cout << "Ingrese los elementos: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    // MUY IMPORTANTE:
    // ordenar el arreglo para que next_permutation funcione bien
    sort(A.begin(), A.end());

    int total_generadas = 0; // cuenta todas las permutaciones
    int total_validas = 0;   // cuenta las que cumplen la condicion

    // do-while para recorrer TODAS las permutaciones
    do {
        total_generadas++;

        bool valida = true; // asumimos que es valida al inicio

        // revisamos la condicion del problema
        // P[i] <= 2 * P[i+1]
        for (int i = 0; i < n - 1; i++) {
            if (A[i] > 2 * A[i + 1]) {
                valida = false; // ya no cumple
                break; // no tiene sentido seguir revisando
            }
        }

        // si la permutacion es valida, la imprimimos
        if (valida) {
            for (int x : A) {
                cout << x << " ";
            }
            cout << endl;

            total_validas++;
        }

    } while (next_permutation(A.begin(), A.end())); 
    // genera la siguiente permutacion automaticamente

    // resultados finales
    cout << "\nTotal generadas: " << total_generadas << endl;
    cout << "Total validas: " << total_validas << endl;

    return 0;
}