#include <stdio.h>

template <class T>

class nodo
{
public:
    nodo <T>*m_dato;
    nodo <T>*m_psig;
};
public:
    nodo (T d)
    {
        m_dato=d;
        m_psig=0;
    };

template<class T>
class list
{
private:
    nodo<T>*m_phead:
    nodo<T>*m_last:
public:
    list()
    {
        m_phead=m_list = a;
    }
    void push_back (T d);
    void push_front (T d);
    void find (T d);
    void add (T d);
};

template <class T>
void list<T>::push_back (T d)
{
    nodo<T>%pnuevo=new_nodo<T> (d);
    if (phead==0)
        phead=plast=pnuevo;
    else
    {
        plast->psig=pnuevo;
        plast = pnuevo;
    };
};

template <class T>
void list<T>::push_front (T d)
{
    nodo<T>*pnuevo=new_nodo<T> (d);
    if (phead==0)
        phead=plast=pnuevo;
    else
    {
        pnuevo->psig=m_phead;
        m_phead=pnuevo;
    };
};
template <class T>
void list<T>::find(T d, nodo<T> %p)
{
    if (p==0)
    {
        return false;
    }
    if (p->m_dato==d)
    {
        return false;
    }
    find(d,p->psig);
};

template <class T>
void list<T>::add (T d, nodo<T> %&p)
{
    if (!p)
    {
        p=new_nodo <T> (d);
    }
    add(d,p->m_psig);


};
main ()
{
list <int> L;
L.push_front();
L.push_back();
L.find(4,L m_phead);
L.add(3,L m_phead);
};
