#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

#include "symbol.h"
#include "auxlib.h"
#include "lyutils.h"
#include "astree.h"


vector<symbol_table*> symbol_stack;

vector<astree*> strings;

vector<int> blocks;

vector<astree*> global_queue;

int block_count = 0;
// int block_int = 0;
symbol_table structs;
symbol_table idents;
symbol_table var;
symbol_table* f = new symbol_table;
// symbol_table

extern FILE* outfile;

// The lval attribute appears on any node in the AST which can
// receive an assignment.  This includes all variables (global,
// local, or parameter) and the result of the indexing ([]) and
// selector (.) operators.


//todo: 
// 1) typechecking ;__;
// 2) fix .ast output to list attributes
// just read the output guidlines




void set_attr(astree* node, symbol* s, bool t) {
   if(!t)
   { s->block_nr = blocks.back();
    }
    else{
        s->block_nr = blocks.end()[-2];
    }

    node->block_nr = s->block_nr;

    s->filenr = node->lloc.filenr;
    s->linenr = node->lloc.linenr;
    s->offset = node->lloc.offset;
    // 3 identifier types: void types, primitive types, 
    // and reference types in a language
    //   in this language:
    //     1 void type: void
    //     1 primitive type: int
    //     acouple reference type: created by struct 
    // definitions, arrays [], string, null
    switch(node->symbol) {
        case TOK_INT: 
        {s->attributes[ATTR_int] = 1;break;}
        case TOK_VOID:
        {s->attributes[ATTR_void] = 1;break;}
        case TOK_NULL: 
        {s->attributes[ATTR_null] = 1;break;}
        case TOK_STRING:
        {s->attributes[ATTR_string] = 1;break;}
        case TOK_TYPEID:
        {
            s->attributes[ATTR_struct] = 1;
            s->lexinfo = string(*(node->lexinfo));
            s->special_case = string(*(node->lexinfo));

            // s->struct_name
            break;
        }

    }

}

// symbol* est_func(astree* node) {

// }

// string generate_attr_out(astree* node){


// return "";

// }

symbol* est_symbol(astree* node,bool t) {
    symbol* s = new symbol;
    set_attr(node, s,t);
    s->attributes[ATTR_lval] = 1;
    s->attributes[ATTR_variable] = 1;
    return s;
}



void setup_symboltable() {
   symbol_stack.push_back(new symbol_table);
   blocks.push_back(block_count++);
}

// symbol* getSymbol(astree* node) {
//     for(int i = symbol_stack.size()-1; )

// }
void dump(FILE* outfile, symbol* s, const char* n) {
 
 fprintf(outfile, "%s (%zu.%zu.%zu) %s\n", 
      n,s->filenr, s->linenr, 
      s->offset, s->print_string.c_str());

    // for (symbol* child: s->parameters) {
    //     dump (outfile, child);
    // }

}

symbol* get_symbol (astree* node) {
   string* name = const_cast<string*>(node->lexinfo);
   for(int i = symbol_stack.size()-1; i >= 0; --i) {
      if(symbol_stack[i] == nullptr) {
         continue;
      }
      if(symbol_stack[i]->find(name) != symbol_stack[i]->end()) {
     if(symbol_stack[i]->at(name)->attributes[ATTR_function] == 0){
        return symbol_stack[i]->at(name);
     }
      }
   }
   return NULL;
}



bool grammar_match_rule_a(attr_bitset attr1, attr_bitset attr2, 
                              string struct1, string struct2) {

    if((struct2 == ".") || (struct1 == "."))
        return true;

    if((struct1 == "+") || struct2 == "+")
        return true;
    if((struct1 == "-") || struct2 == "-")
        return true;
    if((struct1 == "/") || struct2 == "/")
        return true;
    if((struct1 == "*") || struct2 == "*")
        return true;
    
    if((struct2 == "(") || (struct1 == "("))
        return true;

    if((struct2 == "null") || (struct1 == "null"))
        return true;

    if((struct2 == "new") || (struct1 == "new"))
        return true;

     if((struct2 == "") || (struct1 == ""))
        return true;

    if((attr1[ATTR_int] && attr2[ATTR_array]) 
        || (attr2[ATTR_int] && attr1[ATTR_array]) )
        return true;

    if((attr1[ATTR_string] && attr2[ATTR_array])
        || (attr1[ATTR_array] && attr2[ATTR_string]))
        return true;

    if((attr1[ATTR_vaddr] || attr2[ATTR_vaddr]))
        return true;


    if((attr1[ATTR_null] && attr2[ATTR_struct])
    || (attr1[ATTR_struct] && attr2[ATTR_null])
    || (attr1[ATTR_null] && attr2[ATTR_string])
    || (attr1[ATTR_string] && attr2[ATTR_null])
    || (attr1[ATTR_null] && attr2[ATTR_array])
    || (attr1[ATTR_array] && attr2[ATTR_null]))
     return true;

 // (a) Two types are compatible if 
 // they are exactly the same type;  or if
//     one type is any reference type and the 
 // other is null.  In the type
//     checking grammar, in each rule, types in italics must be
//     substituted consistently by comp
 // atible types.  Types are
//     compatible only if the array attribute 
 // is on for both or off for
//     both.

    

    // if(attr2[ATTR_int]=1)
    //     printf("\n%s\n",struct2.c_str());

    if ((attr1[ATTR_int] && attr2[ATTR_int])
    || (attr1[ATTR_int] && attr2[ATTR_array]) 
    || (attr2[ATTR_int] && attr1[ATTR_array]) 
    || (attr1[ATTR_lval] && attr2[ATTR_int])
    || (attr2[ATTR_lval] && attr1[ATTR_int])
    || (attr1[ATTR_lval] && attr2[ATTR_int])
    || (attr2[ATTR_lval] && attr1[ATTR_int])    
    || (attr1[ATTR_string] && attr2[ATTR_string])
    || (attr1[ATTR_array] && attr2[ATTR_array])
    || (attr1[ATTR_struct] && attr2[ATTR_struct])
    || (attr1[ATTR_void] && attr2[ATTR_void])
    || ((attr1[ATTR_struct] && attr2[ATTR_struct]) 
      &&(struct1 != struct2)
      )
    )
      return true;

    printf("\n%s != ? %s\n",struct1.c_str(),struct2.c_str());
   return false;
}

void dump_string(FILE* outfile, string* n, symbol* s ) {
    attr_bitset a = s->attributes;
    string out_s;
    // string name;
    // fprintf(outfile, " ");


    for (uint i = 0; i < blocks.size()-1; ++i) {
        fprintf(outfile, "   ");
    }

    // if(s->attributes[ATTR_param] == 1)
    //     fprintf(outfile, "   ");

// enum { 
//    ATTR_void, ATTR_int, ATTR_null, ATTR_string, ATTR_struct,
// ATTR_array, ATTR_function, ATTR_variable, 
    // ATTR_field, ATTR_typeid,
// ATTR_param, ATTR_lval, ATTR_const, 
    // ATTR_vreg, ATTR_vaddr, ATTR_bitset_size,
// };

    if (a[ATTR_field] == 0) 
        out_s += "{"+to_string(s->block_nr)+"} ";

    if (a[ATTR_field] == 1) 
        out_s += "field {" + s->lexinfo + "} ";

    if (a[ATTR_void] == 1) 
        out_s += "void ";

     if (a[ATTR_int] == 1) 
        out_s += "int ";

    if (a[ATTR_null] == 1) 
        out_s += "null ";

    if (a[ATTR_string] == 1) 
        out_s += "string ";

    if (a[ATTR_struct] == 1) 
        out_s += "struct \"" + s->lexinfo + "\" ";

    if (a[ATTR_array] == 1)
        out_s += "array ";

    if (a[ATTR_function] == 1) 
         out_s += "function ";    

    if (a[ATTR_variable] == 1) 
         out_s += "variable ";

    if (a[ATTR_lval] == 1) 
        out_s += "lval ";

    if (a[ATTR_param] == 1) 
        out_s += "param ";

    if (a[ATTR_const] == 1) 
        out_s += "const ";

    if (a[ATTR_vreg] == 1) 
        out_s += "vreg ";

    if (a[ATTR_vaddr] == 1) 
        out_s += "vaddr ";   


    // fprintf(outfile, "%s (%zu.%zu.%zu) %s\n", 
    //   name.c_str(),s->filenr, s->linenr, 
    //   s->offset, out_s.c_str());
    s->print_string += out_s;

    dump(outfile, s, n->c_str());
}



