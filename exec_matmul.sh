#!/bin/bash

# Les valeurs à faire varier
N_VALUES=(1 2 4 8 16 32 64 128)
M_VALUES=(1 2 4 8 16 32 64 128)
K_VALUES=(1 2 4 8 16 32 64 128)

# Parcourir toutes les combinaisons possibles
for N in "${N_VALUES[@]}"; do
  for M in "${M_VALUES[@]}"; do
    for K in "${K_VALUES[@]}"; do
      # Exécuter l'executable avec les paramètres actuels
      ./matmul_papi $N $M $K
    done
  done
done
