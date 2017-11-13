#pragma once

#include <memory>

#include <git2.h>
#include <gsl/gsl>

namespace yaga {
namespace git {

struct repository;
struct revwalk {
    explicit revwalk(repository& repo);
    void push_range(gsl::cstring_span<> range);
    bool next(git_oid& oid);
private:
    std::unique_ptr<git_revwalk, decltype(&git_revwalk_free)> walk;
};

}
}
