#ifndef PILA_H
#define PILA_H
#include <nodo.h>

template <class T>
class Pila
{
    public:
        Pila();
        void push(T d);
        T pop();
        T top();
        bool isEmpty();
    private:
        Nodo<T>* m_pTop;
};

template <class T>
bool Pila<T>::isEmpty()
{
    return m_ptop == 0;
}

template <class T>
T Pila<T>::pop()
{
    if (!isEmpty())
    {
        Nodo<T>* p = m_pTop;
        T tmp = p->m_dato;
        m_pTop = p->m_psig;
        delete p;
        return T;
    }
}

template <class T>
T Pila<T>::top()
{
    return m_pTop->m_dato;
}

template <class T>
void Pila<T>::push(T d)
{
    Nodo<T>* p = new Nodo<T>(d);
    if (m_pTop)
    {
        p->m_psig = m_pTop;
    }
    m_pTop = p;
}

#endif // PILA_H
