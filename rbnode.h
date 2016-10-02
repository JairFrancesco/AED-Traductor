#ifndef RBNODE_H
#define RBNODE_H


enum Color {RED, BLACK};

template <class T>
class RBNode
{
    public:
        RBNode() {
            m_pIzquierda = m_pDerecha = m_pPadre = 0;
        };
        T m_Dato;
        RBNode<T>* m_pIzquierda, *m_pDerecha, *m_pPadre;
        Color color;

        RBNode(T d)
        {
            m_pIzquierda = m_pDerecha = m_pPadre = 0;
            color = RED;
            m_Dato = d;
        }
    private:
};

#endif // RBNODE_H
