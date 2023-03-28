all: build run clear

build:
  g++ *.cpp -o main.exe
run:
  ./main.exe
clear:
  rm main.exe
