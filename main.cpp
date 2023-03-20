
#include "Bank/Bank.h"
#include "DataBases/VectorDBAccounts.h"
#include "DataBases/VectorDBClients.h"
#include "DataBases/VectorDBBanks.h"
#include "Executable.h"
#include "IOSystem/IOIostream.h"

int main() {
  //Bank::SetWorkerIdCNT(0); // Лучше считывать с файла, потому что у нас уже будут сохраненные worker с этими ай-ди

  DataBaseAccounts* accounts = new VectorDBAccounts();
  DataBaseBanks* banks = new VectorDBBanks();
  DataBaseClients* clients = new VectorDBClients();

  Show* out = new ConsoleShow();
  Get* in = new ConsoleGet();

  system_date = {0, 0, 1};

  Executable exe = Executable(out, in, accounts, banks, clients);
  exe.Start();

  delete accounts;
  delete banks;
  delete clients;
}
