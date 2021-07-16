#include "tabbcom.h"

//-------------------------------------------------------------//
//----------------------------TABBCOM--------------------------//
//-------------------------------------------------------------//
ostream& operator<<(ostream &os, TABBCom &arbol)
{
	os << arbol.Niveles();
	return os;
}
void TABBCom::Copiar(const TABBCom& arbol)
{
	if(arbol.nodo != NULL)
	{
		TNodoABB *aux= new TNodoABB();
		aux->item= arbol.nodo->item;
		nodo= aux;
		//Llamada recursiva
		nodo->iz.Copiar(arbol.nodo->iz);
		nodo->de.Copiar(arbol.nodo->de);
	}
	else
		nodo= NULL;
}
// AUXILIAR : Devuelve el recorrido en inorden
void TABBCom::InordenAux(TVectorCom &vector, int &pos)//IRD
{
	if(!EsVacio())
	{
		nodo->iz.InordenAux(vector, pos);
		vector[pos++]= Raiz();
		nodo->de.InordenAux(vector, pos);
	}

}
// AUXILIAR : Devuelve el recorrido en preorden
void TABBCom::PreordenAux(TVectorCom &vector, int &pos)//RID
{
	if(!EsVacio())
	{
		vector[pos++]= Raiz();
		nodo->iz.PreordenAux(vector, pos);
		nodo->de.PreordenAux(vector, pos);
	}
}
// AUXILIAR : Devuelve el recorrido en postorden
void TABBCom::PostordenAux(TVectorCom &vector, int &pos)//IDR
{
	if(!EsVacio())
	{
		nodo->iz.PostordenAux(vector, pos);
		nodo->de.PostordenAux(vector, pos);
		vector[pos++]= Raiz();
	}
}
// Constructor por defecto
TABBCom::TABBCom()
{
	nodo= NULL;
}
// Constructor de copia
TABBCom::TABBCom (const TABBCom& arbol)
{
	Copiar(arbol);
}
// Destructor
TABBCom::~TABBCom ()
{
	if(nodo != NULL)
	{
		nodo->~TNodoABB();//Primero llamamos al destructor de TNodoABB
		delete nodo;
		nodo= NULL;
	}
}
// Sobrecarga del operador asignación
TABBCom& TABBCom::operator=(const TABBCom &arbol)
{
	if(this != &arbol)
	{
		(*this).~TABBCom();//Destructor
		this->Copiar(arbol);
	}
	return *this;
}

//MÉTODOS

