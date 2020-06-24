#ifndef MEME_GEN_FRONTEND_H
#define MEME_GEN_FRONTEND_H

#include <string>
#include <vector>

#include "../libraries/boost-http/include/request.hpp"
#include "meme_gen_backend.h"

class meme_gen_frontend {
    public:
        void init(std::shared_ptr<meme_gen_backend> backend);
        std::string generate_vote_counted_page();
        std::string generate_link_page(int id);
        std::string generate_create_page();
        std::string generate_single_meme_page(int id); //will need to take some params
        std::string generate_leaderboard_page();
        std::string generate_vote_page();

    private:
    std::shared_ptr<meme_gen_backend> backend_;


};


#endif // MEME_GEN_FRONTEND_H