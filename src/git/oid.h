#ifndef YAGA_GIT_OID_H
#define YAGA_GIT_OID_H

#include <string>

#include <git2.h>
#include <outcome.hpp>

#include "error.h"

namespace outcome = OUTCOME_V2_NAMESPACE;

namespace yaga {
namespace git {

struct oid {
    static outcome::result<oid, error> from_string(const std::string& str);

    git_oid& raw();
    const git_oid& raw() const;

  private:
    constexpr oid(git_oid&& oid_raw);
    git_oid oid_raw;
};

}  // namespace git
}  // namespace yaga

#endif
