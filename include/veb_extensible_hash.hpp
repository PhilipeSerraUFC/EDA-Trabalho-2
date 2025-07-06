#ifndef VEBEXTENSIBLEHASH_HPP
#define VEBEXTENSIBLEHASH_HPP

#include "van_emde_boas.hpp"

class VeBExtensibleHash{

    public:

    vector<vector<pair<Int32, VanEmdeBoas*>>> buckets = {};
    uint32_t  values_quantity = 0;
    uint32_t hash_size = 0;
    uint8_t  number_of_bits;

    const float MAX_OCCUPANCY_RATE = 0.75;
    const float MIN_OCCUPANCY_RATE = 0.25;

    int HashFunction(Int32);

    void Doubling();

    void Halfing();

    void Rehash();

    VeBExtensibleHash(uint8_t);

    VanEmdeBoas* Search(Int32);

    VanEmdeBoas* Insert(Int32);

    void Remove(Int32);

    void Print();

};

#endif