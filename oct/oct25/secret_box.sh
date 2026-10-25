#!/bin/bash
# Գործնական 3 — mmap — Խնդիր 5
# Գործարկում՝  chmod +x secret_box.sh && ./secret_box.sh
# Ստուգում՝    ./secret_box.sh check

export LC_ALL=C
BOX="box.bin"
STATE=".box_state"
OS=$(uname -s)

case "$OS" in
    Darwin) OS_NAME="macOS"; MODE=1 ;;
    Linux)  OS_NAME="Linux"; MODE=2 ;;
    *)      echo "Այս ՕՀ-ը չի աջակցվում՝ $OS"; exit 1 ;;
esac

if [ "$1" = "check" ]; then
    if [ ! -f "$STATE" ] || [ ! -f "$BOX" ]; then
        echo "Նախ գործարկեք՝ ./secret_box.sh"
        exit 1
    fi
    read OFFSET LEN HASH < "$STATE"
    GOT=$(dd if="$BOX" bs=1 skip="$OFFSET" count="$LEN" 2>/dev/null | base64 | tr -d '\n')
    if [ "$GOT" = "$HASH" ]; then
        echo "Ճիշտ է։ Հաղորդագրությունը վերծանված է հենց ֆայլի մեջ։"
    else
        echo "Սխալ է։ box.bin ֆայլում հաղորդագրությունը դեռ վերծանված չէ։"
    fi
    exit 0
fi

MESSAGES=("MMAP TURNS A FILE INTO AN ARRAY"
          "MAP ANONYMOUS NEEDS NO FILE"
          "SHARED MAPPINGS REACH THE DISK"
          "PRIVATE MAPPINGS USE COPY ON WRITE"
          "MSYNC SAVES CHANGES TO THE FILE"
          "MUNMAP FREES THE MAPPING")
MSG=${MESSAGES[RANDOM % ${#MESSAGES[@]}]}
LEN=${#MSG}
KEY=$((RANDOM % 200 + 40))
OFFSET=$((RANDOM % 3000 + 100))

byte() { printf "\\$(printf '%03o' "$1")"; }
le32() {
    byte $(($1 & 255)); byte $((($1 >> 8) & 255))
    byte $((($1 >> 16) & 255)); byte $((($1 >> 24) & 255))
}
encode_char() { byte $(( $(printf '%d' "'$1") ^ KEY )); }

{
    printf 'BOX3'
    le32 "$OFFSET"; le32 "$LEN"; le32 "$KEY"; le32 "$MODE"
    head -c $((OFFSET - 20)) /dev/urandom
    if [ "$MODE" -eq 1 ]; then
        for ((i = 0; i < LEN; i++)); do encode_char "${MSG:i:1}"; done
    else
        for ((i = LEN - 1; i >= 0; i--)); do encode_char "${MSG:i:1}"; done
    fi
    head -c $((RANDOM % 500 + 100)) /dev/urandom
} > "$BOX"

printf '%s %s %s\n' "$OFFSET" "$LEN" "$(printf '%s' "$MSG" | base64 | tr -d '\n')" > "$STATE"

echo "=================================================="
echo " Գործնական 3 — mmap — Խնդիր 5. Գաղտնի արկղ"
echo " ՕՀ՝ $OS_NAME"
echo "=================================================="
echo " Ստեղծվեց $BOX ֆայլը ($(wc -c < "$BOX" | tr -d ' ') բայթ)։"
echo " Ֆայլի սկզբում գրված է struct BoxHeader (20 բայթ)՝"
echo "   magic[4], offset, length, key, mode"
echo " Գաղտնի հաղորդագրությունը գտնվում է offset դիրքում։"
echo " Քո ռեժիմը (mode) կգտնես header-ի մեջ։"
echo
echo " Ստուգում՝ ./secret_box.sh check"
echo "=================================================="
