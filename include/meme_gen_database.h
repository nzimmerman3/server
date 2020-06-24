#ifndef MEME_GEN_DATABASE_H
#define MEME_GEN_DATABASE_H

#include <memory>
#include <vector>
#include <boost/thread/shared_mutex.hpp>

#include "meme.h"
#include "sqlite3.h"
#include "logger.h"

class meme_gen_database {
    public:
        meme_gen_database();
        ~meme_gen_database();
        void init_database(); //sets up the database and creates a table for memes
        void add_entry(const meme& m);
        //void alter_entry(const meme& m);
        void vote(int id); //increments the vote count of a meme by 1
        void delete_entry(int id);
        std::shared_ptr<meme> retreive_entry(int id);
        std::vector<std::shared_ptr<meme>> retreive_all_entries();

    private:
        sqlite3* db;
        src::severity_logger_mt<logging::trivial::severity_level> slg;
        boost::shared_mutex mu;
};


#endif // MEME_GEN_DATABASE_H