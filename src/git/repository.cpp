#include "repository.h"

#include "misc.h"
#include "revwalk.h"

namespace yaga {
namespace git {

repository::repository(git_repository* repo_raw) : repo(repo_raw, git_repository_free) {}

repository repository::open(gsl::cstring_span<> path) {
    init();
    git_repository* repo_raw = nullptr;
    git_repository_open(&repo_raw, gsl::ensure_z(path).data());
    return repository(repo_raw);
}

repository repository::open_bare(gsl::cstring_span<> path) {
    init();
    git_repository* repo_raw = nullptr;
    git_repository_open_bare(&repo_raw, gsl::ensure_z(path).data());
    return repository(repo_raw);
}

git_repository* repository::raw() {
    return repo.get();
}

git_repository* repository::raw() const {
    return repo.get();
}

revwalk repository::create_revwalk() {
    return revwalk(*this);
}

}  // namespace git
}  // namespace yaga
