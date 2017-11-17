#ifndef YAGA_GIT_CHECKOUT_H
#define YAGA_GIT_CHECKOUT_H

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

#include <git2.h>
#include <stx/optional.hpp>

#include "diff.h"

namespace yaga_git
{
    enum class checkout_strategy
    {
        none = GIT_CHECKOUT_NONE,
        safe = GIT_CHECKOUT_SAFE,
        force = GIT_CHECKOUT_FORCE,
        recreate_missing = GIT_CHECKOUT_RECREATE_MISSING,
        allow_conflicts = GIT_CHECKOUT_ALLOW_CONFLICTS,
        remove_untracked = GIT_CHECKOUT_REMOVE_UNTRACKED,
        remove_ignored = GIT_CHECKOUT_REMOVE_IGNORED,
        update_only = GIT_CHECKOUT_UPDATE_ONLY,
        dont_update_index = GIT_CHECKOUT_DONT_UPDATE_INDEX,
        no_refresh = GIT_CHECKOUT_NO_REFRESH,
        skip_unmerged = GIT_CHECKOUT_SKIP_UNMERGED,
        use_ours = GIT_CHECKOUT_USE_OURS,
        use_theirs = GIT_CHECKOUT_USE_THEIRS,
        disable_pathspec_match = GIT_CHECKOUT_DISABLE_PATHSPEC_MATCH,
        skip_locked_directories = GIT_CHECKOUT_SKIP_LOCKED_DIRECTORIES,
        dont_overwrite_ignored = GIT_CHECKOUT_DONT_OVERWRITE_IGNORED,
        conflict_style_merge = GIT_CHECKOUT_CONFLICT_STYLE_MERGE,
        conflict_style_diff3 = GIT_CHECKOUT_CONFLICT_STYLE_DIFF3,
        dont_remove_existing = GIT_CHECKOUT_DONT_REMOVE_EXISTING,
        dont_write_index = GIT_CHECKOUT_DONT_WRITE_INDEX,
        update_submodules = GIT_CHECKOUT_UPDATE_SUBMODULES,
        update_submodules_if_changed = GIT_CHECKOUT_UPDATE_SUBMODULES_IF_CHANGED
    };

    enum class checkout_notification_type
    {
        none = GIT_CHECKOUT_NOTIFY_NONE,
        conflict = GIT_CHECKOUT_NOTIFY_CONFLICT,
        dirty = GIT_CHECKOUT_NOTIFY_DIRTY,
        updated = GIT_CHECKOUT_NOTIFY_UPDATED,
        untracked = GIT_CHECKOUT_NOTIFY_UNTRACKED,
        ignored = GIT_CHECKOUT_NOTIFY_IGNORED,
        all = GIT_CHECKOUT_NOTIFY_ALL
    };

    struct checkout_progress_status
    {
        std::string path;
        std::size_t completed_steps;
        std::size_t total_steps;

        checkout_progress_status() = default;
        checkout_progress_status(
            const char* path,
            std::size_t completed_steps,
            std::size_t total_steps);
    };

    struct checkout_notify_status
    {
        checkout_notification_type why;
        std::string path;
        diff_file baseline;
        diff_file target;
        diff_file workdir;

        checkout_notify_status() = default;
        checkout_notify_status(
            git_checkout_notify_t why,
            const char* path,
            const git_diff_file* baseline,
            const git_diff_file* target,
            const git_diff_file* workdir);
    };

    using checkout_progress_callback = std::function<void(checkout_progress_status&&)>;
    using checkout_notify_callback = std::function<int(checkout_notify_status&&)>;

    struct checkout_options
    {
        checkout_options& strategy(checkout_strategy strategy);
        checkout_options& disable_filters(bool disable);
        checkout_options& directory_mode(unsigned int mode);
        checkout_options& file_mode(unsigned int mode);
        checkout_options& notifcation_types(checkout_notification_type types);
        checkout_options& paths(const std::vector<char*>& paths);
        checkout_options& target_directory(const std::string& directory);
        checkout_options& ancestor_label(const std::string& label);
        checkout_options& our_label(const std::string& label);
        checkout_options& their_label(const std::string& label);

        template <typename T>
        checkout_options& notify_callback(const T& callback);

        template <typename T>
        checkout_options& progress_callback(const T& callback);

        git_checkout_options build();

      private:
        // TODO(gustorn):
        // 1) How to expose file_open_flags in a cross-platform manner? Docs refer to open(2) flags
        // 2) Add baseline, baseline_index, perfdata
        stx::optional<checkout_strategy> strategy_;
        stx::optional<bool> disable_filters_;
        stx::optional<unsigned int> dir_mode_;
        stx::optional<unsigned int> file_mode_;
        stx::optional<int> file_open_flags_;
        stx::optional<checkout_notification_type> notify_flags_;
        stx::optional<checkout_notify_callback> notify_callback_;
        stx::optional<checkout_progress_callback> progress_callback_;
        stx::optional<std::vector<char*>> paths_;
        stx::optional<std::string> target_directory_;
        stx::optional<std::string> ancestor_label_;
        stx::optional<std::string> our_label_;
        stx::optional<std::string> their_label_;
    };

    checkout_strategy operator|(checkout_strategy a, checkout_strategy b);
    checkout_strategy operator&(checkout_strategy a, checkout_strategy b);
    checkout_notification_type operator|(
        checkout_notification_type a,
        checkout_notification_type b);
    checkout_notification_type operator&(
        checkout_notification_type a,
        checkout_notification_type b);

    template <typename T>
    checkout_options& checkout_options::notify_callback(const T& callback)
    {
        notify_callback_ = callback;
        return *this;
    }

    template <typename T>
    checkout_options& checkout_options::progress_callback(const T& callback)
    {
        progress_callback_ = callback;
        return *this;
    }
}

#endif
