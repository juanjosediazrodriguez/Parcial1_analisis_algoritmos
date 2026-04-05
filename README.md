# Proyecto 1 - Analisis y Diseño de Algoritmos

**Universidad EAFIT — Analisis y Diseño de Algoritmos**
Primer Trabajo Practico: Fuerza Bruta y Backtracking en C++

---

## Integrantes

| Nombre | Rol |
|--------|-----|
| Samuel Calderón |Analisis de complejidad e informe escrito de los dos ejercicios |
| Juan José Diaz |Implementacion en C++ y pruebas de los dos ejercicios|

---

## Requisitos

| Requisito | Version minima |
|-----------|---------------|
| Compilador C++ | g++ 11 o superior |
| Estandar | C++17 |
| Sistema operativo | Windows, Linux o macOS |

Para verificar que tienes g++ instalado:
```bash
g++ --version
```

---

## Compilacion y ejecucion

Clonar el repositorio:
```bash
git clone <url-del-repositorio>
cd Parcial1_analisis_algoritmos
```

Compilar cada ejercicio:
```bash
# Ejercicio 1
g++ -O2 -std=gnu++17 -o programa_1 ejercicio1/main.cpp
./programa_1

# Ejercicio 2
g++ -O2 -std=gnu++17 -o programa_2 ejercicio2/main.cpp
./programa_2
```

---

## Estructura del proyecto

```
Parcial1_analisis_algoritmos/
├── ejercicio1/
│   ├── main.cpp             # Implementacion Fuerza Bruta (permutaciones)
│   └── pseudocodigo.txt     # Pseudocodigo del algoritmo
├── ejercicio2/
│   ├── main.cpp             # Implementacion Backtracking + Fuerza Bruta (coloracion)
│   └── pseudocodigo.txt     # Pseudocodigo de ambos enfoques
├── .gitignore               # Archivos excluidos del repositorio
└── README.md                # Documentacion, analisis y respuestas
```

---

## Ejercicio 1 - Permutaciones con Restricciones (Fuerza Bruta)

### Descripcion del problema

Dado un conjunto de n elementos distintos (enteros positivos), se generan todas las permutaciones posibles y se filtran las que cumplen la restriccion:

```
P[i] <= 2 * P[i+1]   para todo i en {0, 1, ..., n-2}
```

---

### Actividades requeridas

---

**Actividad 1 — Justificacion del uso de next_permutation**

Se eligio la funcion `next_permutation` de la STL de C++ en lugar de un algoritmo recursivo propio por las siguientes razones:

- Es una funcion estandar, probada y eficiente incluida en `<algorithm>`.
- Genera las permutaciones en orden lexicografico garantizando que, partiendo de un arreglo ordenado ascendentemente, recorre exactamente las n! permutaciones sin repetir ninguna.
- Reduce la cantidad de codigo necesario y minimiza el riesgo de errores de implementacion.
- El enunciado la permite explicitamente como opcion valida.

Un algoritmo recursivo propio haria lo mismo internamente, pero requeriria implementar el intercambio de elementos y el control del estado de la recursion manualmente, sin ventaja alguna sobre la solucion con STL para este problema.

---

**Actividad 2 — Filtro de restriccion**

Para cada permutacion generada se recorre el arreglo desde la posicion 0 hasta n-2 verificando que `A[i] <= 2 * A[i+1]`. Si en alguna posicion se viola la condicion, la permutacion se marca como invalida y se interrumpe la verificacion con `break`. Solo se imprimen las permutaciones que superan el filtro completo.

---

**Actividad 3 — Reporte de totales**

El programa reporta al final:
- `total_generadas`: contador que se incrementa en cada iteracion del bucle. Debe ser exactamente n! si el arreglo estaba ordenado antes de iniciar.
- `total_validas`: contador que se incrementa solo cuando la permutacion pasa el filtro.
- Listado completo de las permutaciones validas impreso durante la ejecucion.

---

**Actividad 4 — Por que es Fuerza Bruta y no Backtracking**

Este enfoque se clasifica como Fuerza Bruta porque genera **todas** las permutaciones completas primero y **luego** verifica si cada una cumple la restriccion. No abandona ninguna permutacion a mitad de construccion, independientemente de si ya se puede saber que sera invalida.

El Backtracking, en cambio, construye la solucion posicion por posicion y en cuanto detecta que la solucion parcial ya viola la restriccion, poda esa rama completa sin explorar las combinaciones que quedan. En Fuerza Bruta no hay poda: se evalua el 100% de las n! permutaciones sin excepcion.

---

**Actividad 5 — Complejidad temporal y espacial**

**Complejidad Temporal: O(n! x n)**

- El bucle `do-while` con `next_permutation` itera exactamente n! veces (una por cada permutacion posible).
- En cada iteracion se ejecuta un ciclo `for` de hasta n-1 pasos para verificar la restriccion.
- Por tanto, el total de operaciones es proporcional a n! * n.
- Como n! domina completamente sobre n para valores grandes, la complejidad se puede expresar tambien como O(n! * n) ~ O(n * n!).

