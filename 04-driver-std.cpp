/** ************************* THE DRIVER ************************ **/
int main(){

    using Pic10b::vector;
    using std::cout;

    cout << "Create & display empty vector (v1)\n";
    vector v1;
    print_vector(v1);
    v1.dump_data();

    int size = 15;
    cout << "\nPopulate & display vector with " << size << " entries (v1)\n";
    for ( int i = 1 ; i <= size ; ++i )
        v1.push_back(i);
    print_vector(v1);

    cout << "\nCopy non-empty vector, pop back last entry & display (v2)\n";
    vector v2(v1);
    v2.pop_back();
    print_vector(v2);

    cout << "\nReassign vector (v1 = v2) & display\n";
    v1 = v2;
    print_vector(v1);

    cout << "\nDump contents of vectors (v1,v2)\n";
    v1.dump_data();
    v2.dump_data();

    return 0;
}

/** 
    OUTPUT:

        Create & display empty vector (v1)
        Vector is empty
        Vector (dump): 0 0 0 0 0 0 0 0 0 0 

        Populate & display vector with 15 entries (v1)
        Vector (contents): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 

        Copy non-empty vector, pop back last entry & display (v2)
        Vector (contents): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 

        Reassign vector (v1 = v2) & display
        Vector (contents): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 

        Dump contents of vectors (v1,v2)
        Vector (dump): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0 0 0 0 0 
        Vector (dump): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0 0 0 0 0 

**/