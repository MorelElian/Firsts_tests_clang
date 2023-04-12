#!/bin/bash

program_names=("Matrix_mul" "Matrix_mul_jit")   # Noms des programmes à exécuter
params=(1 2 4 8 10 16 20 32 40 50 64)   # Tableau de paramètres
repeat=20                                # Nombre de répétitions pour chaque paramètre

for program_name in "${program_names[@]}"; do  # Itération sur les programmes

  for param in "${params[@]}"; do            # Itération sur les paramètres
    for i in $(seq 1 $repeat); do             # Itération sur les répétitions
      # Exécution du programme avec le paramètre et stockage de la sortie
      output=$("./$program_name" "$param" "1000")
    done
  done
done
