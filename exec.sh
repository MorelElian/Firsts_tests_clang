#!/bin/bash

program_names=("for_test.o" "for_test_jit.o")   # Noms des programmes à exécuter
params=(1 10 20 30 40 50 60 70 80 90 100)   # Tableau de paramètres
repeat=500                                 # Nombre de répétitions pour chaque paramètre

for program_name in "${program_names[@]}"; do  # Itération sur les programmes

  for param in "${params[@]}"; do            # Itération sur les paramètres
    for i in $(seq 1 $repeat); do             # Itération sur les répétitions
      # Exécution du programme avec le paramètre et stockage de la sortie
      output=$("./$program_name" "$param")
    done
  done
done
