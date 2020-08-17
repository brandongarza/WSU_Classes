/*
 *  dictionary.h -- A hash-based dictionary for searching definitions
 *   Copyright 2017 - Aaron S. Crandall <acrandal@gmail.com>
 */

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include <string>
#include <iostream>
#include <fstream>

class Dictionary
{

	private:
		Hashtable<string, Word> _dict;  // Primary dictionary store

	bool parseline( string line ) {

		//cout << " [d] Parsing line: " << line << endl;
		string temp = "", word = "", def = "";
		int pos = 0, wpos = 0, sum = -1;
		bool check = false;
		
		for(pos = 0; line[pos] != '\n' && line[pos] != ' '; ++pos){
			;
		}
		temp = line.substr(0, pos);
		
		if(makelower(temp) == "help"){
			help();
		}else if(makelower(temp) == "add"){
			wpos = ++pos;
			for(pos; line[pos] != '\0' && line[pos] != ' '; ++pos){
				if (line[pos] == '"' && check == false){
					wpos ++;
					check = true;
				}
			}
			if(check == true){
				word = line.substr(wpos, pos - wpos - 1);
			}else{
				word = line.substr(wpos, pos - wpos);
			}
			def = line;
			def.erase(0,pos+1);
			add(makelower(word),def);
		}else if(makelower(temp) == "remove"){
			wpos = ++pos;
			for(pos; line[pos] != '\0' && line[pos] != ' '; ++pos){
				if (line[pos] == '"' && check == false){
					wpos ++;
					check = true;
				}
			}
			if(check == true){
				word = line.substr(wpos, pos - wpos - 1);
			}else{
				word = line.substr(wpos, pos - wpos);
			}
			remove(makelower(word));
		}else if(makelower(temp) == "define"){
			wpos = ++pos;
			for(pos; line[pos] != '\0' && line[pos] != ' '; ++pos){
				if (line[pos] == '"' && check == false){
					wpos ++;
					check = true;
				}
			}
			if(check == true){
				word = line.substr(wpos, pos - wpos - 1);
			}else{
				word = line.substr(wpos, pos - wpos);
			}
			define(makelower(word));
		}else if(makelower(temp) == "load"){
			wpos = ++pos;
			for(pos; line[pos] != '\0' && line[pos] != ' '; ++pos){
				if (line[pos] == '"' && check == false){
					wpos ++;
					check = true;
				}
			}
			if(check == true){
				word = line.substr(wpos, pos - wpos - 1);
			}else{
				word = line.substr(wpos, pos - wpos);
			}
			load(word);
		}else if(makelower(temp) == "unload"){
			wpos = ++pos;
			for(pos; line[pos] != '\0' && line[pos] != ' '; ++pos){
				if (line[pos] == '"' && check == false){
					wpos ++;
					check = true;
				}
			}
			if(check == true){
				word = line.substr(wpos, pos - wpos - 1);
			}else{
				word = line.substr(wpos, pos - wpos);
			}
			unload(word);
		}else if(makelower(temp) == "size"){
			size();
		}else if(makelower(temp) == "clear"){
			clear();
		}else if(makelower(temp) == "print"){
			wpos = ++pos;
			if(line.size() > 5){
				for(pos; line[pos] != '\0' && line[pos] != ' '; ++pos){
					if (line[pos] == '"' && check == false){
						wpos ++;
						check = true;
					}
				}
				if(check == true){
					word = line.substr(wpos, pos - wpos - 1);
				}else{
					word = line.substr(wpos, pos - wpos);
				}
				for(char & numbers : word)
						sum += (numbers-48);
			}
			print(sum);
		}else if(makelower(temp) == "random"){
			random();
		}else if(makelower(temp) == "quit"){
			quit();
			
			return true;
		}else{
			help();
		}
		return false;

		
        	cout << endl;
	}

	public:
		Dictionary()	// Default constructor
		 { }

