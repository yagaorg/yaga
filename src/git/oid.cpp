#include "oid.h"

#include "init.h"

namespace yaga_git
{
    outcome::result<oid, error> oid::from_string(const std::string& str)
    {
        init();
        git_oid oid_raw;
        int error = git_oid_fromstr(&oid_raw, str.data());

        if (error < 0)
            return error::from_last_error(error);

        return oid(std::move(oid_raw));
    }

    oid::oid(const git_oid& raw) : oid_raw(raw) {}

    oid::oid(git_oid&& raw) : oid_raw(raw) {}

    git_oid& oid::raw()
    {
        return oid_raw;
    }

    const git_oid& oid::raw() const
    {
        return oid_raw;
    }
}
