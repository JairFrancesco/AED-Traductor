#ifndef NODO_H
#define NODO_H

template  <class T>
class Nodo
{
    public:
        Nodo();
        Nodo (T d){
            m_dato = d;
            m_psig = 0;
        }
        Nodo<T>* m_psig;
        T m_dato;
};

#endif // NODO_H
