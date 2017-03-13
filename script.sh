#!/bin/sh  
f=TestRun.cpp 
tmpf="`mktemp /tmp/onchange.XXXXX`"  
cp "$f" "$tmpf"  
trap "rm $tmpf; exit 1" 2  
while : ; do  
  sleep 2  
  if [ "$f" -nt "$tmpf" ]; then  
     cp "$f" "$tmpf" 
		 clear 
     make dev
  fi  
done 