bool TABBCom::ComparaArboles(const TABBCom &arbol) const
{
	if(EsVacio())
		return true;//Caso base
	else
		return arbol.Buscar(Raiz()) && nodo->iz.ComparaArboles(arbol) && nodo->de.ComparaArboles(arbol);

}
// Sobrecarga del operador igualdad
bool TABBCom::operator==(const TABBCom &arbol) const
{
	if(arbol.Nodos() != Nodos())
		return false;
	else
		return ComparaArboles(arbol);
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TABBCom::EsVacio() const
{
	if(nodo == NULL)
		return true;
	else
		return false;
}
// Inserta el elemento en el árbol
bool TABBCom::Insertar(const TComplejo &complejo)
{
	if(EsVacio())
	{   //Insertamos el nodo raíz
		nodo= new TNodoABB();//Reservamos memoria
		nodo->item= complejo;
		return true;
	}
	else//No está vacío
	{
		if(!Buscar(complejo))//No se ha encontrado
		{
			//Implementar Buscar(): Si ya está incluido-->Devolver false
			if(Raiz().Mod() != complejo.Mod())
			{
				if(Raiz().Mod() > complejo.Mod())//Añadir izquierda
					nodo->iz.Insertar(complejo);
				else//Añadir derecha
					nodo->de.Insertar(complejo);
			}
			else//Tienen mismo Módulo
			{
				if(Raiz().Re() != complejo.Re())
				{
					if(Raiz().Re() > complejo.Re())//Añadir izquierda
						nodo->iz.Insertar(complejo);
					else//Añadir derecha
						nodo->de.Insertar(complejo);
				}
				else//Tienen misma parte real
				{
					if(Raiz().Im() > complejo.Im())//Añadir izquierda
						nodo->iz.Insertar(complejo);
					else//Añadir derecha
						nodo->de.Insertar(complejo);
				}//NO se puede dar el caso de que sean iguales
			}
		}
		else
			return false;//Ya ha sido insertado
	}
	return true;
}
//Método auxiliar y privado del Método Borrar (Busca el mayor por la izquierda)
void TABBCom::MaxIzq(const TABBCom &arbol, TComplejo& complejo)
{
	if(!EsVacio())
	{
		if(arbol.nodo->de.EsVacio() == false)//Existe nodo derecha (Es un número más grande)	
		{
			complejo= arbol.nodo->de.nodo->item;
			MaxIzq(arbol.nodo->de, complejo);
		}
		else
			complejo= arbol.Raiz();
	}
}
// Borra el elemento en el árbol
bool TABBCom::Borrar(const TComplejo &complejo)
{
	TComplejo c(24,0);
	bool OK= false;

	if(!EsVacio())
	{
		if(Buscar(complejo))//Ha sido encontrado
		{
			if(Raiz() == complejo)
			{
				//3 Casos: Nodo Hoja; 1 Hijo, 2 Hijos(Mayor de la izquierda)
				if(nodo->de.EsVacio())
				{
					if(nodo->iz.EsVacio())//NODO HOJA
					{
						nodo->~TNodoABB();
						nodo= NULL;
						OK= true;
						return true;
					}
					else//1 HIJO(izquierda)
					{
						nodo= nodo->iz.nodo;
						OK= true;
						return true;
					}
				}
				else
				{
					if(nodo->iz.EsVacio())//1 HOJA(derecha)
					{
						nodo= nodo->de.nodo;
						OK= true;
						return true;
					}
					else//2 HIJOS MaxIzq
					{
						TComplejo maxIzq;
						MaxIzq(nodo->iz, maxIzq);
						OK= nodo->iz.Borrar(maxIzq);
						nodo->item= maxIzq;
					}
				}
			}
			else
			{
				if(nodo->iz.Borrar(complejo))
					return true;
				if(nodo->de.Borrar(complejo))
					return true;
			}
		}
		else
			return false;//No ha sido encontrado en el árbol
	}
	else
		return false;//El arbol está vacio, no se puede eliminar
	return OK;
	
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBCom::Buscar(const TComplejo &complejo) const
{
	if(!EsVacio())//No está vacío el árbol/Fin del árbol
	{
		//cout << "Comparando con: " << nodo->item << endl;
		if(nodo->item == complejo)
			return true;
		else
		{
			//Llamada recursiva
			if(nodo->iz.Buscar(complejo))//Ha sido encontrado en el subarbol izquierdo
				return true;
			if(nodo->de.Buscar(complejo))//Ha sido encontrado en el subarbol derecho
				return true;
		}
	}
	else 
		return false;
}
// Devuelve el elemento en la raíz del árbol
TComplejo TABBCom::Raiz() const
{
	if(EsVacio())//Está vacio_>TComplejo vacío
		return TComplejo();
	else
		return nodo->item;
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TABBCom::Altura() const
{
	int alturaI, alturaD;
	if(!EsVacio())
	{
		alturaI= nodo->iz.Altura();
		alturaD= nodo->de.Altura();
		if(alturaI < alturaD)
		{
			return 1 + alturaD;
		}
		else
			return 1 + alturaI;
	}
	else
		return 0;
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TABBCom::Nodos() const
{
	if(!EsVacio())
		return 1 + nodo->iz.Nodos() + nodo->de.Nodos();
	else
		return 0;
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TABBCom::NodosHoja() const
{
	if(!EsVacio())
	{
		if(nodo->iz.EsVacio() && nodo->de.EsVacio())//Ambos están vacios por tanto es una hoja
			return 1;
		else
			return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
	}	
	else
		return 0;
}
// Devuelve el recorrido en inorden
TVectorCom TABBCom::Inorden()//IRD
{
	int posicion= 1;
	TVectorCom vector(Nodos());
	InordenAux(vector,posicion);

	return vector;
}
// Devuelve el recorrido en preorden
TVectorCom TABBCom::Preorden()//RID
{
	int posicion= 1;
	TVectorCom vector(Nodos());
	PreordenAux(vector,posicion);

	return vector;
}
// Devuelve el recorrido en postorden
TVectorCom TABBCom::Postorden()//IDR
{
	int posicion= 1;
	TVectorCom vector(Nodos());
	PostordenAux(vector,posicion);

	return vector;
}
// Devuelve el recorrido en niveles
TVectorCom TABBCom::Niveles()
{
	queue<TABBCom> cola;
	TABBCom aux;
	TVectorCom vector(Nodos());
	cola.push(*this);//Encolamos todo el arbol
	int pos= 1;
	while(!cola.empty())
	{
		aux= cola.front();//Cabeza
		vector[pos++]= aux.Raiz();
		cola.pop();//Desencolar
		if(!aux.nodo->iz.EsVacio())
			cola.push(aux.nodo->iz);
		if(!aux.nodo->de.EsVacio())
			cola.push(aux.nodo->de);
	}

	return vector;
}

//--------------------------------------------------------------//
//----------------------------TNODOABB--------------------------//
//--------------------------------------------------------------//

// Constructor por defecto
TNodoABB::TNodoABB ():item(),iz(),de()
{
}
// Constructor de copia
TNodoABB::TNodoABB (const TNodoABB &nodo):item(nodo.item),iz(nodo.iz),de(nodo.de)
{
}
// Destructor
TNodoABB::~TNodoABB ()//Destructor por Layering
{
}
// Sobrecarga del operador asignación
TNodoABB& TNodoABB::operator=(const TNodoABB &nodo)
{
	return *this;
}