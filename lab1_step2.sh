#Name: Han Duan
#Date: Jan 17th 2023
#Title: Lab 1 - Basic Shell Programming
#Description: This program asks for radius of circle and returns area and perimeter. 

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "JohnD" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
        exit 1 
fi

area (){
    area=`echo "$1 * $1 * 3.1415" | bc`
    echo "The area of the circle is $area"
}

perimeter (){
    perimeter=`echo "$1 * 2 * 3.1415" | bc`
    echo "The perimeter of the circle is $perimeter"
}

response="Yes" 
while [ $response != "No" ]
do 
    echo "Enter radius of circle: "
    read radius 
    if [ $radius -lt 1  ]
    then
            echo "enter a positive number"
            exit 1
    else 
        area $radius
        perimeter $radius 

        echo "Would you like to repeat for another circle [Yes/No]?"
        read response
    fi 
done
