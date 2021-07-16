#ifndef _TCOMPLEJO_H_
#define _TCOMPLEJO_H_

#include <iostream>
#include <cmath>//Para cuando se implemente funciones matemáticas
using namespace std;

class TComplejo
{
    friend ostream& operator<< (ostream &, const TComplejo &);
    friend TComplejo operator+ (const double , const TComplejo&);
    friend TComplejo operator- (const double , const TComplejo&);
    friend TComplejo operator* (const double , const TComplejo&);

    private:
     
        double re; //Parte real
        double im; //Parte imaginaria
        void Copia(const TComplejo&);
    
    public:

        TComplejo(double= 0, double= 0);//Constructor de la parte real e imaginaria
        TComplejo(const TComplejo&);//Constructor de copia
        ~TComplejo();//Destructor
        TComplejo& operator= (const TComplejo&);//Operador de asginación

        //METODOS

        //Sobrecarga de operadores aritméticos
        TComplejo operator+(const TComplejo&) const;
        TComplejo operator-(const TComplejo&) const;
        TComplejo operator*(const TComplejo&) const;
        //----------------------------
        TComplejo operator+(const double) const;
        TComplejo operator-(const double) const;
        TComplejo operator*(const double) const;
        //Otros
        bool operator==(const TComplejo&) const; //IGUALDAD entre complejos
        bool operator!=(const TComplejo&) const; //DESIGUALDAD entre complejos

        double Re() const; // Devuelve PARTE REAL
        double Im() const; // Devuelve PARTE IMAGINARIA

        void Re(double); // Modifica PARTE REAL
        void Im(double); // Modifica PARTE IMAGINARIA

        double Arg(void) const; // Calcula el Argumento (en Radianes)
        double Mod(void) const; // Calcula el Módulo
};

#endif