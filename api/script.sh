#! /usr/bin/env bash

array=('teste' 'usr' 'bin' 'json' 'test' 'lib' 'etc' '')

for i in {0..1000};do sleep 0.5s
    num=$((i % 8))
    if (( $num == 0 ));then
        wget --method=GET --post-data "name=abc${i}&email=abc${i}@abc.com&password=password${i}" -p localhost:8000/	 -O /dev/null;
        wget --method=GET -p localhost:8000/?name=${array[num]} -O /dev/null;
    elif (( $num == 1 ));then
        wget --method=POST --post-data "name=abc${i}&email=abc${i}@abc.com&password=password${i}" -p localhost:8000/ -O /dev/null;
        wget --method=POST --post-data "name=abc${i}&email=abc${i}@abc.com&password=password${i}" -p localhost:8000/${array[num]} -O /dev/null;
    elif (( $num == 2 ));then
        wget --method=PUT -p localhost:8000/ -O /dev/null;
        wget --method=PUT -p localhost:8000/${array[num]} -O /dev/null;
    elif (( $num == 3 ));then
        wget --method=PATCH -p localhost:8000/ -O /dev/null;
        wget --method=PATCH -p localhost:8000/${array[num]} -O /dev/null;
    elif (( $num == 4 ));then
        wget --method=DELETE -p localhost:8000/ -O /dev/null;
        wget --method=DELETE -p localhost:8000/${array[num]} -O /dev/null;
    elif (( $num == 5 ));then
        wget --method=OPTIONS -p localhost:8000/ -O /dev/null;
        wget --method=OPTIONS -p localhost:8000/${array[num]} -O /dev/null;
    else
        wget --method=HEAD -p localhost:8000/ -O /dev/null;
        wget --method=HEAD -p localhost:8000/${array[num]} -O /dev/null;
    fi
done
