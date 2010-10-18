Any question please mail jiangkun1@gmail.com

1 Configure

	The dbparser need libsbml to transfer math expressions to MathML string. So libsbml-3.4.1 or
libsbml 4.0.1 is needed. And modfy those two flags in the Makefile to configure libsbml's header and
libraries path.
	CCFLAGS = -g -I../../ExternalCode/sbml -I../../ExternalCode
	LIBS = libsbml.a libxerces-c.a libxml2.a -lz

2 BUILD

	After configuring, BUILD is very simple. There is only one Makefile in this fold. You can just 
type the command
	make
to build the dbparser.

3 How to use, example

    dbparser is kind of a XML editor, to read a data input configure file to generate the needed XML
formated file. The input file should follow a synatx.
	Take the test1.in as example. Run ./dbparser < test1.in, We can get a XML version file test.xml.

Description:
	1) file = [test.xml]
	   This is to specify the output file name;
	2) module: [helloworld] id = [abcvd];
	   Define a XML node named module, and value is "helloworld", and with attribute id="abcvd"
	3) module id=[a] , name=[b], class=[c], time=[10] { SUBMODULE_STATEMENT };
	   Define a XML node with a XML node as its value, that is to say, define a composite XML node;
    4) math: [a+b];
	   Define a math expression a+b, and it will be transferred to MathML Node.

The synatx is simple, have fun!

4 synatx of input configure file 
synatx:
	files:  /*empty*/
	     | files file_des;
	
	file_des: filename_state module_statement ;
	
	filename_state: TOK_FILENAME '=' VALUESTRING;
		
	module_statement: module_name TOK_GROUPSTART module_body_statement TOK_GROUPEND 
			| TOKEN_IDENTIFIER ':' VALUESTRING module_attribute separte
			| TOK_MATH ':' VALUESTRING separte
			;
	
	module_name: TOKEN_IDENTIFIER module_attribute ;
	
	module_attribute:  /*empty*/
			| module_attribute TOKEN_IDENTIFIER '=' VALUESTRING ;
	
	module_body_statement:  {}/*empty body*/
			     | module_body_statement TOKEN_COMMENT 
			     | module_body_statement module_statement 
			     ;
	separte: ';'
       ;
