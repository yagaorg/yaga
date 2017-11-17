#ifndef YAGA_GIT_REVWALK_H
#define YAGA_GIT_REVWALK_H

#include <memory>
#include <string>

#include <git2.h>
#include <outcome.hpp>

#include "error.h"

namespace outcome = OUTCOME_V2_NAMESPACE;

namespace yaga_git
{
    struct oid;
    struct repository;

    struct revwalk
    {
        static outcome::result<revwalk, error> from_repository(repository& repo);

        void push_range(const std::string& range);
        bool next(oid& oid);

      private:
        revwalk(git_revwalk* raw);
        std::unique_ptr<git_revwalk, decltype(&git_revwalk_free)> walk;
    };
}

#endif
