#pragma once

#include <iostream>   // std::ostream, std::cout

using std::string;

namespace Pic10b {

    template<typename T>
    class vector {
      private:
        T* the_data;
        size_t the_size;
        size_t the_capacity;

        static const int INIT_CAP = 10;


      public:
        // The big 4 
        vector();
        vector( const vector<T>& );
        vector<T>& operator=( const vector<T>& );
        ~vector();

        // other overloads
        vector<T>& operator+=( const vector<T>& );
        bool operator<( const vector<T>& );
        bool operator<=( const vector<T>& );
        bool operator>( const vector<T>& );
        bool operator>=( const vector<T>& );
        bool operator==( const vector<T>& );
        bool operator!=( const vector<T>& );


        // Other members [public]
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        T front() const;
        T back() const; 
        T at( size_t index ) const;
        T& operator[]( size_t index );
        T operator[]( size_t index ) const; 
        void dump_data_to( std::ostream& out ) const;
        void dump_data() const;
        void push_back( T new_value );
        void pop_back();

      private:
        //Other members [private]
        void reserve( size_t new_capacity );

    }; // end Pic10b::vector


    /** ************************* THE BIG 4 ************************* **/
    template<typename T>
    vector<T>::vector() : the_data(nullptr), the_size(0), the_capacity(INIT_CAP){
        the_data = new T[the_capacity];
        std::cout << "xxxxxxxxxx Default constructor called\n";
    }

    template<typename T>
    vector<T>::vector( const vector<T>& source ) : the_data(nullptr), the_size(source.the_size),
        the_capacity(source.the_capacity){

        the_data = new T[the_capacity];

        // Deep copy of internal array
        for ( int i = 0 ; i < the_size ; ++i ){
            the_data[i] = source.the_data[i];
        }
        std::cout << "xxxxxxxxxx Copy constructor called\n";
    }

    template<typename T>
    vector<T>& vector<T>::operator=( const vector<T>& rhs ){
        if ( this != &rhs ) {     // Self-assignment?
            // Release old memory and request more 
            delete[] the_data;
            the_data = new T[rhs.the_capacity];

            // Shallow copy non-pointers
            the_size = rhs.the_size;
            the_capacity = rhs.the_capacity;

            // Deep copy internal array
            for ( int i = 0 ; i < the_size ; ++i )
                the_data[i] = rhs.the_data[i];
        }
        std::cout << "xxxxxxxxxx Assignment operator called\n";
        return *this;
    }

    template<typename T>
    vector<T>::~vector(){
        delete[] the_data;
        std::cout << "xxxxxxxxxx Destructor called\n";
    }

    /** *********************** MEMBER OPERATORS *********************** **/
    
    // template overload for plusequals defined using overloaded addition
    template<typename T>
    vector<T>& vector<T>::operator+=(const vector<T>& b){
        for(int i = 0; i < the_size; i++){
            the_data[i] += b[i];
        }
        return *this;
    }

    template<typename T>
    bool vector<T>::operator<( const vector<T>& b){
        return ((*this)*(*this)) < (b*b);
    }


    template<typename T>
    bool vector<T>::operator<=( const vector<T>& b){
        return ((*this)*(*this)) <= (b*b);
    }

    template<typename T>
    bool vector<T>::operator>( const vector<T>& b){
        return ((*this)*(*this)) > (b*b);
    }


    template<typename T>
    bool vector<T>::operator>=( const vector<T>& b){
        return ((*this)*(*this)) >= (b*b);
    }


    template<typename T>
    bool vector<T>::operator==( const vector<T>& b){
        for(int i = 0; i < the_size; i++)
            if(the_data[i] != b[i])
                return false;
        return true;
    }
    
    template<typename T>
    bool vector<T>::operator!=( const vector<T>& b){
        for(int i = 0; i < the_size; i++)
            if(the_data[i] != b[i])
                return true;
        return false;
    }

    /** *********************** OTHER MEMBERS *********************** **/
    template<typename T>
    bool vector<T>::empty() const {
        return the_size == 0;
    }

    template<typename T>
    size_t vector<T>::size() const {
        return the_size;
    }

    template<typename T>
    size_t vector<T>::capacity() const {
        return the_capacity;
    } 

    template<typename T>
    T vector<T>::front() const {
        return *the_data;
    }

    template<typename T>
    T vector<T>::back() const {
        return *(the_data + the_size - 1);
    } 

