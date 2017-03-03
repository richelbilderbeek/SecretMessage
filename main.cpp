#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "secretmessagemaindialog.h"
#include "secretmessagemenudialog.h"

#pragma GCC diagnostic pop

int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::sema::MenuDialog().Execute(args);
}
