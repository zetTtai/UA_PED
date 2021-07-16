#include "tlistacom.h"

//----------------------------------------------------------------//
//----------------------------TLISTANODO--------------------------//
//----------------------------------------------------------------//
void TListaNodo::Copiar(const TListaNodo& nodo)
{
	e= nodo.e;
	anterior= nodo.anterior;
	siguiente= nodo.siguiente;
}
// Constructor por defecto
TListaNodo::TListaNodo ()
{
	e= TComplejo();
	anterior= NULL;
	siguiente= NULL;
}
// Constructor de copia
TListaNodo::TListaNodo (const TListaNodo& nodo)
{
	Copiar(nodo);
}
// Destructor
TListaNodo::~TListaNodo ()
{
	e.~TComplejo();	
}
// Sobrecarga del operador asignación
TListaNodo& TListaNodo::operator=( const TListaNodo& nodo)
{
	if (this != &nodo)
    {
        (*this).~TListaNodo();//Destructor
        this->Copiar(nodo);
    }
	return (*this);
}

//----------------------------------------------------------------//
//----------------------------TLISTAPOS---------------------------//
//----------------------------------------------------------------//
// Constructor por defecto
TListaPos::TListaPos ()
{
	pos= NULL;
}
// Constructor de copia
TListaPos::TListaPos (const TListaPos &position)
{
	pos= position.pos;
}
// Destructor
TListaPos::~TListaPos ()
{
	pos= NULL;
}
// Sobrecarga del operador asignación
TListaPos& TListaPos::operator=(const TListaPos &position)
{
	pos= position.pos;
	return (*this);
} 

//MÉTODOS
// Sobrecarga del operador igualdad
bool TListaPos::operator==(const TListaPos &position)
{
	if(pos == position.pos)
		return true;
	else
		return false;
}
// Sobrecarga del operador desigualdad
bool TListaPos::operator!=(const TListaPos &position)
{
	if(pos != position.pos)
		return true;
	else
		return false;
}
// Devuelve la posición anterior
TListaPos TListaPos::Anterior() const
{
	TListaPos aux;

	if(pos!= NULL)
	{
		if((*pos).anterior != NULL)
			aux.pos= (*pos).anterior;
	}
	
	return aux;
}
// Devuelve la posición siguiente
TListaPos TListaPos::Siguiente() const
{
	TListaPos aux;

	if(pos != NULL)
	{
		if((*pos).siguiente != NULL)
			aux.pos= (*pos).siguiente;
	}
	
	return aux;
}
// Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
bool TListaPos::EsVacia() const
{
	if (pos == NULL)
		return true;
	else
		return false;
}

// //----------------------------------------------------------------//
// //----------------------------TLISTACOM---------------------------//
// //----------------------------------------------------------------//
ostream& operator<< (ostream& os, TListaCom &lista)
{
	TListaPos indice= lista.Primera();
	os << "{";
	while(indice.EsVacia() == false)//Mientras hayan elementos
	{
		if(indice.Siguiente().EsVacia() == false)
			os << lista.Obtener(indice) << " ";
		else
			os << lista.Obtener(indice);//Último elemento	

		indice= indice.Siguiente();//Pasamos a la siguiente posición
	}
	os << "}";

    return os;
}

void TListaCom::Copiar(const TListaCom &lista)
{
	if(lista.EsVacia() == false)
	{
		TListaPos indice;
		indice.pos= lista.ultimo;//Empezamos por el último por como funciona InsCabeza
		//InsCabeza(InsCabeza(ListaVacia() , a) , b) --> [b a]

		while(indice.EsVacia() == false)//Mientras la posición actual sea vacía
		{
			TComplejo complejo= lista.Obtener(indice);
			InsCabeza(complejo);
			indice= indice.Anterior();//Leemos la lista desde el ultimo -> primero
		}
	}
}
// Constructor por defecto
TListaCom::TListaCom ()
{
	primero= NULL;
	ultimo= NULL;
}
// Constructor de copia
TListaCom::TListaCom (TListaCom &lista)
{
	primero= NULL;
	ultimo= NULL;
	Copiar(lista);
}
// Destructor
TListaCom::~TListaCom ()
{
	if(Longitud() == 1)
	{
		delete primero;
		primero= NULL;
		ultimo= NULL;
	}
	else
	{
		TListaPos indice;
		indice.pos= primero;

		while(indice.EsVacia() == false)
		{
			if(indice.Siguiente().EsVacia() == false)//NO es el último
			{
				indice= indice.Siguiente();//Recorrer la lista

				if(indice.Anterior().pos == primero)
				{
					delete indice.Anterior().pos;// == primero
					primero= NULL;
				}
				else
					delete indice.Anterior().pos;
			}
			else
			{
				delete ultimo;
				ultimo= NULL;
				indice.pos= NULL;
			}
		}
	}
}
// Sobrecarga del operador asignación
TListaCom& TListaCom::operator=(const TListaCom &lista)
{
	if(this == &lista)
		return (*this);
	
	if(EsVacia() == false)
		(*this).~TListaCom();	
	
	Copiar(lista);

	return (*this);
}

