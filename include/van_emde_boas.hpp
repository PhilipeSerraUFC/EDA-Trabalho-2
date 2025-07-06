#ifndef VANEMDEBOAS
#define VANEMDEBOAS

#include <stdint.h>
#include <vector>
#include "int32.hpp"

using namespace std;
//forward declarations
class VeBExtensibleHash;

//class
class VanEmdeBoas { 
    private:
        bool is_empty = true;

    public: 

        uint8_t number_of_bits;
        Int32 veb_min;
        Int32 veb_max;

        VeBExtensibleHash* clusters;
        VanEmdeBoas* summary;

        VanEmdeBoas(uint8_t);

        void Delete();

        void Insert(Int32);

        void Remove(Int32);

        Int32 Sucessor(Int32);

        Int32 Predecessor(Int32);

        vector<vector<Int32>> Print();
};

#endif