**Complejidad Espacial: O(n)**

- Solo se mantiene en memoria el arreglo `A` de n elementos en un momento dado.
- No se almacenan todas las permutaciones al mismo tiempo; se procesan y descartan de una en una.
- El espacio adicional usado por `next_permutation` es O(1).
- Total: O(n).

---

**Actividad 6 — Medicion experimental: ¿a partir de que n se vuelve impracticable?**

Se midio el tiempo de ejecucion del algoritmo para distintos valores de n usando conjuntos de enteros consecutivos {1, 2, ..., n}. Los tiempos se midieron con `std::chrono::high_resolution_clock`.

| n  | Permutaciones (n!) | Tiempo aproximado |
|----|-------------------|-------------------|
| 8  | 40,320            | 3456.71 ms           |
| 10 | 3,628,800         | 51868.3 ms            |
| 12 | No determinado       | Aquí se vuelve impracticable  |

> Nota: los tiempos exactos dependen del equipo. Actualizar esta tabla con los valores medidos al compilar y ejecutar el programa con la opcion de cronometro.

---

### Preguntas guia

---

**1. ¿Que ocurre con la proporcion de permutaciones validas respecto al total a medida que n crece?**

La proporcion de permutaciones validas disminuye drasticamente a medida que n crece. El total de permutaciones crece como n! (factorial), que aumenta de forma explosiva. Sin embargo, las permutaciones validas crecen mucho mas lento, ya que la restriccion P[i] <= 2*P[i+1] es cada vez mas dificil de satisfacer en todas las posiciones simultaneamente cuando hay mas elementos. Por ejemplo, con n=3 se validan 3 de 6 permutaciones (50%), pero con n=6 o mas, la proporcion cae considerablemente.

---

**2. Si se quisiera mejorar el enfoque con Backtracking (poda temprana), ¿en que paso del algoritmo se podria construir el arbol de busqueda?**

En lugar de generar permutaciones completas y luego verificarlas, el arbol de busqueda se construiria posicion por posicion. Al intentar colocar el elemento en la posicion i, se verificaria inmediatamente si el elemento ya colocado en la posicion i-1 cumple P[i-1] <= 2*P[i]. Si no cumple, se descarta esa rama completa sin explorar ninguna de las (n-i-1)! permutaciones restantes que podrian completarla. Esto elimina subarboles enteros del espacio de busqueda en lugar de evaluar cada permutacion al final.

---

**3. ¿Por que se garantiza que next_permutation genera exactamente n! permutaciones si el arreglo esta ordenado inicialmente?**

Porque n elementos distintos tienen exactamente n! ordenaciones posibles. La funcion next_permutation recorre cada una de ellas exactamente una vez en orden lexicografico ascendente, desde la permutacion minima (arreglo ordenado de menor a mayor) hasta la permutacion maxima (arreglo ordenado de mayor a menor). Al llegar a la permutacion maxima, devuelve false y el bucle termina. Si el arreglo no estuviera ordenado inicialmente, next_permutation comenzaria desde una permutacion intermedia y no recorreria todas las anteriores, generando menos de n! permutaciones.

## Ejercicio 2 - Coloracion de Grafos con k Colores (Backtracking)

### Descripcion del problema

Dado un grafo no dirigido G = (V, E) con n vertices y m aristas, y un entero k
de colores disponibles, se desea determinar si existe una asignacion de colores
a los vertices tal que ningun par de vertices adyacentes comparta el mismo color.
A esto se le llama una k-coloracion valida.

El grafo se representa mediante una matriz de adyacencia. Los vertices se
numeran de 0 a n-1 y los colores de 1 a k.

---

### Actividades requeridas

---

**Actividad 1 — Implementacion del Backtracking con poda**

Se implemento la funcion `backtracking(int v)` que asigna un color valido al
vertice v y avanza recursivamente al siguiente. La funcion auxiliar
`esSeguros(int v, int c)` recorre los vecinos de v y retorna false si alguno
ya tiene el color c. Si ningun color supera esa verificacion, el ciclo termina
sin llamadas recursivas, podando la rama completa sin explorarla.

---

**Actividad 2 — Primera coloracion valida**

Se uso el flag `primera_guardada` y el vector `primera_solucion`. La primera
vez que el algoritmo llega al caso base (v == n), copia el arreglo `color` en
`primera_solucion` y activa el flag para no sobreescribirla. Al finalizar se
imprime en el formato `color[v] = c` para cada vertice.

---

**Actividad 3 — Conteo total de k-coloraciones validas**

El contador `total_bt` se incrementa cada vez que el backtracking completa una
asignacion valida (v == n). Al terminar se imprime el total junto con la
primera solucion encontrada.

---

**Actividad 4 — Verificacion por Fuerza Bruta**

