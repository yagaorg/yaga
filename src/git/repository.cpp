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
            return error::from_last_error(error);

        return repository(repo_raw);
    }

    outcome::result<repository, error>
    repository::clone(const std::string& url, const std::string& path, clone_options& options)
    {
        init();
        git_repository* repo_raw = nullptr;
        git_clone_options opts = options.build();
        int error = git_clone(&repo_raw, url.data(), path.data(), &opts);
        if (error < 0)
            return error::from_last_error(error);

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

    outcome::result<commit, error> repository::lookup_commit(oid oid)
    {
        git_commit* raw_commit;

        int error = git_commit_lookup(&raw_commit, repo_.get(), &oid.raw());
        if (error < 0)
            return error::from_last_error(error);

        return commit::from_raw(raw_commit);
    }

    create_repository_state::create_repository_state(const char* path_raw, int is_bare)
        : path(path_raw), bare(is_bare)
    {
    }

    clone_options& clone_options::checkout(const checkout_options& options)
    {
        checkout_options_ = options;
        return *this;
    }

    clone_options& clone_options::fetch(const fetch_options& fetch)
    {
        fetch_options_ = fetch;
        return *this;
    }

    clone_options& clone_options::bare(bool is_bare)
    {
        bare_ = is_bare;
        return *this;
    }

    clone_options& clone_options::local(clone_local local_option)
    {
        local_ = local_option;
        return *this;
    }

    clone_options& clone_options::branch(const std::string& branch_name)
    {
        branch_ = branch_name;
        return *this;
    }

    git_clone_options clone_options::build()
    {
        git_clone_options options = GIT_CLONE_OPTIONS_INIT;

        if (checkout_options_)
            options.checkout_opts = checkout_options_.value().build();

        if (fetch_options_)
            options.fetch_opts = fetch_options_.value().build();

        if (bare_)
            options.bare = bare_.value();

        if (local_)
            options.local = static_cast<git_clone_local_t>(local_.value());

        if (branch_)
            options.checkout_branch = branch_.value().data();

        return options;
    }
}
