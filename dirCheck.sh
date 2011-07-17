#!/bin/bash

dir="/home/harisha/Harisha_samples/"
list="$(ls -A $dir)"
echo $list
if [ x"$list" == x ] ; then	
	echo $dir is empty
else
	echo $dir is not empty
fi
