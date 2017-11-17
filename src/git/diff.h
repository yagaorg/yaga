#ifndef YAGA_GIT_DIFF_H
#define YAGA_GIT_DIFF_H

#include <cstdint>

#include <git2.h>

#include "oid.h"
#include "types.h"

namespace yaga_git
{
    enum class diff_flag : uint32_t
    {
        binary = GIT_DIFF_FLAG_BINARY,
        not_binary = GIT_DIFF_FLAG_NOT_BINARY,
        valid_id = GIT_DIFF_FLAG_VALID_ID,
        exists = GIT_DIFF_FLAG_EXISTS
    };

    struct diff_file
    {
        oid id;
        std::string path;
        git_off_t size;
        diff_flag flags;
        filemode mode;
        std::uint16_t id_abbrev;

        diff_file() = default;
        diff_file(const git_diff_file* file);
    };

    diff_flag operator|(diff_flag a, diff_flag b);
    diff_flag operator&(diff_flag a, diff_flag b);
}

#endif
