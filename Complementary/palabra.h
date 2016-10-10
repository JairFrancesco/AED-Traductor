#ifndef PALABRA_H
#define PALABRA_H

#include <string>
//#include <conio.h>
#include <vector>
using namespace std;

class Palabra
{
    public:
        Palabra(){}
        Palabra(string idm1, std::vector<string> idm2):idioma1(idm1), idioma2(idm2){}
        string idioma1;
        std::vector<string> idioma2;
        bool operator==(Palabra &p2)
        {
            return (this->idioma1 == p2.idioma1 && this->idioma2.at(0) == p2.idioma2.at(0));
        }
        bool operator!=(Palabra &p2){
            return (this->idioma1 != p2.idioma1 && this->idioma2.at(0) != p2.idioma2.at(0));
        }
        bool operator<(Palabra &p2){
            if ((this->idioma1).compare(p2.idioma1)<0 && (this->idioma2.at(0)).compare(p2.idioma2.at(0))<0)
            {
                return true;
            }
            return false;
        }

        bool operator>(Palabra &p2){
            if ((this->idioma1).compare(p2.idioma1)>0 && (this->idioma2.at(0)).compare(p2.idioma2.at(0))>0)
            {
                return true;
            }
            return false;
        }

        bool operator<=(Palabra &p2){
            if ((this->idioma1).compare(p2.idioma1)>=0 && (this->idioma2.at(0)).compare(p2.idioma2.at(0))>=0)
            {
                return true;
            }
            return false;
        }

        bool operator>=(Palabra &p2){
            if ((this->idioma1).compare(p2.idioma1)<=0 && (this->idioma2.at(0)).compare(p2.idioma2.at(0))<=0)
            {
                return true;
            }
            return false;
        }
        //friend ostream & operator<< (ostream &, string &);
};

/*
ostream & operator<< (ostream & salida, Palabra & s){
      salida<< s.idioma1;
      salida<<s.idioma2.at(0);
      return (salida);    //habilita el proceso en cascada
}
*/


#endif // PALABRA_H
