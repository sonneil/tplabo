#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CorrePocoyo{

  public:

	CorrePocoyo();

	CorrePocoyo(const CorrePocoyo<T>&);

	~CorrePocoyo();

	void nuevoCorredor(const T&);

	void nuevoCorredor(const T&, const T&);

	void seCansa(const T&);

	void sobrepasar(const T&);

	const T& corredorFilmado() const;
	
	void filmarProxPerdedor();

	void filmarProxExitoso();

	const T& damePrimero() const;	

	int damePosicion(const T& ) const;	

	const T& dameCorredorEnPos(int) const;	
	
	bool esVacia() const;

	int tamanio() const;	

	bool operator==(const CorrePocoyo<T>&) const;	

	ostream& mostrarCorrePocoyo(ostream&) const;

  private:

	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	struct Nodo {
		Nodo* nextCorredor;
		T currCorredor;
		
		
		Nodo (const T& n) : nextCorredor(), currCorredor(n) { };
	};
	
	int tamanioc;
	Nodo* prmCorredor;
	Nodo* filmando;
};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

template<class T>
CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& cp) {
	this->tamanioc = 0;
	if (cp.tamanio() != 0) {
		if (cp.tamanioc > 0) {
			this->tamanioc = cp.tamanio();
			this->prmCorredor = new Nodo(cp.damePrimero());
			// Guardo el primer corredor en un nodo auxiliar
			Nodo* nAux = this->prmCorredor;
			// Copio todos los nodos de cp
			for (int i = 0; i < cp.tamanio()-1; i++) {
				this->prmCorredor = new Nodo(cp.dameCorredorEnPos(i));
				this->prmCorredor = this->prmCorredor->nextCorredor;
			}
			// Copio el ultimo nodo de cp y dejo CorrePocoyo en su estado original
			this->prmCorredor = new Nodo(cp.dameCorredorEnPos(cp.tamanio()-1));
			this->prmCorredor->nextCorredor = nAux;
			this->prmCorredor = this->prmCorredor->nextCorredor;
		}
	}
}

template<class T>
CorrePocoyo<T>::CorrePocoyo(){
	this->tamanioc=0;
	this->prmCorredor=NULL;
	this->filmando=NULL;
}

// funciona
template<class T>
void CorrePocoyo<T>::nuevoCorredor(const T& nuevo){
	Nodo* nuevoNodo = new Nodo(nuevo);
	if(this->tamanioc==0) {
		this->prmCorredor = nuevoNodo;
		this->filmando = nuevoNodo;
		this->prmCorredor->nextCorredor = this->prmCorredor;
	} else {
		Nodo * actual=this->prmCorredor;
		while((actual->nextCorredor->currCorredor)!=(this->prmCorredor->currCorredor)) {
			actual=(actual->nextCorredor);
		}
		actual->nextCorredor = nuevoNodo;
		nuevoNodo->nextCorredor = this->prmCorredor;
	}
	tamanioc++;
}

template<class T>
CorrePocoyo<T>::~CorrePocoyo() {
	if (this != NULL) {
		if (this->tamanioc > 0) {
			// Borro todos los nodos de cp
			for (int i = 0; i < this->tamanio(); i++) {
				Nodo* nAux = this->prmCorredor;
				this->prmCorredor = nAux->nextCorredor;
				delete nAux;
			}
		
		}
	}
	// TODO: Borrar tamanio?
}

template<class T>
void CorrePocoyo<T>::seCansa(const T& cansado) {
	Nodo* actual = this->prmCorredor;
	Nodo* nBorrar = this->prmCorredor;
	while(actual->nextCorredor->currCorredor!=cansado) {
		actual = actual->nextCorredor;
	}
	nBorrar = actual->nextCorredor;
	if (this->filmando->currCorredor == nBorrar->currCorredor) {
		this->filmando = nBorrar->nextCorredor;	
	}
	actual->nextCorredor = nBorrar->nextCorredor;
	this->tamanioc--;
	delete nBorrar;
}

template<class T>
bool CorrePocoyo<T>::esVacia() const {
	return (this->tamanioc == 0);
}

template<class T>
int CorrePocoyo<T>::tamanio() const {
	return this->tamanioc;
}

template<class T>
void CorrePocoyo<T>::filmarProxPerdedor() {
	this->filmando = this->filmando->nextCorredor;	
}

template<class T>
const T& CorrePocoyo<T>::corredorFilmado() const {
	return filmando->currCorredor;
}

template<class T>
int CorrePocoyo<T>::damePosicion(const T& corredor) const {
	int pos = 0;
	Nodo* actual = this->prmCorredor;
	while (actual->currCorredor == corredor) {
		actual = actual->nextCorredor;		
		pos++;
	}
	return pos;
}

template<class T>
ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& cout) const {
	if (this->tamanioc == 0) {
		cout << "[]" << endl;
	} else {
		Nodo* actual = this->prmCorredor;
		cout << "[";
		for (int i=0; i < this->tamanio(); i++) {
			if (this->tamanio()-1 != i) {
				cout << actual->currCorredor << "-" << actual->nextCorredor->currCorredor << ", ";
			} else {
				cout << actual->currCorredor << "-" << actual->nextCorredor->currCorredor;
			}
			actual = actual->nextCorredor;
		}
		cout << "]" << endl;
	}
	return cout;
}
#endif //CORREPOCOYO_H_
