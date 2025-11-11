#!/bin/bash

echo -e "Employee Database\n"

echo -e "File name:"
read fname

touch $fname

# write header
echo -e "EMPNO \t Name \t Mobile \t" >> $fname

ch=0
while [ $ch -lt 6 ]
do

echo -e "1) Create Employee book\n"
echo -e "2) View Employee Data\n"
echo -e "3) Insert a record\n"
echo -e "4) Delete a record\n"
echo -e "5) Modify a record\n"
echo -e "6) Exit"

echo "Enter Your Choice:"
read ch

case $ch in 

    1)

    echo "Enter number of records:"
    read n

        for((i=0;i<$n;i++))
        do

        echo "Enter EMPNO:"
        read empno

        echo "Enter name:"
        read name

        echo "Enter mobile number:"
        read mob

        echo -e "$empno \t $name \t $mob" >> $fname

        done

    ;;

    2)

    cat  $fname

    ;;

    3) 
        echo "Enter EMPNO:"
        read empno

        echo "Enter name:"
        read name

        echo "Enter mobile number:"
        read mob

        echo -e "$empno \t $name \t $mob " >> $fname

    ;;
    4)

        echo "Enter EMPNO to delete:"
        read empno

        if grep -w $empno $fname
        then
            grep -wv $empno $fname >>temp
            rm $fname
            mv temp $fname
            echo "Record deleted."
        else
            echo "record not found"
        fi


    ;;
    5)
    echo "Enter EMPNO to modify:"
    read empno

    if grep -w $empno $fname
    then
        # remove old record
        grep -wv $empno $fname >>temp
        rm $fname
        mv temp $fname

        # get new details
        echo "Enter EMPNO:"
        read empno

        echo "Enter name:"
        read name

        echo "Enter mobile number:"
        read mob

        echo -e "$empno \t $name \t $mob " >> $fname
        echo "Record modified."
        else
            echo "record not found"
        fi
    ;;
    6)
        # choosing 6 will break out because while condition fails (ch >= 6)
    ;;
    *)
        echo "Invalid choice"
    ;;

esac

done
