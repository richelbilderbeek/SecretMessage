#ifndef SECRETMESSAGEMENUDIALOG_H
#define SECRETMESSAGEMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"

namespace ribi {
namespace sema {

struct MenuDialog final : public ::ribi::MenuDialog
{
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace sema
} //~namespace ribi

#endif // SECRETMESSAGEMENUDIALOG_H
