#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector> 
#include <list>

using namespace std;
template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
	vector<list<VALTYPE>> hash;

	private:
		/**
		 *  Rehash the table into a larger table when the load factor is too large
		 */
		void rehash() {
			vector<list<VALTYPE>> old = hash;
			hash.resize(nextPrime(2*hash.size()));
			for( auto & thisList: hash)
				thisList.clear();

			currentSize = 0;
			Word temp;

			for(int index = 0; index<old.size();index++)
			{
				auto & tempList = old[index];
				for(typename list<VALTYPE>::iterator place = tempList.begin(); place != tempList.end();place++)
				{
					temp = *place;
				insert(temp.myword, temp);
				}
			}		            
		}

		/**
		 *  Function that takes the key (a string or int) and returns the hash key
		 *   This function needs to be implemented for several types it could be used with!
		 */
		int hash_function(int key) 
		{
			return (key % bucket_count());
		}

		int hash_function(string key) 
		{
			int keyval = 0;
			for(char ch: key)
				if(ch >= 97 && ch<= 122)
					keyval += ch;
			return (keyval % bucket_count());
		}

		
	public:
		/**
		 *  Basic constructor
		 */

		int currentSize;

		Hashtable( int startingSize = 101 )
		{
            currentSize = 0;
			hash.resize(startingSize);
			for (int i = 0; i < 101; ++i)
			{
				hash[i].clear();
			}
		}

		/**
		 *  Add an element to the hash table
		 */
		bool insert(KEYTYPE key, VALTYPE val) {
            
            		int check = hash_function(key);
			if(check< hash.size())
			{
				auto & tempList = hash[check];
				if(!tempList.empty())
				{
					for (typename list<VALTYPE>::iterator place = tempList.begin(); !tempList.empty() && place != tempList.end(); place++)
					{
						if (mycompare(key, place->myword)) 
						{
							tempList.erase(place);
							currentSize--;
						}
					}
				}
				tempList.push_back(val);
				currentSize++;
			
				if (load_factor() > 1.0)
				{
					rehash();
				}
				return true;
			}
				return false;
		}

		/**
		 *  Return whether a given key is present in the hash table
		 */
		bool contains(KEYTYPE key) 
		{
			auto & tempList = hash[hash_function(key)];
			if(tempList.empty())
			{
				for(typename list<VALTYPE>::iterator place = tempList.begin(); place != tempList.end();place++)
				{
					if(mycompare(key,place->myword))
					{
						return true;
					}
				}
			}
			return false;
		}


		/**
		 *  Completely remove key from hash table
		 *   Returns number of elements removed
		 */
		int remove(KEYTYPE key) 
		{
			// Doesn't actually remove anything yet
			int check = hash_function(key);
			auto & tempList = hash[check];
			if(!tempList.empty())
			{
				for (typename list<VALTYPE>::iterator place = tempList.begin(); !tempList.empty() && place != tempList.end(); place++)
				{
					if (mycompare(key, place->myword)) 
					{
						tempList.erase(place);
						currentSize--;
						return 1;
					}
				}
			}
				return 0;		
		}

		/**
		 *  Searches the hash and returns a pointer
		 *   Pointer to Word if found, or nullptr if nothing matches
		 */
		VALTYPE *find(KEYTYPE key) 
		{
			int check = hash_function(key);
			auto & tempList = hash[check];
			if (!tempList.empty())
			{
				for(typename list<VALTYPE>::iterator place = tempList.begin();place != tempList.end();place++)
				{
					if(mycompare(key, place->myword))
					{
						return &* place;
					}
				}
			}
			return nullptr;
		}

		/**
		 *  Return current number of elements in hash table
		 */
		int size() 
		{
			return currentSize;
		}

		/**
		 *  Return true if hash table is empty, false otherwise
		 */
		bool empty() 
		{
			return(currentSize == 0) ? true : false;
		}

		/**
		 *  Calculates the current load factor for the hash
		 */
		float load_factor() 
		{
			//return _hash.load_factor();
			return ((float)currentSize / (float) bucket_count());
		}

		/**
		 *  Returns current number of buckets (elements in vector)
		 */
		int bucket_count() 
		{
			return hash.size();
		}

		/**
		 *  Deletes all elements in the hash
		 */
		void clear() 
		{
			for(int i = 0; i<bucket_count(); i++)
				hash[i].clear();
			currentSize = 0;
			hash.resize(101);
		}

		bool isPrime( int n )
		{
			if( n == 2 || n == 3 )
				return true;

			if( n == 1 || n % 2 == 0 )
				return false;

			for( int i = 3; i * i <= n; i += 2 )
				if( n % i == 0 )
					return false;

			return true;
		}
				
		int nextPrime( int n )
		{
			if( n % 2 == 0 )
				++n;

			for( ; !isPrime( n ); n += 2 )
				;

			return n;
		}

		bool mycompare(const string& lhs, const string& rhs)
		{
			if(lhs.size() != rhs.size())
				return false;
			for(int index = 0; index < lhs.size(); ++index)
			{
				if(tolower(lhs[index]) != tolower(rhs[index]))
					return false;
			}
			return true;
		}
		
		list<VALTYPE> & printhelp(int i)
		{
			return hash[i];
		}
};
#endif