    template<typename T>
    T vector<T>::at( size_t index ) const {
        if ( index < the_size )
            return the_data[index];
        return the_data[0];
    }

    template<typename T>
    T& vector<T>::operator[]( size_t index ){
        return the_data[index];
    }

    template<typename T>
    T vector<T>::operator[]( size_t index ) const {
        return the_data[index];
    }

    template<typename T>
    void vector<T>::dump_data_to( std::ostream& out ) const {
        out << "Vector (dump): ";
        for ( size_t i = 0 ; i < the_capacity ; ++i )
            out << the_data[i] << ' ';
        out << '\n';
    }
    
    template<typename T>
    void vector<T>::dump_data() const {
        dump_data_to( std::cout );
    }

    template<typename T>
    void vector<T>::push_back( T new_value ){
        if ( the_size == the_capacity ) 
            reserve( the_capacity + 1 );     // `the_data` is reassigned

        the_data[the_size++] = new_value;
    }

    // This implementation does not shrink the vector (ever)
    template<typename T>
    void vector<T>::pop_back(){
        if ( the_size > 0 )
            --the_size;
    }

    template<typename T>
    void vector<T>::reserve( size_t new_capacity ){
        if ( new_capacity > the_capacity ) {
            if ( new_capacity <= 2 * the_capacity )
                new_capacity = 2 * the_capacity;

            T* old_location = the_data;

            the_data = new T[new_capacity];
            the_capacity = new_capacity;

            for ( size_t i = 0 ; i < the_size ; ++i )
                the_data[i] = old_location[i];

            delete old_location;
        }
    }

} // end Pic10b namespace

/** ************************ NON-MEMBER OPERATORS ************************ **/
// template overload for stream output
template<typename T>
std::ostream& operator<<( std::ostream& out, const Pic10b::vector<T>& v ){
    for ( size_t i = 0 ; i < v.size() ; ++i )
        out << v[i] << ' ';
    return out;
}

// template overload for vector multiplications (serves as vec * vec primary)
template<typename T>
T operator*(const Pic10b::vector<T>& a, const Pic10b::vector<T>& b){
    T c = 0;
    for(int i = 0; i < a.size(); i++){
        c += a[i] * b[i];    
    }
    return c;
}
// template overload for string vector multiplications
template<typename T>
Pic10b::vector<string> operator*(const Pic10b::vector<string>& a, const Pic10b::vector<string>& b){
    Pic10b::vector<string> c = a;
    for(int i = 0; i < a.size(); i++){
        c[i] = c[i] + b[i];    
    }
    return c;
}
// template overload for non-vector * vector multiplications (serves as nonvec * vec primary)
template<typename T>
Pic10b::vector<T> operator*(const T& a, const Pic10b::vector<T>& b){
    Pic10b::vector<T> c = b;
    for(int i = 0; i < b.size(); i++){
        c[i] *= a;    
    }
    return c;
}
// template overload for vector * non-vector multiplications (serves as vec * nonvec primary)
template<typename T>
Pic10b::vector<T> operator*(const Pic10b::vector<T>& a, const T& b){
    Pic10b::vector<T> c = a;
    for(int i = 0; i < a.size(); i++){
        c[i] *= b;    
    }
    return c;
}
//specialization for vector + string multiplications
template<>
Pic10b::vector<string> operator*(const Pic10b::vector<string>& a, const string& b){
    Pic10b::vector<string> c = a;
    for(int i = 0; i < a.size(); i++){
        c[i] = c[i] + ' ' + b; // should process as string concatenation    
    }
    return c;
}
// specialization for string + vector multiplications
template<>
Pic10b::vector<string> operator*(const string& a, const Pic10b::vector<string>& b){
    Pic10b::vector<string> c = b;
    for(int i = 0; i < a.size(); i++){
        c[i] = a + ' ' + c[i]; // should process as string concatenation    
    }
    return c;
}

// template overload for vector addition 
template<typename T>
Pic10b::vector<T> operator+(const Pic10b::vector<T>& a, const Pic10b::vector<T>& b){
    Pic10b::vector<T> c = a;
    for(int i = 0; i < a.size(); i++){
        c[i] += b[i];    
    }
    return c;
}
/** ************************ OTHER FUNCTIONS ************************ **/
template<typename T>
void print_vector( const Pic10b::vector<T>& v ){
    if ( v.empty() )
        std::cout << "Vector is empty\n";
    else
        std::cout << "Vector (contents): " << v << '\n' ;
} 

