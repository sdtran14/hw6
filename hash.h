#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <algorithm>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        //HASH_INDEX_T wValues[5] = {0,0,0,0,0};
        int idx = k.size();
				HASH_INDEX_T total = 0;
        for(int i = 4; i>=0; i--)
        {
						idx = idx-6;
						int len = 6;
						if(idx < 0) 
						{
							len += idx;
							idx = 0;
						}

						std::string curStr = k.substr(idx, len);
						//std::cout<<curStr<<std::endl;
						HASH_INDEX_T res = 0;
						for(size_t j = 0; j<curStr.size(); j++) 
						{
							res = (res * 36) + letterDigitToNumber(curStr[j]);
						}
						total += res*rValues[i];
						//std::cout<<total<<std::endl;
            if(idx<=0) break;
        }
        return total;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(isalpha(letter)) return tolower(letter) - 'a';
        else return 26+ (letter-'0') ;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

