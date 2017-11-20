#ifndef YAGA_GIT_REPOSITORY_H
#define YAGA_GIT_REPOSITORY_H

#include <functional>
#include <memory>
#include <string>

#include <git2.h>
#include <outcome.hpp>
#include <stx/optional.hpp>

#include "checkout.h"
#include "commit.h"
#include "error.h"
#include "remote.h"
#include "revwalk.h"

namespace outcome = OUTCOME_V2_NAMESPACE;

namespace yaga_git
{
    struct clone_options;

    struct repository
    {
        static outcome::result<repository, error> open(const std::string& path);
        static outcome::result<repository, error> open_bare(const std::string& path);

        static outcome::result<repository, error> clone(
            const std::string& url,
            const std::string& path);

        static outcome::result<repository, error>
        clone(const std::string& url, const std::string& path, clone_options& options);

        git_repository* raw();
        git_repository* raw() const;

        outcome::result<revwalk, error> create_revwalk();
        outcome::result<commit, error> lookup_commit(oid oid);

      private:
        explicit repository(git_repository* repo_raw);
        std::unique_ptr<git_repository, decltype(&git_repository_free)> repo_;
    };

    struct create_repository_state
    {
        std::string path;
        bool bare;

        create_repository_state() = default;
        create_repository_state(const char* path_raw, int is_bare);
    };

    using create_repository_callback = std::function<int(create_repository_state&&)>;

    enum class clone_local
    {
        automatic = GIT_CLONE_LOCAL_AUTO,
        local = GIT_CLONE_LOCAL,
        no_local = GIT_CLONE_NO_LOCAL,
        local_no_links = GIT_CLONE_LOCAL_NO_LINKS
    };

    struct clone_options
    {
        clone_options& checkout(const checkout_options& options);
        clone_options& fetch(const fetch_options& fetch);
        clone_options& bare(bool is_bare);
        clone_options& local(clone_local local_option);
        clone_options& branch(const std::string& branch_name);

        template <typename T>
        clone_options& repository_callback(const T& callback);

        git_clone_options build();

      private:
        // TODO(gustorn): Add create remote callback
        stx::optional<checkout_options> checkout_options_;
        stx::optional<fetch_options> fetch_options_;
        stx::optional<bool> bare_;
        stx::optional<clone_local> local_;
        stx::optional<std::string> branch_;
        stx::optional<create_repository_callback> repository_callback_;
    };

    template <typename T>
    clone_options& clone_options::repository_callback(const T& callback)
    {
        repository_callback_ = callback;
        return *this;
    }
}

#endif
