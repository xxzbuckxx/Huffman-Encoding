#!/bin/bash

cd ../ && make
for i in $(ls ../../resources/corpora/calgary); do
	echo "ENCODE"
	echo "checking diff -i $i"
	diff <(./encode -i ../../resources/corpora/calgary/$i) <(../../resources/asgn6/encode -i ../../resources/corpora/calgary/$i)
	echo "checking diff for pipe $i"
	diff <(cat ../../resources/corpora/calgary/$i | ./encode) <(cat ../../resources/corpora/calgary/$i | ../../resources/asgn5/encode )
	echo ""
done
