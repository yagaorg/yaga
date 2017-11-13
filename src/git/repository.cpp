#include "repository.h"

#include "misc.h"

namespace yaga {
namespace git {

repository::repository(git_repository* repo)
    : repo(repo, git_repository_free) {}

repository repository::open(gsl::cstring_span<> path) {
    init();
    git_repository* repo = nullptr;
    git_repository_open(&repo, gsl::ensure_z(path).data());
    return repository(repo);
}

repository repository::open_bare(gsl::cstring_span<> path) {
    init();
    git_repository* repo = nullptr;
    git_repository_open_bare(&repo, gsl::ensure_z(path).data());
    return repository(repo);
}

git_repository* repository::raw() {
    return repo.get();
}

git_repository* repository::raw() const {
    return repo.get();
}

revwalk repository::revwalk() {
    return yaga::git::revwalk(*this);
}

}
}
