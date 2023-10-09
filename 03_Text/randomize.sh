if [ "$1" == "" ]; then
    SL=0.01
else
    SL=$1
fi

exit_handler() {
  trap - EXIT
  test -r "$TMPFILE1" && rm -f "$TMPFILE1"
  test -r "$TMPFILE2" && rm -f "$TMPFILE2"
}

trap exit_handler EXIT HUP INT QUIT PIPE TERM

TMPFILE1="`mktemp`"
TMPFILE2="`mktemp`"

cat | hexdump -v -e '/1 "%02X \n"' > $TMPFILE1

MAXROW=$( cat < $TMPFILE1 | grep -o 0A | wc -l)

ROW=0
COL=0

cat < $TMPFILE1 | while read In; do
    case $In in
    0A) COL=0 ; ROW=$(( ROW + 1 ));;
    20) COL=$(( COL+1 )) ;;
    *) echo >> $TMPFILE2 "$ROW $COL $In" ; COL=$(( COL + 1 ));;
    esac
done

tput clear

cat < $TMPFILE2 | shuf | while read ROW COL CHAR; do
    tput cup $ROW $COL
    echo -en "\x$CHAR"
    sleep $SL
done

tput cup $MAXROW 0 
