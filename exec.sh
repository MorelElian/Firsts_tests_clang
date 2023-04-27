#!/bin/bash

program_names=("software_pipelining")   # Noms des programmes à exécuter
params=(1 2 4 8 10 16 20 32 40 50 64 128 256 512 1024 4096)   # Tableau de paramètres 
params2=(4 5 6 7)
 repeat=20                                # Nombre de répétitions pour cha

for program_name in "${program_names[@]}"; do  # Itération sur les programmes

  for param in "${params[@]}"; do
  for param2 in "${params2[@]}"; do            # Itération sur les paramètres
    for i in $(seq 1 $repeat); do             # Itération sur les répétitions
      # Exécution du programme avec le paramètre et stockage de la sortie
      "./$program_name" "$param" "$param2"
    done
  done
done
done

  
 
