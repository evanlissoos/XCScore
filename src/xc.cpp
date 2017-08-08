/**
  * @file xc.cpp
  * Implementation of the XC set of class for the XC scoring library
  *
  * @author:  Evan Lissoos
  * @date Created:  12/22/16
  */

#include "xc.h"

//Function used in std::sort to compare Runner ptrs
bool comp_runners(Runner* a, Runner* b)
{
  return (*a < *b);
}

//Function to convert a float representing time in seconds to a std::string
inline std::string floatToTime(float time_in)
{
  int min = (int) time_in/60;
  int sec = (int) time_in - (min*60);
  float msec = time_in - ((min*60) + sec);
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3) << msec;
  return std::to_string(min) + ":" + std::to_string(sec) + ss.str().substr(1);
}

//XCRace::Runner implementations
Runner::Runner(std::string n, float tr, int ti)
{
  name = n;
  time_run = tr;
  team_id = ti;
}

bool Runner::operator<(const Runner& other) const
{
  return time_run < other.time_run;
}


//XCRace::team implementations
Team::Team(std::string n)
{
  name = n;
}

bool Team::operator<(const Team& other) const
{
  if(!is_eligable() || !other.is_eligable())
  {
    if(!is_eligable() && !other.is_eligable())
      return true;
    if(!is_eligable())
      return false;
    return true;
  }

  if(score == other.score)
  {
    int score_tie, score_tie_other;
    if(team_runners.size() == 5 || team_runners.size() == 5)
    {
      score_tie = score - team_runners[4]->ind_score;
      score_tie_other = other.score - other.team_runners[4]->ind_score;
    }
    else
    {
      score_tie = score + team_runners[5]->ind_score;
      score_tie_other = other.score + other.team_runners[5]->ind_score;
    }
    return score_tie < score_tie_other;
  }

  return score < other.score;
}

bool Team::is_eligable() const
{
  return team_runners.size() >= 5;
}

void Team::score_team()
{
  if(!is_eligable())
    score = -1;
  else
  {
    score = 0;
    for(int i = 0; i < 5; i++)
      score += team_runners[i]->ind_score;
  }
}

//XCRace implementations
XCRace::XCRace()
{
  id_gen = 0;
}

XCRace::~XCRace()
{
  for(unsigned int i = 0; i < runners.size(); i++)
    delete runners[i];
}

void XCRace::add_runner(std::string n, std::string sn, int tr)
{
  if(school_id.find(sn) == school_id.end())
  {
    school_id.emplace(sn, id_gen);
    school_id_rev.emplace(id_gen,sn);
    teams.push_back(Team(sn));
    id_gen++;
  }

  runners.push_back(new Runner(n, tr, school_id[sn]));
}

void XCRace::score_race()
{
  sort_race();

  std::map<int, int> team_place;

  for(unsigned int i = 0; i < runners.size(); i++)
  {
    //Adding the runner to their respective team in order
    teams[runners[i]->team_id].team_runners.push_back(runners[i]);

    //Calculating team place for the runner
    if(team_place.find(runners[i]->team_id) == team_place.end())
      team_place.emplace(runners[i]->team_id, 0);
    team_place[runners[i]->team_id] = team_place[runners[i]->team_id]+1;
    runners[i]->team_place = team_place[runners[i]->team_id];
  }

  //Have to do this in a seperate loop so we know if teams are valid or not
  for(unsigned int i = 0; i < runners.size(); i++)
    runners[i]->ind_score = score_runner(runners[i]);

  for(unsigned int i = 0; i < teams.size(); i++)
    teams[i].score_team();

  sort_teams();
}

void XCRace::print_race()
{
  for(unsigned int i = 0; i < teams.size(); i++)
  {
    if(teams[i].score > 0)
      std::cout << i+1 << ". " << teams[i].name << " : " << teams[i].score << std::endl;
    else
      std::cout << "   " << teams[i].name << std::endl;
  }
}

void XCRace::write_race(std::string file_name)
{
  std::ofstream out_file;
  out_file.open(file_name);
  std::string place,team_score,run_score;

  out_file << "RACE RESULTS" << std::endl;
  for(unsigned int i = 0; i < runners.size(); i++)
  {
    out_file << i+1 << ".\t" << runners[i]->name << "\t" << school_id_rev[runners[i]->team_id]
    << "\t" << floatToTime(runners[i]->time_run) << std::endl;
  }
  out_file << std::endl;

  out_file << "TEAM RESULTS" << std::endl;
  for(unsigned int i = 0; i < teams.size(); i++)
  {
    if(teams[i].score > 0)
    {
      place = std::to_string(i+1) + ". ";
      team_score = std::to_string(teams[i].score);
    }

    else
    {
      place = "   ";
      team_score = " ";
    }

    out_file << place << teams[i].name << " " << team_score << std::endl;

    for(unsigned int j = 0; j < teams[i].team_runners.size(); j++)
    {
      if(j == 5 || j == 6)
        run_score = "(" + std::to_string(teams[i].team_runners[j]->ind_score) + ")";
      else if(teams[i].team_runners[j]->ind_score > 0)
        run_score = std::to_string(teams[i].team_runners[j]->ind_score);
      else
        run_score = " ";

      out_file << "\t\t" << teams[i].team_runners[j]->name << "\t" << run_score << "\t" << floatToTime(teams[i].team_runners[j]->time_run) << std::endl;
    }
    out_file << std::endl;
  }

  out_file.close();
}

void XCRace::debug()
{
  for(unsigned int i = 0; i < teams.size(); i++)
  {
    for(unsigned int j = 0; j < teams[i].team_runners.size(); j++)
    {
      std::cout << teams[i].team_runners[j]->name << " " << teams[i].team_runners[j]->ind_score << std::endl;
    }
  }
}

void XCRace::sort_race()
{
  std::sort(runners.begin(), runners.end(), comp_runners);
}

void XCRace::sort_teams()
{
  std::sort(teams.begin(), teams.end());
}

int XCRace::score_runner(Runner* current_runner) const
{
  static int current_score = 1;

  if(!teams[current_runner->team_id].is_eligable() || current_runner->team_place > 7)
    return 0;

  current_score++;
  return (current_score-1);
}
