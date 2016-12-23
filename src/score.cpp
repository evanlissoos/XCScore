/**
  * @file main.cpp
  * Implementation example of the XC library
  *
  * @author:  Evan Lissoos
  * @date Created:  12/22/16
  */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

#include "xc.h"

float calculate_time(std::string str)
{
  int seg = 0;
  std::string min = "", sec = "", msec = ".";
  for(unsigned int i = 0; i < str.length(); i++)
  {
    switch(seg)
    {
      case 0  :   if(str[i] == ':')
                    seg++;
                  else
                    min += str[i];
                  break;
      case 1  :   if(str[i] == '.' || str[i] == ':')
                    seg++;
                  else
                    sec += str[i];
                  break;
      case 2  :   msec += str[i];
    }
  }
  try {return (int) stod(min)*60 + (int) stod(sec) + stod(msec);}
  catch (std::exception& e) {std::cout << "ERROR: Formatting of input file is incorrect" << std::endl; return -1.0;}
}

int main(int argc, char* argv[])
{
  //Checking if no arguments were passed
  if(argc == 1)
  {
    std::cout << "ERROR: No input file given as argument" << std::endl;
    return 0;
  }

  //Setting up file stream
  std::ifstream in_file;
  in_file.open(std::string(argv[1]), std::ifstream::in);

  //Checking if the file is valid
  if(!in_file.good())
  {
    std::cout << "ERROR: No such file '" << argv[1] << "' exists" << std::endl;
    return 0;
  }

  //Checking if want to output results to file
  bool should_output = false;
  std::string flag,out_file = "results.csv";
  if(argc >= 3)
  {
    flag = std::string(argv[2]);
    //If want to add more flags, can make a dictionary mapping flags to function pointers
    if(flag == "-o" || flag == "-O")
      should_output = true;
    else
    {
      std::cout << "ERROR: No valid option '" << flag << "' exists" << std::endl;
      return 0;
    }

    if(argc >= 4)
      out_file = std::string(argv[3]);
  }

  //Going through the file and setting up structures
  std::string name, school, time_run;  //std::strings to hold the values grabbed from the file
  XCRace race;
  float hold_time;

  while(in_file.good())
  {
    //Grab values on the current line
    getline(in_file, name, ',');
    getline(in_file, school, ',');
    getline(in_file, time_run);

    if(name == "")
      break;

    hold_time = calculate_time(time_run);
    if(hold_time == -1.0)
      return 0;

    //Add runner to the XCRace structure
    race.add_runner(name, school, hold_time);
  }

  race.score_race();
  race.print_race();
  if(should_output)
    race.write_race(out_file);

  return 0;
}
