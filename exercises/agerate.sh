name='1'
age=1
while [[ -n $name && $age -ne 0 ]]
do
    echo "enter your name:"
    read name
    if [[ -z $name ]]
    then
        break
    fi
    echo "enter your age:"
    read age
    if [[ $age -eq 0 ]]
    then
        break
    fi
    if [[ $age -le 16 ]]
    then
        group=child
    elif [[ ($age -ge 17) && ($age -le 25) ]]
    then
        group=youth
    else
        group=adult
    fi
    echo "$name, your group is $group"
done
echo "bye"
