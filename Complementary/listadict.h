#ifndef LISTADICT_H
#define LISTADICT_H

#endif // LISTADICT_H

public class ListaDict:
{
public:
    Lista& operator++ ()     // prefix ++
    {
        // Do work on this.   (increment your object here)

        return *this;
    }

    // You want to make the ++ operator work like the standard operators
    // The simple way to do this is to implement postfix in terms of prefix.
    //
    Lista  operator++ (int)  // postfix ++
    {
       Number result(*this);   // make a copy for result
       ++(*this);              // Now use the prefix version to do the work
       return result;          // return the copy (the old) value.
    }
private:
};
