#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include <conio.h>

using namespace std;

class Palabra
{
    public:
        Palabra(){};
        Palabra(string idm1, string idm2):idioma1(idm1), idioma2(idm2){};
        string idioma1, idioma2;
        bool operator==(Palabra &p2);
        bool operator!=(Palabra &p2);
        bool operator<(Palabra &p2);

        //friend ostream & operator<< (ostream &, string &);
};

/*
ostream & operator<< (ostream & salida, Palabra & s){
      salida<< s.idioma1;
      salida<<s.idioma2;
      return (salida);    //habilita el proceso en cascada
}
*/

bool Palabra::operator==(Palabra &p2)
{
    return (this->idioma1 == p2.idioma1 || this->idioma2 == p2.idioma2);
}

bool Palabra::operator!=(Palabra &p2)
{
    return (this->idioma1 != p2.idioma1 && this->idioma2 != p2.idioma2);
}

bool Palabra::operator<(Palabra &p2)
{
    if ((this->idioma1).compare(p2.idioma1)<0 && (this->idioma2).compare(p2.idioma2)<0)
    {
        return true;
    }
    return false;
}

#endif // PALABRA_H
