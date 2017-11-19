#ifndef YAGA_GIT_TREE_ENTRY_H
#define YAGA_GIT_TREE_ENTRY_H

#include <string>

#include <git2.h>

#include "types.h"

namespace yaga_git
{
    struct tree_entry
    {
        static tree_entry from_raw(const git_tree_entry* raw_tree_entry);

        tree_entry(
            const std::string& name,
            const object_type& type,
            const filemode& mode);

        const filemode& mode() const;
        const std::string& name() const;
        const object_type& type() const;

      private:
        filemode mode_;
        std::string name_;
        object_type type_;

        tree_entry(const git_tree_entry* raw_tree_entry);
    };
}

#endif
