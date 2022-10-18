#!/bin/bash

cat "$1" | LC_ALL=C awk 'length($0) >= 3 && length($0) <= 15' | sort | uniq | shuf -o dirtyfle
