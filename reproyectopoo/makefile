all: compilar
compilar: main loginSystem Users UserSys ActaSys
	g++ -o programa main.o loginSystem.o Users.o UserSys.o ActaSys.o
main: main.cpp
	g++ -c main.cpp
loginSystem: loginSystem.cpp loginSystem.hpp
	g++ -c loginSystem.cpp
Users: Users.cpp Users.hpp
	g++ -c Users.cpp
UserSys: UserSys.cpp UserSys.hpp
	g++ -c UserSys.cpp
ActaSys: ActaSys.cpp ActaSys.hpp
	g++ -c ActaSys.cpp