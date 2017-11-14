#include "repository.h"

#include "misc.h"

namespace yaga {
namespace git {

repository::repository(git_repository* repo_raw) : repo(repo_raw, git_repository_free) {}

outcome::result<repository, error> repository::open(gsl::cstring_span<> path) {
    init();
    git_repository* repo_raw = nullptr;
    int e = git_repository_open(&repo_raw, gsl::ensure_z(path).data());
    if (e < 0) {
        return error::from_last_error(e);
    }

    return repository(repo_raw);
}

outcome::result<repository, error> repository::open_bare(gsl::cstring_span<> path) {
    init();
    git_repository* repo_raw = nullptr;
    int e = git_repository_open_bare(&repo_raw, gsl::ensure_z(path).data());
    if (e < 0) {
        return error::from_last_error(e);
    }

    return repository(repo_raw);
}

git_repository* repository::raw() {
    return repo.get();
}

git_repository* repository::raw() const {
    return repo.get();
}

outcome::result<revwalk, error> repository::create_revwalk() {
    return revwalk::from_repository(*this);
}

}  // namespace git
}  // namespace yaga
