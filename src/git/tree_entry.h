#ifndef YAGA_GIT_TREE_ENTRY_H
#define YAGA_GIT_TREE_ENTRY_H

#include <functional>
#include <memory>

#include <git2.h>
#include <stx/string_view.hpp>

#include "types.h"

namespace yaga_git
{
    struct tree_entry
    {
        tree_entry(const git_tree_entry* raw_tree_entry);
        tree_entry(git_tree_entry* raw_tree_entry);

        const filemode& mode() const;
        const stx::string_view& name() const;
        const object_type& type() const;

      private:
        filemode mode_;
        stx::string_view name_;
        std::unique_ptr<git_tree_entry, decltype(&git_tree_entry_free)> raw_tree_entry_;
        object_type type_;
    };
}

#endif
