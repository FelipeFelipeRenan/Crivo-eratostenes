![crivo](https://user-images.githubusercontent.com/72557256/194676593-72f57172-ed0e-469d-818b-2e17e751205b.png)

<div align="center">
 <h2>Programação concorrente (CC0021)</h2>
</div>

O crivo de Eratóstenes é um método de identificar a primalidade dos números até determinado limite N ( N ∈ Naturais). Na tentativa de determinar os números primos de um intervalo [2, n], pode-se utilizar uma alternativa básica para resolver o problema, pela realização do teste de primalidade em cada elemento do intervalo, ou seja, verificar se é divisível somente por 1 e ele mesmo.

## Features

- Algoritmo sequencial
- Algoritmo paralelo (MP)
- Algoritmo paralelo (MPI) 🚧


#### Compilar e executar 🚀

Sequencial e com Openmp:

```sh
gcc -fopenmp crivo_xxxx.c main.c -lm -o app && ./app
```

Algoritmo com MPI:

```sh
mpicc crivo_mpi.c -lm -o app && mpiexec -n NUMERO_DE_PROCESSOS ./app
```
