/**
  * @file xc.h
  * Definition of the XC set of class for the XC scoring library
  *
  * @author:  Evan Lissoos
  * @date Created:  12/22/16
  */

#ifndef XC_H
#define XC_H

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>

class Runner
{
  public:
    std::string name;                                                           //Name of Runner
    float time_run;                                                             //Time in seconds run
    int team_id;                                                                //Team id
    int ind_score;                                                              //Score of the individual for their team
    int team_place;                                                             //Place on team

    Runner(std::string n, float tr, int ti);                                    //Constr to be used when parsing file
    bool operator<(const Runner& other) const;                                  //Operator to be used for sorting runners
};

class Team
{
  public:
    std::string name;                                                           //Name of team
    std::vector<Runner*> team_runners;                                          //List of runners on team
    int score;                                                                  //Team score

    Team(std::string n);                                                        //Constructor with num runners
    bool operator<(const Team& other) const;                                    //Operator to be used for sorting teams
    bool is_eligable() const;                                                   //Returns whether the team is able to be scored
    void score_team();                                                          //Scores the team
};

class XCRace
{
  public:
    XCRace();                                                                   //Constructor
    ~XCRace();                                                                  //Destructor
    void add_runner(std::string n, std::string sn, int tr);                     //Adds Runner to race and to the team
    void score_race();                                                          //Function that sorts race by time run
    void print_race();                                                          //Prints team results of the race
    void write_race(std::string file_name);                                     //Writes results to a file with the name given in the parameter
    void debug();                                                               //Function that is changed to debug the program at given points during excecution

  private:
    void sort_race();                                                           //Sorts the race's runners by time run
    void sort_teams();                                                          //Sorts the teams by official XC scoring
    int score_runner(Runner* current_runner) const;                             //Calculates the score for the runner at the given index

    std::vector<Runner*> runners;                                               //List of pointers to runners
    std::vector<Team> teams;                                                    //List of teams
    std::map<std::string, int> school_id;                                       //Mapping of school names to ids
    std::map<int, std::string> school_id_rev;                                   //Reverse mapping used for after the the teams have been sorted
    int id_gen;                                                                 //Int used to keep track and assign school ids
};

#endif  //XC_H
