#ifndef YAGA_GIT_TREE_H
#define YAGA_GIT_TREE_H

#include <string>

#include <git2.h>
#include <outcome.hpp>

#include "error.h"
#include "tree_entry.h"

namespace outcome = OUTCOME_V2_NAMESPACE;

namespace yaga_git
{
    struct tree
    {
        tree(git_tree* raw_tree);

        git_tree& raw();
        const git_tree& raw() const;

        tree_entry entry_by_index(int index) const;
        outcome::result<tree_entry, error> entry_by_path(const std::string& path) const;

      private:
        git_tree* raw_tree_;
    };
}

#endif