bool typecheck(astree* root) {

    switch (root->symbol) {
        

        case TOK_NULL: {
         root->attributes[ATTR_null] = 1;
         root->attributes[ATTR_const] = 1;
         break;
        }
        case TOK_STRINGCON: {
         root->attributes[ATTR_const] = 1;
         root->attributes[ATTR_string] = 1;

         break;
        }
        case TOK_FIELD: {
            root->attributes[ATTR_field]=1;
            root->attributes[ATTR_vaddr] = 1;
            root->attributes[ATTR_lval] = 1;
            root->attributes[ATTR_variable] = 1;

        }
        case TOK_INTCON: {
         root->attributes[ATTR_const] = 1;
         root->attributes[ATTR_int] = 1;
         break;
        }
        case TOK_CHARCON: {
         root->attributes[ATTR_const] = 1;
         root->attributes[ATTR_int] = 1;
         break;
        }
        case TOK_INT: {
         root->attributes[ATTR_int] = 1;
         break;
        }
        case TOK_STRING: {
         root->attributes[ATTR_string] = 1;
         break;
        }
        case TOK_ARRAY: {
         attr_bitset attrs = root->children[0]->attributes;
         if(attrs[ATTR_void]
            || attrs[ATTR_void]
            || (attrs[ATTR_struct]
               && string(*(root->children[0]->lexinfo)) == "")) {
            cerr << "Invalid array type" << endl;
            return false;
         }
         if(attrs[ATTR_int])
            root->attributes[ATTR_int] = 1;
         else if(attrs[ATTR_string])
            root->attributes[ATTR_string] = 1;

         root->attributes[ATTR_vreg] = 1;
         root->attributes[ATTR_array] = 1;
         break;
      }
      case TOK_TYPEID: {
            string* name = const_cast<string*>(root->lexinfo);
            if(structs.find(name) == structs.end()) {
               break;
            }
            symbol* str = structs.at(name);
            root->attributes[ATTR_struct] = 1;
            string(*(root->lexinfo)) = str->lexinfo;
            root->struct_ = str->lexinfo;
         break;
      }
      case TOK_VOID: {
         
         
         break;
      }
      case TOK_VARDECL: {
         astree* n;
         if(root->children[0]->symbol != TOK_ARRAY)
            n = root->children[0]->children[0];
         else
            n = root->children[0]->children[1];

         if(!grammar_match_rule_a(n->attributes,
            root->children[1]->attributes,
            string(*(n->lexinfo)), 
            string(*(root->children[1]->lexinfo)))) {
            cerr << "Incompatible types" << endl;
            return false;
         }
        break;
      }
      case TOK_RETURNVOID: {
         root->attributes[ATTR_void] = 1;
         // aaaaaaaaaaaaahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
         break;
      }
      case TOK_RETURN: {
        //maybe for asg5
         break;
      }
      case '=': {

         if(!grammar_match_rule_a(root->children[0]->attributes,
            root->children[1]->attributes,
            string(*(root->children[0]->lexinfo)),
            string(*(root->children[1]->lexinfo)))
            || !root->children[0]->attributes[ATTR_lval]) {
            cerr << "Incorrect assignment" << endl;
            return false;
         }
root->attributes[ATTR_string] = 
root->children[0]->attributes[ATTR_string];
root->attributes[ATTR_int] = 
root->children[0]->attributes[ATTR_int];
root->attributes[ATTR_struct] = 
root->children[0]->attributes[ATTR_struct];
root->attributes[ATTR_array] = 
root->children[0]->attributes[ATTR_array];
// root->lexinfo = root->children[0]->lexinfo;
root->struct_ = root->children[0]->struct_;
root->attributes[ATTR_vreg] = 1;
         break;
      }
      case TOK_POS:
      case TOK_NEG: {
         if(!root->children[0]->attributes[ATTR_int]
            && root->children[0]->attributes[ATTR_array]){
            cerr << "Cannot use UNOP on this type" << endl;
            return false;
         }

         root->attributes[ATTR_int] = 1;
         root->attributes[ATTR_vreg] = 1;
         break;
      }
      case TOK_NEW: {
         root->attributes = root->children[0]->attributes;
         // root->lexinfo = root->children[0]->lexinfo;
         root->struct_ = root->children[0]->struct_;
         root->attributes[ATTR_vreg] = 1;
         break;
      }
      case TOK_CALL: {
         vector<astree*> params;
         for(uint i = 1; i < root->children.size(); ++i) {
            params.push_back(root->children[i]);
         }

         string* name = const_cast<string*>(
            root->children[0]->lexinfo);

         symbol* sym;
         if(idents.find(name) != idents.end()) {
            sym = idents.at(name);
         } else {
            cerr << "Function not declared" << endl;
            return false;
         }

         if(params.size() != sym->parameters->size()) {
            cerr << "Incorrect number of parameters given" << endl;
            return false;
         }
         if(params.size() > 0) {
            for(uint i = 0; i < params.size()-1; ++i) {
               if(!grammar_match_rule_a(params[i]->attributes,
                     sym->parameters->at(i)->attributes,
                     string(*(params[i]->lexinfo)),
                     sym->parameters->at(i)->lexinfo)) {
                  cerr << "Function parameters do not match" << endl;
                  return false;
               }
            }
         }
         root->attributes = sym->attributes;
         root->attributes[ATTR_vreg] = 1;
         root->attributes[ATTR_function] = 1;
         string(*(root->lexinfo)) = sym->lexinfo;
         root->struct_ = sym->special_case;
         break;
      }
      case '-':
      case '*':
      case '/':
      case '%':
      case '+': {
         astree* root1 = root->children[0];
         astree* root2 = root->children[1];
         if(!(root1->attributes[ATTR_int]
            && root2->attributes[ATTR_int])
            && (root1->attributes[ATTR_array]
            || root2->attributes[ATTR_array])) {
            cerr << "Incompatible BINOP types" << endl;
            return false;
         }
         root->attributes[ATTR_int] = 1;
         root->attributes[ATTR_vreg] = 1;
         break;
      }
      case TOK_EQ:
      case TOK_NE:
      case TOK_GT:
      case TOK_LE:
      case TOK_LT:
      case TOK_GE: {
         if(!grammar_match_rule_a(root->children[0]->attributes,
            root->children[1]->attributes, 
            string(*(root->children[0]->lexinfo)),
            string(*(root->children[1]->lexinfo)))) {
            cerr << "Invalid comparison" << endl;
            return false;
         }

         root->attributes[ATTR_int] = 1;
         root->attributes[ATTR_vreg] = 1;
         break;
      }
      case TOK_NEWSTRING: {
         if(!root->children[1]->attributes[ATTR_int]) {
            cerr << "Size is not integer" << endl;
            return false;
         }
         root->attributes[ATTR_vreg] = 1;
         root->attributes[ATTR_string] = 1;
         break;
      }
      case TOK_IDENT: {
         string* name = const_cast<string*>(root->lexinfo);
         // printf("name: %s", root->lexinfo->c_str());
         symbol* sym = get_symbol(root);

          if(sym == NULL) {
            if(idents.find(name) != idents.end()) { 
               sym = idents[name];
            } else if(var.find(name) != var.end()) {    
                sym = var[name];
            }
            else {
               cerr << "Undeclared identifier" << endl;
               return false;
            }
         }
         root->attributes = sym->attributes;

         root->block_nr = sym->block_nr;
         // string(*(root->lexinfo)) = sym->lexinfo;
          root->struct_ = sym->special_case;


         break;
      }
      case TOK_INDEX: {

        string x(root->children[1]->lexinfo->c_str());

        if(!(x == ".")){
            if(!root->children[1]->attributes[ATTR_int]) {
                cerr << "Cannot access array without integer";
                return false;
             }

             if(!(root->children[0]->attributes[ATTR_string])
                && !(root->children[0]->attributes[ATTR_array])) {
                cerr << "Not proper type for array access" << endl;
                return false;
             }
        }

         
         if(root->children[0]->attributes[ATTR_string]
            && !root->children[0]->attributes[ATTR_array]) {
            root->attributes[ATTR_int] = 1;
         }
         else {
            root->attributes[ATTR_int] = 
            root->children[0]->attributes[ATTR_int];
            root->attributes[ATTR_string] = 
            root->children[0]->attributes[ATTR_string];
            root->attributes[ATTR_struct] = 
            root->children[0]->attributes[ATTR_struct];
         }

         root->attributes[ATTR_array] = 0;
         root->attributes[ATTR_vaddr] = 1;
         root->attributes[ATTR_lval] = 1;
         root->attributes[ATTR_variable] = 0;
         // root->lexinfo = root->children[1]->lexinfo;
         root->struct_ = root->children[1]->struct_;
         break;
      }
      case '.': {

            string name_v(root->children[0]->struct_);

            if(name_v == "."){
                astree* period = root->children[0];
                period->attributes = period->children[0]->attributes;

            }

            // if(!root->children[0]->attributes[ATTR_struct]) {
            // cerr << "Invalid usage of field selection";
            // return false;
            // }

// (f) Field selection sets the selector (.) attribute as 
            // follows:  The
//     left operand must be a struct type or an error message 
            // is
//     generated.  Look up the field in the structure and copy 
// its type
//     attributes to the selector, removing the field attribute 
// and
//     adding the vaddr attribute.

// string* name = const_cast<string*>(root->children[0]->lexinfo);
// // if(f->find(name) == f->end()) {
// //    cerr << "Cannot reference field of 
            // undefined struct" << endl;
// //    return false;
// // }
// symbol* str_sym = f->at(name);
// symbol_table* str = new symbol_table;
// symbol_entry entry (name,str_sym);
// str->insert(entry);

// string* field_name = const_cast<string*>(
//    root->children[0]->lexinfo);

// root->attributes = str->at(field_name)->attributes;
// root->struct_ = str->at(field_name)->lexinfo;

            root->attributes[ATTR_field] = 0;
            root->attributes[ATTR_vaddr] = 1;
            root->attributes[ATTR_lval] = 1;
            root->attributes[ATTR_variable] = 1;
            root->struct_ = name_v;
            break;
        }
      
      default: break;
   }


    //... lots of case blocks : - (


  
//     2.4  Type checking



   return true;
}



