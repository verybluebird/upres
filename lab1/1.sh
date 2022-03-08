#!/bin/sh
#if argument is not written
if [ "$1" = "" ];
        then
                echo "Error! Write an argument!" &>2
                exit 1
fi
if [ ` stat -c "%A" $1 | grep "r"| wc -l` = "0" ];
        then
                echo "You don't have rights to read!" &>2
                exit 1
fi

#full path to argument_dir
fname=`find /home/NSTU/pmi-b9110 -type d -name $1`

#if argument_dir is not found
if [ "$fname" = "" ];
        then
                echo "Error! Can't find this folder!" &>2
                exit 1
fi



#read lines of dirs in argument_dir in loop
ls -F1 $fname| grep '/'| while read -r line ;
do
#if dir contains 0 dirs then print it
        if [ `ls -F1 ${fname}/$line| grep '/' | wc -l` = "0" ];
        then
                echo $line
        fi
done

