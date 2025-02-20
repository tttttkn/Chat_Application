

all:
	gcc src/*.c -o app -pthread
	echo "Build Done"