bool symbol_run (astree* root, FILE* outfile) {
        //ahahahahahaha



    switch (root->symbol) {
        case TOK_BLOCK: {

// (g) Whenever you see a block, increment the global 
            // block count and
//     push that number on the block count stack.  
            // Then store the block
//     number in the AST node and traverse the block.  
// When leaving a
//     block, pop the block number from the stack.  
// Each block will have
//     a unique number, with 0 being the global block, 
// and the others
//     numbered in sequence 1, 2, 3, etc.

            blocks.push_back(block_count++);
            if(root->children[0]->symbol == TOK_VARDECL){}
            symbol_stack.push_back(nullptr);
            // blocks.pop_back();
            break;
        }
        case TOK_FUNCTION: {
            //getting function name for search and print
            string* func_name = 
    const_cast<string*>(root->children[0]->children[0]->lexinfo);
            


            if(symbol_stack.back() == nullptr)
            {
                symbol_stack.pop_back();
                symbol_stack.push_back(new symbol_table);
            }

            symbol* sf = new symbol;
            set_attr(root->children[0]->children[0], sf);
            sf->attributes[ATTR_function] = 1;

            dump_string(outfile,func_name, sf);

            astree* node = root->children[0];

            if(node->symbol == TOK_ARRAY){
                node->children[1]->attributes = sf->attributes;
                node->children[1]->struct_ = sf->special_case;

            }else{
                node->children[0]->attributes = sf->attributes;
                node->children[0]->struct_ = sf->special_case;

                switch(node->symbol){
                    case TOK_INT: {
                        sf->attributes[ATTR_int] = 1;
                        break;
                    }
                    case TOK_VOID: {
                        sf->attributes[ATTR_void] = 1;

                        break;
                    }
                    case TOK_STRING: {
                        sf->attributes[ATTR_string] = 1;

                        break;
                    }
                    case TOK_STRUCT: {
                        sf->attributes[ATTR_struct] = 1;

                        break;
                    }
                    default: break;
                }
            }

// if(root->attributes[ATTR_void]) {
//          fprintf(outfile, "        __%s(", 
//             (root->children[0]->lexinfo)->c_str());
//       } else if(root->attributes[ATTR_int]) {
//            attr_bitset attr = root->attributes;
//            if(attr[ATTR_int]) {
//               reg += "i" + to_string(num);
//            } else if(attr[ATTR_string]) {
//               reg += "s" + to_string(num);
//            } else if(attr[ATTR_struct]) {
//               reg += "p" + to_string(num);
//            }
//            num++;
//          fprintf(outfile, "        int %s = __%s (", reg.c_str(), 
//             (root->children[0]->lexinfo)->c_str());
//       } else if(root->attributes[ATTR_string]) {
//            attr_bitset attr = root->attributes;
//            if(attr[ATTR_int]) {
//               reg += "i" + to_string(num);
//            } else if(attr[ATTR_string]) {
//               reg += "s" + to_string(num);
//            } else if(attr[ATTR_struct]) {
//               reg += "p" + to_string(num);
//            }
//            num++;
//          fprintf(outfile, "        char* %s = __%s (", reg.c_str(), 
//             (root->children[0]->lexinfo)->c_str());
//       } else if(root->attributes[ATTR_struct]) {
//            attr_bitset attr = root->attributes;
//            if(attr[ATTR_int]) {
//               reg += "i" + to_string(num);
//            } else if(attr[ATTR_string]) {
//               reg += "s" + to_string(num);
//            } else if(attr[ATTR_struct]) {
//               reg += "p" + to_string(num);
//            }
            //set global block
            sf->block_nr = 0;
            root->children[0]->children[0]->block_nr=0;

            sf->parameters = new vector<symbol*>;
            blocks.push_back(block_count++);

            symbol_stack.push_back(new symbol_table);

            //iterate through paramlist of function
            //special rules for array parameter

        //     FUNCTION "" (7.22.1)
        // |  |  VOID "void" (7.22.1)
        // |  |  |  DECLID "insertion_sort" (7.22.6)
        // |  |  PARAMLIST "(" (7.22.21)
        // |  |  |  INT "int" (7.22.22)
        // |  |  |  |  DECLID "size" (7.22.26)
        // |  |  |  ARRAY "[]" (7.22.38)
        // |  |  |  |  STRING "string" (7.22.32)
        // |  |  |  |  DECLID "array" (7.22.41)

// FUNCTION "" (4.2.5) {0} 
// |  |  TYPEID "node" (4.2.5) {0} struct "node" 
// |  |  |  DECLID "func" (4.2.10) {0} function 
// |  |  PARAMLIST "(" (4.2.15) {0} 
// |  |  |  TYPEID "node" (4.2.16) {1} struct "node" 
// |  |  |  |  DECLID "head" (4.2.21) {1} struct 
            // "head" variable lval param (4.4.1)
            for (size_t child = 0; 
                child < root->children[1]->children.size(); 
                ++child) {
                astree* node = root->children[1]->children[child];
                symbol* parameter = new symbol;
                // blocks.push_back(block_int++);
                // blocks.push_back(block_count++);




                string* p_name;

                if(node->symbol == TOK_ARRAY)
                {
                    parameter = est_symbol(node->children[0]);
                    parameter->attributes[ATTR_array]=1;
                    parameter->attributes[ATTR_param]=1;
                    node->children[1]->attributes = 
                    parameter->attributes;
                    node->children[1]->struct_ = 
                        parameter->special_case;

                    // node->children[0]->
                    // node->children[0]->
                    // node->children[0]->
    // string p_name_v(node->children[1]->lexinfo->c_str());
                    p_name = 
                const_cast<string*>(node->children[1]->lexinfo);

                }
                else
                {
                    parameter = est_symbol(node);
                    parameter->attributes[ATTR_param]=1;

                    node->children[0]->attributes = 
                    parameter->attributes;
                    node->children[0]->block_nr = 
                        parameter->block_nr;
                    node->children[0]->struct_ = 
                        parameter->special_case;
                    if(node->children[0]->symbol == TOK_TYPEID){
                        node->children[0]->children[0]->struct_ = 
                            parameter->special_case;

                    }


    // string p_name_v(node->children[0]->lexinfo->c_str());
                    p_name = 
                const_cast<string*>(node->children[0]->lexinfo);

                }



                sf->parameters->push_back(parameter);

                symbol_entry entry(p_name,parameter);

                symbol_stack.back()->insert(entry);

                dump_string(outfile,p_name,parameter);

            }

            if(idents.find(func_name) != idents.end()) {
    if(idents[func_name]->attributes[ATTR_function] == 1)
    {
if(idents[func_name]->parameters != sf->parameters)
{
    fprintf(stderr, "function %s declared parameter mismatch\n",
        func_name->c_str());
}
                }
            }

            symbol_entry entry(func_name,sf);

            symbol_stack.back()->insert(entry);

            idents.insert(entry);

            fprintf(outfile,"\n");

            // blocks.push_back(block_count--);


            // else{
            //     // idents.insert()
            // }




            // printf("lexinfo baby: %s\n\n",func_name.c_str());

            //use name to run through identifiers table
            //if not in, put it in


// (h) Whenever you see a function or prototype, 
            // perform the block
//     entering operation, and traverse the function.  
// Treat the function
//     as if it were a block.  The parameters are 
// inserted into the
//     symbol table as owned by the function's 
// block.


// (i) If the function is already in the symbol 
// table, but only as a
//     prototype, match the prototype of the new 
// function with the
//     previous one of the same name.  If they
 // differ, print an error
//     message.  If the function is already in 
 // the symbol table as a
//     function, print an error message about a
 // duplicate declaration.

// (j) If the function is not in the symbol table, 
 // enter it, along with
//     its parameters.  If this is an actual function, 
// traverse the block
//     as you normally would, with the block number
 // being the next one in
//     line.  A function creates at least two blocks, 
 // one for itself, and
//     one for the block of statements that it owns.

// 
            break;
        }
        case TOK_PROTOTYPE: {


        
              string* func_name;

            symbol* sf = new symbol;
            set_attr(root->children[0]->children[0], sf);
            sf->attributes[ATTR_function] = 1;
            astree* node = root->children[0];


            if(node->symbol == TOK_ARRAY){
                node->children[1]->attributes = sf->attributes;
                node->children[0]->attributes[ATTR_array] =1;
                func_name = 
        const_cast<string*>(root->children[0]->children[1]->lexinfo);

            }else{
                node->children[0]->attributes = sf->attributes;
                func_name = 
        const_cast<string*>(root->children[0]->children[0]->lexinfo);

                switch(node->symbol){
                    case TOK_INT: {
                        sf->attributes[ATTR_int] = 1;
                        break;
                    }
                    case TOK_VOID: {
                        sf->attributes[ATTR_void] = 1;

                        break;
                    }
                    case TOK_STRING: {
                        sf->attributes[ATTR_string] = 1;

                        break;
                    }
                    case TOK_STRUCT: {
                        sf->attributes[ATTR_struct] = 1;

                        break;
                    }
                    default: break;
                }
            }


            if(symbol_stack.back() == nullptr)
            {
                symbol_stack.pop_back();
                symbol_stack.push_back(new symbol_table);

            }

           

            dump_string(outfile,func_name, sf);



            // printf("%s",node->symbol);

// |  PROTOTYPE "" (6.37.7)
// |  |  ARRAY "[]" (6.37.7)
// |  |  |  STRING "string" (6.37.1)
// |  |  |  DECLID "getargv" (6.37.10)




            //set global block
            sf->block_nr = 0;
            root->children[0]->children[0]->block_nr=0;

            sf->parameters = new vector<symbol*>;
            blocks.push_back(block_count++);

            symbol_stack.push_back(new symbol_table);

            //iterate through paramlist of function
            //special rules for array parameter

        //     FUNCTION "" (7.22.1)
        // |  |  VOID "void" (7.22.1)
        // |  |  |  DECLID "insertion_sort" (7.22.6)
        // |  |  PARAMLIST "(" (7.22.21)
        // |  |  |  INT "int" (7.22.22)
        // |  |  |  |  DECLID "size" (7.22.26)
        // |  |  |  ARRAY "[]" (7.22.38)
        // |  |  |  |  STRING "string" (7.22.32)
        // |  |  |  |  DECLID "array" (7.22.41)
            for (size_t child = 0; 
                child < root->children[1]->children.size(); 
                ++child) {
                astree* node = root->children[1]->children[child];
                symbol* parameter = new symbol;
                node->children[0]->struct_ = parameter->special_case;
                node->children[0]->block_nr = parameter->block_nr;


                // blocks.push_back(block_int++);



                string* p_name = new string;

                parameter->attributes[ATTR_param]=1;

                sf->parameters->push_back(parameter);



if(node->symbol == TOK_ARRAY)
{
    parameter = est_symbol(node->children[0]);
    parameter->attributes[ATTR_array]=1;
    node->children[1]->attributes = 
    parameter->attributes;
    string p_name_v(node->children[1]->lexinfo->c_str());
    p_name = const_cast<string*>(node->children[1]->lexinfo);

}
else
{
    parameter = est_symbol(node);
    node->children[0]->attributes = parameter->attributes;
    string p_name_v(node->children[0]->lexinfo->c_str());
    p_name = const_cast<string*>(node->children[0]->lexinfo);
}




                symbol_entry entry(p_name,parameter);

                symbol_stack.back()->insert(entry);

                dump_string(outfile,p_name,parameter);


            }

if(idents.find(func_name) != idents.end()) {
    if(idents[func_name]->attributes[ATTR_function] == 1)
    {
        if(idents[func_name]->parameters != sf->parameters)
        {
            fprintf(stderr, 
                "function %s declared parameter mismatch\n",
                func_name->c_str());
        }
    }
}

            symbol_entry entry(func_name,sf);

            symbol_stack.back()->insert(entry);

            idents.insert(entry);




            //^^ see function

            break;
        }
        case TOK_STRUCT: {

//     STRUCT "struct" (4.1.2)
// |  |  TYPEID "node" (4.1.9)
// |  |  '{' "{" (4.1.14)
// |  |  |  INT "int" (4.1.16)
// |  |  |  |  FIELD "foo" (4.1.20)
// |  |  |  TYPEID "node" (4.1.25)
// |  |  |  |  FIELD "link" (4.1.30)

            // blocks.push_back(block_int++);

string struct_name_v(root->children[0]->lexinfo->c_str());
string* struct_name = 
const_cast<string*>(root->children[0]->lexinfo);
            symbol* ss = new symbol;

            ss->lexinfo = struct_name_v;
            ss->special_case = struct_name_v;

            set_attr(root, ss);
            ss->block_nr = 0;
            root->block_nr =0;
            ss->attributes[ATTR_struct] = 1;

            root->attributes = ss->attributes;

            symbol_entry entry(struct_name, ss);

            structs.insert(entry);

            dump_string(outfile, struct_name, ss);

            ss->fields = new symbol_table;
            root->struct_ = ss->special_case;

            if(root->children.size() > 1){

                //its a regular struct!
for (size_t child = 0; 
    child < root->children[1]->children.size(); 
    ++child) {
    astree* node = root->children[1]->children[child];
    string name_v(node->lexinfo->c_str());
    string* name = const_cast<string*>(node->lexinfo);

    //reference to another struct or somesuch
    if(node->symbol == TOK_TYPEID) {
        if(structs.find(name) == structs.end()){
            fprintf(stderr,"no struct with name %s\n",name->c_str());
            break;
        }
    }

    fprintf(outfile,"   ");

    symbol* s = new symbol;

    string* f_name;

    if(node->symbol == TOK_ARRAY) {

        f_name = const_cast<string*>(
            node->children[1]->lexinfo);
        set_attr(node->children[0],s);
        s->attributes[ATTR_array]=1;
        s->attributes[ATTR_field]=1;
        node->children[0]->block_nr=0;
        node->children[1]->struct_ = struct_name_v;
        s->special_case = struct_name_v;

    }
    else {
        f_name = const_cast<string*>(
            node->children[0]->lexinfo);
        set_attr(node,s);
        s->attributes[ATTR_field]=1;
        node->block_nr = 0;
        node->children[0]->struct_ = struct_name_v;
        s->special_case = struct_name_v;
    }
    s->attributes[ATTR_field] =1;
    s->lexinfo = struct_name_v;

    s->block_nr = 0;
    symbol_entry entry(f_name,s);
    ss->fields->insert(entry);
    f->insert(entry);

    dump_string(outfile,f_name,s);

            }


            }

            symbol_entry entry1(struct_name, ss);



            ss->fields->insert(entry1);
            f->insert(entry1);

            fprintf(outfile,"\n");



// (b) Whenever a structure definition is 
            // found, create a new entry in
//     the structure hash, using the typei
// d as a key.  The block number
//     is 0 because structures are declare
// d globally.  Then create a hash
//     table and insert each field into th
// at hash table, pointed at by
//     this structure table entry.  Field 
// names are also in block 0.

// 
// (c) The structure name must be inserted
 // into the structure hash before
//     the field table is processed, becau
 // se type type of a field may be
//     the structure itself.
// 

// (d) If a structure name is found that 
// is not in the hash, insert it
//     with a null pointer for the field table.  If it later becomes
//     defined, fill in the fields.
// 

// (e) If an incomplete structure has a fi
// eld selected from it, or if it
//     follows new, or if it used in a dec
// laration of other than a field,
//     print an error message about referring to an incomplete type.

// 
// (f) All other identifiers are inserted 
// into the main symbol tables.


            break;
        }
        case TOK_VARDECL: {

//VARDECL "=" (4.6.41)
//  |  INT "int" (4.6.35)
//  |  |  DECLID "f" (4.6.39)
//  |  INTCON "8" (4.6.43)

// |  VARDECL "=" (7.33.15) {0} 
// |  |  ARRAY "[]" (7.33.7) {0} string array vreg 
// |  |  |  STRING "string" (7.33.1) {0} string 
// |  |  |  
    // DECLID "argv" (7.33.10) {0} array variable lval (7.3.33)

            if(symbol_stack.back() == nullptr)
            {
                symbol_stack.push_back(new symbol_table);
            }

// printf("name: %s\n",root->children[0]->children[0]->
            // lexinfo->c_str());

string var_name_v(root->children[0]->children[0]->lexinfo->c_str());

            string* var_name;


            symbol* sv = new symbol;

    if(root->children[0]->symbol == TOK_ARRAY){
        sv = est_symbol(root->children[0]->children[1]);
        root->children[0]->children[1]->block_nr = sv->block_nr;
        sv->attributes[ATTR_array] = 1;
        sv->attributes[ATTR_vardecl] = 1;
        var_name = 
const_cast<string*>(root->children[0]->children[1]->lexinfo);
    if(root->children[0]->children[0]->symbol == TOK_STRING){
            // printf("this is a string: %s\n",var_name_v.c_str());
            strings.push_back(root);
            sv->attributes[ATTR_string] = 1;
        }
    }else{
        sv = est_symbol(root->children[0]);
        sv->attributes[ATTR_vardecl] = 1;
        root->children[0]->children[0]->block_nr = sv->block_nr;

        if(root->children[1]->symbol == TOK_STRINGCON){
            // printf("this is a string: %s\n",var_name_v.c_str());
            strings.push_back(root);
        }

                //     switch(node->symbol) {
                //     case TOK_INT: 
                //     {s->attributes[ATTR_int] = 1;break;}
                //     case TOK_VOID:
                //     {s->attributes[ATTR_void] = 1;break;}
                //     case TOK_NULL: 
                //     {s->attributes[ATTR_null] = 1;break;}
                //     case TOK_STRING:
                //     {s->attributes[ATTR_string] = 1;break;}
                //     case TOK_TYPEID:
                //     {
                //         s->attributes[ATTR_struct] = 1;
                //         s->lexinfo = string(*(node->lexinfo));

                //         // s->struct_name
                //         break;
                //     }
                if(root->children[0]->symbol == TOK_TYPEID){
                    root->children[0]->children[0]->struct_ = 
                    *(root->children[0]->lexinfo);
                }

                // }
// |  VARDECL "=" (4.21.12) {0} 
// |  |  TYPEID "node" (4.21.5) {0} struct "node" 
// |  |  |  
// DECLID "h" (4.21.10) {0} struct "h" variable lval (4.3.21)
                root->block_nr = sv->block_nr;

                var_name = 
    const_cast<string*>(root->children[0]->children[0]->lexinfo);
            }

            if(sv->block_nr == 0){
// printf("this is a global variable: %s\n",var_name_v.c_str());

                global_queue.push_back(root);
            }

if(sv->block_nr != 0){
    symbol_table* back = symbol_stack.back();
    if(back != nullptr) {
      if(back->find(var_name) != back->end()) {
         if(!back->at(var_name)->attributes[ATTR_function]){
            fprintf(stderr, 
                "variable %s declared in scope more than once\n",
                var_name->c_str());
            break;
         }
      }
    }
}
           

            astree* node = root->children[0];


// |  VARDECL "=" (7.55.15)
// |  |  ARRAY "[]" (7.55.7)
// |  |  |  STRING "string" (7.55.1)
// |  |  |  DECLID "argv" (7.55.10)

            // printf("%s",node->symbol);

            if(node->symbol == TOK_ARRAY){
                // printf("this is an array");
                node->children[1]->attributes = sv->attributes;
                node->children[1]->attributes[ATTR_array] =1;

            }else{
                node->children[0]->attributes = sv->attributes;

            }

            symbol_entry entry(var_name, sv);
            symbol_stack.back()->insert(entry);
            // idents.insert(entry);
            var.insert(entry);
            idents.insert(entry);

            // if(node->children[0]->symbol == TOK_TYPEID){

            // }


            dump_string(outfile, var_name, sv);

            // symbol


// (k) Whenever you see a variable declaration,
 // look it up in the symbol
//     table.  Print a duplicate declaration er
 // ror message if it is in
//     the symbol table at the top of the symbo
// l vector stack.

// (l) If it is not found, enter it into the sy
// mbol table at the top of
//     the symbol stack and set the attributes 
// and other fields as
//     appropriate.


            break;
        }
        case '.': {

// '.' "." (7.36.26) {0} 
// |  '.' "." (7.36.22) {0} variable lval vaddr (7.5.36)
// |  |  IDENT "stack" (7.36.17) {0} struct "stack" 
            // 
            // variable lval param (7.6.36)
// |  |  FIELD "top" (7.36.23) field {} int const (7.6.36)
// |  FIELD "data" (7.36.27) field {} int const (7.5.36)
//string* name = const_cast<string*>(root->children[0]->lexinfo);
            

            break;
        }



        default: break;
    }


    // assert (root != nullptr);
    //postorder tree traverse
    for (size_t child = 0; child < root->children.size(); 
        ++child) {
        if(!symbol_run(root->children[child], outfile))
            return false;
    }

    // for (astree* child: root->children) {
    //     if(!symbol_run(child))
    //         return false;
    // }

    if(!typecheck(root)) return false;




// (m) In the scanner and parser, error 
    // messages were printed using a
//     global coördinate maintained by t
// he scanner.  In this assignment
//     and the next, all error messages 
// must be the coördinates in some
//     appropriate AST node, since the g
// lobal coördinate at this time
//     indicates end of file.
// 
    // ??????????????????????????????????????????????
    //block exit
    // block_count--;
    switch(root->symbol) {
        case TOK_BLOCK:{
            symbol_stack.pop_back();
            blocks.pop_back();
            // fprintf(outfile,"\n");

            break;
        }
        case TOK_FUNCTION:{
            symbol_stack.pop_back();
            blocks.pop_back();
            fprintf(outfile,"\n");

            break;
        }
        case TOK_PROTOTYPE:{
            symbol_stack.pop_back();
            blocks.pop_back();
            fprintf(outfile,"\n");

            break;
        }
        default:break;
    }

    return true;
}
vector<unordered_map<const string*, string>> vars;
vector<unordered_map<const string*, string>> vars_temp;


