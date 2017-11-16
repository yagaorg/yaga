#include "oid.h"

#include "misc.h"

namespace yaga {
namespace git {

outcome::result<oid, error> oid::from_string(gsl::cstring_span<> str) {
    init();
    git_oid oid_raw;
    int error = git_oid_fromstr(&oid_raw, gsl::ensure_z(str).data());

    if (error < 0) {
        return error::from_last_error(error);
    }

    return oid(std::move(oid_raw));
}

constexpr oid::oid(git_oid&& raw) : oid_raw(raw) {}

git_oid& oid::raw() {
    return oid_raw;
}

const git_oid& oid::raw() const {
    return oid_raw;
}

}  // namespace git
}  // namespace yaga
