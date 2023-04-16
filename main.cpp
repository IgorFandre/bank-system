#include "Executable/Executable.h"
#include "Filesystem/Filesystem.h"

int main() {
  //Bank::SetWorkerIdCNT(0); // Лучше считывать с файла, потому что у нас уже будут сохраненные worker с этими ай-ди

  // need to define static const std::string in Request.h

  Filesystem::CheckDirectory("Data");

  //DateSetter::SetDate();
  //DateSetter::SaveDate();

  Executable exe = Executable();
  exe.Start();

  //Bank* b(new Bank("aba", -100, 10, 10));

  //JsonDBBanks db;
  //db.WriteBank(*b);
  //std::cout << db.GetBanks().size();
  //delete b;
  //DepositAccount* new_acc = new DepositAccount(100, 1, Date(10, 0, 0));
  //CreditAccount* new_acc2 = new CreditAccount(1, 12, -100, 12, Date(), Date());
  //std::unique_ptr<DataBaseAccounts> accs(dynamic_cast<DataBaseAccounts*>(new JsonDBAccounts()));
  //accs->WriteAccount("abc", 5, new_acc2);
  //std::vector<Account*> acc = accs->GetUserAccounts("abc", 5);
  //std::cout << 1;
  //accs->DeleteClientAccounts("abc", 1);
  //Request r("aba", 123, "it is fucking shit.");
  //r.WriteRequest();
  //std::cout << Request::ReadLastRequest("aba").text << std::endl;

}