int num = 1;

bool global_var_flag = false;

string comp(astree* root, FILE* outfile) {
   string sym1, sym2;
   sym1 = block_traversal(root->children[0],outfile);
   sym2 = block_traversal(root->children[1],outfile);
// cout<<"return of comP: "<< sym1 << " " 
   // << *(root->lexinfo) <<" " <<sym2;
   return sym1 + " " + *(root->lexinfo) + " " + sym2;
}

string vs(astree* root) {

    if(root->attributes[ATTR_struct])
    {
         for(int i = vars.size()-1; i >= 0; --i) {
                  if(vars[i].find(root->lexinfo) == vars[i].end())
                     continue;
                  else {
                     return vars[i].at(root->lexinfo);
                    }

            }
            while(vars.size() <= uint(root->block_nr)) {
              unordered_map<const string*, string> map;
              vars.push_back(map);
           }
           // printf("\nlexinfo: %s",(root->lexinfo)->c_str());
           // printf("\nblock_nr: %zd\n",(root->block_nr));
           string new_var = "_";
           if(root->block_nr != 0)
              new_var += to_string(root->block_nr)+"_"+
                *(root->lexinfo);
           else if(root->attributes[ATTR_field]) {
              new_var += *(root->lexinfo);
           }
           else
              new_var += "_"+*(root->lexinfo);

           pair <const string*, string> var (root->lexinfo, new_var);
           vars[root->block_nr].insert(var);

           for(int i = vars_temp.size()-1; i >= 0; --i) {
      if(vars_temp[i].find(root->lexinfo) == vars_temp[i].end())
                     continue;
                  else {
                     return vars_temp[i].at(root->lexinfo);
                    }

            }  
            while(vars_temp.size() <= uint(root->block_nr)) {
              unordered_map<const string*, string> map;
              vars_temp.push_back(map);
           }
           // printf("\nlexinfo: %s",(root->lexinfo)->c_str());
           // printf("\nblock_nr: %zd\n",(root->block_nr));
           new_var = "_";
           if(root->block_nr != 0)
              new_var += 
          to_string(root->block_nr)+"_"+*(root->lexinfo);
           else if(root->attributes[ATTR_field]) {
              new_var += *(root->lexinfo);
           }
           else
              new_var += "_"+*(root->lexinfo);

           pair <const string*, string> var1 (root->lexinfo, new_var);
           vars_temp[root->block_nr].insert(var1);
           
           return new_var;  


    }
    else if(global_var_flag){
            for(int i = vars.size()-1; i >= 0; --i) {
                  if(vars[i].find(root->lexinfo) == vars[i].end())
                     continue;
                  else {
                     return vars[i].at(root->lexinfo);
                    }

            }
            while(vars.size() <= uint(root->block_nr)) {
              unordered_map<const string*, string> map;
              vars.push_back(map);
           }
           // printf("\nlexinfo: %s",(root->lexinfo)->c_str());
           // printf("\nblock_nr: %zd\n",(root->block_nr));
           string new_var = "_";
           if(root->block_nr != 0)
              new_var += to_string(root->block_nr)+"_"+
          *(root->lexinfo);
           else if(root->attributes[ATTR_field]) {
              new_var += *(root->lexinfo);
           }
           else
              new_var += "_"+*(root->lexinfo);

           pair <const string*, string> var (root->lexinfo, new_var);
           vars[root->block_nr].insert(var);
           return new_var;  
    }
    else {
            for(int i = vars_temp.size()-1; i >= 0; --i) {
      if(vars_temp[i].find(root->lexinfo) == vars_temp[i].end())
         continue;
      else {
         return vars_temp[i].at(root->lexinfo);
        }

            }  
            while(vars_temp.size() <= uint(root->block_nr)) {
              unordered_map<const string*, string> map;
              vars_temp.push_back(map);
           }
           // printf("\nlexinfo: %s",(root->lexinfo)->c_str());
           // printf("\nblock_nr: %zd\n",(root->block_nr));
           string new_var = "_";
           if(root->block_nr != 0)
              new_var += to_string(root->block_nr)+"_"+
          *(root->lexinfo);
           else if(root->attributes[ATTR_field]) {
              new_var += *(root->lexinfo);
           }
           else {
                new_var += "_"+*(root->lexinfo);
           }

              
           pair <const string*, string> var (root->lexinfo, new_var);
           vars_temp[root->block_nr].insert(var);

           return new_var;

    }   
   
}



