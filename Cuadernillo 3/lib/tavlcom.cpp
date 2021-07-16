#include "tavlcom.h"

ostream& operator<<(ostream &os, TAVLCom &arbol)
{
	TVectorCom aux= arbol.Inorden();
	os << aux;
	return os;
}
//-------------------------------------------------------------//
//----------------------------TAVLCOM--------------------------//
//-------------------------------------------------------------//


//AUXILIAR : Devuelve una copia del arbol pasado por parámetros
void TAVLCom::Copiar(const TAVLCom &arbol)
{
	if(arbol.raiz != NULL)
	{
		TNodoAVL *aux= new TNodoAVL();
		aux->item= arbol.raiz->item;
		raiz= aux;
		//Llamada recursiva
		raiz->iz.Copiar(arbol.raiz->iz);
		raiz->de.Copiar(arbol.raiz->de);
	}
	else
		raiz= NULL;
}

// Constructor por defecto
TAVLCom::TAVLCom ()
{
	raiz= NULL;
}
// Constructor de copia
TAVLCom::TAVLCom (const TAVLCom &arbol)
{
	Copiar(arbol);
}
// Destructor
TAVLCom::~TAVLCom ()
{
	if(raiz != NULL)
	{
		raiz->~TNodoAVL();
		delete raiz;
		raiz= NULL;
	}
}
// Sobrecarga del operador asignación
TAVLCom& TAVLCom::operator=(const TAVLCom &arbol)
{
	if(this != &arbol)
	{
		(*this).~TAVLCom();
		this->Copiar(arbol);
	}
	return *this;
}

// MÉTODOS

