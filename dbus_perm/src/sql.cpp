#include "sql.h"

sqlite3 *openOrCreateDB(sqlite3 *db) {
  char *errMsg = nullptr;

  int rc = sqlite3_open("permissions.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return NULL;
  }

  const char *createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS permissions (
            id INTEGER PRIMARY KEY,
            permission INTEGER NOT NULL,
            path TEXT NOT NULL
        );
    )";

  rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQLite error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    sqlite3_close(db);
    return NULL;
  }

  return db;
}
int writeRecordToDB(int permission, std::string path) {

  sqlite3 *db = openOrCreateDB(db);
  if (db == NULL)
    return 1;

  const char *insertSQL =
      "INSERT INTO permissions (permission, path) VALUES (?, ?);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db)
              << std::endl;
    sqlite3_close(db);
    return rc;
  }

  sqlite3_bind_int(stmt, 1, permission);
  sqlite3_bind_text(stmt, 2, path.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "Failed to add record to db: " << sqlite3_errmsg(db)
              << std::endl;
  } else {
    std::cout << "Record added to db!" << std::endl;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return 0;
}