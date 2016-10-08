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

        RBNode<T>* getAbuelo(){
            return m_pPadre->m_pPadre;
        }

        RBNode<T>* getPadre(){
            return m_pPadre;
        }

        RBNode<T>* getTio(){
            return (m_pPadre->soyDerecho() ? m_pPadre->m_pPadre->m_pIzquierda : m_pPadre->m_pPadre->m_pDerecha);
        }
        RBNode<T>* getHermano(){
            return (soyDerecho() ? m_pPadre->m_pIzquierda : m_pPadre->m_pDerecha);
        }

        bool soyIzquierdo(){
            if (m_pPadre->m_pIzquierda == this)
                return true;
            return false;
        }
        bool soyDerecho(){
            if (m_pPadre->m_pDerecha == this)
                return true;
            return false;
        }

        RBNode(T d)
        {
            m_pIzquierda = m_pDerecha = m_pPadre = 0;
            color = RED;
            m_Dato = d;
        }
    private:
};

#endif // RBNODE_H
