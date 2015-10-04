/*
 * cmdlineoptions.cpp
 *
 *  Created on: 04. Okt. 2015
 *      Author: qwc
 */

#include "CmdLineOptions.h"

namespace cmdlineoptions {

CmdLineOptions::~CmdLineOptions() {}

const std::unique_ptr<CmdLineOptions> &CmdLineOptions::i() {
  if (!instance) {
    instance = std::unique_ptr<CmdLineOptions>(new CmdLineOptions());
  }
  return instance;
}

std::shared_ptr<Option> CmdLineOptions::create(std::string &name) {
  std::shared_ptr<Option> option = std::make_shared<Option>(name);
  this->options.insert(std::make_pair(name, option));
  return option;
}

std::shared_ptr<Option> CmdLineOptions::getOption(std::string &name) {
  return this->options.at(name);
}

void CmdLineOptions::setCommandCharacter(char &cmdchar) {
  this->cmdchar = cmdchar;
}

void CmdLineOptions::parse(char **argv, int argc) {}

void CmdLineOptions::parse(std::list<std::string> argv) {}

CmdLineOptions::CmdLineOptions() {}

} /* namespace cmdlineoptions */