	/**
	 *  Run the main dictionary user interface
	 */
	void run_ui() {
		// print out header
		cout << "+------------------------------------------+" << endl;
		cout << "|-- Welcome to the best dictionary evar! --|" << endl;
		cout << "+------------------------------------------+" << endl;
		
		string instr;
		bool check = false;
		cout << " Enter command (^D or EOF quits): ";
		
		// read in user input until eof
		while (getline(cin, instr)) {
			cout << endl << " --debug-- Entered command: " << instr << endl;
			check = parseline(instr);
			// call function based on line contents
			// print results
			if(check == true)
				break;
			instr.clear();

			cout << "Enter command: ";
		}
		cout << endl;
	}

	void help(){
		cout << "help	-> print out command help" << endl;
		cout << "add “word” “definition”	-> Add (or update!) a word and it’s definition" << endl;
		cout << "remove “word”	-> Remove a given word" << endl;
		cout << "define “word”	-> Define a word by printing out it’s definition" << endl;
		cout << "load “filename”	-> Load in a JSON file of dictionary words" << endl;
		cout << "unload “filename”	-> Remove words from a given JSON file of dictionary words" << endl;
		cout << "size	-> Print out current number of words in the dictionary" << endl;
		cout << "clear	-> Remove ALL words from the dictionary" << endl;
		cout << "print [#words]	-> Print out all words, unless user gives a maximum number" << endl;
		cout << "random	-> Print out a single word chosen randomly from the dictionary" << endl;
		cout << "quit	->-> Quit the user interface and shut down" << endl;
	}
	
	void add(const string word, const string def){
		Word newWord(word, def);
		bool check = _dict.insert(word, newWord);
		if(check == false)
			cout << "Unable to Enter Word" << endl;
	}
	
	void remove (const string word){
		int check = _dict.remove(word);
		if (check < 1){
			cout <<"Unable to remove: " << word << endl;
		}else {
			cout << "Successfully Removed" << word << endl;
		}
	}
	
	void define(const string word){
		Word* temp = _dict.find(word);
		cout << temp->definition << endl;
	}
	
	void load(const string filename){
		ifstream infile(filename);
		
		Word newWord;
		
		bool check = false;
		string lines;
		getline(infile,lines);
		getline(infile,lines);
		
		while(check == false)
		{
			getline(infile,lines,':');
			if(lines[2] == ']'){
				check = true;
			}else{
				getline(infile,lines,'"');
				getline(infile,lines,'"');
				newWord.myword = makelower(lines);
				getline(infile,lines,':');
				getline(infile,lines,'"');
				getline(infile,lines,'"');
				newWord.definition = lines;
				getline(infile,lines);
				_dict.insert(newWord.myword,newWord);
			}
		}
		infile.close();
	}
	
	void unload(const string filename){
		ifstream infile(filename);
		
		bool check = false;
		string dump;
		getline(infile,dump);
		getline(infile,dump);
		
		while(check == false)
		{
			getline(infile,dump,':');
			if(dump[2] == ']'){
				check = true;
			}else{
				getline(infile,dump,'"');
				getline(infile,dump,'"');
				_dict.remove(makelower(dump));
				getline(infile,dump);
			}
		}
		infile.close();
	}
	
	
	void size(){
		cout << _dict.currentSize << endl;
	}
	
	void clear(){
		_dict.clear();
	}
	
	void print(int numWords = -1){
		srand (time(NULL));
		if(numWords == -1)
		{
			for(int i = 0; i < _dict.bucket_count(); i++)
			{
				list<Word> temp = _dict.printhelp(i);
				for(list<Word>::iterator place = temp.begin(); place != temp.end();place++)
					cout << place->myword << " , " << place->definition << endl;
			}
		}else{
			int count = 0, k, j, p;
			for(int i = 0; i < numWords; i++){
				list<Word>::iterator place;
				j = rand() % _dict.bucket_count();
				list<Word> temp = _dict.printhelp(j);
				if(!temp.empty()){
					k = rand() % temp.size();
					p = 0;
					
					for(place = temp.begin();p < k; ++p)
						place++;
					cout << place->myword << " , " << place->definition << endl;
				}
			}
		}
	}
	void random(){
		print(1);
	}
	void quit(){
		cout << "Goodbye" << endl;
		clear();
	}
	
	
	string makelower(string temp){
		for(int i = 0; i < temp.size(); ++i)
		{
			if(temp[i] <= 90 && temp[i] >= 65)
				temp[i] += 32;
		}
		return temp;
	}




};



#endif
