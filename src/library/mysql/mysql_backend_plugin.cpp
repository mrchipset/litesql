#include "litesql/backend.hpp"
#include "mysql.hpp"

using namespace litesql;

extern "C" __declspec(dllexport) Backend* createBackend(const std::string& parameter)
{
  Backend* pBackend = nullptr;
  try {
    pBackend = new MySQL(parameter);
  } catch(const DatabaseError& /*ex*/) {
    pBackend = nullptr;
  }
  return pBackend;
}

extern "C" __declspec(dllexport) void deleteBackend(Backend* backend)
{
  if (backend)
  {
    delete backend;
  }
}
