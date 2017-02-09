echo "args n:$# is $1 $2 ..."
if [[ -z $1 ]] 
then 
    echo "arg 1 is empty"
fi
if [[ -n $2 ]]
then
    echo "arg 2 not is empty"
fi
if [[ $1 == "some" ]]
then
    echo "arg one is some"
fi
if [[ -e $1 ]]
then
    echo "$1 exist"
else
    echo "$1 dont exist"
fi

if [[ -f $1 ]]
then
    echo "$1 is File"
    if [[ -x $1 ]]
    then
        echo "and executable"
    fi
fi
if [[ -d $1 ]]
then
    echo "$1 is Dir"
fi
if [[ (-f $1) && (-x $1) ]]
then
    echo "file and exec"
fi
if [[ $# -lt 2 ]]
then
    echo "FEW arguments"
fi
