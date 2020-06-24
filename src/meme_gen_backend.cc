#include "../include/meme_gen_backend.h"

#include <algorithm>
#include <random>

#include "../include/logger.h"

meme_gen_backend::meme_gen_backend() : id_next_(0), db_() {
  init_database();
  populate_map();
}

void meme_gen_backend::populate_map() {
  //not 100% sure this uri format is correct
  //TODO add more images when sure this works
  image_uri_map_ = {
    {"spongebob", "meme_images/spongebob.jpg"}
  };
}

void meme_gen_backend::create_meme(meme& m) {
  m.id_ = gen_id();
  m.votes_ = 0;
  db_.add_entry(m);
  valid_ids_.push_back(m.id_);
}

std::shared_ptr<meme> meme_gen_backend::get_meme(int id) {
  return db_.retreive_entry(id);
}

std::vector<std::shared_ptr<meme>> meme_gen_backend::get_all_memes() {
  return db_.retreive_all_entries();
}

void meme_gen_backend::vote_meme(int id) {
  db_.vote(id);
}

void meme_gen_backend::delete_meme(int id) {
  db_.delete_entry(id);
  valid_ids_.erase(std::remove(valid_ids_.begin(), valid_ids_.end(), id), valid_ids_.end());
}

int meme_gen_backend::gen_id() {
  int next;
  id_lock_.lock();
  next = id_next_;
  id_next_++;
  id_lock_.unlock();
  return next;
}

void meme_gen_backend::init_database() {
  db_.init_database();
}

bool meme_gen_backend::is_valid_id(int id) {
  return std::find(valid_ids_.begin(), valid_ids_.end(), id) != valid_ids_.end();
}

std::tuple<int, int> meme_gen_backend::get_random_ids() {
  if(valid_ids_.size() < 2) {
    return std::make_tuple(-1, -1);
  }
  else
  {
    int first = valid_ids_.at(rand() % valid_ids_.size());
    int second = first;
    while(second == first) {
      second = valid_ids_.at(rand() % valid_ids_.size());
    }   
    return std::make_tuple(first, second); 
  }
}

std::vector<std::string> meme_gen_backend::image_options() {
  std::vector<std::string> options;
  for(std::map<std::string, std::string>::iterator it = image_uri_map_.begin(); it != image_uri_map_.end(); ++it) {
    options.push_back(it->first);
  }
  return options;
}

std::string meme_gen_backend::image_to_uri(std::string image) {
  if (image_uri_map_.find(image) != image_uri_map_.end()) {
    return image_uri_map_[image];
  }
  else {
    return "";
  } 
}

meme meme_gen_backend::parse_create_submission(std::string form) {
  src::severity_logger_mt<logging::trivial::severity_level> slg;
  BOOST_LOG_SEV(slg, logging::trivial::info) << "Total Form Body:" << form;
  meme m;
  std::vector<std::string> fields = {"memetemplates=", "title=", "toptext=", "bottomtext="};

  //if form format has been checked
  m.image_choice_ = form_find(form, fields[0]);
  BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme image choice:" << m.image_choice_;
  m.title_ = form_find(form, fields[1]);
  BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme title:" << m.title_;
  m.top_text_ = form_find(form, fields[2]);
  BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme top text:" << m.top_text_;
  m.bottom_text_ = form_find(form, fields[3]);
  BOOST_LOG_SEV(slg, logging::trivial::info) << "Meme bottom text:" << m.bottom_text_;

  return m;
}

int meme_gen_backend::parse_vote_submission(std::string form) {
  //if form format has been checked
  return stoi(form.substr(3));
}


std::string meme_gen_backend::form_find(std::string form, std::string field) {
  int s_pos = form.find(field) + field.length();
  int e_pos = form.find("&", s_pos);
  return form.substr(s_pos, e_pos - s_pos);
}
