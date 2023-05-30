#include "List.h"
#include "Alloc.h"
#include "version.h"
#include <iostream>
#include <map>
#include <memory>

int fac(int val) {
	if (val < 0)
		return 0;
	if (val == 0)
		return 1;
	else
		return val * fac(val - 1);
}
int main(){

	int val;
	//Реализация пользовательского контейнера List с аллокатором стандартной библиотеки stl
	List <int>stlAllocList;
	for (int i = 0; i < 10; ++i) {
		stlAllocList.push_back(i);
	}
	stlAllocList.print();
	 
	//Реализация пользовательского контейнера List с пользовательским аллокатором 
	List <int, CastAlloc<int,10>>castAllocList;
	for (int i = 0; i < 10; ++i) {
		castAllocList.push_back(i);
	}
	castAllocList.print();
	 
	//Реализация контейнера std::map со стандартным аллокатором
	std::map<int, int> stlAllocMap;
	for (int i = 0; i < 10; ++i) {
		val = fac(i);
		stlAllocMap.insert({ i, val });
	}
	for (auto it : stlAllocMap) {
		std::cout << it.first << " " << it.second << std::endl;
	}

	//Реализация контейнера Map с пользовательским аллокатором
	std::map<int, int, std::less<int>, CastAlloc<std::pair<const int, int>, 10>> castAllocMap;
	for (int i = 0; i < 10; ++i) {
		val = fac(i);
		castAllocMap.insert({ i, val });
	}
	for (auto it : castAllocMap) {
		std::cout << it.first << " " << it.second << std::endl;
	}

	return 0;
}
