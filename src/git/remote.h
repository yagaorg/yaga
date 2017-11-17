#ifndef YAGA_GIT_REMOTE_H
#define YAGA_GIT_REMOTE_H

#include <git2.h>
#include <stx/optional.hpp>

namespace yaga_git
{
    enum class autotag_option
    {
        unspecified = GIT_REMOTE_DOWNLOAD_TAGS_UNSPECIFIED,
        automatic = GIT_REMOTE_DOWNLOAD_TAGS_AUTO,
        none = GIT_REMOTE_DOWNLOAD_TAGS_NONE,
        all = GIT_REMOTE_DOWNLOAD_TAGS_ALL
    };

    enum class fetch_prune
    {
        unspecified = GIT_FETCH_PRUNE_UNSPECIFIED,
        prune = GIT_FETCH_PRUNE,
        no_prune = GIT_FETCH_NO_PRUNE,
    };

    struct fetch_options
    {
        fetch_options& prune(fetch_prune prune);
        fetch_options& update_fetchhead(bool update);
        fetch_options& download_tags(autotag_option option);

        git_fetch_options build() const;

      private:
        // TODO(gustorn): add remote callbacks, proxy options, headers
        stx::optional<fetch_prune> prune_;
        stx::optional<bool> update_fetchhead_;
        stx::optional<autotag_option> download_tags_;
    };
}

#endif
