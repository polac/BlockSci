//
//  dedup_address_info.hpp
//  blocksci
//
//  Created by Harry Kalodner on 3/7/18.
//

#ifndef dedup_address_info_hpp
#define dedup_address_info_hpp

#include "address_fwd.hpp"
#include <blocksci/util/util.hpp>

namespace blocksci {
    template <>
    struct DedupAddressInfo<DedupAddressType::PUBKEY> {
        static constexpr char name[] = "pubkey_script";
        static constexpr bool deduped = true;
        static constexpr bool spendable = true;
        static constexpr bool indexed = false;
        static constexpr std::array<AddressType::Enum, 3> addressTypes = {{AddressType::PUBKEY, AddressType::PUBKEYHASH, AddressType::WITNESS_PUBKEYHASH}};
    };
    
    template <>
    struct DedupAddressInfo<DedupAddressType::SCRIPTHASH> {
        static constexpr char name[] = "scripthash_script";
        static constexpr bool deduped = true;
        static constexpr bool spendable = true;
        static constexpr bool indexed = false;
        static constexpr std::array<AddressType::Enum, 2> addressTypes = {{AddressType::SCRIPTHASH, AddressType::WITNESS_SCRIPTHASH}};
    };
    
    template <>
    struct DedupAddressInfo<DedupAddressType::MULTISIG> {
        static constexpr char name[] = "multisig_script";
        static constexpr bool deduped = true;
        static constexpr bool spendable = true;
        static constexpr bool indexed = true;
        static constexpr std::array<AddressType::Enum, 1> addressTypes = {{AddressType::MULTISIG}};
    };
    
    template <>
    struct DedupAddressInfo<DedupAddressType::NONSTANDARD> {
        static constexpr char name[] = "nonstandard_script";
        static constexpr bool deduped = false;
        static constexpr bool spendable = true;
        static constexpr bool indexed = true;
        static constexpr std::array<AddressType::Enum, 1> addressTypes = {{AddressType::NONSTANDARD}};
    };
    
    template <>
    struct DedupAddressInfo<DedupAddressType::NULL_DATA> {
        static constexpr char name[] = "null_data_script";
        static constexpr bool deduped = false;
        static constexpr bool spendable = false;
        static constexpr bool indexed = true;
        static constexpr std::array<AddressType::Enum, 1> addressTypes = {{AddressType::NULL_DATA}};
    };
    
    using DedupAddressInfoList = array_to_tuple_t<DedupAddressType::Enum, DedupAddressType::size, DedupAddressType::all>;
    
    template <template<DedupAddressType::Enum> class K>
    using to_dedup_address_tuple_t = apply_template_t<DedupAddressType::Enum, K, DedupAddressInfoList>;
    
    template<DedupAddressType::Enum type>
    struct SpendableFunctor {
        static constexpr bool f() {
            return DedupAddressInfo<type>::spendable;
        }
    };
    
    constexpr void scriptTypeCheckThrow(size_t index) {
        index >= DedupAddressType::size ? throw std::invalid_argument("combination of enum values is not valid") : 0;
    }
    
    static constexpr auto spendableTable = blocksci::make_static_table<DedupAddressType, SpendableFunctor>();
    
    constexpr bool isSpendable(DedupAddressType::Enum t) {
        auto index = static_cast<size_t>(t);
        scriptTypeCheckThrow(index);
        return spendableTable[index];
    }
    
    template<DedupAddressType::Enum type>
    struct DedupedFunctor {
        static constexpr bool f() {
            return DedupAddressInfo<type>::deduped;
        }
    };
    
    static constexpr auto dedupedTable = blocksci::make_static_table<DedupAddressType, DedupedFunctor>();
    
    constexpr bool isDeduped(DedupAddressType::Enum t) {
        auto index = static_cast<size_t>(t);
        scriptTypeCheckThrow(index);
        return dedupedTable[index];
    }
    
    std::string dedupAddressName(DedupAddressType::Enum type);
}

#endif /* dedup_address_info_hpp */
