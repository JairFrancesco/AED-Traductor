#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include<iostream>
#include<list>

using namespace std;

template<class T>
class NodoBHeap
{
    typedef NodoBHeap<T> *  pNodo;
    public:
      int                m_Grado;
      T                  m_Dato;
      pNodo              m_pPadre;
      list< pNodo >      m_Son;
     NodoBHeap(T d)
      {
           m_Dato = d;
           m_Grado =0;
      }
};

template<class T>
class Bheap
{
    typedef NodoBHeap<T> *  pNodo;
    typedef    list< pNodo >       TLista;
    typedef typename   TLista::iterator  TIterator;

    private:
      TLista  m_Heads;
    public:
      Bheap(){};
      TLista getRaices()
      {
          return m_Heads;
      }
      void Insert(T d)
      {
          m_Heads.push_back(new NodoBHeap<T>(d));
          merge();
      }
      void insertarpalabra(Palabra pal)
      {
          string a=pal.idioma1;
          int i,res;
          i=res=0;
          while (a[i]!='\0')
          {
              int c=a[i];
              res=res+c;
              i++;
          }
          int reso=res;
          Insert(reso);
          /*
          for (std::vector<string>::iterator it=pal.idioma2.begin();it!=pal.idioma2.end();it++)
          {

              while (a[i]!='\0')
              {
                  int c=a[i];
                  res=res+c;
                  i++;
              }
              insertar(res);
              res=reso;
          }
          */
      }
      T minimo()
      {
            TIterator it = m_Heads.begin();
            T min =  (*it)->m_Dato;
             for(; it !=m_Heads.end() ; ++it)
                  if(min>(*it)->m_Dato)
                     min = (*it)->m_Dato;
            return min;
      }
      void merge()
      {
            int n = m_Heads.size()+1;
            //pNodo arreglo[n];
            vector<pNodo> v;
            for( int i =0;i<n ; ++i) v.push_back(0);  //arreglo[i] = 0;

            TIterator it = m_Heads.begin();
            while(it!=m_Heads.end()){
                int pos = (*it)->m_Grado;

                if(v.at(pos) == 0){
                    v.at(pos) = (*it);
                    it++;
                }
                else
                {
                    if (v.at(pos)->m_Dato > (*it)->m_Dato)
                    {
                        swap(*(v.at(pos)),*(*it));
                        for(TIterator it2 = v.at(pos)->m_Son.begin() ;it2!= v.at(pos)->m_Son.end();++it2)
                        {
                            (*it2)->m_pPadre = v.at(pos);
                        }
                        for(TIterator it2 = (*it)->m_Son.begin(); it2!= (*it)->m_Son.end();++it2)
                        {
                            (*it2)->m_pPadre = *it;
                        }
                    }
                    v.at(pos)->m_Son.push_back(*it);
                    (*it)->m_pPadre = v.at(pos);
                    TIterator temp = it;
                    temp--;
                    m_Heads.erase(it);
                    it = temp;
                    v.at(pos)->m_Grado++;
                    v.at(pos) = 0;
                }
            }
      }
      void Decrease_key(pNodo p , T d)
      {
          p->m_Dato = d;
          while(p->m_pPadre)
          {
                 if (p->m_Dato < p->m_pPadre->m_Dato)
                        swap(p->m_Dato,p->m_pPadre->m_Dato);
                 else return;
          }
      }

      void Extract_min()
      {

            TIterator it = m_Heads.begin();
            pNodo min =  it;
             for(; it !=m_Heads.end() ; ++it)
                  if(min->m_Dato>it->m_Dato)
                     min = it;

             TIterator it_son = min->m_Son.begin();
             for(; it_son !=min->m_Son.end() ; ++it_son)
                  m_Heads.push_back(it_son);
             m_Heads.remove(min);
             merge();
      }

      void Delete(pNodo p)
      {
          Decrease_key(p,-10000);
          Extract_min();
      }




};



#endif // BINOMIALHEAP_H
