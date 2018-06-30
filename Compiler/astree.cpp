// $Id: astree.cpp,v 1.15 2017-10-05 16:39:39-07 - - $

#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>

#include "astree.h"
#include "string_set.h"
#include "lyutils.h"
#include "symbol.h"

astree::astree (int symbol_, const location& lloc_, const char* info) {
   symbol = symbol_;
   lloc = lloc_;
   lexinfo = string_set::intern (info);
   // vector defaults to empty -- no children
}

astree::~astree() {
   while (not children.empty()) {
      astree* child = children.back();
      children.pop_back();
      delete child;
   }
   if (yydebug) {
     fprintf (stderr, "Deleting astree (");
      astree::dump (stderr, this,0);
      // astree::print (stderr, this);

      fprintf (stderr, ")\n");
   }
}

astree* astree::adopt (astree* child1, astree* child2) {
   if (child1 != nullptr) children.push_back (child1);
   if (child2 != nullptr) children.push_back (child2);
   return this;
}

astree* astree::adopt_sym (astree* child, int symbol_) {
   symbol = symbol_;
   return adopt (child);
}

astree* astree::substitute (astree* tree, int new_symbol) {
   tree->symbol = new_symbol;
   return tree;
}


void astree::dump_node (FILE* outfile) {
   fprintf (outfile, "%p->{%s %zd.%zd.%zd \"%s\":",
            this, parser::get_tname (symbol),
            lloc.filenr, lloc.linenr, lloc.offset,
            lexinfo->c_str());
   for (size_t child = 0; child < children.size(); ++child) {
      fprintf (outfile, " %p", children.at(child));
   }
}

void astree::dump_tree (FILE* outfile, int depth) {
   fprintf (outfile, "%*s", depth * 3, "");
   dump_node (outfile);
   fprintf (outfile, "\n");
   for (astree* child: children) child->dump_tree (outfile, depth + 1);
   fflush (nullptr);
}

void astree::dump (FILE* outfile, astree* tree, int depth) {
   fprintf (outfile, "%.*s", depth * 3, 
"|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  ");
   const char *tname = parser::get_tname (tree->symbol);
  
   bool f = false;

   attr_bitset a = tree->attributes;
    string out_s;

   // retrieve_symbol(tree);

    // enum { 
    //    ATTR_void, ATTR_int, ATTR_null, ATTR_string, ATTR_struct,
    // ATTR_array, ATTR_function, 
    // ATTR_variable, ATTR_field, ATTR_typeid,
    // ATTR_param, ATTR_lval,
    //ATTR_const, ATTR_vreg, ATTR_vaddr, ATTR_bitset_size,
    // };

    if (a[ATTR_field] == 0) 
        out_s += "{"+to_string(tree->block_nr)+"} ";

    if (a[ATTR_field] == 1) 
        {
         out_s += "field {" + tree->struct_ + "} ";
         f = true;
      }

    if (a[ATTR_void] == 1) 
        out_s += "void ";

     if (a[ATTR_int] == 1) 
        out_s += "int ";

    if (a[ATTR_null] == 1) 
        out_s += "null ";

    if (a[ATTR_string] == 1) 
        out_s += "string ";

    if (a[ATTR_struct] == 1) 
        out_s += "struct \"" + string(tree->lexinfo->c_str()) + "\" ";

    if (a[ATTR_array] == 1)
        out_s += "array ";

    if (a[ATTR_function] == 1) 
         out_s += "function ";    

    if (a[ATTR_variable] == 1) 
    {
         out_s += "variable ";
         f = true;

    }

    if (a[ATTR_lval] == 1) 
        out_s += "lval ";

    if (a[ATTR_param] == 1) 
        out_s += "param ";

    if (a[ATTR_const] == 1) 
        out_s += "const ";

    if (a[ATTR_vreg] == 1) 
        out_s += "vreg ";

    if (a[ATTR_vaddr] == 1) 
    {
        out_s += "vaddr ";  

    }

      if (f)
      {
         char file_tmp[0x1000];
         sprintf(file_tmp,"(%zd.%d.%zd)", tree->lloc.filenr, 
            depth , (tree->lloc.linenr - tree->block_nr));
         string x(file_tmp);
         out_s += x;
      }

   if(strstr (tname, "TOK_") == tname) tname += 4;
   fprintf (outfile, "%s \"%s\" (%zd.%zd.%zd) %s\n",
            tname, tree->lexinfo->c_str(),
            tree->lloc.filenr, tree->lloc.linenr, tree->lloc.offset,  
            out_s.c_str());

   for (astree* child: tree->children) {
      astree::dump (outfile, child, depth + 1);
   }
}