//MÉTODOS
// Sobrecarga del operador igualdad
bool TListaCom::operator==( TListaCom &lista)
{
	TListaPos indice1, indice2;
	indice1.pos= primero;
	indice2.pos= lista.primero;

	if(Longitud() == lista.Longitud())
	{
		while(indice1.EsVacia() == false && indice1.EsVacia() == false)
		{
			if(Obtener(indice1) != lista.Obtener(indice2))
				return false;
			indice1= indice1.Siguiente();
			indice2= indice2.Siguiente();
		}
	}
	else
		return false;
	return true;
}
// Sobrecarga del operador desigualdad
bool TListaCom::operator!=(TListaCom &lista)
{
	return !(this == &lista);	
}
// Sobrecarga del operador suma
TListaCom TListaCom::operator+(TListaCom &lista)
{
	TListaCom aux= lista;//Guardamos el segundo operando en una variable auxiliar
	TListaPos indice;
	indice.pos= ultimo;

	while(indice.EsVacia() == false)
	{
		aux.InsCabeza(Obtener(indice));
		indice= indice.Anterior();
	}
	return aux;
}
// Sobrecarga del operador resta
TListaCom TListaCom::operator-(TListaCom &lista)//Crear una lista con los que sean distintos
{
	TListaCom aux= (*this);

	TListaPos indice1, indice2;

	indice1.pos= aux.primero;
	indice2.pos= lista.primero;

	while(indice2.EsVacia() == false)
	{
		//Vamos eliminando todos los elementos de "aux" que sean iguales
		while(indice1.EsVacia() == false)//Comparamos el primer elemento de "lista" con toda la lista "aux"
		{
			if(aux.Obtener(indice1) == lista.Obtener(indice2))
				aux.Borrar(indice1);
			
			indice1= indice1.Siguiente();
		}
		indice1.pos= aux.primero;//Volvemos a leer toda la lista "aux"
		indice2= indice2.Siguiente();
	}
	return aux;
}
// Devuelve true si la lista está vacía, false en caso contrario
bool TListaCom::EsVacia() const
{
	if(primero == NULL && ultimo == NULL)
		return true;
	return false;	
}
// Inserta el elemento en la cabeza de la lista
bool TListaCom::InsCabeza(const TComplejo &complejo)
{
	TListaNodo *cabeza= new TListaNodo();//Reservamos memoria
	if(cabeza == NULL)
	{
		cerr << "ERROR: No se ha podido reservar memoria" << endl;
		return false;
	}
	(*cabeza).e= complejo;
	if(EsVacia() == true)
	{
		primero= cabeza;
		ultimo= cabeza;
	}
	else
	{
		(*primero).anterior= cabeza;
		(*cabeza).siguiente= primero;//Cabeza pasa a ser el primer elemento
		primero= cabeza;
	}
	return true;
}
// Inserta el elemento a la izquierda de la posición indicada
bool TListaCom::InsertarI(const TComplejo &complejo, const TListaPos &position)
{
	if(position.EsVacia())
		return false;
	TListaNodo *nodo= new TListaNodo();//Reservamos memoria	
	if(nodo == NULL)
	{
		cerr << "ERROR: No se ha podido reservar memoria" << endl;
		return false;
	}
	//[ANTERIOR] [NODO] [SIGUIENTE] 
	//Al ser InsertarI enlazamos al ANTERIOR, si es vacio -->NODO es la cabeza de la lista
	if(position.Anterior().EsVacia() == false)//NO es la cabeza
	{
		(*position.Anterior().pos).siguiente= nodo;//Anterior() es un TListaPos y su privada pos es un TListaNodo, podemos acceder a sus privadas
		(*nodo).anterior= position.Anterior().pos;//(*nodo) equivale a un TListaNodo, podemos acceder a sus privadas
	}
	else
		primero= nodo;//Cabeza == primero
	//SIGUIENTE = a la posición actual (ha sido desplazado a la derecha)
	(*position.pos).anterior= nodo;
	(*nodo).siguiente= position.pos;
	(*nodo).e= complejo;

	return true;
}
// Inserta el elemento a la derecha de la posición indicada
bool TListaCom::InsertarD(const TComplejo &complejo, const TListaPos &position)
{
	if(position.EsVacia())
		return false;
	TListaNodo *nodo= new TListaNodo();//Reservamos memoria	
	if(nodo == NULL)
	{
		cerr << "ERROR: No se ha podido reservar memoria" << endl;
		return false;
	}
	//[ANTERIOR] [NODO] [SIGUIENTE] 
	//Al ser InsertarI enlazamos al SIGUIENTE, si es vacio -->NODO es el último de la lista
	if(position.Siguiente().EsVacia() == false)//NO es el último
	{
		(*position.Siguiente().pos).anterior= nodo;
		(*nodo).siguiente= position.Siguiente().pos;
	}
	else
		ultimo= nodo;
	//SIGUIENTE = a la posición actual (ha sido desplazado a la derecha)
	(*position.pos).siguiente= nodo;
	(*nodo).anterior= position.pos;
	(*nodo).e= complejo;

	return true;	
}
// Busca y borra la primera ocurrencia del elemento
bool TListaCom::Borrar(const TComplejo &complejo)
{
	TListaPos indice;
	indice.pos= primero;

	while(indice.EsVacia() == false)
	{
		if(Obtener(indice) == complejo)	
		{
			Borrar(indice);//Borramos respecto a la posición/indice
			return true;//Salimos del bucle
		}
		
		indice= indice.Siguiente();//Recorremos la lista cambiado el índice
	}
	return false;
}
// Busca y borra todas las ocurrencias del elemento
bool TListaCom::BorrarTodos(const TComplejo &complejo)
{
	TListaPos indice;
	indice.pos= primero;
	bool eliminado= false;

	while(indice.EsVacia() == false)
	{
		if(Obtener(indice) == complejo)
		{
			eliminado= true;
			TListaPos aux;//Puntero auxiliar para saber cual borrar
			if(indice.Siguiente().EsVacia() == false)
			{
				indice= indice.Siguiente();//Nos situamos en el siguiente (recorrer la lista)
				aux= indice.Anterior();//Guardamos en la auxiliar el anterior (el que queremos eliminar)
			}
			else//Último elemento
				aux= indice;//Eliminamos el actual (fin de la lista, no hay siguiente)
			
			Borrar(aux);//Borrar respecto a su posición
		}
		else
			indice= indice.Siguiente();//Seguimos recorriendo la lista
	}
	return eliminado;	
}
// Borra el elemento que ocupa la posición indicada
bool TListaCom::Borrar(const TListaPos &position)
{
	TListaPos actual= position;//Guardamos la posición del Nodo a eliminar
	if(position.EsVacia() == true)
		return false;//No se puede borrar lo que no existe

	//Nodo está en medio (Lo marginamos)
	if(actual.Siguiente().EsVacia() == false && actual.Anterior().EsVacia() == false)
	{	
		//Nodo que es el anterior al que queremos eliminar
		(*actual.Anterior().pos).siguiente= actual.Siguiente().pos;//Lo enlazamos con el SIGUIENTE del que vamos a eliminar
		//Nodo que es el siguiente al que queremos eliminar
		(*actual.Siguiente().pos).anterior= actual.Anterior().pos;//Lo enlazamos con el ANTERIOR del que vamos a eliminar
	}
	//Último nodo
	else if(actual.Siguiente().EsVacia() == true && actual.Anterior().EsVacia() == false)
	{
		//Nodo que es el anterior al que queremos eliminar. SU SIGUIENTE
		(*actual.Anterior().pos).siguiente= NULL;//Es el que queremos eliminar
		ultimo= actual.Anterior().pos;
	}
	//Es la cabeza
	else if(actual.Siguiente().EsVacia() == false && actual.Anterior().EsVacia() == true)
	{
		//Nodo que es el siguiente al que queremos eliminar. SU ANTERIOR
		(*actual.Siguiente().pos).anterior= NULL;//Es el que queremos eliminar
		primero= actual.Siguiente().pos;
	}
	//Único elemento de la lista
	else if(actual.Siguiente().EsVacia() == true && actual.Anterior().EsVacia() == true)
	{
		primero= NULL;
		ultimo= NULL;
	}
	//Liberamos memoria
	delete actual.pos;
	actual.pos= NULL;

	return true;	
}
// Obtiene el elemento que ocupa la posición indicada
TComplejo TListaCom::Obtener(const TListaPos &position) const
{
	TComplejo aux= TComplejo();
	if(position.EsVacia() == true)
		return aux;//Devolvemos un TComplejo vacio
	return (*position.pos).e;//*TListaPos.pos equivale a un TListaNodo
}
// Devuelve true si el elemento está en la lista, false en caso contrario
bool TListaCom::Buscar(const TComplejo &complejo) const
{	
	TListaPos indice;
	indice.pos= primero;

	while(indice.EsVacia() == false)
	{
		if(Obtener(indice) == complejo)	
			return true;
		
		indice= indice.Siguiente();//Recorremos la lista cambiado el índice
	}
	return false;	
}
// Devuelve la longitud de la lista
int TListaCom::Longitud()
{
	int contador= 0;
	TListaPos indice;
	indice.pos= primero;

	while(indice.EsVacia() == false)
	{
		contador++;
		indice= indice.Siguiente();//Recorremos la lista cambiado el índice
	}
	return contador;
}
// Devuelve la primera posición en la lista
TListaPos TListaCom::Primera() const
{
	TListaPos first;
	first.pos= primero;
	return first;
}
// Devuelve la última posición en la lista
TListaPos TListaCom::Ultima() const
{
	TListaPos last;
	last.pos= ultimo;
	return last;
}