grammar s;
options{language=C;}
@parser::includes 
{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aide.h"
}



s 	:'<'bin'>' '<'bin'>'
	'<Document>''<name>'bin'</name>'
		styletag liste '</Document>''</kml>' EOF
	;

styletag
	:	'<Style' bin '>''<IconStyle>''<scale>'coordinate'</scale>''<Icon>''<href>'bin'</href>''</Icon>''</IconStyle>''<LabelStyle>'
		'<color>' name '</color>'
		'<scale>'coordinate'</scale>''</LabelStyle>'
		'</Style>' styletag
		| 	
	;
	
liste	: '<Placemark>'ville'</Placemark>'liste
	| 
	;
	
ville 
	:
	'<name>'nom_ville=name'</name>'
	'<description>''<![CDATA[' '<' bin '>population:' pop=population '<br>'bin '<br>' bin '<a' bin '>' name '</a><' name '>' '</font>' ']]>'   
	'</description>''<styleUrl>'bin'</styleUrl>'  
	'<Point>'coordonnees'</Point>' 
	{printf("\%s,\%d", ($nom_ville.text->chars),($pop.text->toInt32($pop.text)));}
	
	;
	
coordonnees returns [coord c]
	:	'<coordinates>' b=bin '</coordinates>' 	
	{int i=0;int j=0; 

	while(($b.text->chars[i]) != ',') {
	$c.longi[i]=($b.text->chars[i]); i++;
	}
	$c.longi[i]='\0'; j=i+1;
	while(($b.text->chars[j]) != ',') {
	$c.lat[j-i+1]=$b.text->chars[j]; j++;
	} 
	c.lat[j]='\0';
	
	if (($c.longi[0])=='-') ($c.longi[strlen($c.longi)])='W'; else ($c.longi[strlen($c.longi)])='E'; 
	if (($c.lat[0])=='-') ($c.lat[strlen($c.lat)])='S'; else ($c.lat[strlen($c.lat)])='N';
	printf("\%s,\%s\n",$c.lat,$c.longi); 
	}
	;
	
population 
	:	NOM
	;
	
	
coordinate
	: 	COO
	;


bin	:	ALPHA 
	;


name	: 	NOM
	;


COO	:	('-')? ('.'|'0'..'9')+
	;


NOM  
	:('a'..'z'|'A'..'Z'|'0'..'9'|'-'|' '|'É'|'ô'|'é'|'è'|'ö'|'ë'|'\''|'î'|'Î'|'ç'|'â'|'ê'|'à')*
    	;

    
ALPHA
    	: ('a'..'z'|'A'..'Z'| '0'..'9' | '-' |' '|'!' | '"' | ';' | ',' |'&'|'/'|'.'|':'|'?'|']'|'#'|'='|'ô'|'é'|'è'|'ö'|'ë'|'\''|'î'|'Î'|'É')+
    	;

WS  :   ( ' '
        | '\t'
        | '\r'
        | '\n'
        ) {$channel=HIDDEN;}
    ;
