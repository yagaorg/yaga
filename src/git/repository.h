#ifndef YAGA_GIT_REPOSITORY_H
#define YAGA_GIT_REPOSITORY_H

#include <memory>
#include <string>

#include <git2.h>
#include <outcome.hpp>

#include "error.h"
#include "revwalk.h"

namespace outcome = OUTCOME_V2_NAMESPACE;

namespace yaga {
namespace git {

struct clone_options {
  private:
};

struct repository {
    static outcome::result<repository, error> open(const std::string& path);
    static outcome::result<repository, error> open_bare(const std::string& path);
    static outcome::result<repository, error> clone(const std::string& url,
                                                    const std::string& path);

    git_repository* raw();
    git_repository* raw() const;

    outcome::result<revwalk, error> create_revwalk();

  private:
    explicit repository(git_repository* repo_raw);
    std::unique_ptr<git_repository, decltype(&git_repository_free)> repo;
};

}  // namespace git
}  // namespace yaga

#endif
