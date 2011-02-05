:compile.bat
  cl /EHsc /DTEST_PARSER ../parser.cpp ../ConfigureParser.cpp ../ActionsAndRules.cpp ../SemiExpression.cpp ../Tokenizer.cpp /link setargv.obj
