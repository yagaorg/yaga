#include "revwalk.h"

#include "misc.h"
#include "oid.h"
#include "repository.h"

namespace yaga {
namespace git {

revwalk::revwalk(repository& repository) : walk(nullptr, git_revwalk_free) {
    init();
    git_revwalk* revwalk_raw;
    git_revwalk_new(&revwalk_raw, repository.raw());
    walk.reset(revwalk_raw);
}

bool revwalk::next(oid& oid) {
    return !git_revwalk_next(&oid.raw(), walk.get());
}

void revwalk::push_range(gsl::cstring_span<> range) {
    git_revwalk_push_range(walk.get(), gsl::ensure_z(range).data());
}

}  // namespace git
}  // namespace yaga
