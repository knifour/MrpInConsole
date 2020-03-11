#include <iostream>
#include <string>
#include <stdio.h>
#include <mysql.h>
#include <mysqlutil.h>

using namespace std;

int main(void){
	string sql;
	string filename = "OutGet01.sql";
	
	MYSQL *conn = mysql_init(NULL);
	
	if (conn == NULL){
		printf("%s\n", mysql_error(conn));
		return 1;
	}
	
	if (mysql_real_connect(conn, "localhost", "sales", "print", "BF", 0, NULL, 0) == NULL){
    printf("%s\n", mysql_error(conn));
	  return 1;
	}
	
	if (mysql_query(conn, "set names UTF8;")){
		printf("%s\n", mysql_error(conn));
		return 1;
	}
	
	readSqlCommand(filename.c_str(), &sql);
	
	if (mysql_query(conn, sql.c_str())){
		printf("%s\n", mysql_error(conn));
		return 1;
	}
	
	MYSQL_RES *result = mysql_store_result(conn);
	
	if (result == NULL){
		printf("%s\n", mysql_error(conn));
		return 1;
	}
	
	int iFields = mysql_num_fields(result);
	
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	
	while ((row = mysql_fetch_row(result))) {
		for (int i=0; i<iFields; i++) {
			if (i == 0) {
				while (field = mysql_fetch_field(result)) {
					printf("%s ", field->name);
				}
				printf("\n");
			}
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

  mysql_free_result(result);
	mysql_close(conn);
	return 0;
}