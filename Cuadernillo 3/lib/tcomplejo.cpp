//#include "/home/rbm61/Escritorio/prac/include/tcomplejo.h"
#include "tcomplejo.h"

//Friends
ostream& operator <<(ostream &os, const TComplejo &tc)
{
    os << "(" << tc.Re() << " " << tc.Im() << ")";
    return os;
}
//Sobrecarga del operador suma: double + TComplejo
TComplejo operator +(const double d, const TComplejo &tc)
{
    //Construimos un TComplejo con la variable double
    TComplejo aux(d);
    TComplejo resultado;
    resultado= aux + tc;
    return resultado;
}
//Sobrecarga del operador resta: double - TComplejo
TComplejo operator -(const double d, const TComplejo &tc)
{
    //Construimos un TComplejo con la variable double
    TComplejo aux(d);
    TComplejo resultado;
    resultado= aux - tc;
    return resultado;
}
//Sobrecarga del operador multiplicación: double * TComplejo
TComplejo operator *(const double d, const TComplejo &tc)
{
    //Construimos un TComplejo con la variable double
    TComplejo aux(d);
    TComplejo resultado;
    resultado= aux * tc;
    return resultado;
}
//Método auxiliar para copiar los métodos privados
void TComplejo::Copia(const TComplejo &tc)
{
    re= tc.re;
    im= tc.im;
}
// Devuelve PARTE REAL
double TComplejo::Re() const
{
    return re;
}
// Devuelve PARTE IMAGINARIA
double TComplejo::Im() const
{
    return im;
}
// Modifica PARTE REAL
void TComplejo::Re(double re) 
{
    this->re= re;
}
// Modifica PARTE IMAGINARIA
void TComplejo::Im(double im) 
{
    this->im= im;
}

double TComplejo::Arg() const
{
    double arg= atan2(Im(), Re());
    return arg;
}
double TComplejo::Mod() const
{
    double mod= sqrt(pow(re,2) + pow(im,2));
    return mod;
}
//Constructor de la parte real e imaginaria
TComplejo::TComplejo(double re, double im)
{
    Re(re);
    Im(im);
}
//Constructor de copia
TComplejo::TComplejo(const TComplejo& tc)
{
    Copia(tc);
}
//Destructor
TComplejo::~TComplejo()
{
    Re(0.0);
    Im(0.0);
}
//Operador de asignación
TComplejo& TComplejo::operator =(const TComplejo& tc)
{
    if (this != &tc)
    {
        (*this).~TComplejo();//Destructor
        this->Copia(tc);
    }
    return *this;   
}
//ARITMETICOS CON TCOMPLEJO COMO PARAMETROS
//Sobrecarga operador suma: TComplejo + TComplejo
TComplejo TComplejo::operator +(const TComplejo& tc) const//No modifica la clase
{                                                         //El parámetro es constante y no se puede modificar
    TComplejo resultado(Re() + tc.Re(), Im() + tc.Im());
    return resultado;
}
//Sobrecarga operador resta: TComplejo - TComplejo
TComplejo TComplejo::operator -(const TComplejo& tc) const
{
    TComplejo resultado(Re() - tc.Re(), Im() - tc.Im());
    return resultado;
}
//Sobrecarga operador multiplicación: TComplejo * TComplejo
TComplejo TComplejo::operator *(const TComplejo& tc) const
{
    //Creamos dos complejos auxiliares
    //Parte Real del complejo actual [Re()] multiplica los componentes de 'tc'
    TComplejo c1(Re() * tc.Re() , Re() * tc.Im());  
    //Parte Imaginaria del complejo actual [Im()] multiplica los componentes de 'tc'
    //Im() * tc.Im() equivale a la parte real de c2 con simbolo cambiado
    TComplejo c2(Im() * tc.Im() * -1 , Im() * tc.Re());
    //Con la suma de estos complejos obtenemos el resultado
    TComplejo resultado(0,0);
    resultado= c1 + c2;
    return resultado;
}
// //ARITMETICO CON DOUBLE COMO PARAMETROS
//Sobrecarga operador suma: TComplejo + double
TComplejo TComplejo::operator +(const double d) const
{
    TComplejo tc(d);
    TComplejo resultado(0,0);
    resultado= (*this) + tc;
    return resultado;
}
//Sobrecarga operador resta: TComplejo - double
TComplejo TComplejo::operator -(const double d) const
{
    TComplejo tc(d);
    TComplejo resultado(0,0);
    resultado= (*this) - tc;
    return resultado;
}
//Sobrecarga operador multiplicación: TComplejo * double
TComplejo TComplejo::operator *(double d) const
{
    TComplejo tc(d);
    TComplejo resultado(0,0);
    resultado= (*this) * tc;
    return resultado;
}
//IGUALDAD entre complejos
bool TComplejo::operator==(const TComplejo& tc) const
{
    bool iguales= false;
    if (re == tc.Re())
    {
        if (im == tc.Im())
        iguales= true;
    }

    return iguales;
    
}
//DESIGUALDAD entre complejos
bool TComplejo::operator!=(const TComplejo& tc) const
{
    return !((*this) == tc);
}