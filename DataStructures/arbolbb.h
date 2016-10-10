#ifndef ARBOLBB_H
#define ARBOLBB_H
#include <searchstructure.h>

template <class T>
class NodoB
{
    public:
        NodoB(T d){
            this->valor=d;
            mpder=mpizq=0;

        }
        NodoB(){}
        T getval()
        {
            return this->valor;
        }
        virtual ~NodoB(){
        }
    public:
        T valor;
        NodoB<T>* mpizq;
        NodoB<T>* mpder;


};

template<class T>
class Btree : public SearchStructure
{
    public:
        Btree(){
            this->raiz=0;
        }
        void insertar(Palabra d)
        {
            NodoB<T>* nuevo=new NodoB<T>(d);
            if (!raiz)
                this->raiz=nuevo;
            else
            {
                NodoB<T>* p,*q;
                p=this->raiz;
                while (p)
                {
                    q=p;
                    if (d==p->valor) return;
                    if (d>p->valor) p=p->mpder;
                    else p=p->mpizq;
                }
                if (d>q->valor) q->mpder=nuevo;
                else q->mpizq=nuevo;
            }
        }
        void begin()
        {
            NodoB<T>* aux= raiz;
            while(aux->mpizq)
            {
                aux=aux->mpizq;
            }
            current=aux;
        }
        void end()
        {
            NodoB<T>*aux=raiz;
            while (aux->mpder)
                aux=aux->mpder;
            last=aux;
        }
        bool terminate()
        {
            if (!current->mpder && current==last) return true;
            return false;
        }

        void next()
        {
            if (!current) return;
            NodoB<T>*aux=current;
            if (aux->mpder) current=current->mpder;
            else
            {
                NodoB<T>* p=padre(aux);
                while(aux->valor > p->valor)
                {
                    aux=p;
                    p=padre(aux);
                }
                current=p;
            }
        }

        T getData()
        {
            return current->valor;
        }

        NodoB<T>* padre(NodoB<T>* h)
        {
            NodoB<T>* p,*q;
            p=this->raiz;
            T d=h->valor;
            while (p)
            {
                if (d==p->valor) break;
                q=p;
                if (d>p->valor) p=p->mpder;
                else p=p->mpizq;
            }
            return q;
        }

        ~Btree();

    public:
        NodoB<T>* raiz;
        NodoB<T>* current;
        NodoB<T>* last;

    
};


#endif //ARBOLBB_H
