#!/bin/bash
# Գործնական 3 — mmap — Խնդիր 1
# Գործարկում՝  chmod +x logs_generator.sh && ./logs_generator.sh
# Ստուգում՝    ./logs_generator.sh check <թիվ>

OS=$(uname -s)
case "$OS" in
    Darwin) OS_NAME="macOS"; BASE="$HOME/Library/Logs/practice3" ;;
    Linux)  OS_NAME="Linux"; BASE="$HOME/.local/state/practice3" ;;
    *)      echo "Այս ՕՀ-ը չի աջակցվում՝ $OS"; exit 1 ;;
esac
TMP_BASE="/tmp/practice3_$(id -un)"
CARD="$BASE/task_card.txt"
SECRET="$BASE/.answer"
MANIFEST="$BASE/manifest.txt"

if [ "$1" = "check" ]; then
    if [ ! -f "$SECRET" ]; then
        echo "Նախ գործարկեք՝ ./logs_generator.sh"
        exit 1
    fi
    if [ -z "$2" ]; then
        echo "Օգտագործում՝ ./logs_generator.sh check <թիվ>"
        exit 1
    fi
    if [ "$(printf '%s' "$2" | base64)" = "$(cat "$SECRET")" ]; then
        echo "Ճիշտ է։ Ապրե՛ս։"
    else
        echo "Սխալ է։ Ստուգեք ծրագիրը և փորձեք նորից։"
    fi
    exit 0
fi

LEVELS=(INFO INFO INFO INFO INFO DEBUG DEBUG WARN WARN WARN ERROR ERROR CRITICAL)
SERVICES=(auth api db cache net disk backup)
MESSAGES=("User login" "User logout" "Connection timeout" "Connection refused"
          "Disk usage 91%" "Packet lost" "Cache miss" "Query took 1203 ms"
          "Permission denied" "Backup completed" "Service restarted"
          "Config reloaded" "Out of memory" "Request served")

make_log() {
    local file=$1 n=$2 i
    local t=$((8 * 3600 + RANDOM % 3600))
    mkdir -p "$(dirname "$file")"
    for ((i = 0; i < n; i++)); do
        t=$((t + RANDOM % 40 + 1))
        printf '2026-10-25 %02d:%02d:%02d [%s] %s: %s\n' \
            $((t / 3600 % 24)) $((t / 60 % 60)) $((t % 60)) \
            "${LEVELS[RANDOM % ${#LEVELS[@]}]}" \
            "${SERVICES[RANDOM % ${#SERVICES[@]}]}" \
            "${MESSAGES[RANDOM % ${#MESSAGES[@]}]}"
    done > "$file"
}

rm -rf "$BASE" "$TMP_BASE"
FILES=("$BASE/app/app.log"
       "$BASE/database/db.log"
       "$BASE/network/net.log"
       "$BASE/network/archive/net.1.log"
       "$TMP_BASE/cache/cache.log")

echo "Ստեղծում եմ լոգ ֆայլերը..."
for f in "${FILES[@]}"; do
    make_log "$f" $((RANDOM % 400 + 300))
done
printf '%s\n' "${FILES[@]}" > "$MANIFEST"

case "$OS" in
    Darwin) TARGET="${FILES[0]}"; WORDS=(ERROR WARN timeout refused) ;;
    Linux)  TARGET="${FILES[2]}"; WORDS=(CRITICAL ERROR lost denied) ;;
esac
WORD=${WORDS[RANDOM % ${#WORDS[@]}]}
COUNT=$(grep -c -- "$WORD" "$TARGET")
printf '%s' "$COUNT" | base64 > "$SECRET"

{
    echo "=================================================="
    echo " Գործնական 3 — mmap — Խնդիր 1"
    echo " ՕՀ՝ $OS_NAME"
    echo "=================================================="
    echo " Ստեղծվեցին լոգ ֆայլեր՝"
    for f in "${FILES[@]}"; do
        printf '   %s (%s տող)\n' "$f" "$(wc -l < "$f" | tr -d ' ')"
    done
    echo " Բոլոր ֆայլերի ցանկը՝ $MANIFEST"
    echo
    echo " ՔՈ ՏԱՐԲԵՐԱԿԸ"
    echo "   Ֆայլ՝ $TARGET"
    echo "   Բառ՝  $WORD"
    echo
    echo " Գրիր ծրագիր, որը mmap-ով կբացի ֆայլը և կհաշվի,"
    echo " թե քանի անգամ է այնտեղ հանդիպում «$WORD» բառը։"
    echo
    echo " Ստուգում՝ ./logs_generator.sh check <քո ստացած թիվը>"
    echo " Այս տեքստը պահպանված է՝ $CARD"
    echo "=================================================="
} | tee "$CARD"