string statement(astree* root, FILE* outfile, bool gvar) {
   string expr, op;

   astree* sym1 = root->children[0];
   string arr, variable;
   switch(sym1->symbol) {
      case TOK_INDEX: {
         expr += 
         block_traversal(root->children[0]->children[0], outfile) + 
         "[" 
         + block_traversal(root->children[0]->children[1], outfile) 
         + "] = ";
         break;
      }
      case TOK_INT: {
         if(root->block_nr == 0)
            expr += vs(root->children[0]->children[0]) + " = ";
         else
            expr += "int " +
               vs(root->children[0]->children[0]) + " = ";
         break;
      }
      case TOK_STRING: {
         if(root->block_nr == 0)
            expr += vs(root->children[0]->children[0]) + " = ";
         else
            expr += "char* " +
               vs(root->children[0]->children[0]) + " = ";
         break;
      }
      case TOK_TYPEID: {
         if(root->block_nr == 0)
            expr += vs(root->children[0]->children[0]) + " = ";
         else
            expr += "struct s_" + (sym1->struct_) + "* " +
               vs(root->children[0]->children[0]) + " = ";
         break;
      }
      case TOK_ARRAY: {
         op = "p"+to_string(num++);
         if(root->block_nr != 0) {
            if(sym1->children[1]->attributes[ATTR_int]) {
               arr+= "int";
            } else if(sym1->children[1]->attributes[ATTR_string]
                  && sym1->children[1]->attributes[ATTR_array]) {
               arr+= "char*";
            } else if(sym1->children[1]->attributes[ATTR_string]) {
               arr+= "char";
            } else if(sym1->children[1]->attributes[ATTR_struct]) {
               arr+= "struct " + *(sym1->children[0]->lexinfo) + "*";
            }
            arr += "* " + op;
         }
         else {
            arr += vs(sym1->children[1]);
         }
         expr += arr + " = ";
         break;
      }
      default: {
         cerr << "Some other symbol" << endl;
         cout << parser::get_tname(sym1->symbol) << endl;
         break;
      }
   }

   if(root->children.size() > 1) {
      astree* sym2 = root->children[1];
      switch(sym2->symbol) {
         case TOK_INDEX: {
expr += block_traversal(root->children[1]->children[0], outfile) +
   "[" + block_traversal(root->children[1]->children[1], outfile)
      +"]";
            break;
         }
         case TOK_IDENT: {
            expr += vs(sym2);
            break;
         }
         case TOK_NULL: {
            expr += " "+*(root->lexinfo)+" 0";
         }
         case TOK_INT:
         case TOK_INTCON:
         case TOK_STRING:
         case TOK_STRINGCON: {
            expr += *(sym2->lexinfo);
            break;
         }
         case TOK_LE:
         case TOK_EQ:
         case TOK_NE:
         case TOK_GE:
         case TOK_LT:
         case TOK_GT:{
            expr += comp(root->children[1],outfile);
            break;
         }
         case '+':
         case '-':
         case '*':
         case '%':
         case '/': {
            string symbol1, symbol2;
            symbol1 = block_traversal(root->children[1]->children[0], 
                outfile);
            symbol2 = block_traversal(root->children[1]->children[1], 
                outfile);
            expr += symbol1+" "+*(sym2->lexinfo)+" "+symbol2;
            break;
         }
         case TOK_NEWARRAY: {
            expr += "xcalloc ("+*(sym2->children[1]->lexinfo) +
               ", sizeof(" + arr + "))";
            break;
         }
         case TOK_CALL: {
            if(gvar)
               expr += block_traversal(root->children[1], outfile);
            else
               block_traversal(root->children[1], outfile);
            break;
         }
         case TOK_NEW: {
            expr += "xcalloc (1, sizeof (struct s_" +
               (sym2->struct_) + "))";
            break;
         }
         case '.': {
            expr += block_traversal(sym2, outfile);
            break;
         }
         default: {
            cout << "Something else" << endl;
            cout << " " << *(root->lexinfo)<<" "<<*(sym2->lexinfo);
            break;
         }
      }
   }
   fprintf(outfile, "        %s;\n", expr.c_str());
   return op;
}

