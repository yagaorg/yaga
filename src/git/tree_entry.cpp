#include "tree_entry.h"

namespace yaga_git
{
    tree_entry::tree_entry(const git_tree_entry* raw_tree_entry)
        : mode_(static_cast<filemode>(git_tree_entry_filemode(raw_tree_entry))),
          name_(git_tree_entry_name(raw_tree_entry)),
          raw_tree_entry_(nullptr, nullptr),
          type_(static_cast<object_type>(git_tree_entry_type(raw_tree_entry)))
    {
    }

    tree_entry::tree_entry(git_tree_entry* raw_tree_entry)
        : mode_(static_cast<filemode>(git_tree_entry_filemode(raw_tree_entry))),
          name_(git_tree_entry_name(raw_tree_entry)),
          raw_tree_entry_(raw_tree_entry, git_tree_entry_free),
          type_(static_cast<object_type>(git_tree_entry_type(raw_tree_entry)))
    {
    }

    const filemode& tree_entry::mode() const
    {
        return mode_;
    }

    const stx::string_view& tree_entry::name() const
    {
        return name_;
    }

    const object_type& tree_entry::type() const
    {
        return type_;
    }
}
