#pragma once

#include <memory>
#include <string>

#include <git2.h>
#include <gsl/gsl>

namespace yaga {
namespace git {

struct revwalk;
struct repository {
    static repository open(gsl::cstring_span<> path);
    static repository open_bare(gsl::cstring_span<> path);

    git_repository* raw();
    git_repository* raw() const;

    revwalk create_revwalk();

  private:
    explicit repository(git_repository* repository);
    std::unique_ptr<git_repository, decltype(&git_repository_free)> repo;
};

}  // namespace git
}  // namespace yaga
