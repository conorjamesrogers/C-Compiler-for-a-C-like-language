// $Id: main.cpp,v 1.18 2017-10-19 16:02:14-07 - - $
//CONOR ROGERS
//COJAROGE
//1558818

#include <string>
#include <vector>
using namespace std;

#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "astree.h"
#include "auxlib.h"
#include "lyutils.h"
#include "string_set.h"
#include "symbol.h"

const string cpp_name = "/usr/bin/cpp -nostdinc";
string cpp_command;

// Open a pipe from the C preprocessor.
// Exit failure if can't.
// Assigns opened pipe to FILE* yyin.
void cpp_popen (const char* filename, const char* comm_pass) {
   cpp_command = cpp_name + " " + comm_pass + " " + filename;
   yyin = popen (cpp_command.c_str(), "r");
   if (yyin == nullptr) {
      syserrprintf (cpp_command.c_str());
      exit (exec::exit_status);
   }else {
      if (yy_flex_debug) {
         fprintf (stderr, "-- popen (%s), fileno(yyin) = %d\n",
                  cpp_command.c_str(), fileno (yyin));
      }
      lexer::newfilename (cpp_command);

   }
}

void cpp_pclose() {
   int pclose_rc = pclose (yyin);
   eprint_status (cpp_command.c_str(), pclose_rc);
   if (pclose_rc != 0) exec::exit_status = EXIT_FAILURE;
}


const char* scan_opts (int argc, char** argv) {
   opterr = 0;
   yy_flex_debug = 0;
   yydebug = 0;
   lexer::interactive = isatty (fileno (stdin))
                    and isatty (fileno (stdout));
   int opt;
   char* filename;
   string comm_pass;
   
   while ((opt = getopt (argc, argv, ":ly@:D:")) != -1){
      switch(opt)
      {
        case 'l':
          //for scanner
          yy_flex_debug = 1;
          // printf("l is set\n");
          // printf("file path: %s\n",optarg);
        break;
        case 'y':
          //yacc, for scanner
          yydebug = 1;
          // printf("y is set\n");
          // printf("file path: %s\n",optarg);
        break;
        case 'D':
          //argument passes to cpp command call
          // printf("D is set\n");
          comm_pass = "-D" + string(optarg);
          // printf("comm_pass: %s\n",optarg);
        break;
        case '@':
           // printf("@ is set \n");
           // printf("flag: %s\n",optarg);
        break;
        case ':':
          fprintf(stderr,"-%c without filename\n", optopt);
          break;
        case '?':
          fprintf(stderr,"unknown arg %c\n", optopt);

        break;
        default:
        break;

      }
      //set filename (always the last)

   }
    filename = argv[argc-1];


   if(string(filename).find(".oc") == string::npos)
   {
    string msg = "ERROR, file given not .oc: %s.\nCorrect run:\n\t";
      msg += "oc [-ly] [-@ flag...] [-D string] <program>.oc\n";
      fprintf(stderr,msg.c_str(),filename);
      exit (exec::exit_status);
   }
   // const char* filename = optind == argc ? "-" : argv[optind];
   cpp_popen (filename, comm_pass.c_str());
   return filename;
}

int main (int argc, char** argv) {
   exec::execname = basename (argv[0]);
   if (yydebug or yy_flex_debug) {
      // fprintf (stderr, "Command:");
      // for (char** arg = &argv[0]; arg < &argv[argc]; ++arg) {
      //       fprintf (stderr, " %s", *arg);
      // }
      // fprintf (stderr, "\n");
   }
   const char* filename = scan_opts (argc, argv);
   int parse_rc = yyparse();
   cpp_pclose();
   yylex_destroy();
   if (yydebug or yy_flex_debug) {
      fprintf (stderr, "Dumping parser::root:\n");
      if (parser::root != nullptr) parser::root->dump_tree (stderr);
      fprintf (stderr, "Dumping string_set:\n");
      string_set::dump (stderr);
   }
   if (parse_rc) {
      errprintf ("parse failed (%d)\n", parse_rc);
   }else {
      // parser::root->dump_tree(stdout);
      string str_file(filename);

      string::size_type pos = str_file.find('.');
      if (pos != std::string::npos)
      {
         str_file = str_file.substr(0, pos);
      }
      else
      {
         // do nothing
      }

      if(!parser::root)
      {
         fprintf(stderr,"astree null, are values being adopted?\n");
      }

      // printf("%s\n",(str_file+".str").c_str());
      // printf("%s\n",(str_file+".tok").c_str());

      // str_file = str_file + ".str";
      string_set::dump (fopen((str_file + ".str").c_str(), "w"));
      astree::print (fopen((str_file + ".tok").c_str(), "w"), 
        parser::root);

      

      //symbol setup
      setup_symboltable();
      if(!symbol_run(parser::root, 
        fopen((str_file + ".sym").c_str(), "w")))
      {
        //fail!!!!
        exit (exec::exit_status);
      }
      
      astree::dump(fopen((str_file + ".ast").c_str(), "w"), 
        parser::root);

      // astree::print (stdout, parser::root);
      // parser::root->dump_tree(stdout);
      // string_set::dump(stdout);

      // oil_dump(parser::root, stdout);

      oil_dump(parser::root, fopen((str_file + ".oil").c_str(), "w"));

            
      delete parser::root;
   }
   return exec::exit_status;
}

