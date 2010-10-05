#!/bin/bash

pwd=`echo $PWD`
cmd="$pwd/parser"

cur_file=`echo $0`
#
for file in $(find . -name "*.sh")
do
	cd $pwd;
	cd ${file%/*};
	if [ "${file##*/}" = "${cur_file##*/}" ]
	then continue
	fi
	echo "parsing $file";
	$cmd <${file##*/};
done