// Sobrecarga del operador igualdad
bool TAVLCom::operator==(TAVLCom &arbol)
{
	TVectorCom original= Preorden();
	TVectorCom vector= arbol.Preorden();

	if(original == vector)
		return true;
	else
		return false;
}
// Sobrecarga del operador desigualdad
bool TAVLCom::operator!=(TAVLCom &arbol)
{
	TVectorCom original= Preorden();
	TVectorCom vector= arbol.Preorden();

	if(original == vector)
		return false;
	else
		return true;
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TAVLCom::EsVacio() const
{
	if(raiz == NULL)
		return true;
	else
		return false;	
}

//-------------------------------------//
//--------------IZQUIERDA--------------//
//-------------------------------------//
void TAVLCom::IzquierdaIzquierda()
{
	//cout << "Rotación II" << endl;
	TNodoAVL* RaizJ;

	//J= Subarbol izquierdo original
    RaizJ= raiz->iz.raiz;
    raiz->iz.raiz= NULL;

    //Subarbol izquierdo original= Subarbol Derecho J
    raiz->iz.raiz= RaizJ->de.raiz;
    RaizJ->de.raiz= NULL;

    //Subarbol derecho de J= arbol original
    RaizJ->de.raiz= raiz;
    raiz= NULL;

    //Restablecemos el equilibrio
    RaizJ->fe= 0; 
    RaizJ->de.raiz->fe= 0;

    //Igualamos el arbol original a J
    raiz= RaizJ;
    RaizJ= NULL;
}

void TAVLCom::IzquierdaDerecha()
{
	//cout << "Rotación ID" << endl;
	TNodoAVL* RaizJ, *RaizK;
	int aux;

	//J= Subarbol izquierdo original
    RaizJ= raiz->iz.raiz;
    raiz->iz.raiz= NULL;

    //K= Subarbol derecho orignal
    RaizK= RaizJ->de.raiz;
    RaizJ->de.raiz= NULL;

    //Guardamos el factor de equilibrio actual en una auxiliar
    aux= RaizK->fe;

    //Subarbol izquierdo original= subarbol derecho de K
    raiz->iz.raiz= RaizK->de.raiz;
    RaizK->de.raiz= NULL;

    //Subarbol derecho de J= subarbol izquierdo de K
    RaizJ->de.raiz= RaizK->iz.raiz;
    RaizK->iz.raiz= NULL;

    //Subarbol izquierdo de K= arbol j
    RaizK->iz.raiz= RaizJ;
    RaizJ= NULL;

    //Subarbol derecho de K= arbol original
    RaizK->de.raiz= raiz;
    raiz= NULL;

    //Restablecemos el equilibrio
    RaizK->fe= 0;

    //Actualizamos el equilibrio en función del factor de equilibrio almacenado
    switch(aux)
    {
        case -1:
            RaizK->iz.raiz->fe= 0;
            RaizK->de.raiz->fe= 1;
            break;
        case 1:
            RaizK->iz.raiz->fe= -1;
            RaizK->de.raiz->fe= 0;
            break;
        case 0:
            RaizK->iz.raiz->fe= 0;
            RaizK->de.raiz->fe= 0;
            break;
    }

    //Igualamos el arbol original al arbol J
    raiz= RaizK;
    RaizK= NULL;
}

//-------------------------------------//
//---------------DERECHA---------------//
//-------------------------------------//
void TAVLCom::DerechaDerecha()
{
	//cout << "Rotación DD" << endl;
	TNodoAVL* RaizJ;
	//Mover (J, HijoDe(I));
    RaizJ= raiz->de.raiz;
    raiz->de.raiz= NULL;

    //Mover (HijoDe(I), HijoIz(J));
    raiz->de.raiz= RaizJ->iz.raiz;
    RaizJ->iz.raiz= NULL;

    // Mover (HijoIz (J), I);
    RaizJ->iz.raiz= raiz;
    raiz= NULL;

    //FE (J) = 0; FE (HijoIz (J))=0;
    RaizJ->fe= 0; 
    RaizJ->iz.raiz->fe= 0;

    //Mover (I,J);
    raiz= RaizJ;
    RaizJ= NULL;
}

void TAVLCom::DerechaIzquierda()
{
	//cout << "Rotación DI" << endl;
	TNodoAVL* RaizJ, *RaizK;
	int aux;

	//Mover (J, HijoDe (I));
    RaizJ= raiz->de.raiz;
    raiz->de.raiz= NULL;

    //Mover (K, HijoIZ (J));
    RaizK= RaizJ->iz.raiz;
    RaizJ->iz.raiz= NULL;

    //E2 = FE (K);
    aux= RaizK->fe;

    //Mover (HijoDE (I), HijoIz(K));
    raiz->de.raiz=RaizK->iz.raiz;
    RaizK->iz.raiz=NULL;

    //Mover (HijoIz (J), HijoDe(K));
    RaizJ->iz.raiz= RaizK->de.raiz;
    RaizK->de.raiz= NULL;

    //Mover (HijoDe (K), J);
    RaizK->de.raiz= RaizJ;
    RaizJ= NULL;

    //Mover (HijoIz (K), I);
    RaizK->iz.raiz= raiz;
    raiz= NULL;

    //FE (K) = 0;
    RaizK->fe= 0;

    switch(aux)
    {
        case -1:
            RaizK->de.raiz->fe= 1;
            RaizK->iz.raiz->fe= 0;
            break;
        case 1:
            RaizK->de.raiz->fe= 0;
            RaizK->iz.raiz->fe= -1;
            break;
        case 0:
            RaizK->de.raiz->fe= 0;
            RaizK->iz.raiz->fe= 0;
            break;
    }

    //Mover (I, K);
    raiz= RaizK;
    RaizK= NULL;
}


void TAVLCom::ActualizarFE()
{
	if(!EsVacio())
	{
		//Actualizamos el factor de equilibrio
		raiz->fe= raiz->de.Altura() - raiz->iz.Altura();
		raiz->iz.ActualizarFE();
		raiz->de.ActualizarFE();
	}
}

void TAVLCom::EquilibrarArbol()
{
	if(!raiz->iz.EsVacio())
		raiz->iz.EquilibrarArbol();

	if(!raiz->de.EsVacio())
		raiz->de.EquilibrarArbol();

	//NODO HOJA
	switch(raiz->fe)
	{
		case 2:
			if(raiz->de.raiz->fe == 0 || raiz->de.raiz->fe == 1)
				DerechaDerecha();

			else if(raiz->de.raiz->fe == -1)
				DerechaIzquierda();

			break;
		case -2:
			if(raiz->iz.raiz->fe == 0 || raiz->iz.raiz->fe == -1)
				IzquierdaIzquierda();

			else if(raiz->iz.raiz->fe ==  1)
				IzquierdaDerecha();

			break;
	}
}

bool TAVLCom::InsertarAux(const TComplejo &complejo, bool &crece)
{
	bool creceHijoIz, creceHijoDe, OK;
	creceHijoIz= creceHijoDe= OK= false;

	if(EsVacio())
	{   //Insertamos el nodo raíz
		raiz= new TNodoAVL();//Reservamos memoria
		raiz->item= complejo;
		crece= OK= true;
		return OK;
	}
	else//No está vacío
	{
		if(!Buscar(complejo))//No se ha encontrado
		{
			//Implementar Buscar(): Si ya está incluido-->Devolver false
			if(Raiz().Mod() != complejo.Mod())
			{
				if(Raiz().Mod() > complejo.Mod())//Añadir izquierda
					OK= raiz->iz.Insertar(complejo);
				else//Añadir derecha
					OK= raiz->de.Insertar(complejo);
			}
			else//Tienen mismo Módulo
			{
				if(Raiz().Re() != complejo.Re())
				{
					if(Raiz().Re() > complejo.Re())//Añadir izquierda
						OK= raiz->iz.Insertar(complejo);
					else//Añadir derecha
						OK= raiz->de.Insertar(complejo);
				}
				else//Tienen misma parte real
				{
					if(Raiz().Im() > complejo.Im())//Añadir izquierda
						OK= raiz->iz.Insertar(complejo);
					else//Añadir derecha
						OK= raiz->de.Insertar(complejo);
				}//NO se puede dar el caso de que sean iguales
			}
		}
		else
			crece= false;//Ya ha sido insertado
	}
	//Actualización de factores de equilibrio
	if(OK == true)
	{
		ActualizarFE();
		EquilibrarArbol();
	}

	return OK;
}
// Inserta el elemento TComplejo en el árbol
bool TAVLCom::Insertar(const TComplejo &complejo)
{
	bool crece= false;
	return InsertarAux(complejo, crece);	
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TAVLCom::Buscar(const TComplejo &complejo) const
{
	if(!EsVacio())//No está vacío el árbol/Fin del árbol
	{
		if(raiz->item == complejo)
			return true;
		else
		{
			//Llamada recursiva
			if(raiz->iz.Buscar(complejo))//Ha sido encontrado en el subarbol izquierdo
				return true;
			if(raiz->de.Buscar(complejo))//Ha sido encontrado en el subarbol derecho
				return true;
		}
	}
	else 
		return false;
}
//Método auxiliar y privado del Método Borrar (Busca el mayor por la izquierda)
void TAVLCom::MaxIzq(const TAVLCom &arbol, TComplejo& complejo)
{
	if(!EsVacio())
	{
		if(arbol.raiz->de.EsVacio() == false)//Existe nodo derecha (Es un número más grande)	
		{
			complejo= arbol.raiz->de.raiz->item;
			MaxIzq(arbol.raiz->de, complejo);
		}
		else
			complejo= arbol.Raiz();
	}
}
bool TAVLCom::BorrarAux(const TComplejo &complejo, bool &decrece)
{
	bool decreceHijoIz, decreceHijoDe, OK;
	decreceHijoIz= decreceHijoDe= OK= false;

	if(!EsVacio())
	{
		if(Buscar(complejo))//Ha sido encontrado
		{
			if(Raiz() == complejo)
			{
				//3 Casos: Nodo Hoja; 1 Hijo, 2 Hijos(Mayor de la izquierda)
				if(raiz->de.EsVacio())
				{
					if(raiz->iz.EsVacio())//NODO HOJA
					{
						raiz->~TNodoAVL();
						raiz= NULL;
						decrece= OK= true;
						return OK;
					}
					else//1 HIJO(izquierda)
					{
						raiz= raiz->iz.raiz;//Movemos TODO el subarbol izquierdo al nodo raiz
						decrece= OK= true;
						return true;
					}
				}
				else
				{
					if(raiz->iz.EsVacio())//1 HIJO(derecha)
					{
						raiz= raiz->de.raiz;
						decrece= OK= true;
						return true;
					}
					else//2 HIJOS MaxIzq
					{
						TComplejo maxIzq;
						MaxIzq(raiz->iz, maxIzq);
						OK= raiz->iz.BorrarAux(maxIzq, decreceHijoIz);
						raiz->item= maxIzq;
					}
				}
			}
			else
			{
				if(raiz->iz.BorrarAux(complejo, decreceHijoIz))
					OK= true;
				if(raiz->de.BorrarAux(complejo, decreceHijoDe))
					OK= true;
			}
		}
	}
	//Actualización de factores de equilibrio
	if(OK == true)
	{
		ActualizarFE();
		EquilibrarArbol();
	}

	return OK;
}
// Borra un TComplejo del árbol AVL
bool TAVLCom::Borrar(const TComplejo &complejo)
{
	bool decrece= false;
	return BorrarAux(complejo, decrece);
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TAVLCom::Altura() const
{
	int alturaI, alturaD;
	if(!EsVacio())
	{
		alturaI= raiz->iz.Altura();
		alturaD= raiz->de.Altura();
		if(alturaI < alturaD)
			return 1 + alturaD;

		else
			return 1 + alturaI;
	}
	else
		return 0;
}
// Devuelve el elemento TComplejo raíz del árbol AVL
TComplejo TAVLCom::Raiz() const
{
	if(EsVacio())
		return TComplejo();
	else
		return raiz->item;
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TAVLCom::Nodos() const
{
	if(!EsVacio())
		return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
	else
		return 0;
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TAVLCom::NodosHoja() const
{
	if(!EsVacio())
	{
		if(raiz->iz.EsVacio() && raiz->de.EsVacio())//Ambos están vacios por tanto es una hoja
			return 1;
		else
			return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
	}	
	else
		return 0;
}

// AUXILIAR : Devuelve el recorrido en inorden
void TAVLCom::InordenAux(TVectorCom &vector, int &pos)
{
	if(!EsVacio())
	{
		raiz->iz.InordenAux(vector, pos);
		vector[pos]= Raiz();
		pos++;
		raiz->de.InordenAux(vector, pos);
	}
}
// AUXILIAR : Devuelve el recorrido en preorden
void TAVLCom::PreordenAux(TVectorCom &vector, int &pos)
{
	if(!EsVacio())
	{
		vector[pos]= Raiz();
		pos++;
		raiz->iz.PreordenAux(vector, pos);
		raiz->de.PreordenAux(vector, pos);
	}
}
// AUXILIAR : Devuelve el recorrido en postorden
void TAVLCom::PostordenAux(TVectorCom &vector, int &pos)
{
	if(!EsVacio())
	{
		raiz->iz.PostordenAux(vector, pos);
		raiz->de.PostordenAux(vector, pos);
		vector[pos]= Raiz();
		pos++;
	}
}

// Devuelve el recorrido en inorden sobre un vector
TVectorCom TAVLCom::Inorden()
{
	// Posición en el vector que almacena el recorrido
	int posicion = 1;
	// Vector del tamaño adecuado para almacenar todos los nodos
	TVectorCom vector(Nodos());
	InordenAux(vector, posicion);
	return vector;
}
// Devuelve el recorrido en preorden sobre un vector
TVectorCom TAVLCom::Preorden()
{
	// Posición en el vector que almacena el recorrido
	int posicion = 1;
	// Vector del tamaño adecuado para almacenar todos los nodos
	TVectorCom vector(Nodos());
	PreordenAux(vector, posicion);
	return vector;
}
// Devuelve el recorrido en postorden sobre un vector
TVectorCom TAVLCom::Postorden()
{
	// Posición en el vector que almacena el recorrido
	int posicion = 1;
	// Vector del tamaño adecuado para almacenar todos los nodos
	TVectorCom vector(Nodos());
	PostordenAux(vector, posicion);
	return vector;
}

//-------------------------------------------------------------//
//----------------------------TNODOAVL-------------------------//
//-------------------------------------------------------------//

// Constructor por defecto
TNodoAVL::TNodoAVL ():item(),iz(),de()
{
	fe= 0;
}
// Constructor de copia
TNodoAVL::TNodoAVL (const TNodoAVL &nodo):item(nodo.item),iz(nodo.iz),de(nodo.de)
{
	fe= nodo.fe;
}
// Destructor (por layering)
TNodoAVL::~TNodoAVL ()
{
	fe= 0;
}
// Sobrecarga del operador asignación
TNodoAVL& TNodoAVL::operator=(const TNodoAVL &nodo)
{
	if(this != &nodo)
	{
		(*this).~TNodoAVL();//Destructor
        TNodoAVL(nodo);
	}
	return *this;
}
