# Crivo de Eratóstenes
## _Programação concorrente (CC0021)_

O crivo de Eratóstenes é um método de identificar a primalidade dos números até determinado limite N ( N ∈ Naturais). Na tentativa de determinar os números primos de um intervalo [2, n], pode-se utilizar uma alternativa básica para resolver o problema, pela realização do teste de primalidade em cada elemento do intervalo, ou seja, verificar se é divisível somente por 1 e ele mesmo

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
