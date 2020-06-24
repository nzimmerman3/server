#ifndef MEME_GEN_BACKEND_H
#define MEME_GEN_BACKEND_H

#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <map>

#include "meme.h"
#include "meme_gen_database.h"

class meme_gen_backend {
  public:
    meme_gen_backend();
    
    void populate_map();
    //takes a meme given by user without a valid id and adds it to database with a valid id
    //adds the id number to meme object
    void create_meme(meme& m);
    std::shared_ptr<meme> get_meme(int id);
    std::vector<std::shared_ptr<meme>> get_all_memes();
    void vote_meme(int id);
    void delete_meme(int id);
    void init_database();
    bool is_valid_id(int id);
    std::tuple<int, int> get_random_ids();
    std::vector<std::string> image_options();
    std::string image_to_uri(std::string image);
    meme parse_create_submission(std::string form);
    int parse_vote_submission(std::string form);

  private:
    std::string form_find(std::string form, std::string field);

    int gen_id();
    int id_next_;
    meme_gen_database db_;
    std::mutex id_lock_;
    std::vector<int> valid_ids_;
    std::map<std::string, std::string> image_uri_map_;
};


#endif // MEME_GEN_BACKEND_H