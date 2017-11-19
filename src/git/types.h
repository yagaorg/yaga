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

    enum class object_type
    {
        // Object can be any of the following.
        any = GIT_OBJ_ANY,
        // Object is invalid.
        bad = GIT_OBJ_BAD,
        // Reserved for future use.
        ext1 = GIT_OBJ__EXT1,
        // A commit object.
        commit = GIT_OBJ_COMMIT,
        // A tree (directory listing) object.
        tree = GIT_OBJ_TREE,
        // A file revision object.
        blob = GIT_OBJ_BLOB,
        // An annotated tag object.
        tag = GIT_OBJ_TAG,
        // Reserved for future use.
        ext2 = GIT_OBJ__EXT2,
        // A delta, base is given by an offset.
        ofs_delta = GIT_OBJ_OFS_DELTA,
        // A delta, base is given by object id.
        ref_delta = GIT_OBJ_REF_DELTA
    };

    struct time_with_offset
    {
        time_with_offset(time_t new_time, int new_offset) : time(new_time), offset(new_offset) {}
        time_t time;
        int offset;
    };
}

#endif
