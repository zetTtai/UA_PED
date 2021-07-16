#ifndef _TVECTORCOM_H_
#define _TVECTORCOM_H_

#include <iostream>
#include <tcomplejo.h>
using namespace std;

class TVectorCom
{
    friend ostream& operator<< (ostream&, const TVectorCom&);

    private:

        TComplejo *c;
        TComplejo error;
        int tamano;
        void Copiar(const TVectorCom&);

    public:
        //Constructor por defecto
        TVectorCom();
        //Constructor a partir de tamaño
        TVectorCom(const int);
        //Constructor de copia
        TVectorCom(const TVectorCom&);
        //Destructor
        ~TVectorCom();
        //Sobregarca de operador de asignación
        TVectorCom& operator= (const TVectorCom&);

        // Sobrecarga del operador igualdad
        bool operator== (TVectorCom&) const;
        // Sobrecarga del operador desigualdad
        bool operator!= (TVectorCom&) const;
        // Sobrecarga del operador corchete (parte IZQUIERDA)
        TComplejo& operator[] (int);
        // Sobrecarga del operador corchete (parte DERECHA)
        TComplejo operator[] (int) const;
        // Tamaño del vector (posiciones TOTALES)
        int Tamano();
        // Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
        int Ocupadas();
        // Devuelve TRUE si existe el TComplejo en el vector
        bool ExisteCom(const TComplejo&);
        // Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL O POSTERIOR al argumento
        void MostrarComplejos(const double);
        // REDIMENSIONAR el vector de TComplejo
        bool Redimensionar(const int);

};

#endif