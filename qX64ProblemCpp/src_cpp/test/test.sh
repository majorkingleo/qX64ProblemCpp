#!/usr/bin/env bash

PROG=../../qX64Problem

for i in *  ; do
	if test -d $i ; then
		( cd $i && $PROG -test-file in.* > output.txt ) 
		  res=`diff --ignore-blank-lines $i/output.txt $i/expected_result.txt` 
		  
		  if ! test -z "$res" ; then
			echo "DIFFER in $i:"
			echo "     $res"
			echo 
		  else
			echo "check $i passed"
		  fi 
	fi
done
