#ifndef _TAVLCOM_H_
#define _TAVLCOM_H_

#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"
using namespace std;

class TNodoAVL;

class TAVLCom
{
	friend class TNodoAVL;

	// Sobrecarga del operador salida
	friend ostream & operator<<(ostream &, TAVLCom &);

	private:
		// Puntero al nodo
		TNodoAVL *raiz;
		// AUXILIAR : Devuelve el recorrido en inorden
		void InordenAux(TVectorCom &, int &);
		// AUXILIAR : Devuelve el recorrido en preorden
		void PreordenAux(TVectorCom &, int &);
		// AUXILIAR : Devuelve el recorrido en postorden
		void PostordenAux(TVectorCom &, int &);
		//AUXILIAR : Devuelve una copia del arbol pasado por parámetros
		void Copiar(const TAVLCom &);
		
		//Rotación Izquierda izquierda
		void IzquierdaIzquierda();
		//Rotación Izquierda derecha
		void IzquierdaDerecha();
		//Rotación Derecha derecha
		void DerechaDerecha();
		//Rotación Derecha izquierda
		void DerechaIzquierda();

		//Método con el cual actualizamos todos los FE de todos los nodos del árbol
		void ActualizarFE();
		//Método en el que se decide que rotación realizar con respecto al FE
		void EquilibrarArbol();

		//AUXILIAR : Inserta hijos manteniendo el equilibrio
		bool InsertarAux(const TComplejo &, bool &);
		//AUXILIAR : Busca el máximo elemento por la izquierda
		void MaxIzq(const TAVLCom &, TComplejo &);
		//AUXILIAR : Borra hijos manteniendo el equilibrio
		bool BorrarAux(const TComplejo &, bool &);
	public:
		// Constructor por defecto
		TAVLCom ();
		// Constructor de copia
		TAVLCom (const TAVLCom &);
		// Destructor
		~TAVLCom ();
		// Sobrecarga del operador asignación
		TAVLCom & operator=(const TAVLCom &);
		// MÉTODOS
		// Sobrecarga del operador igualdad
		bool operator==(TAVLCom &);
		// Sobrecarga del operador desigualdad
		bool operator!=(TAVLCom &);
		// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
		bool EsVacio() const;
		// Inserta el elemento TComplejo en el árbol
		bool Insertar(const TComplejo &);
		// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
		bool Buscar(const TComplejo &) const;
		// Borra un TComplejo del árbol AVL
		bool Borrar(const TComplejo &);
		// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
		int Altura() const;
		// Devuelve el elemento TComplejo raíz del árbol AVL
		TComplejo Raiz() const;
		// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
		int Nodos() const;
		// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
		int NodosHoja() const;
		// Devuelve el recorrido en inorden sobre un vector
		TVectorCom Inorden();
		// Devuelve el recorrido en preorden sobre un vector
		TVectorCom Preorden();
		// Devuelve el recorrido en postorden sobre un vector
		TVectorCom Postorden();
};

class TNodoAVL
{
	friend class TAVLCom;
	private:
		// El elemento del nodo
		TComplejo item;
		// Subárbol izquierdo y derecho
		TAVLCom iz, de;
		// Factor de equilibrio
		int fe;
	public:
		// Constructor por defecto
		TNodoAVL ();
		// Constructor de copia
		TNodoAVL (const TNodoAVL &);
		// Destructor
		~TNodoAVL ();
		// Sobrecarga del operador asignación
		TNodoAVL & operator=(const TNodoAVL &);
};

#endif