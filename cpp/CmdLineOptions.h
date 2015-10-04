/*
 * cmdlineoptions.h
 *
 *  Created on: 04. Okt. 2015
 *      Author: qwc
 */

#ifndef CMDLINEOPTIONS_H_
#define CMDLINEOPTIONS_H_
#include <memory>
#include <string>
#include <list>

namespace cmdlineoptions {

// using namespace std;

class CmdLineOptions;

class Option {
private:
  // important information
  std::string name;
  std::string description;
  bool set;
  // lists
  std::unique_ptr<std::list<std::string>> options;
  std::unique_ptr<std::list<std::string>> possibleParameters;
  std::unique_ptr<std::list<std::string>> defaultParameters;
  std::unique_ptr<std::list<std::string>> values;

public:
  Option();
  Option(std::string name);
  virtual ~Option();

  void setName(std::string name);

};

class CmdLineOptions {

public:
  virtual ~CmdLineOptions();
  static std::unique_ptr<CmdLineOptions> i();
  std::shared_ptr<Option> create(std::string name);
  std::shared_ptr<Option> getOption(std::string name);

private:
  CmdLineOptions();
  static std::unique_ptr<CmdLineOptions> instance;
};

} /* namespace cmdlineoptions */

#endif /* CMDLINEOPTIONS_H_ */
