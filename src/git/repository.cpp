#include "repository.h"

#include "init.h"

namespace yaga_git
{
    repository::repository(git_repository* repo_raw) : repo_(repo_raw, git_repository_free) {}

    outcome::result<repository, error> repository::open(const std::string& path)
    {
        init();
        git_repository* repo_raw = nullptr;
        int error = git_repository_open(&repo_raw, path.data());
        if (error < 0)
        {
            return error::from_last_error(error);
        }

        return repository(repo_raw);
    }

    outcome::result<repository, error> repository::open_bare(const std::string& path)
    {
        init();
        git_repository* repo_raw = nullptr;
        int error = git_repository_open_bare(&repo_raw, path.data());
        if (error < 0)
        {
            return error::from_last_error(error);
        }

        return repository(repo_raw);
    }

    outcome::result<repository, error> repository::clone(
        const std::string& url,
        const std::string& path)
    {
        init();
        git_repository* repo_raw = nullptr;
        int error = git_clone(&repo_raw, url.data(), path.data(), nullptr);
        if (error < 0)
        {
            return error::from_last_error(error);
        }

        return repository(repo_raw);
    }

    git_repository* repository::raw()
    {
        return repo_.get();
    }

    git_repository* repository::raw() const
    {
        return repo_.get();
    }

    outcome::result<revwalk, error> repository::create_revwalk()
    {
        return revwalk::from_repository(*this);
    }

    commit repository::lookup_commit(oid oid)
    {
        git_commit *raw_commit;
        int error = git_commit_lookup(&raw_commit, repo_.get(), &oid.raw());
        return commit::from_raw(raw_commit);
    }
}