void astree::print (FILE* outfile, astree* tree, int depth, 
   bool first_flag) {
   // printf("curr: %zd, prev: %zd\n",tree->lloc.filenr,prev_filenr);
   if(first_flag){

      // string str_file("/usr/bin/cpp oc-programs/01-hello.oc");

      // string::size_type pos = str_file.find(' ');
      // if (pos != std::string::npos)
      // {
      //    str_file = str_file.substr(pos+1, str_file.length());
      // }
      // else
      // {
      //    // do nothing
      //    printf("didn;t work\n\n");
   
      // printf("FILENAME FROM CPP GOES HEARE!!!\n");
      // pch = strtok (lexer::filename (tree->lloc.filenr)," ");
      // fprintf(outfile,"# %zd %s\n", 
      //    tree->lloc.linenr, (lexer::filename 
      // (tree->lloc.filenr))->c_str());
      fprintf(outfile,"%s",(lexer::get_filenames_print())->c_str());
      //get lexer::includes() cpp filenames

      // int c;
      // string s;
      // ifstream file;
      // // file = fopen(".filelist", "r");
      // file.open("filelist");
      // if (file) {
      //     // while ((c = getc(file)) != EOF)
      //     //     fprintf(outfile, "%d",c);
      //     // fclose(file);
      //    while (getline(file, s))
      //    {
      //        // ...
      //       fprintf(outfile,"%s \n",s.c_str());
      //    }
      // }
      // else{
      //    fprintf(stdout,"file doesn't exist\n");
      // }



      // if( remove( "filelist" ) != 0 )
      //    fprintf(stderr, "Error deleting file\n");
      // else{
      //    //do nothing
      //    fprintf(stdout,"file erased\n");
      // }
      // filelist_printing(outfile);
         
   }
   else{
      fprintf(outfile,"%zd%5zd.%03zd%6d%3s%-13s%2s%s)\n",
         tree->lloc.filenr,tree->lloc.linenr, 
         tree->lloc.offset, tree->symbol, 
         "",parser::get_tname(tree->symbol),"(", 
         tree->lexinfo->c_str());
   }
   // fprintf (outfile, "%*s", depth * 3, "");
   // fprintf (outfile, "%s \"%s\" (%zd.%zd.%zd)\n",
   //          parser::get_tname (tree->symbol), 
   // tree->lexinfo->c_str(),
   //          tree->lloc.filenr, tree->lloc.linenr, 
   // tree->lloc.offset);
   //don;t mess with filenames vector
   //printf padding spaces
      


   for (astree* child: tree->children) {
      astree::print (outfile, child, depth, false);
   }
}

void destroy (astree* tree1, astree* tree2) {
   if (tree1 != nullptr) delete tree1;
   if (tree2 != nullptr) delete tree2;
}

void errllocprintf (const location& lloc, const char* format,
                    const char* arg) {
   static char buffer[0x1000];
   assert (sizeof buffer > strlen (format) + strlen (arg));
   snprintf (buffer, sizeof buffer, format, arg);
   errprintf ("%s:%zd.%zd: %s", 
              (lexer::filename (lloc.filenr))->c_str(), 
              lloc.linenr, lloc.offset,
              buffer);
}
