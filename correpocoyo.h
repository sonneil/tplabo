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

	/*
	 * Crea una nueva carrera
	 */
	CorrePocoyo();

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CorrePocoyo(const CorrePocoyo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CorrePocoyo();

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. Lo agregará al final 
	 */
	void nuevoCorredor(const T&);
	
	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor 
	 */
	void nuevoCorredor(const T&, const T&);
	
	/*
	 * Elimina del pocoyo al que se envía
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T&);
	/*
	 * El corredor pasa al que está adelante 
	 *
	 * PRE: Existe un corredor delante de él y T es un corredor 
	 */
	void sobrepasar(const T&);
	
	/*
	 * Devuelve el corredor que está siendo filmado.
	 *
	 * PRE: Hay adeptos en la CorrePocoyo.
	 */
	const T& corredorFilmado() const;
	
    	/*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de atás 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxPerdedor();
	    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de adelante 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxExitoso();
	
	/*
	 * Devuelve al Primero. 
	 *
	 * PRE: Hay elementos 
	 */
	const T& damePrimero() const;	

	/*
	 * Devuelve la posición del elemento pasado por parámetro. 
	 *
	 * PRE: Existe ese corredor 
	 */
	int damePosicion(const T& ) const;	

	/*
	 * Devuelve el corredor de la posición. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int) const;	

	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	bool esVacia() const;

	
	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	bool operator==(const CorrePocoyo<T>&) const;	
	
	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	ostream& mostrarCorrePocoyo(ostream&) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		Nodo* nextCorredor;
		T currCorredor;
	};
	
	int tamanio;
	Nodo* prmCorredor;
	Nodo* filmando;
};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

// Implementación a hacer por los alumnos.
template<class T>
void CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& cp) {
	this->tamanio = 0;
	if (cp != null) {
		if (cp.tamanio > 0) {
			this->tamanio = cp.tamanio;
			this->prmCorredor = new Nodo;
			// Guardo el primer corredor en un nodo auxiliar
			Nodo* nAux = prmCorredor;
			// Copio todos los nodos de cp
			for (int i = 0; i < cp.tamanio()-1; i++) {
				this->prmCorredor->currCorredor = new T(cp.dameCorredorEnPos(i));
				this->prmCorredor->nextCorredor = new Nodo;
				this->prmCorredor = this->prmCorredor->nextCorredor;
				this->tamanio++;
			}
			// Copio el ultimo nodo de cp y dejo CorrePocoyo en su estado original
			this->prmCorredor->currCorredor = new T(cp.dameCorredorEnPos(cp.tamanio()-1);
			this->prmCorredor->nextCorredor = nAux;
			this->prmCorredor = this->prmCorredor->nextCorredor;
			this->tamanio++;
			// delete nAux; Creo que no va, se borra el contenido del puntero?
		}
	}
}

template<class T>
void CorrePocoyo<T>::~CorrePocoyo() {
	this->tamanio = 0;
	if (cp != null) {
		if (cp.tamanio > 0) {
			this->tamanio = cp.tamanio;
			this->prmCorredor = new Nodo;
			// Borro todos los nodos de cp
			for (int i = 0; i < this->tamanio(); i++) {
				Nodo* nAux = new Nodo;
				this->nAux = this->prmCorredor->nextCorredor;
				delete nAux;
			}
		
		}
	}
	delete tamanio;
}

template<class T>
void CorrePocoyo<T>::seCansa(const T& cansado) {
	Nodo* actual = this->prmCorredor;
	Nodo* nBorrar = this->prmCorredor;
	while(actual->nextCorredor->currCorredor!=cansado) {
		actual = actual->nextCorredor;
	}
	nBorrar = actual->nextCorredor;
	if (this->filmado->currCorredor == nBorrar->currCorredor) {
		this->filmado = actual->nextCorredor->nextCorredor;	
	}
	actual->nextCorredor = actual->nextCorredor->nextCorredor;
	this->tamanio--;
	delete nBorrar;
}

template<class T>
bool CorrePocoyo<T>::esVacia() {
	return (this->tamanio == 0);
}

template<class T>
int CorrePocoyo<T>::tamanio() {
	return this->tamanio;
}

template<class T>
void CorrePocoyo<T>::filmarProxPerdedor() {
	this->filmado = this->filmado->nextCorredor;	
}

template<class T>
const T& CorrePocoyo<T>::corredorFilmado() {
	return filmado->currCorredor;
}

template<class T>
int CorrePocoyo<T>::damePosicion(const T& corredor) {
	int pos = 0;
	Nodo* actual = this->prmCorredor;
	while (actual->currCorredor == corredor) {
		actual = actual->nextCorredor;		
		pos++;
	}
	return pos;
}

template<class T>
ostream& CorrePocoyo<T>::mostrar(ostream& cout) {
	if (this->tamanio == 0) {
		cout << "[]" << endl;	
	} else {
		Nodo* actual = this->prmCorredor;
		cout << "[" << endl;
		for (int i=0; i < this->tamanio; i++) {
			cout << "[" + actual->currCorredor + "]" << endl;
		}
		cout << "]" << endl;
	}
	return cout;
}
#endif //CORREPOCOYO_H_
