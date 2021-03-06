#include <mysql.h>
#include <my_global.h>

int error(MYSQL *conn){
  fprintf(stderr, "Error : %s\n", mysql_error(conn) );
  mysql_close(conn);
  exit(1);
}

int main(int argc, char const *argv[]) {
  MYSQL *conn = mysql_init(NULL);

  if(!conn){
    fprintf(stderr, "%s\n", mysql_error(conn) );
    exit(1);
  }

  // We are going to use database cprogram and create the table,
  if( mysql_real_connect(conn, "localhost", "root", "password", "cprogram", 0, NULL, 0) == NULL) {
    error(conn);
  }

  if(mysql_query(conn, "drop table if exists test")){
    error(conn);
  }

  if( mysql_query(conn, "create table test(id INT PRIMARY KEY AUTO_INCREMENT, name TEXT, age INT)")){
    error(conn);
  }
  else{
    fprintf(stderr, "Query Success : table Created \n" );
  }

  mysql_query(conn, "insert into test values(1, 'Venkatesh', 24)");
  mysql_query(conn, "insert into test values(2, 'ravi', 20)");
  mysql_query(conn, "insert into test  values(3, 'Mahesh', 27)");
  mysql_query(conn, "insert into test values(4, 'Rahul', 18)");

  int id = mysql_insert_id(conn);
  printf(" Last Insert ID : %d \n",id );

  mysql_close(conn);
  exit(0);

}
