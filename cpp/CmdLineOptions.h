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
  // lists for attributes of an option
  std::unique_ptr<std::list<std::string>> options;
  std::unique_ptr<std::list<std::string>> possibleParameters;
  std::unique_ptr<std::list<std::string>> defaultParameters;
  // values, this list can only be filled by parsing the input data
  std::unique_ptr<std::list<std::string>> values;

public:
  Option();
  Option(std::string name);
  virtual ~Option();

  // Methods setting configuration attributes
  std::shared_ptr<Option> setName(std::string name);
  std::shared_ptr<Option> addCommand(std::string cmd);
  std::shared_ptr<Option> addPossibleParameter(std::string param);
  std::shared_ptr<Option> addDefaultParameter(std::string param);
  std::shared_ptr<Option> setStrictChoice(bool strict);

  // Methods for retrieving information in different formats
  std::shared_ptr<std::list<std::string>> getValues();
  std::string getValueAsString(uint index);
  uint getValueCount();
  int getValueAsInteger(uint index);
  double getValueAsDouble(uint index);
  float getValueAsFloat(uint index);
};

class CmdLineOptions {

public:
  virtual ~CmdLineOptions();
  static std::unique_ptr<CmdLineOptions> i();
  std::shared_ptr<Option> create(std::string name);
  std::shared_ptr<Option> getOption(std::string name);
  void setCommandCharacter(char cmdchar);

  void parse(char** argv, int argc);
  void parse(std::list<std::string> argv);

private:
  char cmdchar;
  CmdLineOptions();
  static std::unique_ptr<CmdLineOptions> instance;
};

} /* namespace cmdlineoptions */

#endif /* CMDLINEOPTIONS_H_ */
