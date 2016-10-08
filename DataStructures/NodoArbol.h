#ifndef NODO_H
#define NODO_H

template <class T>
class Nodo
{
    public:
        Nodo(T d)
        {
            this->valor=d;
            this->altura=0;
            mpson[0]=mpson[1]=0;
        }
        virtual ~Nodo(){}
    protected:
    public:
        T valor;
        int altura;
        Nodo<T>* mpson[2];

};

#endif // NODO_H