string call(astree* root, FILE* outfile) {

   vector<string> vreg;

   if(!root->attributes[ATTR_function])
      return block_traversal(root, outfile);

   for(uint i = 1; i < root->children.size(); ++i) {
         vreg.push_back(call(root->children[i],outfile));
   }
   string reg;

   if(root->attributes[ATTR_vardecl] != 1) {
      if(root->attributes[ATTR_void]) {
         fprintf(outfile, "        __%s(", 
            (root->children[0]->lexinfo)->c_str());
      } else if(root->attributes[ATTR_int]) {
           attr_bitset attr = root->attributes;
           if(attr[ATTR_int]) {
              reg += "i" + to_string(num);
           } else if(attr[ATTR_string]) {
              reg += "s" + to_string(num);
           } else if(attr[ATTR_struct]) {
              reg += "p" + to_string(num);
           }
           num++;
         fprintf(outfile, "        int %s = __%s (", reg.c_str(), 
            (root->children[0]->lexinfo)->c_str());
      } else if(root->attributes[ATTR_string]) {
           attr_bitset attr = root->attributes;
           if(attr[ATTR_int]) {
              reg += "i" + to_string(num);
           } else if(attr[ATTR_string]) {
              reg += "s" + to_string(num);
           } else if(attr[ATTR_struct]) {
              reg += "p" + to_string(num);
           }
           num++;
         fprintf(outfile, "        char* %s = __%s (", reg.c_str(), 
            (root->children[0]->lexinfo)->c_str());
      } else if(root->attributes[ATTR_struct]) {
           attr_bitset attr = root->attributes;
           if(attr[ATTR_int]) {
              reg += "i" + to_string(num);
           } else if(attr[ATTR_string]) {
              reg += "s" + to_string(num);
           } else if(attr[ATTR_struct]) {
              reg += "p" + to_string(num);
           }
           num++;
         fprintf(outfile, "        struct* s_%s = __%s (", 
            reg.c_str(), 
            (root->children[0]->lexinfo)->c_str());
      }
   } else {
      reg += "__" + *(root->children[0]->lexinfo)+"(";
      if(vreg.size() > 0)
         reg += vreg[0];

      for(uint i = 2; i < root->children.size(); ++i) {
            reg += ", "+ vreg[i-1];
      }
      reg += ")";
      return reg;
   }

   if(vreg.size() > 0)
      fprintf(outfile, "%s", vreg[0].c_str());

   for(uint i = 2; i < root->children.size(); ++i) {
      fprintf(outfile, ", %s", vreg[i-1].c_str());
   }
   fprintf(outfile, ");\n");

   return reg;
}

