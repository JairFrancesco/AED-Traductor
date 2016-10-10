#ifndef SEARCHSTRUCTURE_H
#define SEARCHSTRUCTURE_H
#include <palabra.h>

int distanciaLevenshtein(const string& , const string& );

class SearchStructure
{
    public:
        SearchStructure(){}
        virtual void insertar(Palabra d) = 0;
        //virtual std::vector<Palabra> find(Palabra , int )=0;
        virtual void begin()=0;
        virtual bool terminate()=0;
        virtual void next()=0;
        virtual Palabra getData()=0;


};

#endif // SEARCHSTRUCTURE_H
