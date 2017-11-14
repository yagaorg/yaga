#ifndef YAGA_GIT_REVWALK_H
#define YAGA_GIT_REVWALK_H

#include <memory>

#include <git2.h>
#include <gsl/gsl>

namespace yaga {
namespace git {

struct oid;
struct repository;

struct revwalk {
    explicit revwalk(repository& repo);
    void push_range(gsl::cstring_span<> range);
    bool next(oid& oid);

  private:
    std::unique_ptr<git_revwalk, decltype(&git_revwalk_free)> walk;
};

}  // namespace git
}  // namespace yaga

#endif
