# C-Compiler-for-a-C-like-language

The following is an automated report about my lexical parsing and grammar for this C compiler.

GNU Bison XML Automaton Report
==============================

input grammar: parser.y

### Table of Contents

*   [Reductions](#reductions)
    *   [Nonterminals useless in grammar](#nonterminals_useless_in_grammar)
    *   [Terminals unused in grammar](#terminals_unused_in_grammar)
    *   [Rules useless in grammar](#rules_useless_in_grammar)
*   [Conflicts](#conflicts)
*   [Grammar](#grammar)
    *   [Itemset](#grammar)
    *   [Terminal symbols](#terminals)
    *   [Nonterminal symbols](#nonterminals)
*   [Automaton](#automaton)

Reductions
----------

### Nonterminals useless in grammar

### Terminals unused in grammar

TOK\_CHAR TOK\_BLOCK TOK\_CALL TOK\_IFELSE TOK\_INITDECL TOK\_POS TOK\_NEG TOK\_NEWARRAY TOK\_FIELD TOK\_ORD TOK\_CHR TOK\_ROOT TOK\_NEWSTRING TOK\_RETURNVOID TOK\_VARDECL TOK\_FUNCTION TOK\_PARAMLIST TOK\_PROTOTYPE TOK\_INDEX TOK\_DECLID '%'

### Rules useless in grammar

Conflicts
---------

[State 66](#state_66) conflicts: 13 shift/reduce [State 104](#state_104) conflicts: 13 shift/reduce [State 123](#state_123) conflicts: 1 shift/reduce

Grammar
-------

0 $accept → start **$end** 1 start → program 2 program → program structdef 3 | program function 4 | program statement 5 | program **error** **'}'** 6 | program **error** **';'** 7 | %empty 8 structdef\_ellipse → **'{'** fielddecl **';'** 9 | structdef\_ellipse fielddecl **';'** 10 structdef → **TOK\_STRUCT** **TOK\_IDENT** structdef\_ellipse **'}'** 11 | **TOK\_STRUCT** **TOK\_IDENT** **'{'** **'}'** 12 fielddecl → basetype **TOK\_IDENT** 13 | basetype **TOK\_ARRAY** **TOK\_IDENT** 14 basetype → **TOK\_VOID** 15 | **TOK\_INT** 16 | **TOK\_STRING** 17 | **TOK\_TYPEID** 18 | **TOK\_IDENT** 19 function\_ellipse → **'('** identdecl 20 | function\_ellipse **','** identdecl 21 function → identdecl function\_ellipse **')'** block 22 | identdecl function\_ellipse **')'** **';'** 23 | identdecl **'('** **')'** block 24 | identdecl **'('** **')'** **';'** 25 identdecl → basetype **TOK\_IDENT** 26 | basetype **TOK\_ARRAY** **TOK\_IDENT** 27 block\_ellipse → **'{'** statement 28 | block\_ellipse statement 29 block → block\_ellipse **'}'** 30 | **'{'** **'}'** 31 statement → block 32 | vardecl 33 | while 34 | ifelse 35 | return 36 | expr **';'** 37 | **';'** 38 vardecl → identdecl **'='** expr **';'** 39 while → **TOK\_WHILE** **'('** expr **')'** statement 40 ifelse → **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement 41 | **TOK\_IF** **'('** expr **')'** statement 42 return → **TOK\_RETURN** expr **';'** 43 | **TOK\_RETURN** **';'** 44 binop → **TOK\_EQ** 45 | **TOK\_NE** 46 | **TOK\_LT** 47 | **TOK\_LE** 48 | **TOK\_GT** 49 | **TOK\_GE** 50 | **'='** 51 | **'+'** 52 | **'-'** 53 | **'\*'** 54 | **'/'** 55 unop → **'+'** 56 | **'-'** 57 | **'!'** 58 | **TOK\_NEW** 59 expr → expr binop expr 60 | unop expr 61 | allocator 62 | call 63 | **'('** expr **')'** 64 | variable 65 | constant 66 allocator → **TOK\_NEW** **TOK\_IDENT** **'('** **')'** 67 | **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** 68 | **TOK\_NEW** basetype **'\['** expr **'\]'** 69 call\_elipse → **TOK\_IDENT** **'('** expr 70 | call\_elipse **','** expr 71 call → call\_elipse **')'** 72 | **TOK\_IDENT** **'('** **')'** 73 variable → **TOK\_IDENT** 74 | expr **'\['** expr **'\]'** 75 | expr **'.'** **TOK\_IDENT** 76 constant → **TOK\_INTCON** 77 | **TOK\_CHARCON** 78 | **TOK\_STRINGCON** 79 | **TOK\_NULL**

### Terminals, with rules where they appear

**$end** (0) [0](#rule_0) **'!'** (33) [57](#rule_57) **'%'** (37) **'('** (40) [19](#rule_19) [23](#rule_23) [24](#rule_24) [39](#rule_39) [40](#rule_40) [41](#rule_41) [63](#rule_63) [66](#rule_66) [67](#rule_67) [69](#rule_69) [72](#rule_72) **')'** (41) [21](#rule_21) [22](#rule_22) [23](#rule_23) [24](#rule_24) [39](#rule_39) [40](#rule_40) [41](#rule_41) [63](#rule_63) [66](#rule_66) [67](#rule_67) [71](#rule_71) [72](#rule_72) **'\*'** (42) [53](#rule_53) **'+'** (43) [51](#rule_51) [55](#rule_55) **','** (44) [20](#rule_20) [70](#rule_70) **'-'** (45) [52](#rule_52) [56](#rule_56) **'.'** (46) [75](#rule_75) **'/'** (47) [54](#rule_54) **';'** (59) [6](#rule_6) [8](#rule_8) [9](#rule_9) [22](#rule_22) [24](#rule_24) [36](#rule_36) [37](#rule_37) [38](#rule_38) [42](#rule_42) [43](#rule_43) **'='** (61) [38](#rule_38) [50](#rule_50) **'\['** (91) [68](#rule_68) [74](#rule_74) **'\]'** (93) [68](#rule_68) [74](#rule_74) **'{'** (123) [8](#rule_8) [11](#rule_11) [27](#rule_27) [30](#rule_30) **'}'** (125) [5](#rule_5) [10](#rule_10) [11](#rule_11) [29](#rule_29) [30](#rule_30) **error** (256) [5](#rule_5) [6](#rule_6) **TOK\_VOID** (258) [14](#rule_14) **TOK\_CHAR** (259) **TOK\_INT** (260) [15](#rule_15) **TOK\_STRING** (261) [16](#rule_16) [67](#rule_67) **TOK\_IF** (262) [40](#rule_40) [41](#rule_41) **TOK\_ELSE** (263) [40](#rule_40) **TOK\_WHILE** (264) [39](#rule_39) **TOK\_RETURN** (265) [42](#rule_42) [43](#rule_43) **TOK\_STRUCT** (266) [10](#rule_10) [11](#rule_11) **TOK\_NULL** (267) [79](#rule_79) **TOK\_NEW** (268) [58](#rule_58) [66](#rule_66) [67](#rule_67) [68](#rule_68) **TOK\_ARRAY** (269) [13](#rule_13) [26](#rule_26) **TOK\_EQ** (270) [44](#rule_44) **TOK\_NE** (271) [45](#rule_45) **TOK\_LT** (272) [46](#rule_46) **TOK\_LE** (273) [47](#rule_47) **TOK\_GT** (274) [48](#rule_48) **TOK\_GE** (275) [49](#rule_49) **TOK\_IDENT** (276) [10](#rule_10) [11](#rule_11) [12](#rule_12) [13](#rule_13) [18](#rule_18) [25](#rule_25) [26](#rule_26) [66](#rule_66) [69](#rule_69) [72](#rule_72) [73](#rule_73) [75](#rule_75) **TOK\_INTCON** (277) [76](#rule_76) **TOK\_CHARCON** (278) [77](#rule_77) **TOK\_STRINGCON** (279) [78](#rule_78) **TOK\_BLOCK** (280) **TOK\_CALL** (281) **TOK\_IFELSE** (282) **TOK\_INITDECL** (283) **TOK\_POS** (284) **TOK\_NEG** (285) **TOK\_NEWARRAY** (286) **TOK\_TYPEID** (287) [17](#rule_17) **TOK\_FIELD** (288) **TOK\_ORD** (289) **TOK\_CHR** (290) **TOK\_ROOT** (291) **TOK\_NEWSTRING** (292) **TOK\_RETURNVOID** (293) **TOK\_VARDECL** (294) **TOK\_FUNCTION** (295) **TOK\_PARAMLIST** (296) **TOK\_PROTOTYPE** (297) **TOK\_INDEX** (298) **TOK\_DECLID** (299)

### Nonterminals, with rules where they appear

**$accept** (61) on left: [0](#rule_0) **start** (62) on left: [1](#rule_1) on right: [0](#rule_0) **program** (63) on left: [2](#rule_2) [3](#rule_3) [4](#rule_4) [5](#rule_5) [6](#rule_6) [7](#rule_7) on right: [1](#rule_1) [2](#rule_2) [3](#rule_3) [4](#rule_4) [5](#rule_5) [6](#rule_6) **structdef\_ellipse** (64) on left: [8](#rule_8) [9](#rule_9) on right: [9](#rule_9) [10](#rule_10) **structdef** (65) on left: [10](#rule_10) [11](#rule_11) on right: [2](#rule_2) **fielddecl** (66) on left: [12](#rule_12) [13](#rule_13) on right: [8](#rule_8) [9](#rule_9) **basetype** (67) on left: [14](#rule_14) [15](#rule_15) [16](#rule_16) [17](#rule_17) [18](#rule_18) on right: [12](#rule_12) [13](#rule_13) [25](#rule_25) [26](#rule_26) [68](#rule_68) **function\_ellipse** (68) on left: [19](#rule_19) [20](#rule_20) on right: [20](#rule_20) [21](#rule_21) [22](#rule_22) **function** (69) on left: [21](#rule_21) [22](#rule_22) [23](#rule_23) [24](#rule_24) on right: [3](#rule_3) **identdecl** (70) on left: [25](#rule_25) [26](#rule_26) on right: [19](#rule_19) [20](#rule_20) [21](#rule_21) [22](#rule_22) [23](#rule_23) [24](#rule_24) [38](#rule_38) **block\_ellipse** (71) on left: [27](#rule_27) [28](#rule_28) on right: [28](#rule_28) [29](#rule_29) **block** (72) on left: [29](#rule_29) [30](#rule_30) on right: [21](#rule_21) [23](#rule_23) [31](#rule_31) **statement** (73) on left: [31](#rule_31) [32](#rule_32) [33](#rule_33) [34](#rule_34) [35](#rule_35) [36](#rule_36) [37](#rule_37) on right: [4](#rule_4) [27](#rule_27) [28](#rule_28) [39](#rule_39) [40](#rule_40) [41](#rule_41) **vardecl** (74) on left: [38](#rule_38) on right: [32](#rule_32) **while** (75) on left: [39](#rule_39) on right: [33](#rule_33) **ifelse** (76) on left: [40](#rule_40) [41](#rule_41) on right: [34](#rule_34) **return** (77) on left: [42](#rule_42) [43](#rule_43) on right: [35](#rule_35) **binop** (78) on left: [44](#rule_44) [45](#rule_45) [46](#rule_46) [47](#rule_47) [48](#rule_48) [49](#rule_49) [50](#rule_50) [51](#rule_51) [52](#rule_52) [53](#rule_53) [54](#rule_54) on right: [59](#rule_59) **unop** (79) on left: [55](#rule_55) [56](#rule_56) [57](#rule_57) [58](#rule_58) on right: [60](#rule_60) **expr** (80) on left: [59](#rule_59) [60](#rule_60) [61](#rule_61) [62](#rule_62) [63](#rule_63) [64](#rule_64) [65](#rule_65) on right: [36](#rule_36) [38](#rule_38) [39](#rule_39) [40](#rule_40) [41](#rule_41) [42](#rule_42) [59](#rule_59) [60](#rule_60) [63](#rule_63) [67](#rule_67) [68](#rule_68) [69](#rule_69) [70](#rule_70) [74](#rule_74) [75](#rule_75) **allocator** (81) on left: [66](#rule_66) [67](#rule_67) [68](#rule_68) on right: [61](#rule_61) **call\_elipse** (82) on left: [69](#rule_69) [70](#rule_70) on right: [70](#rule_70) [71](#rule_71) **call** (83) on left: [71](#rule_71) [72](#rule_72) on right: [62](#rule_62) **variable** (84) on left: [73](#rule_73) [74](#rule_74) [75](#rule_75) on right: [64](#rule_64) **constant** (85) on left: [76](#rule_76) [77](#rule_77) [78](#rule_78) [79](#rule_79) on right: [65](#rule_65)

Automaton
---------

### state 0

[0](#rule_0) $accept → . start **$end** [1](#rule_1) start → . program [2](#rule_2) program → . program structdef [3](#rule_3) | . program function [4](#rule_4) | . program statement [5](#rule_5) | . program **error** **'}'** [6](#rule_6) | . program **error** **';'** [7](#rule_7) | . %empty $default [reduce using rule 7](#rule_7) (program) start [go to state 1](#state_1) program [go to state 2](#state_2)

### state 1

[0](#rule_0) $accept → start . **$end** $end [shift, and go to state 3](#state_3)

### state 2

[1](#rule_1) start → program . \[$end\] [2](#rule_2) program → program . structdef [3](#rule_3) | program . function [4](#rule_4) | program . statement [5](#rule_5) | program . **error** **'}'** [6](#rule_6) | program . **error** **';'** [10](#rule_10) structdef → . **TOK\_STRUCT** **TOK\_IDENT** structdef\_ellipse **'}'** [11](#rule_11) | . **TOK\_STRUCT** **TOK\_IDENT** **'{'** **'}'** [14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [21](#rule_21) function → . identdecl function\_ellipse **')'** block [22](#rule_22) | . identdecl function\_ellipse **')'** **';'** [23](#rule_23) | . identdecl **'('** **')'** block [24](#rule_24) | . identdecl **'('** **')'** **';'** [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [27](#rule_27) block\_ellipse → . **'{'** statement [28](#rule_28) | . block\_ellipse statement [29](#rule_29) block → . block\_ellipse **'}'** [30](#rule_30) | . **'{'** **'}'** [31](#rule_31) statement → . block [32](#rule_32) | . vardecl [33](#rule_33) | . while [34](#rule_34) | . ifelse [35](#rule_35) | . return [36](#rule_36) | . expr **';'** [37](#rule_37) | . **';'** [38](#rule_38) vardecl → . identdecl **'='** expr **';'** [39](#rule_39) while → . **TOK\_WHILE** **'('** expr **')'** statement [40](#rule_40) ifelse → . **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement [41](#rule_41) | . **TOK\_IF** **'('** expr **')'** statement [42](#rule_42) return → . **TOK\_RETURN** expr **';'** [43](#rule_43) | . **TOK\_RETURN** **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** error [shift, and go to state 4](#state_4) TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IF [shift, and go to state 8](#state_8) TOK\_WHILE [shift, and go to state 9](#state_9) TOK\_RETURN [shift, and go to state 10](#state_10) TOK\_STRUCT [shift, and go to state 11](#state_11) TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 14](#state_14) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) TOK\_TYPEID [shift, and go to state 18](#state_18) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '{' [shift, and go to state 21](#state_21) '!' [shift, and go to state 22](#state_22) ';' [shift, and go to state 23](#state_23) '(' [shift, and go to state 24](#state_24) $end [reduce using rule 1](#rule_1) (start) structdef [go to state 25](#state_25) basetype [go to state 26](#state_26) function [go to state 27](#state_27) identdecl [go to state 28](#state_28) block\_ellipse [go to state 29](#state_29) block [go to state 30](#state_30) statement [go to state 31](#state_31) vardecl [go to state 32](#state_32) while [go to state 33](#state_33) ifelse [go to state 34](#state_34) return [go to state 35](#state_35) unop [go to state 36](#state_36) expr [go to state 37](#state_37) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 3

[0](#rule_0) $accept → start **$end** . $default accept

### state 4

[5](#rule_5) program → program **error** . **'}'** [6](#rule_6) | program **error** . **';'** '}' [shift, and go to state 43](#state_43) ';' [shift, and go to state 44](#state_44)

### state 5

[14](#rule_14) basetype → **TOK\_VOID** . $default [reduce using rule 14](#rule_14) (basetype)

### state 6

[15](#rule_15) basetype → **TOK\_INT** . $default [reduce using rule 15](#rule_15) (basetype)

### state 7

[16](#rule_16) basetype → **TOK\_STRING** . $default [reduce using rule 16](#rule_16) (basetype)

### state 8

[40](#rule_40) ifelse → **TOK\_IF** . **'('** expr **')'** statement **TOK\_ELSE** statement [41](#rule_41) | **TOK\_IF** . **'('** expr **')'** statement '(' [shift, and go to state 45](#state_45)

### state 9

[39](#rule_39) while → **TOK\_WHILE** . **'('** expr **')'** statement '(' [shift, and go to state 46](#state_46)

### state 10

[42](#rule_42) return → **TOK\_RETURN** . expr **';'** [43](#rule_43) | **TOK\_RETURN** . **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) ';' [shift, and go to state 48](#state_48) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 49](#state_49) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 11

[10](#rule_10) structdef → **TOK\_STRUCT** . **TOK\_IDENT** structdef\_ellipse **'}'** [11](#rule_11) | **TOK\_STRUCT** . **TOK\_IDENT** **'{'** **'}'** TOK\_IDENT [shift, and go to state 50](#state_50)

### state 12

[79](#rule_79) constant → **TOK\_NULL** . $default [reduce using rule 79](#rule_79) (constant)

### state 13

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [58](#rule_58) unop → **TOK\_NEW** . \[TOK\_NULL, TOK\_NEW, TOK\_INTCON, TOK\_CHARCON, TOK\_STRINGCON, '+', '-', '!', '('\] [66](#rule_66) allocator → **TOK\_NEW** . **TOK\_IDENT** **'('** **')'** [67](#rule_67) | **TOK\_NEW** . **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | **TOK\_NEW** . basetype **'\['** expr **'\]'** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 51](#state_51) TOK\_IDENT [shift, and go to state 52](#state_52) TOK\_TYPEID [shift, and go to state 18](#state_18) $default [reduce using rule 58](#rule_58) (unop) basetype [go to state 53](#state_53) Conflict between [rule 58](#rule_58) and token TOK\_IDENT resolved as shift (TOK\_NEW < TOK\_IDENT).

### state 14

[18](#rule_18) basetype → **TOK\_IDENT** . \[TOK\_ARRAY, TOK\_IDENT\] [69](#rule_69) call\_elipse → **TOK\_IDENT** . **'('** expr [72](#rule_72) call → **TOK\_IDENT** . **'('** **')'** [73](#rule_73) variable → **TOK\_IDENT** . \[TOK\_EQ, TOK\_NE, TOK\_LT, TOK\_LE, TOK\_GT, TOK\_GE, '=', '+', '-', '\*', '/', '.', ';', '\['\] '(' [shift, and go to state 54](#state_54) TOK\_ARRAY [reduce using rule 18](#rule_18) (basetype) TOK\_IDENT [reduce using rule 18](#rule_18) (basetype) $default [reduce using rule 73](#rule_73) (variable)

### state 15

[76](#rule_76) constant → **TOK\_INTCON** . $default [reduce using rule 76](#rule_76) (constant)

### state 16

[77](#rule_77) constant → **TOK\_CHARCON** . $default [reduce using rule 77](#rule_77) (constant)

### state 17

[78](#rule_78) constant → **TOK\_STRINGCON** . $default [reduce using rule 78](#rule_78) (constant)

### state 18

[17](#rule_17) basetype → **TOK\_TYPEID** . $default [reduce using rule 17](#rule_17) (basetype)

### state 19

[55](#rule_55) unop → **'+'** . $default [reduce using rule 55](#rule_55) (unop)

### state 20

[56](#rule_56) unop → **'-'** . $default [reduce using rule 56](#rule_56) (unop)

### state 21

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [27](#rule_27) block\_ellipse → . **'{'** statement [27](#rule_27) | **'{'** . statement [28](#rule_28) | . block\_ellipse statement [29](#rule_29) block → . block\_ellipse **'}'** [30](#rule_30) | . **'{'** **'}'** [30](#rule_30) | **'{'** . **'}'** [31](#rule_31) statement → . block [32](#rule_32) | . vardecl [33](#rule_33) | . while [34](#rule_34) | . ifelse [35](#rule_35) | . return [36](#rule_36) | . expr **';'** [37](#rule_37) | . **';'** [38](#rule_38) vardecl → . identdecl **'='** expr **';'** [39](#rule_39) while → . **TOK\_WHILE** **'('** expr **')'** statement [40](#rule_40) ifelse → . **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement [41](#rule_41) | . **TOK\_IF** **'('** expr **')'** statement [42](#rule_42) return → . **TOK\_RETURN** expr **';'** [43](#rule_43) | . **TOK\_RETURN** **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IF [shift, and go to state 8](#state_8) TOK\_WHILE [shift, and go to state 9](#state_9) TOK\_RETURN [shift, and go to state 10](#state_10) TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 14](#state_14) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) TOK\_TYPEID [shift, and go to state 18](#state_18) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '{' [shift, and go to state 21](#state_21) '!' [shift, and go to state 22](#state_22) '}' [shift, and go to state 55](#state_55) ';' [shift, and go to state 23](#state_23) '(' [shift, and go to state 24](#state_24) basetype [go to state 26](#state_26) identdecl [go to state 56](#state_56) block\_ellipse [go to state 29](#state_29) block [go to state 30](#state_30) statement [go to state 57](#state_57) vardecl [go to state 32](#state_32) while [go to state 33](#state_33) ifelse [go to state 34](#state_34) return [go to state 35](#state_35) unop [go to state 36](#state_36) expr [go to state 37](#state_37) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 22

[57](#rule_57) unop → **'!'** . $default [reduce using rule 57](#rule_57) (unop)

### state 23

[37](#rule_37) statement → **';'** . $default [reduce using rule 37](#rule_37) (statement)

### state 24

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [63](#rule_63) | **'('** . expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 58](#state_58) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 25

[2](#rule_2) program → program structdef . $default [reduce using rule 2](#rule_2) (program)

### state 26

[25](#rule_25) identdecl → basetype . **TOK\_IDENT** [26](#rule_26) | basetype . **TOK\_ARRAY** **TOK\_IDENT** TOK\_ARRAY [shift, and go to state 59](#state_59) TOK\_IDENT [shift, and go to state 60](#state_60)

### state 27

[3](#rule_3) program → program function . $default [reduce using rule 3](#rule_3) (program)

### state 28

[19](#rule_19) function\_ellipse → . **'('** identdecl [20](#rule_20) | . function\_ellipse **','** identdecl [21](#rule_21) function → identdecl . function\_ellipse **')'** block [22](#rule_22) | identdecl . function\_ellipse **')'** **';'** [23](#rule_23) | identdecl . **'('** **')'** block [24](#rule_24) | identdecl . **'('** **')'** **';'** [38](#rule_38) vardecl → identdecl . **'='** expr **';'** '=' [shift, and go to state 61](#state_61) '(' [shift, and go to state 62](#state_62) function\_ellipse [go to state 63](#state_63)

### state 29

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [27](#rule_27) block\_ellipse → . **'{'** statement [28](#rule_28) | . block\_ellipse statement [28](#rule_28) | block\_ellipse . statement [29](#rule_29) block → . block\_ellipse **'}'** [29](#rule_29) | block\_ellipse . **'}'** [30](#rule_30) | . **'{'** **'}'** [31](#rule_31) statement → . block [32](#rule_32) | . vardecl [33](#rule_33) | . while [34](#rule_34) | . ifelse [35](#rule_35) | . return [36](#rule_36) | . expr **';'** [37](#rule_37) | . **';'** [38](#rule_38) vardecl → . identdecl **'='** expr **';'** [39](#rule_39) while → . **TOK\_WHILE** **'('** expr **')'** statement [40](#rule_40) ifelse → . **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement [41](#rule_41) | . **TOK\_IF** **'('** expr **')'** statement [42](#rule_42) return → . **TOK\_RETURN** expr **';'** [43](#rule_43) | . **TOK\_RETURN** **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IF [shift, and go to state 8](#state_8) TOK\_WHILE [shift, and go to state 9](#state_9) TOK\_RETURN [shift, and go to state 10](#state_10) TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 14](#state_14) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) TOK\_TYPEID [shift, and go to state 18](#state_18) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '{' [shift, and go to state 21](#state_21) '!' [shift, and go to state 22](#state_22) '}' [shift, and go to state 64](#state_64) ';' [shift, and go to state 23](#state_23) '(' [shift, and go to state 24](#state_24) basetype [go to state 26](#state_26) identdecl [go to state 56](#state_56) block\_ellipse [go to state 29](#state_29) block [go to state 30](#state_30) statement [go to state 65](#state_65) vardecl [go to state 32](#state_32) while [go to state 33](#state_33) ifelse [go to state 34](#state_34) return [go to state 35](#state_35) unop [go to state 36](#state_36) expr [go to state 37](#state_37) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 30

[31](#rule_31) statement → block . $default [reduce using rule 31](#rule_31) (statement)

### state 31

[4](#rule_4) program → program statement . $default [reduce using rule 4](#rule_4) (program)

### state 32

[32](#rule_32) statement → vardecl . $default [reduce using rule 32](#rule_32) (statement)

### state 33

[33](#rule_33) statement → while . $default [reduce using rule 33](#rule_33) (statement)

### state 34

[34](#rule_34) statement → ifelse . $default [reduce using rule 34](#rule_34) (statement)

### state 35

[35](#rule_35) statement → return . $default [reduce using rule 35](#rule_35) (statement)

### state 36

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [60](#rule_60) | unop . expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 66](#state_66) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 37

[36](#rule_36) statement → expr . **';'** [44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) ';' [shift, and go to state 79](#state_79) '\[' [shift, and go to state 80](#state_80) binop [go to state 81](#state_81)

### state 38

[61](#rule_61) expr → allocator . $default [reduce using rule 61](#rule_61) (expr)

### state 39

[70](#rule_70) call\_elipse → call\_elipse . **','** expr [71](#rule_71) call → call\_elipse . **')'** ',' [shift, and go to state 82](#state_82) ')' [shift, and go to state 83](#state_83)

### state 40

[62](#rule_62) expr → call . $default [reduce using rule 62](#rule_62) (expr)

### state 41

[64](#rule_64) expr → variable . $default [reduce using rule 64](#rule_64) (expr)

### state 42

[65](#rule_65) expr → constant . $default [reduce using rule 65](#rule_65) (expr)

### state 43

[5](#rule_5) program → program **error** **'}'** . $default [reduce using rule 5](#rule_5) (program)

### state 44

[6](#rule_6) program → program **error** **';'** . $default [reduce using rule 6](#rule_6) (program)

### state 45

[40](#rule_40) ifelse → **TOK\_IF** **'('** . expr **')'** statement **TOK\_ELSE** statement [41](#rule_41) | **TOK\_IF** **'('** . expr **')'** statement [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 84](#state_84) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 46

[39](#rule_39) while → **TOK\_WHILE** **'('** . expr **')'** statement [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 85](#state_85) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 47

[69](#rule_69) call\_elipse → **TOK\_IDENT** . **'('** expr [72](#rule_72) call → **TOK\_IDENT** . **'('** **')'** [73](#rule_73) variable → **TOK\_IDENT** . \[TOK\_EQ, TOK\_NE, TOK\_LT, TOK\_LE, TOK\_GT, TOK\_GE, '=', '+', '-', '\*', '/', '.', ';', ',', ')', '\[', '\]'\] '(' [shift, and go to state 54](#state_54) $default [reduce using rule 73](#rule_73) (variable)

### state 48

[43](#rule_43) return → **TOK\_RETURN** **';'** . $default [reduce using rule 43](#rule_43) (return)

### state 49

[42](#rule_42) return → **TOK\_RETURN** expr . **';'** [44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) ';' [shift, and go to state 86](#state_86) '\[' [shift, and go to state 80](#state_80) binop [go to state 81](#state_81)

### state 50

[8](#rule_8) structdef\_ellipse → . **'{'** fielddecl **';'** [9](#rule_9) | . structdef\_ellipse fielddecl **';'** [10](#rule_10) structdef → **TOK\_STRUCT** **TOK\_IDENT** . structdef\_ellipse **'}'** [11](#rule_11) | **TOK\_STRUCT** **TOK\_IDENT** . **'{'** **'}'** '{' [shift, and go to state 87](#state_87) structdef\_ellipse [go to state 88](#state_88)

### state 51

[16](#rule_16) basetype → **TOK\_STRING** . \['\['\] [67](#rule_67) allocator → **TOK\_NEW** **TOK\_STRING** . **'('** expr **')'** '(' [shift, and go to state 89](#state_89) $default [reduce using rule 16](#rule_16) (basetype)

### state 52

[18](#rule_18) basetype → **TOK\_IDENT** . \['\['\] [66](#rule_66) allocator → **TOK\_NEW** **TOK\_IDENT** . **'('** **')'** '(' [shift, and go to state 90](#state_90) $default [reduce using rule 18](#rule_18) (basetype)

### state 53

[68](#rule_68) allocator → **TOK\_NEW** basetype . **'\['** expr **'\]'** '\[' [shift, and go to state 91](#state_91)

### state 54

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [69](#rule_69) | **TOK\_IDENT** **'('** . expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [72](#rule_72) | **TOK\_IDENT** **'('** . **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) ')' [shift, and go to state 92](#state_92) unop [go to state 36](#state_36) expr [go to state 93](#state_93) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 55

[30](#rule_30) block → **'{'** **'}'** . $default [reduce using rule 30](#rule_30) (block)

### state 56

[38](#rule_38) vardecl → identdecl . **'='** expr **';'** '=' [shift, and go to state 61](#state_61)

### state 57

[27](#rule_27) block\_ellipse → **'{'** statement . $default [reduce using rule 27](#rule_27) (block\_ellipse)

### state 58

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [63](#rule_63) | **'('** expr . **')'** [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) ')' [shift, and go to state 94](#state_94) '\[' [shift, and go to state 80](#state_80) binop [go to state 81](#state_81)

### state 59

[26](#rule_26) identdecl → basetype **TOK\_ARRAY** . **TOK\_IDENT** TOK\_IDENT [shift, and go to state 95](#state_95)

### state 60

[25](#rule_25) identdecl → basetype **TOK\_IDENT** . $default [reduce using rule 25](#rule_25) (identdecl)

### state 61

[38](#rule_38) vardecl → identdecl **'='** . expr **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 96](#state_96) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 62

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [19](#rule_19) function\_ellipse → **'('** . identdecl [23](#rule_23) function → identdecl **'('** . **')'** block [24](#rule_24) | identdecl **'('** . **')'** **';'** [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IDENT [shift, and go to state 97](#state_97) TOK\_TYPEID [shift, and go to state 18](#state_18) ')' [shift, and go to state 98](#state_98) basetype [go to state 26](#state_26) identdecl [go to state 99](#state_99)

### state 63

[20](#rule_20) function\_ellipse → function\_ellipse . **','** identdecl [21](#rule_21) function → identdecl function\_ellipse . **')'** block [22](#rule_22) | identdecl function\_ellipse . **')'** **';'** ',' [shift, and go to state 100](#state_100) ')' [shift, and go to state 101](#state_101)

### state 64

[29](#rule_29) block → block\_ellipse **'}'** . $default [reduce using rule 29](#rule_29) (block)

### state 65

[28](#rule_28) block\_ellipse → block\_ellipse statement . $default [reduce using rule 28](#rule_28) (block\_ellipse)

### state 66

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [60](#rule_60) | unop expr . \[TOK\_EQ, TOK\_NE, TOK\_LT, TOK\_LE, TOK\_GT, TOK\_GE, '=', '+', '-', '\*', '/', '.', ';', ',', ')', '\[', '\]'\] [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) '\[' [shift, and go to state 80](#state_80) TOK\_EQ \[[reduce using rule 60](#rule_60) (expr)\] TOK\_NE \[[reduce using rule 60](#rule_60) (expr)\] TOK\_LT \[[reduce using rule 60](#rule_60) (expr)\] TOK\_LE \[[reduce using rule 60](#rule_60) (expr)\] TOK\_GT \[[reduce using rule 60](#rule_60) (expr)\] TOK\_GE \[[reduce using rule 60](#rule_60) (expr)\] '=' \[[reduce using rule 60](#rule_60) (expr)\] '+' \[[reduce using rule 60](#rule_60) (expr)\] '-' \[[reduce using rule 60](#rule_60) (expr)\] '\*' \[[reduce using rule 60](#rule_60) (expr)\] '/' \[[reduce using rule 60](#rule_60) (expr)\] '.' \[[reduce using rule 60](#rule_60) (expr)\] '\[' \[[reduce using rule 60](#rule_60) (expr)\] $default [reduce using rule 60](#rule_60) (expr) binop [go to state 81](#state_81)

### state 67

[44](#rule_44) binop → **TOK\_EQ** . $default [reduce using rule 44](#rule_44) (binop)

### state 68

[45](#rule_45) binop → **TOK\_NE** . $default [reduce using rule 45](#rule_45) (binop)

### state 69

[46](#rule_46) binop → **TOK\_LT** . $default [reduce using rule 46](#rule_46) (binop)

### state 70

[47](#rule_47) binop → **TOK\_LE** . $default [reduce using rule 47](#rule_47) (binop)

### state 71

[48](#rule_48) binop → **TOK\_GT** . $default [reduce using rule 48](#rule_48) (binop)

### state 72

[49](#rule_49) binop → **TOK\_GE** . $default [reduce using rule 49](#rule_49) (binop)

### state 73

[50](#rule_50) binop → **'='** . $default [reduce using rule 50](#rule_50) (binop)

### state 74

[51](#rule_51) binop → **'+'** . $default [reduce using rule 51](#rule_51) (binop)

### state 75

[52](#rule_52) binop → **'-'** . $default [reduce using rule 52](#rule_52) (binop)

### state 76

[53](#rule_53) binop → **'\*'** . $default [reduce using rule 53](#rule_53) (binop)

### state 77

[54](#rule_54) binop → **'/'** . $default [reduce using rule 54](#rule_54) (binop)

### state 78

[75](#rule_75) variable → expr **'.'** . **TOK\_IDENT** TOK\_IDENT [shift, and go to state 102](#state_102)

### state 79

[36](#rule_36) statement → expr **';'** . $default [reduce using rule 36](#rule_36) (statement)

### state 80

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [74](#rule_74) | expr **'\['** . expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 103](#state_103) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 81

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [59](#rule_59) | expr binop . expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 104](#state_104) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 82

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [70](#rule_70) | call\_elipse **','** . expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 105](#state_105) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 83

[71](#rule_71) call → call\_elipse **')'** . $default [reduce using rule 71](#rule_71) (call)

### state 84

[40](#rule_40) ifelse → **TOK\_IF** **'('** expr . **')'** statement **TOK\_ELSE** statement [41](#rule_41) | **TOK\_IF** **'('** expr . **')'** statement [44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) ')' [shift, and go to state 106](#state_106) '\[' [shift, and go to state 80](#state_80) binop [go to state 81](#state_81)

### state 85

[39](#rule_39) while → **TOK\_WHILE** **'('** expr . **')'** statement [44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) ')' [shift, and go to state 107](#state_107) '\[' [shift, and go to state 80](#state_80) binop [go to state 81](#state_81)

### state 86

[42](#rule_42) return → **TOK\_RETURN** expr **';'** . $default [reduce using rule 42](#rule_42) (return)

### state 87

[8](#rule_8) structdef\_ellipse → **'{'** . fielddecl **';'** [11](#rule_11) structdef → **TOK\_STRUCT** **TOK\_IDENT** **'{'** . **'}'** [12](#rule_12) fielddecl → . basetype **TOK\_IDENT** [13](#rule_13) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IDENT [shift, and go to state 97](#state_97) TOK\_TYPEID [shift, and go to state 18](#state_18) '}' [shift, and go to state 108](#state_108) fielddecl [go to state 109](#state_109) basetype [go to state 110](#state_110)

### state 88

[9](#rule_9) structdef\_ellipse → structdef\_ellipse . fielddecl **';'** [10](#rule_10) structdef → **TOK\_STRUCT** **TOK\_IDENT** structdef\_ellipse . **'}'** [12](#rule_12) fielddecl → . basetype **TOK\_IDENT** [13](#rule_13) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IDENT [shift, and go to state 97](#state_97) TOK\_TYPEID [shift, and go to state 18](#state_18) '}' [shift, and go to state 111](#state_111) fielddecl [go to state 112](#state_112) basetype [go to state 110](#state_110)

### state 89

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [67](#rule_67) | **TOK\_NEW** **TOK\_STRING** **'('** . expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 113](#state_113) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 90

[66](#rule_66) allocator → **TOK\_NEW** **TOK\_IDENT** **'('** . **')'** ')' [shift, and go to state 114](#state_114)

### state 91

[55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [68](#rule_68) | **TOK\_NEW** basetype **'\['** . expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 47](#state_47) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '!' [shift, and go to state 22](#state_22) '(' [shift, and go to state 24](#state_24) unop [go to state 36](#state_36) expr [go to state 115](#state_115) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 92

[72](#rule_72) call → **TOK\_IDENT** **'('** **')'** . $default [reduce using rule 72](#rule_72) (call)

### state 93

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [69](#rule_69) call\_elipse → **TOK\_IDENT** **'('** expr . \[',', ')'\] [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) '\[' [shift, and go to state 80](#state_80) $default [reduce using rule 69](#rule_69) (call\_elipse) binop [go to state 81](#state_81)

### state 94

[63](#rule_63) expr → **'('** expr **')'** . $default [reduce using rule 63](#rule_63) (expr)

### state 95

[26](#rule_26) identdecl → basetype **TOK\_ARRAY** **TOK\_IDENT** . $default [reduce using rule 26](#rule_26) (identdecl)

### state 96

[38](#rule_38) vardecl → identdecl **'='** expr . **';'** [44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) ';' [shift, and go to state 116](#state_116) '\[' [shift, and go to state 80](#state_80) binop [go to state 81](#state_81)

### state 97

[18](#rule_18) basetype → **TOK\_IDENT** . $default [reduce using rule 18](#rule_18) (basetype)

### state 98

[23](#rule_23) function → identdecl **'('** **')'** . block [24](#rule_24) | identdecl **'('** **')'** . **';'** [27](#rule_27) block\_ellipse → . **'{'** statement [28](#rule_28) | . block\_ellipse statement [29](#rule_29) block → . block\_ellipse **'}'** [30](#rule_30) | . **'{'** **'}'** '{' [shift, and go to state 21](#state_21) ';' [shift, and go to state 117](#state_117) block\_ellipse [go to state 29](#state_29) block [go to state 118](#state_118)

### state 99

[19](#rule_19) function\_ellipse → **'('** identdecl . $default [reduce using rule 19](#rule_19) (function\_ellipse)

### state 100

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [20](#rule_20) function\_ellipse → function\_ellipse **','** . identdecl [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IDENT [shift, and go to state 97](#state_97) TOK\_TYPEID [shift, and go to state 18](#state_18) basetype [go to state 26](#state_26) identdecl [go to state 119](#state_119)

### state 101

[21](#rule_21) function → identdecl function\_ellipse **')'** . block [22](#rule_22) | identdecl function\_ellipse **')'** . **';'** [27](#rule_27) block\_ellipse → . **'{'** statement [28](#rule_28) | . block\_ellipse statement [29](#rule_29) block → . block\_ellipse **'}'** [30](#rule_30) | . **'{'** **'}'** '{' [shift, and go to state 21](#state_21) ';' [shift, and go to state 120](#state_120) block\_ellipse [go to state 29](#state_29) block [go to state 121](#state_121)

### state 102

[75](#rule_75) variable → expr **'.'** **TOK\_IDENT** . $default [reduce using rule 75](#rule_75) (variable)

### state 103

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [74](#rule_74) variable → expr . **'\['** expr **'\]'** [74](#rule_74) | expr **'\['** expr . **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) '\[' [shift, and go to state 80](#state_80) '\]' [shift, and go to state 122](#state_122) binop [go to state 81](#state_81)

### state 104

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [59](#rule_59) | expr binop expr . \[TOK\_EQ, TOK\_NE, TOK\_LT, TOK\_LE, TOK\_GT, TOK\_GE, '=', '+', '-', '\*', '/', '.', ';', ',', ')', '\[', '\]'\] [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) '\[' [shift, and go to state 80](#state_80) TOK\_EQ \[[reduce using rule 59](#rule_59) (expr)\] TOK\_NE \[[reduce using rule 59](#rule_59) (expr)\] TOK\_LT \[[reduce using rule 59](#rule_59) (expr)\] TOK\_LE \[[reduce using rule 59](#rule_59) (expr)\] TOK\_GT \[[reduce using rule 59](#rule_59) (expr)\] TOK\_GE \[[reduce using rule 59](#rule_59) (expr)\] '=' \[[reduce using rule 59](#rule_59) (expr)\] '+' \[[reduce using rule 59](#rule_59) (expr)\] '-' \[[reduce using rule 59](#rule_59) (expr)\] '\*' \[[reduce using rule 59](#rule_59) (expr)\] '/' \[[reduce using rule 59](#rule_59) (expr)\] '.' \[[reduce using rule 59](#rule_59) (expr)\] '\[' \[[reduce using rule 59](#rule_59) (expr)\] $default [reduce using rule 59](#rule_59) (expr) binop [go to state 81](#state_81)

### state 105

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [70](#rule_70) call\_elipse → call\_elipse **','** expr . \[',', ')'\] [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) '\[' [shift, and go to state 80](#state_80) $default [reduce using rule 70](#rule_70) (call\_elipse) binop [go to state 81](#state_81)

### state 106

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [27](#rule_27) block\_ellipse → . **'{'** statement [28](#rule_28) | . block\_ellipse statement [29](#rule_29) block → . block\_ellipse **'}'** [30](#rule_30) | . **'{'** **'}'** [31](#rule_31) statement → . block [32](#rule_32) | . vardecl [33](#rule_33) | . while [34](#rule_34) | . ifelse [35](#rule_35) | . return [36](#rule_36) | . expr **';'** [37](#rule_37) | . **';'** [38](#rule_38) vardecl → . identdecl **'='** expr **';'** [39](#rule_39) while → . **TOK\_WHILE** **'('** expr **')'** statement [40](#rule_40) ifelse → . **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement [40](#rule_40) | **TOK\_IF** **'('** expr **')'** . statement **TOK\_ELSE** statement [41](#rule_41) | . **TOK\_IF** **'('** expr **')'** statement [41](#rule_41) | **TOK\_IF** **'('** expr **')'** . statement [42](#rule_42) return → . **TOK\_RETURN** expr **';'** [43](#rule_43) | . **TOK\_RETURN** **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IF [shift, and go to state 8](#state_8) TOK\_WHILE [shift, and go to state 9](#state_9) TOK\_RETURN [shift, and go to state 10](#state_10) TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 14](#state_14) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) TOK\_TYPEID [shift, and go to state 18](#state_18) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '{' [shift, and go to state 21](#state_21) '!' [shift, and go to state 22](#state_22) ';' [shift, and go to state 23](#state_23) '(' [shift, and go to state 24](#state_24) basetype [go to state 26](#state_26) identdecl [go to state 56](#state_56) block\_ellipse [go to state 29](#state_29) block [go to state 30](#state_30) statement [go to state 123](#state_123) vardecl [go to state 32](#state_32) while [go to state 33](#state_33) ifelse [go to state 34](#state_34) return [go to state 35](#state_35) unop [go to state 36](#state_36) expr [go to state 37](#state_37) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 107

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [27](#rule_27) block\_ellipse → . **'{'** statement [28](#rule_28) | . block\_ellipse statement [29](#rule_29) block → . block\_ellipse **'}'** [30](#rule_30) | . **'{'** **'}'** [31](#rule_31) statement → . block [32](#rule_32) | . vardecl [33](#rule_33) | . while [34](#rule_34) | . ifelse [35](#rule_35) | . return [36](#rule_36) | . expr **';'** [37](#rule_37) | . **';'** [38](#rule_38) vardecl → . identdecl **'='** expr **';'** [39](#rule_39) while → . **TOK\_WHILE** **'('** expr **')'** statement [39](#rule_39) | **TOK\_WHILE** **'('** expr **')'** . statement [40](#rule_40) ifelse → . **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement [41](#rule_41) | . **TOK\_IF** **'('** expr **')'** statement [42](#rule_42) return → . **TOK\_RETURN** expr **';'** [43](#rule_43) | . **TOK\_RETURN** **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IF [shift, and go to state 8](#state_8) TOK\_WHILE [shift, and go to state 9](#state_9) TOK\_RETURN [shift, and go to state 10](#state_10) TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 14](#state_14) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) TOK\_TYPEID [shift, and go to state 18](#state_18) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '{' [shift, and go to state 21](#state_21) '!' [shift, and go to state 22](#state_22) ';' [shift, and go to state 23](#state_23) '(' [shift, and go to state 24](#state_24) basetype [go to state 26](#state_26) identdecl [go to state 56](#state_56) block\_ellipse [go to state 29](#state_29) block [go to state 30](#state_30) statement [go to state 124](#state_124) vardecl [go to state 32](#state_32) while [go to state 33](#state_33) ifelse [go to state 34](#state_34) return [go to state 35](#state_35) unop [go to state 36](#state_36) expr [go to state 37](#state_37) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 108

[11](#rule_11) structdef → **TOK\_STRUCT** **TOK\_IDENT** **'{'** **'}'** . $default [reduce using rule 11](#rule_11) (structdef)

### state 109

[8](#rule_8) structdef\_ellipse → **'{'** fielddecl . **';'** ';' [shift, and go to state 125](#state_125)

### state 110

[12](#rule_12) fielddecl → basetype . **TOK\_IDENT** [13](#rule_13) | basetype . **TOK\_ARRAY** **TOK\_IDENT** TOK\_ARRAY [shift, and go to state 126](#state_126) TOK\_IDENT [shift, and go to state 127](#state_127)

### state 111

[10](#rule_10) structdef → **TOK\_STRUCT** **TOK\_IDENT** structdef\_ellipse **'}'** . $default [reduce using rule 10](#rule_10) (structdef)

### state 112

[9](#rule_9) structdef\_ellipse → structdef\_ellipse fielddecl . **';'** ';' [shift, and go to state 128](#state_128)

### state 113

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [67](#rule_67) allocator → **TOK\_NEW** **TOK\_STRING** **'('** expr . **')'** [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) ')' [shift, and go to state 129](#state_129) '\[' [shift, and go to state 80](#state_80) binop [go to state 81](#state_81)

### state 114

[66](#rule_66) allocator → **TOK\_NEW** **TOK\_IDENT** **'('** **')'** . $default [reduce using rule 66](#rule_66) (allocator)

### state 115

[44](#rule_44) binop → . **TOK\_EQ** [45](#rule_45) | . **TOK\_NE** [46](#rule_46) | . **TOK\_LT** [47](#rule_47) | . **TOK\_LE** [48](#rule_48) | . **TOK\_GT** [49](#rule_49) | . **TOK\_GE** [50](#rule_50) | . **'='** [51](#rule_51) | . **'+'** [52](#rule_52) | . **'-'** [53](#rule_53) | . **'\*'** [54](#rule_54) | . **'/'** [59](#rule_59) expr → expr . binop expr [68](#rule_68) allocator → **TOK\_NEW** basetype **'\['** expr . **'\]'** [74](#rule_74) variable → expr . **'\['** expr **'\]'** [75](#rule_75) | expr . **'.'** **TOK\_IDENT** TOK\_EQ [shift, and go to state 67](#state_67) TOK\_NE [shift, and go to state 68](#state_68) TOK\_LT [shift, and go to state 69](#state_69) TOK\_LE [shift, and go to state 70](#state_70) TOK\_GT [shift, and go to state 71](#state_71) TOK\_GE [shift, and go to state 72](#state_72) '=' [shift, and go to state 73](#state_73) '+' [shift, and go to state 74](#state_74) '-' [shift, and go to state 75](#state_75) '\*' [shift, and go to state 76](#state_76) '/' [shift, and go to state 77](#state_77) '.' [shift, and go to state 78](#state_78) '\[' [shift, and go to state 80](#state_80) '\]' [shift, and go to state 130](#state_130) binop [go to state 81](#state_81)

### state 116

[38](#rule_38) vardecl → identdecl **'='** expr **';'** . $default [reduce using rule 38](#rule_38) (vardecl)

### state 117

[24](#rule_24) function → identdecl **'('** **')'** **';'** . $default [reduce using rule 24](#rule_24) (function)

### state 118

[23](#rule_23) function → identdecl **'('** **')'** block . $default [reduce using rule 23](#rule_23) (function)

### state 119

[20](#rule_20) function\_ellipse → function\_ellipse **','** identdecl . $default [reduce using rule 20](#rule_20) (function\_ellipse)

### state 120

[22](#rule_22) function → identdecl function\_ellipse **')'** **';'** . $default [reduce using rule 22](#rule_22) (function)

### state 121

[21](#rule_21) function → identdecl function\_ellipse **')'** block . $default [reduce using rule 21](#rule_21) (function)

### state 122

[74](#rule_74) variable → expr **'\['** expr **'\]'** . $default [reduce using rule 74](#rule_74) (variable)

### state 123

[40](#rule_40) ifelse → **TOK\_IF** **'('** expr **')'** statement . **TOK\_ELSE** statement [41](#rule_41) | **TOK\_IF** **'('** expr **')'** statement . \[$end, error, TOK\_VOID, TOK\_INT, TOK\_STRING, TOK\_IF, TOK\_ELSE, TOK\_WHILE, TOK\_RETURN, TOK\_STRUCT, TOK\_NULL, TOK\_NEW, TOK\_IDENT, TOK\_INTCON, TOK\_CHARCON, TOK\_STRINGCON, TOK\_TYPEID, '+', '-', '{', '!', '}', ';', '('\] TOK\_ELSE [shift, and go to state 131](#state_131) TOK\_ELSE \[[reduce using rule 41](#rule_41) (ifelse)\] $default [reduce using rule 41](#rule_41) (ifelse)

### state 124

[39](#rule_39) while → **TOK\_WHILE** **'('** expr **')'** statement . $default [reduce using rule 39](#rule_39) (while)

### state 125

[8](#rule_8) structdef\_ellipse → **'{'** fielddecl **';'** . $default [reduce using rule 8](#rule_8) (structdef\_ellipse)

### state 126

[13](#rule_13) fielddecl → basetype **TOK\_ARRAY** . **TOK\_IDENT** TOK\_IDENT [shift, and go to state 132](#state_132)

### state 127

[12](#rule_12) fielddecl → basetype **TOK\_IDENT** . $default [reduce using rule 12](#rule_12) (fielddecl)

### state 128

[9](#rule_9) structdef\_ellipse → structdef\_ellipse fielddecl **';'** . $default [reduce using rule 9](#rule_9) (structdef\_ellipse)

### state 129

[67](#rule_67) allocator → **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** . $default [reduce using rule 67](#rule_67) (allocator)

### state 130

[68](#rule_68) allocator → **TOK\_NEW** basetype **'\['** expr **'\]'** . $default [reduce using rule 68](#rule_68) (allocator)

### state 131

[14](#rule_14) basetype → . **TOK\_VOID** [15](#rule_15) | . **TOK\_INT** [16](#rule_16) | . **TOK\_STRING** [17](#rule_17) | . **TOK\_TYPEID** [18](#rule_18) | . **TOK\_IDENT** [25](#rule_25) identdecl → . basetype **TOK\_IDENT** [26](#rule_26) | . basetype **TOK\_ARRAY** **TOK\_IDENT** [27](#rule_27) block\_ellipse → . **'{'** statement [28](#rule_28) | . block\_ellipse statement [29](#rule_29) block → . block\_ellipse **'}'** [30](#rule_30) | . **'{'** **'}'** [31](#rule_31) statement → . block [32](#rule_32) | . vardecl [33](#rule_33) | . while [34](#rule_34) | . ifelse [35](#rule_35) | . return [36](#rule_36) | . expr **';'** [37](#rule_37) | . **';'** [38](#rule_38) vardecl → . identdecl **'='** expr **';'** [39](#rule_39) while → . **TOK\_WHILE** **'('** expr **')'** statement [40](#rule_40) ifelse → . **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement [40](#rule_40) | **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** . statement [41](#rule_41) | . **TOK\_IF** **'('** expr **')'** statement [42](#rule_42) return → . **TOK\_RETURN** expr **';'** [43](#rule_43) | . **TOK\_RETURN** **';'** [55](#rule_55) unop → . **'+'** [56](#rule_56) | . **'-'** [57](#rule_57) | . **'!'** [58](#rule_58) | . **TOK\_NEW** [59](#rule_59) expr → . expr binop expr [60](#rule_60) | . unop expr [61](#rule_61) | . allocator [62](#rule_62) | . call [63](#rule_63) | . **'('** expr **')'** [64](#rule_64) | . variable [65](#rule_65) | . constant [66](#rule_66) allocator → . **TOK\_NEW** **TOK\_IDENT** **'('** **')'** [67](#rule_67) | . **TOK\_NEW** **TOK\_STRING** **'('** expr **')'** [68](#rule_68) | . **TOK\_NEW** basetype **'\['** expr **'\]'** [69](#rule_69) call\_elipse → . **TOK\_IDENT** **'('** expr [70](#rule_70) | . call\_elipse **','** expr [71](#rule_71) call → . call\_elipse **')'** [72](#rule_72) | . **TOK\_IDENT** **'('** **')'** [73](#rule_73) variable → . **TOK\_IDENT** [74](#rule_74) | . expr **'\['** expr **'\]'** [75](#rule_75) | . expr **'.'** **TOK\_IDENT** [76](#rule_76) constant → . **TOK\_INTCON** [77](#rule_77) | . **TOK\_CHARCON** [78](#rule_78) | . **TOK\_STRINGCON** [79](#rule_79) | . **TOK\_NULL** TOK\_VOID [shift, and go to state 5](#state_5) TOK\_INT [shift, and go to state 6](#state_6) TOK\_STRING [shift, and go to state 7](#state_7) TOK\_IF [shift, and go to state 8](#state_8) TOK\_WHILE [shift, and go to state 9](#state_9) TOK\_RETURN [shift, and go to state 10](#state_10) TOK\_NULL [shift, and go to state 12](#state_12) TOK\_NEW [shift, and go to state 13](#state_13) TOK\_IDENT [shift, and go to state 14](#state_14) TOK\_INTCON [shift, and go to state 15](#state_15) TOK\_CHARCON [shift, and go to state 16](#state_16) TOK\_STRINGCON [shift, and go to state 17](#state_17) TOK\_TYPEID [shift, and go to state 18](#state_18) '+' [shift, and go to state 19](#state_19) '-' [shift, and go to state 20](#state_20) '{' [shift, and go to state 21](#state_21) '!' [shift, and go to state 22](#state_22) ';' [shift, and go to state 23](#state_23) '(' [shift, and go to state 24](#state_24) basetype [go to state 26](#state_26) identdecl [go to state 56](#state_56) block\_ellipse [go to state 29](#state_29) block [go to state 30](#state_30) statement [go to state 133](#state_133) vardecl [go to state 32](#state_32) while [go to state 33](#state_33) ifelse [go to state 34](#state_34) return [go to state 35](#state_35) unop [go to state 36](#state_36) expr [go to state 37](#state_37) allocator [go to state 38](#state_38) call\_elipse [go to state 39](#state_39) call [go to state 40](#state_40) variable [go to state 41](#state_41) constant [go to state 42](#state_42)

### state 132

[13](#rule_13) fielddecl → basetype **TOK\_ARRAY** **TOK\_IDENT** . $default [reduce using rule 13](#rule_13) (fielddecl)

### state 133

[40](#rule_40) ifelse → **TOK\_IF** **'('** expr **')'** statement **TOK\_ELSE** statement . $default [reduce using rule 40](#rule_40) (ifelse)

* * *

This document was generated using [GNU Bison 3.0.4](http://www.gnu.org/software/bison/ "GNU Bison") XML Automaton Report.  
Verbatim copying and distribution of this entire page is permitted in any medium, provided this notice is preserved.
