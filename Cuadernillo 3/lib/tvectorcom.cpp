#include "tvectorcom.h"

ostream& operator<< (ostream& os, const TVectorCom& original)
{
    TVectorCom vector= original;
    os << "[";
    for(int i=0; i < vector.tamano; i++)
    {
        os << "(" << (i + 1) << ") ";
        os << vector.c[i];
        if(i < vector.tamano - 1)
            os << ", ";
    }
        
    os << "]";
    return os;
}

void TVectorCom::Copiar(const TVectorCom& vector)
{
    c= new TComplejo[vector.tamano];
    tamano= vector.tamano;
    for(int i=0; i < vector.tamano; i++)  
        c[i]= vector.c[i];
}

//Constructor por defecto
TVectorCom::TVectorCom()
{
    c= NULL;
    tamano= 0;
}
//Constructor a partir de tamaño
TVectorCom::TVectorCom(const int tam)
{
    if(tam <= 0)
    {
        c= NULL;
        tamano= 0;
    }
    else
    {
        c= new TComplejo[tam];
        tamano= tam;
    }
}
//Constructor de copia
TVectorCom::TVectorCom(const TVectorCom& vector)
{
    Copiar(vector);
}
//Destructor
TVectorCom::~TVectorCom()
{
    tamano= 0;

    if(c != NULL)
    {
        delete [] c;
        c= NULL;
    }   
}
//Sobregarca de operador de asignación
TVectorCom& TVectorCom::operator= (const TVectorCom& vector)
{
    if (this != &vector)
    {
        (*this).~TVectorCom();//Destructor
        this->Copiar(vector);
    }
    return *this;   
}

// Sobrecarga del operador igualdad
bool TVectorCom::operator== (TVectorCom& vector) const
{
    bool check= true;
    if(tamano == vector.Tamano())
    {
        for(int i=0; i < tamano; i++)
        {
            if(c[i] != vector.c[i])
            {
                check= false;
                break;
            }
        }
    }
    else
        check= false;
    return check;
}
// Sobrecarga del operador desigualdad
bool TVectorCom::operator!= (TVectorCom& vector) const
{
    bool check= true;
    if(tamano == vector.Tamano())
    {
        for(int i=0; i < tamano; i++)
        {
            if(c[i] == vector.c[i])
            {
                check= false;
                break;
            }
        }
    }
    return check;
}
// Sobrecarga del operador corchete (parte IZQUIERDA)
TComplejo& TVectorCom::operator[] (int pos)
{
    if(pos <= tamano && pos >= 1)
    {
        for(int i=0; i < tamano; i++)
        {
            if(i == (pos - 1))
                return c[i];
        }
    }
    else
    {
        error= 0;
        return error;
    }
}
// Sobrecarga del operador corchete (parte DERECHA)
TComplejo TVectorCom::operator[] (int pos) const
{
    if(pos < tamano || pos >= 1)
    {
        for(int i=0; i < tamano; i++)
            if(i == (pos - 1))
                return c[i];
    }
    return 0;
}
// Tamaño del vector (posiciones TOTALES)
int TVectorCom::Tamano()
{
    return tamano;
}
// Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
int TVectorCom::Ocupadas()
{
    int cont= 0;
    TComplejo aux;
    for(int i=0; i < tamano; i++)
        if(c[i] != aux)
            cont++;

    return cont;
}
// Devuelve TRUE si existe el TComplejo en el vector
bool TVectorCom::ExisteCom(const TComplejo& complejo)
{
    for(int i=0; i < tamano; i++)
        if(c[i] == complejo)
            return true;

    return false;
}
// Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL O POSTERIOR al argumento
void TVectorCom::MostrarComplejos(const double real)
{
    TVectorCom aux;

    for(int i=0; i < tamano; i++)//Creamos un vector con todos los complejos que cumplen la condición
    {
        if(c[i].Re() >= real)
        {
            aux.Redimensionar(aux.Tamano() + 1);
            aux[aux.Tamano()]= c[i];
        }
    }
    cout << "[";
    for(int i=0; i < aux.tamano; i++)
    {
        cout << aux.c[i];
        if(i < aux.tamano - 1)
            cout << ", ";
    }   
    cout << "]";
}
// REDIMENSIONAR el vector de TComplejo
bool TVectorCom::Redimensionar(const int resize)
{
    bool redimensionado= false;

    if(resize > 0)
    {
        if(resize > tamano)//Aumentar
        {
            TVectorCom vector(resize);
            for(int i=0; i < tamano; i++)
                vector.c[i]= c[i];
            (*this)= vector;
            redimensionado= true;
        }
        if(resize < tamano)//Disminuir
        {
            TVectorCom vector(resize);
            for(int i=0; i < vector.Tamano(); i++)
                vector.c[i]= c[i];
            (*this)= vector;
            redimensionado= true;
        }
    }

    return redimensionado;
}
