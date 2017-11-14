#include "revwalk.h"

#include "misc.h"
#include "repository.h"

namespace yaga {
namespace git {

revwalk::revwalk(repository& repo) : walk(nullptr, git_revwalk_free) {
    init();
    git_revwalk* revwalk;
    git_revwalk_new(&revwalk, repo.raw());
    this->walk =
        std::unique_ptr<git_revwalk, decltype(&git_revwalk_free)>(revwalk, git_revwalk_free);
}

bool revwalk::next(git_oid& oid) {
    return !git_revwalk_next(&oid, walk.get());
}

void revwalk::push_range(gsl::cstring_span<> range) {
    git_revwalk_push_range(walk.get(), gsl::ensure_z(range).data());
}

}  // namespace git
}  // namespace yaga
