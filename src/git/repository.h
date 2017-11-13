#pragma once

#include <memory>
#include <string>

#include <git2.h>
#include <gsl/gsl>

#include "revwalk.h"

namespace yaga {
namespace git {

struct repository {
    static repository open(gsl::cstring_span<> path);
    static repository open_bare(gsl::cstring_span<> path);

    git_repository* raw();
    git_repository* raw() const;

    revwalk revwalk();

private:
    explicit repository(git_repository* repository);
    std::unique_ptr<git_repository, decltype(&git_repository_free)> repo;
};

}
}
