#include "dataForm.h"
#include <istream>
#include <fstream>
#include <sstream>

using namespace std;
void  data_Read() {
	FILE * fp;
	if ((fp = fopen("u1817.tsp", "rb")) == NULL) {
		cout<<"Open File failed.\n"<<endl;
		exit(0);
	}

}