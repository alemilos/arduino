#!/bin/bash

# Nome del file di output
OUTPUT_FILE="repo_dump.txt"

# Rimuove il file se esiste già per iniziare da zero
if [ -f "$OUTPUT_FILE" ]; then
    rm "$OUTPUT_FILE"
fi

echo "Inizio scansione della repository..."

# Trova i file e processali
# -maxdepth 4: limita la profondità
# -not -path "*/.*": esclude cartelle nascoste (come .git o .pio)
find . -maxdepth 4 \( -name "*.cpp" -o -name "*.h" -o -name "*.ini" \) -not -path "*/.*" | while read -r file; do
    echo "Processing: $file"
    echo "========================================" >> "$OUTPUT_FILE"
    echo "FILE: $file" >> "$OUTPUT_FILE"
    echo "========================================" >> "$OUTPUT_FILE"
    cat "$file" >> "$OUTPUT_FILE"
    # Aggiunge tre linee vuote tra un file e l'altro per leggibilità
    echo -e "\n\n\n" >> "$OUTPUT_FILE"
done

echo "Completato! Il dump è disponibile in: $OUTPUT_FILE"