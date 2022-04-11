all: clean main

main:
	gcc -o main src/main.c && ./main

clean:
	rm -f main

test:
	gcc -o main src/main.c && ./main < tests/in.txt > out_test.txt && diff -w out_test.txt tests/out.txt && echo "OK" || exit 1
	gcc -o main src/main.c && ./main < tests/in_full.txt > out_test.txt && diff -w out_test.txt tests/out_full.txt && echo "OK" || exit 1