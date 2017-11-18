#include "revwalk.h"

#include "error.h"
#include "init.h"
#include "oid.h"
#include "repository.h"

namespace yaga_git
{
    outcome::result<revwalk, error> revwalk::from_repository(repository& repository)
    {
        init();
        git_revwalk* revwalk_raw;
        int error = git_revwalk_new(&revwalk_raw, repository.raw());
        if (error)
        {
            return error::from_last_error(error);
        }
        return revwalk(revwalk_raw);
    }

    revwalk::revwalk(git_revwalk* raw) : walk_(raw, git_revwalk_free) {}

    bool revwalk::next(oid& oid)
    {
        return !git_revwalk_next(&oid.raw(), walk_.get());
    }

    void revwalk::push_range(const std::string& range)
    {
        git_revwalk_push_range(walk_.get(), range.data());
    }
}
