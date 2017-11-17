#ifndef YAGA_GIT_MISC_H
#define YAGA_GIT_MISC_H

#include <git2.h>

namespace yaga_git
{
    struct libgit
    {
        libgit()
        {
            git_libgit2_init();
        }

        ~libgit()
        {
            git_libgit2_shutdown();
        }
    };

    inline void init()
    {
        static libgit git;
    }
}

#endif
