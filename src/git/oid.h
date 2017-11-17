#ifndef YAGA_GIT_OID_H
#define YAGA_GIT_OID_H

#include <string>

#include <git2.h>
#include <outcome.hpp>

#include "error.h"

namespace outcome = OUTCOME_V2_NAMESPACE;

namespace yaga_git
{
    struct oid
    {
        oid() = default;
        oid(const git_oid& oid_raw);
        oid(git_oid&& oid_raw);
        static outcome::result<oid, error> from_string(const std::string& str);

        git_oid& raw();
        const git_oid& raw() const;

      private:
        git_oid oid_raw;
    };

}  // namespace yaga

#endif