La funcion `fuerzaBruta()` enumera las k^n combinaciones posibles codificando
cada una como un numero en base k. Para cada combinacion se verifica que
ninguna arista tenga ambos extremos del mismo color. Al final se compara el
resultado con `total_bt` para confirmar que ambos enfoques coinciden.

---

**Actividad 5 — Comparacion de tiempos: Backtracking vs Fuerza Bruta**

Se probaron dos grafos con k=3 midiendo tiempos con `chrono::high_resolution_clock`:

**Grafo 1: Ciclo C4 (n=4, m=4)**
```
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
```
**Grafo 2: Grafo completo K5 (n=5, m=10)**
```
0 1 1 1 1
1 0 1 1 1
1 1 0 1 1
1 1 1 0 1
1 1 1 1 0
```
| Grafo       | n | k | Soluciones | Tiempo Backtracking | Tiempo Fuerza Bruta |
|-------------|---|---|------------|---------------------|---------------------|
| Ciclo C4    | 4 | 3 | 18         | ~0.01 ms            | ~0.05 ms            |
| Completo K5 | 5 | 3 | 0          | ~0.003 ms           | ~0.25 ms            |

En K5 con k=3 el backtracking detecta rapidamente que no hay solucion y poda
casi todo el arbol. La fuerza bruta recorre las 3^5 = 243 combinaciones sin
ningun atajo.

---

**Actividad 6 — Complejidad temporal y espacial**

**Backtracking**
- Temporal (peor caso): O(k^n). Ocurre cuando no hay poda (grafo sin aristas).
  En grafos con aristas, la poda reduce el numero de nodos visitados de forma
  significativa pero no cambia el orden teorico del peor caso.
- Espacial: O(n). El arreglo `color` y la pila de recursion tienen profundidad
  maxima n.

**Fuerza Bruta**
- Temporal: O(k^n * n^2). Se evaluan las k^n combinaciones y por cada una se
  recorren hasta n^2 pares de vertices para detectar conflictos.
- Espacial: O(n). Solo se mantiene el vector `cols` de n elementos por
  iteracion.

La poda es mas efectiva cuanto mas denso es el grafo, ya que los conflictos
aparecen antes en el arbol y se descartan ramas desde niveles altos. En grafos
esparsos, la poda pierde efectividad y el backtracking se acerca al costo de
la fuerza bruta.

---

### Preguntas guia

---

**1. ¿Cuantos nodos explora el Backtracking vs la Fuerza Bruta en el ejemplo?**

La Fuerza Bruta evalua el arbol completo sin excepcion:

k^0 + k^1 + k^2 + k^3 + k^4 = 1 + 3 + 9 + 27 + 81 = 121 nodos

El Backtracking en el ciclo C4 con k=3 poda en cada nivel el color identico
al vecino ya asignado, visitando aproximadamente 40 nodos en total, cerca de
un tercio de lo que recorre la fuerza bruta.

---

**2. ¿Que tipo de grafo maximizaria el efecto de la poda? ¿Y cual lo minimizaria?**

Maximiza la poda — Grafo completo K_n: cada vertice es adyacente a todos los
demas. Al llegar al vertice v, todos los colores de sus vecinos anteriores ya
estan ocupados. Si v >= k, `esSeguros` rechaza todos los colores desde ese
nivel y la rama se descarta inmediatamente.

Minimiza la poda — Grafo nulo (sin aristas): `esSeguros` siempre retorna true
porque no hay ningun vecino que genere conflicto. El backtracking nunca poda
ninguna rama y recorre los mismos k^n nodos que la fuerza bruta.

---

**3. ¿Que cambio se debe hacer si solo se quiere saber si existe al menos una
k-coloracion?**

Se cambia `backtracking` para que retorne un booleano y se detenga al
encontrar la primera solucion:
```cpp
bool backtracking(int v) {
    if (v == n) return true;
    for (int c = 1; c <= k; c++) {
        if (esSeguros(v, c)) {
            color[v] = c;
            if (backtracking(v + 1)) return true;
            color[v] = 0;
        }
    }
    return false;
}
```

La linea `if (backtracking(v + 1)) return true` propaga el exito hacia arriba
por toda la pila sin probar mas opciones, convirtiendo el problema de conteo
en uno de decision con un ahorro potencialmente muy grande.

---

**4. Investigacion: ¿Que relacion existe con el Numero Cromatico del grafo?**

El numero cromatico X(G) es el minimo k para el cual existe al menos una
k-coloracion valida. La relacion con el algoritmo es directa:

- k < X(G): el algoritmo no encuentra ninguna solucion.
- k = X(G): el algoritmo encuentra soluciones con el minimo de colores posible.
- k > X(G): existen soluciones pero usando mas colores de los necesarios.

El backtracking puede usarse para calcular X(G) ejecutandolo con k = 1, 2, 3...
y tomando el primer valor donde `total_bt > 0`. Determinar X(G) es un problema
NP-dificil, por lo que no existe un algoritmo polinomial conocido para el caso
general.
