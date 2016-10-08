#ifndef COLA_H
#define COLA_H
#include <nodo.h>

template <class T>
class Cola
{
    public:
        Cola(){
            m_phead = m_plast = 0;
        }
        virtual ~Cola();
        void encolar();
        T desencolar();
        T front();
        bool isEmpty();

    private:
        Nodo<T>* m_phead;
        Nodo<T>* m_plast;

};

template <class T>
Cola<T>::~Cola()
{
    //dtor
}

template <class T>
Cola<T>::isEmpty(){
    return m_phead == 0;
}

template <class T>
Cola<T>::desencolar(){
    if (isEmpty()){
        return;
    } else {
        Nodo<T>* p = m_phead;
        T tmp = p->m_dato;
        m_phead = m_phead->m_psig;
        delete(p);
        return tmp;
    }
};

template <class T>
Cola<T>::encolar(T d){
    Nodo<T>* p = new Nodo<T>(d);
    if (!m_phead)
    {
        m_phead = m_plast = p;
        m_plast->m_pSig = 0;
    }
    else
    {
        m_plast->m_pSig = p;
        m_plast = p;
        m_plast->m_psig = 0;
    }
}

template <class T>
T Cola<T>::front()
{
    return m_phead->m_dato;
}

#endif // COLA_H
