#ifndef SEARCHSTRUCTURE_H
#define SEARCHSTRUCTURE_H
#include <palabra.h>

int distanciaLevenshtein(const string& , const string& );

class SearchStructure
{
    public:
        SearchStructure(){}
        virtual void insertar(Palabra d) = 0;
        virtual std::vector<Palabra> find(Palabra d)=0;


};

#endif // SEARCHSTRUCTURE_H
