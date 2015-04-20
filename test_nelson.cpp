#include "correpocoyo.h"

int main() {
	CorrePocoyo<int> cp;
	cp.nuevoCorredor(1);
	cp.nuevoCorredor(2);
	cp.nuevoCorredor(3);
	int tamanio = cp.tamanio();
	cp.seCansa(2);
	cp.mostrarCorrePocoyo(cout);
	cout << tamanio << endl;
}
