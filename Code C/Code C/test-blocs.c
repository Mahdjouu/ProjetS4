#include "rsa_header.h"

int main(){
	uchar *msg = (uchar *) malloc(5*sizeof(char));
	//msg = "abcd";
	msg[0] = 'a';msg[1] = 'b';msg[2] = 'c';msg[3] = 'd';
	printf("Message avant : %s\n",msg);
	uint nb;
	nb = convert_4byte2int(msg);
	printf("msg=%s --> nb=%d\n",msg,nb);
	convertInt2uchar(nb,msg);
	printf("nb=%d --> msg=%s\n",nb,msg);
	return 0;
}
