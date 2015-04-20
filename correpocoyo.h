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
CorrePocoyo<T>::CorrePocoyo(){
	this.tamanioc=0;
	this.prmCorredor=NULL;
	this.filmando=NULL;
}

template<class T>
void CorrePocoyo<T>::nuevoCorredor(const T& nuevo){
	Nodo * nuevoNodo = new Nodo;
	nuevoNodo->nextCorredor=this.prmCorredor;
	nuevoNodo->currCorredor=new T(nuevo);
	if(this.tamanioc==0){
		this.filmando=nuevoNodo;
	}else{
		Nodo * actual=this.prmCorredor;
		while((actual->nextCorredor->currCorredor)!=(this->prmCorredor->currCorredor)){
			actual=(actual->nextCorredor);
		}
		actual->nextCorredor=nuevoNodo;
	}
	tamanioc++;
}

template<class T>
int CorrePocoyo<T>::tamanio() const{
	return this.tamanioc; 
}

template<class T>
bool CorrePocoyo<T>::esVacia() const{
	return this.tamanioc==0; 
}

#endif //CORREPOCOYO_H_
