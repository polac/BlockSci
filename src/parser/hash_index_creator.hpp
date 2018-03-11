//
//  hash_index_creator.hpp
//  blocksci
//
//  Created by Harry Kalodner on 8/26/17.
//
//

#ifndef hash_index_creator_hpp
#define hash_index_creator_hpp

#include "parser_index.hpp"
#include "parser_fwd.hpp"

#include <blocksci/chain/chain_fwd.hpp>
#include <blocksci/index/hash_index.hpp>

#include <tuple>

namespace blocksci {
    class uint256;
}

class HashIndexCreator;

template<blocksci::EquivAddressType::Enum type>
struct ParserIndexScriptInfo<HashIndexCreator, type> : std::false_type {};

class HashIndexCreator : public ParserIndex<HashIndexCreator> {
    blocksci::HashIndex db;
public:
    
    HashIndexCreator(const ParserConfigurationBase &config, const std::string &path);
    void processTx(const blocksci::Transaction &tx, const blocksci::ScriptAccess &scripts);
    
    template<blocksci::EquivAddressType::Enum type>
    void processScript(uint32_t equivNum, const blocksci::ChainAccess &, const blocksci::ScriptAccess &);
    
    void rollback(const blocksci::State &state);
    void tearDown() override {}
};

#endif /* hash_index_creator_hpp */
