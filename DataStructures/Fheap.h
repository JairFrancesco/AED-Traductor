#ifndef FHEAP_H
#define FHEAP_H
#include "NodoF.h"
#include <math.h>
#include <algorithm>
#include <vector>


template <class T>
bool buscar(std::list<NodoF<T>* > l,NodoF<T>* p)
{
    for (auto i:l)
    {
        if (&(*i)==p)
            return true;
    }
    return false;

}

template <class T>
void imprimir_vector(std::vector<NodoF<T>* > l)
{
    std::cout<<"{ ";
    for (auto i: l)
    {
        if (i)
            std::cout<<(i)->valor<<" -> ";
        else
            std::cout<<"vacio"<<" -> ";
    }
    std::cout<<" }"<<std::endl;

}

template <class T>
void imprimir_lista(std::list<NodoF<T>* > l)
{
    std::cout<<"{ ";
    for (auto it : l)
        std::cout<< (it)->valor<<","<<(it)->get_grado()<<" -> ";
    std::cout<< "}"<<std::endl;
}

template <class T>
class Fheap
{
    typedef NodoF<T>* Fnodo;
    typedef std::list<Fnodo> Flista;
    typedef typename Flista::iterator Fiterator;

    public:
        Fheap()
        {

        }
        void insertar(T);
        void unir_raices(Fnodo&, Fnodo&);
        void actualizar_min();
        void borrar(NodoF<T>*&);
        void unir(Fheap<T>);
        void ver_raices()
        {
            std::cout<<"raices: ";
            imprimir_lista(this->raices);
        }
        T getmin()
        {
            return (*minimo)->valor;
        }
        void decrease_key(Fnodo&, T);
        void compactar();
        void eliminar_min();
        virtual ~Fheap(){}
    protected:
    public:
        Flista raices;
        Fiterator minimo;

};


template <class T>
void Fheap<T>::unir(Fheap<T> otro)
{
    if ((*otro.minimo)->valor < (*minimo)->valor)
    {
        this->minimo=otro.minimo;
    }
    this->raices.merge(otro.raices);
}

template <class T>
void Fheap<T>::borrar(NodoF<T>*& a)
{
    decrease_key(a,-12321);
    eliminar_min();

}


template <class T>
void Fheap<T>::actualizar_min()
{
    Fiterator vmini=raices.begin();
    for (Fiterator mini=raices.begin();mini=raices.end();mini++)
    {
        if ((*vmini)->valor>(*mini)->valor)
            vmini=mini;
        (*mini)->marcado=false;
    }
    this->minimo=vmini;
}

template <class T>
void Fheap<T>::decrease_key(NodoF<T>*& a, T d)
{
    a->valor=d;

    if (a->valor<a->padre->valor)
    {
        if (!a->padre->marcado)
        {
            a->padre->marcado=true;
            a->padre=0;
            a->padre->hijos.remove(a);
            a->marcado=false;
            raices.push_front(a);
        }
        else
        {
            while (a->padre || a->padre->marcado)
            {
                a->marcado=false;
                a->padre=0;
                a->padre.hijos.remove(a);
                raices.push_front(a);
                a=a->padre;
            }
        }

    }
    actualizar_min();
}


template <class T>
void Fheap<T>::compactar()
{
    int a=log2(raices.size());
    std::vector<NodoF<T>*> v;
    for (int i=0;i<a+1;i++)
    {
        v.push_back(0);
    }
    Fiterator it=raices.begin();
    NodoF<T>* aux=*it;
    while (it!=raices.end())
    {
        std::cout<<"el nodo entrante es: "<<(*it)->valor<<" *  ";
        int grado=(*it)->get_grado();
        if (!v.at(grado))
        {
            std::cout<<"En este grado puede llenarse: "<<(*it)->valor<<std::endl;
            v.at(grado)=*it;
            it++;
        }
        else
        {
            std::cout<<"En este grado no puede llenarse: "<<(*it)->valor<<std::endl;
            Fiterator itaux=it;
            if ((v.at(grado))->valor<(*it)->valor)
            {
                std::cout<<"el del vector padre (vector) "<<(v.at(grado))->valor<<"       ";
                Fiterator itaux=find(raices.begin(),raices.end(),v.at(grado));
                unir_raices(v.at(grado),*it);
                it=itaux;
                int ngrado= (*it)->get_grado();
                if (!v.at(ngrado))
                {
                    v.at(grado)=0;
                    v.at(ngrado)=(*it);
                    it++;
                }
                else
                {
                    v.at(grado)=0;
                }


            }
            else
            {

                std::cout<<"el del vector padre (iterador) "<<(*it)->valor<<"       ";
//                int agrado=(*it)->
                unir_raices(*it,v.at(grado));

                int ngrado=(*it)->get_grado();
                if (!v.at(ngrado))
                {
                    v.at(grado)=0;
                    v.at(ngrado)=(*it);
                    it++;
                }



            }
            //unir_raices(v.at(grado),*it);


        }
        std::cout<<"raices: ";
        imprimir_lista(raices);
        std::cout<<"vec: ";
        imprimir_vector(v);
        std::cout<<"------------------------------"<<std::endl;
//        it++;

    }
    std::cout<<"vec: ";
    imprimir_vector(v);


}


template <class T>
void Fheap<T>::eliminar_min()
{
    Fnodo aux=*minimo;
    raices.remove(aux);
    if (!aux->hijos.empty())
    {
        for (auto i: aux->hijos)
        {
            raices.push_back(i);
            aux->hijos.remove(i);
            i->padre=0;
        }
    }
    actualizar_min();
    compactar();
}



template <class T>
void Fheap<T>::unir_raices(NodoF<T>*& a, NodoF<T>*& b)
{
    if ((a->valor)<(b->valor))
    {
        raices.remove(b);
        a->hijos.push_front(b);
        //std::cout<<"va: "<<b->valor<<std::endl;
        b->padre=a;
        std::cout<<"prueba: ";
        imprimir_lista(a->hijos);

    }


}

template <class T>
void Fheap<T>::insertar(T d)
{
    Fnodo nuevo=new NodoF<T>(d);
    if (raices.empty())
    {
        raices.push_back(nuevo);
        minimo=raices.begin();
    }
    else
    {
        raices.insert(minimo,nuevo);
        if ((*minimo)->valor>=d) minimo--;
    }
    //ver_raices();
    //std::cout<<"Por ahora el minimo es: "<<(*minimo)->valor<<std::endl;
}




#endif // FHEAP_H
