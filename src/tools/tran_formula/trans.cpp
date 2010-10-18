#include <stdio.h>
#include <string.h> 
#include <string> 
#include <sbml/SBMLTypes.h> 
#include <iostream>
#include <fstream>

using namespace std;

//char* translateInfix (const char* formula);
string translateInfix (const char* formula);
char *translateInfixCh (const char* formula);
char * translateMathML (const char* xml);

#define FILE_BUF 256
char buff[FILE_BUF];
string exp_buff;

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		fprintf (stderr, "please input file name");
		return -1;
	}

	if (argc > 2)
	{
		fprintf (stderr, "options error");
		return -1;
	}

	ifstream infile(argv[1], ifstream::in);
	if (!infile)
	{
		fprintf (stderr, "no file %s exist", argv[2]);
		return -1;
	}

	ofstream ofile("out.txt", ofstream::out|ofstream::trunc);
	if (!ofile)
	{
		fprintf (stderr, "file out.txt create error");
		return -1;
	}

	exp_buff.clear();
	int num = 1;
	while (getline(infile, exp_buff, '\n'))
	{
		if (exp_buff.empty())
			continue;

		string xml_str = translateInfix(exp_buff.c_str());
		
		ofile << "--- exp "<< num <<" ---" << endl;
		ofile << xml_str << endl;
		ofile << translateInfixCh(exp_buff.c_str()) << endl;
		ofile << "--- exp "<< num <<" end ---" << endl;

		num ++;
	}

	infile.close();
	ofile.close();

//        printf ("Result:\n %s", translateInfix("A+B"));
	return 0;
}

/**
 * Translates the given infix formula into MathML.
 *
 * @return the MathML as a string.  The caller owns the memory and is
 * responsible for freeing it.
 */
string
translateInfix (const char* formula)
{

  char* result;
  string res;

  ASTNode_t* math = SBML_parseFormula(formula);

  result = writeMathMLToString(math);
  if (result == NULL)
	  return NULL;

  res.clear();
  res += "<math>\n  ";
  char *pos = strstr(result, "<apply>");
  if (pos == NULL)
  {
	  res += "</math>";
	  return res;
  }
  res += pos;

  /*delete the version declaration*/
  /*delete the default namespace*/
  ASTNode_free(math);
  
  if (result != NULL)
	  free (result);
  return res;
}

char*
translateInfixCh (const char* formula)
{

  char* result;
  char* res;

  ASTNode_t* math = SBML_parseFormula(formula);

  result = writeMathMLToString(math);
  if (result == NULL)
	  return NULL;

  int len = strlen(result) + 1;
  res = (char*) malloc (len * sizeof(char));
  memset(res, 0, len * sizeof(char));
  strcpy(res, "<math>\n  ");
  char *pos = strstr(result, "<apply>");
  if (pos == NULL)
  {
	  strcat(res, "<math>\n  ");
	  return res;
  }
  strcat (res, pos);

  /*delete the version declaration*/
  /*delete the default namespace*/
  ASTNode_free(math);
  
  if (result != NULL)
	  free (result);
  return res;
}

/**
 * Translates the given MathML into an infix formula.  The MathML must
 * contain no leading whitespace, but an XML header is optional.
 *
 * @return the infix formula as a string.  The caller owns the memory and
 * is responsible for freeing it.
 */
char * translateMathML (const char* xml)
{
  char*           result;
  ASTNode_t*      math;

  math   = readMathMLFromString(xml);
  result = SBML_formulaToString(math);

  ASTNode_free(math);
  return result;
}
