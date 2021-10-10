#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include "main_imports.hpp"
#include "number_generator.hpp"
#include "hash.hpp"
#include "user.hpp"
#include "transaction.hpp"

BlockchainUser generate_user(string name);
BlockchainTransaction generate_transaction(BlockchainUser &sender, BlockchainUser &recipient);


#endif