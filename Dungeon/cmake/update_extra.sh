#!/bin/bash

# Configurazioni
SOURCE_DIR="src"
HEADER_DIR="include"
CMAKE_EXTRA_FILE="cmake/extra.cmake"
TMP_FILE="/tmp/extra_new.cmake"

# Intestazione del file (con warning)
cat > "$TMP_FILE" <<EOL
# File generato automaticamente da update_extra.sh
# Modifiche MANUALI sopra il commento '###' saranno preservate
# Tutto sotto sara' sovrascritto!

### INIZIO AREA MANUALE ###
EOL

# Preserva eventuali modifiche manuali esistenti
if [ -f "$CMAKE_EXTRA_FILE" ]; then
    sed -n '/### INIZIO AREA MANUALE ###/q;p' "$CMAKE_EXTRA_FILE" >> "$TMP_FILE"
fi

# Aggiungi la lista automatica dei sorgenti
echo -e "\n### INIZIO AREA AUTOMATICA ###" >> "$TMP_FILE"
echo "target_sources(\${PROJECT_NAME} PRIVATE" >> "$TMP_FILE"

find "$SOURCE_DIR"  \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \)| sort | while read -r file; do
    echo "    $file" >> "$TMP_FILE"
done

find "$HEADER_DIR"  \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \)| sort | while read -r file; do
    echo "    $file" >> "$TMP_FILE"
done


echo ")" >> "$TMP_FILE"

# Sostituisci il file solo se ci sono cambiamenti
if ! cmp -s "$TMP_FILE" "$CMAKE_EXTRA_FILE"; then
    mv "$TMP_FILE" "$CMAKE_EXTRA_FILE"
    echo "File $CMAKE_EXTRA_FILE aggiornato."
else
    echo "Nessun cambiamento necessario."
    rm "$TMP_FILE"
fi