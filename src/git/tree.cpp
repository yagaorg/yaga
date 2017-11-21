#include "tree.h"

using namespace std;

namespace yaga_git
{
    tree::tree(git_tree* raw_tree) : raw_tree_(raw_tree)
    {
    }

    git_tree& tree::raw()
    {
        return *raw_tree_;
    }

    const git_tree& tree::raw() const
    {
        return *raw_tree_;
    }

    tree_entry tree::entry_by_index(int index) const
    {
        auto* raw_tree_entry = git_tree_entry_byindex(raw_tree_, index);

        return tree_entry(raw_tree_entry);
    }

    outcome::result<tree_entry, error> tree::entry_by_path(const std::string& path) const
    {
        git_tree_entry* raw_tree_entry;
        int error = git_tree_entry_bypath(&raw_tree_entry, raw_tree_, path.c_str());
        if (error < 0)
            return error::from_last_error(error);

        return tree_entry(raw_tree_entry);
    }
}
