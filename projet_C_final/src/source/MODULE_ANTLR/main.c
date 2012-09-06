#include "sLexer.h"
#include "sParser.h"
#include <stdio.h>

int main(int argc, char* argv[]){


  pANTLR3_INPUT_STREAM input;
  psLexer lex;
  pANTLR3_COMMON_TOKEN_STREAM tokens;
  psParser parser;


  input = antlr3AsciiFileStreamNew((pANTLR3_UINT8)argv[1]);
  lex = sLexerNew(input);
  tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lex));
  parser = sParserNew(tokens);

  printf("debut de l'analyse \n");

  parser->s(parser);


  printf("fin de l'analyse \n");
  //parser->free(parser);
  //tokens->free(tokens);
  //lex->free(lex);
  //input->close(input);
  return 0;
}