string block_traversal(astree* root, FILE* outfile) {

   switch(root->symbol) {

      // Statements
      case TOK_TYPEID: {
         return (root->struct_);
      }
      case TOK_VARDECL: {
         string decl = statement(root,outfile, false);
         return decl;
         break;
      }
      case TOK_BLOCK: {
         for(uint i = 0; i < root->children.size(); ++i) {
            block_traversal(root->children[i], outfile);
         }
         break;
      }
      case TOK_WHILE: {
         fprintf(outfile, "while_%zd_%zd_%zd:;\n",
            root->lloc.filenr, root->lloc.linenr, 
            root->lloc.offset);
         string operand;
         if(root->children[0]->attributes[ATTR_lval]) {
            operand = vs(root->children[0]);
         } else {
            operand = "i" + to_string(num++);
            fprintf(outfile, "        int %s = %s;\n", 
                operand.c_str(), 
               block_traversal(root->children[0], outfile).c_str());
            block_traversal(root->children[0], outfile);
         }
         fprintf(outfile, "        ");
         fprintf(outfile, "if(!%s) goto break_%zd_%zd_%zd;\n", 
            operand.c_str(), root->lloc.filenr, 
            root->lloc.linenr, root->lloc.offset);

         // Traverse through while block
         block_traversal(root->children[1], outfile);

         fprintf(outfile, "        ");
         fprintf(outfile, "goto while_%zd_%zd_%zd;\n",
            root->lloc.filenr, root->lloc.linenr, 
            root->lloc.offset);

         fprintf(outfile, "break_%zd_%zd_%zd:;\n",
            root->lloc.filenr, root->lloc.linenr, 
            root->lloc.offset);
         break;
      }
      case TOK_IFELSE: {
         string operand;
         if(root->children[0]->attributes[ATTR_lval]) {
            operand = block_traversal(root->children[0], outfile);;
         } else {
            operand = "i" + to_string(num++);
            fprintf(outfile, "        int %s = %s;\n", 
                operand.c_str(), 
               block_traversal(root->children[0], outfile).c_str());
         }
         fprintf(outfile, "        if(!%s) goto else_%zd_%zd_%zd;\n", 
            operand.c_str(), root->lloc.filenr,
            root->lloc.linenr, root->lloc.offset);
         fprintf(outfile, "        ");
         block_traversal(root->children[1], outfile);
         fprintf(outfile, "goto fi_%zd_%zd_%zd;\n",
            root->lloc.filenr, root->lloc.linenr, root->lloc.offset);
         fprintf(outfile, "else_%zd_%zd_%zd:;\n",
            root->lloc.filenr, root->lloc.linenr, root->lloc.offset);
         fprintf(outfile, "        ");
         block_traversal(root->children[2], outfile);
         fprintf(outfile, "fi_%zd_%zd_%zd:;\n",
            root->lloc.filenr, root->lloc.linenr, root->lloc.offset);
         break;
      }
      case TOK_IF: {
// |  |  BLOCK "{" (7.5.23) {0} 
// |  |  |  BLOCK "{" (7.6.4) {0} 
// |  |  |  |  IF "if" (7.6.5) {0} 
// |  |  |  |  |  '!' "!" (7.6.9) {0} 
// |  |  |  |  |  |  NE "!=" (7.6.15) {0} int vreg 
// |  |  |  |  |  |  |  IDENT "str" (7.6.11) {12}
 // string variable lval param (7.7.-6)
// |  |  |  |  |  |  |  NULL "null" (7.6.18) {0} null const 
// |  |  |  |  |  CALL "(" (7.6.39) {0} void function vreg 
// |  |  |  |  |  |  IDENT "__assert_fail" (7.6.25)
 // {0} void function 
// |  |  |  |  |  |  STRINGCON ""str != null"" (7.6.40)
 // {0} string const 
// |  |  |  |  |  |  STRINGCON ""oc-programs/23-atoi.oc""
 // (7.6.55) {0} string const 
// |  |  |  |  |  |  INTCON "6" (7.6.81) {0} int const 
         string operand;
         if(root->children[0]->attributes[ATTR_lval]) {
            operand = block_traversal(root->children[0],outfile);;
         } else {
            operand = "i" + to_string(num++);
            fprintf(outfile, "        int %s = %s;\n", 
                operand.c_str(), 
               block_traversal(root->children[0], outfile).c_str());
         }
         fprintf(outfile, "        if(!%s) goto fi_%zd_%zd_%zd;\n", 
            operand.c_str(), root->lloc.filenr,
            root->lloc.linenr, root->lloc.offset);
         block_traversal(root->children[1], outfile);
         fprintf(outfile, "fi_%zd_%zd_%zd:;\n",
            root->lloc.filenr, root->lloc.linenr, root->lloc.offset);
         break;
      }
      case TOK_RETURN: {
         if (root->children[0]->attributes[ATTR_const]) {
            fprintf(outfile, "        return %s;\n", 
               (root->children[0]->lexinfo)->c_str());
         } else if(root->children[0]->attributes[ATTR_variable]) {
            fprintf(outfile, "        return %s;\n", 
               vs(root->children[0]).c_str());
         } else {
            fprintf(outfile, "        return %s;\n", 
               block_traversal(root->children[0], outfile).c_str());
         }
         break;
      }
      case TOK_RETURNVOID: {
         fprintf(outfile, "        return;\n");
         break;
      }

      case TOK_CALL: {
         return call(root,outfile);
         break;
      }

      // Expressions
      case TOK_NEG:
      case TOK_POS:{
         return *(root->lexinfo)+block_traversal(root->children[0], 
            outfile);
      }
      case TOK_LE:
      case TOK_EQ:
      case TOK_NE:
      case TOK_GE:
      case TOK_GT:
      case TOK_LT: {
        return comp(root,outfile);
      }
      case '=': {
         astree* root1 = root->children[0];
         astree* root2 = root->children[1];
         fprintf(outfile, "        %s = %s;\n", 
            block_traversal(root1, outfile).c_str(), 
            block_traversal(root2, outfile).c_str());
         break;
      }
      case '.': {
         string vreg, type;
         if(root->attributes[ATTR_int]) {
            type = "int";
         } else if(root->attributes[ATTR_string]
               && root->attributes[ATTR_array]) {
            type = "char *";
         } else if(root->attributes[ATTR_string]) {
            type = "char";
         } else if(root->attributes[ATTR_struct]) {
            type = "struct s_" + (root->struct_) + " *";
         }

         vreg = "a"+to_string(num++);
         fprintf(outfile, "        %s*%s = &%s->f_%s_%s;\n", 
            type.c_str(), vreg.c_str(),
            
         block_traversal(root->children[0], outfile).c_str(),
            (root->children[0]->struct_).c_str(),
            (root->children[1]->lexinfo)->c_str());
         
         return "(*"+vreg+")";
      }
      case '+':
      case '-':
      case '*':
      case '%':
      case '/': {
            string sym1 = vs(root->children[0]);
            string sym2 = vs(root->children[1]);

            sym1 = block_traversal(root->children[0], outfile);
            sym2 = block_traversal(root->children[1], outfile);
            string vreg = "";
            attr_bitset attr = root->attributes;
            if(attr[ATTR_int]) {
              vreg += "i" + to_string(num);
            } else if(attr[ATTR_string]) {
              vreg += "s" + to_string(num);
            } else if(attr[ATTR_struct]) {
              vreg += "p" + to_string(num);
            }
            num++;
         fprintf(outfile, "        int %s = ", vreg.c_str());
         fprintf(outfile, "%s %s %s;\n", sym1.c_str(), 
            (root->lexinfo)->c_str(), sym2.c_str());

         return vreg;
      }
      case TOK_CHARCON:
      case TOK_INTCON:
      case TOK_STRINGCON: {
         return *(root->lexinfo);
      }
      case TOK_NULL:{
         return "0";
      }
      case TOK_IDENT: {
         return vs(root);
      }
      case TOK_NEWARRAY: {
         astree* sym1 = root->children[0];
         string arr;
   
         if(sym1->attributes[ATTR_int]) {
            arr+= "int";
         } else if(sym1->attributes[ATTR_string] 
               && sym1->attributes[ATTR_array]) {
            arr+= "char*";
         } else if(sym1->attributes[ATTR_string]) {
            arr+= "char";
         } else if(sym1->attributes[ATTR_struct]) {
            arr+= "struct " + *(sym1->lexinfo) + "*";
         }

         return "xcalloc ("+block_traversal(root->children[1], 
            outfile) +
            ", sizeof(" + arr + "))";
      }
      case '!': {
        return block_traversal(root->children[0], outfile);
        break;
      }
      case TOK_INDEX: {
         string vreg, type;
         if(root->attributes[ATTR_int]) {
            type = "int *";
         } else if(root->attributes[ATTR_string] 
               && root->attributes[ATTR_array]) {
            type = "char **";
         } else if(root->attributes[ATTR_string]) {
            type = "char *";
         } else if(root->attributes[ATTR_struct]) {
            type = "struct s_" + (root->children[0]->struct_) + 
            " **";
         }

         vreg = "a"+to_string(num++);
         fprintf(outfile, "        %s%s = &%s[%s];\n", type.c_str(), 
            vreg.c_str(), block_traversal(root->children[0], 
                outfile).c_str(),
            block_traversal(root->children[1],outfile).c_str());

         return "(*"+vreg+")";;
      }
      default: break;
   }
   
   return "";
}

string format_var(astree* node) {
   astree* var;
   string val;
    // bool x = false;
   if(node->symbol == TOK_ARRAY){
     var = node->children[1];
            // x = true;
    }else
      var = node->children[0];

   attr_bitset attr = var->attributes;

   if(attr[ATTR_void]) {
      val += "void ";
   }
   if (attr[ATTR_int] == 1) {
      val += "int";
   } if (attr[ATTR_struct] == 1) {
       val += "struct s_"+ (var->struct_) +"* ";
   } if (attr[ATTR_string] == 1) {
      val += "char*";
   }

   if(attr[ATTR_array]) {
     val += "* ";

   } else {
      val += " ";
   }

   if(attr[ATTR_field]) {
      val += "f_"+ (var->struct_)+vs(var);
   }

   if(attr[ATTR_param]) {
      val += vs(var);
   }
   // if(x)
   //  val += "* ";

   return val;
}

// STRUCT "struct" (4.1.2) {0} struct "struct" 
// |  |  TYPEID "node" (4.1.9) {0} struct "node" 
// |  |  '{' "{" (4.1.14) {0} 
// |  |  |  INT "int" (4.1.16) {0} int 
// |  |  |  |  FIELD "foo" (4.1.20) 
// field {node} int variable lval const vaddr (4.4.1)
// |  |  |  TYPEID "node" (4.1.25) {0} struct "node" 
// |  |  |  |  FIELD "link" (4.1.30) 
// field {node} int variable lval const vaddr (4.4.1)

void print_structs(astree* root, FILE* outfile){
    if(root->children[0]->lexinfo == NULL)
      return;

   fprintf(outfile, "struct s_%s {\n", 
    root->children[0]->lexinfo->c_str());

   if(root->children.size() > 1) {
      astree* list = root->children[1];
      string var;
      for(uint i = 0; i < list->children.size(); ++i) {
         list->children[i]->struct_ = 
         *(root->children[0]->lexinfo);
      }
      for(uint i = 0; i < list->children.size(); ++i) {
        // printf("%s\n",list->children[i]->struct_.c_str());
         var = format_var(list->children[i]);
         fprintf(outfile, "        %s;\n", var.c_str());
      }
   }
   fprintf(outfile, "};\n");

}

