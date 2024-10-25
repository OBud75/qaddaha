#!/bin/bash

read -p "Entrez l'extension d'entrée " input_ext
read -p "Entrez l'extension de sortie  " output_ext
read -p "Entrez le lieu d'origine des fichiers " source_dir
read -p "Entrez le lieu où les fichiers seront renommés " dest_dir

file_count=$(ls "$source_dir" | grep -c "*\.$input_ext$")
for i in {file_count}; do mv "$source_dir/img_$i.$input_ext" "$dest_dir/img_$i.$output_ext"; done
echo "badaboum le renommage est done wsh wsh"