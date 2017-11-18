#ifndef YAGA_GIT_TYPES_H
#define YAGA_GIT_TYPES_H

#include <git2.h>

namespace yaga_git
{
    enum class filemode
    {
        unreadable = GIT_FILEMODE_UNREADABLE,
        tree = GIT_FILEMODE_TREE,
        blob = GIT_FILEMODE_BLOB,
        executable = GIT_FILEMODE_BLOB_EXECUTABLE,
        link = GIT_FILEMODE_LINK,
        commit = GIT_FILEMODE_COMMIT
    };

    struct time_with_offset
    {
        time_with_offset(time_t new_time, int new_offset) : time(new_time), offset(new_offset) {}
        time_t time;
        int offset;
    };
}

#endif