// |  VARDECL "=" (7.33.15) {0} 
// |  |  ARRAY "[]" (7.33.7) {0} string array vreg 
// |  |  |  STRING "string" (7.33.1) {0} string 
// |  |  |  DECLID "argv" (7.33.10) {0} 
// array variable lval (7.3.33)
void print_strings(astree* root, FILE* outfile){
    // fprintf(outfile,"string: %s\n", 
    // root->children[0]->children[0]->lexinfo->c_str());

    if(root->children[0]->attributes[ATTR_array])
    {
        fprintf(outfile, "char **__%s;\n", 
        (root->children[0]->children[1]->lexinfo)->c_str());
    }
    else {
        fprintf(outfile, "char* %s = %s;\n", 
      (root->children[0]->children[0]->lexinfo)->c_str(),
      (root->children[1]->lexinfo)->c_str());
    }


}


void print_global_vars(astree* root, FILE* outfile){
// fprintf(outfile,"global variable: %s\n", 
    // root->children[0]->children[0]->lexinfo->c_str());
// fprintf(outfile,"var type: %s\n", 
    // root->children[0]->lexinfo->c_str());

   astree* var;
   if(root->children[0]->symbol == TOK_ARRAY) {
      var = root->children[0]->children[1];
   } else {
      var = root->children[0]->children[0];
   }

   string list = format_var(root->children[0]);
   string name = vs(var);
   fprintf(outfile, "%s%s;\n", list.c_str(), name.c_str());
}


void print_functions(astree* root, FILE* outfile){
    //function prints
    astree* v;
    // bool x;
   if(root->children[0]->symbol == TOK_ARRAY) {
      v = root->children[0]->children[1];
      // x = true;
   } else {
      v = root->children[0]->children[0];
      // x = false;
   }
   // astree* v1 = root->children[0];
   string args = format_var(root);
        // string args;
        // for(uint i = 0; i < v1->children.size(); ++i) {
        //     args += "        ";
        //     astree* var;
        //     if(v1->symbol == TOK_ARRAY)
        //       var = v1->children[1];
        //     else
        //       var = v1->children[0];

        //     attr_bitset attr = var->attributes;

        //     if(attr[ATTR_void]) {
        //       args += "void ";
        //     }
        //     if (attr[ATTR_int] == 1) {
        //       args += "int ";
        //     } if (attr[ATTR_struct] == 1) {
        //       if(x)
        //          args += "struct s_" + vs(var) + "* ";
        //       else
        //          args += "struct s_"+ (v1->struct_) +"* ";
        //     } if (attr[ATTR_string] == 1) {
        //       args += "char*";
        //     }

        //     if(attr[ATTR_array]) {
        //       args += "* ";
        //     } else {
        //       args += " ";
        //     }

        //     if(attr[ATTR_field]) {
        //       args += "f_"+ (var->struct_)+vs(var);
        //     }

        //     if(attr[ATTR_param]) {
        //       args += vs(var);
        //     }
        //   if(i < v1->children.size()-1) 
        //      args += ",\n";
        // }
   fprintf(outfile, "%s__%s (\n", args.c_str(), 
    v->lexinfo->c_str());

   // string arg_pack = format_args(root->children[1]);
    astree* v1 = root->children[1];
    string arg_parameter;
    for(uint i = 0; i < v1->children.size(); ++i) {
      arg_parameter += "        "+format_var(v1->children[i]);
      // vars.pop_back();
      if(i < v1->children.size()-1) 
         arg_parameter += ",\n";
   }
   fprintf(outfile, "%s)\n{\n", arg_parameter.c_str());

   for(uint i = 0; i < root->children[2]->children.size(); ++i) {
      block_traversal(root->children[2]->children[i],outfile);
   }

   fprintf(outfile, "}\n");



}


void print_global_logic(astree* root, FILE* outfile){
    //global prints
    // global_var_flag = true;
    for(uint i = 0; i < root->children.size(); i++){
        if(root->children[i]->symbol != TOK_FUNCTION
            && root->children[i]->symbol != TOK_PROTOTYPE
            && root->children[i]->symbol != TOK_VARDECL
            && root->children[i]->symbol != TOK_STRUCT){
            // print_functions(root, outfile);
            block_traversal(root->children[i],outfile);
        }
    }

    fprintf(outfile, "}\n");

}

//AAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHH : - )
void oil_dump(astree* root, FILE* outfile){
   fprintf(outfile, 
    "#define __OCLIB_C__\n#include \"oclib.oh\"\n\n");

    // 1: print all structure definitions
    //     one option is to go through the AST and 
   // find the structures
    //     again, BUT
    //         it would be easiest to iterate over 
   // the structure table
    // global_var_flag = true;
    for(uint i = 0; i < root->children.size(); i++){
        if(root->children[i]->symbol == TOK_STRUCT){
            print_structs(root->children[i], outfile);
        }
    }


    // 2: print all string constants
    //     iterate over the 'global queue' 
    // (a new data structure for 
    //     this asg5) and print them.
    for(uint i = 0; i < strings.size(); i++){
       print_strings(strings[i], outfile);
    }

    // 3: print all global variabls
    //     iterate last remaining symbol table in symbol state
    //     or var-table ?
    global_var_flag = true;
    // for(uint i = 0; i < global_queue.size(); i++){
    //     print_global_vars(global_queue[i], outfile);
    // }
    for(uint i = 0; i < root->children.size(); i++){
if(root->children[i]->symbol == TOK_VARDECL){
    if(!root->children[i]->children[0]->attributes[ATTR_string]){
        if(root->children[i]->children[0]->symbol == TOK_ARRAY)
        {
            if(root->children[i]->children[1]->symbol != TOK_STRING){
                print_global_vars(root->children[i], outfile);

            }

        }else{
            print_global_vars(root->children[i], outfile);

        }

    }
}
    }
// |  FUNCTION "" (7.8.1) {0} 
// |  |  INT "int" (7.8.1) {0} int 
// |  |  |  DECLID "fac" (7.8.5) {0} function 
// |  |  PARAMLIST "(" (7.8.9) {0} 
// |  |  |  INT "int" (7.8.10) {12} int 
// |  |  |  |  DECLID "n" (7.8.14) {0} int 
    // variable lval param (7.4.8)
// |  |  BLOCK "{" (7.8.17) {0} 
// |  |  |  VARDECL "=" (7.9.10) {13} 
// |  |  |  |  INT "int" (7.9.4) {13} int 
// |  |  |  |  |  DECLID "f" (7.9.8) {0} int variable lval (7.5.9)
// |  |  |  |  INTCON "1" (7.9.12) {0} int const 
// |  |  |  WHILE "while" (7.10.4) {0} 
// |  |  |  |  GT ">" (7.10.13) {0} 
// |  |  |  |  |  IDENT "n" (7.10.11) {0} 
    // int variable lval param (7.5.10)
// |  |  |  |  |  INTCON "1" (7.10.15) {0} int const 
// |  |  |  |  BLOCK "{" (7.10.18) {0} 
// |  |  |  |  |  '=' "f" (7.11.9) {0} int vreg 
// |  |  |  |  |  |  IDENT "f" (7.11.7) {0} 
    // int variable lval (7.6.11)
// |  |  |  |  |  |  '*' "*" (7.11.13) {0} int vreg 
// |  |  |  |  |  |  |  IDENT "f" (7.11.11) {0} 
    // int variable lval (7.7.11)
// |  |  |  |  |  |  |  IDENT "n" (7.11.15) {0} 
    // int variable lval param (7.7.11)
// |  |  |  |  |  '=' "n" (7.12.9) {0} int vreg 
// |  |  |  |  |  |  IDENT "n" (7.12.7) {0} 
    // int variable lval param (7.6.12)
// |  |  |  |  |  |  '-' "-" (7.12.13) {0} int vreg 
// |  |  |  |  |  |  |  IDENT "n" (7.12.11) {0} 
    // int variable lval param (7.7.12)
// |  |  |  |  |  |  |  INTCON "1" (7.12.15) {0} int const 
// |  |  |  RETURN "return" (7.14.4) {0} 
// |  |  |  |  IDENT "f" (7.14.11) {0} int variable lval (7.4.14)

    // 4: print all function definitions
    //     real code !
    //     iterate over the children of the root in AST
    //     traversal
    global_var_flag = false;
    for(uint i = 0; i < root->children.size(); i++){
        if(root->children[i]->symbol == TOK_FUNCTION){
// fprintf(outfile,"%s",
            // root->children[i]->children[0]->lexinfo->c_str());
            print_functions(root->children[i], outfile);
        }
    }

    // 5: print __ocmain then all toplevel code
    //     iterate over children of root
    //     traversal

    fprintf(outfile, "void __ocmain (void)\n{\n");
    // global_var_flag = true;
    for(uint i = 0; i < global_queue.size(); i++){
       statement(global_queue[i], outfile, true);
    }

    // fprintf(outfile,"while/if/stuff garb-O...\n");

    // string wow;

    print_global_logic(root, outfile);
        

    // data structures:

    //     Structure table: empty

    //     String queue: empty

    //     symboltable stack: only 1 item-> global scope
    //         find things with func attribute
    //         find things with no func attribute

}

