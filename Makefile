

all:
	gcc src/*.c -o app -pthread
	echo "Build Done"

memory_check:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./app 5000