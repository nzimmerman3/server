
//The following link was referenced for the sqlite implementation below:
//https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm


#include "../include/meme_gen_database.h"
// #include <boost/thread/locks.hpp>

meme_gen_database::meme_gen_database() {
  init_database();
}

meme_gen_database::~meme_gen_database() {
  sqlite3_close(db); //closes the connection to the database upon destruction of the server
}

void meme_gen_database::init_database()
{
  const char *sql;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open(NULL, &db);
  if (rc) {
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Can't open database. Error: " << sqlite3_errmsg(db);
    return;
  } else {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Opened database successfully";
  }

  sql = "CREATE TABLE MEME(" \
    "ID INT PRIMARY KEY NOT NULL," \
    "TITLE TEXT NOT NULL," \
    "TOP_TEXT TEXT NOT NULL," \
    "BOTTOM_TEXT TEXT NOT NULL," \
    "IMAGE_CHOICE TEXT NOT NULL," \
    "VOTES INT NOT NULL);"; //creates the database table to store all memes
  
  rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg); //executes the above command to create the meme table
  if (rc != SQLITE_OK) { //command successfully executed
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Can't create MEME table. SQL error: " << zErrMsg;
    sqlite3_free(zErrMsg);
  } else {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "MEME table created successfully";
  }
}

void meme_gen_database::add_entry(const meme& m)
{
  boost::unique_lock<boost::shared_mutex> lock(mu); //uses a unique lock for all writes to the database

  sqlite3_stmt* stmt;
  const char *sql;
  int rc;

  sql = "INSERT INTO MEME (ID,TITLE,TOP_TEXT,BOTTOM_TEXT,IMAGE_CHOICE,VOTES) " \
    "VALUES (?,?,?,?,?,?);"; //inserts the specified meme into the database

  sqlite3_prepare(db, sql, -1, &stmt, 0); //prepares the above command to fill in the ? values
  sqlite3_bind_int(stmt, 1, m.id_);
  sqlite3_bind_text(stmt, 2, m.title_.c_str(), m.title_.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, m.top_text_.c_str(), m.top_text_.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, m.bottom_text_.c_str(), m.bottom_text_.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, m.image_choice_.c_str(), m.image_choice_.length(), SQLITE_STATIC);
  sqlite3_bind_int(stmt, 6, m.votes_);

  rc = sqlite3_step(stmt); //executes the command with the filled in values

  if (rc != SQLITE_DONE) {
    BOOST_LOG_SEV(slg, logging::trivial::error) << "Meme with ID, " << m.id_ << ", inserted unsuccessfully";
  } else {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID, " << m.id_ << ", inserted successfully";
  }

  sqlite3_finalize(stmt);
}

void meme_gen_database::vote(int id) {
  boost::unique_lock<boost::shared_mutex> lock(mu); //write lock

  sqlite3_stmt* stmt1; //used for SELECT statement
  sqlite3_stmt* stmt2; //used for UPDATE statement
  const char *sql;
  int rc;
  int votes;

  sql = "SELECT VOTES FROM MEME WHERE ID = ?;"; //retrieves the vote count for the meme corresponding to id

  sqlite3_prepare(db, sql, -1, &stmt1, 0);
  sqlite3_bind_int(stmt1, 1, id);
  rc = sqlite3_step(stmt1);

  if(rc != SQLITE_ROW || !sqlite3_column_text(stmt1, 0)) { //the entry corresponding to id is not found
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " not found in the database";
  } else {  //the entry corresponding to id is found
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " found in the database";
    votes = sqlite3_column_int(stmt1, 0);
  }

  sqlite3_finalize(stmt1);


  sql = "UPDATE MEME SET VOTES = ? WHERE ID = ?;"; //updates the vote count of the meme corresponding to id 

  sqlite3_prepare(db, sql, -1, &stmt2, 0);
  sqlite3_bind_int(stmt2, 1, votes + 1); //increments the vote count
  sqlite3_bind_int(stmt2, 2, id);
  rc = sqlite3_step(stmt2);

  if(rc != SQLITE_DONE) {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " unsuccessfully voted on";
  } else {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " successfully voted on";
  }

  sqlite3_finalize(stmt2);
}

