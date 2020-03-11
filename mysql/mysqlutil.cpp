#include <string>
#include <fstream>
#include <mysqlutil.h>

int readSqlCommand(const char *filename, std::string *sql){
	std::string buf;
	std::fstream file;
	
	*sql = "";
	file.open(filename, std::ios::in);
	while (getline(file, buf)){
		*sql = *sql + buf + " ";
	}
	
	return 0;
}