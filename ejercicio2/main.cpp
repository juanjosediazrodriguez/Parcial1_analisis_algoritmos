
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>  // para pow en fuerza bruta
using namespace std;

//  variables globales 
int n, k;
vector<vector<int>> ady;     // matriz de adyacencia del grafo
vector<int> color;           // color asignado a cada vertice (0 = sin color)
int total_bt;                // contador de soluciones del backtracking
bool primera_guardada;       // flag para guardar solo la primera solucion
vector<int> primera_solucion; // guarda la primera coloracion valida encontrada


// FUNCION: esSeguros
// Verifica si puedo asignar el color c al vertice v sin conflicto.
// Recorro todos los vecinos de v y si alguno ya tiene el color c,
// no es seguro asignarlo.

bool esSeguros(int v, int c) {
    for (int u = 0; u < n; u++) {
        // si u es vecino de v Y ya tiene el color c → conflicto
        if (ady[v][u] == 1 && color[u] == c) {
            return false;
        }
    }
    return true;
}


// FUNCION: backtracking
// Intenta colorear los vertices uno a uno desde el vertice v.
// Si llega a v == n significa que coloreamos todos los vertices
// exitosamente -> contamos esa solucion.
// Si no, probamos cada color del 1 al k. Si el color es seguro,
// lo asignamos y llamamos recursivamente al siguiente vertice.
// Despues deshacemos la asignacion (backtrack) para probar el
// siguiente color.
void backtracking(int v) {

    // caso base: ya coloreamos todos los n vertices
    if (v == n) {
        total_bt++;
        // guardamos la primera solucion encontrada
        if (!primera_guardada) {
            primera_solucion = color;
            primera_guardada = true;
        }
        return;
    }

    // probamos cada color disponible para el vertice v
    for (int c = 1; c <= k; c++) {
        if (esSeguros(v, c)) {
            color[v] = c;          // asignamos el color
            backtracking(v + 1);   // intentamos colorear el siguiente vertice
            color[v] = 0;          // BACKTRACK: deshacemos para probar otro color
        }
        // si el color no es seguro, simplemente lo saltamos (PODA)
        // esto evita explorar todas las combinaciones de los vertices
        // restantes cuando ya sabemos que hay un conflicto
    }
}


// FUNCION: fuerzaBruta
// Prueba las k^n combinaciones posibles de colores.
// Representa cada combinacion como un numero en base k:
//   combinacion 0   [1,1,1,...,1]
//   combinacion 1   [1,1,1,...,2]
//   ...
//   combinacion k^n-1  [k,k,k,...,k]
// Para cada combinacion verifica todas las aristas del grafo.
int fuerzaBruta() {
    int total_fb = 0;
    long long combinaciones = (long long)pow(k, n);

    for (long long mask = 0; mask < combinaciones; mask++) {

        // convertir el numero 'mask' a una asignacion de colores en base k
        // ejemplo con k=3, n=3:
        //   mask=0   colores = [1,1,1]
        //   mask=1   colores = [1,1,2]
        //   mask=5   colores = [1,3,3]
        vector<int> cols(n);
        long long temp = mask;
        for (int i = 0; i < n; i++) {
            cols[i] = (temp % k) + 1; // colores van de 1 a k
            temp /= k;
        }

        // verificar que ningun par de vertices adyacentes tenga el mismo color
        bool valida = true;
        for (int u = 0; u < n && valida; u++) {
            for (int v = u + 1; v < n && valida; v++) {
                if (ady[u][v] == 1 && cols[u] == cols[v]) {
                    valida = false; // conflicto encontrado
                }
            }
        }

        if (valida) total_fb++;
    }

    return total_fb;
}



// FUNCION: leerGrafo
// Lee la matriz de adyacencia desde consola
void leerGrafo() {
    while (true) {
        cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";
        cout << "  (solo se permiten 0 o 1. La diagonal debe ser 0. La matriz debe ser simetrica)\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val;
                while (true) {
                    cin >> val;
                    if (val == 0 || val == 1) {
                        ady[i][j] = val;
                        break;
                    }
                    cout << "Valor invalido en [" << i << "][" << j << "]. Solo se permite 0 o 1: ";
                }
            }
        }

        // validar diagonal = 0
        bool diag_ok = true;
        for (int i = 0; i < n; i++) {
            if (ady[i][i] != 0) { diag_ok = false; break; }
        }
        if (!diag_ok) {
            cout << "\nError: la diagonal debe ser 0 (un vertice no se conecta consigo mismo). Reingrese.\n\n";
            continue;
        }

        // validar simetria: ady[i][j] == ady[j][i]
        bool simetrica = true;
        for (int i = 0; i < n && simetrica; i++)
            for (int j = 0; j < n && simetrica; j++)
                if (ady[i][j] != ady[j][i]) simetrica = false;

        if (!simetrica) {
            cout << "\nError: la matriz no es simetrica (si [i][j]=1 entonces [j][i] debe ser 1). Reingrese.\n\n";
            continue;
        }

        break; // matriz valida
    }
}


// 
// FUNCION: ejecutarYMedir
// Corre backtracking y fuerza bruta sobre el grafo actual,
// muestra resultados y tiempos de ambos enfoques.
//
void ejecutarYMedir() {

    //  reiniciar estado 
    color.assign(n, 0);
    total_bt = 0;
    primera_guardada = false;
    primera_solucion.clear();

    //  BACKTRACKING 
    cout << "\nBacktracking \n";
    auto ini_bt = chrono::high_resolution_clock::now();
    backtracking(0);
    auto fin_bt = chrono::high_resolution_clock::now();
    double ms_bt = chrono::duration<double, milli>(fin_bt - ini_bt).count();

    if (total_bt == 0) {
        cout << "No existe una " << k << "-coloracion valida\n";
    } else {
        cout << "Total de " << k << "-coloraciones: " << total_bt << "\n";
        cout << "Primera solucion:\n";
        for (int v = 0; v < n; v++)
            cout << "  color[" << v << "] = " << primera_solucion[v] << "\n";
    }
    cout << "Tiempo Backtracking : " << ms_bt << " ms\n";

    //  FUERZA BRUTA 
    cout << "\n Fuerza Bruta \n";
    auto ini_fb = chrono::high_resolution_clock::now();
    int total_fb = fuerzaBruta();
    auto fin_fb = chrono::high_resolution_clock::now();
    double ms_fb = chrono::duration<double, milli>(fin_fb - ini_fb).count();

    cout << "Fuerza Bruta confirma: " << total_fb << "\n";
    cout << "Tiempo Fuerza Bruta : " << ms_fb << " ms\n";

    // verificar que ambos coincidan
    if (total_bt == total_fb)
        cout << "\nAmbos enfoques coinciden. \n";
    else
        cout << "\nDIFERENCIA DETECTADA entre enfoques.\n";
}


int main() {

    cout << " Ejercicio 2: Coloracion de Grafos con k Colores\n\n";

    cout << "Ingrese n (numero de vertices): ";
    cin >> n;
    cout << "Ingrese k (numero de colores): ";
    cin >> k;

    // inicializar matriz de adyacencia y arreglo de colores
    ady.assign(n, vector<int>(n, 0));
    color.assign(n, 0);

    leerGrafo();

    ejecutarYMedir();

    return 0;
}
