#include <iostream>
//#include "BinarySearchTree.h"

using namespace std;


template <class T>
class Nodo
{
public:
    T m_dato;
    Nodo<T>*m_pder;
    Nodo<T>*m_pizq;
public:
    Nodo(T d)
    {
        m_dato=d;
        m_pder=m_pizq=0;
    }
};

template <class T>
class Tree
{
public:
    Nodo<T>*m_proot;
public:
    Tree():m_proot(0){};
    bool FindNR(T d); //buscador no recursivo
    bool FindR(T d); //buscador recursivo
    bool agregar(T d);
};

template <class T>
bool Agregar(T d)
{
    if(!m_proot)
        m_proot=new Nodo<T>(d);
    else
    {
        Nodo<T>*p;
        Nodo<T>*q;
        p=q=m_proot;
        while(q!=0)
        {
            p=q;
            if(q->m_dato==d)
                return false;
            if(q->m_dato<d)
                q=q->m_pder;
            else
                q=q->m_pizq;
        }
        if(p->m_dato<d)
            p->m_pder=new Nodo<T>(d);
        else
            p->m_pizq=new Nodo<T>(d);
    }
}
template <class T>
bool FindNR(T d)
{
    Nodo<T>*p->m_proot;
    while(p)
    {
        if(p->m_dato==d)
            return true;
        if(p->m_dato<d)
            p=p->m_pder;
        else
            p=p->m_pizq;
    }
    return false;
}

template <class T>
bool FindR(T d,Nodo<T>*p)
{
    if(!p)
        return false;
    if(p->m_dato==d)
        return true;
    if(p->m_dato<d)
        FindR(d p->m_pder);
    else
        FindR(d, p->m_pizq)
}

