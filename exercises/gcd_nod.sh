gcd () 
{
    a=$1
    b=$2
    if [[ b -eq 0 ]]; then
        echo "GCD is $a"
    else
        let "r = $a % $b"
        gcd $b $r
    fi
}
read a b
while [[ -n $a ]]; do
gcd $a $b
read a b
done
echo "bye"
