#ifndef NODOF_H
#define NODOF_H
#include <list>


template <class T>
class NodoF
{
    public:
        NodoF(T d)
        {
            this->valor=d;
            this->padre=0;
            this->marcado=false;
        }
        int get_grado()
        {
            return this->hijos.size();
        }
        virtual ~NodoF(){}
    protected:
    public:
        T valor;
        NodoF<T>* padre;
        std::list<NodoF<T>* > hijos;
        bool marcado;


};

#endif // NODOF_H
