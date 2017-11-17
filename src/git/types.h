#ifndef YAGA_GIT_TYPES_H
#define YAGA_GIT_TYPES_H

#include <git2.h>

namespace yaga {
namespace git {

enum class filemode {
    unreadable = GIT_FILEMODE_UNREADABLE,
    tree = GIT_FILEMODE_TREE,
    blob = GIT_FILEMODE_BLOB,
    executable = GIT_FILEMODE_BLOB_EXECUTABLE,
    link = GIT_FILEMODE_LINK,
    commit = GIT_FILEMODE_COMMIT
};
}
}  // namespace yaga

#endif
