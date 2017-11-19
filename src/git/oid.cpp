#include "oid.h"

#include "init.h"

using namespace std;

namespace yaga_git
{
    outcome::result<oid, error> oid::from_string(const string& str)
    {
        init();
        git_oid oid_raw;
        int error = git_oid_fromstr(&oid_raw, str.data());

        if (error < 0)
            return error::from_last_error(error);

        return oid(move(oid_raw));
    }

    oid::oid(const git_oid& raw) : oid_raw_(raw) {}

    oid::oid(git_oid&& raw) : oid_raw_(raw) {}

    git_oid& oid::raw()
    {
        return oid_raw_;
    }

    const git_oid& oid::raw() const
    {
        return oid_raw_;
    }

    string oid::to_string() const
    {
        auto *result = git_oid_tostr_s(&oid_raw_);
        return string(result);
    }
}
