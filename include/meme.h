#ifndef MEME_H
#define MEME_H

struct meme
{
  meme() {}
  meme(int id, std::string title, std::string top_text, std::string bottom_text, std::string image_choice, int votes) {
    id_ = id;
    title_ = title;
    top_text_ = top_text;
    bottom_text_ = bottom_text;
    image_choice_ = image_choice;
    votes_ = votes;
  }
  int id_;
  std::string title_;
  std::string top_text_;
  std::string bottom_text_;
  std::string image_choice_;
  int votes_;
};

#endif // MEME_H