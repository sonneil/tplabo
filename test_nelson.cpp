#include "correpocoyo.h"

int main() {
	CorrePocoyo<int> cp;
	cp.nuevoCorredor(1);
	cp.nuevoCorredor(2);
	cp.nuevoCorredor(3);
	cp.mostrarCorrePocoyo(cout);
}
