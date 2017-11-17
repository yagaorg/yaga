#include "remote.h"

namespace yaga {
namespace git {

fetch_options& fetch_options::prune(fetch_prune prune) {
    prune_ = prune;
    return *this;
}

fetch_options& fetch_options::update_fetchhead(bool update) {
    update_fetchhead_ = update;
    return *this;
}

fetch_options& fetch_options::download_tags(autotag_option option) {
    download_tags_ = option;
    return *this;
}

git_fetch_options fetch_options::build() const {
    git_fetch_options options = GIT_FETCH_OPTIONS_INIT;

    if (prune_) {
        options.prune = static_cast<git_fetch_prune_t>(prune_.value());
    }

    if (update_fetchhead_) {
        options.update_fetchhead = update_fetchhead_.value();
    }

    if (download_tags_) {
        options.download_tags = static_cast<git_remote_autotag_option_t>(download_tags_.value());
    }

    return options;
}

}  // namespace git
}  // namespace yaga
