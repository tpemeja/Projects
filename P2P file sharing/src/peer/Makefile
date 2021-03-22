.PHONY: clean

all:
	javac -d ./target src/main/java/fileshare/*.java
	javac -d ./target -cp ./target src/main/java/*.java

run: run1

run1:
	rm -rf peer1
	mkdir peer1
	mkdir peer1/files
	cp -r target/* ./peer1/
	cp files/file1.txt ./peer1/files/file1.txt
	cp files/file.txt ./peer1/files/file.txt
	cp config.ini ./peer1/config.ini
	sudo ifconfig lo 127.0.0.2
	cd ./peer1 && java Main

run2:
	rm -rf peer2
	mkdir peer2
	mkdir peer2/files
	cp -r target/* ./peer2/
	cp files/file2.txt ./peer2/files/file2.txt
	cp files/file.txt ./peer2/files/file.txt
	cp files/ok.jpg ./peer2/files/ok.jpg
	cp config.ini ./peer2/config.ini
	sudo ifconfig lo 127.0.0.3
	cd ./peer2 && java Main

run8081:
	java -ea -cp ./target Main 8081


clean:
	rm -rf target
	rm -rf peer1
	rm -rf peer2
