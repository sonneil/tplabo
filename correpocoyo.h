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
//
	CorrePocoyo();
//chequear
	CorrePocoyo(const CorrePocoyo<T>&);
//chequear
	~CorrePocoyo();
//
	void nuevoCorredor(const T&);
//
	void nuevoCorredor(const T&, const T&);
// falla
	void seCansa(const T&);
//
	void sobrepasar(const T&);
//
	const T& corredorFilmado() const;
//
	void filmarProxPerdedor();
//
	void filmarProxExitoso();
//
	const T& damePrimero() const;	
// 
	int damePosicion(const T& ) const;	
//
	const T& dameCorredorEnPos(int) const;	
//
	bool esVacia() const;
//
	int tamanio() const;	
//chequear
	bool operator==(const CorrePocoyo<T>&) const;	
//
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

// chequear
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


// funciona, se puede escribir mejor
template<class T>
void CorrePocoyo<T>::nuevoCorredor(const T& nuevo, const T& adelantado){
	Nodo* nuevoNodo = new Nodo(nuevo);
	Nodo* actual = this->prmCorredor;
	if(actual->currCorredor==adelantado){
		this->prmCorredor=nuevoNodo;
		nuevoNodo->nextCorredor=actual;
		while((actual->nextCorredor->currCorredor)!=adelantado) {
			actual=(actual->nextCorredor);
		}
		actual->nextCorredor=nuevoNodo;
	}else{
		while((actual->nextCorredor->currCorredor)!=adelantado) {
			actual=(actual->nextCorredor);
		}
		Nodo * nAux=actual->nextCorredor;
		actual->nextCorredor = nuevoNodo;
		nuevoNodo->nextCorredor = nAux;
	}
	tamanioc++;
}

// chequear
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

//falla
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
void CorrePocoyo<T>::sobrepasar(const T& elQSobrepasa){
	Nodo* anterior = this->prmCorredor;
	Nodo* actual = this->prmCorredor->nextCorredor;
	while(actual->nextCorredor->currCorredor!=elQSobrepasa){
		anterior=actual;
		actual=actual->nextCorredor;
	}
	anterior->nextCorredor=actual->nextCorredor;
	Nodo * nAux=actual->nextCorredor->nextCorredor;
	actual->nextCorredor->nextCorredor=actual;
	actual->nextCorredor=nAux;
	
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
void CorrePocoyo<T>::filmarProxExitoso(){
	Nodo* actual = this->prmCorredor;
	while(actual->nextCorredor->currCorredor!=this->filmando->currCorredor) {
		actual = actual->nextCorredor;
	}
	this->filmando=actual;
}

template<class T>
const T& CorrePocoyo<T>::corredorFilmado() const {
	return filmando->currCorredor;
}

template<class T>
const T& CorrePocoyo<T>::damePrimero() const{
	return this->prmCorredor->currCorredor;
}


template<class T>
int CorrePocoyo<T>::damePosicion(const T& corredor) const {
	int pos = 1;
	Nodo* actual = this->prmCorredor;
	while (actual->currCorredor!= corredor) {
		actual = actual->nextCorredor;
		pos++;
	}
	return pos;
}

// Esta va bien
template<class T>
const T& CorrePocoyo<T>::dameCorredorEnPos(int pos) const{
	int n = 1;
	Nodo* actual = this->prmCorredor;
	while(n!=pos){
		actual=actual->nextCorredor;
		n++;
	}
	return actual->currCorredor;
}

// chequear
template<class T>
bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>& carrera) const{
	bool comparacion=((this->tamanioc==carrera->tamanioc) and (this->filmando->currCorredor==carrera->filmando->currCorredor));
	Nodo * actual1=this->prmCorredor;
	Nodo * actual2=carrera->prmCorredor;
	while(comparacion){
		comparacion=(actual1->currCorredor==actual2->currCorredor);
		actual1=actual1->nextCorredor;
		actual2=actual2->nextCorredor;
	}
	return comparacion;
}


//no se como arreglar lo del salto de linea
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
