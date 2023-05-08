#include "Bank.h"

Bank::Bank(std::string &&bank_name,
           const BigInteger &cred_lim,
           const BigInteger &bank_fee,
           int dep_per,
           size_t acc_id,
           size_t cl_id,
           size_t w_id)
    : bank_name_{std::forward<std::string>(bank_name)}
    , credit_limit_{cred_lim}
    , bank_fee_{bank_fee}
    , deposit_percent_{dep_per}
    , account_id_{acc_id}
    , client_id_{cl_id}
    , worker_id_{w_id} {}

size_t Bank::GetAccountID() { return ++account_id_; }
size_t Bank::GetClientID() { return ++client_id_; }
size_t Bank::GetWorkerID() { return ++worker_id_; }