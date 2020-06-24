#include "../include/meme_gen_frontend.h"

void meme_gen_frontend::init(std::shared_ptr<meme_gen_backend> backend)
{
  backend_ = backend;
}

std::string meme_gen_frontend::generate_vote_counted_page()
{
  std::string content = 
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
    "<meta content=\"text/html;charset=utf-8\" http-equiv=\"Content-Type\">"
    "<meta content=\"utf-8\" http-equiv=\"encoding\">"
    "<title>Vote Counted</title>"
    "<style>"
      "body {"
       "text-align: center;"
      "}"
    "</style>"
  "</head>" 
  "<body>"
    "<h1>Your vote has been counted</h1>"
  "</body>"
  "</html>";

  return content;
}

std::string meme_gen_frontend::generate_link_page(int id)
{
  std::string link = "http://www.hardreboot.cs130.org/meme/view-" + std::to_string(id);
  std::string content = 
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
    "<meta content=\"text/html;charset=utf-8\" http-equiv=\"Content-Type\">"
    "<meta content=\"utf-8\" http-equiv=\"encoding\">"
    "<title>Link to Meme</title>"
    "<style>"
      "body {"
       "text-align: center;"
      "}"
    "</style>"
  "</head>" 
  "<body>"
    "<h1>Link to Meme</h1>"
    "<h2>" 
    + link + 
    "</h2>"
  "</body>"
  "</html>";

  return content;

}

std::string meme_gen_frontend::generate_create_page()
{
  std::string options = "";
  auto image_options = backend_->image_options();
  for (auto option: image_options) {
    options += 
    "<option value=" + option + ">" 
      + option + 
    "</option>";
  }

  std::string memes = 
  "<select name=\"memetemplates\" form=\"createForm\">"
    + options +
  "</select>";

  std::string form = 
  "<form method=\"GET\" id=\"createForm\" action=\"meme/submission/\">"
    "<input type=\"text\" id=\"title\" name=\"title\" placeholder=\"Title...\"><br>"
    "<input type=\"text\" id=\"toptext\" name=\"toptext\" placeholder=\"Top text...\"><br>"
    "<input type=\"text\" id=\"bottomtext\" name=\"bottomtext\" placeholder=\"Bottom text...\"><br>"
    "<button type=\"submit\" name=\"action\" value=\"create\">Create</button>"
  "</form>";

  std::string content = 
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
    "<meta content=\"text/html;charset=utf-8\" http-equiv=\"Content-Type\">"
    "<meta content=\"utf-8\" http-equiv=\"encoding\">"
    "<title>Create Meme</title>"
    "<style>"
      "body {"
       "text-align: center;"
      "}"
    "</style>"
  "</head>" 
  "<body>"
    "<h1>Create Meme</h1>"
    + memes + form +
  "</body>"
  "</html>";

  return content;
}

std::string meme_gen_frontend::generate_single_meme_page(int id)
{
  src::severity_logger_mt<logging::trivial::severity_level> slg;
  //BOOST_LOG_SEV(slg, logging::trivial::info) << "";
  auto meme = backend_->get_meme(id);
  if (meme == nullptr) {
    return "";
  }

  std::string title = meme->title_;
  std::string src = backend_->image_to_uri(meme->image_choice_);

  std::string content = 
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
    "<meta content=\"text/html;charset=utf-8\" http-equiv=\"Content-Type\">"
    "<meta content=\"utf-8\" http-equiv=\"encoding\">"
    "<title>" + title + "</title>"
    "<style>"
      ".responsive-img {"
        "width: 100%;"
        "max-width: 400px;"
        "height: auto;"
      "}" 
      ".meme {"
        "position: relative;"
        "text-align: center;"
      "}"
      ".top {"
        "position: relative;"
        "top: 32px;"
        "color: white;"
      "}"
      ".bottom {"
        "position: relative;"
        "bottom: 32px;"
        "color: white;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<div class=\"meme\">"
      "<h1>" + title + "</h1>"
      "<div class=\"top\">" + meme->top_text_ + "</div>"
      "<img class=\"responsive-img\" src=" + src + ">"
      "<div class=\"bottom\">" + meme->bottom_text_ + "</div>"
    "</div>"
  "</body>"
  "</html>";

  return content;
}

std::string meme_gen_frontend::generate_leaderboard_page()
{
  std::string memes;
  for (auto meme: backend_->get_all_memes()) {
    std::string title = meme->title_;
    std::string src = backend_->image_to_uri(meme->image_choice_);
    std::string votes = std::to_string(meme->votes_);

    memes += 
    "<div class=\"meme\">"
      "<h3>" + title + "</h3>"
      "<img class=\"responsive-img\" src=" + src + ">"
      "<p>Votes: " + votes + "</p>"
    "</div>";
  }

  std::string content = 
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
    "<meta content=\"text/html;charset=utf-8\" http-equiv=\"Content-Type\">"
    "<meta content=\"utf-8\" http-equiv=\"encoding\">"
    "<title>Leaderboard</title>"
    "<style>"
      "body {"
        "text-align: center;"
      "}"

      ".responsive-img {"
        "width: 100%;"
        "max-width: 400px;"
        "height: auto;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<h1>Leaderboard</h1>"
    "<div class=\"leaderboard\">" + memes + "</div>"
  "</body>"
  "</html>";

  return content;
}

std::string meme_gen_frontend::generate_vote_page() {

  auto ids = backend_->get_random_ids();
  int firstId = std::get<0>(ids);
  int secondId = std::get<1>(ids);

  if (firstId == -1 || secondId == -1) {
    return "";
  }

  auto first = backend_->get_meme(firstId);
  auto second = backend_->get_meme(secondId);

  if (first == nullptr || second == nullptr) {
    return "";
  }

  std::string memes = 
  "<div class=\"memes\">"
    "<div class=\"meme\">"
      "<img class=\"responsive-img\" src=" + backend_->image_to_uri(first->image_choice_) + ">"
    "</div>"

   "<div class=\"meme\">"
      "<img class=\"responsive-img\" src=" + backend_->image_to_uri(second->image_choice_) + ">" 
    "</div>"
  "</div>";

  std::string form = 
  "<form method=\"GET\" action=\"meme/vote-submission/\">"
    + memes +
    "<button type=\"submit\" name=\"id\" value=" + std::to_string(firstId) + ">Left</button>"
    "<button type=\"submit\" name=\"id\" value=" + std::to_string(secondId) + ">Right</button>"
  "</form>";

  std::string content = 
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
    "<meta content=\"text/html;charset=utf-8\" http-equiv=\"Content-Type\">"
    "<meta content=\"utf-8\" http-equiv=\"encoding\">"
    "<title>Vote Memes</title>"
    "<style>"
      "body {"
        "text-align: center;"
      "}"

      ".memes {"
        "display: flex;"
        "flex-direction: row;"
        "justify-content: space-around;"
      "}"

      ".responsive-img {"
        "width: 100%;"
        "max-width: 400px;"
        "height: auto;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<h1>Choose the better Meme</h1>"
    + form +
  "</body>"
  "</html>";

  return content;
}