void meme_gen_database::delete_entry(int id) {
  boost::unique_lock<boost::shared_mutex> lock(mu); //write lock

  sqlite3_stmt* stmt;
  const char *sql;
  int rc;

  sql = "DELETE FROM MEME WHERE ID = ?;"; //deletes the meme entry corresponding to id

  sqlite3_prepare(db, sql, -1, &stmt, 0);
  sqlite3_bind_int(stmt, 1, id);
  rc = sqlite3_step(stmt);

  if(rc != SQLITE_DONE) {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " unsuccessfully removed from the database";
  } else {
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " successfully removed from the database";
  }

  sqlite3_finalize(stmt);
}

std::shared_ptr<meme> meme_gen_database::retreive_entry(int id)
{
  boost::shared_lock<boost::shared_mutex> lock(mu); //uses a shared lock for all reads from the database
  
  std::shared_ptr<meme> entry = nullptr;
  sqlite3_stmt* stmt;
  const char *sql;
  int rc;

  sql = "SELECT TITLE, TOP_TEXT, BOTTOM_TEXT, IMAGE_CHOICE, VOTES FROM MEME WHERE ID = ?;"; //retrieves the meme entry corresponding to id 

  sqlite3_prepare(db, sql, -1, &stmt, 0);
  sqlite3_bind_int(stmt, 1, id);
  rc = sqlite3_step(stmt);

  if(rc != SQLITE_ROW || !sqlite3_column_text(stmt, 0)) { //the entry corresponding to the id is not found
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " not found in the database";
  } else { //the entry corresponding to the id is found
    BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme with ID " << id << " found in the database";
    std::string title = std::string((char *) sqlite3_column_text(stmt, 0));
    std::string top_text = std::string((char *) sqlite3_column_text(stmt, 1));
    std::string bottom_text = std::string((char *) sqlite3_column_text(stmt, 2));
    std::string image_choice = std::string((char *) sqlite3_column_text(stmt, 3));
    int votes = sqlite3_column_int(stmt, 4);
    entry = std::shared_ptr<meme>(new meme(id, title, top_text, bottom_text, image_choice, votes)); //a meme is created for the corresponding id request
  }

  sqlite3_finalize(stmt);
  return entry;
}

std::vector<std::shared_ptr<meme>> meme_gen_database::retreive_all_entries()
{
  boost::shared_lock<boost::shared_mutex> lock(mu); //read lock
  
  std::vector<std::shared_ptr<meme>> entries;
  sqlite3_stmt* stmt;
  const char *sql;
  int rc;

  sql = "SELECT ID, TITLE, TOP_TEXT, BOTTOM_TEXT, IMAGE_CHOICE, VOTES FROM MEME ORDER BY VOTES DESC;"; //retreives each entry from the database in order of descending votes

  sqlite3_prepare(db, sql, -1, &stmt, 0);
  rc = sqlite3_step(stmt);
  
  while(rc == SQLITE_ROW && sqlite3_column_text(stmt, 0)) { //there is another entry in the set of memes we are iterating through
    int id = sqlite3_column_int(stmt, 0); 
    std::string title = std::string((char *) sqlite3_column_text(stmt, 1));
    std::string top_text = std::string((char *) sqlite3_column_text(stmt, 2));
    std::string bottom_text = std::string((char *) sqlite3_column_text(stmt, 3));
    std::string image_choice = std::string((char *) sqlite3_column_text(stmt, 4));
    int votes = sqlite3_column_int(stmt, 5);

    entries.push_back(std::shared_ptr<meme>(new meme(id, title, top_text, bottom_text, image_choice, votes))); //creates a meme corresponding to each entry in the database
    rc = sqlite3_step(stmt);
  }

  BOOST_LOG_SEV(slg, logging::trivial::info) << "Retrieving all entries from the database";
  sqlite3_finalize(stmt);
  return entries;
}