/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg151044026;

/**
 *
 * @author batuhan
 */
import java.security.InvalidParameterException;
public interface GTUSetInt<E> 
{
    boolean empty();
    int size();
    int max_size();
    void insert(final E parametre)throws InvalidParameterException;//throws InvalidParameterException;
    int erase(E parametre);//std::set::erase de parametre olarak silinecek değeri alan erase için return 
    //						" the function returns the number of elements erased." olarak verildiği için int return ediyorum. 
    GTUSetInt<E> intersection(final GTUSetInt<E> parametre);
    void clear();
    GTUIteratorInt<E> find(final E parametre);
    int count(final E parametre);
    GTUIteratorInt<E> begin();
    GTUIteratorInt<E> end();

    public interface GTUIteratorInt<E>
    {
            boolean hasNext();
            boolean hasPrevious();
            E next();
            E previous();
            E getCurrent();
            void setCurrent(E parametre);
            int getIndex();
            void setIndex(int parametre);
    }
}
