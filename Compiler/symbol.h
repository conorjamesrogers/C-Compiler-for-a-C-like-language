// $Id: symbol.h,v 1.10 2016-10-06 16:42:35-07 - - $

#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <iostream>
using namespace std;

#include "auxlib.h"
#include "lyutils.h"
#include "astree.h"



using attr_bitset = bitset<ATTR_bitset_size>;

// struct location {
//    size_t filenr;
//    size_t linenr;
//    size_t offset;
// };
struct symbol;

using symbol_table = unordered_map<string*,symbol*>; 
using symbol_entry = symbol_table::value_type;



struct symbol {

   attr_bitset attributes;
   vector<symbol*>* parameters;
   size_t block_nr =0;
   size_t filenr;
   size_t linenr;
   size_t offset;
   string lexinfo;
   string print_string;
   symbol_table* fields;
   string special_case;

};


void set_attr(astree* node, symbol* s,bool t = false);

symbol* est_symbol(astree* node, bool t = false);

symbol* est_func(astree* node);

string generate_attr_out(astree* node);

void setup_symboltable();

bool typecheck(astree* root);

symbol* retrieve_symbol(astree* node);

bool symbol_run(astree* root, FILE* outfile);

void oil_dump(astree* root, FILE* outfile);

string block_traversal(astree* node, FILE* outfile);

// void get_func_names(astree* root);

// void destroy (symbol* tree1, symbol* tree2 = nullptr);

// void errllocprintf 
//(const location&, const char* format, const char*);

#endif

