#!/bin/bash

for f in *
do
	diff <(./encode -i $f | ./decode) $f
	echo ""
done
