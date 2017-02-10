read a op b
while [[ $a -ge 0 ]]; do
if [[ $a == "exit" ]]; then
    echo 'bye'
    exit 0
fi
if [[ $op != "+" && $op != "-" && $op != "*" && $op != "/" && $op != "%" && $op != "**"  ]]
then
    echo "error"
    exit 0
fi
if [[ (-z $b) || (-z $a) ]]
then
    echo "error"
    exit 0
fi
let "r = $a $op $b"
echo "$r"
read a op b
done
