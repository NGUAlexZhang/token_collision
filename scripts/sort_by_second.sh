
if [ $# -eq 0 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

if [! -f "$1"]; then
    echo "File Not Found: $1"
    exit 1
fi

sort -k2,2n -t' ' "$1"
