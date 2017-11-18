#include "diff.h"

#include <type_traits>

namespace yaga_git
{
    diff_file::diff_file(const git_diff_file* file)
        : id(file->id),
          path(file->path),
          size(file->size),
          flags(static_cast<diff_flag>(file->flags)),
          mode(static_cast<filemode>(file->mode)),
          id_abbrev(file->id_abbrev)
    {
    }

    diff_flag operator|(diff_flag a, diff_flag b)
    {
        using int_type = std::underlying_type<diff_flag>::type;
        return static_cast<diff_flag>(static_cast<int_type>(a) | static_cast<int_type>(b));
    }

    diff_flag operator&(diff_flag a, diff_flag b)
    {
        using int_type = std::underlying_type<diff_flag>::type;
        return static_cast<diff_flag>(static_cast<int_type>(a) & static_cast<int_type>(b));
    }

}
