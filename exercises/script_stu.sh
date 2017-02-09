case $1 in
    0)
        echo "No students"
        ;;
    1) echo "$1 student";;
    [1-4]) echo "$1 students";;
    *) echo "A lot of students";;
esac

for a in `seq 1 5`
do
    echo $a
done
for str in a , b , c_d
do
  echo "start[$str]"
  if [[ $str > "c" ]]
  then
    continue
  fi
  echo "finish"
done
read A
echo "A$A A"
