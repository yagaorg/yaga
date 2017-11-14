#include "oid.h"

namespace yaga {
namespace git {

oid::oid(gsl::cstring_span<> str) {
    git_oid_fromstr(&oid_raw, gsl::ensure_z(str).data());
}

oid::oid(git_oid&& raw) : oid_raw(raw) {}

git_oid& oid::raw() {
    return oid_raw;
}

const git_oid& oid::raw() const {
    return oid_raw;
}

}  // namespace git
}  // namespace yaga
